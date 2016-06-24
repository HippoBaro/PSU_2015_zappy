using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zappy.Client
{
    public static class Constantes
    {
        public const bool IS_DEBUG = true;

        /* Generic Network */
        public const string NETWORK_REQUEST_ANSWER_OK = "ok\n";
        public const string NETWORK_REQUEST_ANSWER_KO = "ko\n";

        /* DroneManagementRequest */
        public const string NETWORK_REQUEST_MOVE_FORWARD = "avance\n";
        public const string NETWORK_REQUEST_TURN_LEFT = "gauche\n";
        public const string NETWORK_REQUEST_TURN_RIGHT = "droite\n";
        public const string NETWORK_REQUEST_DRONE_FORK = "fork\n";
        public const string NETWORK_REQUEST_DRONE_SEE = "voir\n";
        public const string NETWORK_REQUEST_DRONE_INVENTAIRE = "inventaire\n";
        public const string NETWORK_REQUEST_DRONE_EXPULSE = "expulse\n";

        /* BroadcastRequest */
        public const string NETWORK_REQUEST_DRONE_BROADCAST = "broadcast ";

        /* Drone */
        public const int DRONE_MAX_ELEVATION_LEVEL = 8;
    }
}
