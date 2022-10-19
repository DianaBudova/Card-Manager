#pragma once
#include "Common.h"
#include "CardParent.h"
class CreditCard : public Card
{
public:
	CreditCard() : CreditCard("Not", "Named") {}
	CreditCard(string name, string surname) : Card(name, surname) {}
};