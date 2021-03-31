#include "TimeScanner.h"
#include "Windows.h"
#include <thread>

TimeScanner::TimeScanner(const std::shared_ptr<Base>& base, const std::shared_ptr<ThreatList>& threats, 
	const std::u16string path /*= u""*/, uint32_t hours /*= 0*/, uint32_t minutes /*= 0*/)
	: scanner(base, threats)
{
	scanPath = path;
	this->hours = hours;
	this->minutes = minutes;
}

TimeScanner& TimeScanner::operator=(const TimeScanner& other)
{
	scanner = other.scanner;
	hours = other.hours;
	minutes = other.minutes;
	scanPath = other.scanPath;

	return *this;
}

void TimeScanner::setScanTime(uint32_t hours, uint32_t minutes)
{
	this->hours = hours;
	this->minutes = minutes;
}

void TimeScanner::setScanPath(const std::u16string& path)
{
	scanPath = path;
}


void TimeScanner::start()
{
	timeMonitoring();
}

void TimeScanner::timeMonitoring()
{
	SYSTEMTIME now;

	GetLocalTime(&now);

	while (true)
	{
		if (shouldStop)
			return;

		GetLocalTime(&now);
		if (now.wHour == hours && now.wMinute == minutes)
		{
			scanner.startScan(scanPath);
			Sleep(1000 * 60);
		}

		Sleep(1000);
	}

}

