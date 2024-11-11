#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(char show) {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show;	// Ŀ���� ������ ���� ����(0: �Ⱥ���, �� ��: ����)
	ConsoleCursor.dwSize = 1;		// Ŀ�� ũ�� ����(1~100)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

int main(void)
{
	printf("Enter �Է� �� ���� : "); getchar();
	CursorView(0);	// Ŀ���� ������ �ʰ� ����
	srand((unsigned)time(NULL));
	while (1)
	{
		gotoxy((rand() % 300) / 2, rand() % 25);
		printf("*");
		Sleep(100);
	}
}