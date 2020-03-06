using System.Collections;
using System.Net.Sockets;
using System.Net;
using System;
using System.Security;

public class MySocket
{

    private Socket m_socket;
    public string Connect(string strIP, int port)
    {

        string result = null;
        try
        {
            bool bUseIPv6 = false;
            if(strIP.Contains(":"))
            {
                bUseIPv6 = true;
            }

            if(bUseIPv6)
            {
                m_socket = new Socket(AddressFamily.InterNetworkV6, SocketType.Stream, ProtocolType.Tcp);
            }
            else
            {
                m_socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            }
            m_socket.NoDelay = true;
            IPAddress address = null;
            if(IPAddress.TryParse(strIP, out address))
            {
                IPEndPoint tempRemoteIP = new IPEndPoint(address, port);
                EndPoint epTemp = (EndPoint)tempRemoteIP;
                m_socket.Connect(epTemp);
                m_socket.NoDelay = true;
            }
        }
        catch(SocketException e) { result = e.ToString(); }
        catch(ArgumentOutOfRangeException e) { result = e.ToString(); }
        catch(ArgumentNullException e) { result = e.ToString(); }
        catch(ObjectDisposedException e) { result = e.ToString(); }
        catch(InvalidOperationException e) { result = e.ToString(); }
        catch(SecurityException e) { result = e.ToString(); }
        catch(Exception e) { result = e.ToString(); }
        return result;
    }

    public void Close()
    {
        if(null == m_socket)
        {
            return;
        }

        m_socket.Close();
        m_socket = null;
    }

    public int Send(byte[] buf, int offset, int len)
    {
        if(null == m_socket)
        {
            return -1;
        }

        try
        {
            return m_socket.Send(buf, offset, len, SocketFlags.None);
        }
        catch(SocketException e)
        {
        }
        return -1;
    }

    public int Recv(byte[] buf, int len)
    {
        if(null == m_socket)
        {
            return -1;
        }

        try
        {
            return m_socket.Receive(buf, len, SocketFlags.None);
        }
        catch(SocketException e)
        {
            Console.WriteLine(e.ToString());
        }
        return -1;
    }

    public bool PollRead()
    {
        if(null == m_socket)
        {
            return false;
        }
        return m_socket.Poll(0, SelectMode.SelectRead);
    }

    public bool PollWrite()
    {
        if(null == m_socket)
        {
            return false;
        }
        return m_socket.Poll(0, SelectMode.SelectWrite);
    }
}
