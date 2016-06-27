using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zappy.Client.Network.RequestCollection
{
    class HelloWorldRequest : GenericRequest
    {
        public HelloWorldRequest()
        {
            URL = "/hello";
            TYPE = RequestType.GET;
        }

        public override void OnRequest_Arrived()
        {
           /* 
            * List<String> ElementsFormTheRequest;
            *
            * if (this.STATUS == StatusType.OK)
            * {
            *    ElementsFormTheRequest = App.ParseServerAnswerToStringList(this.DATA);
            * }
            */
            base.OnRequest_Arrived();
        }
    }
}
