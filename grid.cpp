#include "grid.hpp"

#include <ncurses.h>
#include <cstdlib>
#include <ctime>

Grid::Grid(int s) : size(s), numEmpty(size*size), greatestNum(0), numGoal(512*size), numTries(0)
{
    tile = new int* [size];

    for(int row=0; row<size; ++row)
    {
        tile[row] = new int[size];
    }

    srand(time(NULL));

    initscr();
    raw();
    keypad(stdscr, true);
    noecho();
}

Grid::~Grid()
{
    endwin();
    for (int i=0; i<size; ++i)
    {
        delete [] tile[i];
        tile[i] = 0;
    }
    delete [] tile;
    tile = 0;
}

void Grid::Start()
{
    Restart();

    int move;
    while ((move = getch()) != 'q')
    {
        switch(move)
        {
            case KEY_UP:
                Up();
                break;
            case KEY_DOWN:
                Down();
                break;
            case KEY_LEFT:
                Left();
                break;
            case KEY_RIGHT:
                Right();
                break;
            case 'r':
                Restart();
        }
    }
}

bool Grid::TestLeft() const
{
    if (numEmpty > 0)
    {
        return true;
    }
    for (int row=0; row<size; ++row)
    {
        for (int col=0; col<size-1; ++col)
        {
            if (tile[row][col] == tile[row][col+1])
            {
                return true;
            }
        }
    }

    return false;
}

void Grid::Left()
{
    if (!TestLeft())
    {
        return;
    }

    for (int row=0; row<size; ++row)
    {
        bool again = true;
        while (again)
        {
            again = false;
            for (int col=1; col<size; ++col)
            {
                if ((tile[row][col] != 0) && (tile[row][col-1] == 0))
                {
                    tile[row][col-1] = tile[row][col];
                    tile[row][col] = 0;
                    again = true;
                }
            }
        }
        for (int col=0; col<size-1; ++col)
        {
            if (tile[row][col] == 0)
            {
                continue;
            }
            else if (tile[row][col] == tile[row][col+1])
            {
                tile[row][col] *= 2;
                if (tile[row][col] > greatestNum)
                {
                    greatestNum = tile[row][col];
                }
                tile[row][col+1] *= 0;
                numEmpty++;
                ++col;
            }
        }
        again = true;
        while(again)
        {
            again = false;
            for (int col=1; col<size; ++col)
            {
                if ((tile[row][col] != 0) && (tile[row][col-1] == 0))
                {
                    tile[row][col-1] = tile[row][col];
                    tile[row][col] = 0;
                    again = true;
                }
            }
        }
    }

    Seed();
}

bool Grid::TestRight() const
{
    if (numEmpty > 0)
    {
        return true;
    }
    for (int row=0; row<size; ++row)
    {
        for (int col=size-1; col>0; --col)
        {
            if (tile[row][col] == tile[row][col-1])
            {
                return true;
            }
        }
    }

    return false;
}

void Grid::Right()
{
    if (!TestRight())
    {
        return;
    }

    for (int row=0; row<size; ++row)
    {
        bool again = true;
        while (again)
        {
            again = false;
            for (int col=size-2; col>-1; --col)
            {
                if ((tile[row][col] != 0) && (tile[row][col+1] == 0))
                {
                    tile[row][col+1] = tile[row][col];
                    tile[row][col] = 0;
                    again = true;
                }
            }
        }
        for (int col=size-1; col>0; --col)
        {
            if (tile[row][col] == 0)
            {
                continue;
            }
            else if (tile[row][col] == tile[row][col-1])
            {
                tile[row][col] *= 2;
                if (tile[row][col] > greatestNum)
                {
                    greatestNum = tile[row][col];
                }
                tile[row][col-1] *= 0;
                numEmpty++;
                --col;
            }
        }
        again = true;
        while (again)
        {
            again = false;
            for (int col=size-2; col>-1; --col)
            {
                if ((tile[row][col] != 0) && (tile[row][col+1] == 0))
                {
                    tile[row][col+1] = tile[row][col];
                    tile[row][col] = 0;
                    again = true;
                }
            }
        }
    }

    Seed();
}

bool Grid::TestDown() const
{
    if (numEmpty > 0)
    {
        return true;
    }
    for (int col=0; col<size; ++col)
    {
        for (int row=size-1; row>0; --row)
        {
            if (tile[row][col] == tile[row-1][col])
            {
                return true;
            }
        }
    }

    return false;
}

void Grid::Down()
{
    if (!TestDown())
    {
        return;
    }

    for (int col=0; col<size; ++col)
    {
        bool again = true;
        while (again)
        {
            again = false;
            for (int row=size-2; row>-1; --row)
            {
                if ((tile[row][col] != 0) && (tile[row+1][col] == 0))
                {
                    tile[row+1][col] = tile[row][col];
                    tile[row][col] = 0;
                    again = true;
                }
            }
        }
        for (int row=size-1; row>0; --row)
        {
            if (tile[row][col] == 0)
            {
                continue;
            }
            else if (tile[row][col] == tile[row-1][col])
            {
                tile[row][col] *= 2;
                if (tile[row][col] > greatestNum)
                {
                    greatestNum = tile[row][col];
                }
                tile[row-1][col] *= 0;
                numEmpty++;
                --row;
            }
        }
        again = true;
        while (again)
        {
            again = false;
            for (int row=size-2; row>-1; --row)
            {
                if ((tile[row][col] != 0) && (tile[row+1][col] == 0))
                {
                    tile[row+1][col] = tile[row][col];
                    tile[row][col] = 0;
                    again = true;
                }
            }
        }
    }

    Seed();
}

