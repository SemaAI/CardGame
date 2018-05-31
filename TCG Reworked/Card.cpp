#include "Card.h"

#include "Player.h"

Card::Card()
{
	Name = "Empty";
	Cost = 0;
	CardType = Type::General;
	IsEnabled = false;

	AttackPower = 0;
	CurrentAttackPower = AttackPower;
	HP = 0;
	CurrentHP = HP;

	CanDash = false;
	CanAggro = false;

	Index = 0;
}

Card::Card(string name, int cost, Type type, int atk, int hp, bool dash, bool aggro, int index)
{
	Name = name;
	Cost = cost;
	CardType = type;
	IsEnabled = false;

	AttackPower = atk;
	CurrentAttackPower = AttackPower;
	HP = hp;
	CurrentHP = HP;

	CanDash = dash;
	CanAggro = aggro;

	Index = index;

}

Card::~Card()
{

}

void Card::EnableBattlecry(Player& enemy)
{
	switch (Index)
	{
	case 1:	case 2: // 돌진: 아군 하수인 하나에 공격력 +2, 돌진 부여 -> 돌진 부여는 보류
		if (Place->size() != 0)
		{
			cout << "돌진 : 공격력 +2를 부여할 하수인을 선택하세요(왼쪽부터 1)" << endl << endl;
			int input;
			cin >> input;
			if (input <= Place->size())
			{
				(*Place)[input - 1].CurrentAttackPower += 2;
			}
		}
		break;
	case 5: case 6: // 마무리 일격: 피해를 입은 하수인 하나를 처치
		for (int i = 0; i < enemy.Board.size(); i++)
		{
			if (enemy.Board[i].CurrentHP < enemy.Board[i].HP)
			{
				cout << enemy.Board[i].Name;
			}
		}
		cout << endl << endl;
		cout << "마무리 일격 : 피해를 입은 하수인 하나를 처치 할 수 있습니다. 위의 카드 중 처치할 하수인을 선택하세요(보드 번호로 선택)" << endl << endl;
		int cardToKill;
		cin >> cardToKill;
		if (cardToKill <= enemy.Board.size())
		{
			enemy.Board[cardToKill - 1].EraseMEE();
		}
		break;
	case 7: case 8: // 멀록 바다사냥꾼: 1/1의 멀록 정찰병 한 마리 소환
		cout << "멀록 바다사냥꾼 : 1/1의 멀록 정찰병 한 마리 소환" << endl << endl;
		_sleep(500);
		(*MyPlayer).Board.push_back(Card("멀록 정찰병", 0, Type::Servant, 1, 1, false, false, 31));
		break;
	case 11: case 12: // 영웅의 일격: 내 영웅이 이번 턴에 공격력 +4
		cout << "영웅의 일격 : 내 영웅에게 이번 턴만 공격력 +4를 부여합니다." << endl << endl;
		_sleep(500);
		MyPlayer->BuffedAttackPower += 4;
		break;
	case 13: case 14: // 이글거리는 전쟁도끼: 3/2의 무기 장착
		cout << "이글거리는 전쟁도끼 : 3/2의 무기를 장착합니다." << endl << endl;
		_sleep(500);
		MyPlayer->AttackPower = 3;
		MyPlayer->AttackCount += 2;
		break;
	case 15: case 16: // 가시덩굴 사냥꾼: 1/1의 멧돼지 한 마리 소환
		cout << "가시덩굴 사냥꾼 : 1/1의 멧돼지를 한 마리 소환합니다." << endl << endl;
		_sleep(500);
		(*MyPlayer).Board.push_back(Card("멧돼지", 0, Type::Servant, 1, 1, false, false, 32));
		break;
	case 19: case 20: // 전쟁노래 사령관: 내 돌진 하수인들이 공격력 +1
		cout << "전쟁노래 사령관 : 내 돌진 하수인들에게 공격력 +1을 부여합니다." << endl << endl;
		_sleep(500);
		for (int i = 0; i < Place->size(); i++)
		{
			if ((*Place)[i].CanDash)
			{
				(*Place)[i].CurrentAttackPower += 1;
			}
		}
		break;
	case 21: case 22: // 기계 용 정비사: 2/1의 소형 기계 용 한 마리 소환
		cout << "기계 용 정비사 : 2/1의 소형 기계 용 한 마리를 소환합니다." << endl << endl;
		_sleep(500);
		(*MyPlayer).Board.push_back(Card("소형 기계 용", 0, Type::Servant, 2, 1, false, false, 33));
		break;

	default:
		break;
	}
}

void Card::EnableDeathrattle(Player& enemy)
{

}

void Card::EnableSpecial(Player& enemy)
{
	switch (Index)
	{
	case 25: case 26:
		// 구루바시 광전사: 피해를 입을 때 마다 공격력 +3
		break;
	default:
		break;
	}
}

void Card::Attack(Card& target)
{
	target.GetHurt(CurrentAttackPower);
	GetHurt(target.CurrentAttackPower);
}

void Card::GetHurt(int damage)
{
	CurrentHP -= damage;
}

void Card::EraseMEE()
{
	if (CurrentHP <= 0)
	{
		for (int i = 0; i < (*Place).size(); i++)
		{
			if ((*Place)[i].Index == Index)
			{
				(*Place).erase((*Place).begin() + i);
				return;
			}
		}
	}
}