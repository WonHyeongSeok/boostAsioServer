#include "pch.h"
#include "BaseSession.h"
#include "BaseService.h"



BaseSession::~BaseSession()
{
	//SocketUtils::Close(_socket);
}

//
//void BaseSession::Send(SendBufferPtr sendBuffer)
//{
//	if (IsConnected() == false)
//		return;
//
//	bool registerSend = false;
//
//	// ���� RegisterSend�� �ɸ��� ���� ���¶��, �ɾ��ش�
//	{
//		//WRITE_LOCK;
//
//		_sendQueue.push(sendBuffer);
//
//		if (_sendRegistered.exchange(true) == false)
//			registerSend = true;
//	}
//
//	if (registerSend)
//		RegisterSend();
//}

//void BaseSession::Send(SendBufferPtr sendBuffer)
//{
//}

bool BaseSession::Connect()
{
	return RegisterConnect();
}

bool BaseSession::Start()
{
	_connected = true;
	DoRead();
	DoSend();
	return true;
}

void BaseSession::Disconnect(const WCHAR* cause)
{
	if (_connected.exchange(false) == false)
		return;

	// TEMP
	wcout << "Disconnect : " << cause << endl;

	RegisterDisconnect();
}


bool BaseSession::RegisterConnect()
{
	return false;
}

bool BaseSession::RegisterDisconnect()
{
	//_disconnectEvent.Init();
	//_disconnectEvent.owner = shared_from_this(); // ADD_REF

	//if (false == SocketUtils::DisconnectEx(_socket, &_disconnectEvent, TF_REUSE_SOCKET, 0))
	//{
	//	int32 errorCode = ::WSAGetLastError();
	//	if (errorCode != WSA_IO_PENDING)
	//	{
	//		_disconnectEvent.owner = nullptr; // RELEASE_REF
	//		return false;
	//	}
	//}

	return true;
}

void BaseSession::RegisterRead()
{
	//if (IsConnected() == false)
	//	return;

	//_recvEvent.Init();
	//_recvEvent.owner = shared_from_this(); // ADD_REF

	//WSABUF wsaBuf;
	//wsaBuf.buf = reinterpret_cast<char*>(_recvBuffer.WritePos());
	//wsaBuf.len = _recvBuffer.FreeSize();

	//DWORD numOfBytes = 0;
	//DWORD flags = 0;
	//if (SOCKET_ERROR == ::WSARecv(_socket, &wsaBuf, 1, OUT & numOfBytes, OUT & flags, &_recvEvent, nullptr))
	//{
	//	int32 errorCode = ::WSAGetLastError();
	//	if (errorCode != WSA_IO_PENDING)
	//	{
	//		HandleError(errorCode);
	//		_recvEvent.owner = nullptr; // RELEASE_REF
	//	}
	//}
}

void BaseSession::RegisterSend()
{
	if (IsConnected() == false)
		return;

	//_sendEvent.Init();
	//_sendEvent.owner = shared_from_this(); // ADD_REF

	//// ���� �����͸� sendEvent�� ���
	//{
	//	WRITE_LOCK;

	//	int32 writeSize = 0;
	//	while (_sendQueue.empty() == false)
	//	{
	//		SendBufferRef sendBuffer = _sendQueue.front();

	//		writeSize += sendBuffer->WriteSize();
	//		// TODO : ���� üũ

	//		_sendQueue.pop();
	//		_sendEvent.sendBuffers.push_back(sendBuffer);
	//	}
	//}

	//// Scatter-Gather (����� �ִ� �����͵��� ��Ƽ� �� �濡 ������)
	//Vector<WSABUF> wsaBufs;
	//wsaBufs.reserve(_sendEvent.sendBuffers.size());
	//for (SendBufferRef sendBuffer : _sendEvent.sendBuffers)
	//{
	//	WSABUF wsaBuf;
	//	wsaBuf.buf = reinterpret_cast<char*>(sendBuffer->Buffer());
	//	wsaBuf.len = static_cast<LONG>(sendBuffer->WriteSize());
	//	wsaBufs.push_back(wsaBuf);
	//}

	//DWORD numOfBytes = 0;
	//if (SOCKET_ERROR == ::WSASend(_socket, wsaBufs.data(), static_cast<DWORD>(wsaBufs.size()), OUT & numOfBytes, 0, &_sendEvent, nullptr))
	//{
	//	int32 errorCode = ::WSAGetLastError();
	//	if (errorCode != WSA_IO_PENDING)
	//	{
	//		HandleError(errorCode);
	//		_sendEvent.owner = nullptr; // RELEASE_REF
	//		_sendEvent.sendBuffers.clear(); // RELEASE_REF
	//		_sendRegistered.store(false);
	//	}
	//}
}

