using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Zappy.Client.MapSystem;

namespace Zappy.Client
{
    public class AIAutomation
    {
        private Drone this_drone { get; set; }
        private DroneAttitude Attitude { get; set; }
        private Dictionary<int, DroneLevel> UpgradeRequirements = new Dictionary<int, DroneLevel>();

        public class DroneLevel
        {
            public Dictionary<RessourceType, int> Requirements = new Dictionary<RessourceType, int>();

            public int GetRequirementCountForRessourceType(RessourceType type)
            {
                if (Requirements.ContainsKey(type))
                    return (Requirements[type]);
                return (0);
            }
        };

        public enum DroneAttitude : int
        {
            SEEK_HORIZONTAL = 0,
            SEEK_VERTICAL = 1
        };

        public AIAutomation(ref Drone _drone)
        {
            this.this_drone = _drone;
            Random rand = new Random();
            this.Attitude = (DroneAttitude)rand.Next(0, 1);
            load_elevation_profile();
        }

        private void load_elevation_profile()
        {
            // Setting Elevation level 1
            this.UpgradeRequirements.Add(1, new DroneLevel
            {
                Requirements = new Dictionary<RessourceType, int>
                {
                    {RessourceType.LINEMATE, 1 }
                }
            });

            // Setting Elevation level 2
            this.UpgradeRequirements.Add(2, new DroneLevel
            {
                Requirements = new Dictionary<RessourceType, int>
                {
                    {RessourceType.LINEMATE, 1 },
                    {RessourceType.DERAUMERE, 1 },
                    {RessourceType.SIBUR, 1 }
                }
            });

            // Setting Elevation level 3
            this.UpgradeRequirements.Add(3, new DroneLevel
            {
                Requirements = new Dictionary<RessourceType, int>
                {
                    {RessourceType.LINEMATE, 2 },
                    {RessourceType.DERAUMERE, 0 },
                    {RessourceType.SIBUR, 1 },
                    {RessourceType.PHIRAS, 2 }
                }
            });

            // Setting Elevation level 4
            this.UpgradeRequirements.Add(4, new DroneLevel
            {
                Requirements = new Dictionary<RessourceType, int>
                {
                    {RessourceType.LINEMATE, 1 },
                    {RessourceType.DERAUMERE, 1 },
                    {RessourceType.SIBUR, 2 },
                    {RessourceType.PHIRAS, 1 }
                }
            });

            // Setting Elevation level 5
            this.UpgradeRequirements.Add(5, new DroneLevel
            {
                Requirements = new Dictionary<RessourceType, int>
                {
                    {RessourceType.LINEMATE, 1 },
                    {RessourceType.DERAUMERE, 2 },
                    {RessourceType.SIBUR, 1 },
                    {RessourceType.MENDIANE, 3 }
                }
            });

            // Setting Elevation level 6
            this.UpgradeRequirements.Add(6, new DroneLevel
            {
                Requirements = new Dictionary<RessourceType, int>
                {
                    {RessourceType.LINEMATE, 1 },
                    {RessourceType.DERAUMERE, 2 },
                    {RessourceType.SIBUR, 3 },
                    {RessourceType.PHIRAS, 1 }
                }
            });

            // Setting Elevation level 7
            this.UpgradeRequirements.Add(7, new DroneLevel
            {
                Requirements = new Dictionary<RessourceType, int>
                {
                    {RessourceType.LINEMATE, 2 },
                    {RessourceType.DERAUMERE, 2 },
                    {RessourceType.SIBUR, 2 },
                    {RessourceType.MENDIANE, 2 },
                    {RessourceType.PHIRAS, 1 },
                    {RessourceType.THYSTAME, 1 }
                }
            });

        }

        private bool change_orientation_totop()
        {
            while (this_drone.Rotation != RotationState.TOP)
            {
                if (this_drone.Rotation == RotationState.BOTTOM ||
                    this_drone.Rotation == RotationState.LEFT)
                    this_drone.Turn90DegreeesLeft();
                else
                    this_drone.Turn90DegreeesRight();
            }
            return (true);
        }

        private bool change_orientation_toright()
        {
            while (this_drone.Rotation != RotationState.RIGHT)
            {
                if (this_drone.Rotation == RotationState.LEFT ||
                    this_drone.Rotation == RotationState.BOTTOM)
                    this_drone.Turn90DegreeesRight();
                else
                    this_drone.Turn90DegreeesLeft();
            }
            return (true);
        }

        private bool seek_for_ressource_nearby(RessourceType ressource)
        {
            Drone Ghost; 
            MapTile Top;
            MapTile Left;
            MapTile Right;
            MapTile Bottom;

            Ghost = new Drone(this.this_drone);
            Top = Ghost.ActualMapTile.GetTopTile(Ghost);
            Right = Ghost.ActualMapTile.GetRightTile(Ghost);
            Left = Ghost.ActualMapTile.GetLeftTile(Ghost);
            Bottom = Ghost.ActualMapTile.GetBottomTile(Ghost);

            // Update sight
            this.this_drone.See();

            // Finding the ressources nearby
            if (Top.GetRessourceEstimation(ressource) > 0)
            {
                this_drone.MoveFoward();
                return (this_drone.TakeObject(ressource));
            }
            if (Right.GetRessourceEstimation(ressource) > 0)
            {
                this_drone.Turn90DegreeesRight();
                this_drone.MoveFoward();
                return (this_drone.TakeObject(ressource));
            }
            if (Left.GetRessourceEstimation(ressource) > 0)
            {
                this_drone.Turn90DegreeesLeft();
                this_drone.MoveFoward();
                return (this_drone.TakeObject(ressource));
            }
            if (Left.GetRessourceEstimation(ressource) > 0)
            {
                this_drone.Turn90DegreeesLeft();
                this_drone.Turn90DegreeesLeft();
                this_drone.MoveFoward();
                return (this_drone.TakeObject(ressource));
            }
            return (false);
        }

        private void seek_ressources_to_upgrade()
        {
            bool ressource_found = false;
            int X = this.this_drone.GetMap().X;
            int Y = this.this_drone.GetMap().Y;
            int imax = 0;
            int i = 0;

            if (Attitude == DroneAttitude.SEEK_HORIZONTAL)
                imax = Y;
            else
                imax = X;

            while (ressource_found == false)
            {
                i = 0;
                while (i != imax)
                {
                    foreach (RessourceType type in this_drone.Inventory.Keys)
                    {
                        if (this_drone.GetRessourceCount(type) < UpgradeRequirements[this_drone.Level].GetRequirementCountForRessourceType(type))
                        {
                            if ((ressource_found = seek_for_ressource_nearby(type)) == true)
                                break;
                        }
                    }
                   
                    if (this.Attitude == DroneAttitude.SEEK_HORIZONTAL)
                        change_orientation_toright();
                    else
                        change_orientation_totop();
                    this.this_drone.MoveFoward();
                    i++;
                }
                change_orientation_totop();
                this.this_drone.MoveFoward();
            }
        }

        public void Play()
        {
            while (1 == 1)
            {
                seek_ressources_to_upgrade();
            }
        }

    }
}
