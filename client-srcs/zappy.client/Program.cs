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
            while (App.Network.Connect("localhost", 42) == false);

            /* Waiting Input */
            Console.Read();
		}
    }
}
