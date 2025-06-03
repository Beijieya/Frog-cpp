#include "GameObject.h"

Map* GameObject::mp = nullptr;

GameObject::GameObject(int X,int Y,char c) : x(X), y(Y), icon(c)
{
    if (mp) mp->setXY(x, y, icon);
}

bool GameObject::setXY(int X,int Y)
{
    x = X;  y = Y;
    return mp ? mp->setXY(x, y, icon) : false;
}
