#include "gamesmethod.h"
#include "qdebug.h"

#define DEBUG

GamesMethod::GamesMethod()
{

}

GamesMethod::~GamesMethod()
{

}

void GamesMethod::moveUp()
{
  #ifdef DEBUG
    qDebug() << "parent up method";
  #endif
}

void GamesMethod::moveDown()
{
  #ifdef DEBUG
    qDebug() << "parent down method";
  #endif
}

void GamesMethod::moveLeft()
{
  #ifdef DEBUG
    qDebug() << "parent left method";
  #endif
}

void GamesMethod::moveRight()
{
  #ifdef DEBUG
    qDebug() << "parent right method";
  #endif
}

void GamesMethod::pressEnter()
{
  #ifdef DEBUG
    qDebug() << "parent enter method";
  #endif
}

void GamesMethod::pressTab()
{
  #ifdef DEBUG
    qDebug() << "parent tab method";
  #endif
}
