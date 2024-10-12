#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"

#define SUCCESS 0
#define FAILURE 1
#define MAX_LINES 10

void print_board(const board *game_board)
{
    int row_index, element_count;
    int total_lines = game_board->total_lines; // Asegúrate de que `total_lines` esté definido en la estructura `board`

    printf("\nTablero actual:\n");
    printf("Turno del jugador %d\n", game_board->turno_jugador);

    // Imprimir el tablero
    for (row_index = 0; row_index < total_lines; ++row_index)
    {
        element_count = game_board->lines[row_index];

        printf("[%d] ", row_index + 1); // Mostrar el número de fila

        // Imprimir la cantidad de elementos por fila
        for (int j = 0; j < element_count; ++j)
        {
            printf(" | ");
        }

        printf("\n"); // Salto de línea después de cada fila
    }
}

int take(int row, int num, board *game_board)
{
    // Comprobación de la fila válida
    if (row < 1 || row > game_board->total_lines)
    {
        printf("Fila inválida. Introduzca una fila entre 1 y 4.\n");
        return false; // Retorno indicando error en la fila
    }

    // Comprobación si la fila tiene elementos
    if (game_board->lines[row - 1] == 0)
    {
        printf("Esa fila no tiene elementos disponibles.\n");
        return false; // Retorno indicando que la fila está vacía
    }

    // Comprobación de la cantidad válida de elementos
    if (num < 1 || num > game_board->lines[row - 1])
    {
        printf("El número de elementos a tomar debe estar entre 1 y %d.\n", game_board->lines[row - 1]);
        return false; // Retorno indicando error en el número de elementos
    }

    // Si pasa todas las validaciones, se resta el número de elementos de la fila
    game_board->lines[row - 1] -= num;

    return true; // Retorno indicando éxito
}

int is_win(board *game_board)
{
    int total_lines = game_board->total_lines;

    // Recorremos las líneas del tablero
    for (int i = 0; i < total_lines; ++i)
    {
        // Si alguna línea tiene más de 1, no hay victoria
        if (game_board->lines[i] > 1)
            return false;

        // Si encontramos una línea con 1, verificamos que no haya otra ya encontrada
        if (game_board->lines[i] == 1)
        {
            // Si ya se había encontrado una línea ganadora, retornamos 0
            for (int j = i + 1; j < total_lines; ++j)
            {
                if (game_board->lines[j] == 1)
                    return false;
            }

            // Si no se encuentra más, es una victoria
            return true;
        }
    }

    // Si no se encontraron líneas con valor 1, no hay victoria
    return false;
}

void assign_mem(const int rows, board *game_board)
{
    // Se asigna memoria y si no se puede se aborta
    game_board->lines = (int *)malloc(rows * sizeof(int));
    if (game_board->lines == NULL)
    {
        printf("Error al asignar memoria\n");
        exit(1);
    }
}

void free_mem(board *game_board)
{
    free(game_board->lines);
}

void board_config(board *game_board)
{
    int rows;
    int res_row;

    while (true)
    {
        printf("\nIntroduce el número de filas para jugar: ");
        res_row = scanf("%d", &rows);

        // Comprobamos si las entradas son válidas y si los valores son positivos
        if (res_row == 1 && (rows > 0 && rows < MAX_LINES))
            break;

        // Si no, indicamos el error y limpiamos el buffer de entrada
        printf("Entrada inválida. Debe ser un número positivo entre 1 y %d.", MAX_LINES);
        while (getchar() != '\n')
            ; // Limpiamos el buffer para evitar bucle infinito
    }

    // Se configura el tablero
    game_board->total_lines = rows;
    assign_mem(rows, game_board);

    // Inicialización del tablero
    for (int i = 0; i < rows; ++i)
        game_board->lines[i] = 2 * (i + 1) - 1;
}

void read_data(int *row, int *num)
{
    int res_row, res_num;

    while (true)
    {
        printf("\nIntroduce la fila (número entero positivo): ");
        res_row = scanf("%d", row);

        printf("\nIntroduce el número de elementos a recoger (número entero positivo): ");
        res_num = scanf("%d", num);

        // Comprobamos si las entradas son válidas y si los valores son positivos
        if (res_row == 1 && res_num == 1 && *row > 0 && *num > 0)
            break;

        // Si no, indicamos el error y limpiamos el buffer de entrada
        printf("Entrada inválida. Deben ser dos números enteros positivos.");
        while (getchar() != '\n')
            ; // Limpiamos el buffer para evitar bucle infinito
    }
}

int main(void)
{
    int row, number;
    board game_board;

    printf("========\n");
    printf("Nim game\n");
    printf("========\n");
    board_config(&game_board);

    game_board.turno_jugador = 1;

    while (1)
    {
        // Imprimir el tablero y leer los datos
        print_board(&game_board);
        read_data(&row, &number);

        // Coger los elementos de la fila
        if (take(row, number, &game_board) == true)
        {
            // Verificar si el jugador actual ha ganado
            if (is_win(&game_board))
            {
                printf("¡Ha ganado el jugador %d!\n", game_board.turno_jugador);
                free_mem(&game_board);
                return 0;
            }
        }

        game_board.turno_jugador = game_board.turno_jugador == 1 ? 2 : 1;
    }

    return 0;
}
