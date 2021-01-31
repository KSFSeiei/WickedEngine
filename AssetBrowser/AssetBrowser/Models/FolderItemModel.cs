using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

using Livet;

namespace AssetBrowser.Models
{
    class FolderItemModel : BaseItemModel
    {
        #region 公開定義

        #endregion

        #region 非公開定義

        #endregion

        #region 公開プロパティ

        /// <summary>
        /// 子ども
        /// </summary>
        protected ObservableCollection<BaseItemModel> _Children = new ObservableCollection<BaseItemModel>();
        public ObservableCollection<BaseItemModel> Children
        {
            get => _Children;
            private set => RaisePropertyChangedIfSet(ref _Children, value);
        }

        bool _IsDeleted;
        public bool IsDeleted
        {
            get => _IsDeleted;
            private set => RaisePropertyChangedIfSet(ref _IsDeleted, value);
        }

        #endregion

        #region 公開フィールド

        #endregion

        #region 非公開フィールド

        /// <summary>
        /// 
        /// </summary>
        protected List<string> _OriginalChildrenPath;

        #endregion

        #region 公開メソッド

        /// <summary>
        /// フォルダを最新の状態に更新
        /// </summary>
        override protected internal void AdjustToOriginal()
        {
            HashSet<string> oldChildrenPath;
            if (_OriginalChildrenPath != null)
            {
                oldChildrenPath = new HashSet<string>(_OriginalChildrenPath);
            }
            else
            {
                oldChildrenPath = new HashSet<string>();
            }

            string[] newFoldersPath = null;
            string[] newFilesPath = null;
            List<string> newChildrenPath = new List<string>();

            // 指定のフォルダが存在するか確認
            if (System.IO.Directory.Exists(_OriginalPath))
            {
                newFoldersPath = System.IO.Directory.GetDirectories(_OriginalPath);
                newFilesPath = System.IO.Directory.GetFiles(_OriginalPath);
                IsDeleted = false;
            }
            else
            {
                IsDeleted = true;
                // 子供を更新
                BaseItemModel[] children = _Children.ToArray();
                foreach (BaseItemModel child in children)
                {
                    child.AdjustToOriginal();
                }
                // 子供がいなければ死ぬ
                if (_Children.Count == 0)
                {
                    //_ParentFolder.RemoveChildren(this);
                }
                return;
            }

            bool isUpdate = false;

            // フォルダの更新
            foreach (string path in newFoldersPath)
            {
                // 既に存在する場合newChildrenPathに追加してはoldFoldersPathから削除
                if (oldChildrenPath.Contains(path))
                {
                    newChildrenPath.Add(path);
                }
                // 存在しないパスであればnewChildrenPathに追加してモデルを生成
                else
                {
                    newChildrenPath.Add(path);
                    _Children.Add(new FolderItemModel(this, path));
                    isUpdate = true;
                }
            }

            // ファイルの更新
            foreach (string path in newFilesPath)
            {
                // 既に存在する場合は追加する必要がないのでnewFoldersPathから削除
                if (oldChildrenPath.Contains(path))
                {
                    newChildrenPath.Add(path);
                }
                // 存在しないパスであれば子供に追加
                else
                {
                    newChildrenPath.Add(path);
                    _Children.Add(new AssetItemModel(this, path));
                    isUpdate = true;
                }
            }

            // パスリストを更新
            _OriginalChildrenPath = newChildrenPath;

            // 子供を更新
            for (int i = 0; i < _Children.Count; i++)
            {
                _Children[i].AdjustToOriginal();
            }

            if (isUpdate)
            {
                RaisePropertyChanged(nameof(Children));
            }
        }



        #endregion

        #region 非公開メソッド

        /// <summary>
        /// コンストラクタ（RootItemModel用）
        /// </summary>
        protected FolderItemModel() 
        { 
            _Children = new ObservableCollection<BaseItemModel>(); 
        }

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="parent"></param>
        /// <param name="path"></param>
        protected FolderItemModel(FolderItemModel parent, string path)
        {
            BaseInitCreateData(parent, path);
        }

        /// <summary>
        /// モデルを新規生成する処理(ロード失敗時)
        /// </summary>
        /// <param name="parent"></param>
        /// <param name="path"></param>
        protected override void BaseInitCreateData(FolderItemModel parent, string path)
        {
            base.BaseInitCreateData(parent, path);
            //_Type = ItemDataType.Folder;
            _Children = new ObservableCollection<BaseItemModel>();
        }

        #endregion
    }
}
