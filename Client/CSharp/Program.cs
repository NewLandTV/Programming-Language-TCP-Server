using System.Net.Sockets;
using System.Text;

const ushort BUFFER_SIZE = 2048;

Socket clientSocket = new Socket(SocketType.Stream, ProtocolType.Tcp);

clientSocket.Connect("127.0.0.1", 2222);

string? buffer = null;

while (buffer == null)
{
    buffer = Console.ReadLine();
}

clientSocket.Send(Encoding.ASCII.GetBytes(buffer), SocketFlags.None);

byte[] recvBuffer = new byte[BUFFER_SIZE];

clientSocket.Receive(recvBuffer, SocketFlags.None);

Console.WriteLine($"From server : {Encoding.ASCII.GetString(recvBuffer)}");

clientSocket.Close();