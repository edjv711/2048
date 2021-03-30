#include "grid.hpp"

#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <string>

Grid::Grid(int s) : _size(s), _numEmpty(_size*_size), _greatestNum(0), _numGoal(512*_size), _numTries(0)
{
    _tile = new int* [_size];

    for(int row=0; row<_size; ++row)
    {
        _tile[row] = new int[_size];
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
    for (int i=0; i<_size; ++i)
    {
        delete [] _tile[i];
        _tile[i] = 0;
    }
    delete [] _tile;
    _tile = 0;
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
    for (int row=0; row<_size; ++row)
    {
        for (int col=1; col<_size; ++col)
        {
            if ((_tile[row][col] !=0) && (_tile[row][col-1] == 0))
            {
                return true;
            }
        }
    }
    for (int row=0; row<_size; ++row)
    {
        for (int col=0; col<_size-1; ++col)
        {
            if (_tile[row][col] == 0)
            {
                continue;
            }
            if (_tile[row][col] == _tile[row][col+1])
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

    for (int row=0; row<_size; ++row)
    {
        bool again = true;
        while (again)
        {
            again = false;
            for (int col=1; col<_size; ++col)
            {
                if ((_tile[row][col] != 0) && (_tile[row][col-1] == 0))
                {
                    _tile[row][col-1] = _tile[row][col];
                    _tile[row][col] = 0;
                    again = true;
                }
            }
        }
        for (int col=0; col<_size-1; ++col)
        {
            if (_tile[row][col] == 0)
            {
                continue;
            }
            else if (_tile[row][col] == _tile[row][col+1])
            {
                _tile[row][col] *= 2;
                if (_tile[row][col] > _greatestNum)
                {
                    _greatestNum = _tile[row][col];
                }
                _tile[row][col+1] *= 0;
                _numEmpty++;
                ++col;
            }
        }
        again = true;
        while(again)
        {
            again = false;
            for (int col=1; col<_size; ++col)
            {
                if ((_tile[row][col] != 0) && (_tile[row][col-1] == 0))
                {
                    _tile[row][col-1] = _tile[row][col];
                    _tile[row][col] = 0;
                    again = true;
                }
            }
        }
    }

    Seed();
}

bool Grid::TestRight() const
{
    for (int row=0; row<_size; ++row)
    {
        for (int col=_size-2; col>-1; --col)
        {
            if ((_tile[row][col] !=0) && (_tile[row][col+1] == 0))
            {
                return true;
            }
        }
    }
    for (int row=0; row<_size; ++row)
    {
        for (int col=_size-1; col>0; --col)
        {
            if (_tile[row][col] == 0)
            {
                continue;
            }
            if (_tile[row][col] == _tile[row][col-1])
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

    for (int row=0; row<_size; ++row)
    {
        bool again = true;
        while (again)
        {
            again = false;
            for (int col=_size-2; col>-1; --col)
            {
                if ((_tile[row][col] != 0) && (_tile[row][col+1] == 0))
                {
                    _tile[row][col+1] = _tile[row][col];
                    _tile[row][col] = 0;
                    again = true;
                }
            }
        }
        for (int col=_size-1; col>0; --col)
        {
            if (_tile[row][col] == 0)
            {
                continue;
            }
            else if (_tile[row][col] == _tile[row][col-1])
            {
                _tile[row][col] *= 2;
                if (_tile[row][col] > _greatestNum)
                {
                    _greatestNum = _tile[row][col];
                }
                _tile[row][col-1] *= 0;
                _numEmpty++;
                --col;
            }
        }
        again = true;
        while (again)
        {
            again = false;
            for (int col=_size-2; col>-1; --col)
            {
                if ((_tile[row][col] != 0) && (_tile[row][col+1] == 0))
                {
                    _tile[row][col+1] = _tile[row][col];
                    _tile[row][col] = 0;
                    again = true;
                }
            }
        }
    }

    Seed();
}

bool Grid::TestDown() const
{
    for (int col=0; col<_size; ++col)
    {
        for (int row=_size-2; row>-1; --row)
        {
            if ((_tile[row][col] != 0) && (_tile[row+1][col] == 0))
            {
                return true;
            }
        }
    }
    for (int col=0; col<_size; ++col)
    {
        for (int row=_size-1; row>0; --row)
        {
            if (_tile[row][col] == 0)
            {
                continue;
            }
            if (_tile[row][col] == _tile[row-1][col])
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

    for (int col=0; col<_size; ++col)
    {
        bool again = true;
        while (again)
        {
            again = false;
            for (int row=_size-2; row>-1; --row)
            {
                if ((_tile[row][col] != 0) && (_tile[row+1][col] == 0))
                {
                    _tile[row+1][col] = _tile[row][col];
                    _tile[row][col] = 0;
                    again = true;
                }
            }
        }
        for (int row=_size-1; row>0; --row)
        {
            if (_tile[row][col] == 0)
            {
                continue;
            }
            else if (_tile[row][col] == _tile[row-1][col])
            {
                _tile[row][col] *= 2;
                if (_tile[row][col] > _greatestNum)
                {
                    _greatestNum = _tile[row][col];
                }
                _tile[row-1][col] *= 0;
                _numEmpty++;
                --row;
            }
        }
        again = true;
        while (again)
        {
            again = false;
            for (int row=_size-2; row>-1; --row)
            {
                if ((_tile[row][col] != 0) && (_tile[row+1][col] == 0))
                {
                    _tile[row+1][col] = _tile[row][col];
                    _tile[row][col] = 0;
                    again = true;
                }
            }
        }
    }

    Seed();
}

bool Grid::TestUp() const
{
    for (int col=0; col<_size; ++col)
    {
        for (int row=1; row<_size; ++row)
        {
            if ((_tile[row][col] != 0) && (_tile[row-1][col] == 0))
            {
                return true;
            }
        }
    }
    for (int col=0; col<_size; ++col)
    {
        for (int row=0; row<_size-1; ++row)
        {
            if (_tile[row][col] == 0)
            {
                continue;
            }
            if (_tile[row][col] == _tile[row+1][col])
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

    for (int col=0; col<_size; ++col)
    {
        bool again = true;
        while (again)
        {
            again = false;
            for (int row=1; row<_size; ++row)
            {
                if ((_tile[row][col] != 0) && (_tile[row-1][col] == 0))
                {
                    _tile[row-1][col] = _tile[row][col];
                    _tile[row][col] = 0;
                    again = true;
                }
            }
        }
        for (int row=0; row<_size-1; ++row)
        {
            if (_tile[row][col] == 0)
            {
                continue;
            }
            else if (_tile[row][col] == _tile[row+1][col])
            {
                _tile[row][col] *= 2;
                if (_tile[row][col] > _greatestNum)
                {
                    _greatestNum = _tile[row][col];
                }
                _tile[row+1][col] *= 0;
                _numEmpty++;
                ++row;
            }
        }
        again = true;
        while (again)
        {
            again = false;
            for (int row=1; row<_size; ++row)
            {
                if ((_tile[row][col] != 0) && (_tile[row-1][col] == 0))
                {
                    _tile[row-1][col] = _tile[row][col];
                    _tile[row][col] = 0;
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
    int position = rand() % _numEmpty;

    for (int row=0; row<_size; ++row)
    {
        for (int col=0; col<_size; ++col)
        {
            if (_tile[row][col] == 0)
            {
                if (position == 0)
                {
                    _tile[row][col] = newValue;
                    --_numEmpty;
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
    int numDigits = getNumDigits(_numGoal);
    move(0, 0);
    addch(ACS_ULCORNER);
    for (int col=0; col<_size; ++col)
    {
        for (int digit=0; digit<numDigits; ++digit)
        {
            addch(ACS_HLINE);
        }
        if (col == _size-1)
        {
            addch(ACS_URCORNER);
        }
        else
        {
            addch(ACS_TTEE);
        }
    }
    for (int row=0; row<_size; ++row)
    {
        move(row*2+1, 0);
        addch(ACS_VLINE);
        for (int col=0; col<_size; ++col)
        {
            for (int digit=0; digit<numDigits; ++digit)
            {
                printw(" ");
            }
            addch(ACS_VLINE);
        }
        if (row == _size-1)
        {
            move(row*2+2, 0);
            addch(ACS_LLCORNER);
            for (int col=0; col<_size; ++col)
            {
                for (int digit=0; digit<numDigits; ++digit)
                {
                    addch(ACS_HLINE);
                }
                if (col == _size-1)
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
            for (int col=0; col<_size; ++col)
            {
                for (int digit=0; digit<numDigits; ++digit)
                {
                    addch(ACS_HLINE);
                }
                if (col == _size-1)
                {
                    addch(ACS_RTEE);
                }
                else
                {
                    addch(ACS_PLUS);
                }
            }
        }
        for (int col=0; col<_size; ++col)
        {
            move(row*2+1, col*5+1);

            if (_tile[row][col] != 0)
            {
                printw("%d", _tile[row][col]);
            }
        }
    }
    mvprintw(_size*2+1,0, "Try #: %d", _numTries);
    mvprintw(_size*2+2,0, "Press 'r' to restart.");
    mvprintw(_size*2+3,0, "Press 'q' to quit.");
}

void Grid::Restart()
{
    ++_numTries;

    _numEmpty = _size*_size;
    _greatestNum = 0;

    for(int row=0; row<_size; ++row)
    {
        for(int col=0; col<_size; ++col)
        {
            _tile[row][col] = 0;
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
        mvprintw(_size*2+4,0, "Game over.");
        return false;
    }

    if (_greatestNum == _numGoal)
    {
        mvprintw(_size*2+4,0, "You win.");
        getch();
        endwin();
        exit(0);
    }

    return true;
}

int Grid::getNumDigits(unsigned x) const
{
    std::string s = std::to_string(x);
    return s.length();
}
