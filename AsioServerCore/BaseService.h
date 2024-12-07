#pragma once
#include "Listener.h"
#include <functional>


using SessionGenFuc = std::function<BaseSessionPtr(boost::asio::ip::tcp::socket&, boost::asio::io_context&)>;
//using SessionGenFuc = function<BaseSessionPtr(void)>;

enum class ServiceType : uint8
{
	Server,
	Client
};

class BaseService : public enable_shared_from_this<BaseService>
{
public:
	BaseService(ServiceType type, SessionGenFuc factory, int32 maxSessionCount = 1);
	BaseService(ServiceType type, int32 maxSessionCount = 1);
	virtual ~BaseService();

	virtual bool		Start() abstract;
	bool				CanStart() { return _sessionFactory != nullptr; }

	virtual void		CloseService();
	void				SetSessionFactory(SessionGenFuc func) { _sessionFactory = func; }

	//void				Broadcast(SendBufferRef sendBuffer);
	BaseSessionPtr			CreateSession(boost::asio::ip::tcp::socket& socket);
	void				AddSession(BaseSessionPtr session);
	void				ReleaseSession(BaseSessionPtr session);
	int32				GetCurrentSessionCount() { return _sessionCount; }
	int32				GetMaxSessionCount() { return _maxSessionCount; }

public:
	ServiceType			GetServiceType() { return _type; }
	boost::asio::io_context io_context;

protected:
	//USE_LOCK;
	ServiceType			_type;

	map<uint64,  BaseSessionPtr>	_sessions;
	int32				_sessionCount = 0;
	int32				_maxSessionCount = 0;
	SessionGenFuc		_sessionFactory;

	atomic<uint64> _sessionGenId;
};



/*-----------------
	GameServerService
------------------*/

class GameServerService : public BaseService
{
public:
	GameServerService(SessionGenFuc factory, int32 maxSessionCount = 1);
	GameServerService(int32 maxSessionCount = 1);
	virtual ~GameServerService() {}

	virtual bool	Start() override;
	virtual void	CloseService() override;

private:
	std::shared_ptr<Listener> _listener = nullptr;
};