bool Grid::TestUp() const
{
    if (numEmpty > 0)
    {
        return true;
    }
    for (int col=0; col<size; ++col)
    {
        for (int row=0; row<size-1; ++row)
        {
            if (tile[row][col] == tile[row+1][col])
            {
                return true;
            }
        }
    }

    return false;
}

void Grid::Up()
{
    if (!TestUp())
    {
        return;
    }

    for (int col=0; col<size; ++col)
    {
        bool again = true;
        while (again)
        {
            again = false;
            for (int row=1; row<size; ++row)
            {
                if ((tile[row][col] != 0) && (tile[row-1][col] == 0))
                {
                    tile[row-1][col] = tile[row][col];
                    tile[row][col] = 0;
                    again = true;
                }
            }
        }
        for (int row=0; row<size-1; ++row)
        {
            if (tile[row][col] == 0)
            {
                continue;
            }
            else if (tile[row][col] == tile[row+1][col])
            {
                tile[row][col] *= 2;
                if (tile[row][col] > greatestNum)
                {
                    greatestNum = tile[row][col];
                }
                tile[row+1][col] *= 0;
                numEmpty++;
                ++row;
            }
        }
        again = true;
        while (again)
        {
            again = false;
            for (int row=1; row<size; ++row)
            {
                if ((tile[row][col] != 0) && (tile[row-1][col] == 0))
                {
                    tile[row-1][col] = tile[row][col];
                    tile[row][col] = 0;
                    again = true;
                }
            }
        }
    }

    Seed();
}

void Grid::Seed(bool check)
{
    int newValue = 2 + 2 * (rand() % 2);
    int position = rand() % numEmpty;

    for (int row=0; row<size; ++row)
    {
        for (int col=0; col<size; ++col)
        {
            if (tile[row][col] == 0)
            {
                if (position == 0)
                {
                    tile[row][col] = newValue;
                    --numEmpty;
                    Draw();
                    if (check)
                    {
                        Check();
                    }
                    return;
                }
                --position;
            }
        }
    }
}

void Grid::Draw()
{
    refresh();
    int numDigits = getNumDigits(numGoal);
    move(0, 0);
    addch(ACS_ULCORNER);
    for (int col=0; col<size; ++col)
    {
        for (int digit=0; digit<numDigits; ++digit)
        {
            addch(ACS_HLINE);
        }
        if (col == size-1)
        {
            addch(ACS_URCORNER);
        }
        else
        {
            addch(ACS_TTEE);
        }
    }
    for (int row=0; row<size; ++row)
    {
        move(row*2+1, 0);
        addch(ACS_VLINE);
        for (int col=0; col<size; ++col)
        {
            for (int digit=0; digit<numDigits; ++digit)
            {
                printw(" ");
            }
            addch(ACS_VLINE);
        }
        if (row == size-1)
        {
            move(row*2+2, 0);
            addch(ACS_LLCORNER);
            for (int col=0; col<size; ++col)
            {
                for (int digit=0; digit<numDigits; ++digit)
                {
                    addch(ACS_HLINE);
                }
                if (col == size-1)
                {
                    addch(ACS_LRCORNER);
                }
                else
                {
                    addch(ACS_BTEE);
                }
            }
        }
        else
        {
            move(row*2+2, 0);
            addch(ACS_LTEE);
            for (int col=0; col<size; ++col)
            {
                for (int digit=0; digit<numDigits; ++digit)
                {
                    addch(ACS_HLINE);
                }
                if (col == size-1)
                {
                    addch(ACS_RTEE);
                }
                else
                {
                    addch(ACS_PLUS);
                }
            }
        }
        for (int col=0; col<size; ++col)
        {
            move(row*2+1, col*5+1);

            int digitsRemaining = numDigits - getNumDigits(tile[row][col]);
            if (tile[row][col] != 0)
            {
                printw("%d", tile[row][col]);
            }
            for(int digit=0; digit<digitsRemaining; ++digit)
            {
                printw(" ");
            }
        }
    }
    mvprintw(size*2+1,0, "Try #: %d", numTries);
    mvprintw(size*2+2,0, "Press 'r' to restart.");
    mvprintw(size*2+3,0, "Press 'q' to quit.");
}

void Grid::Restart()
{
    ++numTries;

    numEmpty = size*size;
    greatestNum = 0;

    for(int row=0; row<size; ++row)
    {
        for(int col=0; col<size; ++col)
        {
            tile[row][col] = 0;
        }
    }

    clear();
    Seed(false);
    Seed(false);
}

bool Grid::Check()
{
    if (!TestLeft() &&
        !TestRight() &&
        !TestUp() &&
        !TestDown())
    {
        mvprintw(size*2+4,0, "Game over.");
        return false;
    }

    if (greatestNum == numGoal)
    {
        mvprintw(size*2+4,0, "You win.");
        getch();
        endwin();
        exit(0);
    }

    return true;
}

int Grid::getNumDigits(unsigned int x) const
{
    int numDigits = 0;
    while (x > 0)
    {
        x /= 10;
        ++numDigits;
    }
    return numDigits;
}
