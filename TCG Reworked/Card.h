#pragma once

#include "Header.h"

class Player;

class Card
{
public:
	Card();
	Card(string name, int cost, Type type, int atk, int hp, bool dash, bool aggro, int index);
	~Card();

	string Name;
	int Cost;
	Type CardType;
	bool IsEnabled;

	vector<Card>* Place;
	Player* MyPlayer;

	int AttackPower;
	int CurrentAttackPower;
	int HP;
	int CurrentHP;

	bool CanDash;
	bool CanAggro;

	int Index;

	void EnableBattlecry(Player& enemy);
	void EnableDeathrattle(Player& enemy);
	void EnableSpecial(Player& enemy);
	void Attack(Card& target);
	void GetHurt(int damage);
	void EraseMEE();
};