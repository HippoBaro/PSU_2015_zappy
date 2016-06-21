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
        ERROR,
        WARNING
    }

    public class GenericRequest
    {
        protected string URL { get; set; }
        protected string DATA { get; set; }
        protected string ANSWER { get; set; }

        protected RequestType TYPE { get; set; }
        protected StatusType STATUS { get; set; } = StatusType.OK;

        public event RequestCallback RequestReceived;
        public delegate void RequestCallback(GenericRequest REQUEST, string ANSWER, StatusType STATUS);

        public void SetDataToSend(string data)
        {
            this.DATA = data;
        }

        public virtual void OnRequest_Arrived()
        {
            RequestReceived.Invoke(this, this.ANSWER, this.STATUS);
        }

        public virtual String GetData()
        {
            return (this.ANSWER);
        }

        public override string ToString()
        {
            return (this.ANSWER);
        }
    }
}