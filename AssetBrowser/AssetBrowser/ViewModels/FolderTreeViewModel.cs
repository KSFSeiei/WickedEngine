using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Threading;

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
    class FolderTreeViewModel : ViewModel
    {
        #region 公開プロパティ

        /// <summary>
        /// 
        /// </summary>
        private ReadOnlyDispatcherCollection<TreeBaseItemViewModel> _Items;
        public ReadOnlyDispatcherCollection<TreeBaseItemViewModel> Items
        {
            get => _Items;
            set => RaisePropertyChangedIfSet(ref _Items, value);
        }

        #endregion

        #region 公開フィールド

        #endregion

        #region 非公開フィールド

        /// <summary>
        /// 
        /// </summary>
        private AssetManager _AssetManager;

        /// <summary>
        /// 
        /// </summary>
        private PropertyChangedEventListener _AssetBrowserListener;

        /// <summary>
        /// 
        /// </summary>
        const string _SaveName = "FolderTree.vm";

        /// <summary>
        /// 
        /// </summary>
        private int _Id;

        static private int _InstanceCount = 0;

        #endregion

        #region 公開メソッド

        /// <summary>
        /// コンストラクタ
        /// </summary>
        public FolderTreeViewModel()
        {
            _Id = _InstanceCount++;

            _AssetManager = AssetManager.GetInstance();
            _AssetBrowserListener   = new PropertyChangedEventListener(_AssetManager, AssetBrowserEvent);
            DispatcherCollection<TreeBaseItemViewModel> dispatcherItems = new DispatcherCollection<TreeBaseItemViewModel>(DispatcherHelper.UIDispatcher);
            dispatcherItems.Add(new TreeFolderItemViewModel(_AssetManager.RootFolder, this, null));
            //データの読み込み
            try
            {
                Dictionary<string, TreeBaseItemData> list = DataManager.LoadModelData<Dictionary<string, TreeBaseItemData>>(_SaveName + _Id.ToString());
                dispatcherItems.FirstOrDefault().SetLoadData(list);
            }
            catch { }

            _Items = new ReadOnlyDispatcherCollection<TreeBaseItemViewModel>(dispatcherItems);
            

            //Disposeするものをまとめておく
            CompositeDisposable.Add(_AssetBrowserListener);
            CompositeDisposable.Add(_Items.First());
        }

        /// <summary>
        /// フォルダモデルの変更イベント
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="args"></param>
        public void AssetBrowserEvent(object obj, PropertyChangedEventArgs args)
        {
            //if (args.PropertyName == nameof(_AssetBrowserModel.FolderSort))
            //{
            //    SortType = _AssetBrowserModel.FolderSort;
            //}
            //else if (args.PropertyName == nameof(_AssetBrowserModel.SelectModel))
            //{
            //    SelectModel = _AssetBrowserModel.SelectModel;
            //}
        }

        #endregion

        #region 非公開メソッド

        /// <summary>
        /// 終了処理
        /// </summary>
        /// <param name="disposing"></param>
        protected override void Dispose(bool disposing)
        {
            //データの書き出し
            Dictionary<string, TreeBaseItemData> list = new Dictionary<string, TreeBaseItemData>();
            _Items.First().CreateFolderData(list);
            DataManager.SaveModelData(_SaveName + _Id.ToString(), list);

            base.Dispose(disposing);
        }


        #endregion
    }
}
