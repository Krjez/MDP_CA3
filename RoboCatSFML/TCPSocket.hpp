class TCPSocket
{
public:
	~TCPSocket();
	int								Connect(const SocketAddress& inAddress) const;
	int								Bind(const SocketAddress& inToAddress) const;
	int								Listen(int inBackLog = 32) const;
	shared_ptr< TCPSocket >			Accept(SocketAddress& inFromAddress) const;
	int32_t							Send(const void* inData, size_t inLen) const;
	int32_t							Receive(void* inBuffer, size_t inLen) const;
private:
	friend class SocketUtil;
	TCPSocket(SOCKET inSocket) : mSocket(inSocket) {}
	SOCKET		mSocket;
};
typedef shared_ptr< TCPSocket > TCPSocketPtr;