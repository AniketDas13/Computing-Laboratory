#include "common.h"
#include <ctype.h>
#include <stdio.h>

int main(int ac, char *av[])
{
    char S[128], guesses[64], *cp;
    int N, i, l, ticks;
    double scores[2] = {0.0};     /* A's score = score[0], B's score = score[1] */
    int guesser = 1, thinker = 0; /* Round 1: A is thinker, B is guesser */

    scanf("%d\n", &N);
    for (i = 0; i < N; i++)
    {
        int counts_S[128] = {0};
        scanf("%s %s\n", S, guesses);
#if DEBUG > 0
        fprintf(, "Round %d\nS = %s\nGuesses = %s\n", i + 1, S, guesses);
#endif // DEBUG

        /* Mark which characters are present */
        for (cp = S; *cp; cp++)
        {
            if (isupper(*cp))
                counts_S['a' + *cp - 'A']++;
            else
                counts_S[*cp]++;
        }
        l = cp - S; // length of S
#ifdef DEBUG
        fprintf(stderr, "len(S) = %d\n", l);
#endif // DEBUG

        /* Process the guesses */
        ticks = 0;
        for (cp = guesses; /* nothing to check */; cp++)
        {
#ifdef DEBUG
            fprintf(stderr, "Guess = %c ", *cp);
#endif // DEBUG
            if (isupper(*cp))
                *cp = 'a' + *cp - 'A';
            if (*cp != '_' && !isalnum(*cp))
            { /* guesser gives up */
                scores[thinker] += 1.0 / 37;
#ifdef DEBUG
                fprintf(stderr, "%c loses / gives up.\n\n", (i % 2) ? 'A' : 'B');
#endif // DEBUG
                break;
            }
            ticks += counts_S[*cp];
#ifdef DEBUG
            fprintf(stderr, "%d hits.\n", counts_S[*cp]);
#endif // DEBUG
            counts_S[*cp] = 0;
            if (ticks == l)
            { /* guesser wins */
#ifdef DEBUG
                fprintf(stderr, "%c wins after %ld guesses.\n\n",
                        (i % 2) ? 'A' : 'B', (cp - guesses + 1));
#endif // DEBUG
                scores[guesser] += 1.0 / (cp - guesses + 1);
                break;
            }
        }
        /* Switch roles */
        guesser = 1 - guesser;
        thinker = 1 - thinker;
    }

    printf("%f %f\n", scores[0], scores[1]);

    return 0;
}