#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int start, end;
} Ladder, Snake;

int main()
{
    int k, m, n, l, s, r;

    scanf("%d %d %d %d %d %d", &k, &m, &n, &l, &s, &r);

    Ladder *ladders = (Ladder *)malloc(l * sizeof(Ladder));
    for (int i = 0; i < l; i++)
    {
        scanf("%d %d", &ladders[i].start, &ladders[i].end);
    }

    Snake *snakes = (Snake *)malloc(s * sizeof(Snake));
    for (int i = 0; i < s; i++)
    {
        scanf("%d %d", &snakes[i].start, &snakes[i].end);
    }

    int **dice_rolls = (int **)malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++)
    {
        dice_rolls[i] = (int *)malloc(k * sizeof(int));
        for (int j = 0; j < k; j++)
        {
            scanf("%d", &dice_rolls[i][j]);
        }
    }

    // for (int i = 0; i < l; i++)
    // {
    //     printf("L%d: [%d, %d]\n", i + 1, ladders[i].start, ladders[i].end);
    // }

    // for (int i = 0; i < s; i++)
    // {
    //     printf("S%d: [%d, %d]\n", i + 1, snakes[i].start, snakes[i].end);
    // }

    // for (int i = 0; i < r; i++)
    // {
    //     printf("R%d: ", i + 1);
    //     for (int j = 0; j < k; j++)
    //     {
    //         printf("%d ", dice_rolls[i][j]);
    //     }
    //     printf("\n");
    // }

    int *player_positions = (int *)calloc(k, sizeof(int));
    int *player_rounds = (int *)calloc(k, sizeof(int));
    int *is_looping = (int *)calloc(k, sizeof(int));

    for (int i = 0; i < r; i++)
    {
        for (int p = 0; p < k; p++)
        {
            if (player_positions[p] == m * n || is_looping[p])
                continue;

            int new_pos = player_positions[p] + dice_rolls[i][p];
            if (new_pos > m * n)
            {
                player_rounds[p] = i + 1;
                continue;
            }

            int *visited = (int *)calloc(m * n + 1, sizeof(int));
            int curr_pos = new_pos;

            while (1)
            {
                int flag = 0;
                visited[curr_pos]++;

                for (int i = 0; i < l; i++)
                {
                    if (ladders[i].start == curr_pos)
                    {
                        curr_pos = ladders[i].end;
                        flag = 1;
                        break;
                    }
                }

                if (!flag)
                {
                    for (int i = 0; i < s; i++)
                    {
                        if (snakes[i].start == curr_pos)
                        {
                            curr_pos = snakes[i].end;
                            flag = 1;
                            break;
                        }
                    }
                }

                if (!flag)
                    break;

                // if (curr_pos == new_pos)
                // {
                //     is_looping[p] = 1;
                //     player_rounds[p] = i + 1;
                //     break;
                // }

                if (visited[curr_pos] > 1)
                {
                    is_looping[p] = 1;
                    player_rounds[p] = i + 1;
                    break;
                }
            }

            if (is_looping[p])
                continue;

            for (int j = 0; j < k; j++)
            {
                if (j != p && player_positions[j] == curr_pos)
                {
                    player_positions[j] = 0;
                }
            }

            player_positions[p] = curr_pos;
            player_rounds[p] = i + 1;
        }
    }

    for (int p = 0; p < k; p++)
    {
        printf("%d ", p + 1);
        if (is_looping[p])
        {
            printf("LOOPING %d\n", player_rounds[p]);
        }
        else if (player_positions[p] == m * n)
        {
            printf("COMPLETED %d\n", player_rounds[p]);
        }
        else
        {
            printf("%d %d\n", player_positions[p], player_rounds[p]);
        }
    }

    return 0;
}