#pragma once

#include "Card.h"

class Player
{
public:
	Player(string name);
	~Player();

	string Name;

	int HP;

	int AttackPower;
	int AttackCount;

	int DefencivePower;

	int BuffedAttackPower;

	int MaxCostTurn;
	int NowCost;

	vector<Card> Deck;
	vector<Card> Hand;
	vector<Card> Board;

	void ShuffleDeck();

	Card DrawCard();

	bool PlayTurn(Player& enemy);
	bool UseCardInHand(Player& enemy);
	bool UseCardOnBoard(Player& enemy);
	bool RaiseCardInHand(Card& cardToRaise, Player& enemy);
	bool PlayerAttack(Player& enemy);

	//bool RemoveCard(Card& cardToRemove);
};