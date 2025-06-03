#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <conio.h>          // _getch()

#include "Config.h"
#include "Map.h"
#include "Entity.h"
#include "Vehicle.h"

/* ---- 固定參數 ---- */
constexpr int TIME_LIMIT     = 60;   // 秒
constexpr int INIT_LIVES     = 3;
constexpr int BONUS_MAX      = 3;
constexpr int BONUS_TTL      = 50;   // frame ≈ 15 s
constexpr int BONUS_SPAWN_FR = 5;    // 每 5 frame 嘗試生成

inline int rnd(int l, int r) { return l + rand() % (r - l + 1); }

/* ==================================================== */
int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    /* ── 互動輸入難度 ── */
    std::string difficulty;
    do {
        std::cout << "Difficulty (easy/hard)? " << std::flush;
        std::getline(std::cin, difficulty);
    } while (difficulty != "easy" && difficulty != "hard");

    const int carSp  = (difficulty == "hard") ? 2 : 1;
    const int motoSp = (difficulty == "hard") ? 1 : 0;

    /* 1 = 安全區，0 = 道路 */
    int R[MAP_HEIGHT] = {1, 1, 0, 0, 1,
                         0, 0, 1, 0, 0,
                         1, 0, 0, 1, 1};

    /* ================= 可能多次重新開局 ================= */
    while (true)
    {
        Map map(MAP_WIDTH, MAP_HEIGHT, R);
        GameObject::setMap(&map);

        std::vector<GameObject*> objs;
        auto* frog = new Frog(MAP_WIDTH / 2, MAP_HEIGHT - 1, INIT_LIVES);
        objs.push_back(frog);

        /* 障礙與車輛 ------------------------------------------------- */
        for (int i = 0; i < MAP_HEIGHT; ++i) {
            objs.push_back(new Obstacle(rnd(0, MAP_WIDTH - 1), i));

            if (R[i] == 0) {                           // 道路才放車
                int dir   = (i % 2 ? 1 : -1);          // 偶數列向左、奇數列向右
                int start = (dir == 1 ? 0 : MAP_WIDTH - 1);
                int spd   = (i % 2 == 0) ? carSp : motoSp;
                if (spd == 0) continue;

                int d = dir * spd;
                objs.push_back(
                    (i % 2 == 0)
                        ? static_cast<GameObject*>(new Car(start, i, 'C', d))
                        : static_cast<GameObject*>(new Moto(start, i, 'M', d)));
            }
        }

        auto begin = std::chrono::steady_clock::now();
        int frame = 0;
        int timeLeft = TIME_LIMIT;

        /* ------------------- 單局主迴圈 ------------------- */
        while (true)
        {
            /* -- 時間 -- */
            int elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                              std::chrono::steady_clock::now() - begin)
                              .count();
            timeLeft = TIME_LIMIT - elapsed;

            /* -- 嘗試生成 Bonus -- */
            if (frame % BONUS_SPAWN_FR == 0) {
                int active = 0;
                for (auto* o : objs)
                    if (dynamic_cast<Bonus*>(o)) ++active;

                if (active < BONUS_MAX) {
                    int row = rnd(1, MAP_HEIGHT - 2);
                    if (R[row] == 1) {                 // 只在安全區生成
                        objs.push_back(
                            new Bonus(rnd(0, MAP_WIDTH - 1), row, BONUS_TTL));
                    }
                }
            }

            /* -- 逐物件 move，並刪除過期 Bonus -- */
            bool levelClear = false;
            for (auto it = objs.begin(); it != objs.end();) {
                if (!(*it)->move() && dynamic_cast<Frog*>(*it))
                    levelClear = true;

                if (auto* b = dynamic_cast<Bonus*>(*it); b && b->expired()) {
                    delete b;
                    it = objs.erase(it);
                } else {
                    ++it;
                }
            }

            /* -- 踩到 Bonus -- */
            for (auto it = objs.begin(); it != objs.end(); ++it) {
                if (auto* b = dynamic_cast<Bonus*>(*it);
                    b && frog->X() == b->X() && frog->Y() == b->Y()) {
                    frog->addScore(5);
                    delete b;
                    objs.erase(it);
                    break;
                }
            }

            /* -- 撞車扣命 -- */
            for (auto* o : objs) {
                if (o == frog) continue;
                if (frog->X() == o->X() && frog->Y() == o->Y()) {
                    if (dynamic_cast<Vehicle*>(o)) {
                        frog->collide();
                        std::this_thread::sleep_for(std::chrono::milliseconds(400));
                        break;
                    }
                }
            }

            /* -- 畫面刷新 -- */
            system("cls");          // Windows 清螢幕
            map.draw(frog->Score(), frog->Lives(), timeLeft);

            /* -- 過關 -- */
            if (levelClear) {
                std::cout << "\n\n== YOU WIN!! ==\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;              // 跳出單局迴圈
            }

            /* -- Game Over -- */
            if (timeLeft <= 0 || frog->Lives() <= 0) {
                std::cout << "\n\n=== GAME OVER ===\n";
                std::cout << "Score: " << frog->Score() << '\n';
                std::cout << "Press R to restart, others to exit.\n";
                char k = _getch();

                for (auto* o : objs) delete o;
                objs.clear();

                if (k != 'R' && k != 'r')
                    return 0;       // 離開程式
                else
                    break;          // 重新開局
            }

            ++frame;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }

        /* 清理物件，進入下一回合 */
        for (auto* o : objs) delete o;
        objs.clear();
    }
}
