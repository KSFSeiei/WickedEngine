using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace AssetBrowser.Data
{
    class DataManager
    {
        #region 公開定義

        #endregion

        #region 非公開定義

        #endregion

        #region 公開プロパティ

        /// <summary>
        /// インスタンスの取得
        /// </summary>
        /// <returns></returns>
        static public DataManager GetInstance()
        {
            if (_Instance == null)
            {
                _Instance = new DataManager();
            }
            return _Instance;
        }

        #endregion

        #region 公開フィールド

        #endregion

        #region 非公開フィールド

        static private DataManager _Instance;
        private StringBuilder _LoadErrorFiles;
        private StringBuilder _SaveErrorFiles;

        #endregion

        #region 公開メソッド

        /// <summary>
        /// モデルデータ書き出し処理
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="name"></param>
        /// <param name="data"></param>
        /// <param name="typeList"></param>
        /// <returns></returns>
        static public bool SaveModelData<T>(string name, T data, IEnumerable<Type> typeList = null)
        {
            string tempName = name + ".json.temp";
            string fileName = name + ".json";
            using (var fs = new FileStream(tempName.ToString(), FileMode.Create))
            using (var writer = JsonReaderWriterFactory.CreateJsonWriter(fs, Encoding.UTF8, true, true, "  "))
            {
                DataContractJsonSerializer serializer;
                if (typeList == null)
                {
                    serializer = new DataContractJsonSerializer(data.GetType());
                }
                else
                {
                    serializer = new DataContractJsonSerializer(data.GetType(), typeList);
                }
                try
                {
                    serializer.WriteObject(writer, data);
                }
                catch
                {
                    //失敗した場合はエラーメッセージをためておく
                    GetInstance()._SaveErrorFiles.AppendLine(fileName.ToString());
                    return false;
                }
            }
            try
            {
                File.Delete(fileName);
                File.Move(tempName.ToString(), fileName);
            }
            catch
            {
                //失敗した場合はエラーメッセージをためておく
                GetInstance()._SaveErrorFiles.AppendLine(fileName.ToString());
            }
            return true;
        }

        /// <summary>
        /// モデルデータの読み込み処理
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="name"></param>
        /// <param name="data"></param>
        /// <param name="typeList"></param>
        /// <returns></returns>
        static public T LoadModelData<T>(string name, IEnumerable<Type> typeList = null)
        {
            string fileName = name + ".json";
            T data;
            using (var fs = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                DataContractJsonSerializer serializer;
                if (typeList == null)
                {
                    serializer = new DataContractJsonSerializer(typeof(T));
                }
                else
                {
                    serializer = new DataContractJsonSerializer(typeof(T), typeList);
                }

                fs.Position = 0;
                try
                {
                    data = (T)serializer.ReadObject(fs);
                }
                catch
                {
                    //失敗した場合はエラーメッセージをためておく
                    GetInstance()._LoadErrorFiles.AppendLine(fileName.ToString());
                    return default(T);
                }
            }
            return data;
        }

        /// <summary>
        /// セーブ時に発生したエラーメッセージをダイアログに表示するイベント
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="args"></param>
        static public void SaveMessageEvent(object obj, EventArgs args)
        {
            if (_Instance != null)
            {
                _Instance.ShowSaveErrorMessage();
            }
        }

        /// <summary>
        /// ロード時に発生したエラーメッセージをダイアログに表示するイベント
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="args"></param>
        static public void LoadMessageEvent(object obj, EventArgs args)
        {
            if (_Instance != null)
            {
                _Instance.ShowLoadErrorMessage();
            }
        }

        #endregion

        #region 非公開メソッド

        /// <summary>
        /// コンストラクタ
        /// </summary>
        private DataManager()
        {
            _LoadErrorFiles = new StringBuilder();
            _SaveErrorFiles = new StringBuilder();
        }

        /// <summary>
        /// セーブ時に発生したエラーメッセージをダイアログに表示
        /// </summary>
        private void ShowSaveErrorMessage()
        {
            if (!string.IsNullOrEmpty(_SaveErrorFiles.ToString()))
            {
                _SaveErrorFiles.Append("\nの保存に失敗しました");
                MessageBox.Show(_SaveErrorFiles.ToString());
                _SaveErrorFiles.Clear();
            }
        }

        /// <summary>
        /// ロード時に発生したエラーメッセージをダイアログに表示
        /// </summary>
        private void ShowLoadErrorMessage()
        {
            if (!string.IsNullOrEmpty(_LoadErrorFiles.ToString()))
            {
                _LoadErrorFiles.Append("\nが存在していない、もしくは破損している可能性があります");
                MessageBox.Show(_LoadErrorFiles.ToString());
                _LoadErrorFiles.Clear();
            }
        }

        #endregion
    }
}
