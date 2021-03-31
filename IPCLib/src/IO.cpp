#include "IO.h"

Input::Input(const std::u16string& path)
{
	handle = CreateFile((wchar_t*)path.c_str(), 
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	HRESULT error = GetLastError();
}
Input::Input(const std::shared_ptr<IPC>& ipc)
{
	handle = ipc->readHandle();
}

Output::Output(const std::u16string& path)
{
	handle = CreateFile((wchar_t*)path.c_str(), GENERIC_WRITE, 0, NULL,
		TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handle == INVALID_HANDLE_VALUE)
		handle = CreateFile((wchar_t*)path.c_str(), GENERIC_WRITE, 0, NULL,
			CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
}
Output::Output(const std::shared_ptr<IPC>& ipc)
{
	handle = ipc->writeHandle();
}

void Input::close()
{
	CloseHandle(handle);
}
void Output::close()
{
	CloseHandle(handle);
}

// Input

int8_t Input::readInt8()
{
	DWORD bytesRead;
	int8_t result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}
int16_t Input::readInt16()
{
	DWORD bytesRead;
	int16_t result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}
int32_t Input::readInt32()
{
	DWORD bytesRead;
	int32_t result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}
int64_t Input::readInt64()
{
	DWORD bytesRead;
	int64_t result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}

uint8_t Input::readUInt8()
{
	DWORD bytesRead;
	uint8_t result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}
uint16_t Input::readUInt16()
{
	DWORD bytesRead;
	uint16_t result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}
uint32_t Input::readUInt32()
{
	DWORD bytesRead;
	uint32_t result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}
uint64_t Input::readUInt64()
{
	DWORD bytesRead;
	uint64_t result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}

std::u16string Input::readU16String()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();
	char16_t result[1024];
	ReadFile(handle, result, size * sizeof(char16_t), &bytesRead, NULL);
	HRESULT error = GetLastError();

	result[size] = u'\0';
	return std::move(std::u16string(result));
}

char16_t Input::readU16Char()
{
	DWORD bytesRead;
	char16_t result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}

std::string Input::readASCIIString()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();
	char result[1024];
	ReadFile(handle, result, size * sizeof(char), &bytesRead, NULL);

	result[size] = '\0';
	return std::move(std::string(result));
}

char Input::readASCIIChar()
{
	DWORD bytesRead;
	char result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}

float Input::readFloat32()
{
	DWORD bytesRead;
	float result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}
double Input::readFloat64()
{
	DWORD bytesRead;
	double result;
	ReadFile(handle, (void*)&result, sizeof(result), &bytesRead, NULL);

	return result;
}

std::vector<int8_t> Input::readArrayInt8()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();

	std::vector<int8_t> result;
	result.resize(size);

	ReadFile(handle, result.data(), sizeof(int8_t) * size, &bytesRead, NULL);

	return std::move(result);
}
std::vector<int16_t> Input::readArrayInt16()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();

	std::vector<int16_t> result;
	result.resize(size);

	ReadFile(handle, result.data(), sizeof(int16_t) * size, &bytesRead, NULL);

	return std::move(result);
}
std::vector<int32_t> Input::readArrayInt32()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();

	std::vector<int32_t> result;
	result.resize(size);

	ReadFile(handle, result.data(), sizeof(int32_t) * size, &bytesRead, NULL);

	return std::move(result);
}
std::vector<int64_t> Input::readArrayInt64()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();

	std::vector<int64_t> result;
	result.resize(size);

	ReadFile(handle, result.data(), sizeof(int64_t) * size, &bytesRead, NULL);

	return std::move(result);
}

std::vector<uint8_t> Input::readArrayUInt8()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();

	std::vector<uint8_t> result;
	result.resize(size);

	ReadFile(handle, result.data(), sizeof(uint8_t) * size, &bytesRead, NULL);

	return std::move(result);
}
std::vector<uint16_t> Input::readArrayUInt16()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();

	std::vector<uint16_t> result;
	result.resize(size);

	ReadFile(handle, result.data(), sizeof(uint16_t) * size, &bytesRead, NULL);

	return std::move(result);
}
std::vector<uint32_t> Input::readArrayUInt32()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();

	std::vector<uint32_t> result;
	result.resize(size);

	ReadFile(handle, result.data(), sizeof(uint32_t) * size, &bytesRead, NULL);

	return std::move(result);
}
std::vector<uint64_t> Input::readArrayUInt64()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();

	std::vector<uint64_t> result;
	result.resize(size);

	ReadFile(handle, result.data(), sizeof(uint64_t) * size, &bytesRead, NULL);

	return std::move(result);
}

