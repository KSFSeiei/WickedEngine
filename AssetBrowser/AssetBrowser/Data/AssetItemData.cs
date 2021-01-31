using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization;

namespace AssetBrowser.Data
{
    [DataContract]
    class FileItemData : BaseItemData
    {
        #region プロパティ
        [DataMember]
        public byte[] FileHash { get; set; }
        [DataMember]
        public bool IsChanged { get; set; }
        [DataMember]
        public FileInfo Info { get; set; }
        [DataMember]
        public DateTime Time { get; set; }
        #endregion

        #region フィールド
        #endregion

        #region 公開処理
        /// <summary>
        /// コンストラクタ
        /// </summary>
        public FileItemData() { }

        /// <summary>
        /// 継承元のデータをセットする処理
        /// </summary>
        /// <param name="data"></param>
        public void SetData(FileItemData data)
        {
            base.SetData(data);
            FileHash = data.FileHash;
            IsChanged = data.IsChanged;
            Info = data.Info;
            Time = data.Time;
        }
        #endregion
    }
}
