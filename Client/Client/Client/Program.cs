using System;

namespace Client
{
	public class Option {
		public string Host { get; private set; }
		public UInt16 Port { get; private set; }

		public void Configure(string[] args) {
			try {
				for (int i = 0; i < args.Length; i++) {
					if (args [i] == "-h")
						Host = args [++i];
					else if (args [i] == "-p")
						Port = UInt16.Parse(args[++i]);
				}
			} catch (Exception ex) {
				Console.WriteLine ("Invalid arguments");
				Environment.Exit (0);
			}
		}
	}

	class MainClass
	{
		public static void Main (string[] args)
		{
			var option = new Option();
			option.Configure (args);
			var net = new Network (option);

			Console.WriteLine(net.ReceiveMessage(TimeSpan.FromSeconds(1)));
			net.SendMessage("test");
			Console.WriteLine(net.ReceiveMessage(null));
			while (true) {
				Console.WriteLine ("Waiting");
				Console.WriteLine(net.ReceiveMessage(null));
				net.SendMessage("avance");
			}
		}
	}
}
