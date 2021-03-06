﻿using System;
using System.Collections.Generic;

using Zappy.Client;

namespace Zappy.Client.MapSystem
{
	public class MapTile
	{
        public Dictionary<RessourceType, int> Ressources { get { return (_ressources); } }
        private Dictionary<RessourceType, int> _ressources { get; set; } = new Dictionary<RessourceType, int>();

		public int X { get { return (_Y);} }
		public int Y { get { return (_X);} }

		private int _X;
		private int _Y;


		public MapTile(int MapHeight_X, int MapWidth_Y)
		{
			this._X = MapHeight_X;
			this._Y = MapWidth_Y;
		}

        public MapTile GetTopTile(Drone this_drone)
        {
            if (this_drone.GetRotationState() == RotationState.TOP)
                return (MapMath.GetTopTile(this_drone.GetMap(), this)); // OK

            if (this_drone.GetRotationState() == RotationState.RIGHT)
                return (MapMath.GetRightTile(this_drone.GetMap(), this)); // OK

            if (this_drone.GetRotationState() == RotationState.BOTTOM)
                return (MapMath.GetBottomTile(this_drone.GetMap(), this)); // OK

            if (this_drone.GetRotationState() == RotationState.LEFT)
                return (MapMath.GetLeftTile(this_drone.GetMap(), this)); // OK
            return (null);
        }

        public MapTile GetRightTile(Drone this_drone)
        {
            if (this_drone.GetRotationState() == RotationState.TOP)
                return (MapMath.GetRightTile(this_drone.GetMap(), this)); // OK

            if (this_drone.GetRotationState() == RotationState.RIGHT)
                return (MapMath.GetBottomTile(this_drone.GetMap(), this)); // OK

            if (this_drone.GetRotationState() == RotationState.BOTTOM)
                return (MapMath.GetRightTile(this_drone.GetMap(), this)); // OK

            if (this_drone.GetRotationState() == RotationState.LEFT)
                return (MapMath.GetBottomTile(this_drone.GetMap(), this)); // OK
            return (null);
        }

        public MapTile GetBottomTile(Drone this_drone)
        {
            if (this_drone.GetRotationState() == RotationState.TOP)
                return (MapMath.GetBottomTile(this_drone.GetMap(), this)); // OK

            if (this_drone.GetRotationState() == RotationState.RIGHT)
                return (MapMath.GetLeftTile(this_drone.GetMap(), this)); // OK

            if (this_drone.GetRotationState() == RotationState.BOTTOM)
                return (MapMath.GetTopTile(this_drone.GetMap(), this));  // OK

            if (this_drone.GetRotationState() == RotationState.LEFT)
                return (MapMath.GetRightTile(this_drone.GetMap(), this)); // OK
            return (null);
        }

        public MapTile GetLeftTile(Drone this_drone)
        {
            if (this_drone.GetRotationState() == RotationState.TOP)
                return (MapMath.GetLeftTile(this_drone.GetMap(), this)); // OK

            if (this_drone.GetRotationState() == RotationState.RIGHT)
                return (MapMath.GetBottomTile(this_drone.GetMap(), this)); // OK

            if (this_drone.GetRotationState() == RotationState.BOTTOM)
                return (MapMath.GetLeftTile(this_drone.GetMap(), this));  // OK

            if (this_drone.GetRotationState() == RotationState.LEFT)
                return (MapMath.GetTopTile(this_drone.GetMap(), this)); // OK
            return (null);
        }

        public void AddRessourceEstimation(RessourceType type, int ressource_toadd)
		{
            if (_ressources.ContainsKey(type) == false) {
                _ressources.Add(type, ressource_toadd);
                return ;
            }
			_ressources[type] += ressource_toadd;
		}

		public void SetRessourceEstimation(RessourceType type, int effective_count)
		{
            if (_ressources.ContainsKey(type) == false)
            {
                _ressources.Add(type, effective_count);
                return ;
            }
            _ressources[type] = effective_count;
		}

        public int GetRessourceEstimation(RessourceType type)
        {
            if (_ressources.ContainsKey(type) == false)
            {
                _ressources.Add(type, 0);
                return (0);
            }
            return (_ressources[type]);
        }

        public RessourceType GetRessource(RessourceType type)
		{
			/* Perform a request to get a special ressource from the server */
			/* if requested ressource is not found */
			return (RessourceType.NOT_FOUND);
		}
	}
}

