#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int no_of_players;
struct Player
{
    char name[21];
    char symbol;
    int amount;
};
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}
void TicTacToe_Board(char Display[4][4], int amount)
{
    system("cls");
    printf("Number of chances left = %d\n\n", amount);
    printf(" %c | %c | %c\n", Display[0][0], Display[0][1], Display[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", Display[1][0], Display[1][1], Display[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c", Display[2][0], Display[2][1], Display[2][2]);
}
int TicTacToe_Game(char Display[4][4], struct Player P1, struct Player P2, int opp1, int opp2)
{
    int i, j, side = 0;

    system("cls");
    printf("Player %d, %s will use '%c' symbol\nPlayer %d, %s will use '%c' symbol\n", opp1, P1.name, P1.symbol, opp2, P2.name, P2.symbol);
    system("pause");
    printf("\nThe Game between\nPlayer %s & Player %s\nhas started!!!!!\n\n", P1.name, P2.name);
    system("pause");

    int position, playerCheck;

    while (!(P1.amount == 0 && P2.amount == 0))
    {
        if (P1.amount != 0)
        {
            do
            {
                do
                {
                    TicTacToe_Board(Display, P1.amount);
                    printf("\n\nPlayer %s's turn (%c):\nEnter your position = ", P1.name, P1.symbol);
                    scanf("%d", &position);
                } while (!(position >= 1 && position <= 9));
            } while (Display[(position - 1) / 3][(position - 1) % 3] == P1.symbol || Display[(position - 1) / 3][(position - 1) % 3] == P2.symbol);
            Display[(position - 1) / 3][(position - 1) % 3] = P1.symbol;
            P1.amount--;
            TicTacToe_Board(Display, P1.amount);
            delay(1000);

            playerCheck = (Display[0][0] == P1.symbol && Display[0][1] == P1.symbol && Display[0][2] == P1.symbol) || (Display[1][0] == P1.symbol && Display[1][1] == P1.symbol && Display[1][2] == P1.symbol) || (Display[2][0] == P1.symbol && Display[2][1] == P1.symbol && Display[2][2] == P1.symbol) || (Display[0][0] == P1.symbol && Display[1][0] == P1.symbol && Display[2][0] == P1.symbol) || (Display[0][1] == P1.symbol && Display[1][1] == P1.symbol && Display[2][1] == P1.symbol) || (Display[0][2] == P1.symbol && Display[1][2] == P1.symbol && Display[2][2] == P1.symbol) || (Display[0][0] == P1.symbol && Display[1][1] == P1.symbol && Display[2][2] == P1.symbol) || (Display[2][0] == P1.symbol && Display[1][1] == P1.symbol && Display[0][2] == P1.symbol);
            if (playerCheck)
            {
                printf("\n\nPlayer %s won this match\n\n", P1.name);
                side++;
                if (!(P1.amount == 0 && P2.amount == 0))
                    printf("Time for next match.....\n");
                system("pause");
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                        Display[i][j] = (char)(3 * i + j + 49);
                }
                continue;
            }
            if (!playerCheck && Display[0][0] != '1' && Display[0][1] != '2' && Display[0][2] != '3' && Display[1][0] != '4' && Display[1][1] != '5' && Display[1][2] != '6' && Display[2][0] != '7' && Display[2][1] != '8' && Display[2][2] != '9')
            {
                printf("\n\nIt's a draw\n\n");
                if (!(P1.amount == 0 && P2.amount == 0))
                    printf("Time for next match.....\n");
                system("pause");
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                        Display[i][j] = (char)(3 * i + j + 49);
                }
                continue;
            }
        }
        if (P2.amount != 0)
        {
            do
            {
                do
                {
                    TicTacToe_Board(Display, P2.amount);
                    printf("\n\nPlayer %s's turn (%c):\nEnter your position = ", P2.name, P2.symbol);
                    scanf("%d", &position);
                } while (!(position >= 1 && position <= 9));
            } while (Display[(position - 1) / 3][(position - 1) % 3] == P1.symbol || Display[(position - 1) / 3][(position - 1) % 3] == P2.symbol);
            Display[(position - 1) / 3][(position - 1) % 3] = P2.symbol;
            P2.amount--;
            TicTacToe_Board(Display, P2.amount);
            delay(1000);

            playerCheck = (Display[0][0] == P2.symbol && Display[0][1] == P2.symbol && Display[0][2] == P2.symbol) || (Display[1][0] == P2.symbol && Display[1][1] == P2.symbol && Display[1][2] == P2.symbol) || (Display[2][0] == P2.symbol && Display[2][1] == P2.symbol && Display[2][2] == P2.symbol) || (Display[0][0] == P2.symbol && Display[1][0] == P2.symbol && Display[2][0] == P2.symbol) || (Display[0][1] == P2.symbol && Display[1][1] == P2.symbol && Display[2][1] == P2.symbol) || (Display[0][2] == P2.symbol && Display[1][2] == P2.symbol && Display[2][2] == P2.symbol) || (Display[0][0] == P2.symbol && Display[1][1] == P2.symbol && Display[2][2] == P2.symbol) || (Display[2][0] == P2.symbol && Display[1][1] == P2.symbol && Display[0][2] == P2.symbol);
            if (playerCheck)
            {
                printf("\n\nPlayer %s won this match\n\n", P2.name);
                side--;
                if (!(P1.amount == 0 && P2.amount == 0))
                    printf("Time for next match.....\n");
                system("pause");
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                        Display[i][j] = (char)(3 * i + j + 49);
                }
                continue;
            }
            if (!playerCheck && Display[0][0] != '1' && Display[0][1] != '2' && Display[0][2] != '3' && Display[1][0] != '4' && Display[1][1] != '5' && Display[1][2] != '6' && Display[2][0] != '7' && Display[2][1] != '8' && Display[2][2] != '9')
            {
                printf("\n\nIt's a draw\n\n");
                if (!(P1.amount == 0 && P2.amount == 0))
                    printf("Time for next match.....\n");
                system("pause");
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                        Display[i][j] = (char)(3 * i + j + 49);
                }
                continue;
            }
        }
    }
    printf("\n\nThe Game between Player %s & Player %s is Finished!!!!!\n", P1.name, P2.name);
    system("pause");

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            Display[i][j] = (char)(3 * i + j + 49);
    }
    return side;
}
int main()
{
    if (fopen("Players.dat", "rb") == NULL)
        return 0;
    FILE *fptr = fopen("Players.dat", "rb");
    fread(&no_of_players, sizeof(no_of_players), 1, fptr);
    struct Player P[no_of_players];
    fread(P, sizeof(P), 1, fptr);
    fclose(fptr);

    char Display[4][4] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    int i, j;

    int playerWins[no_of_players];
    for (i = 1; i <= no_of_players; i++)
        playerWins[i - 1] = 0;

    for (i = 1; i <= no_of_players; i++)
    {
        int side; // This is the winning side between two players
        for (j = i + 1; j <= no_of_players; j++)
        {
            side = TicTacToe_Game(Display, P[i - 1], P[j - 1], i, j);
            if (side > 0)
            {
                printf("\nPlayer %s won the Game\n", P[i - 1].name);
                playerWins[i - 1]++;
            }
            else if (side < 0)
            {
                printf("\nPlayer %s won the Game\n", P[j - 1].name);
                playerWins[j - 1]++;
            }
            else if (side == 0)
                printf("\nThe Game is a draw\n");
            system("pause");
        }
    }

    system("cls");
    printf("\t\t\t\t\t\tFinal Result!!!!!\n\n");
    for (i = 0; i < no_of_players; i++)
        printf("Player %d, %s has won %d Game(s)\n", i + 1, P[i].name, playerWins[i]);
    printf("\n");
    system("pause");
}