#ifndef GRID_HPP_123456789
#define GRID_HPP_123456789

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

    int getNumDigits(unsigned int x) const;
private:
    int size;
    int numEmpty;
    int greatestNum;
    int numGoal;
    unsigned long int numTries;
    int** tile;
};

#endif
