#pragma once
#include "Common.h"
#include "CardParent.h"
class DebitCard : public Card
{
public:
	DebitCard() : DebitCard("Not", "Named") {}
	DebitCard(string name, string surname) : Card(name, surname) {}
};