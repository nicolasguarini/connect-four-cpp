/*--INCLUDES--*/
//#include "stdafx.h"
#include "pch.h"
#include <iostream>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <time.h>
using namespace std;

/*---CONSTANTS--*/
#define LEN 20 //maximum length of the name
#define R 7 //rows of the playing field
#define C 7 //colums of the playing field

/*---PROTOTYPES---*/
void menu();
void game_user_vs_user();
void game_user_vs_cpu();
void generate_playing_field(char m[][C]);
void display_playing_field(char m[][C]);
void insert_token(char m[][C], int c, bool players, char name_player_1[], char name_player_2[]);
void check_win (char m[][C], bool players, bool *flag_win, char name_player_1[], char name_player_2[]);
void check_full_column(char m[][C], int c);
void selector(unsigned short color);
void check_playing_field(char m[][C], int i, int j, int player_code, bool *flag_win, char name_player_1[], char name_player_2[]);
void insert_token_animation(char m[][C], int i, int c, bool players, char name_player_1[], char name_player_2[]);
void settings();

int main()
{
	menu();
	return 0;
}

void menu()
{
	int user_choice;
	do {
		system("cls");
		printf("1-User VS User\n");
		printf("2-User VS CPU\n");
		printf("3-Settings\n");
		printf("0-Esci\n");
		cin >> user_choice;

		switch (user_choice)
		{
		case 1:
			game_user_vs_user();
			break;
		case 2:
			game_user_vs_cpu();
			break;
		case 3:
			printf("This section is not developed yet");
			system("pause");
			break;
		case 0:
			return;
		default:
			break;
		}
	} while (user_choice != 0);
}

void settings()
{
	system("cls");
	printf("1-Background Settings\n");
	printf("2-Colors Settings ");
}

void game_user_vs_user()
{
	char name_player_1[LEN + 1];
	char name_player_2[LEN + 1];

	bool flag_win = false;

	system("cls");
	char m[R][C]; //playing field (m stands for matrix)
	int c; //column choosen
	bool players = false; //false = player 1; true = player 2

	//Inserting player names
	printf("Insert the name of the player 1: ");
	cin >> name_player_1;
	printf("Insert the name of the player 2: ");
	cin >> name_player_2;
	printf("Names saved correctly!!\n");
	Sleep(1000);

	generate_playing_field(m);

	while(true) {
		system("cls");
		if (players == false)
			printf("+--TURN OF %s--+\n", name_player_1);
		else
			printf("+--TURN OF %s--+\n", name_player_2);

		printf("Insert the row where you want to insert the token: \n");

		display_playing_field(m);

		do {
			cin >> c;
		} while ((c > R || c < 1));
		c -= 1;
		insert_token(m, c, players, name_player_1, name_player_2);

		check_win(m, players, &flag_win, name_player_1, name_player_2);

		if (flag_win == true)
			return;
		players = !players;
	}

}

void check_full_column(char m[][C], int c)
{
	bool flag = true;
	for (int i = R - 1; i >= 0; i--)
	{
		if (m[i][c] == 127) {
			flag = false;
			break;
		}
	}

	if (flag == true) {
		printf("This column is full!!!\n");
		system("pause");
	}
}

void insert_token(char m[][C], int c, bool players, char name_player_1[], char name_player_2[])
{
	for (int i = R - 1; i >= 0; i--)
	{
		if (m[i][c] == 127) {
			if (players == false)
			{
				insert_token_animation(m, i, c, players, name_player_1, name_player_2);
				m[i][c] = 1;
			}
			else {
				insert_token_animation(m, i, c, players, name_player_1, name_player_2);
				m[i][c] = 2;
			}
			break;
		}
	}
	
	check_full_column(m, c);
}

void insert_token_animation(char m[][C], int i, int c, bool players, char name_player_1[], char name_player_2[])
{
	char player_code;
	if (players == false)
		player_code = 1;
	else
		player_code = 2;


	for (int j = 0; j <= i; j++)
	{
		m[j][c] = player_code;
		system("cls");
		if (players == false)
			printf("+--TURN OF %s--+\n", name_player_1);
		else
			printf("+--TURN OF %s--+\n", name_player_2);

		display_playing_field(m);
		if (j != i)
			m[j][c] = 127;

		Sleep(150);
	}

}

void check_win(char m[][C], bool players, bool *flag_win, char name_player_1[], char name_player_2[])
{
	if (*flag_win == true)
		return;

	for (int i = R - 1; i >= 0; i--) {
		for (int j = C - 1; j >= 0; j--)
		{
			if (players == false)
				if (m[i][j] == 1)
					check_playing_field(m, i, j, 1, flag_win, name_player_1, name_player_2);
			if (players == true)
				if (m[i][j] == 2)
					check_playing_field(m, i, j, 2, flag_win, name_player_1, name_player_2);
		}
	}
}

