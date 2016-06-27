using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zappy.Client.Network.RequestCollection
{
    public enum DroneRequestType
    {
        UNKNOW,
        FORWARD,
        INVENTORY,
        TURN_LEFT,
        TURN_RIGHT,
        EXPULSE,
        FORK,
        SEE
    }

    public class DroneManagementRequest : GenericRequest
    {
        private Drone ThisDrone { get; set; }
        private DroneRequestType Request { get; set; }

        public DroneManagementRequest(Drone _drone)
        {
            ThisDrone = _drone;
        }

        public void SetRequest(DroneRequestType _request)
        {
            if (_request == DroneRequestType.FORWARD)
                SetDataToSend(Constantes.NETWORK_REQUEST_MOVE_FORWARD);
            if (_request == DroneRequestType.TURN_RIGHT)
                SetDataToSend(Constantes.NETWORK_REQUEST_TURN_RIGHT);
            if (_request == DroneRequestType.TURN_LEFT)
                SetDataToSend(Constantes.NETWORK_REQUEST_TURN_LEFT);
            if (_request == DroneRequestType.EXPULSE)
                SetDataToSend(Constantes.NETWORK_REQUEST_DRONE_EXPULSE);
            if (_request == DroneRequestType.FORK)
                SetDataToSend(Constantes.NETWORK_REQUEST_DRONE_FORK);
            if (_request == DroneRequestType.SEE)
                SetDataToSend(Constantes.NETWORK_REQUEST_DRONE_SEE);
            if (_request == DroneRequestType.INVENTORY)
                SetDataToSend(Constantes.NETWORK_REQUEST_DRONE_INVENTAIRE);
        }

        public override void OnRequest_Arrived()
        {
            // First -> base
            base.OnRequest_Arrived();

            if (this.STATUS == StatusType.OK)
            {
                if (Request == DroneRequestType.FORWARD)
                    ThisDrone.MoveFoward();
                if (Request == DroneRequestType.TURN_RIGHT)
                    ThisDrone.Turn90DegreeesRight();
                if (Request == DroneRequestType.TURN_LEFT)
                    ThisDrone.Turn90DegreeesLeft();
                if (Request == DroneRequestType.SEE)
                    ThisDrone.ApplySight(this.GetData());
                if (Request == DroneRequestType.INVENTORY)
                    ThisDrone.ApplyInventory(this.GetData());
            }
        }
    }
}
