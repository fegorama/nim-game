#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void print_board(board game_board)
{
    int l, i, n;
    int total_lines = sizeof(game_board.lines) / sizeof(game_board.lines[0]);

    for (l = 0; l < total_lines; ++l)
    {
        n = game_board.lines[l];

        printf("[%d] ", l + 1);

        for (i = 0; i < n; ++i)
            printf(" | ");

        printf("\n");
    }
}

int take(int row, int num, board *game_board)
{
    int res = 1;

    if (row < 1 || row >= 4)
        printf("Fila inválida. Introduzca una fila correcta.\n");
    else if (game_board->lines[row - 1] == 0)
        printf("Esa fila no existe o no tiene elementos.\n");
    else if (num < 1 || num > game_board->lines[row - 1])
        printf("El número de elementos a coger en una fila no puede ser superior a los que hay o inferior a 1.\n");
    else
    {
        game_board->lines[row - 1] -= num;
    }

    return res;
}

void read_data(int *row, int *num)
{
    int res_row;
    int res_num;

    do
    {
        printf("\nIntroduce la fila: ");
        res_row = scanf("%d", row);

        if (res_row == 'x')
            exit (0);

        printf("\nIntroduce el número de elementos a recoger: ");
        res_num = scanf("%d", num);

        if (res_num == 'x')
            exit(0);

        if ((res_row != 1 || res_num != 1))
        {
            printf("Entrada inválida. Deben ser dos números enteros positivos o 'x' para salir.");
            while (getchar() != '\n')
            {
            };
        }

    } while (res_row != 1 || res_num != 1);
}

int main(void)
{
    int row, number;
    board game_board = {1, 3, 5, 7};

    while (1)
    {
        printf("Nim game\n");
        print_board(game_board);
        read_data(&row, &number);
        if (take(row, number, &game_board) == 0)
        {
            // ...
        }
    }

    return 0;
}
