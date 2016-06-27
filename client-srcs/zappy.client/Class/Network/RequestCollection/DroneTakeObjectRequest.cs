using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zappy.Client.Network.RequestCollection
{
    class DroneTakeObjectRequest : GenericRequest
    {
        private Drone ThisDrone { get; set; }
        private RessourceType RessourceRequest { get; set; }

        public DroneTakeObjectRequest(Drone _drone)
        {
            ThisDrone = _drone;
        }

        public void SetRequest(RessourceType _ressource)
        {
            this.RessourceRequest = _ressource;
            SetDataToSend(String.Format("{ {0} }", _ressource.ToString().ToLower()));
        }

    }
}
