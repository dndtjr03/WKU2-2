#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>

#define DINO_BOTTOM_Y 17
#define CACTUS_BOTTOM_Y 25
#define CACTUS_BOTTOM_X 45

void ClearDino(int dinoY);	//공룡 지우기
void ClearCactus(int cactusX);	//선인장 지우기

void Cursorview(char show);
void SetColor(unsigned short text);
void SetConsoleView();
void DrawDino(int dinoY);
void GotoXY(int x, int y);
void DrawCactus(int cactusX);
int IsCollision(const int  cactusX, const int dinoY);
int GetKeyDown();
void DrawGameOver(const int score);

// 색상
enum {
	BLACK,			// 0
	DARK_BLUE,		// 1
	DARK_GREEN,		// 2	
	DARK_SKYBLUE,	// 3
	DARK_RED,		// 4
	DARK_VOILET,	// 5
	DARK_YELLOW,	// 6
	GRAY,			// 7
	DARK_GRAY,		// 8
	BLUE,			// 9
	GREEN,			// 10
	SKYBLUE,		// 11
	RED,			// 12	
	VOILET,			// 13
	YELLOW,			// 14
	WHITE			// 15
};

int main()
{
	SetConsoleView();
	while (true)
	{
		// 게임 시작 시 초기화
		int isJumping = false;
		int isBottom = true;
		const int gravity = 3;

		int dinoY = DINO_BOTTOM_Y;
		int cactusX = CACTUS_BOTTOM_X;

		int score = 0;
		clock_t  start, curr;	// 점수 변수 초기화
		start = clock();		// 시작 시간 초기화

		while (true)
		{	// 게임 한 판에 대한 루프
			// 충돌체크 트리의 x값과 y값을 판단.
			if (IsCollision(cactusX, dinoY)) break;
			// space 키가 눌렸고, 바닥이 아닐 때 점프
			// space key ASCII : 32
			if (GetKeyDown() == ' ' && isBottom)
			{
				isJumping = true;
				isBottom = false;
			}

			// 점프 중이라면 Y를 감소, 점프가 끝났으면 Y를 증가.
			if(isJumping)
				dinoY -= gravity;
			else dinoY += gravity;
			// Y가 계속해서 증가하는걸 막기 위해 바닥을 지정.
			if (dinoY >= DINO_BOTTOM_Y)
			{
				dinoY = DINO_BOTTOM_Y;
				isBottom = true;
			}
			
			// 점프의 맨 위를 찍으면 점프가 끝난 상황.
			if (dinoY <= 3)
				isJumping = false;
			
			//선인장(장애물)이 왼쪽으로 (x음수) 가도록 하고
			// 선인장(장애물)이 위치가 왼쪽 끝으로 가면 다시 오른쪽 끝으로 소환.
			cactusX -= 2;
			if (cactusX <= 0)
				cactusX = CACTUS_BOTTOM_X;

			DrawDino(dinoY);		// 공룡 그리기
			DrawCactus(cactusX);	// 선인장 그리기

			curr = clock();		// 현재 시간 받아오기
			if (((curr - start) / CLOCKS_PER_SEC) >= 1)	// 1초가 넘었을 때
			{
				score++;			// 점수 증가
				start = clock();	// 시작 시간 초기화
			}

			Sleep(60);		// Game Speed 설정
			//system("cls");		// clear
			ClearDino(dinoY);
			ClearCactus(cactusX);

			SetColor(WHITE);
			/* 점수출력을 1초마다 해주는 것이 아니라 항상 출력해주면서,
			 1초가 지났을 때, ++ 해줍니다.*/
			/* 커서를 가운데 위쪽으로 옮긴다.콘솔창이 cols = 100이니까
			 2 * x 이므로 22정도 넣어줌.*/
			GotoXY(22, 0); printf("Score: %d ", score);		// 점수 출력
			GotoXY(20, 2); printf("점프 : space key");

		}

		// 게임 오버 메뉴
		DrawGameOver(score);
	}
}

// 콘솔 텍스트 색상 변경 함수
void SetColor(unsigned short text)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

