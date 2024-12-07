#pragma once


class Listener : public enable_shared_from_this<Listener>
{

public:
	// 생성자
	Listener(boost::asio::io_context& io_context, const std::string& address, const std::string& port)
		: io_context_(io_context), acceptor_(io_context)
	{
		_address = address;
		_port = port;
	}

	Listener() = delete;
	//Listener(boost::asio::io_context& ioContext, std::string address, std::string port);
	//Listener(shared_ptr<boost::asio::io_context>& ioContext);
	~Listener();
	

public:
	/* 외부에서 사용 */
	void CloseSocket();

	const std::string& GetAddress();
	const std::string& GetPort();

	bool isOpen();
	virtual void StartListen(int multListenCount = 1);
	virtual void Close();
	bool Init(std::shared_ptr<BaseService> service);

private:

	/* Accept */
	void RegistAccept();
	void OnAsyncAccept(boost::system::error_code ec, asioTcpSocketPtr ptr);



public:
	boost::asio::io_context& io_context_;
	boost::asio::ip::tcp::acceptor acceptor_;
	std::string _address;
	std::string _port;
	std::shared_ptr<BaseService> _baseService;
};


