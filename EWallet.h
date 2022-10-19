#pragma once
#include "Common.h"
#include "CardParent.h"
class EWallet : public Card
{
public:
	EWallet() : EWallet("Not", "Named") {}
	EWallet(string name, string surname) : Card(name, surname) {}
};