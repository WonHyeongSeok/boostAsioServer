//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//#include <queue>
//#include <boost/asio.hpp>
//#include "Session.h"
//#include "BaseService.h"
////
////
////class ServerService : public BaseService
////{
////public:
////    ServerService(boost::asio::io_context& io_context, short port)
////        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
////        socket_(io_context) 
////    {
////        doAccept();
////        startSendTimer(io_context);
////    }
////
////
////    void startSendTimer(boost::asio::io_context& io_context);
////    void sendToAllSessions(const string& message);
////    shared_ptr<Session> createSession();
////    void setSessionFactor(function<shared_ptr<Session(void)>> factorFunc);
////
////private:
////    void doAccept();
////    tcp::acceptor acceptor_;
////    tcp::socket socket_; //client socekt
////    vector<shared_ptr<Session>> sessions_;
////
////    shared_ptr<deadline_timer> timer_;
////    mutex mutex_; // 세션 컨테이너에 대한 뮤텍스
////    function<shared_ptr<Session(void)>> _sessionFactor;
////};
////