void check_playing_field(char m[][C], int i, int j, int player_code, bool *flag_win, char name_player_1[], char name_player_2[])
{
	int cont_up = 0;
	int cont_down = 0;
	int cont_right = 0;
	int cont_left = 0;
	int cont_up_right = 0;
	int cont_up_left = 0;
	int cont_down_right = 0;
	int cont_down_left = 0;

	//case up
	if (m[i + 1][j] == player_code)
		cont_up++;
	if (m[i + 2][j] == player_code)
		cont_up++;
	if (m[i + 3][j] == player_code)
		cont_up++;

	//case down
	if (m[i - 1][j] == player_code)
		cont_down++;
	if (m[i - 2][j] == player_code)
		cont_down++;
	if (m[i - 3][j] == player_code)
		cont_down++;

	//case right
	if (m[i][j + 1] == player_code)
		cont_right++;
	if (m[i][j + 2] == player_code)
		cont_right++;
	if (m[i][j + 3] == player_code)
		cont_right++;

	//case left
	if (m[i][j - 1] == player_code)
		cont_left++;
	if (m[i][j - 2] == player_code)
		cont_left++;
	if (m[i][j - 3] == player_code)
		cont_left++;

	//case up right
	if (m[i - 1][j + 1] == player_code)
		cont_up_right++;
	if (m[i - 2][j + 2] == player_code)
		cont_up_right++;
	if (m[i - 3][j + 3] == player_code)
		cont_up_right++;

	//case up left
	if (m[i - 1][j - 1] == player_code)
		cont_up_left++;
	if (m[i - 2][j - 2] == player_code)
		cont_up_left++;
	if (m[i - 3][j - 3] == player_code)
		cont_up_left++;

	//case down left
	if (m[i + 1][j - 1] == player_code)
		cont_down_left++;
	if (m[i + 2][j - 2] == player_code)
		cont_down_left++;
	if (m[i + 3][j - 3] == player_code)
		cont_down_left++;

	//case down right
	if (m[i + 1][j + 1] == player_code)
		cont_down_right++;
	if (m[i + 2][j + 2] == player_code)
		cont_down_right++;
	if (m[i + 3][j + 3] == player_code)
		cont_down_right++;

	if (cont_up >= 3 || cont_down >= 3 || cont_right >= 3 || cont_left >= 3 || cont_up_right >= 3 || cont_up_left >= 3 || cont_down_left >= 3 || cont_down_right >= 3)
	{
		if(player_code == 1)
			printf("WOW, %s, YOU WON!!!\n", name_player_1);
		else
			printf("WOW, %s, YOU WON!!!\n", name_player_2);

		system("pause");
		*flag_win = true;
		return;
	}
}

void generate_playing_field(char m[][C])
{
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			m[i][j] = 127;
}

void display_playing_field(char m[][C])
{
	int red = 4, cyan = 2, white = 7;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (m[i][j] == 1)
				selector(red);
			else
				if (m[i][j] == 2)
					selector(cyan);
				else
					selector(white);
			printf("%c ", m[i][j]);
		}
		printf("\n");
	}
	cout << endl;
	selector(white);
	for (int i = 0; i < R; i++)
		printf("%d ", i + 1);
	printf("\n");
}

void game_user_vs_cpu() //for informations about the code see "game_user_vs_user()" function
{
	srand(time(NULL));
	char name_player_1[LEN + 1];
	char name_player_2[LEN + 1];

	bool flag_win = false;

	system("cls");
	char m[R][C];
	int c;
	bool players = false;

	printf("Insert the name of the player 1: ");
	cin >> name_player_1;
	printf("Insert the name of the CPU: ");
	cin >> name_player_2;
	printf("Names saved correctly!!\n");
	Sleep(1000);

	generate_playing_field(m);

	while(true) {
		system("cls");
		if (players == false)
			printf("+--TURN OF %s--+\n", name_player_1);
		else
			printf("+--TURN OF %s--+\n", name_player_2);

		if (players == false)
		{
			printf("Insert the row where you want to insert the token: \n");
			display_playing_field(m);

			do {
				cin >> c;
			} while ((c > R || c < 1));
			c -= 1;

			insert_token(m, c, players, name_player_1, name_player_2);
		}
		else
		{
			printf("%s is thinking...\n", name_player_2);
			display_playing_field(m);
			Sleep(2000);
			c = 1 + rand() % 7;
			insert_token(m, c, players, name_player_1, name_player_2);
		}

		check_win(m, players, &flag_win, name_player_1, name_player_2);

		if (flag_win == true) {
			return;
		}
		players = !players;
	}
}

void selector(unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

