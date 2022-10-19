#pragma once
#include "Common.h"
#include "PaymentItem.h"
void PrintConsole(const PaymentItem& obj)
{
	cout << obj << endl;
}
void PrintFile(ostream& fout, const PaymentItem& obj)
{
	fout << obj << endl;
}
void PrintConsoleCategory(const string category, const uint sum)
{
	cout << std::format("{:<10}\t{:>16}", category, sum) << endl;
}
void PrintFileCategory(ostream& fout, const string category, const uint sum)
{
	fout << std::format("{:<10}\t{:>12}", category, sum) << endl;
}
bool PredicateDay(const PaymentItem& obj, const Date& date)
{
	return obj.GetDate() == date;
}
bool PredicateWeek(const PaymentItem& obj, const Date& date)
{
	return obj.GetDate().CheckDateWeek(date);
}
bool PredicateMonth(const PaymentItem& obj, const Date& date)
{
	return obj.GetDate().CheckDateMonth(date);
}
bool PredicateSum(const uint sum01, const uint sum02)
{
	return sum01 == sum02;
}