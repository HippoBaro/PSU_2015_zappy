using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Zappy.Client.MapSystem;

namespace Zappy.Client.Class
{
    public class Item
    {
        public RessourceType Type { get { return (_type); } }
        private RessourceType _type { get; set; }

        public Item(RessourceType type)
        {
            _type = type;
        }

        public override string ToString()
        {
            return (Enum.GetName(typeof(RessourceType), _type));
        }
    }
}
