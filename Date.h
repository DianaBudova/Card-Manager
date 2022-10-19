#pragma once
#include "Common.h"
#include <chrono>
class Date
{
private:
	static const ushort  minYear = 1900;
	static const ushort  maxYear = 9999;
	static const ubyte monthLen[];
	static const string monthNames[];
	static const string dayNames[];
	ubyte minute = 0;
	ubyte hour = 0;
	ubyte day = 1;
	ubyte month = 1;
	ushort year = minYear;
public:
	Date() : Date(0, 0, 0, 0, 0) {}
	Date(ubyte m, ushort y) : Date(0, 0, 0, m ,y) {}
	Date(ubyte d, ubyte m, ushort y) : Date(0, 0, d, m, y) {}
	Date(ubyte min, ubyte h, ubyte d, ubyte m, ushort y)
	{
		minute = min;
		hour = h;
		day = d;
		month = m;
		year = y;
	}
	static bool TryParse(string date, Date* result)
	{
		if (!result)
			return false;
		std::stringstream dateData(date);
		size_t delimeterPos = date.find_first_of(string(".,/-"));
		if (delimeterPos == string::npos)
			return false;
		char delimeter = date[delimeterPos];
		string currentComponent;
		if (!std::getline(dateData, currentComponent, delimeter))
			return false;
		result->SetDay(std::stoi(currentComponent));
		if (!std::getline(dateData, currentComponent, delimeter))
			return false;
		result->SetMonth(std::stoi(currentComponent));
		if (!std::getline(dateData, currentComponent, delimeter) || currentComponent.length() != 4)
			return false;
		result->SetYear(std::stoi(currentComponent));
		return result->IsValidDate();
	}
	static uint Difference(const Date& lho, const Date& rho)
	{
		if (lho == rho)
			return 0;
		uint date01 = lho.year * 365 + lho.day;
		for (ubyte i = 1; i < lho.month; i++)
			date01 += monthLen[i];
		ubyte years = lho.year;
		if (lho.month <= 2)
			years--;
		date01 += years / 4 - years / 100 + years / 400;
		uint date02 = rho.year * 365 + rho.day;
		for (ubyte i = 1; i < rho.month; i++)
			date02 += monthLen[i];
		years = rho.year;
		if (rho.month <= 2)
			years--;
		date02 += years / 4 - years / 100 + years / 400;
		return (date01 > date02) ? date01 - date02 : date02 - date01;
	}
	static Date Today()
	{
		auto ymd = std::chrono::year_month_day{ floor<std::chrono::days>(std::chrono::zoned_time{std::chrono::system_clock::now()}.get_local_time()) };
		Date today(ymd.day().operator unsigned int(), ymd.month().operator unsigned int(), ymd.year().operator int());
		return today;
	}
	static bool IsLeapYear(int year)
	{
		return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));
	}
	static ubyte DayOfWeek(ubyte day, ubyte month, ushort year)
	{
		static ubyte magicMonth[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
		year -= month < 3;
		return ((year + year / 4 - year / 100 + year / 400 + magicMonth[month - 1] + day) % 7);
	}
	static bool IsValidDate(ubyte day, ubyte month, ushort year)
	{
		return !(year < Date::minYear || year > Date::maxYear || month < 1 || month > 12 || day < 1 || day >(Date::monthLen[month] + (Date::IsLeapYear(year) ? 1 : 0)));
	}
	static ubyte GetMonthLength(ushort year, ubyte month)
	{
		return (month == 2) ? Date::IsLeapYear(year) ? 29 : 28 : Date::monthLen[month];
	}
	static ushort GetYearLength(ushort year)
	{
		return Date::IsLeapYear(year) ? 366 : 365;
	}
	static Date DateByOffset(ushort year, ushort offset)
	{
		offset = __min(offset, Date::GetYearLength(year));
		Date result(1, 1, year);
		for (ubyte i = 1; i <= 12; i++)
		{
			result.month = i;
			ubyte currentMonthLen = Date::GetMonthLength(year, i);
			if (offset <= currentMonthLen)
				break;
			offset -= currentMonthLen;
		}
		result.day = offset;
		return result;
	}
	bool IsLeapYear() const
	{
		return Date::IsLeapYear(this->year);
	}
	int DayOfWeek() const
	{
		return Date::DayOfWeek(this->day, this->month, this->year);
	}
	bool IsValidDate() const
	{
		return Date::IsValidDate(this->day, this->month, this->year);
	}
	void SetMinute(ubyte min)
	{
		this->minute = min;
	}
	void SetHour(ubyte h)
	{
		this->hour = h;
	}
	void SetDay(ubyte d)
	{
		this->day = d;
	}
	void SetMonth(ubyte m)
	{
		this->month = m;
	}
	void SetYear(ushort y)
	{
		this->year = y;
	}
	ubyte GetMinute() const
	{
		return minute;
	}
	ubyte GetHour() const
	{
		return hour;
	}
	ubyte GetDay() const
	{
		return day;
	}
	ubyte GetMonth() const
	{
		return month;
	}
	ushort GetYear() const
	{
		return year;
	}
	ushort DaysSoFar() const
	{
		ushort days = this->day;
		for (ubyte i = 1; i < this->month; i++)
			days += Date::GetMonthLength(this->year, i);
		return days;
	}
	ushort DaysLeft() const
	{
		return Date::GetYearLength(this->year) - this->DaysSoFar();
	}
	string ToString() const
	{
		return string(std::format("{:02}.{:02}.{} - {:02}:{:02}", this->day, this->month, this->year, this->hour, this->minute));
	}
	bool operator==(const Date& rho) const
	{
		return this->day == rho.day && this->month == rho.month && this->year == rho.year;
	}
	bool operator!=(const Date& other) const
	{
		return !(*this == other);
	}
	friend bool operator<(const Date& lho, const Date& rho)
	{
		if (lho.year < rho.year)
			return true;
		else if (lho.year > rho.year)
			return false;
		if (lho.month < rho.month)
			return true;
		else if (lho.month > rho.month)
			return false;
		return lho.day < rho.day;
	}
	friend bool operator>=(const Date& lho, const Date& rho)
	{
		return !(lho < rho);
	}
	Date AddDays(uint offsetDays) const
	{
		ushort daysLeft = this->DaysLeft(), year = this->year;
		if (offsetDays <= daysLeft)
			offsetDays += this->DaysSoFar();
		else
			while (offsetDays > daysLeft)
			{
				offsetDays -= daysLeft;
				daysLeft = Date::GetYearLength(++year);
			}
		return Date::DateByOffset(year, offsetDays);
	}
	Date SubDays(uint offsetDays) const
	{
		ushort daysLeft = this->DaysLeft(), year = this->year;
		if (offsetDays <= daysLeft)
			offsetDays = this->DaysSoFar() - offsetDays;
		else
			while (offsetDays > daysLeft)
			{
				offsetDays -= daysLeft;
				daysLeft = Date::GetYearLength(--year);
			}
		return Date::DateByOffset(year, offsetDays);
	}
	bool CheckDateWeek(const Date& rho) const
	{
		if (rho < *this)
			return false;
		if (operator==(rho))
			return true;
		return Difference(*this, rho) < 7;
	}
	bool CheckDateMonth(const Date& rho) const 
	{
		if (rho < *this)
			return false;
		if (operator==(rho))
			return true;
		return Difference(*this, rho) < monthLen[this->month];
	}
	Date operator+(ushort offset)
	{
		AddDays(offset);
	}
	Date operator-(ushort offset)
	{
		SubDays(offset);
	}
	ushort operator-(const Date& other) const
	{
		return Date::Difference(*this, other);
	}
};
const ubyte Date::monthLen[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const string Date::monthNames[] = { "None","January","February","March","April","May","June","July","August","September","October","November","December" };
const string Date::dayNames[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };