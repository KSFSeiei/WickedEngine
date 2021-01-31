using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Livet;

namespace AssetBrowser.Models
{
    /// <summary>
    /// Assetを管理するマネジャークラス
    /// </summary>
    class AssetManager : NotificationObject
    {
        private RootItemModel _RootFolder;
        public RootItemModel RootFolder
        {
            get => _RootFolder;
        }

        /// <summary>
        /// モデルデータの読み込み処理
        /// </summary>
        /// <param name="path"></param>
        /// <param name="name"></param>
        public void LoadModelData(string path, string name)
        {
            //AssetBrowserData data = DataManager.LoadModelData<AssetBrowserData>(_SaveName);
            //if (data != null)
            //{
            //    _RootFolder.LoadData(data.Assets);
            //    _RootFolder.CheckFileHash();
            //    SelectModel = _RootFolder.SearchPath(data.SelectPath);
            //    ViewFolder = _RootFolder.SearchPath(data.ViewFolderPath) as FolderItemModel;
            //    FileSort = (FileSortType)data.FileSortType;
            //    FolderSort = (FolderSortType)data.FolderSortType;
            //    IsSplitMode = data.IsSplitMode;
            //}
            //else
            {
                _RootFolder.SetRootFolder(path, name);
            }
            RaisePropertyChanged(nameof(RootFolder));
            //EditHistory.Clear(this);
            //HistoryChanged();
        }

        #region 公開定義

        #endregion

        #region 非公開定義

        #endregion

        #region 公開プロパティ

        #endregion

        #region 公開フィールド

        #endregion

        #region 非公開フィールド

        #endregion

        #region 公開メソッド

        /// <summary>
        /// インスタンスの取得
        /// </summary>
        /// <returns></returns>
        static private AssetManager _Instance = new AssetManager();
        static public AssetManager GetInstance()
        {
            return _Instance;
        }

        #endregion

        #region 非公開メソッド

        /// <summary>
        /// コンストラクタ
        /// </summary>
        private AssetManager()
        {
            _RootFolder     = new RootItemModel();
            
        }

        #endregion
    }
}
