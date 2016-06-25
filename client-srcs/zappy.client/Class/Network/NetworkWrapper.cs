using System;
using System.Runtime.InteropServices;

namespace Zappy.Client.Network
{
	public enum NetworkType
	{
		SERVER,
		CLIENT
	}

	public struct Network
	{

	};

	public static class NetworkWrapper
	{
		[DllImport ("./libnetwork.so")]
		public static extern IntPtr CreateNetwork (NetworkType type, Int16 port, string server_adress);
	}
}

