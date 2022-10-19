#pragma once
#include "Common.h"
#include "Functions.h"
#include "CardManager.h"
class Menu
{
private:
	CardManager CM;
	void Bar01() const
	{
		cout << endl << "+---WELCOME-TO-PERSONAL-FINANCIAL-MANAGEMENT---+" << endl
			<< "|                                              |" << endl
			<< "|   CREATE CREDIT CARD                 (1)     |" << endl
			<< "|   CREATE DEBIT CARD                  (2)     |" << endl
			<< "|   CREATE E-WALLET                    (3)     |" << endl;
		if (!CM.CheckValidCard(1) || !CM.CheckValidCard(2) || !CM.CheckValidCard(3))
			cout << "|   MANAGE PERSONAL FINANCIAL          (4)     |" << endl;
		cout << "|   EXIT                               (0)     |" << endl
			<< "|                                              |" << endl
			<< "+----------------------------------------------+" << endl << endl;
	}
	void Bar02() const
	{
		cout << endl << "+----------------------------------------------+" << endl
			<< "|                                              |" << endl;
		if (!CM.CheckValidCard(1))
			cout << "|   MANAGE CREDIT CARD                 (1)     |" << endl;
		if (!CM.CheckValidCard(2))
			cout << "|   MANAGE DEBIT CARD                  (2)     |" << endl;
		if (!CM.CheckValidCard(3))
			cout << "|   MANAGE E-WALLET                    (3)     |" << endl;
		cout << "|   RETURN                             (4)     |" << endl
			<< "|   EXIT                               (0)     |" << endl
			<< "|                                              |" << endl
			<< "+----------------------------------------------+" << endl << endl;
	}
	void Bar03() const
	{
		cout << endl << "+----------------------------------------------+" << endl
			<< "|                                              |" << endl
			<< "|   REPLENISHMENT                      (1)     |" << endl
			<< "|   PAY                                (2)     |" << endl
			<< "|   SHOW PAYMENT BY DATE               (3)     |" << endl
			<< "|   SHOW TOP 3 BY SUM                  (4)     |" << endl
			<< "|   SHOW TOP 3 BY CATEGORIES           (5)     |" << endl
			<< "|   RETURN                             (6)     |" << endl
			<< "|   EXIT                               (0)     |" << endl
			<< "|                                              |" << endl
			<< "+----------------------------------------------+" << endl << endl;
	}
	void BarPrint01() const
	{
		cout << "+---DATE--&--TIME-------CATEGORY---------SUM---+" << endl;
	}
	void BarPrint02() const
	{
		cout << "+----CATEGORY----------------------SUM---------+" << endl;
	}
	void CheckChoice(const ushort num01, const ushort num02, ushort& value) const
	{
		while (value < num01 || value > num02)
		{
			cout << "Enter again >> ";
			cin >> value;
		}
	}
public:
	Menu()
	{
		Create();
	}
	void Create()
	{
		Bar01();
		cout << "Enter the menu item >> ";
		ushort item;
		cin >> item;
		CheckChoice(0, 4, item);
		if (!item)
			exit(0);
		if (item == 4)
		{
			if (!CM.CheckValidCard(1) || !CM.CheckValidCard(2) || !CM.CheckValidCard(3))
				Manage();
			else
				CheckChoice(0, 3, item);
		}
		string name, surname;
		cout << "Enter name >> ";
		cin >> name;
		cout << "Enter surname >> ";
		cin >> surname;
		switch (item)
		{
		case 1:
			if (CM.CreateCard(item, name, surname))
				cout << "Credit Card created successfully" << endl;
			else
				cout << "Credit Card exists already" << endl;
			Manage();
			break;
		case 2:
			if (CM.CreateCard(item, name, surname))
				cout << "Debit Card created successfully" << endl;
			else
				cout << "Debit Card exists already" << endl;
			Manage();
			break;
		case 3:
			if (CM.CreateCard(item, name, surname))
				cout << "E-Wallet created successfully" << endl;
			else
				cout << "E-Wallet exists already" << endl;
			Manage();
			break;
		}
	}
	void Manage()
	{
		Bar02();
		cout << "Enter the menu item >> ";
		ushort item;
		cin >> item;
		CheckChoice(0, 4, item);
		for (ushort i = 0; i < 3; i++)
		{
			if (item == i + 1)
				if (!CM.CheckValidCard(item))
					break;
				else
				{
					while (true)
					{
						if (!CM.CheckValidCard(item))
							break;
						cout << "Enter incorrect value" << endl
							<< "Enter again >> ";
						cin >> item;
					}
					break;
				}
		}
		switch (item)
		{
		case 1:
			if (!CM.CheckValidCard(1))
				ManageCreditCard();
			break;
		case 2:
			if (!CM.CheckValidCard(2))
				ManageDebitCard();
			break;
		case 3:
			if (!CM.CheckValidCard(3))
				ManageEWallet();
			break;
		case 4:
			Create();
			break;
		case 0:
			exit(0);
		}
	}
	void ManageCreditCard()
	{
		while (true)
		{
			Bar03();
			cout << "Enter the menu item >> ";
			ushort item;
			cin >> item;
			CheckChoice(0, 6, item);
			switch (item)
			{
			case 1:
				uint sum;
				cout << "Enter sum >> ";
				cin >> sum;
				if (CM.ReplenishmentCard(1, sum))
					cout << "Credit Card balance replenished successfully of " << sum - CM.GetCardCommission(1) << endl;
				else
					cout << "Sum more than " << CM.GetCardMaxSumPayment(1) << "  OR  Cash limit has been reached" << endl;
				break;
			case 2:
			{
				string category;
				cout << endl << "| ";
				for (size_t i = 0; i < numberOfCt; i++)
					cout << Categories[i] << " | ";
				cout << endl << "Enter category >> ";
				cin >> category;
				uint sum;
				cout << "Enter sum >> ";
				cin >> sum;
				if (CM.PayCard(1, category, sum))
					cout << "Paid successfully" << endl;
				else
					cout << "Too little cash  OR  Category entered wrong" << endl;
				break;
			}
			case 3:
			{
				ushort choice;
				cout << "Day(1), Week(2), Month(3)" << endl;
				cout << "Enter show >> ";
				cin >> choice;
				CheckChoice(1, 3, choice);
				string date01;
				cout << "Enter to which date(dd.mm.yyyy) >> ";
				cin >> date01;
				Date date02;
				Date::TryParse(date01, &date02);
				BarPrint01();
				switch (choice)
				{
				case 1:
					CM.AllCardPayment(1, PrintConsole, PredicateDay, date02);
					break;
				case 2:
					CM.AllCardPayment(1, PrintConsole, PredicateWeek, date02);
					break;
				case 3:
					CM.AllCardPayment(1, PrintConsole, PredicateMonth, date02);
					break;
				}
				break;
			}
			case 4:
			{
				ushort choice;
				cout << "Week(1), Month(2)" << endl;
				cout << "Enter show >> ";
				cin >> choice;
				CheckChoice(1, 2, choice);
				string date01;
				cout << "Enter to which date(dd.mm.yyyy) >> ";
				cin >> date01;
				Date date02;
				Date::TryParse(date01, &date02);
				BarPrint01();
				switch (choice)
				{
				case 1:
					CM.AllCardPaymentMaxSum(1, PrintConsole, PrintFile, PredicateWeek, PredicateSum, date02);
					break;
				case 2:
					CM.AllCardPaymentMaxSum(1, PrintConsole, PrintFile, PredicateMonth, PredicateSum, date02);
					break;
				}
				break;
			}
			case 5:
			{
				ushort choice;
				cout << "Week(1), Month(2)" << endl;
				cout << "Enter show >> ";
				cin >> choice;
				CheckChoice(1, 2, choice);
				string date01;
				cout << "Enter to which date(dd.mm.yyyy) >> ";
				cin >> date01;
				Date date02;
				Date::TryParse(date01, &date02);
				BarPrint02();
				switch (choice)
				{
				case 1:
					CM.AllCardPaymentPopularCategory(1, PrintConsoleCategory, PrintFileCategory, PredicateWeek, date02);
					break;
				case 2:
					CM.AllCardPaymentPopularCategory(1, PrintConsoleCategory, PrintFileCategory, PredicateMonth, date02);
					break;
				}
				break;
			}
			case 6:
				Manage();
				break;
			case 0:
				exit(0);
			}
		}
	}
	void ManageDebitCard()
	{
		while (true)
		{
			Bar03();
			cout << "Enter the menu item >> ";
			ushort item;
			cin >> item;
			CheckChoice(0, 6, item);
			switch (item)
			{
			case 1:
				uint sum;
				cout << "Enter sum >> ";
				cin >> sum;
				if (CM.ReplenishmentCard(2, sum))
					cout << "Debit Card balance replenished successfully of " << sum - CM.GetCardCommission(2) << endl;
				else
					cout << "Sum more than " << CM.GetCardMaxSumPayment(2) << "  OR  Cash limit has been reached" << endl;
				break;
			case 2:
			{
				string category;
				cout << endl << "| ";
				for (size_t i = 0; i < numberOfCt; i++)
					cout << Categories[i] << " | ";
				cout << endl << "Enter category >> ";
				cin >> category;
				uint sum;
				cout << "Enter sum >> ";
				cin >> sum;
				if (CM.PayCard(2, category, sum))
					cout << "Paid successfully" << endl;
				else
					cout << "Too little cash  OR  Category entered wrong" << endl;
				break;
			}
			case 3:
			{
				ushort choice;
				cout << "Day(1), Week(2), Month(3)" << endl;
				cout << "Enter show >> ";
				cin >> choice;
				CheckChoice(1, 3, choice);
				string date01;
				cout << "Enter to which date(dd.mm.yyyy) >> ";
				cin >> date01;
				Date date02;
				Date::TryParse(date01, &date02);
				BarPrint01();
				switch (choice)
				{
				case 1:
					CM.AllCardPayment(2, PrintConsole, PredicateDay, date02);
					break;
				case 2:
					CM.AllCardPayment(2, PrintConsole, PredicateWeek, date02);
					break;
				case 3:
					CM.AllCardPayment(2, PrintConsole, PredicateMonth, date02);
					break;
				}
				break;
			}
			case 4:
			{
				ushort choice;
				cout << "Week(1), Month(2)" << endl;
				cout << "Enter show >> ";
				cin >> choice;
				CheckChoice(1, 2, choice);
				string date01;
				cout << "Enter to which date(dd.mm.yyyy) >> ";
				cin >> date01;
				Date date02;
				Date::TryParse(date01, &date02);
				BarPrint01();
				switch (choice)
				{
				case 1:
					CM.AllCardPaymentMaxSum(2, PrintConsole, PrintFile, PredicateWeek, PredicateSum, date02);
					break;
				case 2:
					CM.AllCardPaymentMaxSum(2, PrintConsole, PrintFile, PredicateMonth, PredicateSum, date02);
					break;
				}
				break;
			}
			case 5:
			{
				ushort choice;
				cout << "Week(1), Month(2)" << endl;
				cout << "Enter show >> ";
				cin >> choice;
				CheckChoice(1, 2, choice);
				string date01;
				cout << "Enter to which date(dd.mm.yyyy) >> ";
				cin >> date01;
				Date date02;
				Date::TryParse(date01, &date02);
				BarPrint02();
				switch (choice)
				{
				case 1:
					CM.AllCardPaymentPopularCategory(2, PrintConsoleCategory, PrintFileCategory, PredicateWeek, date02);
					break;
				case 2:
					CM.AllCardPaymentPopularCategory(2, PrintConsoleCategory, PrintFileCategory, PredicateMonth, date02);
					break;
				}
				break;
			}
			case 6:
				Manage();
				break;
			case 0:
				exit(0);
			}
		}
	}
	void ManageEWallet()
	{
		while (true)
		{
			Bar03();
			cout << "Enter the menu item >> ";
			ushort item;
			cin >> item;
			CheckChoice(0, 6, item);
			switch (item)
			{
			case 1:
				uint sum;
				cout << "Enter sum >> ";
				cin >> sum;
				if (CM.ReplenishmentCard(3, sum))
					cout << "E-Wallet balance replenished successfully of " << sum - CM.GetCardCommission(3) << endl;
				else
					cout << "Sum more than " << CM.GetCardMaxSumPayment(3) << "  OR  Cash limit has been reached" << endl;
				break;
			case 2:
			{
				string category;
				cout << endl << "| ";
				for (size_t i = 0; i < numberOfCt; i++)
					cout << Categories[i] << " | ";
				cout << endl << "Enter category >> ";
				cin >> category;
				uint sum;
				cout << "Enter sum >> ";
				cin >> sum;
				if (CM.PayCard(3, category, sum))
					cout << "Paid successfully" << endl;
				else
					cout << "Too little cash  OR  Category entered wrong" << endl;
				break;
			}
			case 3:
			{
				ushort choice;
				cout << "Day(1), Week(2), Month(3)" << endl;
				cout << "Enter show >> ";
				cin >> choice;
				CheckChoice(1, 3, choice);
				string date01;
				cout << "Enter to which date(dd.mm.yyyy) >> ";
				cin >> date01;
				Date date02;
				Date::TryParse(date01, &date02);
				BarPrint01();
				switch (choice)
				{
				case 1:
					CM.AllCardPayment(3, PrintConsole, PredicateDay, date02);
					break;
				case 2:
					CM.AllCardPayment(3, PrintConsole, PredicateWeek, date02);
					break;
				case 3:
					CM.AllCardPayment(3, PrintConsole, PredicateMonth, date02);
					break;
				}
				break;
			}
			case 4:
			{
				ushort choice;
				cout << "Week(1), Month(2)" << endl;
				cout << "Enter show >> ";
				cin >> choice;
				CheckChoice(1, 2, choice);
				string date01;
				cout << "Enter to which date(dd.mm.yyyy) >> ";
				cin >> date01;
				Date date02;
				Date::TryParse(date01, &date02);
				BarPrint01();
				switch (choice)
				{
				case 1:
					CM.AllCardPaymentMaxSum(3, PrintConsole, PrintFile, PredicateWeek, PredicateSum, date02);
					break;
				case 2:
					CM.AllCardPaymentMaxSum(3, PrintConsole, PrintFile, PredicateMonth, PredicateSum, date02);
					break;
				}
				break;
			}
			case 5:
			{
				ushort choice;
				cout << "Week(1), Month(2)" << endl;
				cout << "Enter show >> ";
				cin >> choice;
				CheckChoice(1, 2, choice);
				string date01;
				cout << "Enter to which date(dd.mm.yyyy) >> ";
				cin >> date01;
				Date date02;
				Date::TryParse(date01, &date02);
				BarPrint02();
				switch (choice)
				{
				case 1:
					CM.AllCardPaymentPopularCategory(3, PrintConsoleCategory, PrintFileCategory, PredicateWeek, date02);
					break;
				case 2:
					CM.AllCardPaymentPopularCategory(3, PrintConsoleCategory, PrintFileCategory, PredicateMonth, date02);
					break;
				}
				break;
			}
			case 6:
				Manage();
				break;
			case 0:
				exit(0);
			}
		}
	}
};