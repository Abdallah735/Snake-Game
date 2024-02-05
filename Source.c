#include <stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// this function is responsible for move all points of the tail behind the head depends on it's motion
void shift_tail(int arr[], int size) {
    for (int i = size - 2; i >= 0; i--)
        arr[i + 1] = arr[i];
}

enum Direction { Top = 1, Down, Right, Left };

struct Map
{
    int Width, Height;
    int FruitX, FruitY;
};

struct Snake
{
    int HeadX, HeadY;
    int Tail_N;
    int Tail_X[50], Tail_Y[50];
    enum Direction Dir;
};

struct Player
{
    int Score;
    bool Lose;
};

struct Map our_map;
struct Snake our_snake;
struct Player our_player;

// this function is responsible for generate fruit randomle on inside the borders of our map
void Generate_Fruit() {
    srand(time(NULL));
    our_map.FruitX = rand() % (our_map.Width - 2) + 1;
    our_map.FruitY = rand() % (our_map.Height - 2) + 1;
}

// this function is responsible for initialize the game and set the beginning of the game
void setup() {
    our_map.Width = 40;
    our_map.Height = 20;
    Generate_Fruit();

    our_snake.HeadX = our_map.Width / 2;
    our_snake.HeadY = our_map.Height / 2;
    our_snake.Tail_N = 0;

    our_player.Score = 0;
    our_player.Lose = 0;
}

// this function is responsible for draw the over all(map, snake(head and tail points), fruit and also show the score of our player)
void Draw() {
    system("cls");
    for (int i = 0; i < our_map.Height; i++) {
        for (int j = 0; j < our_map.Width; j++) {
            if (i == 0 || i == our_map.Height - 1) printf("*");
            else if (j == 0 || j == our_map.Width - 1) printf("*");
            else if (i == our_snake.HeadY && j == our_snake.HeadX) printf("O");
            else if (i == our_map.FruitY && j == our_map.FruitX) printf("$");
            else {
                bool flag = false;
                for (int s = 0; s < our_snake.Tail_N; s++) {
                    if (our_snake.Tail_X[s] == j && our_snake.Tail_Y[s] == i) {
                        printf("o");
                        flag = true;
                        break;
                    }
                }
                if (!flag) printf(" ");
            }
        }
        printf("\n");
    }
    printf("Player Score : %d\n", our_player.Score);
    printf("Press x to exit game\n", our_player.Lose);
}

// this function is responsible for checking  whether the player give order for the snake and change direction depending of this order
void Input() {
    if (_kbhit()) {
        char c = _getch();
        switch (c) {
        case 'w': our_snake.Dir = Top; break;
        case 's': our_snake.Dir = Down; break;
        case 'd': our_snake.Dir = Right; break;
        case 'a': our_snake.Dir = Left; break;
        case 'x': exit(0);
        }
    }
}

// this function is responsible for moving the snake depending on the current direction which identified by Input function
void Move() {
    shift_tail(our_snake.Tail_X, 50);
    shift_tail(our_snake.Tail_Y, 50);
    our_snake.Tail_X[0] = our_snake.HeadX;
    our_snake.Tail_Y[0] = our_snake.HeadY;
    switch (our_snake.Dir) {
    case Top: our_snake.HeadY--; break;
    case Down: our_snake.HeadY++; break;
    case Right: our_snake.HeadX++; break;
    case Left: our_snake.HeadX--; break;
    }
    if (our_snake.HeadY >= our_map.Height || our_snake.HeadY <= 0 || our_snake.HeadX >= our_map.Width || our_snake.HeadX <= 0)
        our_player.Lose = 1;
    for (int i = 0; i < our_snake.Tail_N; i++) {
        if (our_snake.Tail_X[i] == our_snake.HeadX && our_snake.Tail_Y[i] == our_snake.HeadY)
            our_player.Lose = true;
    }
    if (our_snake.HeadX == our_map.FruitX && our_snake.HeadY == our_map.FruitY) {
        Generate_Fruit();
        our_player.Score += 1;
        our_snake.Tail_N++;
    }
}

int main() {
    setup();
    while (!our_player.Lose) {
        Draw();
        Input();
        Move();
        Sleep(50);
    }
    system("pause");
    return 0;
}
