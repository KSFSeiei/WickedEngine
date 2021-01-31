using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;

namespace AssetBrowser.Data
{
    [DataContract]
    class FolderItemData : BaseItemData
    {
        #region プロパティ
        [DataMember]
        public bool IsDeleted { get; set; }

        [DataMember]
        public List<string> OriginalChildrenPath { get; set; }
        #endregion

        #region フィールド
        #endregion

        #region 公開処理
        /// <summary>
        /// コンストラクタ
        /// </summary>
        public FolderItemData() { }

        /// <summary>
        /// 継承元のデータをセットする処理
        /// </summary>
        /// <param name="data"></param>
        public void SetData(FolderItemData data)
        {
            base.SetData(data);
            OriginalChildrenPath = data.OriginalChildrenPath;
            IsDeleted = data.IsDeleted;
        }
        #endregion

        #region 非公開処理
        #endregion
    }
}
