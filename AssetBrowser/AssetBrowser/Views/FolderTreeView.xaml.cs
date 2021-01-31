using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using AssetBrowser.ViewModels;

namespace AssetBrowser.Views
{
    /// <summary>
    /// FolderTreeView.xaml の相互作用ロジック
    /// </summary>
    public partial class FolderTreeView : UserControl
    {
        public FolderTreeView()
        {
            InitializeComponent();
            Dispatcher.ShutdownStarted += CloseEvent;
        }

        /// <summary>
        /// 終了イベント
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="args"></param>
        private void CloseEvent(object obj, EventArgs args)
        {
            _FolderTreeVM.Dispose();
            Dispatcher.ShutdownStarted -= CloseEvent;
        }
    }
}
