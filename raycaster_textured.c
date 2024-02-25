#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minilibx/mlx.h"

#define WIDTH 1280
#define HEIGHT 720
#define KEY_ESC 53

// derlemek icin bunu kullan
// gcc -framework OpenGL -framework AppKit -L./minilibx -lmlx -g raycaster_textured.c 

typedef struct s_player
{
    void *mlx;
    void *win;
    int current_frame;
    int num_frames;
    char *frame_names[39];
} t_player;

void init_anim(t_player *player)
{
    player->current_frame = 0;
    player->num_frames = 39;
    
    int a = 0;
    int b = 0;
    int i = 1;

    while(i <= 39)
    {
        char filename[20];
        sprintf(filename, "activision/%d.xpm", i);
        player->frame_names[i - 1] = mlx_xpm_file_to_image(player->mlx, filename, &a, &b);
        if (!player->frame_names[i - 1])
        {
            fprintf(stderr, "Error loading XPM file: %s\n", filename);
            exit(1);
        }
        i++;
    }
}

void update_frame(t_player *player)
{
    static int frame_count = 0;
    int delay_factor = 1000;

    if (frame_count % delay_factor == 0)
    {
        mlx_put_image_to_window(player->mlx, player->win, player->frame_names[player->current_frame], -300, -200);
        
        player->current_frame++;
        if (player->current_frame >= player->num_frames)
            player->current_frame = 0;
    }
    frame_count++;
}

int key_press(int keycode, t_player *player)
{
    if (keycode == KEY_ESC)
        exit(0);
    return (0);
}

int main()
{
    t_player player;

    player.mlx = mlx_init();
    player.win = mlx_new_window(player.mlx, WIDTH, HEIGHT, "Animation");

    init_anim(&player);
    mlx_hook(player.win, 2, 1L << 0, key_press, &player);
    mlx_loop_hook(player.mlx, (void *)update_frame, &player);
    mlx_loop(player.mlx);

    return (0);
}
