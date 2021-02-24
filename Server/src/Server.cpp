#include "Server.h"
#include <IPC.h>
#include <thread>
#include <iostream>

Server::~Server()
{
	ipc::Disconnect(hServer);
	ipc::Disconnect(hClient);
}

void Server::processRequest()
{
	uint8_t cmdCode = ipc::ReadUInt32(hServer);
	if (cmdCode == (uint8_t)CMDCODE::TEST)
		processTestRequest();
}

void Server::waitForClient()
{
	hClient = ipc::ConnectToSlot(u"\\\\.\\mailslot\\client");

	while (ipc::IsInvalid(hClient))
	{
		Sleep(10);
		hClient = ipc::ConnectToSlot(u"\\\\.\\mailslot\\client");
	}

	WaitForSingleObject(clientUp, INFINITE);
}

void Server::startReading()
{
	hServer = ipc::CreateSlot(u"\\\\.\\mailslot\\server");

	while (true)
	{
		waitForClient();

		while (WaitForSingleObject(clientUp, 0) != WAIT_TIMEOUT)
		{
			if (!ipc::HasNewData(hServer))
				continue;

			processRequest();
		}

		ipc::Disconnect(hClient);
	}
}


void Server::processTestRequest()
{
	struct TestStruct
	{
		char testStringFromStruct[256];
		int16_t testNumberFromStruct;
	} testStruct;

	uint32_t testNumber = ipc::ReadUInt32(hServer);
	std::u16string testString = ipc::ReadU16String(hServer);
	std::vector<int16_t> testVector = ipc::ReadArrayInt16(hServer);
	testStruct = ipc::ReadStruct<TestStruct>(hServer);

	std::cout << testNumber << std::endl;
	std::wcout << (wchar_t*)testString.c_str() << std::endl;

	for (auto el : testVector)
		std::cout << el << " ";
	std::cout << std::endl;

	std::cout << testStruct.testStringFromStruct << std::endl;
	std::cout << testStruct.testNumberFromStruct << std::endl;

	ipc::WriteUInt32(hClient, testNumber);
	ipc::WriteU16String(hClient, testString);
	ipc::WriteArrayInt16(hClient, testVector.data(), testVector.size());
	ipc::WriteStruct<TestStruct>(hClient, testStruct);
}

