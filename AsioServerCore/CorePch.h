#pragma once

#include "Types.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include <boost/asio.hpp>
#include <mutex>
#include "Types.h"
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include "Container.h"

#include <windows.h>
#include <iostream>
using namespace std;

//#include <winsock2.h>
//#include <mswsock.h>
//#include <ws2tcpip.h>
//#pragma comment(lib, "ws2_32.lib")

#include "Lock.h"
#include "ObjectPool.h"
#include "TypeCast.h"
#include "Memory.h"
#include "SendBuffer.h"
#include "Session.h"
#include "JobQueue.h"

using asio_context = boost::asio::io_context;
using asio_tcp = boost::asio::ip::tcp;
using asio_tcp_socket = boost::asio::ip::tcp::socket;
using asioTcpSocketPtr = std::shared_ptr<asio_tcp_socket>;
//using sessionStrand = boost::asio::strand;
//#include <winsock2.h>
//#include <mswsock.h>
//#include <ws2tcpip.h>
//#pragma comment(lib, "ws2_32.lib")
#include <condition_variable>

#include "ReceiveBuffer.h"
using SendBufferPtr = std::shared_ptr<SendBuffer>;
#include "BaseSession.h"
using BaseSessionPtr = std::shared_ptr<BaseSession>;


#pragma once


