
#include "pch.h"
#include "BaseService.h"

using namespace boost::asio;

int main() {


    try
    {
        boost::asio::io_context io_context; //io_service를해주는 boost::asio의 핵심 변수

        std::shared_ptr<GameServerService> service = std::make_shared<GameServerService>(
            1);

        service->Start();
        //io_context.run();

    }
  catch (std::exception& e) {
      std::cerr << "Exception: " << e.what() << std::endl;
  }
  while (true)
  {

  }

    return 0;
}
