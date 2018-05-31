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
	case 1:	case 2: // ����: �Ʊ� �ϼ��� �ϳ��� ���ݷ� +2, ���� �ο� -> ���� �ο��� ����
		if (Place->size() != 0)
		{
			cout << "���� : ���ݷ� +2�� �ο��� �ϼ����� �����ϼ���(���ʺ��� 1)" << endl << endl;
			int input;
			cin >> input;
			if (input <= Place->size())
			{
				(*Place)[input - 1].CurrentAttackPower += 2;
			}
		}
		break;
	case 5: case 6: // ������ �ϰ�: ���ظ� ���� �ϼ��� �ϳ��� óġ
		for (int i = 0; i < enemy.Board.size(); i++)
		{
			if (enemy.Board[i].CurrentHP < enemy.Board[i].HP)
			{
				cout << enemy.Board[i].Name;
			}
		}
		cout << endl << endl;
		cout << "������ �ϰ� : ���ظ� ���� �ϼ��� �ϳ��� óġ �� �� �ֽ��ϴ�. ���� ī�� �� óġ�� �ϼ����� �����ϼ���(���� ��ȣ�� ����)" << endl << endl;
		int cardToKill;
		cin >> cardToKill;
		if (cardToKill <= enemy.Board.size())
		{
			enemy.Board[cardToKill - 1].EraseMEE();
		}
		break;
	case 7: case 8: // �ַ� �ٴٻ�ɲ�: 1/1�� �ַ� ������ �� ���� ��ȯ
		cout << "�ַ� �ٴٻ�ɲ� : 1/1�� �ַ� ������ �� ���� ��ȯ" << endl << endl;
		_sleep(500);
		(*MyPlayer).Board.push_back(Card("�ַ� ������", 0, Type::Servant, 1, 1, false, false, 31));
		break;
	case 11: case 12: // ������ �ϰ�: �� ������ �̹� �Ͽ� ���ݷ� +4
		cout << "������ �ϰ� : �� �������� �̹� �ϸ� ���ݷ� +4�� �ο��մϴ�." << endl << endl;
		_sleep(500);
		MyPlayer->BuffedAttackPower += 4;
		break;
	case 13: case 14: // �̱۰Ÿ��� ���ﵵ��: 3/2�� ���� ����
		cout << "�̱۰Ÿ��� ���ﵵ�� : 3/2�� ���⸦ �����մϴ�." << endl << endl;
		_sleep(500);
		MyPlayer->AttackPower = 3;
		MyPlayer->AttackCount += 2;
		break;
	case 15: case 16: // ���õ��� ��ɲ�: 1/1�� ����� �� ���� ��ȯ
		cout << "���õ��� ��ɲ� : 1/1�� ������� �� ���� ��ȯ�մϴ�." << endl << endl;
		_sleep(500);
		(*MyPlayer).Board.push_back(Card("�����", 0, Type::Servant, 1, 1, false, false, 32));
		break;
	case 19: case 20: // ����뷡 ��ɰ�: �� ���� �ϼ��ε��� ���ݷ� +1
		cout << "����뷡 ��ɰ� : �� ���� �ϼ��ε鿡�� ���ݷ� +1�� �ο��մϴ�." << endl << endl;
		_sleep(500);
		for (int i = 0; i < Place->size(); i++)
		{
			if ((*Place)[i].CanDash)
			{
				(*Place)[i].CurrentAttackPower += 1;
			}
		}
		break;
	case 21: case 22: // ��� �� �����: 2/1�� ���� ��� �� �� ���� ��ȯ
		cout << "��� �� ����� : 2/1�� ���� ��� �� �� ������ ��ȯ�մϴ�." << endl << endl;
		_sleep(500);
		(*MyPlayer).Board.push_back(Card("���� ��� ��", 0, Type::Servant, 2, 1, false, false, 33));
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
		// ����ٽ� ������: ���ظ� ���� �� ���� ���ݷ� +3
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