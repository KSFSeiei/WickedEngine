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
    class TreeBaseItemViewModel : ViewModel
    {
        protected BaseItemModel _Model;
        public BaseItemModel Model
        {
            get => _Model;
            internal protected set => RaisePropertyChangedIfSet(ref _Model, value);
        }

        protected string _Name;
        public string Name
        {
            get => _Name;
            set => RaisePropertyChangedIfSet(ref _Name, value);
        }

        /// <summary>
        /// 
        /// </summary>
        public virtual ReadOnlyDispatcherCollection<TreeBaseItemViewModel> Children { get => null; set { } }


        protected FolderTreeViewModel _EntryTreeVM;

        /// <summary>
        /// 
        /// </summary>
        protected TreeBaseItemViewModel _Parent;
        public TreeBaseItemViewModel Parent
        {
            get => _Parent;
        }

        /// <summary>
        /// 
        /// </summary>
        protected string _Path;
        public string Path
        {
            get => _Path;
            set => RaisePropertyChangedIfSet(ref _Path, value);
        }

        /// <summary>
        /// 
        /// </summary>
        virtual public bool IsExpanded { get => false; set { } }

        protected bool _IsUseAlias;

        /// <summary>
        /// モデルデータからVMを生成する処理(ロード失敗時)
        /// </summary>
        /// <param name="parentIndex"></param>
        /// <returns></returns>
        protected internal void BaseInitCreateData(BaseItemModel model, FolderTreeViewModel entryTree, TreeBaseItemViewModel parent)
        {
            _Model       = model;
            _Parent      = parent;
            _EntryTreeVM = entryTree;
            _Name        = model.GetDisplayName();
            _Path        = model.Path;
        }

        /// <summary>
        /// モデルデータをデータクラスに変換する処理
        /// </summary>
        /// <param name="parentIndex"></param>
        /// <returns></returns>
        protected internal TreeBaseItemData CreateItemData()
        {
            TreeBaseItemData data = new TreeBaseItemData();
            data.Name       = _Name;
            data.Path       = _Path;
            data.IsUseAlias = _IsUseAlias;
            return data;
        }

        /// <summary>
        /// ロードデータの設定処理
        /// </summary>
        /// <param name="data"></param>
        protected internal void SetLoadData(TreeBaseItemData data)
        {
            _Name = data.Name;
            _Path = data.Path;
            _IsUseAlias = data.IsUseAlias;
        }

        /// <summary>
        /// 保存用のデータを生成する処理
        /// </summary>
        /// <param name="list"></param>
        /// <param name="parentIndex"></param>
        virtual public void CreateFolderData(Dictionary<string, TreeBaseItemData> list)
        {
            list[_Path] = CreateItemData();
        }

        /// <summary>
        /// ロードデータをセットする処理（公開用）
        /// </summary>
        /// <param name="list"></param>
        virtual public void SetLoadData(Dictionary<string, TreeBaseItemData> list)
        {
            TreeBaseItemData data = null;
            if (list != null)
            {
                data = list[_Model.Path] as TreeBaseItemData;
                if (data != null)
                {
                    SetLoadData(data);
                }
            }
        }
    }
}
