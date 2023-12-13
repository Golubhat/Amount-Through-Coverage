#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}
#define SIZE 20
char CoverageBoard[SIZE + 1][SIZE + 1];
struct BoardPosition
{
    int Y;
    int X;
};
void DisplayCoverageBoard()
{
    system("cls");
    int i, j;

    printf("Press 'wasd' to move the token\nPress 'q' to place the token\n");
    for (i = 1; i <= SIZE + 1; i++)
        printf(" -");
    printf("\n");

    for (i = 1; i <= SIZE; i++)
    {
        printf("|");
        for (j = 0; j < SIZE; j++)
            printf(" %c", CoverageBoard[SIZE - i][j]);
        printf(" |\n");
    }

    for (i = 1; i <= SIZE + 1; i++)
        printf(" -");
    printf("\n");
}

enum Status
{
    START,
    PLACE,
    END
};
enum Circuit
{
    OPENED,
    CLOSED
};
struct CoveragePlayer
{
    char symbol;
    int symbolsUsed;
    enum Status status;
    struct BoardPosition startPos, currPos, endPos;
    int areaCovered;
    enum Circuit circuit;
};
void calculateArea(struct CoveragePlayer *CP, int areaToFill[SIZE + 1][SIZE + 1], int y, int x)
{
    if (CP->circuit == CLOSED)
    {
        if (((CP->startPos.Y == SIZE - 1 && CP->endPos.X == SIZE - 1) || (CP->startPos.X == SIZE - 1 && CP->endPos.Y == SIZE - 1)) && (y == 0 || x == 0))
            CP->circuit = OPENED;
        else if (((CP->startPos.Y == 0 && CP->endPos.X == SIZE - 1) || (CP->startPos.X == SIZE - 1 && CP->endPos.Y == 0)) && (y == SIZE - 1 || x == 0))
            CP->circuit = OPENED;
        else if (((CP->startPos.Y == 0 && CP->endPos.X == 0) || (CP->startPos.X == 0 && CP->endPos.Y == 0)) && (y == SIZE - 1 || x == SIZE - 1))
            CP->circuit = OPENED;
        else if (((CP->startPos.Y == SIZE - 1 && CP->endPos.X == 0) || (CP->startPos.X == 0 && CP->endPos.Y == SIZE - 1)) && (y == 0 || x == SIZE - 1))
            CP->circuit = OPENED;

        else if ((CP->startPos.Y == SIZE - 1 && CP->endPos.Y == SIZE - 1) && (y == 0 || x == 0 || x == SIZE - 1))
            CP->circuit = OPENED;
        else if ((CP->startPos.X == SIZE - 1 && CP->endPos.X == SIZE - 1) && (y == 0 || y == SIZE - 1 || x == 0))
            CP->circuit = OPENED;
        else if ((CP->startPos.Y == 0 && CP->endPos.Y == 0) && (y == SIZE - 1 || x == 0 || x == SIZE - 1))
            CP->circuit = OPENED;
        else if ((CP->startPos.X == 0 && CP->endPos.X == 0) && (y == 0 || y == SIZE - 1 || x == SIZE - 1))
            CP->circuit = OPENED;
    }

    areaToFill[y][x] = 1;
    if (y < SIZE - 1)
    {
        if (areaToFill[y + 1][x] == 0)
            calculateArea(CP, areaToFill, y + 1, x);
    }
    if (x < SIZE - 1)
    {
        if (areaToFill[y][x + 1] == 0)
            calculateArea(CP, areaToFill, y, x + 1);
    }
    if (y > 0)
    {
        if (areaToFill[y - 1][x] == 0)
            calculateArea(CP, areaToFill, y - 1, x);
    }
    if (x > 0)
    {
        if (areaToFill[y][x - 1] == 0)
            calculateArea(CP, areaToFill, y, x - 1);
    }
}
void StartTheCoverage(struct CoveragePlayer *CP)
{
    char ch;
    do
    {
        CP->currPos.Y = rand() % SIZE;
        CP->currPos.X = rand() % SIZE;
    } while (CoverageBoard[CP->currPos.Y][CP->currPos.X] != ' ');

    CoverageBoard[CP->currPos.Y][CP->currPos.X] = CP->symbol;
    DisplayCoverageBoard();
    while (1)
    {
        ch = getch();
        if (ch == 'w')
        {
            if (CP->currPos.Y < SIZE - 1 && CoverageBoard[CP->currPos.Y + 1][CP->currPos.X] == ' ')
            {
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = ' ';
                CP->currPos.Y++;
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = CP->symbol;
                DisplayCoverageBoard();
            }
            else if (CP->currPos.Y == SIZE - 1 && CoverageBoard[0][CP->currPos.X] == ' ')
            {
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = ' ';
                CP->currPos.Y = 0;
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = CP->symbol;
                DisplayCoverageBoard();
            }
        }
        else if (ch == 's')
        {
            if (CP->currPos.Y > 0 && CoverageBoard[CP->currPos.Y - 1][CP->currPos.X] == ' ')
            {
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = ' ';
                CP->currPos.Y--;
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = CP->symbol;
                DisplayCoverageBoard();
            }
            else if (CP->currPos.Y == 0 && CoverageBoard[SIZE - 1][CP->currPos.X] == ' ')
            {
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = ' ';
                CP->currPos.Y = SIZE - 1;
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = CP->symbol;
                DisplayCoverageBoard();
            }
        }
        else if (ch == 'a')
        {
            if (CP->currPos.X > 0 && CoverageBoard[CP->currPos.Y][CP->currPos.X - 1] == ' ')
            {
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = ' ';
                CP->currPos.X--;
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = CP->symbol;
                DisplayCoverageBoard();
            }
            else if (CP->currPos.X == 0 && CoverageBoard[CP->currPos.Y][SIZE - 1] == ' ')
            {
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = ' ';
                CP->currPos.X = SIZE - 1;
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = CP->symbol;
                DisplayCoverageBoard();
            }
        }
        else if (ch == 'd')
        {
            if (CP->currPos.X < SIZE - 1 && CoverageBoard[CP->currPos.Y][CP->currPos.X + 1] == ' ')
            {
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = ' ';
                CP->currPos.X++;
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = CP->symbol;
                DisplayCoverageBoard();
            }
            else if (CP->currPos.X == SIZE - 1 && CoverageBoard[CP->currPos.Y][0] == ' ')
            {
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = ' ';
                CP->currPos.X = 0;
                CoverageBoard[CP->currPos.Y][CP->currPos.X] = CP->symbol;
                DisplayCoverageBoard();
            }
        }
        else if (ch == 'q')
        {
            if (CP->status == START && (CP->currPos.Y == 0 || CP->currPos.Y == SIZE - 1 || CP->currPos.X == 0 || CP->currPos.X == SIZE - 1))
            {
                CP->startPos = CP->currPos;
                CP->status = PLACE;
                CP->symbolsUsed++;
                break;
            }
            else if (CP->status == PLACE && (CoverageBoard[CP->currPos.Y - 1][CP->currPos.X] == CP->symbol || CoverageBoard[CP->currPos.Y + 1][CP->currPos.X] == CP->symbol || CoverageBoard[CP->currPos.Y][CP->currPos.X - 1] == CP->symbol || CoverageBoard[CP->currPos.Y][CP->currPos.X + 1] == CP->symbol))
            {
                if (CP->currPos.Y == 0 || CP->currPos.Y == SIZE - 1 || CP->currPos.X == 0 || CP->currPos.X == SIZE - 1)
                {
                    CP->endPos = CP->currPos;
                    CP->status = END;
                }
                CP->symbolsUsed++;
                break;
            }
        }
    }

    if (CP->status == END)
    {
        int areaToFill[SIZE + 1][SIZE + 1], y, x;
        int i, j;
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                if (CoverageBoard[i][j] == CP->symbol)
                    areaToFill[i][j] = -1;
                else
                    areaToFill[i][j] = 0;
            }
        }
        CP->circuit = CLOSED;
        do
        {
            y = rand() % SIZE;
            x = rand() % SIZE;
        } while (areaToFill[y][x] != 0);
        calculateArea(CP, areaToFill, y, x);

        CP->areaCovered = 0;
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                if (areaToFill[i][j] == 1)
                    CP->areaCovered++;
            }
        }
        int verticalBorder = (CP->startPos.Y == 0 && CP->endPos.Y == SIZE - 1) || (CP->startPos.Y == SIZE - 1 && CP->endPos.Y == 0);
        int horizontalBorder = (CP->startPos.X == 0 && CP->endPos.X == SIZE - 1) || (CP->startPos.X == SIZE - 1 && CP->endPos.X == 0);
        if (verticalBorder || horizontalBorder)
            CP->areaCovered = (CP->areaCovered > (SIZE * SIZE) / 2) ? (SIZE * SIZE) - (CP->areaCovered + CP->symbolsUsed) : CP->areaCovered;
        else
            CP->areaCovered = (CP->circuit == OPENED) ? (SIZE * SIZE) - (CP->areaCovered + CP->symbolsUsed) : CP->areaCovered;
    }
}

