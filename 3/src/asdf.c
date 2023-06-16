#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#include "stack.h"
#include "vector.h"

enum CellState {
    Close,
    Open
};

struct Cell {
    int x;
    int y;
    enum CellState Left;
    enum CellState Right;
    enum CellState Top;
    enum CellState Bottom;
    enum CellState Visited;
} typedef Cell;

char printCell(Cell cell) {
    if (cell.Left == Open && cell.Right == Open && cell.Top == Open && cell.Bottom == Open) {
        return '0';
    }
    else if (cell.Left == Open && cell.Right == Open && cell.Top == Open && cell.Bottom == Close) {
        return '1';
    }
    else if (cell.Left == Open && cell.Right == Open && cell.Top == Close && cell.Bottom == Open) {
        return '2';
    }
    else if (cell.Left == Open && cell.Right == Open && cell.Top == Close && cell.Bottom == Close) {
        return '3';
    }
    else if (cell.Left == Open && cell.Right == Close && cell.Top == Open && cell.Bottom == Open) {
        return '4';
    }
    else if (cell.Left == Open && cell.Right == Close && cell.Top == Open && cell.Bottom == Close) {
        return '5';
    }
    else if (cell.Left == Open && cell.Right == Close && cell.Top == Close && cell.Bottom == Open) {
        return '6';
    }
    else if (cell.Left == Open && cell.Right == Close && cell.Top == Close && cell.Bottom == Close) {
        return '7';
    }
    else if (cell.Left == Close && cell.Right == Open && cell.Top == Open && cell.Bottom == Open) {
        return '8';
    }
    else if (cell.Left == Close && cell.Right == Open && cell.Top == Open && cell.Bottom == Close) {
        return '9';
    }
    else if (cell.Left == Close && cell.Right == Open && cell.Top == Close && cell.Bottom == Open) {
        return 'A';
    }
    else if (cell.Left == Close && cell.Right == Open && cell.Top == Close && cell.Bottom == Close) {
        return 'B';
    }
    else if (cell.Left == Close && cell.Right == Close && cell.Top == Open && cell.Bottom == Open) {
        return 'C';
    }
    else if (cell.Left == Close && cell.Right == Close && cell.Top == Open && cell.Bottom == Close) {
        return 'D';
    }
    else if (cell.Left == Close && cell.Right == Close && cell.Top == Close && cell.Bottom == Open) {
        return 'E';
    }
    else if (cell.Left == Close && cell.Right == Close && cell.Top == Close && cell.Bottom == Close) {
        return 'F';
    }
    else {
        return 0;
    }
}

void mazemakeBinary(int height, int width) {

    Cell** maze = (Cell**)malloc(sizeof(Cell*) * (height + 1));
    for (int row = 0; row < height + 1; row++) {
        maze[row] = (Cell*)malloc(sizeof(Cell) * width);
    }
    if (maze != NULL) {
        for (int x = 0; x < width; x++) {//Инициализируем матрицу для лабиринта. На клеточку всего 6 аргументов- 4 грани 2-мерной стенки и координаты клетки лабиринта
            for (int y = 0; y < height; y++) {
                maze[y][x].x = x;
                maze[y][x].y = y;
                maze[y][x].Bottom = Close;
                maze[y][x].Left = Close;
                maze[y][x].Right = Close;
                maze[y][x].Top = Close;
                maze[y][x].Visited = false;
            }
        }

        int startX = 0;
        int startY = 0;

        Stack* path = createStack();
        push(path, &maze[startY][startX]);

        while (!isEmptyStack(path)) {//Когда закончатся клеточки)

            char newStringFlag = 0;
            Cell _cur_cell = *(Cell*)top(path);

            Vector* nextStep = createVector();
            if ((_cur_cell.x >= 0) && (_cur_cell.x < width - 1)) {//Вправо
                push_back(nextStep, &maze[_cur_cell.y][_cur_cell.x + 1]);
            }
            if ((_cur_cell.y > 0) && (_cur_cell.y < height)) {//Вверх
                push_back(nextStep, &maze[_cur_cell.y - 1][_cur_cell.x]);
            }
            if ((_cur_cell.x == width - 1) && _cur_cell.y < height - 1) {//Переход на некст строку
                push_back(nextStep, &maze[_cur_cell.y][_cur_cell.x]);
                newStringFlag = 1;
            }


            if (!isEmptyVector(nextStep)) {//Пока есть хотя бы одно решение
                Cell next_step;
                if (!newStringFlag) {//Не переход ли на новую строку
                    next_step = *(Cell*)vGet(nextStep, rand() % vectorSize(nextStep));
                    if (next_step.x != _cur_cell.x) {//Тут вроде очевидно
                        maze[_cur_cell.y][_cur_cell.x].Right = Open;
                        maze[next_step.y][next_step.x].Left = Open;
                    }
                    else if (next_step.y != _cur_cell.y) {
                        maze[_cur_cell.y][_cur_cell.x].Top = Open;
                        maze[next_step.y][next_step.x].Bottom = Open;
                    }

                    if (_cur_cell.y == height - 1 && _cur_cell.x == width - 1) {
                        break;
                    }
                    next_step = maze[_cur_cell.y][_cur_cell.x + 1];//Шажочек вправо

                }
                else {
                    next_step = *(Cell*)vGet(nextStep, vectorSize(nextStep) - 1);
                    if (next_step.y > 0) {
                        maze[_cur_cell.y][_cur_cell.x].Top = Open;
                        maze[next_step.y - 1][next_step.x].Bottom = Open;
                    }
                    next_step = maze[_cur_cell.y + 1][startX];
                    newStringFlag = 0;
                }
                pop(path);//Выкидываем отработанную клеточку и решения с ней вместе
                push(path, &next_step);//Вписываем новую клеточку

            }
            else {
                pop(path);//Избавляемся от вариантов без решений
            }

        }

        FILE* outputFile = fopen("maze.txt", "w");
        fprintf(outputFile, "%d\n%d\n", width, height);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                fprintf(outputFile, "%c", printCell(maze[y][x]));
            }
            fprintf(outputFile, "\n");
        }

    }

    free(maze);

}

