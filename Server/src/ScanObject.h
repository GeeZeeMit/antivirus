#pragma once

#include <stdint.h>
#include <string>
#include <zip.h>

enum class OBJTYPE { NONE = 0, DIRENTRY, ZIPENTRY, MEMORY};

struct ScanObject
{
	OBJTYPE objtype = OBJTYPE::NONE;

	// Атрибуты для записи каталога
	std::u16string fileType = u"";
	std::u16string filePath = u"";

	// Атрибуты для записи архива
	zip_t* archive = nullptr;
	zip_int64_t index = 0;

	// Атрибуты памяти
	uint8_t* address = nullptr;
	size_t size = 0;

};