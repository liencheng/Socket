using System.Collections;
using System.Net;
using System.Net.Sockets;
using System;
using System.Security;
using System.IO;
using System.Threading;
using System.Collections.Generic;

namespace Network
{
    public enum SendPacketEnum
    {
        DontSend =0,
        Sawadika = 1,
        Kouyimadai = 2,
    }
    public class ClientRobotLogic
    {

        public ClientRobotLogic(SendPacketEnum sendLogic) { SendLogic = sendLogic; }
        public  SendPacketEnum SendLogic = SendPacketEnum.DontSend;
        private MySocket m_socket = new MySocket();
        private MemoryStream m_msInput = new MemoryStream();        
        private MemoryStream m_msOutput = new MemoryStream();       
        private MemoryStream m_msPacketCache = new MemoryStream();
        private bool m_bCanReceivePacket = true;
        private int m_protobufPacketCacheLen = 1024; 

        private UInt32 m_ClientSeq = 0;
        private bool m_CanSendPacket = false;
        public byte[] Session = new byte[] { };
        private byte[] remainByte = new byte[1024]; 
        // 状态相关
        public enum ConnectState
        {
            DISCONNECT,       
            CONNECTING,        
            CONNECTED,          
        }

        public delegate void ConnectChangeDelegate(ConnectState newState);
        public ConnectState State { get { return m_connectState; } }
        private ConnectState m_connectState = ConnectState.DISCONNECT;
        private ConnectChangeDelegate m_delConnectChange;

        private bool m_bGetConnectResult = false;
        private bool m_bConnectSuccess = false;

        public void SetCanSendPacket(bool value)
        {
            m_CanSendPacket = value;
        }

        private void ChangeConnectState(ConnectState newState)
        {
            ConnectState lastState = m_connectState;
            m_connectState = newState;
            if(null != m_delConnectChange && lastState != newState && lastState != ConnectState.CONNECTING)
            {
                m_delConnectChange(newState);
            }
        }

        //输出通信消息开关_方便定位消息包
        private bool m_bLOgPacketInfoLogOpen = false;
        private void OnSendBytes(int nBytes)
        {
            m_nSendDataLenth += nBytes;
            m_nTotalSendDataLenth += (ulong)(nBytes);
        }

        //每秒发送/接收量
        private int m_nSendDataLenth = 0;
        private int m_nRecvDataLenth = 0;

        //总发送/接收量
        private ulong m_nTotalSendDataLenth = 0;
        private ulong m_nTotalRecvDataLenth = 0;

        // 输出流处理
        private void ProcessOutput(string packet)
        {

            string sendMsg = packet;
            byte[] byteArray = System.Text.Encoding.Default.GetBytes ( sendMsg );
            m_msOutput.Write(byteArray, 0, byteArray.Length);
            long nByteNeedToSend = m_msOutput.Length;
            // 取出要发送的数据
            if(nByteNeedToSend == 0)
            {
                return;
            }
            byte[] sendBytes = m_msOutput.GetBuffer();

            int sendByteOffset = 0;
            int leftBytes = (int)nByteNeedToSend;
            while(leftBytes > 0)
            {
                int retSend = m_socket.Send(sendBytes, sendByteOffset, leftBytes);
                if(retSend < 0)
                {
                    ConnectLost();
                    return;
                }
                else if(retSend == 0)
                {
                    ConnectLost();
                    return;
                }
                else
                {
                    OnSendBytes(retSend);

                    leftBytes -= retSend;
                    sendByteOffset += retSend;
                }
            }
            // 清空输出流
            m_msOutput.Position = 0;
            m_msOutput.SetLength(0);
        }

        // 连接服务器
        public delegate void DelConnectResult(bool bSuccess);
        Thread m_hConnectThread = null;
        string m_strConnectIP;
        int m_nConnectPort;
        DelConnectResult m_delConnectResult;
        public void Connect(string strIP, int port, DelConnectResult delConnectResult)
        {
            if(m_connectState == ConnectState.CONNECTING)
            {
                return;
            }
            m_strConnectIP = strIP;
            m_nConnectPort = port;
            m_delConnectResult = delConnectResult;
            m_ClientSeq = 0;
            SetCanSendPacket(false);
            Close();
            ChangeConnectState(ConnectState.CONNECTING);

            m_hConnectThread = new Thread(new ThreadStart(ConnectThread));
            m_hConnectThread.Start();
        }

        // 连接线程
        public void ConnectThread()
        {
            string result = m_socket.Connect(m_strConnectIP, m_nConnectPort);
            if(string.IsNullOrEmpty(result))
            {
                m_bConnectSuccess = true;

                Console.WriteLine("connect succ.");
            }
            else
            {
                m_bConnectSuccess = false;
            }

            m_bGetConnectResult = true;
        }

        //主动断开连接
        public void Disconnect()
        {
            Console.WriteLine("network disconect");
            Close();
        }
        // 出错后被动断开连接
        public void ConnectLost()
        {
            Console.WriteLine("network connect lost");
            Close();
        }

        // 关闭连接并清空流
        private void Close()
        {
            m_socket.Close();
            m_msInput.Position = 0;
            m_msInput.SetLength(0);
            m_msOutput.Position = 0;
            m_msOutput.SetLength(0);
        }

        // 心跳
        int nSeqNum = 0;
        public void Update()
        {
            string addr_ip = "127.0.0.1";
            int addr_port = 2718;
            if(!m_bConnectSuccess)
            {
                Connect(addr_ip, addr_port, null);
                Console.WriteLine("connecting...");
            }
            else
            {

                switch(SendLogic)
                {
                    case SendPacketEnum.DontSend:
                        break;
                    case SendPacketEnum.Kouyimadai:
                        ProcessOutput("kou& yi madai." + (nSeqNum++));
                        break;
                    case SendPacketEnum.Sawadika:
                        ProcessOutput("sa wa di ka.." + (nSeqNum++));
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

