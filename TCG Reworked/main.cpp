#include "Player.h"

int Turn = 0;
bool IsGameOver = false;

Player playerX = Player("Player X");
Player playerY = Player("Player Y");

vector<Card> OriginalDeck;

void Setup();
bool Update();
void ShowHandandBoard(Player& player, Player& enemy);

int main()
{
	Setup();

	do {
		IsGameOver = Update();
	} while (!IsGameOver);

	for (int i = 0; i < 1000; i++)
	{
		cout << "Game over" << endl;
		if (playerX.HP <= 0)
		{
			cout << "player Y �¸�" << endl;
		}
		else if (playerY.HP <= 0)
		{
			cout << "player X �¸�" << endl;
		}
		else
		{
			cout << "����???" << endl;
		}
		_sleep(1000);
	}

	return 0;
}

void Setup()
{
	Turn = 1;

	// ��ü ī�� �� �ʱ�ȭ
	OriginalDeck.push_back(Card("Empty", 0, Type::General, 0, 0, 0, 0, 0));
	OriginalDeck.push_back(Card("����", 3, Type::Spell, 0, 0, 0, 0, 1));
	OriginalDeck.push_back(Card("����", 3, Type::Spell, 0, 0, 0, 0, 2));
	OriginalDeck.push_back(Card("�ַ� ��Ż��", 1, Type::Servant, 2, 1, 0, 0, 3));
	OriginalDeck.push_back(Card("�ַ� ��Ż��", 1, Type::Servant, 2, 1, 0, 0, 4));
	OriginalDeck.push_back(Card("������ �ϰ�", 1, Type::Spell, 0, 0, 0, 0, 5));
	OriginalDeck.push_back(Card("������ �ϰ�", 1, Type::Spell, 0, 0, 0, 0, 6));
	OriginalDeck.push_back(Card("�ַ� �ٴٻ�ɲ�", 2, Type::Servant, 2, 1, 0, 0, 7));
	OriginalDeck.push_back(Card("�ַ� �ٴٻ�ɲ�", 2, Type::Servant, 2, 1, 0, 0, 8));
	OriginalDeck.push_back(Card("�������� �׷�Ʈ", 2, Type::Servant, 2, 2, 0, 1, 9));
	OriginalDeck.push_back(Card("�������� �׷�Ʈ", 2, Type::Servant, 2, 2, 0, 1, 10));
	OriginalDeck.push_back(Card("������ �ϰ�", 2, Type::Spell, 0, 0, 0, 0, 11));
	OriginalDeck.push_back(Card("������ �ϰ�", 2, Type::Spell, 0, 0, 0, 0, 12));
	OriginalDeck.push_back(Card("�̱۰Ÿ��� ���� ����", 2, Type::Spell, 0, 0, 0, 0, 13));
	OriginalDeck.push_back(Card("�̱۰Ÿ��� ���� ����", 2, Type::Spell, 0, 0, 0, 0, 14));
	OriginalDeck.push_back(Card("���õ��� ��ɲ�", 3, Type::Servant, 2, 3, 0, 0, 15));
	OriginalDeck.push_back(Card("���õ��� ��ɲ�", 3, Type::Servant, 2, 3, 0, 0, 16));
	OriginalDeck.push_back(Card("���� ���", 3, Type::Servant, 3, 1, 1, 0, 17));
	OriginalDeck.push_back(Card("���� ���", 3, Type::Servant, 3, 1, 1, 0, 18));
	OriginalDeck.push_back(Card("���� �뷡 ��ɰ�", 3, Type::Servant, 2, 3, 0, 0, 19));
	OriginalDeck.push_back(Card("���� �뷡 ��ɰ�", 3, Type::Servant, 2, 3, 0, 0, 20));
	OriginalDeck.push_back(Card("���� �����", 4, Type::Servant, 2, 4, 0, 0, 21));
	OriginalDeck.push_back(Card("���� �����", 4, Type::Servant, 2, 4, 0, 0, 22));
	OriginalDeck.push_back(Card("���� ���д밡", 4, Type::Servant, 3, 5, 0, 1, 23));
	OriginalDeck.push_back(Card("���� ���д밡", 4, Type::Servant, 3, 5, 0, 1, 24));
	OriginalDeck.push_back(Card("����ٽ� ������", 5, Type::Servant, 2, 7, 0, 0, 25));
	OriginalDeck.push_back(Card("����ٽ� ������", 5, Type::Servant, 2, 7, 0, 0, 26));
	OriginalDeck.push_back(Card("���ָ� �����", 6, Type::Servant, 6, 7, 0, 0, 27));
	OriginalDeck.push_back(Card("���ָ� �����", 6, Type::Servant, 6, 7, 0, 0, 28));
	OriginalDeck.push_back(Card("�������� ����", 6, Type::Servant, 6, 5, 0, 1, 29));
	OriginalDeck.push_back(Card("�������� ����", 6, Type::Servant, 6, 5, 0, 1, 30));

	// ī�� �й�
	playerX.Deck = OriginalDeck;
	for (int i = 0; i < playerX.Deck.size(); i++)
	{
		playerX.Deck[i].MyPlayer = &playerX;
	}

	playerY.Deck = OriginalDeck;
	for (int i = 0; i < playerY.Deck.size(); i++)
	{
		playerY.Deck[i].MyPlayer = &playerY;
	}

	// ī�� ����
	playerX.ShuffleDeck();
	playerY.ShuffleDeck();

	// ī�� ���� Ȯ���� ���� �ӽ� �ڵ�------------
	/*
	cout << "\n\n����ī��" << endl;
	for (int i = 0; i < OriginalDeck.size(); i++)
	{
		cout << "\n\t" << OriginalDeck[i].Name;
	}
	cout << endl << endl;
	cout << "\nXī��" << endl;
	for (int i = 0; i < playerX.Deck.size(); i++)
	{
		cout << "\n\t" << playerX.Deck[i].Name;
	}
	cout << endl << endl;
	cout << "\nYī��" << endl;
	for (int i = 0; i < playerY.Deck.size(); i++)
	{
		cout << "\n\t" << playerY.Deck[i].Name;
	}
	cout << endl << endl;
	*/
	//-----------------------------------------

	// ���� 2�� �̱�
	for (int i = 0; i < 2; i++)
	{
		playerX.DrawCard();
	}
	// �İ� 4�� �̱�
	for (int i = 0; i < 4; i++)
	{
		playerY.DrawCard();
	}
}

