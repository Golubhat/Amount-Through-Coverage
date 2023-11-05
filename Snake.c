#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
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
#define HEIGHT 20
#define WIDTH 50
void Snake_Board(char Display[HEIGHT + 1][WIDTH + 1], int score, int playerTime)
{
    system("cls");
    int i, j;
    printf("\t\t\tScore: %d\t\t\t\tTime: %d\n", score, playerTime);
    for (i = 0; i < WIDTH + 1; i++)
        printf(" -");
    printf("\n");
    for (i = 0; i < HEIGHT; i++)
    {
        printf("|");
        for (j = 0; j < WIDTH; j++)
            printf(" %c", Display[i][j]);
        printf(" |\n");
    }
    for (i = 0; i < WIDTH + 1; i++)
        printf(" -");
}
struct Position
{
    int posX;
    int posY;
};
int Snake_Game(char Display[HEIGHT + 1][WIDTH + 1], char foodSymbol, char playerSymbol, int playerTime)
{
    int i, j;
    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
            Display[i][j] = ' ';
    }

    int length = 5;
    struct Position *body = (struct Position *)malloc(length * sizeof(struct Position));
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    } dir = RIGHT;
    body[0].posX = 40;
    body[0].posY = 10;
    body[1].posX = 39;
    body[1].posY = 10;
    body[2].posX = 38;
    body[2].posY = 10;
    body[3].posX = 37;
    body[3].posY = 10;
    body[4].posX = 36;
    body[4].posY = 10;
    for (i = 0; i < length; i++)
        Display[body[i].posY][body[i].posX] = playerSymbol;

    struct Position food;
    do
    {
        food.posX = rand() % WIDTH;
        food.posY = rand() % HEIGHT;
    } while (Display[food.posY][food.posX] != ' ');
    Display[food.posY][food.posX] = foodSymbol;

    int score = 0;
    int countDown = 1;
    while (1)
    {
        Snake_Board(Display, score, playerTime);
        if (playerTime == 0)
            break;

        delay(200);
        if (kbhit())
        {
            char move = getch();
            if (move == 'w' && dir != DOWN)
                dir = UP;
            else if (move == 's' && dir != UP)
                dir = DOWN;
            else if (move == 'a' && dir != RIGHT)
                dir = LEFT;
            else if (move == 'd' && dir != LEFT)
                dir = RIGHT;
        }

        struct Position bodyAddition = body[length - 1];
        Display[body[length - 1].posY][body[length - 1].posX] = ' ';
        for (i = length - 1; i > 0; i--)
            body[i] = body[i - 1];

        if (dir == UP)
        {
            if (body[0].posY == 0)
                break;
            if (Display[body[0].posY - 1][body[0].posX] == playerSymbol)
                break;
            else
                body[0].posY--;
        }
        else if (dir == DOWN)
        {
            if (body[0].posY == HEIGHT - 1)
                break;
            if (Display[body[0].posY + 1][body[0].posX] == playerSymbol)
                break;
            else
                body[0].posY++;
        }
        else if (dir == LEFT)
        {
            if (body[0].posX == 0)
                break;
            if (Display[body[0].posY][body[0].posX - 1] == playerSymbol)
                break;
            else
                body[0].posX--;
        }
        else if (dir == RIGHT)
        {
            if (body[0].posX == WIDTH - 1)
                break;
            if (Display[body[0].posY][body[0].posX + 1] == playerSymbol)
                break;
            else
                body[0].posX++;
        }
        int isFood = (Display[body[0].posY][body[0].posX] == foodSymbol);
        Display[body[0].posY][body[0].posX] = playerSymbol;
        if (isFood)
        {
            score += 10;
            body = (struct Position *)realloc(body, (++length) * sizeof(struct Position));
            body[length - 1] = bodyAddition;
            Display[body[length - 1].posY][body[length - 1].posX] = playerSymbol;
            do
            {
                food.posX = rand() % WIDTH;
                food.posY = rand() % HEIGHT;
            } while (Display[food.posY][food.posX] != ' ');
            Display[food.posY][food.posX] = foodSymbol;
        }
        if (countDown == 10)
        {
            playerTime--;
            countDown = 1;
        }
        else
            countDown++;
    }
    return score;
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

    char Display[HEIGHT + 1][WIDTH + 1];

    int playerScore[no_of_players];
    for (int i = 1; i <= no_of_players; i++)
    {
        system("cls");
        printf("Player %d, %s will have snake with '%c' symbol\n", i, P[i - 1].name, P[i - 1].symbol);
        srand(time(0));
        char foodSymbol, done;
        do
        {
            foodSymbol = rand() % 94 + 33;
            done = 'y';
            for (int i = 0; i < no_of_players; i++)
            {
                if (foodSymbol == P[i].symbol)
                {
                    done = 'n';
                    break;
                }
            }
        } while (done == 'n');
        printf("The food will be '%c'\n", foodSymbol);
        system("pause");
        printf("\nThe Game is Started!!!!!\n");
        system("pause");

        playerScore[i - 1] = Snake_Game(Display, foodSymbol, P[i - 1].symbol, P[i - 1].amount);
        printf("\n\nPlayer %s, Score = %d\n", P[i - 1].name, playerScore[i - 1]);
        system("pause");
    }
    system("cls");
    printf("\t\t\t\t\t\tFinal Result!!!!!\n\n");
    for (int i = 0; i < no_of_players; i++)
        printf("Player %d, %s has scored %d points\n", i + 1, P[i].name, playerScore[i]);
    printf("\n");
    system("pause");
}