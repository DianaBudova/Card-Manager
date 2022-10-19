#pragma once
#include "Common.h"
#include "CardParent.h"
#include "CreditCard.h"
#include "DebitCard.h"
#include "EWallet.h"
#include <fstream>
class CardManager
{
	typedef void (*CMPrinterConsole)(const PaymentItem&);
	typedef void (*CMPrinterFile)(ostream&, const PaymentItem&);
	typedef void (*CMPrinterConsoleCategory)(const string, const uint);
	typedef void (*CMPrinterFileCategory)(ostream&, const string, const uint);
	typedef bool (*CMPredicateDate)(const PaymentItem&, const Date&);
	typedef bool (*CMPredicateSum)(const uint, const uint);
private:
	Card cards[3];
	void AllPaymentDate(const Card& obj, CMPrinterConsole printer, CMPredicateDate checkDate, const Date& date) const
	{
		for (size_t i = 0; i < obj.GetPaymentList().size(); i++)
			if (checkDate(obj.GetPaymentList()[i], date))
				printer(obj.GetPaymentList()[i]);
	}
	void AllPaymentMaxSum(const Card& obj, CMPrinterConsole printer01, CMPrinterFile printer02, CMPredicateDate checkDate, CMPredicateSum checkSum, const Date& date) const
	{
		std::vector<int> temp;
		for (size_t i = 0; i < obj.GetPaymentList().capacity(); i++)
			if (checkDate(obj.GetPaymentList()[i], date))
				temp.push_back(obj.GetPaymentList()[i].GetSum());
		std::sort(temp.begin(), temp.end());
		std::vector<int> sum;
		for (size_t i = 0; i < 3; i++)
			sum.push_back(temp[temp.size() - i - 1]);
		std::ofstream fout("TOP_3_MAX_SUM.txt", std::ios_base::trunc);
		if (!fout.is_open())
			cout << "Don't record to file" << endl;
		for (size_t i = 0; i < sum.capacity(); i++)
		{
			if (sum[i])
			{
				for (size_t j = 0; j < obj.GetPaymentList().capacity(); j++)
					if (checkDate(obj.GetPaymentList()[j], date))
						if (checkSum(obj.GetPaymentList()[j].GetSum(), sum[i]))
						{
							printer01(obj.GetPaymentList()[j]);
							printer02(fout, obj.GetPaymentList()[j]);
							break;
						}
			}
			else
				return;
		}
	}
	void AllPaymentPopularCategory(const Card& obj, CMPrinterConsoleCategory printer01, CMPrinterFileCategory printer02, CMPredicateDate checkDate, const Date& date) const
	{
		if (obj.GetPaymentList().size() == 0)
			return;
		std::vector<int> categoriesIndex, temp;
		for (size_t i = 0; i < numberOfCt; i++)
		{
			categoriesIndex.push_back(0);
			temp.push_back(0);
		}
		for (size_t i = 0; i < obj.GetPaymentList().size(); i++)
			for (size_t j = 0; j < numberOfCt; j++)
				if (obj.GetPaymentList()[i].GetCategory() == Categories[j] && checkDate(obj.GetPaymentList()[i], date))
				{
					categoriesIndex[j]++;
					temp[j]++;
					break;
				}
		std::sort(temp.begin(), temp.end());
		string arrCt[3];
		for (size_t i = 0, j = 0; i < numberOfCt; i++)
			if (temp[numberOfCt - j - 1] == 0)
				break;
			else
				if (categoriesIndex[i] == temp[numberOfCt - j - 1])
					arrCt[j++] = Categories[i];
		int arrSum[3] = {0, 0, 0};
		for (size_t i = 0; i < 3; i++)
			if (arrCt[i] == "")
				break;
			else
			{
				for (size_t j = 0; j < obj.GetPaymentList().size(); j++)
					if (arrCt[i] == obj.GetPaymentList()[j].GetCategory() && checkDate(obj.GetPaymentList()[j], date))
						arrSum[i] += obj.GetPaymentList()[j].GetSum();
			}
		std::ofstream fout("TOP_3_POPULAR_CATEGORIES.txt", std::ios_base::trunc);
		if (!fout.is_open())
			cout << "Don't record to file" << endl;
		for (int i = 0; i < 3; i++)
			if (arrCt[i] == "" && arrSum[i] == 0)
				return;
			else
			{
				printer01(arrCt[i], arrSum[i]);
				printer02(fout, arrCt[i], arrSum[i]);
			}
	}
public:
	bool CheckValidCard(ushort choice) const
	{
		switch (choice)
		{
		case 1:
			return (cards[0].GetName() == "Not" && cards[0].GetSurname() == "Named");
		case 2:
			return (cards[1].GetName() == "Not" && cards[1].GetSurname() == "Named");
		case 3:
			return (cards[2].GetName() == "Not" && cards[2].GetSurname() == "Named");
		}
		return false;
	}
	bool CreateCard(ushort choice, string name, string surname)
	{
		switch (choice)
		{
		case 1:
			if (!CheckValidCard(1))
				return false;
			cards[0] = CreditCard(name, surname);
			return true;
		case 2:
			if (!CheckValidCard(2))
				return false;
			cards[1] = DebitCard(name, surname);
			return true;
		case 3:
			if (!CheckValidCard(3))
				return false;
			cards[2] = EWallet(name, surname);
			return true;
		}
		return false;
	}
	bool ReplenishmentCard(ushort choice, uint sum)
	{
		switch (choice)
		{
		case 1:
			if (CheckValidCard(1))
				return false;
			return cards[0].IncreaseCash(sum);
		case 2:
			if (CheckValidCard(2))
				return false;
			return cards[1].IncreaseCash(sum);
		case 3:
			if (CheckValidCard(3))
				return false;
			return cards[2].IncreaseCash(sum);
		}
		return false;
	}
	bool PayCard(ushort choice, string category, uint sum)
	{
		switch (choice)
		{
		case 1:
			if (CheckValidCard(1))
				return false;
			return cards[0].Pay(category, sum);
		case 2:
			if (CheckValidCard(2))
				return false;
			return cards[1].Pay(category, sum);
		case 3:
			if (CheckValidCard(3))
				return false;
			return cards[2].Pay(category, sum);
		}
		return false;
	}
	void AllCardPayment(ushort choice, CMPrinterConsole printer, CMPredicateDate checkDate, const Date& date) const
	{
		switch (choice)
		{
		case 1:
			if (CheckValidCard(1))
				return;
			AllPaymentDate(cards[0], printer, checkDate, date);
			break;
		case 2:
			if (CheckValidCard(2))
				return;
			AllPaymentDate(cards[1], printer, checkDate, date);
			break;
		case 3:
			if (CheckValidCard(3))
				return;
			AllPaymentDate(cards[2], printer, checkDate, date);
			break;
		}
	}
	void AllCardPaymentMaxSum(ushort choice, CMPrinterConsole printer01, CMPrinterFile printer02, CMPredicateDate checkDate, CMPredicateSum checkSum, const Date& date) const
	{
		switch (choice)
		{
		case 1:
			if (CheckValidCard(1))
				return;
			AllPaymentMaxSum(cards[0], printer01, printer02, checkDate, checkSum, date);
			break;
		case 2:
			if (CheckValidCard(2))
				return;
			AllPaymentMaxSum(cards[1], printer01, printer02, checkDate, checkSum, date);
			break;
		case 3:
			if (CheckValidCard(3))
				return;
			AllPaymentMaxSum(cards[2], printer01, printer02, checkDate, checkSum, date);
			break;
		}
	}
	void AllCardPaymentPopularCategory(ushort choice, CMPrinterConsoleCategory printer01, CMPrinterFileCategory printer02, CMPredicateDate checkDate, const Date& date) const
	{
		switch (choice)
		{
		case 1:
			if (CheckValidCard(1))
				return;
			AllPaymentPopularCategory(cards[0], printer01, printer02, checkDate, date);
			break;
		case 2:
			if (CheckValidCard(2))
				return;
			AllPaymentPopularCategory(cards[1], printer01, printer02, checkDate, date);
			break;
		case 3:
			if (CheckValidCard(3))
				return;
			AllPaymentPopularCategory(cards[2], printer01, printer02, checkDate, date);
			break;
		}
	}
	ushort GetCardCommission(ushort choice) const
	{
		switch (choice)
		{
		case 1:
			return cards[0].GetCommission();
		case 2:
			return cards[1].GetCommission();
		case 3:
			return cards[2].GetCommission();
		}
	}
	uint GetCardMaxSumPayment(ushort choice) const
	{
		switch (choice)
		{
		case 1:
			return cards[0].GetMaxSumPayment();
		case 2:
			return cards[1].GetMaxSumPayment();
		case 3:
			return cards[2].GetMaxSumPayment();
		}
	}
};