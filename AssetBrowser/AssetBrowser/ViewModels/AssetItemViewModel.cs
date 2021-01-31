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

namespace AssetBrowser.ViewModels
{
    class AssetItemViewModel : ViewModel
    {
        #region 公開定義

        #endregion

        #region 非公開定義

        #endregion

        #region 公開プロパティ

        /// <summary>
        /// 
        /// </summary>
        private AssetItemModel _Model;
        public BaseItemModel Model
        {
            get => _Model;
        }

        #endregion

        #region 公開フィールド

        #endregion

        #region 非公開フィールド

        #endregion

        #region 公開メソッド
       
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="file"></param>
        public AssetItemViewModel(AssetItemModel asset)
        {
            _Model      = asset;
            //_FileName = asset.GetDisplayName();
            //_IsUseAlias = asset.IsUseAlias;
            //_FilePath = asset.Path;
            //_IsChanged = asset.IsChanged;
            //_FileModelListener = new PropertyChangedEventListener(_Model, ChangedFileModel);
            //CreateToolTip();
            //CompositeDisposable.Add(_FileModelListener);

        }

        #endregion

        #region 非公開メソッド

        #endregion
    }
}
