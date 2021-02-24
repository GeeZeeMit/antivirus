#pragma once
#include <Windows.h>
#include <stdint.h>
#include <string>
#include <vector>

enum class TYPECODE : uint8_t
{
	UINT8 = 0, UINT32,
	INT8, INT32,
	U16STRING,
	STRUCT,

	// arrays
	AINT16
};
enum class CMDCODE : uint8_t
{
	TEST = 0
};

class ipc
{
public:
	// utility
	static HANDLE CreateSlot(const std::u16string& name);
	static HANDLE ConnectToSlot(const std::u16string& name);
	static void Disconnect(HANDLE hSlot);
	static bool HasNewData(HANDLE hSlot);
	static bool IsInvalid(HANDLE hSlot);
	inline static void WaitForData(HANDLE hSlot) { while (!HasNewData(hSlot)) {} }

	// WRITE

	//signed int
	static void WriteInt8(HANDLE hSlot, int8_t value);
	static void WriteInt32(HANDLE hSlot, int32_t value);
	
	//unsigned int
	static void WriteUInt8(HANDLE hSlot, uint8_t value);
	static void WriteUInt32(HANDLE hSlot, uint32_t value);

	// string
	static void WriteU16String(HANDLE hSlot, const std::u16string& value);

	// array
	static void WriteArrayInt16(HANDLE hSlot, int16_t* values, uint32_t size);

	// struct
	template<typename T>
	static void WriteStruct(HANDLE hSlot, const T& value)
	{
		DWORD bytesWritten;
		WriteFile(hSlot, (const void*)&value, sizeof(value), &bytesWritten, NULL);
	}

	// READ

	// signed int
	static int8_t  ReadInt8(HANDLE hSlot);
	static int32_t ReadInt32(HANDLE hSlot);

	// unsigned int
	static uint32_t ReadUInt32(HANDLE hSlot);
	
	// string
	static std::u16string ReadU16String(HANDLE hSlot);
	
	// array
	static std::vector<int16_t> ReadArrayInt16(HANDLE hSlot);
	
	// struct
	template<typename T>
	static T ReadStruct(HANDLE hSlot)
	{
		WaitForData(hSlot);

		DWORD bytesRead;
		T result;
		ReadFile(hSlot, (void*)&result, sizeof(result), &bytesRead, NULL);

		return result;
	}

};
