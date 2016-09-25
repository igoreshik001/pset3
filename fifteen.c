/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
// обнуление массива (доска)
    for (int i=0; i<DIM_MAX;i++)
        for (int j=0;j<DIM_MAX;j++)
            board[i][j] = -1;
            
    int numbers = d*d-1;// количество плиток
// набор массива
    for (int i = 0; i<d; i++)
        for (int j = 0; j<d; j++)
        {
            board[i][j] = numbers;
            numbers--;
        }
    if (d%2 == 0) // если четное, меняем местами
    {
        board[d-1][d-3]=1;
        board[d-1][d-2]=2;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
// вывод доски
    for (int i=0;i<d;i++)
    {
        for (int j=0;j<d; j++)
        {
            if (board[i][j] == 0)//нолик выводим подчеркиванием
            {
                printf("|__");
            }
            else
            {
                if (board[i][j]<10)//если число меньше 10 добавляем пробел для выравнивания столбцов
                {
                    printf("| %i", board[i][j]);
                }
                else
                {
                    printf("|%i", board[i][j]);
                }
            }
        }
        printf("|\n");//конец рядка, снос
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
// поиск выбранной плитки(числа)
    for (int i=0;i<d;i++)
        for (int j=0;j<d;j++)
        {
            if (board[i][j] == tile)// если нашли
            {
                int offset = 1;//смещение на один рядок вправо (или столбец вниз)
                if (j<d-1 && (board[i][j+offset] == 0))// если плитка не крайняя в ряду и следующая = 0
                {
                //меняем местами и возврат тру
                    int bufer = board[i][j+offset];
                    board[i][j+offset] = board[i][j];
                    board [i][j] = bufer;
                    return true;
                }
                if (i<d-1 && (board[i+offset][j] == 0))// если плитка не в крайнем столбце и в следующем = 0
                {
                    int bufer = board[i+offset][j];
                    board[i+offset][j] = board[i][j];
                    board [i][j] = bufer;
                    return true;
                }
                offset = -1;//смещение на один рядок влево (или столбец вверх)
                if (j>0 && (board[i][j+offset] == 0)) // если плитка не первая в ряду и предидующая = 0
                {
                    int bufer = board[i][j+offset];
                    board[i][j+offset] = board[i][j];
                    board [i][j] = bufer;
                    return true;
                }
                if (i>0 && (board[i+offset][j] == 0))// если плитка не в первом столбце и в предидующем = 0
                {
                    int bufer = board[i+offset][j];
                    board[i+offset][j] = board[i][j];
                    board [i][j] = bufer;
                    return true;
                }
            }
        }
    return false;// значит выбранного числа нет
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int counter =1;
//проверка положения чисел
    for (int i=0;i<d;i++)
        for (int j=0;j<d;j++)
        {
            if (counter == d*d)
                counter = 0;
            if (board[i][j] != counter)// если число на доске не последовательно
                return false;
            counter ++;
        }
    return true;// если все совпадают.Победа!
}
