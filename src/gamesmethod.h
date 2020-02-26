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
    virtual void pressTab();
    virtual void pressEnter();
    virtual void pressTrojuholnik();
    virtual void pressKocka();
    virtual void pressGulicka();
};

#endif // GAMESMETHOD_H