// ���ӿ����Ǹ�(�� �� �ϳ��� ü���� 0 ���ϰ� �Ǹ�) true ��ȯ
// ȿ���� �ߵ��� ������ ü�� Ȯ��
bool Update()
{

	// �ڽ�Ʈ ����
	if (Turn >= 10)
	{
		playerX.MaxCostTurn = 10;
		playerX.NowCost = playerX.MaxCostTurn;
		playerY.MaxCostTurn = 10;
		playerY.NowCost = playerY.MaxCostTurn;
	}
	else {
		playerX.MaxCostTurn = Turn;
		playerX.NowCost = playerX.MaxCostTurn;
		playerY.MaxCostTurn = Turn;
		playerY.NowCost = playerY.MaxCostTurn;
	}

	// ī�� Ȱ��ȭ
	for (int i = 0; i < playerX.Board.size(); i++)
	{
		playerX.Board[i].IsEnabled = true;
	}
	for (int i = 0; i < playerY.Board.size(); i++)
	{
		playerY.Board[i].IsEnabled = true;
	}

	// �÷��̾� X ��
	bool resume = true;

	playerX.DrawCard();
	while (resume)
	{
		system("cls");
		ShowHandandBoard(playerX, playerY);
		resume = playerX.PlayTurn(playerY);
	}
	playerX.BuffedAttackPower = 0;
	_sleep(250);
	system("cls");
	playerY.DrawCard();

	// �÷��̾� Y ��
	resume = true;

	while (resume)
	{
		system("cls");
		ShowHandandBoard(playerY, playerX);
		resume = playerY.PlayTurn(playerX);
	}
	_sleep(250);
	system("cls");

	// ���� ����Ǵ� ȿ�� �ߵ�(���� ī�尡 ���� �� ��)

	if (playerX.HP <= 0 || playerY.HP <= 0)
	{
		return true;
	}

	Turn++;
	return false;
}

// �ڽ��� �տ� �ִ� ī��� ���忡 �ִ� ī�� �����ֱ�
void ShowHandandBoard(Player& player, Player& enemy)
{
	cout << player.Name << " �� " << Turn << "��° ��" << endl << endl;
	cout << player.Name << " �� [HP : " << player.HP << "] [�ڽ�Ʈ : " << player.NowCost << " / " << player.MaxCostTurn << "]\n\n";

	cout << "                                     " << enemy.HP << "\n";
	cout << "====================================����====================================" << endl << endl;
	// ��� ����
	if (enemy.Board.empty())
	{
		cout << "\t\t\t\t----����----";
	}
	else
	{
		for (int i = 0; i < enemy.Board.size(); i++)
		{
			cout << enemy.Board[i].Name << "(" << enemy.Board[i].CurrentAttackPower << "/" << enemy.Board[i].CurrentHP << ")\t";
		}
	}
	cout << endl << endl;
	// �� ����
	if (player.Board.empty())
	{
		cout << "\t\t\t\t----����----";
	}
	else
	{
		for (int i = 0; i < player.Board.size(); i++)
		{
			cout << player.Board[i].Name << "(" << player.Board[i].CurrentAttackPower << "/" << player.Board[i].CurrentHP << ")\t";
		}
	}
	cout << endl << endl;
	cout << "====================================����====================================" << endl << endl;

	cout << "\n";

	cout << "-------------------------------------��-------------------------------------" << endl << endl;
	if (player.Hand.empty())
	{
		cout << "\t\t\t\t----����----";
	}
	for (int i = 0; i < player.Hand.size(); i++)
	{
		cout << player.Hand[i].Name << " : " << player.Hand[i].Cost << "\t";
	}
	cout << endl << endl;
	cout << "-------------------------------------��-------------------------------------" << endl << endl;

	cout << endl << endl;
}