using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

using Livet;
using Livet.Commands;
using Livet.Messaging;
using Livet.Messaging.IO;
using Livet.EventListeners;
using Livet.Messaging.Windows;

using AssetBrowser.Models;
using AssetBrowser.Data;

namespace AssetBrowser.ViewModels
{
    class TreeFolderItemViewModel : TreeBaseItemViewModel
    {
        private ReadOnlyDispatcherCollection<TreeBaseItemViewModel> _Children;
        override public ReadOnlyDispatcherCollection<TreeBaseItemViewModel> Children
        {
            get => _Children;
            set => RaisePropertyChangedIfSet(ref _Children, value);
        }

        private bool _IsExpanded;
        override public bool IsExpanded
        {
            get => _IsExpanded;
            set
            {
                //_EntryTreeVM.UpdataItemCount++;
                RaisePropertyChangedIfSet(ref _IsExpanded, value);
                //_EntryTreeVM.UpdataItemCount--;
            }
        }

        /// <summary>
        /// コンストラクタ（ロード失敗時）
        /// </summary>
        /// <param name="folder"></param>
        /// <param name="entryTree"></param>
        /// <param name="parent"></param>
        public TreeFolderItemViewModel(FolderItemModel folder, FolderTreeViewModel entryTree, TreeBaseItemViewModel parent)
        {
            base.BaseInitCreateData(folder, entryTree, parent);
            //_Type = ItemDataType.Folder;
            //_IsDeleted = folder.IsDeleted;
            UpdateChildren();
            CompositeDisposable.Add(_Children);
        }

        /// <summary>
        /// 所持している子供を更新（ソートも行う）
        /// </summary>
        private void UpdateChildren()
        {
            //// 子供の更新カウンタを増加
            //_EntryTreeVM.UpdataItemCount++;

            Children = ViewModelHelper.CreateReadOnlyDispatcherCollection(
             ((FolderItemModel)_Model).Children,
             x => CreateChild(x),
             DispatcherHelper.UIDispatcher);

            // ソートを行う
            //SortChildren();

            //// 子供の更新カウンタを減少
            //_EntryTreeVM.UpdataItemCount--;
        }

        /// <summary>
        /// 子供の生成処理
        /// </summary>
        /// <param name="model"></param>
        /// <param name="virtualPath"></param>
        /// <returns></returns>
        private TreeBaseItemViewModel CreateChild(BaseItemModel model)
        {
            if( model is FolderItemModel)
            {
                return new TreeFolderItemViewModel((FolderItemModel)model, _EntryTreeVM, this);
            }
            else if (model is AssetItemModel )
            {
                return new TreeAssetItemViewModel((AssetItemModel)model, _EntryTreeVM, this);
            }
            else
            {
                //Debug.Assert(false, "不明なモデルタイプを検知しました。");
            }

            return null;
        }

        /// <summary>
        /// 保存用のデータ生成処理
        /// </summary>
        /// <param name="list"></param>
        /// <param name="parentIndex"></param>
        override public void CreateFolderData(Dictionary<string, TreeBaseItemData> list)
        {
            list[_Path] = CreateItemData();
            foreach (TreeBaseItemViewModel child in _Children)
            {
                child.CreateFolderData(list);
            }
        }

        /// <summary>
        /// モデルデータをデータクラスに変換する処理
        /// </summary>
        /// <param name="parentIndex"></param>
        /// <returns></returns>
        protected internal new TreeFolderItemData CreateItemData()
        {
            TreeFolderItemData data = new TreeFolderItemData();
            data.SetBaseData(base.CreateItemData());
            data.IsExpanded = _IsExpanded;
            return data;
        }

        /// <summary>
        /// ロードデータをセットする処理（公開用）
        /// </summary>
        /// <param name="list"></param>
        override public void SetLoadData(Dictionary<string, TreeBaseItemData> list)
        {
            TreeFolderItemData data = null;
            if (list != null)
            {
                data = list[_Model.Path] as TreeFolderItemData;
                if (data != null)
                {
                    SetLoadData(data);
                }
            }
            foreach (TreeBaseItemViewModel child in _Children)
            {
                child.SetLoadData(list);
            }
        }

        /// <summary>
        /// ロードデータの設定処理
        /// </summary>
        /// <param name="data"></param>
        protected internal void SetLoadData(TreeFolderItemData data)
        {
            base.SetLoadData(data);
            _IsExpanded = data.IsExpanded;
        }
    }
}
