using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataTool
{
    public class EventHandler
    {
        public Action<string>   ChangeStatus { get; set; } = null;
        public Action           ChangeProgress { get; set; } = null;
        public Action<string>   LoadEnd { get; set; } = null;
        public Action<string>   ShowMessageBox { get; set; } = null;
    }
}