//всё, что выше- работает. Генератор работает через раз, в упор не вижу ошибку
bool mazePrepare(int height, int width,Cell** maze) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (maze[y][x].Visited == false) {
                return false;
            }
        }
    }
    return true;
}

bool isItInPath(int* path_x, int* path_y, int randX, int randY,int path_len) {
    int position = 0;
    while (path_len>position) {
        if ((path_x[position] == randX) && (path_y[position] == randY)) {
            return true;
        }
        position++;
    }
    return false;
}

void mazemakeWilson(const int height,const  int width) {

    Cell** maze = (Cell**)malloc(sizeof(Cell*) * (height + 1));
    for (int row = 0; row < height + 1; row++) {
        maze[row] = (Cell*)malloc(sizeof(Cell) * width);
    }
    if (maze != NULL) {
        for (int y = 0; y < height; y++) {//Инициализируем матрицу для лабиринта. На клеточку всего 6 аргументов- 4 грани 2-мерной стенки и координаты клетки лабиринта
            for (int x = 0; x < width; x++) {
                maze[y][x].x = x;
                maze[y][x].y = y;
                maze[y][x].Bottom = Close;
                maze[y][x].Left = Close;
                maze[y][x].Right = Close;
                maze[y][x].Top = Close;
                maze[y][x].Visited = false;
            }
        }
        int x = rand() % width;
        int y = rand() % height;
        maze[y][x].Visited = true;
  
        while (!mazePrepare(height, width, maze)) {

            int randX = 0;
            int randY = 0;

            do {
                randX = rand() % width;
                randY = rand() % height;
            } while (maze[randY][randX].Visited);

            int* path_x = (int*)malloc(height * width);
            memset(path_x, -1, height * width);
            int* path_y = (int*)malloc(height * width);
            memset(path_y, -1, height * width);
            int path_len = 0;
            path_x[path_len] = x;
            path_y[path_len] = y;
            path_len++;

            while (x != randX || y != randY) {

                Cell _cur_cell = maze[randY][randX];
                Vector* nextStep = createVector();

                if ((_cur_cell.x >= 0) && (_cur_cell.x < width - 1)) {//Вправо
                    push_back(nextStep, &maze[_cur_cell.y][_cur_cell.x + 1]);
                }
                if ((_cur_cell.x > 0) && (_cur_cell.x <= width - 1)) {//Влево
                    push_back(nextStep, &maze[_cur_cell.y][_cur_cell.x - 1]);
                }
                if ((_cur_cell.y > 0) && (_cur_cell.y <= height - 1)) {//Вверх
                    push_back(nextStep, &maze[_cur_cell.y - 1][_cur_cell.x]);
                }
                if ((_cur_cell.y >= 0) && (_cur_cell.y < height - 1)) {//Вниз
                    push_back(nextStep, &maze[_cur_cell.y + 1][_cur_cell.x]);
                }
                Cell next_step;
                next_step = *(Cell*)vGet(nextStep, rand() % vectorSize(nextStep));

                path_x[path_len] = (int)next_step.x;
                path_y[path_len] = (int)next_step.y;
                path_len++;

                if (next_step.x != _cur_cell.x) {
                    if (next_step.x - _cur_cell.x > 0) {
                        maze[_cur_cell.y][_cur_cell.x].Right = Open;
                        maze[next_step.y][next_step.x].Left = Open;
                    }
                    else {
                        maze[_cur_cell.y][_cur_cell.x].Left = Open;
                        maze[next_step.y][next_step.x].Right = Open;
                    }
                }
                else if (next_step.y != _cur_cell.y) {
                    if (next_step.y - _cur_cell.y > 0) {
                        maze[_cur_cell.y][_cur_cell.x].Bottom = Open;
                        maze[next_step.y][next_step.x].Top = Open;
                    }
                    else {
                        maze[_cur_cell.y][_cur_cell.x].Top = Open;
                        maze[next_step.y][next_step.x].Bottom = Open;
                    }
                }

                maze[_cur_cell.y][_cur_cell.x].Visited = true;
                if (maze[next_step.y][next_step.x].Visited == true&&!isItInPath(path_x,path_y,x,y,path_len)) {
                    break;
                }
                randX = (int)next_step.x;
                randY = (int)next_step.y;
            }
            for (int i = 0; i < path_len; i++) {
                maze[path_y[i]][path_x[i]].Visited = true;
            }

        }

    }
    FILE* outputFile = fopen("maze.txt", "w");
    fprintf(outputFile, "%d\n%d\n", width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fprintf(outputFile, "%c", printCell(maze[y][x]));
        }
        fprintf(outputFile, "\n");
    }
}

void mazemakeHuntAndKill(int height, int width) {

}

int main() {

    srand(time(NULL));
    int height = 0; int width = 0;

    printf("Choose the size of the labirint ");

    while (height <= 1 || width <= 1) {
        int tmp = scanf("%d %d", &height, &width);
    }
    printf("Then choose the algoritm: ");
    int input =0 ;
    scanf("%d", &input);
    switch (input) {
    case 1:
        mazemakeBinary(height, width);
        break;
    case 2:
        mazemakeWilson(height, width);
        break;
    case 3:
        mazemakeHuntAndKill(height, width);
        break;
    }
    

    return 0;
}
