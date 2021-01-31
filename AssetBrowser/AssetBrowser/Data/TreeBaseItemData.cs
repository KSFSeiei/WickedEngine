using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;


namespace AssetBrowser.Data
{
    [DataContract]
    [KnownType(typeof(TreeFolderItemData))]
    [KnownType(typeof(TreeAssetItemData))]
    class TreeBaseItemData
    {
        #region プロパティ
        [DataMember]
        public int ParentIndex { get; set; }

        [DataMember]
        public string Name { get; set; }

        [DataMember]
        public string Path { get; set; }

        [DataMember]
        public int Type { get; set; }

        [DataMember]
        public bool IsUseAlias { get; set; }

        #endregion

        #region フィールド
        #endregion

        #region 公開処理
        /// <summary>
        /// コンストラクタ
        /// </summary>
        public TreeBaseItemData() { }

        /// <summary>
        /// データのセット用
        /// </summary>
        /// <param name="data"></param>
        public void SetBaseData(TreeBaseItemData data)
        {
            ParentIndex = data.ParentIndex;
            Path = data.Path;
            Name = data.Name;
            Type = data.Type;
            IsUseAlias = data.IsUseAlias;
        }
        #endregion


        #region 非公開処理
        #endregion
    }
}
