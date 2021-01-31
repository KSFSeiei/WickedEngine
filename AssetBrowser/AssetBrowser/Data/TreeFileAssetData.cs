using System.Runtime.Serialization;

namespace AssetBrowser.Data
{
    [DataContract]
    class TreeAssetItemData : TreeBaseItemData
    {
        #region プロパティ
        [DataMember]
        public bool IsChanged { get; set; }
        #endregion

        #region 公開処理
        /// <summary>
        /// コンストラクタ
        /// </summary>
        public TreeAssetItemData() { }

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
