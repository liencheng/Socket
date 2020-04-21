using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Protobuf;

public class PbMsgManager
{
    delegate object SocketDelete(byte [] buf);
    public void HandlePacket(byte []buf, int size, SOCKET_TYPE paktype, Network.ClientRobotLogic robot)
    {
        switch(paktype)
        {
            case SOCKET_TYPE.SC_PONG:
                SC_PONG pak = SC_PONG.Deserialize(buf);
                Handle(pak, robot);
                break;
        }
    }

    void Handle(SC_PONG pak, Network.ClientRobotLogic robot)
    {
        CS_PING rSendPak = new CS_PING();
        rSendPak.id = 100001;
        rSendPak.ansi_time = (int)DateTime.Now.Ticks;
        rSendPak.name = "test";

        byte[] data = CS_PING.SerializeToBytes(rSendPak);
        robot.Send(data, data.Length, SOCKET_TYPE.CS_PING);
    }
    void Register()
    {
        m_FuncFactory[SOCKET_TYPE.SC_PONG] = SC_PONG.Deserialize; 
        m_FuncFactory[SOCKET_TYPE.CS_PING] = SC_PONG.Deserialize; 
    }
    Dictionary<SOCKET_TYPE, SocketDelete> m_FuncFactory = new Dictionary<SOCKET_TYPE, SocketDelete>();
}
    
