#include "IPC.h"
#include <stdexcept>

void ipc::WriteInt8(HANDLE hSlot, int8_t value)
{
	DWORD bytesWritten;
	WriteFile(hSlot, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}

void ipc::WriteInt32(HANDLE hSlot, int32_t value)
{
	DWORD bytesWritten;
	WriteFile(hSlot, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}

void ipc::WriteUInt8(HANDLE hSlot, uint8_t value)
{
	DWORD bytesWritten;
	WriteFile(hSlot, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}

void ipc::WriteUInt32(HANDLE hSlot, uint32_t value)
{
	DWORD bytesWritten;
	WriteFile(hSlot, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}

void ipc::WriteU16String(HANDLE hSlot, const std::u16string& value)
{
	WriteUInt32(hSlot, (uint32_t)value.size());
	DWORD bytesWritten;
	WriteFile(hSlot, (const void*)value.c_str(), value.size() * sizeof(char16_t), &bytesWritten, NULL);
}

void ipc::WriteArrayInt16(HANDLE hSlot, int16_t* values, uint32_t size)
{
	DWORD bytesWritten;

	WriteUInt32(hSlot, size);
	WriteFile(hSlot, values, sizeof(int16_t) * size, &bytesWritten, NULL);
}

int8_t ipc::ReadInt8(HANDLE hSlot)
{
	WaitForData(hSlot);

	DWORD bytesRead;
	int8_t result;
	ReadFile(hSlot, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}

int32_t ipc::ReadInt32(HANDLE hSlot)
{
	WaitForData(hSlot);

	DWORD bytesRead;
	int32_t result;
	ReadFile(hSlot, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}

uint32_t ipc::ReadUInt32(HANDLE hSlot)
{
	WaitForData(hSlot);

	DWORD bytesRead;
	uint32_t result;
	HRESULT error = GetLastError();
	int a = ReadFile(hSlot, (void*)&result, sizeof(result), &bytesRead, NULL);
	error = GetLastError();

	return result;
}

std::u16string ipc::ReadU16String(HANDLE hSlot)
{
	WaitForData(hSlot);

	DWORD bytesRead;
	uint32_t size = ReadUInt32(hSlot);
	char16_t result[1024];
	ReadFile(hSlot, result, size * sizeof(char16_t), &bytesRead, NULL);

	result[size] = u'\0';
	return std::move(std::u16string(result));
}

std::vector<int16_t> ipc::ReadArrayInt16(HANDLE hSlot)
{
	DWORD bytesRead;
	uint32_t size = ReadUInt32(hSlot);

	std::vector<int16_t> result;
	result.resize(size);

	WaitForData(hSlot);

	ReadFile(hSlot, result.data(), sizeof(int16_t) * size, &bytesRead, NULL);

	return std::move(result);
}

HANDLE ipc::CreateSlot(const std::u16string& name)
{
	HANDLE hSlot = CreateMailslot((LPCWSTR)name.c_str(),
		0, MAILSLOT_WAIT_FOREVER, (LPSECURITY_ATTRIBUTES)NULL);

	return hSlot;
}

HANDLE ipc::ConnectToSlot(const std::u16string& name)
{
	HANDLE hSlot = CreateFile((LPCWSTR)name.c_str(),
		GENERIC_WRITE,
		FILE_SHARE_READ,
		(LPSECURITY_ATTRIBUTES)NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);

	return hSlot;
}

void ipc::Disconnect(HANDLE hSlot)
{
	CloseHandle(hSlot);
}

bool ipc::HasNewData(HANDLE hSlot)
{
	DWORD cbMessage, cMessage;
	if (!GetMailslotInfo(hSlot, (LPDWORD)NULL, &cbMessage, &cMessage, (LPDWORD)NULL))
		return true;
	
	return cbMessage != MAILSLOT_NO_MESSAGE;
}

bool ipc::IsInvalid(HANDLE hSlot)
{
	return hSlot == INVALID_HANDLE_VALUE;
}


