using System;
using System.Collections.Generic;

using Zappy.Client.MapSystem;
using Zappy.Client.Class;

namespace Zappy.Client
{
	public class Drone
	{
		private int UID { set; get;}
        public RotationState Rotation { get
            {
                return (rotation);
            }
        }
        private RotationState rotation { get; set; }

		private Map this_world { get; set; }
        public  MapTile ActualMapTile { get { return (actual_maptile); } }
        private MapTile actual_maptile { get; set; } // MapTile will be set after binding @0x0
        private Dictionary<RessourceType, int> Ressources { get; set; }

        /* Default constructor */
        public Drone(int UID, ref Map this_map)
		{
			this.UID = UID;
            this.rotation = RotationState.TOP;
            this.Ressources = new Dictionary<RessourceType, int>();

            // Setting Drone on map
            this.this_world = this_map;
            this.actual_maptile = this_map.GetTile(0, 0);
        }

		/* Ask the server to move the drone forward */
		public bool MoveFoward()
		{
			if (this.this_world == null)
				return (false);

            // --> Asking server to perform action !
            // Blabla

            actual_maptile = actual_maptile.GetTopTile(this);

			return (true);
		}

		/* Ask the server to move the drone 90° Drone Right */
		public bool Turn90DegreeesRight()
		{
			if (this.this_world == null)
				return (false);

            /* If validation OK */
            if (true == true)
            {
                rotation += 90;
                return (true);
            }

			return (false);
		}

		/* Ask the server to move the drone 90° Drone Left */
		public bool Turn90DegreeesLeft()
		{
			if (this.this_world == null)
				return (false);

            /* If validation OK */
            if (true == true)
            {
                rotation -= 90;
                return (true);
            }

            return (false);
		}

        /* Get Actual rotation */
        public RotationState GetRotationState()
        {
            return (this.Rotation);
        }

		/* Ask the server to take a given type of object */
		public bool TakeObject(RessourceType ressource)
		{
			if (this.this_world == null)
				return (false);
			
			return (false);
		}

		/* Ask the server to kickout a given drone defined by it's UID */
		public bool ExpulseDrone(int DroneUID)
		{
			if (this.this_world == null)
				return (false);

			return (false);

		}

		public Dictionary<RessourceType, int> Inventory
		{
			get
			{
				return (this.Ressources);
			}
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

        /*
		** [INTERNAL ROUTINES]
		** Those functions (bellow) are internal routines
		*/
        public void BindMap(ref Map this_map)
		{
			this.this_world = this_map;
            this.actual_maptile = this_map.GetTile(0, 0);
        }

        public Map GetMap()
        {
            return (this.this_world);
        }

    }
}

