using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Collections.ObjectModel;

using Livet;
using Livet.Commands;
using Livet.Messaging;
using Livet.Messaging.IO;
using Livet.EventListeners;
using Livet.Messaging.Windows;

using AssetBrowser.Models;

namespace AssetBrowser.ViewModels
{
    class AssetListViewModel : ViewModel
    {
        #region 公開定義

        #endregion

        #region 非公開定義

        #endregion

        #region 公開プロパティ

        private ObservableCollection<AssetItemViewModel> _Items;
        public ObservableCollection<AssetItemViewModel> Items
        {
            get => _Items;
            set => RaisePropertyChangedIfSet(ref _Items, value);
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
        public AssetListViewModel()
        {
            _Items = new ObservableCollection<AssetItemViewModel>();
        }

        #endregion

        #region 非公開メソッド

        #endregion
    }
}
