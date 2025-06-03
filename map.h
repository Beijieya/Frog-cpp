#pragma once
#include <vector>
#include <iostream>
#include "Config.h"

class Map {
    int  W, H;
    int* R;
    int  score = 0;
    std::vector<std::vector<char>> g, g0;

public:
    Map(int w,int h,int* r);

    void draw(int s,int lives,int t);
    bool setXY(int x,int y,char c);
    bool isObstacle(int x,int y);
};
