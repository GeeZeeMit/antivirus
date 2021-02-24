#include "Client.h"
#include <QString>
#include <QThread>
#include <IPC.h>
#include <array>
#include <iostream>
#include <sstream>

struct TestStruct
{
	char testStringFromStruct[256];
	int16_t testNumberFromStruct;
};


Client::Client(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(this, &Client::output, ui.textEdit, &QTextEdit::append);
	connectToServer();
}

Client::~Client()
{
	ResetEvent(clientUp);
	ipc::Disconnect(hServer);
	ipc::Disconnect(hClient);
}

void Client::readFromServer()
{

}

void Client::writeToServer()
{

}

void Client::connectToServer()
{
	hClient = ipc::CreateSlot(u"\\\\.\\mailslot\\client");
	hServer = ipc::ConnectToSlot(u"\\\\.\\mailslot\\server");

	if (ipc::IsInvalid(hServer))
	{
		wakeUpServer();

		while (true)
		{
			hServer = ipc::ConnectToSlot(u"\\\\.\\mailslot\\server");

			if (!ipc::IsInvalid(hServer))
				break;

			Sleep(10);
		}
	}
	clientUp = OpenEvent(EVENT_ALL_ACCESS, NULL, TEXT("ClientUpEvent"));
	SetEvent(clientUp);
}


void Client::on_testButton_clicked()
{
	QThread* thread = QThread::create(&Client::IPCtestRequest, this);
	thread->start();
}

void Client::IPCtestRequest()
{
	// TEST DATA
	uint32_t testNumber = 8000;

	std::u16string testString = u"String";

	std::array <int16_t, 9> testArray = {
		15, 43, -138, -64, 0, 7, 431, 1, 2 
	};

	TestStruct testStruct = { "Happy New Year", -677 };
	////////////

	// send to server
	if (!ipc::IsInvalid(hServer))
	{
		QString report = QString::fromUtf16(u"Отправка серверу:\n");
		report += QString::number(testNumber) + "\n";
		report += QString::fromUtf16(testString.c_str()) + "\n";
		for (auto el : testArray)
			report += QString::number(el) + " ";
		report += "\n";
		report += testStruct.testStringFromStruct + QString("\n");
		report += QString::number(testStruct.testNumberFromStruct) + "\n";

		output(report);

		ipc::WriteUInt8(hServer, (uint8_t)CMDCODE::TEST);
		ipc::WriteUInt32(hServer, testNumber);
		ipc::WriteU16String(hServer, testString);
		ipc::WriteArrayInt16(hServer, testArray.data(), testArray.size());
		ipc::WriteStruct<TestStruct>(hServer, testStruct);
	}

	if (!ipc::IsInvalid(hClient))
	{
		// read echo from server
		uint32_t testNumberResponse = ipc::ReadUInt32(hClient);
		std::u16string testStringResponse = ipc::ReadU16String(hClient);
		std::vector<int16_t> testVector = ipc::ReadArrayInt16(hClient);
		TestStruct testStructResponse = ipc::ReadStruct<TestStruct>(hClient);
		
		// output

		QString report = QString::fromUtf16(u"Получено с сервера:\n");
		report += QString::number(testNumberResponse) + "\n";
		report += QString::fromUtf16(testStringResponse.c_str()) + "\n";
		for (auto el : testVector)
			report += QString::number(el) + " ";
		report += "\n";
		report += testStructResponse.testStringFromStruct + QString("\n");
		report += QString::number(testStructResponse.testNumberFromStruct) + "\n";

		output(report);
	}
}

void Client::wakeUpServer()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	wchar_t path[256] = L"Server.exe";
	if (!CreateProcess(NULL,
		path,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi)
		)	
	{
		HRESULT error = GetLastError();
		return;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void Client::sendRequest()
{
	writeToServer();
	readFromServer();
}
