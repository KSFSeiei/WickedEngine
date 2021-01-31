using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;

namespace AssetBrowser.Data
{
    public enum ItemDataType
    {
        Unknown,
        Root,
        Folder,
        File,
    }

    [DataContract]
    [KnownType(typeof(FileItemData))]
    [KnownType(typeof(FolderItemData))]
    class BaseItemData
    {
        #region プロパティ
        [DataMember]
        public int ParentIndex { get; set; }

        [DataMember]
        public string Path { get; set; }

        [DataMember]
        public string Name { get; set; }

        [DataMember]
        public string OriginalPath { get; set; }

        [DataMember]
        public string OriginalName { get; set; }

        [DataMember]
        public string Alias { get; set; }

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
        public BaseItemData() { }

        /// <summary>
        /// データのセット用
        /// </summary>
        /// <param name="data"></param>
        public void SetData(BaseItemData data)
        {
            ParentIndex = data.ParentIndex;
            Path = data.Path;
            Name = data.Name;
            OriginalPath = data.OriginalPath;
            OriginalName = data.OriginalName;
            Alias = data.Alias;
            Type = data.Type;
            IsUseAlias = data.IsUseAlias;
        }
        #endregion
    }
}
