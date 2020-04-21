using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using Network;
using System.Diagnostics;

namespace Client
{
    class Program
    {
        static void Main(string[] args)
        {

            //args = new string[2] { "1", "2000" };
            List<ClientRobotLogic> nlPool = new List<ClientRobotLogic>();
            if(args.Length < 2)
            {
                Process.GetCurrentProcess().Kill();
            }

            int nlCt = 1;
            nlCt = Convert.ToInt32(args[1]);

            Console.WriteLine("Start Logic. Main. count:" + nlCt);

            SendPacketEnum sp = SendPacketEnum.DontSend;
            if(args[0] == "0")
            {
                sp = SendPacketEnum.DontSend;
                Console.WriteLine("DontSend Logic.");
            }
            if(args[0] == "1")
            {
                sp = SendPacketEnum.Sawadika;
                Console.WriteLine("Sawadika Logic.");
            }
            if(args[0] == "2")
            {
                sp = SendPacketEnum.Kouyimadai;
                Console.WriteLine("KouyimadaiLogic Logic.");
            }

            if(args[0] == "3")
            {
                sp = SendPacketEnum.SendNum;
                Console.WriteLine("SendNum Logic.");
            }

            if(args[0] == "4")
            {
                sp = SendPacketEnum.SendPb_Ping;
                Console.WriteLine("SendNum Logic.");
            }



            for(int idx = 0; idx < nlCt; ++idx)
            {
                ClientRobotLogic nl = new ClientRobotLogic(sp);
                nlPool.Add(nl);
            }
            nlPool.ForEach(nl => nl.Update());
            do
            {
                Thread.Sleep(1000);
                nlPool.ForEach(nl => nl.Update());
                Console.WriteLine("Tick Main.total:" + nlPool.Count);
            } while(true);
        }
    }
}
