#pragma once

/*--------------
	Session
---------------*/
class BaseService;

struct PacketHeader
{
	uint16 size;
	uint16 id; // ��������ID (ex. 1=�α���, 2=�̵���û)
};

class BaseSession : public enable_shared_from_this<BaseSession>
{
	//friend class Listener;

	enum
	{
		BUFFER_SIZE = 0x10000, // 64KB
	};

public:
	BaseSession() = delete;
	BaseSession(asio_tcp_socket& socket, boost::asio::io_context& io_context)
		: io_context_(io_context), _socket(socket), strand_(boost::asio::make_strand(io_context))
	{
		//data_.clear();
		memset(&sendData_, 0, 1024);
		memset(&data_, 0, 1024);
	}
	virtual ~BaseSession();

public:
	/* �ܺο��� ��� */
	//void				Send(SendBufferPtr sendBuffer);
	bool Connect();
	bool Start();
	void Disconnect(const WCHAR* cause);

	shared_ptr<BaseService>	GetService() { return _service.lock(); }
	void				SetService(shared_ptr<BaseService> service) { _service = service; }
	
public:
	/* ���� ���� */
	//shared_ptr<asio_tcp_socket> GetSocket() { return _socket; }
	bool				IsConnected() { return _connected; }
	//BaseSessionPtr			GetSessionRef() { return static_pointer_cast<BaseSession>(shared_from_this()); }
private:
	/* ���� ���� */
	bool				RegisterConnect();
	bool				RegisterDisconnect();
	void				RegisterRead();
	void				RegisterSend();

	void				ProcessConnect();
	void				ProcessDisconnect();
	void				ProcessRead(boost::system::error_code ec, std::size_t length);
	void				DoRead();
	void				DoSend();
	void				ProcessSend(boost::system::error_code ec, std::size_t length);

protected:
	/* ������ �ڵ忡�� ������ */
	virtual void		OnConnected() { }
	virtual int32		OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void		OnSend(int32 len) { }
	virtual void		OnDisconnected() { }

private:
	weak_ptr<BaseService>	_service;
	boost::asio::ip::tcp::socket& _socket;
	atomic<bool>		_connected = false;

private:
	//USE_LOCK
	/* ���� ���� */
	//ReceiveBuffer				_recvBuffer;

	/* �۽� ���� */
	std::queue<SendBufferPtr>	_sendQueue;
	atomic<bool>			_sendRegistered = false;
	vector<char>			_recvBuffer;
	boost::asio::strand<boost::asio::io_context::executor_type> strand_;
	boost::asio::io_context& io_context_;
	std::array<char, 1024> data_;
	std::array<char, 1024> sendData_;
};
