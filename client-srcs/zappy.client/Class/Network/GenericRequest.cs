using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zappy.Client.Network
{
    public enum RequestType
    {
        GET,
        POST
    }

    public enum StatusType
    {
        OK,
        KO,
        NETWORK_ERROR,
        NETWORK_WARNING
    }

    public class GenericRequest : IDisposable
    {
        protected string URL { get; set; }
        protected string DATA { get; set; }
        protected string ANSWER { get; set; }

        protected RequestType TYPE { get; set; }
        public StatusType STATUS { get; set; } = StatusType.OK;

        public event RequestCallback RequestReceived;
        public delegate void RequestCallback(GenericRequest REQUEST, string ANSWER, StatusType STATUS);

        public void SetDataToSend(string data)
        {
            this.DATA = data;
        }

        public virtual void OnRequest_Arrived()
        {
            this.STATUS = StatusType.OK;
            if (this.ANSWER != null)
            {
                if (this.ANSWER == Constantes.NETWORK_REQUEST_ANSWER_OK)
                    this.STATUS = StatusType.OK;
                if (this.ANSWER == Constantes.NETWORK_REQUEST_ANSWER_KO)
                    this.STATUS = StatusType.KO;
            }
            else
                this.STATUS = StatusType.KO;

            RequestReceived.Invoke(this, this.ANSWER, this.STATUS);
        }

        public virtual String GetData()
        {
            return (this.ANSWER);
        }

        public void Dispose()
        {
            // Dispose
        }

        public override string ToString()
        {
            return (this.ANSWER);
        }
    }
}