// 커서 이동 함수
void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 키보드 입력 함수
int GetKeyDown()
{
	if (_kbhit() != 0) return _getch();
	return false;
}

// 충돌했으면 true, 아니면 false
int IsCollision(const int cactusX,const int dinoY) 
{
	// 트리의 X가 공룡의 몸체쪽에 있을 때,
	// 공룡의 높이가 충분하지 않다면 충돌로 처리.
	GotoXY(0, 0);
	printf("cactusX: %2d, dinoY: %2d", cactusX, dinoY);	//이런 식으로 적절한 x,y를 찾기
	if (cactusX <= 8 && dinoY >= 2 && dinoY > 12) return true;
	return false;
}

//선인장 그리는 함수
void DrawCactus(int cactusX)
{
	SetColor(GREEN);
	GotoXY(cactusX, CACTUS_BOTTOM_Y);
	printf("  $");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 1);
	printf("$ $  ");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 2);
	printf("$ $ $");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 3);
	printf("$$$$$");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 4);
	printf("  $  ");
}

void DrawDino(int dinoY)
{
	SetColor(SKYBLUE);
	GotoXY(0, dinoY);
	static int legFlag = true;
	printf("        $$$$$$$ \n");		// 8, 7, 1
	printf("       $$ $$$$$$\n");		// 7, 2, 1, 6
	printf("       $$$$$$$$$\n");		// 7, 9
	printf("$      $$$      \n");		// 1, 6, 3, 6
	printf("$$     $$$$$$$  \n");		// 2, 5, 7, 2
	printf("$$$   $$$$$     \n");		// 3, 3, 5, 5
	printf(" $$  $$$$$$$$$$ \n");		// 1, 2, 2, 10, 1
	printf(" $$");									// 1, 2
	SetColor(RED);	printf("원광대");
	SetColor(SKYBLUE);
	printf("$$$    \n");						// 3, 4
	printf("  $$$");								// 2, 3
	printf("컴소공");
	printf("$    \n");							// 1, 4
	printf("    $$$$$$$$    \n");		// 4, 8, 4
	printf("     $$$$$$     \n");		// 5, 6, 5
	if (legFlag)
	{
		printf("     $    $$$   \n");		// 5, 1, 4, 3, 3
		printf("     $$         ");			// 5, 2, 9
		legFlag = false;
	}
	else
	{
		printf("     $$$  $     \n");		// 5, 3, 2, 1, 5
		printf("          $$    ");			// 10, 2, 4
		legFlag = true;
	}
}

// 커서 on / off
void Cursorview(char show)
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show;		// 커서를 보일지 말지(0: 안보임, 0 이외: 보임)
	ConsoleCursor.dwSize = 1;		// 커서 크기 결정(1~100)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

// 콘솔창의 크기와 제목 지정 함수
void SetConsoleView()
{
	//Console창의 가로,세로 크기 지정
	system("mode con:cols = 120 lines = 30");
	// Console창의 제목창 표시
	system("title 창의실무프로젝트 구글 공룡 게임 [By. L.U.S}");
	// 커서 안 보이게...
	Cursorview(false);
}

// 충돌했을 때, 게임 오버
void DrawGameOver(const int score)
{
	// 화면을 청소함. cls : Clean Screen의 약자
	system("cls");
	SetColor(YELLOW);
	int x = 22, y = 8;
	GotoXY(x, y);

	printf("====================================");
	GotoXY(x, y + 1);
	printf("==========G A M E O V E R ==========");
	GotoXY(x, y + 2);
	printf("====================================");
	GotoXY(x, y + 5);
	printf("SCORE : %d",score);

	printf("\n\n\n\n\n\n\n\n\n");
	system("pause");
	system("cls");
}

void ClearDino(int dinoY)
{
	GotoXY(0, dinoY);
	for (int i = 0; i < 12; i++)
		printf("                \n");
	printf("                ");
}	

void ClearCactus(int cactusX)
{
	for (int i = 0; i < 5; i++)
	{
		GotoXY(cactusX, CACTUS_BOTTOM_Y + i);
		printf("     ");
	}
}