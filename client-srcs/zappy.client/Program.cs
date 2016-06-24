using System;

using Zappy.Client.MapSystem;
using Zappy.Client.Network;

using Zappy.Client.Network.RequestCollection;

namespace Zappy.Client
{
	class MainClass
	{
		public static void Main (string[] args)
		{
            /* Connecting to server */
            // while (App.Network.Connect("localhost", 42) == false);

            Map this_map = new Map(10, 10);
            Drone this_drone = new Drone(0, ref this_map);
            AIAutomation ai_system;

            /* Testing if things works :) */
            ai_system = new AIAutomation(ref this_drone);

            /* Applying elements on map from sight & useless */
            this_drone.ApplySight(" ,  , LINEMATE df df df, df fd df");
            this_drone.ApplyInventory("{nourriture 345, sibur 3, phiras 5, ..., deraumere 0}");

            /* Let the AI play */
            ai_system.Play();

            /* Waiting Input */
            Console.Read();
		}
    }
}
