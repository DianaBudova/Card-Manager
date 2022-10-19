#pragma once
#include "Common.h"
#include "Date.h"
class PaymentItem
{
private:
	Date date;
	string category;
	uint sum;
public:
	PaymentItem(ubyte min, ubyte h, ubyte d, ubyte m, ushort y, string category, uint sum)
	{
		this->SetDate(min, h, d, m, y);
		this->SetCategory(category);
		this->SetSum(sum);
	}
	void SetDate(ubyte min, ubyte h, ubyte d, ubyte m, ushort y)
	{
		this->date.SetMinute(min);
		this->date.SetHour(h);
		this->date.SetDay(d);
		this->date.SetMonth(m);
		this->date.SetYear(y);
	}
	void SetSum(uint sum)
	{
		this->sum = sum;
	}
	void SetCategory(string category)
	{
		this->category = category;
	}
	Date GetDate() const
	{
		return date;
	}
	string GetCategory() const
	{
		return category;
	}
	uint GetSum() const
	{
		return sum;
	}
	friend ostream& operator<<(ostream& out, const PaymentItem& obj)
	{
		out << std::format("{}\t{:^10}{:>12}", obj.GetDate().ToString(), obj.GetCategory(), (string(std::format("{}", obj.GetSum()))));
		return out;
	}
};