int no_of_players;
struct Player
{
    char name[21];
    char symbol;
    int amount;
};
int main()
{
    srand(time(0));
    int i, j;

    printf("Enter no. of players = ");
    scanf("%d", &no_of_players);
    struct CoveragePlayer CP[no_of_players];
    char user[no_of_players][21];

    enum
    {
        ALL,
        NOT_ALL
    } UniqueNS;
    for (i = 0; i < no_of_players; i++)
    {
        do
        {
            UniqueNS = ALL;
            printf("\nPlayer %d,\nEnter your name: (max. 20 char.) ", i + 1);
            scanf(" %20[^\n]s", &user[i]);
            printf("Enter your symbol: ");
            scanf(" %c", &(CP[i].symbol));
            for (j = 0; j < i; j++)
            {
                if (strcmp(user[i], user[j]) == 0)
                {
                    UniqueNS = NOT_ALL;
                    printf("This name is taken.....\n");
                    break;
                }
                if (CP[i].symbol == CP[j].symbol)
                {
                    UniqueNS = NOT_ALL;
                    printf("This symbol is taken.....\n");
                    break;
                }
            }
        } while (UniqueNS == NOT_ALL);
        CP[i].symbolsUsed = 0;
        CP[i].status = START;
    }
    printf("\nThe Coverage starts now!!!!!\n\n");
    system("pause");

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
            CoverageBoard[i][j] = ' ';
    }
    enum
    {
        YES,
        NO
    } allPlaced;
    do
    {
        allPlaced = YES;
        for (i = 0; i < no_of_players; i++)
        {
            if (CP[i].status != END)
            {
                allPlaced = NO;

                system("cls");
                printf("Player %d, %s's Turn\n", i + 1, user[i]);
                system("pause");

                StartTheCoverage(CP + i);
                
                printf("\tToken placed.....");
                delay(1000);
            }
        }
    } while (allPlaced == NO);
    printf("\n\nThe Coverage is over!!!!!\n\n");

    int Sum_symbolsUsed = 0;
    for (i = 0; i < no_of_players; i++)
    {
        printf("Player %d, %s\n", i + 1, user[i]);
        printf("\nArea covered: %d", CP[i].areaCovered);
        printf("\nSymbols Used: %d\n\n", CP[i].symbolsUsed);
        Sum_symbolsUsed += CP[i].symbolsUsed;
    }
    system("pause");

    system("cls");
    struct Player P[no_of_players];
    if (rand() % 2 == 0)
    {
        for (i = 0; i < no_of_players; i++)
        {
            strcpy(P[i].name, user[i]);
            P[i].symbol = CP[i].symbol;
            P[i].amount = (CP[i].areaCovered * CP[i].symbolsUsed) / Sum_symbolsUsed;
            printf("Amount given to Player %d, %s = %d\n", i + 1, P[i].name, P[i].amount);
        }
    }
    else
    {
        for (i = 0; i < no_of_players; i++)
        {
            strcpy(P[i].name, user[i]);
            P[i].symbol = CP[i].symbol;
            P[i].amount = (CP[i].areaCovered * Sum_symbolsUsed) / CP[i].symbolsUsed;
            printf("Amount given to Player %d, %s = %d\n", i + 1, P[i].name, P[i].amount);
        }
    }
    printf("\n");
    system("pause");

    FILE *fptr = fopen("Players.dat", "wb");
    fwrite(&no_of_players, sizeof(no_of_players), 1, fptr);
    fwrite(P, sizeof(P), 1, fptr);
    fclose(fptr);
}