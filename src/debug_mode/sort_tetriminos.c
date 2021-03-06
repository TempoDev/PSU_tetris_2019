/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** Sorting of the tetriminos chained list (alphabetical order).
*/

#include "fae.h"
#include "tetris.h"

void sort_tetriminos_list(tetrimino_t **list, int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            swap_elements_if_needed(list, j);
        }
    }
}

void swap_elements_if_needed(tetrimino_t **list, int index)
{
    tetrimino_t *tetr = *list;

    for (int i = 0; i < index && tetr->next != NULL; i++)
        tetr = tetr->next;
    if (tetr != NULL && tetr->next != NULL) {
        if (elements_must_be_swapped(tetr->name, tetr->next->name) > 0)
            swap_elements(list, index);
    }
}

int elements_must_be_swapped(char *elem1, char *elem2)
{
    for (; *elem1 && *elem2; elem1++, elem2++) {
        if (get_lowercase(*elem1) > get_lowercase(*elem2))
            return (1);
        else if (get_lowercase(*elem1) < get_lowercase(*elem2))
            return (0);
    }
    return (*elem1 - *elem2 > 0);
}

char get_lowercase(char c)
{
    if (!('A' <= c && c <= 'Z'))
        return (c);
    return (c + ('a' - 'A'));
}

void swap_elements(tetrimino_t **list, int index)
{
    tetrimino_t *cp_prev = *list;
    tetrimino_t *cp_first = NULL;
    tetrimino_t *cp_sec = NULL;
    tetrimino_t *cp_next = NULL;

    for (int i = 0; i < index - 1 && cp_prev->next != NULL; i++)
        cp_prev = cp_prev->next;
    cp_first = (index - 1 >= 0) ? cp_prev->next : cp_prev;
    cp_sec = cp_first->next;
    cp_next = cp_sec->next;
    if (index - 1 >= 0)
        cp_prev->next = cp_sec;
    else
        *list = cp_sec;
    cp_first->next = cp_next;
    cp_sec->next = cp_first;
}