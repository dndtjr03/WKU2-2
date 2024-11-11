#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(char show) {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show;	// 커서를 보일지 말지 결정(0: 안보임, 그 외: 보임)
	ConsoleCursor.dwSize = 1;		// 커서 크기 결정(1~100)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

int main(void)
{
	printf("Enter 입력 시 시작 : "); getchar();
	CursorView(0);	// 커서를 보이지 않게 설정
	srand((unsigned)time(NULL));
	while (1)
	{
		gotoxy((rand() % 300) / 2, rand() % 25);
		printf("*");
		Sleep(100);
	}
}