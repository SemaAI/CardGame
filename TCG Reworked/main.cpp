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
			cout << "player Y 승리" << endl;
		}
		else if (playerY.HP <= 0)
		{
			cout << "player X 승리" << endl;
		}
		else
		{
			cout << "뭐지???" << endl;
		}
		_sleep(1000);
	}

	return 0;
}

void Setup()
{
	Turn = 1;

	// 전체 카드 덱 초기화
	OriginalDeck.push_back(Card("Empty", 0, Type::General, 0, 0, 0, 0, 0));
	OriginalDeck.push_back(Card("돌진", 3, Type::Spell, 0, 0, 0, 0, 1));
	OriginalDeck.push_back(Card("돌진", 3, Type::Spell, 0, 0, 0, 0, 2));
	OriginalDeck.push_back(Card("멀록 약탈꾼", 1, Type::Servant, 2, 1, 0, 0, 3));
	OriginalDeck.push_back(Card("멀록 약탈꾼", 1, Type::Servant, 2, 1, 0, 0, 4));
	OriginalDeck.push_back(Card("마무리 일격", 1, Type::Spell, 0, 0, 0, 0, 5));
	OriginalDeck.push_back(Card("마무리 일격", 1, Type::Spell, 0, 0, 0, 0, 6));
	OriginalDeck.push_back(Card("멀록 바다사냥꾼", 2, Type::Servant, 2, 1, 0, 0, 7));
	OriginalDeck.push_back(Card("멀록 바다사냥꾼", 2, Type::Servant, 2, 1, 0, 0, 8));
	OriginalDeck.push_back(Card("서리늑대 그런트", 2, Type::Servant, 2, 2, 0, 1, 9));
	OriginalDeck.push_back(Card("서리늑대 그런트", 2, Type::Servant, 2, 2, 0, 1, 10));
	OriginalDeck.push_back(Card("영웅의 일격", 2, Type::Spell, 0, 0, 0, 0, 11));
	OriginalDeck.push_back(Card("영웅의 일격", 2, Type::Spell, 0, 0, 0, 0, 12));
	OriginalDeck.push_back(Card("이글거리는 전쟁 도끼", 2, Type::Spell, 0, 0, 0, 0, 13));
	OriginalDeck.push_back(Card("이글거리는 전쟁 도끼", 2, Type::Spell, 0, 0, 0, 0, 14));
	OriginalDeck.push_back(Card("가시덩굴 사냥꾼", 3, Type::Servant, 2, 3, 0, 0, 15));
	OriginalDeck.push_back(Card("가시덩굴 사냥꾼", 3, Type::Servant, 2, 3, 0, 0, 16));
	OriginalDeck.push_back(Card("늑대 기수", 3, Type::Servant, 3, 1, 1, 0, 17));
	OriginalDeck.push_back(Card("늑대 기수", 3, Type::Servant, 3, 1, 1, 0, 18));
	OriginalDeck.push_back(Card("전쟁 노래 사령관", 3, Type::Servant, 2, 3, 0, 0, 19));
	OriginalDeck.push_back(Card("전쟁 노래 사령관", 3, Type::Servant, 2, 3, 0, 0, 20));
	OriginalDeck.push_back(Card("기계용 정비사", 4, Type::Servant, 2, 4, 0, 0, 21));
	OriginalDeck.push_back(Card("기계용 정비사", 4, Type::Servant, 2, 4, 0, 0, 22));
	OriginalDeck.push_back(Card("센진 방패대가", 4, Type::Servant, 3, 5, 0, 1, 23));
	OriginalDeck.push_back(Card("센진 방패대가", 4, Type::Servant, 3, 5, 0, 1, 24));
	OriginalDeck.push_back(Card("구루바시 광전사", 5, Type::Servant, 2, 7, 0, 0, 25));
	OriginalDeck.push_back(Card("구루바시 광전사", 5, Type::Servant, 2, 7, 0, 0, 26));
	OriginalDeck.push_back(Card("돌주먹 오우거", 6, Type::Servant, 6, 7, 0, 0, 27));
	OriginalDeck.push_back(Card("돌주먹 오우거", 6, Type::Servant, 6, 7, 0, 0, 28));
	OriginalDeck.push_back(Card("투기장의 제왕", 6, Type::Servant, 6, 5, 0, 1, 29));
	OriginalDeck.push_back(Card("투기장의 제왕", 6, Type::Servant, 6, 5, 0, 1, 30));

	// 카드 분배
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

	// 카드 섞기
	playerX.ShuffleDeck();
	playerY.ShuffleDeck();

	// 카드 셔플 확인을 위한 임시 코드------------
	/*
	cout << "\n\n원래카드" << endl;
	for (int i = 0; i < OriginalDeck.size(); i++)
	{
		cout << "\n\t" << OriginalDeck[i].Name;
	}
	cout << endl << endl;
	cout << "\nX카드" << endl;
	for (int i = 0; i < playerX.Deck.size(); i++)
	{
		cout << "\n\t" << playerX.Deck[i].Name;
	}
	cout << endl << endl;
	cout << "\nY카드" << endl;
	for (int i = 0; i < playerY.Deck.size(); i++)
	{
		cout << "\n\t" << playerY.Deck[i].Name;
	}
	cout << endl << endl;
	*/
	//-----------------------------------------

	// 선공 2장 뽑기
	for (int i = 0; i < 2; i++)
	{
		playerX.DrawCard();
	}
	// 후공 4장 뽑기
	for (int i = 0; i < 4; i++)
	{
		playerY.DrawCard();
	}
}

