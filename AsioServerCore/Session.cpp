//#include "Session.h"
//#include "pch.h"
//
//#include <thread>
//#include <chrono>
//
////�����ʿ� �ִ� Ŭ���� ����
//void Session::start()
//{
//    //auto self(shared_from_this());
//    //boost::asio::async_write(socket_, boost::asio::buffer("welcome"),
//    //    [this, self](boost::system::error_code ec, std::size_t /*length*/)
//    //    {
//    //        if (!ec) {
//    //            // ���������� �޽����� ������ ��� ó���� �ڵ带 ���⿡ �߰��մϴ�.
//    //            std::cout << "Message sent successfully!" << std::endl;
//    //        }
//    //        else {
//    //            // �޽��� �����⿡ ������ ��� ó���� �ڵ带 ���⿡ �߰��մϴ�.
//    //            std::cerr << "Failed to send message: " << ec.message() << std::endl;
//    //        }
//    //    });
//
//  // sendPacket("accept �Ϸ�\n");
//    readData();
//
//}
//
//void Session::sendPacket(const std::string& message)
//{
//
//    //bool isWriting = !sendQueue_.empty(); // ���� �޽����� ������ ������ Ȯ��
//    //sendQueue_.push(message);
//    //if (!isWriting) 
//    //{
//    //    isWriting = true;
//    //    doWrite(); // ���ο� �޽����� ������ ���� �ƴϸ� �ٷ� ����
//    //}
//
//    {
//        std::lock_guard<std::mutex> lock(mutex_);
//        sendQueue_.push(message);
//    }
//
//    condition_.notify_one(); // ��� ���� �����忡�� �˸�
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
//                // �޽��� �����⿡ ������ ��� ó���� �ڵ带 ���⿡ �߰��մϴ�.
//                std::cerr << "processData: " << ec.message() << std::endl;
//            }
//
//        });
//}
//
//void Session::processData(std::size_t length) {
//    std::string receivedMessage(buffer_, length);
//    // Ŭ���̾�Ʈ�κ��� ������ ������ ó��
//    std::cout << "Received message: " << receivedMessage << std::endl;
//
//    readData(); // ���� �����͸� ����
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
//                sendQueue_.pop(); // ���� �޽��� ����
//                if (!sendQueue_.empty()) {
//                    doWrite(); // ���� �޽����� ���������� ���� �޽����� ����
//                }
//            }
//            else {
//                // �޽��� �����⿡ ������ ��� ó���� �ڵ带 ���⿡ �߰��մϴ�.
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
////        std::unique_lock<std::mutex> lock(mutex_);//lock_guard�� �Ⱦ������� ���������� ���Ϸ���
////        condition_.wait(lock, [this] { return !sendQueue_.empty(); }); // sendQueue�� �����Ͱ� ������ ���
////        message = sendQueue_.front();
////        sendQueue_.pop();
////    }
////    boost::asio::async_write(socket_, boost::asio::buffer("Hello Im Server"),
////        [this, self](boost::system::error_code ec, std::size_t /*length*/)
////        {
////            if (!ec) {
////               // doWrite(); // ���� �޽����� �����ϴ�.
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