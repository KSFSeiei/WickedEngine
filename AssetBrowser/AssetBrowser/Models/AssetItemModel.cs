using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AssetBrowser.Models
{
    class AssetItemModel : BaseItemModel
    {
        /// <summary>
        /// コンストラクタ(新規)
        /// </summary>
        protected internal AssetItemModel(FolderItemModel parent, string path)
        {
            BaseInitCreateData(parent, path);
        }
    }
}
