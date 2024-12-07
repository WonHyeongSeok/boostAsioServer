#include "pch.h"
#include "Listener.h"
#include "BaseService.h"

/*--------------
	Listener
---------------*/

Listener::~Listener()
{
	cout << "Deleted Listener" << endl;
}

void Listener::CloseSocket()
{
}

const std::string& Listener::GetAddress()
{
	return _address;
}

const std::string& Listener::GetPort()
{
	return _port;
}

bool Listener::isOpen()
{
	return false;
}

void Listener::StartListen(int multListenCount)
{
	asio_tcp::resolver resolver(io_context_);
	asio_tcp::endpoint endPoint;
	boost::system::error_code boostErrorCode;

	std::string stringAddress = boost::asio::ip::address_v4::loopback().to_string();
	asio_tcp::resolver::query query(_address, _port);

	endPoint = *resolver.resolve(query);


	acceptor_.open(endPoint.protocol());
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(false), boostErrorCode);
	acceptor_.bind(endPoint);
	acceptor_.listen();

	cout << "Listening........." << endl;

	for (int i = 0; i < multListenCount; i++)
	{
		RegistAccept();
	}
}

void Listener::RegistAccept()
{
	auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);

	acceptor_.async_accept(*socket
		, std::bind(&Listener::OnAsyncAccept, shared_from_this(), std::placeholders::_1, socket)
	);
}

void Listener::OnAsyncAccept(boost::system::error_code ec, asioTcpSocketPtr ptr)
{
	//ptr에서 나온게 이제 제대로된 클라이언트코드
	if (acceptor_.is_open() == false)
		return;

	if (!ec)
	{
		//auto socket = std::move(*ptr);
		if (_baseService != nullptr)
		{
			BaseSessionPtr session = _baseService->CreateSession(*ptr);
			//BaseSessionPtr session = _baseService->CreateSession(socket);
			_baseService->AddSession(session);
			session->Start();
		}
		RegistAccept();
	}
}


void Listener::Close()
{
}

bool Listener::Init(std::shared_ptr<BaseService> service)
{
	_baseService = service;
	return true;
}
