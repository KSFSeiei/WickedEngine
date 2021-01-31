using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;

using AssetBrowser.ViewModels;

namespace AssetBrowser.Converter
{
    public class LeftMarginMultiplierConverter : IValueConverter
    {
        public double Length { get; set; }

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var item = value as TreeBaseItemViewModel;
            if (item == null)
                return new Thickness(0);
            int count = -1;
            while (item != null)
            {
                count++;
                item = item.Parent;
            }

            return new Thickness(Length * count, 0, 0, 0);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new System.NotImplementedException();
        }
    }
}