// 게임오버되면(둘 중 하나라도 체력이 0 이하가 되면) true 반환
// 효과가 발동할 때마다 체력 확인
bool Update()
{

	// 코스트 충전
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

	// 카드 활성화
	for (int i = 0; i < playerX.Board.size(); i++)
	{
		playerX.Board[i].IsEnabled = true;
	}
	for (int i = 0; i < playerY.Board.size(); i++)
	{
		playerY.Board[i].IsEnabled = true;
	}

	// 플레이어 X 턴
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

	// 플레이어 Y 턴
	resume = true;

	while (resume)
	{
		system("cls");
		ShowHandandBoard(playerY, playerX);
		resume = playerY.PlayTurn(playerX);
	}
	_sleep(250);
	system("cls");

	// 공통 적용되는 효과 발동(남은 카드가 없을 때 등)

	if (playerX.HP <= 0 || playerY.HP <= 0)
	{
		return true;
	}

	Turn++;
	return false;
}

// 자신의 손에 있는 카드와 보드에 있는 카드 보여주기
void ShowHandandBoard(Player& player, Player& enemy)
{
	cout << player.Name << " 의 " << Turn << "번째 턴" << endl << endl;
	cout << player.Name << " 의 [HP : " << player.HP << "] [코스트 : " << player.NowCost << " / " << player.MaxCostTurn << "]\n\n";

	cout << "                                     " << enemy.HP << "\n";
	cout << "====================================보드====================================" << endl << endl;
	// 상대 보드
	if (enemy.Board.empty())
	{
		cout << "\t\t\t\t----없음----";
	}
	else
	{
		for (int i = 0; i < enemy.Board.size(); i++)
		{
			cout << enemy.Board[i].Name << "(" << enemy.Board[i].CurrentAttackPower << "/" << enemy.Board[i].CurrentHP << ")\t";
		}
	}
	cout << endl << endl;
	// 내 보드
	if (player.Board.empty())
	{
		cout << "\t\t\t\t----없음----";
	}
	else
	{
		for (int i = 0; i < player.Board.size(); i++)
		{
			cout << player.Board[i].Name << "(" << player.Board[i].CurrentAttackPower << "/" << player.Board[i].CurrentHP << ")\t";
		}
	}
	cout << endl << endl;
	cout << "====================================보드====================================" << endl << endl;

	cout << "\n";

	cout << "-------------------------------------손-------------------------------------" << endl << endl;
	if (player.Hand.empty())
	{
		cout << "\t\t\t\t----없음----";
	}
	for (int i = 0; i < player.Hand.size(); i++)
	{
		cout << player.Hand[i].Name << " : " << player.Hand[i].Cost << "\t";
	}
	cout << endl << endl;
	cout << "-------------------------------------손-------------------------------------" << endl << endl;

	cout << endl << endl;
}