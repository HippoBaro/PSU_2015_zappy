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

            /* Performing a dummy request */
            HelloWorldRequest dummy_request = new HelloWorldRequest();
            dummy_request.RequestReceived += Dummy_request_RequestReceived;
            App.Network.ExecuteRequest(dummy_request);

            /* Waiting Input */
            Console.Read();
		}

        private static void Dummy_request_RequestReceived(GenericRequest REQUEST, string ANSWER, StatusType STATUS)
        {
            /* 
             * 
             * List<String> ElementsFormTheRequest;
             *
             * if (STATUS == StatusType.OK)
             * {
             *    ElementsFormTheRequest = App.ParseServerAnswerToStringList(ANSWER);
             * }
             * 
             */
        }
    }
}