std::vector<float> Input::readArrayFloat32()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();

	std::vector<float> result;
	result.resize(size);


	ReadFile(handle, result.data(), sizeof(float) * size, &bytesRead, NULL);

	return std::move(result);
}
std::vector<double> Input::readArrayFloat64()
{
	DWORD bytesRead;
	uint32_t size = readUInt32();

	std::vector<double> result;
	result.resize(size);

	ReadFile(handle, result.data(), sizeof(double) * size, &bytesRead, NULL);

	return std::move(result);
}

// Output

void Output::writeInt8(int8_t value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}
void Output::writeInt16(int16_t value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}
void Output::writeInt32(int32_t value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}
void Output::writeInt64(int64_t value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}

void Output::writeUInt8(uint8_t value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}
void Output::writeUInt16(uint16_t value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}
void Output::writeUInt32(uint32_t value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}
void Output::writeUInt64(uint64_t value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}

void Output::writeU16String(const std::u16string& value)
{
	writeUInt32((uint32_t)value.size());
	DWORD bytesWritten;
	WriteFile(handle, (const void*)value.c_str(), value.size() * sizeof(char16_t), &bytesWritten, NULL);
}

void Output::writeU16Char(char16_t value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}

void Output::writeASCIIString(const std::string& value)
{
	writeUInt32((uint32_t)value.size());
	DWORD bytesWritten;
	WriteFile(handle, (const void*)value.c_str(), value.size() * sizeof(char), &bytesWritten, NULL);
}
void Output::writeASCIIChar(char value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}

void Output::writeFloat32(float value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}
void Output::writeFloat64(double value)
{
	DWORD bytesWritten;
	WriteFile(handle, (const void*)&value, sizeof(value), &bytesWritten, NULL);
}

void Output::writeArrayInt8(int8_t* values, uint32_t size)
{
	DWORD bytesWritten;

	writeUInt32(size);
	WriteFile(handle, values, sizeof(int8_t) * size, &bytesWritten, NULL);
}
void Output::writeArrayInt16(int16_t* values, uint32_t size)
{
	DWORD bytesWritten;

	writeUInt32(size);
	WriteFile(handle, values, sizeof(int16_t) * size, &bytesWritten, NULL);
}
void Output::writeArrayInt32(int32_t* values, uint32_t size)
{
	DWORD bytesWritten;

	writeUInt32(size);
	WriteFile(handle, values, sizeof(int32_t) * size, &bytesWritten, NULL);
}
void Output::writeArrayInt64(int64_t* values, uint32_t size)
{
	DWORD bytesWritten;

	writeUInt32(size);
	WriteFile(handle, values, sizeof(int64_t) * size, &bytesWritten, NULL);
}

void Output::writeArrayUInt8(uint8_t* values, uint32_t size)
{
	DWORD bytesWritten;

	writeUInt32(size);
	WriteFile(handle, values, sizeof(uint8_t) * size, &bytesWritten, NULL);
}
void Output::writeArrayUInt16(uint16_t* values, uint32_t size)
{
	DWORD bytesWritten;

	writeUInt32(size);
	WriteFile(handle, values, sizeof(uint16_t) * size, &bytesWritten, NULL);
}
void Output::writeArrayUInt32(uint32_t* values, uint32_t size)
{
	DWORD bytesWritten;

	writeUInt32(size);
	WriteFile(handle, values, sizeof(uint32_t) * size, &bytesWritten, NULL);
}
void Output::writeArrayUInt64(uint64_t* values, uint32_t size)
{
	DWORD bytesWritten;

	writeUInt32(size);
	WriteFile(handle, values, sizeof(uint64_t) * size, &bytesWritten, NULL);
}

void Output::writeArrayFloat32(float* values, uint32_t size)
{
	DWORD bytesWritten;

	writeUInt32(size);
	WriteFile(handle, values, sizeof(float) * size, &bytesWritten, NULL);
}
void Output::writeArrayFloat64(double* values, uint32_t size)
{
	DWORD bytesWritten;

	writeUInt32(size);
	WriteFile(handle, values, sizeof(double) * size, &bytesWritten, NULL);
}