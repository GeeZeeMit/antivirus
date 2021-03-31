#pragma once
#include <Windows.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <memory>

#include "IPC.h"

class Input
{
public:
	Input(const std::u16string& path);
	Input(const std::shared_ptr<IPC>& ipc);
	Input(HANDLE handle) { this->handle = handle; }


	~Input() = default;

	void close();
	inline bool isOpen() { return handle != INVALID_HANDLE_VALUE; }

	// signed integers
	int8_t  readInt8();
	int16_t readInt16();
	int32_t readInt32();
	int64_t readInt64();

	// unsigned integers
	uint8_t readUInt8();
	uint16_t readUInt16();
	uint32_t readUInt32();
	uint64_t readUInt64();

	// string and character
	std::u16string readU16String();
	char16_t readU16Char();

	std::string readASCIIString();
	char readASCIIChar();

	// floats
	float readFloat32();
	double readFloat64();

	// arrays
	std::vector<int8_t> readArrayInt8();
	std::vector<int16_t> readArrayInt16();
	std::vector<int32_t> readArrayInt32();
	std::vector<int64_t> readArrayInt64();

	std::vector<uint8_t> readArrayUInt8();
	std::vector<uint16_t> readArrayUInt16();
	std::vector<uint32_t> readArrayUInt32();
	std::vector<uint64_t> readArrayUInt64();

	std::vector<float> readArrayFloat32();
	std::vector<double> readArrayFloat64();


	// struct
	template<typename T>
	T readStruct()
	{
		DWORD bytesRead;
		T result;
		ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

		return result;
	}

private:

	HANDLE handle;
};

class Output
{
public:

	Output(const std::u16string& path);
	Output(const std::shared_ptr<IPC>& ipc);
	Output(HANDLE handle) { this->handle = handle; }

	~Output() = default;

	void close();

	// WRITE FUNCTIONS

	//signed integers
	void writeInt8(int8_t value);
	void writeInt16(int16_t value);
	void writeInt32(int32_t value);
	void writeInt64(int64_t value);

	//unsigned integers
	void writeUInt8(uint8_t value);
	void writeUInt16(uint16_t value);
	void writeUInt32(uint32_t value);
	void writeUInt64(uint64_t value);

	// string and character
	void writeU16String(const std::u16string& value);
	void writeU16Char(char16_t value);

	void writeASCIIString(const std::string& value);
	void writeASCIIChar(char value);

	// floats
	void writeFloat32(float value);
	void writeFloat64(double value);

	// arrays
	void writeArrayInt8(int8_t* values, uint32_t size);
	void writeArrayInt16(int16_t* values, uint32_t size);
	void writeArrayInt32(int32_t* values, uint32_t size);
	void writeArrayInt64(int64_t* values, uint32_t size);

	void writeArrayUInt8(uint8_t* values, uint32_t size);
	void writeArrayUInt16(uint16_t* values, uint32_t size);
	void writeArrayUInt32(uint32_t* values, uint32_t size);
	void writeArrayUInt64(uint64_t* values, uint32_t size);

	void writeArrayFloat32(float* values, uint32_t size);
	void writeArrayFloat64(double* values, uint32_t size);


	// struct
	template<typename T>
	void writeStruct(const T& value)
	{
		DWORD bytesWritten;
		WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
	}

private:
	HANDLE handle;
};