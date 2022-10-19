#pragma once
#include "Common.h"
#include "Date.h"
#include "PaymentItem.h"
class Card
{
private:
	string name = "Not";
	string surname = "Named";
	Date deadline;
	uint cash = 0;
	ushort CVV = 0;
	ushort PIN = 0;
	std::vector<PaymentItem> paymentList;
	static const uint cashLimit = 1000000000;
	static const uint maxSumPayment = 200000;
	static const ushort commission = 2;
	void DecreaseCash(uint sum)
	{
		if ((cash - sum) < 0)
			return;
		cash -= sum;
	}
public:
	Card() : Card("Not", "Named") {}
	Card(string name, string surname)
	{
		srand(time(0));
		this->name = name;
		this->surname = surname;
		CVV = 100 + rand() % 899;
		PIN = 1000 + rand() % 8999;
		tm now;
		time_t timeObject = time(0);
		localtime_s(&now, &timeObject);
		deadline.SetMonth(now.tm_mon + 1);
		deadline.SetYear(now.tm_year + 1902);
	}
	bool IncreaseCash(uint sum)
	{
		if (sum > maxSumPayment || sum + cash - commission > cashLimit)
			return false;
		cash += sum - commission;
		return true;
	}
	bool Pay(string category, uint sum)
	{
		if (sum > cash)
			return false;
		bool leave = false;
		for (uint i = 0; i < numberOfCt; i++)
		{
			if (leave)
				break;
			(category == Categories[i]) ? leave = true : leave = false;
		}
		if (!leave)
			return false;
		tm now;
		time_t timeObject = time(0);
		localtime_s(&now, &timeObject);
		paymentList.push_back(PaymentItem(now.tm_min, now.tm_hour, now.tm_mday, now.tm_mon + 1, now.tm_year + 1900, category, sum));
		DecreaseCash(sum);
		return true;
	}
	uint GetCashLimit() const
	{
		return this->cashLimit;
	}
	uint GetMaxSumPayment() const
	{
		return this->maxSumPayment;
	}
	uint GetCash() const
	{
		return this->cash;
	}
	string GetName() const
	{
		return this->name;
	}
	string GetSurname() const
	{
		return this->surname;
	}
	Date GetDeadline() const
	{
		return this->deadline;
	}
	ushort GetCommission() const
	{
		return this->commission;
	}
	std::vector<PaymentItem> GetPaymentList() const
	{
		return this->paymentList;
	}
};