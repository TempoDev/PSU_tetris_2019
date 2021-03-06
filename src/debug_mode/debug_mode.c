/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** Displays the game's configuration until the user presses a key.
*/

#include <ncurses.h>
#include "fae.h"
#include "tetris.h"

void launch_debug_mode(config_t *config)
{
    struct termios attr1 = {0};
    struct termios attr2 = {0};
    char c = 0;

    fae_put("*** DEBUG MODE ***\n");
    display_keys(config);
    fae_put("Next : %s\n", config->hide_next ? "No" : "Yes");
    fae_put("Level : %d\n", config->level);
    fae_put("Size : %d*%d\n", config->map_height, config->map_width);
    fae_put("Tetriminos : %d\n", config->tlist_size);
    display_tetriminos_list(config);
    fae_put("Press any key to start Tetris");
    ioctl(STDIN_FILENO, TCGETS, &attr1);
    ioctl(STDIN_FILENO, TCGETS, &attr2);
    attr1.c_lflag &= ~(ECHO | ICANON);
    ioctl(STDIN_FILENO, TCSETSF, &attr1);
    read(STDIN_FILENO, &c, 1);
    ioctl(STDIN_FILENO, TCSETSF, &attr2);
}

void display_keys(config_t *config)
{
    fae_put("Key Left : %s\n", get_key_by_code(config->key.move_left));
    fae_put("Key Right : %s\n", get_key_by_code(config->key.move_right));
    fae_put("Key Turn : %s\n", get_key_by_code(config->key.rotate));
    fae_put("Key Drop : %s\n", get_key_by_code(config->key.drop));
    fae_put("Key Quit : %s\n", get_key_by_code(config->key.quit));
    fae_put("Key Pause : %s\n", get_key_by_code(config->key.pause));
}

char *get_key_by_code(int key_code)
{
    switch (key_code) {
    case KEY_UP :
        return ("^EOA");
    case KEY_DOWN :
        return ("^EOB");
    case KEY_RIGHT :
        return ("^EOC");
    case KEY_LEFT :
        return ("^EOD");
    case 32 :
        return ("(space)");
    default :
        return (keyname(key_code));
    }
}

void display_tetriminos_list(config_t *config)
{
    tetrimino_t *list = NULL;

    if (config->tetri_list == NULL)
        return;
    sort_tetriminos_list(&(config->tetri_list), config->tlist_size);
    list = config->tetri_list;
    while (list != NULL) {
        fae_put("Tetriminos : ");
        fae_put("Name %s : ", list->name);
        if (list->shape != NULL) {
            fae_put("Size %d*%d : ", list->width, list->height);
            fae_put("Color %d :\n", list->color);
            display_tetrimino_shape(list);
        } else
            fae_put("Error\n");
        list = list->next;
    }
}

void display_tetrimino_shape(tetrimino_t *tetrimino)
{
    for (int i = 0; i < tetrimino->height; i++) {
        for (int j = 0; j < tetrimino->width; j++)
            fae_put("%c", tetrimino->shape[i][j] ? '*' : ' ');
        fae_put("\n");
    }
}