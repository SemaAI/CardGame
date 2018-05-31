#include "Player.h"

Player::Player(string name)
{
	Name = name;

	HP = 30;

	AttackPower = 0;
	AttackCount = 0;

	DefencivePower = 0;

	BuffedAttackPower = 0;

	MaxCostTurn = 0;
	NowCost = 0;

	vector<Card> Deck = vector<Card>();
	vector<Card> Hand = vector<Card>();
	vector<Card> Board = vector<Card>();

	srand((unsigned int)time(NULL));
}

Player::~Player()
{

}

void Player::ShuffleDeck()
{
	Card card = Card();
	int random;

	// Empty ī��� �״�� �� -> null ó�� �̿�
	for (int i = 1; i < Deck.size(); i++)
	{
		card = Deck[i];
		random = (rand()) % (Deck.size() - 1) + 1;
		Deck[i] = Deck[random];
		Deck[random] = card;
	}
}

Card Player::DrawCard()
{
	Card card;

	card = Deck.back();
	if (card.Index == 0)
	{
		cout << "���� ī�尡 �����ϴ�\n\n";
		_sleep(1000);
		return card;
	}

	Deck.pop_back();
	Hand.push_back(card);
	card.Place = &Hand;
	return card;
}

bool Player::PlayTurn(Player& enemy)
{
	do
	{
		cout << "1. �տ� �ִ� ī�� ����ϱ� / 2. ���忡 �ִ� ī�� ����ϱ� / 0. �� ���� \t �� ��������" << endl << endl;
		int input;
		cin >> input;
		switch (input)
		{
		case 0:
			cout << "���� �����մϴ�." << endl << endl;
			_sleep(1000);
			input = true;
			return false;
		case 1:
			cout << "ī�带 �� �� ���ϴ�." << endl << endl;
			_sleep(500);
			UseCardInHand(enemy);
			return true;
		case 2:
			cout << "���忡 �ִ� ī�带 ����մϴ�." << endl << endl;
			_sleep(500);
			UseCardOnBoard(enemy);
			return true;

		case 3:
			if (AttackCount >= 0)
			{
				cout << "�������� �����մϴ�." << endl << endl;
				_sleep(500);
				PlayerAttack(enemy);
				return true;
			}
			else
			{
				cout << "������ �� �����ϴ�." << endl << endl;
				_sleep(500);
				return true;
			}

		default:
			cout << "�߸� ����!" << endl << endl;
			_sleep(1000);
			return true;
		}
	} while (true);
}

bool Player::UseCardInHand(Player& enemy)
{
	do
	{
		cout << "ī�带 �����ϼ��� (���� ������ 1 ��� 0)" << endl << endl;
		int input;
		cin >> input;
		if (input == 0)
		{
			cout << "����մϴ�" << endl << endl;
			_sleep(1000);
			return false;
		}
		else if (input <= Hand.size())
		{
			if (NowCost >= Hand[input - 1].Cost)
			{
				// ����� ��
				cout << Hand[input - 1].Name << " ī�带 ���ϴ�.\n\n";
				_sleep(1000);
				//

				RaiseCardInHand(Hand[input - 1], enemy);
				break;
			}
			else
			{
				cout << "�ڽ�Ʈ�� " << Hand[input - 1].Cost - NowCost << " �����մϴ�." << endl << endl;
				_sleep(1000);
			}
		}
	} while (true);
	return true;
}

bool Player::UseCardOnBoard(Player& enemy)
{
	do
	{
		cout << "ī�带 �����ϼ��� (���� ������ 1, ��� 0)" << endl << endl;
		int input;
		cin >> input;
		if (input == 0)
		{
			cout << "����մϴ�" << endl << endl;
			_sleep(1000);
			return false;
		}
		else if (input <= Board.size())
		{
			if (Board[input - 1].IsEnabled)
			{
				cout << "������ ����� �����ϼ��� (��� ���� : -1, ī�� : ���� ��ȣ, ��� : 0)" << endl << endl;
				int target;
				cin >> target;
				if (target == 0)
				{
					cout << "����մϴ�" << endl << endl;
					_sleep(1000);
					return false;
				}
				else if (target == -1)
				{
					int damage = Board[input - 1].CurrentAttackPower;
					if (enemy.DefencivePower > damage)
					{
						enemy.DefencivePower -= damage;
					}
					else
					{
						damage -= enemy.DefencivePower;
						enemy.DefencivePower = 0;
						enemy.HP -= damage;
					}
					break;
				}
				else if (target <= enemy.Board.size())
				{
					Board[input - 1].Attack(enemy.Board[target - 1]);
					Board[input - 1].GetHurt(enemy.Board[target - 1].CurrentAttackPower);
					if (Board[input - 1].CurrentHP <= 0)
					{
						Board[input - 1].EnableDeathrattle(enemy);
						Board[input - 1].EraseMEE();
						if (enemy.Board[target - 1].CurrentHP <= 0)
						{
							enemy.Board[target - 1].EnableDeathrattle(*(Board[input - 1].MyPlayer));
							enemy.Board[target - 1].EraseMEE();
						}
						break;
					}

					Board[input - 1].IsEnabled = false;
				}
				else
				{
					cout << "�߸� ����!!" << endl << endl;
					_sleep(1000);
					return true;
				}
			}
			else
			{
				cout << "ī�尡 ��Ȱ��ȭ�Ǿ��־� ������ �� �����ϴ�." << endl << endl;
				_sleep(1000);
			}
		}
	} while (true);
	return true;
}

bool Player::RaiseCardInHand(Card& cardToRaise, Player& enemy)
{
	cardToRaise.EnableBattlecry(enemy);
	Board.push_back(cardToRaise);
	Board[Board.size() - 1].Place = &Board;
	if (Board[Board.size() - 1].CanDash)
	{
		Board[Board.size() - 1].IsEnabled = true;
	}
	NowCost -= cardToRaise.Cost;
	for (int i = 0; i < Hand.size(); i++)
	{
		if (Hand[i].Index == cardToRaise.Index)
		{
			Hand.erase(Hand.begin() + i);
			return true;
		}
	}
	return false;
}

bool Player::PlayerAttack(Player& enemy)
{
	cout << "������ ����� �����ϼ��� (��� ���� : -1, ī�� : ���� ��ȣ, ��� : 0)" << endl << endl;
	int input;
	cin >> input;
	if (input == 0)
	{
		cout << "����մϴ�" << endl << endl;
		_sleep(1000);
		return true;
	}
	else if (input == -1)
	{
		cout << "��� ������ �����մϴ�." << endl << endl;
		_sleep(500);
		int damage = AttackPower + BuffedAttackPower;
		if (enemy.DefencivePower >= damage)
		{
			enemy.DefencivePower -= damage;
		}
		else
		{
			damage -= enemy.DefencivePower;
			enemy.DefencivePower = 0;
			enemy.HP -= damage;
		}
		return true;
	}
}

/*
bool Player::RemoveCard(Card& cardToRemove)
{
	for (int i = 0; i < Board.size(); i++)
	{
		if (Board[i].Index == cardToRemove.Index)
		{
			Board.erase(Board.begin() + i);
			return true;
		}
	}
	return false;
}
*/