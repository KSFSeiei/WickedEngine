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
    class TreeAssetItemViewModel : TreeBaseItemViewModel
    {
        /// <summary>
        /// コンストラクタ（ロード失敗時）
        /// </summary>
        /// <param name="folder"></param>
        /// <param name="entryTree"></param>
        /// <param name="parent"></param>
        public TreeAssetItemViewModel(AssetItemModel file, FolderTreeViewModel entryTree, TreeBaseItemViewModel parent)
        {
            base.BaseInitCreateData(file, entryTree, parent);
            //_IsChanged = file.IsChanged;
        }
    }
}
