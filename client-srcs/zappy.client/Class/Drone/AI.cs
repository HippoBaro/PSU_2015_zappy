using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zappy.Client
{
    public class AI
    {
        private Drone this_drone { get; set; }

        public AI(ref Drone _drone)
        {
            this.this_drone = _drone;
        }
    }
}
