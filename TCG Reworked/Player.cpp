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

	// Empty 카드는 그대로 둠 -> null 처럼 이용
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
		cout << "남은 카드가 없습니다\n\n";
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
		cout << "1. 손에 있는 카드 사용하기 / 2. 보드에 있는 카드 사용하기 / 0. 턴 종료 \t 잘 누르세요" << endl << endl;
		int input;
		cin >> input;
		switch (input)
		{
		case 0:
			cout << "턴을 종료합니다." << endl << endl;
			_sleep(1000);
			input = true;
			return false;
		case 1:
			cout << "카드를 한 장 냅니다." << endl << endl;
			_sleep(500);
			UseCardInHand(enemy);
			return true;
		case 2:
			cout << "보드에 있는 카드를 사용합니다." << endl << endl;
			_sleep(500);
			UseCardOnBoard(enemy);
			return true;

		case 3:
			if (AttackCount >= 0)
			{
				cout << "영웅으로 공격합니다." << endl << endl;
				_sleep(500);
				PlayerAttack(enemy);
				return true;
			}
			else
			{
				cout << "공격할 수 없습니다." << endl << endl;
				_sleep(500);
				return true;
			}

		default:
			cout << "잘못 누름!" << endl << endl;
			_sleep(1000);
			return true;
		}
	} while (true);
}

bool Player::UseCardInHand(Player& enemy)
{
	do
	{
		cout << "카드를 선택하세요 (제일 왼쪽이 1 취소 0)" << endl << endl;
		int input;
		cin >> input;
		if (input == 0)
		{
			cout << "취소합니다" << endl << endl;
			_sleep(1000);
			return false;
		}
		else if (input <= Hand.size())
		{
			if (NowCost >= Hand[input - 1].Cost)
			{
				// 디버깅 중
				cout << Hand[input - 1].Name << " 카드를 냅니다.\n\n";
				_sleep(1000);
				//

				RaiseCardInHand(Hand[input - 1], enemy);
				break;
			}
			else
			{
				cout << "코스트가 " << Hand[input - 1].Cost - NowCost << " 부족합니다." << endl << endl;
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
		cout << "카드를 선택하세요 (제일 왼쪽이 1, 취소 0)" << endl << endl;
		int input;
		cin >> input;
		if (input == 0)
		{
			cout << "취소합니다" << endl << endl;
			_sleep(1000);
			return false;
		}
		else if (input <= Board.size())
		{
			if (Board[input - 1].IsEnabled)
			{
				cout << "공격할 대상을 선택하세요 (상대 영웅 : -1, 카드 : 보드 번호, 취소 : 0)" << endl << endl;
				int target;
				cin >> target;
				if (target == 0)
				{
					cout << "취소합니다" << endl << endl;
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
					cout << "잘못 누름!!" << endl << endl;
					_sleep(1000);
					return true;
				}
			}
			else
			{
				cout << "카드가 비활성화되어있어 공격할 수 없습니다." << endl << endl;
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
	cout << "공격할 대상을 선택하세요 (상대 영웅 : -1, 카드 : 보드 번호, 취소 : 0)" << endl << endl;
	int input;
	cin >> input;
	if (input == 0)
	{
		cout << "취소합니다" << endl << endl;
		_sleep(1000);
		return true;
	}
	else if (input == -1)
	{
		cout << "상대 영웅을 공격합니다." << endl << endl;
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