#include "pch.h"
#include "BaseService.h"

BaseService::BaseService(ServiceType type, SessionGenFuc factory, int32 maxSessionCount)
	: _type(type), _sessionFactory(factory), _maxSessionCount(maxSessionCount)
{

}

BaseService::BaseService(ServiceType type, int32 maxSessionCount)
	: _type(type),  _maxSessionCount(maxSessionCount)
{
}

BaseService::~BaseService()
{
}

void BaseService::CloseService()
{
	// TODO
}

//void BaseService::Broadcast(SendBufferRef sendBuffer)
//{
//	//WRITE_LOCK;
//	for (const auto& session : _sessions)
//	{
//		session->Send(sendBuffer);
//	}
//}

BaseSessionPtr BaseService::CreateSession(boost::asio::ip::tcp::socket& socket)
{
	BaseSessionPtr session = make_shared<BaseSession>(socket, io_context);
	session->SetService(shared_from_this());
	//io_context
	//if (_iocpCore->Register(session) == false)
	//	return nullptr;

	return session;
}

void BaseService::AddSession(BaseSessionPtr session)
{
	//WRITE_LOCK;
	_sessionCount++;
	_sessionGenId++;
	
	auto isSession = _sessions.find(_sessionCount);
	if (isSession != _sessions.end())
	{
		_sessions.insert(std::make_pair(_sessionCount, session));
	}
}

void BaseService::ReleaseSession(BaseSessionPtr session)
{
	//WRITE_LOCK;
	//ASSERT_CRASH(_sessions.erase(session) != 0);
	_sessionCount--;
}

GameServerService::GameServerService(SessionGenFuc factory, int32 maxSessionCount)
	: BaseService(ServiceType::Server, factory, maxSessionCount)
{
}
GameServerService::GameServerService(int32 maxSessionCount)
	: BaseService(ServiceType::Server,  maxSessionCount)
{
}

bool GameServerService::Start()
{
	/*if (CanStart() == false)
		return false;*/

	 _listener = std::make_shared<Listener>(io_context, "127.0.0.1","8080");// <Listener>();
	if (_listener == nullptr)
		return false;

	std::shared_ptr<BaseService> service = static_pointer_cast<GameServerService>(shared_from_this());
	if (_listener->Init(service) == true)
	{
		_listener->StartListen();
		io_context.run();
		return true;
	}

	return false;
}

void GameServerService::CloseService()
{
	BaseService::CloseService();
}