void BaseSession::ProcessConnect()
{
}

void BaseSession::ProcessDisconnect()
{
	//_disconnectEvent.owner = nullptr; // RELEASE_REF

	//OnDisconnected(); // ������ �ڵ忡�� ������
	//GetService()->ReleaseSession(GetSessionRef());
}



void BaseSession::DoRead()
{
	auto onAsyncRead = std::bind(&BaseSession::ProcessRead, shared_from_this(), std::placeholders::_1
		, std::placeholders::_2);

	//_socket.async_read_some(boost::asio::buffer(data_), onAsyncRead);
	//_socket.async_read_some(boost::asio::buffer(_recvBuffer), boost::asio::bind_executor(*strand_, onAsyncRead))

	if (_socket.is_open())
	{
		_socket.async_read_some(boost::asio::buffer(data_),
			boost::asio::bind_executor(strand_, onAsyncRead));
	}
}

void BaseSession::ProcessRead(boost::system::error_code ec, std::size_t length)
{
	if (!ec)
	{
		if (length <= data_.size())
		{
			// �����Ͱ� ��ȿ���� Ȯ���ϰ�, �����ϰ� ó��
			std::string received_data(data_.data(), length);
			std::cout << received_data << std::endl;
			//std::cout << "Received: " << received_data << std::endl;

		}
		// ���� ������ ó��
		// ����ؼ� ���� �����͸� ����

	}
	else
	{
		// ���� �߻� �� ó��
		std::cerr << "Error: " << ec.message() << std::endl;
	}
	std::cout << " end.." << std::endl;
	//DoRead();
}

void BaseSession::DoSend()
{
	std::string sendString = "Hello Here is Asio Server " + std::string(sendData_.data()
		, sendData_.size());
	
	auto onSend = std::bind(&BaseSession::ProcessSend
		, shared_from_this()
		, std::placeholders::_1
		, std::placeholders::_2
		//, sendData_
	);
	boost::asio::async_write(_socket
		, boost::asio::buffer(sendString, sendString.size())
		, boost::asio::bind_executor(strand_, onSend)
	);


	//boost::asio::dispatch(boost::asio::bind_executor(strand_
	//	, std::bind(&BaseSession::ProcessSend, shared_from_this())));
}

void BaseSession::ProcessSend(boost::system::error_code ec, std::size_t length)
{
	std::cout << "Processing data..." << std::endl;

	//auto onSend = std::bind(&BaseSession::)
}

//
//// [size(2)][id(2)][data....][size(2)][id(2)][data....]
//int32 PacketSession::OnRecv(BYTE* buffer, int32 len)
//{
//	int32 processLen = 0;
//
//	while (true)
//	{
//		int32 dataSize = len - processLen;
//		// �ּ��� ����� �Ľ��� �� �־�� �Ѵ�
//		if (dataSize < sizeof(PacketHeader))
//			break;
//
//		PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
//		// ����� ��ϵ� ��Ŷ ũ�⸦ �Ľ��� �� �־�� �Ѵ�
//		if (dataSize < header.size)
//			break;
//
//		// ��Ŷ ���� ����
//		OnRecvPacket(&buffer[processLen], header.size);
//
//		processLen += header.size;
//	}
//
//	return processLen;
//}
