using System;
using System.Runtime.InteropServices;

namespace Client
{
	public class Network
	{
		[StructLayout(LayoutKind.Sequential)]
		struct NetworkInternal {
			public delegate int Send (IntPtr rep);
		}

		[DllImport ("zappy.so", CallingConvention = CallingConvention.Cdecl, CharSet=CharSet.Auto)]
		static unsafe extern  IntPtr CreateNetwork (int type, ushort port, string addr);

		[DllImport ("zappy.so", CallingConvention = CallingConvention.Cdecl, CharSet=CharSet.Auto)]
		static unsafe extern  IntPtr	CreateResponseFromFdWithMessage(int fd, IntPtr message);

		[DllImport ("zappy.so", CallingConvention = CallingConvention.Cdecl, CharSet=CharSet.Auto)]
		static unsafe extern bool Send(IntPtr rep);

		[DllImport ("zappy.so", CallingConvention = CallingConvention.Cdecl, CharSet=CharSet.Auto)]
		static unsafe extern IntPtr Receive(IntPtr net, IntPtr timeout);

		[DllImport ("zappy.so", CallingConvention = CallingConvention.Cdecl, CharSet=CharSet.Auto)]
		static unsafe extern IntPtr GetTimeValFrom(UInt64 usec);

		[DllImport ("zappy.so", CallingConvention = CallingConvention.Cdecl, CharSet=CharSet.Auto)]
		static unsafe extern string  GetRequestAsString(IntPtr request);

		[DllImport ("libc.so.6", CallingConvention = CallingConvention.Cdecl, CharSet=CharSet.Auto)]
		static unsafe extern IntPtr strdup(string str);

		[DllImport ("libc.so.6", CallingConvention = CallingConvention.Cdecl, CharSet=CharSet.Auto)]
		static unsafe extern int gettimeofday(IntPtr tv, IntPtr tz);

	
		private IntPtr net;

		public Network (Option option)
		{
			net = CreateNetwork(1, option.Port, option.Host);
		}

		public void SendMessage(string message) {
			message += '\n';
			Send(CreateResponseFromFdWithMessage(4, strdup(message)));
		}

		public string ReceiveMessage(TimeSpan? timeout) {
			if (timeout.HasValue) {
				var t = (UInt64)timeout.Value.TotalMilliseconds * 1000;
				return GetRequestAsString(Receive (net, GetTimeValFrom (t))).TrimEnd('\n');
			}
			else
				return GetRequestAsString(Receive (net, (IntPtr)0)).TrimEnd('\n');
		}
	}
}

