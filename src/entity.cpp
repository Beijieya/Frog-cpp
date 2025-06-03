#include "Entity.h"
#include <conio.h>

/*── 固定障礙 ─────────────────────────*/
Obstacle::Obstacle(int x,int y) : GameObject(x,y,'O') {}
bool Obstacle::move() { return true; }

/*── Bonus ───────────────────────────*/
Bonus::Bonus(int x,int y,int ttlFrames)
    : GameObject(x,y,'B'), ttl(ttlFrames) {}

bool Bonus::move() {
    setXY(x,y);                  // 每幀重畫
    return --ttl > 0;            // 倒數
}

/*── Frog ────────────────────────────*/
Frog::Frog(int x,int y,int initLives)
    : GameObject(x,y,'F'),
    lives(initLives),
    visited(MAP_HEIGHT,false) {
    visited[y] = true;
}

bool Frog::move() {
    if (kbhit()) {
        int ox=x, oy=y; char k=getch(); if(k==-32) k=getch();
        if(k==72 && y>0)               y--;
        if(k==80 && y<MAP_HEIGHT-1)    y++;
        if(k==75 && x>0)               x--;
        if(k==77 && x<MAP_WIDTH-1)     x++;

        if (mp->isObstacle(x,y)) { x=ox; y=oy; }
        if (!visited[y]) { ++score; visited[y]=true; }
    }
    setXY(x,y);

    return y!=0;                        // 抵達最上排 → 回傳 false
}

/*── Frog ────────────────────────────*/
void Frog::collide()
{
    if (--lives <= 0)                       // 沒命 → game-over 邏輯照舊
        return;

    /*── 重設分數與已拜訪列 ───────────*/
    score = 0;
    std::fill(visited.begin(), visited.end(), false);

    /*── 回到起點並標示目前列已訪問 ──*/
    x = MAP_WIDTH / 2;
    y = MAP_HEIGHT - 1;
    visited[y] = true;
}

