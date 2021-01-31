using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using System.Diagnostics;
using Livet;

namespace AssetBrowser.Models
{
    /// <summary>
    /// Rootアイテム
    /// </summary>
    class RootItemModel : FolderItemModel
    {
        #region 公開プロパティ
       

        #endregion

        #region 公開フィールド

        #endregion

        #region 非公開フィールド

        #endregion

        #region 公開メソッド

        /// <summary>
        /// ルートフォルダのセット
        /// </summary>
        /// <param name="path"></param>
        /// <param name="name"></param>
        public void SetRootFolder(string path, string name)
        {
            _Path           = path;
            _Name           = name;
            _OriginalPath   = path;
            _OriginalName   = name;
            AdjustToOriginal();
            //UpdateFileHash();
        }


        /// <summary>
        /// コンストラクタ
        /// </summary>
        public RootItemModel()
        {
            _Children = new ObservableCollection<BaseItemModel>();
        }

        #endregion

        #region 非公開メソッド
        #endregion
    }
}
