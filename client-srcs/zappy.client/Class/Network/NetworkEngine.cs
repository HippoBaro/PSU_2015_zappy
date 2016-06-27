using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zappy.Client.Network
{
    public class NetworkEngine
    {
        private string      ServerURL { get; set; }
        private int         ServerPort { get; set; }
        private bool        is_init = false;

        public NetworkEngine()
        {
            /* Nothing there */
        }

        public bool ExecuteRequest(GenericRequest request)
        {
            if (is_init == false)
            {
                App.Log(LogLevel.WARNING, "Can not perform request, you did not initialized network connection first.");
                return (false) ;
            }

            /* TO DO */
            return (true);
        }

        public bool Connect(string server_url, int server_port)
        {
            /* Storring settings */
            is_init = true;
            ServerURL = server_url;
            ServerPort = server_port;
            App.Log(LogLevel.INFORMATION, String.Format("Server URL was set to [{0}] on port [{1}]", ServerURL, ServerPort));

            /* Nothing implemented, it does not work */
            App.Log(LogLevel.ERROR, String.Format("Client coudln't connect to server with URL set to [{0}] on port [{1}]", ServerURL, ServerPort));
            App.Log(LogLevel.INFORMATION, String.Format("Retrying in 2 seconds"));
            System.Threading.Thread.Sleep(2000);
            return (false);
        }
    }
}
