//#include "Session.h"
//#include "pch.h"
//
//#include <thread>
//#include <chrono>
//
////서버쪽에 있는 클라의 정보
//void Session::start()
//{
//    //auto self(shared_from_this());
//    //boost::asio::async_write(socket_, boost::asio::buffer("welcome"),
//    //    [this, self](boost::system::error_code ec, std::size_t /*length*/)
//    //    {
//    //        if (!ec) {
//    //            // 성공적으로 메시지를 보냈을 경우 처리할 코드를 여기에 추가합니다.
//    //            std::cout << "Message sent successfully!" << std::endl;
//    //        }
//    //        else {
//    //            // 메시지 보내기에 실패한 경우 처리할 코드를 여기에 추가합니다.
//    //            std::cerr << "Failed to send message: " << ec.message() << std::endl;
//    //        }
//    //    });
//
//  // sendPacket("accept 완료\n");
//    readData();
//
//}
//
//void Session::sendPacket(const std::string& message)
//{
//
//    //bool isWriting = !sendQueue_.empty(); // 현재 메시지를 보내는 중인지 확인
//    //sendQueue_.push(message);
//    //if (!isWriting) 
//    //{
//    //    isWriting = true;
//    //    doWrite(); // 새로운 메시지를 보내는 중이 아니면 바로 보냄
//    //}
//
//    {
//        std::lock_guard<std::mutex> lock(mutex_);
//        sendQueue_.push(message);
//    }
//
//    condition_.notify_one(); // 대기 중인 스레드에게 알림
//    doWrite();
//}
//
//
//void Session::readData()
//{
//    auto self(shared_from_this());
//    socket_.async_read_some(boost::asio::buffer(buffer_, max_length),
//        [this, self](boost::system::error_code ec, std::size_t length)
//        {
//            if (!ec) {
//                processData(length);
//            }
//            else {
//                // 메시지 보내기에 실패한 경우 처리할 코드를 여기에 추가합니다.
//                std::cerr << "processData: " << ec.message() << std::endl;
//            }
//
//        });
//}
//
//void Session::processData(std::size_t length) {
//    std::string receivedMessage(buffer_, length);
//    // 클라이언트로부터 수신한 데이터 처리
//    std::cout << "Received message: " << receivedMessage << std::endl;
//
//    readData(); // 다음 데이터를 읽음
//
//}
//
//void Session::doWrite()
//{
//    auto self(shared_from_this());
//    boost::asio::async_write(socket_, boost::asio::buffer(sendQueue_.front()),
//        [this, self](boost::system::error_code ec, std::size_t /*length*/)
//        {
//            if (!ec) {
//                if (socket_.is_open() == true)
//                {
//
//                    std::cerr << "sock:  " << socket_.is_open() << std::endl;
//                }
//
//                sendQueue_.pop(); // 보낸 메시지 제거
//                if (!sendQueue_.empty()) {
//                    doWrite(); // 보낼 메시지가 남아있으면 다음 메시지를 보냄
//                }
//            }
//            else {
//                // 메시지 보내기에 실패한 경우 처리할 코드를 여기에 추가합니다.
//                std::cerr << "Failed to send message: " << ec.message() << std::endl;
//            }
//
//        });
//}
////void Session::doWrite() 
////{
////    auto self(shared_from_this());
////    std::string message;
////    {
////        std::unique_lock<std::mutex> lock(mutex_);//lock_guard를 안쓴이유는 해제시점을 정하려고
////        condition_.wait(lock, [this] { return !sendQueue_.empty(); }); // sendQueue에 데이터가 없으면 대기
////        message = sendQueue_.front();
////        sendQueue_.pop();
////    }
////    boost::asio::async_write(socket_, boost::asio::buffer("Hello Im Server"),
////        [this, self](boost::system::error_code ec, std::size_t /*length*/)
////        {
////            if (!ec) {
////               // doWrite(); // 다음 메시지를 보냅니다.
////            }
////        });
////}   
//
//void Session::doRead()
//{
//    auto self(shared_from_this());
//    socket_.async_read_some(boost::asio::buffer(buffer_, max_length),
//        [this, self](boost::system::error_code ec, std::size_t length)
//        {
//            if (!ec) {
//                std::cout << "Received: " << std::string(buffer_, length) << std::endl;
//                doRead();
//            }
//            else
//            {
//                if (socket_.is_open() == true)
//                {
//
//                    std::cerr << "sock:  " << socket_.is_open() << std::endl;
//                }
//            }
//        });
//}