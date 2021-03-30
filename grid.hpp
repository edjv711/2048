#pragma once

struct Grid
{
    Grid(int s=4);
    ~Grid();

    bool TestLeft() const;
    bool TestRight() const;
    bool TestUp() const;
    bool TestDown() const;

    void Left();
    void Right();
    void Up();
    void Down();

    void Seed(bool check=true);
    void Draw();
    void Restart();
    bool Check();
    void Start();

private:
    int getNumDigits(unsigned x) const;

    int _size;
    int _numEmpty;
    int _greatestNum;
    int _numGoal;
    int _numTries;
    int** _tile;
};
