using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zappy.Client.Network.RequestCollection
{
    public class BroadcastRequest : GenericRequest
    {
        public BroadcastRequest(string message)
        {
            message = String.Format("{0} {1} {2}", 
                                    Constantes.NETWORK_REQUEST_DRONE_BROADCAST,
                                    message,
                                    "\n");
            SetDataToSend(message);
        }
    }
}
