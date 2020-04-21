using System.Collections;
using System.Net;
using System.Net.Sockets;
using System;
using System.Security;
using System.IO;
using System.Threading;
using System.Collections.Generic;
using Protobuf;

namespace Network
{
    public enum SendPacketEnum
    {
        DontSend =0,
        Sawadika = 1,
        Kouyimadai = 2,
        SendNum = 3,
        SendPb_Ping = 4,
    }
    public class ClientRobotLogic
    {

        // 状态相关
        public enum ConnectState
        {
            DISCONNECT,       
            CONNECTING,        
            CONNECTED,          
        }
        public  SendPacketEnum SendLogic = SendPacketEnum.DontSend;
        private MySocket m_socket = new MySocket();
        private MemoryStream m_InputStream = new MemoryStream();        
        private MemoryStream m_OutputStream = new MemoryStream();
        private byte[] remainByte = new byte[1024]; 
        private int nSeqNum = 0;
        public delegate void ConnectChangeDelegate(ConnectState newState);
        private ConnectState m_connectState = ConnectState.DISCONNECT;
        private ConnectChangeDelegate m_delConnectChange;
        private bool m_bGetConnectResult = false;
        private bool m_bConnectSuccess = false;
        private bool m_bPing = false;
        PbMsgManager m_PakManager = new PbMsgManager();

        public ClientRobotLogic(SendPacketEnum sendLogic)
        {
            SendLogic = sendLogic;
            m_bPing = false;
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
        private void OnSendBytes(int nBytes)
        {
            m_nSendDataLenth += nBytes;
            m_nTotalSendDataLenth += (ulong)(nBytes);
        }

        private int m_nSendDataLenth = 0;

        private ulong m_nTotalSendDataLenth = 0;


        public void Send(byte [] data, int size, SOCKET_TYPE type)
        {
            //写入类型
            int nType = (int)type;
            byte[] typebyte = BitConverter.GetBytes(nType);
            m_OutputStream.Write(typebyte, 0, typebyte.Length);
            //写入大小
            byte[] sizebyte = BitConverter.GetBytes(size);
            m_OutputStream.Write(sizebyte, 0, sizebyte.Length);
            //写入消息体
            m_OutputStream.Write(data, 0, size);
        }
        public void ProcessOutput()
        {
            long nByteNeedToSend = m_OutputStream.Length;
            // 取出要发送的数据
            if(nByteNeedToSend == 0)
            {
                return;
            }
            byte[] sendBytes = m_OutputStream.GetBuffer();

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
            m_OutputStream.Position = 0;
            m_OutputStream.SetLength(0);
        }

        private void ProcessInput()
        {
            if (!m_socket.PollRead())
            {
                return;
            }

            
            byte [] m_ByteRcvCache = new byte [1024];
            int nRecvCnt = 0;
            nRecvCnt = m_socket.Recv(m_ByteRcvCache, 1024);
            if ( nRecvCnt < 0)
            {
                ConnectLost();
                return;
            }
            else if (nRecvCnt == 0)
            {
                ConnectLost();
                return;
            }

            if (nRecvCnt > 0)
            {
                m_InputStream.Write(m_ByteRcvCache, 0, (int)nRecvCnt);
            }
        }

        bool ReadType(ref int type)
        {
            m_InputStream.Position = 0;
            byte[] typebyte = new byte[SOCKET_DEFINE.HEAD_SIZE];
            int readsize = m_InputStream.Read(typebyte, 0, SOCKET_DEFINE.HEAD_SIZE);
            if(readsize != SOCKET_DEFINE.HEAD_SIZE)
            {
                return false;
            }
            type = BitConverter.ToInt32(typebyte, 0);
            return true;
        }
        bool ReadSize(ref int size)
        {
            m_InputStream.Position = 0;
            byte[] sizebyte = new byte[SOCKET_DEFINE.SIZE_SIZE];
            int readsize = m_InputStream.Read(sizebyte, SOCKET_DEFINE.HEAD_SIZE, SOCKET_DEFINE.SIZE_SIZE+SOCKET_DEFINE.HEAD_SIZE);
            if(readsize != SOCKET_DEFINE.SIZE_SIZE)
            {
                return false;
            }
            size = BitConverter.ToInt32(sizebyte, 0);
            return true;
        }

        bool ReadBody(byte []buf, int size)
        {
            m_InputStream.Position = 0;
            if(m_InputStream.Length<size + SOCKET_DEFINE.HEAD_SIZE + SOCKET_DEFINE.SIZE_SIZE)
            {
                return false;
            }
            m_InputStream.Read(buf, SOCKET_DEFINE.HEAD_SIZE + SOCKET_DEFINE.SIZE_SIZE, size);
            return true; 
        }

        private void ProcessInputPacket()
        {
            int _socktype = -1;
            int _socksize = -1;
            m_InputStream.Position = 0;
            if(!ReadType(ref _socktype) || !ReadSize(ref _socksize))
            {
                return;
            }
            byte[] buf = new byte[_socksize];
            if(!ReadBody(buf, _socksize))
            {
                return;
            }
            m_PakManager.HandlePacket(buf, _socksize, (SOCKET_TYPE)_socktype, this);

            long inputPosition = _socksize + SOCKET_DEFINE.HEAD_SIZE + SOCKET_DEFINE.SIZE_SIZE;
            long remainDataSize = m_InputStream.Length - inputPosition;
            if(remainDataSize > 0)
            {
                byte[] remainData = new byte[remainDataSize];
                int readsize = m_InputStream.Read(remainData, (int)inputPosition, (int)remainDataSize);
                if(remainDataSize != readsize)
                {
                    Console.WriteLine("Copy 2 TmpMemory Failed.");
                }
                else
                {
                    m_InputStream.SetLength(0);
                    m_InputStream.Position = 0;
                    m_InputStream.Write(remainData, 0, (int)remainDataSize);
                }
            }
        }



        Thread m_hConnectThread = null;
        string m_strConnectIP;
        int m_nConnectPort;
        public void Connect(string strIP, int port)
        {
            if(m_connectState == ConnectState.CONNECTING)
            {
                return;
            }
            m_strConnectIP = strIP;
            m_nConnectPort = port;
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
            m_InputStream.Position = 0;
            m_InputStream.SetLength(0);
            m_OutputStream.Position = 0;
            m_OutputStream.SetLength(0);
        }
        public void Update()
        {
            string addr_ip = "127.0.0.1";
            int addr_port = 2718;
            if(!m_bConnectSuccess)
            {
                Connect(addr_ip, addr_port);
                Console.WriteLine("connecting...");
            }
            else
            {
                TestSendPak();
                ProcessInput();
                ProcessInputPacket();
                ProcessOutput();
            }

            if(m_bConnectSuccess && !m_bPing)
            {
                DoLogin();
            }
        }

        void DoLogin()
        {
            CS_PING ping = new CS_PING();
            ping.id = 0;
            ping.ansi_time = 100;
            ping.name = "start ping";

            byte[] data = CS_PING.SerializeToBytes(ping);
            Send(data, data.Length, SOCKET_TYPE.CS_PING);

            //m_bPing = true;
        }

        void TestSendPak()
        {
            switch(SendLogic)
            {
                case SendPacketEnum.DontSend:
                    break;
                case SendPacketEnum.Kouyimadai:
                    break;
                case SendPacketEnum.Sawadika:
                    break;
                case SendPacketEnum.SendNum:
                    break;
                case SendPacketEnum.SendPb_Ping:
                    break;
                default:
                    break;
            }
        }
    }
}

