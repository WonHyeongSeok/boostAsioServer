//#include "ServerService.h"
//
//void ServerService::doAccept()
//{
//    std::cout << "Server started. Waiting for connection..." << std::endl;
//    acceptor_.async_accept(socket_, [this](boost::system::error_code ec)
//        {
//            if (!ec) 
//            {
//                auto newSession = std::make_shared<Session>(std::move(socket_));
//                newSession->start();
//                sessions_.push_back(newSession);
//            }
//            doAccept();
//        });
//}
//
//void ServerService::startSendTimer(boost::asio::io_context& io_context)
//{
//    timer_ = std::make_shared<deadline_timer>(io_context);
//    timer_->expires_from_now(boost::posix_time::seconds(10)); // 10초 간격으로 설정
//   // auto self(shared_from_this());
//    timer_->async_wait([this, &io_context](const boost::system::error_code& ec) {
//        if (!ec) {
//            sendToAllSessions("Hello from server!"); // 10초마다 모든 세션에 메시지 보냄
//            startSendTimer(io_context); // 타이머 재시작
//        }
//        });
//}
//
//void ServerService::sendToAllSessions(const std::string& message) 
//{
//    std::lock_guard<std::mutex> lock(mutex_);
//    for (auto& session : sessions_) 
//    {
//        session->sendPacket(message);
//    }
//}
//
//std::shared_ptr<Session> ServerService::createSession()
//{
//   // std::shared_ptr<Session> session = _sessionFactor();
//    return std::shared_ptr<Session>();
//}
//
//void ServerService::setSessionFactor(function<shared_ptr<Session(void)>> factorFunc)
//{
//    _sessionFactor = factorFunc;
//}
