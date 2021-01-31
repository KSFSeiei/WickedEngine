using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Livet;
using AssetBrowser.Data;

namespace AssetBrowser.Models
{
    /// <summary>
    /// 
    /// </summary>
    class BaseItemModel : NotificationObject
    {
        #region 公開プロパティ

        #endregion

        #region 公開フィールド

        #endregion

        #region 非公開フィールド

        protected string _Path;
        public string Path
        {
            get => _Path;
            protected internal set => RaisePropertyChangedIfSet(ref _Path, value);
        }

        public string OriginalPath
        {
            get => _OriginalPath;
        }

        protected string _Name;
        protected string _OriginalPath;
        protected string _OriginalName;


        protected FolderItemModel _ParentFolder;

        #endregion

        #region 公開メソッド

        #endregion

        #region 非公開メソッド

        /// <summary>
        /// フォルダを最新の状態に更新
        /// </summary>
        virtual protected internal void AdjustToOriginal() { }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        virtual public string GetDisplayName()
        {
            //if (_IsUseAlias)
            //    return _Alias;

            return _Name;
        }

        /// <summary>
        /// モデルを新規生成する処理(ロード失敗時)
        /// </summary>
        /// <param name="parent"></param>
        /// <param name="path"></param>
        protected virtual void BaseInitCreateData(FolderItemModel parent, string path)
        {
            _ParentFolder   = parent;
            _Path           = path;
            _Name           = path.Remove(0, parent.OriginalPath.Length + 1);
            _OriginalPath   = path;
            _OriginalName   = _Name;
        }

        /// <summary>
        /// モデルを保存データから再生成する処理(ロード成功時)
        /// </summary>
        /// <param name="models"></param>
        /// <param name="data"></param>
        protected void BaseInitLoadData(List<BaseItemModel> models, BaseItemData data)
        {
            if (data.ParentIndex >= 0)
            {
                _ParentFolder = models[data.ParentIndex] as FolderItemModel;
            }
            _Path = data.Path;
            _Name = data.Name;
            _OriginalPath = data.OriginalPath;
            _OriginalName = data.OriginalName;
            //_Alias = data.Alias;
            //_IsUseAlias = data.IsUseAlias;
            //CheckUseAlias(_Alias);

            var parent = _ParentFolder as FolderItemModel;
            if (parent != null)
            {
                parent.Children.Add(this);
            }
        }

        #endregion
    }
}
