#pragma once
#include "GameObject.h"
#include <vector>

/*──── Obstacle ─────────────────────*/
class Obstacle : public GameObject {
public:
    Obstacle(int x,int y);
    bool move() override;
};

/*──── Bonus ────────────────────────*/
class Bonus : public GameObject {
    int ttl;                               // 剩餘 frame
public:
    Bonus(int x,int y,int ttlFrames);
    bool move() override;                  // 每幀重畫 & 倒數
    bool expired() const { return ttl<=0; }
};

/*──── Frog ─────────────────────────*/
class Frog : public GameObject {
    int score = 0, lives;
    std::vector<bool> visited;
public:
    Frog(int x,int y,int initLives);

    bool move() override;                  // 回傳 false → 抵達終點
    void collide();                        // 撞車 -1 命
    void addScore(int d){ score += d; }

    int Score() const { return score; }
    int Lives() const { return lives; }
};
