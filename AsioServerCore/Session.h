//#include "pch.h"
//using namespace boost::asio;
//using namespace boost::asio::ip;
//using boost::asio::ip::tcp;
//
//class Session : public std::enable_shared_from_this<Session>
//{
//public:
//    Session(tcp::socket socket) : socket_(std::move(socket)) {  }
//    virtual ~Session() {}
//    void start();
//
//    void sendPacket(const std::string& message);
//private:
//    void doWrite();
//    void doRead();
//    void readData();
//    void processData(std::size_t length);
//
//    tcp::socket socket_;
//    enum { max_length = 1024 };
//    char buffer_[max_length];
//
//    std::queue<std::string> sendQueue_;
//    std::mutex mutex_;
//    std::condition_variable condition_;
//public:
//
//    Session() = default;
//};
//
////struct PacketHeader
////{
////	uint16 size;
////	uint16 id; // 프로토콜ID (ex. 1=로그인, 2=이동요청)
////};
////
