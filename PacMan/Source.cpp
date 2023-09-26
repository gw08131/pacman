#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#pragma comment(lib, "Winmm.lib") //winmm.lib 추가
#include <vector>


#define MAX_COL_SIZE 25
#define MAX_ROW_SIZE 19 
int arr[MAX_COL_SIZE][MAX_ROW_SIZE] =
{
   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
   {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
   {1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
   {1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1},
   {1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1},
   {1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1},
   {1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1},
   {1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1},
   {1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
   {1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1},
   {1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1},
   {1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1},
   {1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1},
   {1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1},
   {1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1},
   {1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1},
   {1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
   {1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
   {1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1},
   {1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1},
   {1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1},
   {1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1},
   {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int Min = 100000;
int score = 0;
int x = 2;
int y = 1;

bool item_visited[MAX_COL_SIZE][MAX_ROW_SIZE] = { false };
int enemy_visited[MAX_COL_SIZE][MAX_ROW_SIZE] = { 0 };
int answer[MAX_COL_SIZE][MAX_ROW_SIZE] = { 0 };
void dfs(int temp_enemyX, int temp_enemyY, int count)
{

	if (temp_enemyX == y && temp_enemyY == x / 2)
	{
		if (count < Min)
		{
			Min = count;
			memcpy(answer, enemy_visited, sizeof(int) * MAX_COL_SIZE * MAX_ROW_SIZE);
		}
		return;
	}
	if (temp_enemyX + 1 < MAX_COL_SIZE && arr[temp_enemyX + 1][temp_enemyY] == 0 && enemy_visited[temp_enemyX + 1][temp_enemyY] != true)
	{
		enemy_visited[temp_enemyX + 1][temp_enemyY] = 1;
		dfs(temp_enemyX + 1, temp_enemyY, count + 1);
		enemy_visited[temp_enemyX + 1][temp_enemyY] = 0;

	}
	if (temp_enemyY - 1 >= 0 && arr[temp_enemyX][temp_enemyY - 1] == 0 && enemy_visited[temp_enemyX][temp_enemyY - 1] != true)
	{
		enemy_visited[temp_enemyX][temp_enemyY - 1] = 1;
		dfs(temp_enemyX, temp_enemyY - 1, count + 1);
		enemy_visited[temp_enemyX][temp_enemyY - 1] = 0;
	}
	if (temp_enemyX - 1 >= 0 && arr[temp_enemyX - 1][temp_enemyY] == 0 && enemy_visited[temp_enemyX - 1][temp_enemyY] != true)
	{
		enemy_visited[temp_enemyX - 1][temp_enemyY] = 1;
		dfs(temp_enemyX - 1, temp_enemyY, count + 1);
		enemy_visited[temp_enemyX - 1][temp_enemyY] = 0;
	}
	if (temp_enemyY + 1 < MAX_ROW_SIZE && arr[temp_enemyX][temp_enemyY + 1] == 0 && enemy_visited[temp_enemyX][temp_enemyY + 1] != true)
	{
		enemy_visited[temp_enemyX][temp_enemyY + 1] = 1;
		dfs(temp_enemyX, temp_enemyY + 1, count + 1);
		enemy_visited[temp_enemyX][temp_enemyY + 1] = 0;

	}
	return;

}
int main()
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = false;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);

	printf("\n\n");
	printf("    #####    #      ###    #        #      #     #       #	\n");
	printf("    #   #   # #    #       # #     # #    # #    # #     #	\n");
	printf("    #####  #####   #       #  #   #  #   #####   #   #   #	\n");
	printf("    #      #   #   #       #   # #   #   #   #   #     # #	\n");
	printf("    #      #   #    ###    #    #    #   #   #   #       #	\n");
	gotoxy(23, 13);
	printf("Game Start\n");
	gotoxy(18, 13);
	printf(">\n");
	gotoxy(23, 15);
	printf("Game End\n");
	bool gameStart = false;
	while (!gameStart)
	{
		if (kbhit())
		{
			char szChoice = getch();
			int direct = 0;
			switch (szChoice)
			{
			case '\r':
				gameStart = true;
				break;
			case 'w':
				gotoxy(18, 15);
				printf(" \n");
				gotoxy(18, 13);
				printf(">\n");
				break;
			case 's':
				gotoxy(18, 13);
				printf(" \n");
				gotoxy(18, 15);
				printf(">\n");
			}
		}
	
		if (gameStart)
		{
			system("cls");
			for (int i = 0; i < MAX_COL_SIZE; i++)
			{
				for (int j = 0; j < MAX_ROW_SIZE; j++)
				{
					if (arr[i][j] == 1)
					{
						printf("■"); // 미로 벽 출력
					}
					else
					{
						printf("º");
					}
				}
				printf("\n");
			}

			for (int i = 0; i < MAX_COL_SIZE; i++)
			{
				for (int j = 0; j < MAX_ROW_SIZE; j++)
				{
					if (arr[i][j] != 1)
						item_visited[i][j] = true; // 아이템의 위치 찾기
				}
			}
			std::vector<std::pair<int, int>> enemyList;
			enemyList.push_back({ 34,10 });
			enemyList.push_back({ 8,19 });

			gotoxy(x, y);
			printf("▷");
			for (auto enemy : enemyList)
			{
				int enemyX = enemy.first;
				int enemyY = enemy.second;
				gotoxy(enemyX, enemyY);
				item_visited[enemyX][enemyY] = false;
			}

			printf("▲");
			unsigned __int64 prevTime = GetTickCount();
			bool canPlay = true;
			while (canPlay)
			{
				int tempX = x;
				int tempY = y;
				char szChoice = 0;
				if (kbhit())
				{
					szChoice = getch();
					int direct = 0;
					switch (szChoice)
					{
					case 'w':
						tempY--;
						direct = 1;
						break;
					case 'a':
						tempX -= 2;
						direct = 2;
						break;
					case 's':
						tempY++;
						direct = 3;
						break;
					case 'd':
						tempX += 2;
						direct = 4;
						break;
					}
					if (arr[tempY][tempX / 2] != 1)
					{
						gotoxy(x, y);
						printf("  ");
						if (item_visited[tempY][tempX / 2] == true)
							score++;
						item_visited[tempY][tempX / 2] = false;

						x = tempX;
						y = tempY;
						gotoxy(x, y);
						if (direct == 1)
							printf("△");
						else if (direct == 2)
							printf("◁");
						else if (direct == 3)
							printf("▽");
						else if (direct == 4)
							printf("▷");
						gotoxy(23, 25);
						printf("\n   Current Score : %d\n", score);

					}

				}

				unsigned __int64 curTime = GetTickCount();

				if (curTime - prevTime > 400)	//0.5초마다
				{

					for (int k = 0; k < enemyList.size(); k++)
					{
						int enemyX = enemyList[k].first;
						int enemyY = enemyList[k].second;;
						for (int i = 0; i < MAX_COL_SIZE; i++)
						{
							for (int j = 0; j < MAX_ROW_SIZE; j++)
							{
								if (arr[i][j] != 1)
								{
									answer[i][j] = 0;
									enemy_visited[i][j] = 0;
								}

							}
						}
						Min = 100000;
						dfs(enemyY, enemyX / 2, 0);
						if (answer[enemyList[k].second - 1][enemyList[k].first / 2] == 1)
						{
							gotoxy(enemyList[k].first, enemyList[k].second);
							printf("  ");
							enemyList[k].second = enemyList[k].second - 1;
							gotoxy(enemyList[k].first, enemyList[k].second);
							printf("▲");
							prevTime = curTime;
							item_visited[enemyList[k].second][enemyList[k].first / 2] = false;
						}

						else if (answer[enemyList[k].second + 1][enemyList[k].first / 2] == 1)
						{
							gotoxy(enemyList[k].first, enemyList[k].second);
							printf("  ");

							gotoxy(enemyList[k].first, ++enemyList[k].second);
							printf("▼");
							prevTime = curTime;
							item_visited[enemyList[k].second][enemyList[k].first / 2] = false;
						}
						else if (answer[enemyList[k].second][enemyList[k].first / 2 + 1] == 1)
						{
							gotoxy(enemyList[k].first, enemyList[k].second);
							printf("  ");
							enemyList[k].first += 2;
							gotoxy(enemyList[k].first, enemyList[k].second);
							printf("▶");
							prevTime = curTime;
							item_visited[enemyList[k].second][enemyList[k].first / 2] = false;
						}
						else if (answer[enemyList[k].second][enemyList[k].first / 2 - 1] == 1)
						{
							gotoxy(enemyList[k].first, enemyList[k].second);
							printf("  ");
							enemyList[k].first -= 2;
							gotoxy(enemyList[k].first, enemyList[k].second);
							printf("◀");
							prevTime = curTime;
							item_visited[enemyList[k].second][enemyList[k].first / 2] = false;
						}
						if (enemyList[k].first == x && enemyList[k].second == y)
						{
							canPlay = false;
							break;
						}
					}
				
				}
				// 1,1 = 2,1
			// 1,2 = 4,1
			// 1,3 = 6,1
			//2,1 = 2,2
			// 2, 2 = 4, 2

			}
			gotoxy(23, 28);
			printf("\n   Game End!!\n");
		}
	}

	return 0;
}

