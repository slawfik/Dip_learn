#ifndef GAMESMETHOD_H
#define GAMESMETHOD_H


class GamesMethod
{
public:
    GamesMethod();
    virtual ~GamesMethod();

    virtual void moveUp();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveRight();
    virtual void pressEnter();
    virtual void pressTab();
};

#endif // GAMESMETHOD_H
