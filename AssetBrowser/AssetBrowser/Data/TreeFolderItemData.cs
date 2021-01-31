using System.Runtime.Serialization;

namespace AssetBrowser.Data
{
    [DataContract]
    class TreeFolderItemData : TreeBaseItemData
    {
        #region プロパティ
        [DataMember]
        public bool IsExpanded { get; set; }

        #endregion

        #region 公開処理
        /// <summary>
        /// コンストラクタ
        /// </summary>
        public TreeFolderItemData() { }

        /// <summary>
        /// 継承元のデータをセットする処理
        /// </summary>
        /// <param name="data"></param>
        public new void SetBaseData(TreeBaseItemData data)
        {
            base.SetBaseData(data);
        }
        #endregion
    }
}
