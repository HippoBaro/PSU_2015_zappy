using System;
using System.Collections.Generic;

using Zappy.Client.Network.RequestCollection;
using Zappy.Client.MapSystem;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace Zappy.Client
{
	public class Drone
    {
		private int UID { set; get;}
        public int Level { get; set; } = 1;
        private bool IsCloned { get; set; } = false;
        public RotationState Rotation { get
            {
                return (rotation);
            }
        }
        private RotationState rotation { get; set; }

		private Map Map { get; set; }
        public  MapTile ActualMapTile { get { return (actual_maptile); } }
        private MapTile actual_maptile { get; set; } // MapTile will be set after binding @0x0
        private Dictionary<RessourceType, int> Ressources { get; set; }
        private DroneManagementRequest DroneRequest { get; set; }
        public Dictionary<RessourceType, int> Inventory
        {
            get
            {
                return (this.Ressources);
            }
        }

        /* Default constructor */
        public Drone(int UID, ref Map this_map)
		{
			this.UID = UID;
            this.rotation = RotationState.TOP;
            this.Ressources = new Dictionary<RessourceType, int>();
            this.DroneRequest = new DroneManagementRequest(this);

            // Setting Drone on map
            this.Map = this_map;
            this.actual_maptile = this_map.GetTile(0, 0);
        }

        public Drone(Drone _drone_to_copy)
        {
            this.UID = UID;
            this.rotation = _drone_to_copy.Rotation;

            // Setting Drone on map
            this.IsCloned = true;
            this.Map = _drone_to_copy.GetMap();
            this.actual_maptile = _drone_to_copy.ActualMapTile;
            this.DroneRequest = _drone_to_copy.DroneRequest;
        }

        #region DRONE SIGHT

        private static void ApplyRessourcesOnTile(MapTile maptile, int actual_tile, ref List<string> Ressources)
        {
            int count;

            count = 0;
            foreach (RessourceType type in Enum.GetValues(typeof(RessourceType)))
            {
                count = Regex.Matches(Ressources[actual_tile].ToLower(), type.ToString().ToLower()).Count;
                maptile.SetRessourceEstimation(type, count);
                if (Constantes.IS_DEBUG == true && count > 0)
                {
                    Console.WriteLine(" --> Adding [{0}] elements of type [{1}] on MapTile [{2}x{3}]",
                                            count, type.ToString(), maptile.X, maptile.Y);
                }
            }
        }

        private static void ApplyRessourceOnSightAtLevel(Drone player, ref int actual_tile, ref List<string> Ressources, int level_n)
        {
            Drone drone_forked;
            int i2;
            int i;

            i = 0;
            i2 = 0;
            drone_forked = new Drone(player);

            while (i < level_n)
            {
                drone_forked.MoveLeft_Offline();
                i++;
            }

            while (i2 < ((level_n * 2) + 1))
            {
                actual_tile++;
                ApplyRessourcesOnTile(drone_forked.ActualMapTile, actual_tile, ref Ressources);
                drone_forked.MoveRight_Offline();
                i2++;
            }
        }

        /* Fuction lunched by callback of a network request giving the sight */
        public void ApplySight(string server_sight_string)
        {
            List<string> Ressources;
            Drone ghost_drone;
            int actual_tile;
            int i;

            i = 0;
            actual_tile = 0;
            Ressources = App.ParseServerAnswerToStringList(server_sight_string);
            ApplyRessourcesOnTile(this.ActualMapTile, 0, ref Ressources);
            ghost_drone = new Drone(this);
            while (i != this.Level)
            {
                ghost_drone.MoveFoward();
                ApplyRessourceOnSightAtLevel(ghost_drone, ref (actual_tile), ref Ressources, i + 1);
                i++;
            }
        }

        #endregion

        #region CLIENT SIDE

        /* Get Actual rotation */
        public RotationState GetRotationState()
        {
            return (this.Rotation);
        }

        public void AddRessources(RessourceType type, int ressource_toadd)
        {
            if (Ressources.ContainsKey(type) == false)
            {
                Ressources.Add(type, ressource_toadd);
                return;
            }
            Ressources[type] += ressource_toadd;
        }

        public void SubstractRessources(RessourceType type, int ressource_tosubstract)
        {
            if (Ressources.ContainsKey(type) == false)
            {
                Ressources.Add(type, ressource_tosubstract);
                return;
            }
            Ressources[type] -= ressource_tosubstract;
        }

        public void SetRessource(RessourceType type, int effective_count)
        {
            if (Ressources.ContainsKey(type) == false)
            {
                Ressources.Add(type, effective_count);
                return;
            }
            Ressources[type] = effective_count;
        }

        public int GetRessourceCount(RessourceType type)
        {
            if (this.Ressources.ContainsKey(type))
                return (this.Ressources[type]);
            return (0);
        }

        /* Fuction lunched by callback of a network request giving the inventory */
        public void ApplyInventory(string server_inventory_string)
        {
            Regex regex = new Regex(@"\d+");
            List<string> Ressource;
            int value;
            int occur;

            Ressource = App.ParseServerAnswerToStringList(server_inventory_string);
            foreach (string str in Ressource)
            {
                // Getting numeric value
                Match match = regex.Match(str);
                if (match.Success)
                {
                    value = Convert.ToInt32(match.Value);
                    foreach (RessourceType type in Enum.GetValues(typeof(RessourceType)))
                    {
                        occur = Regex.Matches(str.ToLower(), type.ToString().ToLower()).Count;
                        if (occur > 0)
                        {
                            if (Constantes.IS_DEBUG == true)
                                Console.WriteLine(" --> Setting in inventory [{0}] elements of type [{1}]", value, type.ToString());
                            this.SetRessource(type, value);
                            break;
                        }
                    }
                }
            }
        }

        #endregion

        #region ASK SERVER

        /* Ask the server to move the drone forward */
        public bool MoveFoward()
        {
            if (this.Map == null)
                return (false);

            this.DroneRequest.SetRequest(DroneRequestType.FORWARD);
            App.Network.ExecuteRequest(this.DroneRequest);

            if (this.DroneRequest.STATUS == Network.StatusType.OK)
            {
                actual_maptile = actual_maptile.GetTopTile(this);
                return (true);
            }
            return (false);
        }

        /* Ask the server to move the drone forward */
        public bool See()
        {
            if (this.Map == null)
                return (false);

            this.DroneRequest.SetRequest(DroneRequestType.SEE);
            App.Network.ExecuteRequest(this.DroneRequest);

            if (this.DroneRequest.STATUS == Network.StatusType.OK)
            {
                // Handled in DroneRequest ;)
                return (true);
            }
            return (false);
        }

        /* Ask the server to move the drone 90° Drone Right */
        public bool Turn90DegreeesRight()
		{
			if (this.Map == null)
				return (false);

            this.DroneRequest.SetRequest(DroneRequestType.TURN_RIGHT);
            App.Network.ExecuteRequest(this.DroneRequest);

            if (this.DroneRequest.STATUS == Network.StatusType.OK)
            {
				if ((int)this.rotation + 90 >= 360)
					this.rotation = (RotationState) 0;
				else
					this.rotation += 90;
                return (true);
            }
            else
                return (false);
		}

		/* Ask the server to move the drone 90° Drone Left */
		public bool Turn90DegreeesLeft()
		{
			if (this.Map == null)
				return (false);

            this.DroneRequest.SetRequest(DroneRequestType.TURN_LEFT);
            App.Network.ExecuteRequest(this.DroneRequest);

            if (this.DroneRequest.STATUS == Network.StatusType.OK)
            {
				if ((int)(this.rotation - 90) < 0)
					this.rotation = (RotationState) 270;
				else
					this.rotation -= 90;
                return (true);
            }
            else
                return (false);
		}

		/* Ask the server to take a given type of object */
		public bool TakeObject(RessourceType ressource)
		{
			if (this.Map == null)
				return (false);

            using (DroneTakeObjectRequest DTOR = new DroneTakeObjectRequest(this))
            {
                App.Network.ExecuteRequest(DTOR);

                if (DTOR.STATUS == Network.StatusType.OK)
                {
                    this.AddRessources(ressource, 1);
                    return (true);
                }
            }
            return (false);
		}

		/* Ask the server to kickout a drone on this case */
		public bool ExpulseDrone()
		{
			if (this.Map == null)
				return (false);

            this.DroneRequest.SetRequest(DroneRequestType.EXPULSE);
            App.Network.ExecuteRequest(this.DroneRequest);

            if (this.DroneRequest.STATUS == Network.StatusType.OK)
            {
                return (true);
            }
            return (false);
        }

        /* Ask the server to fork a given drone as 'this' */
        public void ForkDrone()
        {
            if (this.Map == null)
                return;

            this.DroneRequest.SetRequest(DroneRequestType.FORK);
            App.Network.ExecuteRequest(this.DroneRequest);
        }

        /* Ask the server the inventory of curent drone */
        public bool UpdateInventory()
        {
            if (this.Map == null)
                return (false);

            this.DroneRequest.SetRequest(DroneRequestType.INVENTORY);
            App.Network.ExecuteRequest(this.DroneRequest);

            if (this.DroneRequest.STATUS == Network.StatusType.OK)
            {
                return (true);
            }
            return (false);
        }

        /* Ask the server to broadcast sound */
        public void BroadcastSound(string message)
        {
            if (this.Map == null)
                return;

            using (BroadcastRequest sound = new BroadcastRequest(message))
            {
                App.Network.ExecuteRequest(sound);
            }
        }
        #endregion

        #region PATH FINDING // INTERNAL

        /* ONLY CLONED DRONE CAN USE THOSE FXs */

        /* Unfair // Move Left */
        public bool MoveTop_Offline()
        {
            if (this.Map == null || this.IsCloned == false)
                return (false);

            actual_maptile = actual_maptile.GetTopTile(this);
            return (true);
        }

        /* Unfair // Move Left */
        public bool MoveLeft_Offline()
        {
            if (this.Map == null || this.IsCloned == false)
                return (false);

            actual_maptile = actual_maptile.GetLeftTile(this);
            return (true);
        }

        /* Unfair // Move Right */
        public bool MoveRight_Offline()
        {
            if (this.Map == null || this.IsCloned == false)
                return (false);

            actual_maptile = actual_maptile.GetRightTile(this);
            return (true);
        }

        /* Unfair // Move Right */
        public bool MoveBackwards_Offline()
        {
            if (this.Map == null || this.IsCloned == false)
                return (false);

            actual_maptile = actual_maptile.GetBottomTile(this);
            return (true);
        }

        #endregion

        #region INTERNAL ROUTINES

        /*
		** [INTERNAL ROUTINES]
		** Those functions (bellow) are internal routines
		*/
        public void BindMap(ref Map this_map)
		{
			this.Map = this_map;
            this.actual_maptile = this_map.GetTile(0, 0);
        }

        public Map GetMap()
        {
            return (this.Map);
        }

        #endregion
    }
}
