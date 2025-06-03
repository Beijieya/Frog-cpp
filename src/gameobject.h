#pragma once
#include "Map.h"

/*---------------------------------------------------------
 | GameObject ‧ 所有遊戲物件的共同基底
 *--------------------------------------------------------*/
class GameObject {
protected:
    int  x, y;        // 目前座標
    char icon;        // 在地圖上顯示的字元
    static Map* mp;   // 指向全域地圖（由 main 設定）

public:
    GameObject(int X, int Y, char c);
    virtual ~GameObject() = default;

    /* 必須由子類實作的行為 —— 回傳 false 可用來告知「物件要被移除」或「關卡結束」 */
    virtual bool move() = 0;

    /* 共同存取器 */
    int  X()    const { return x;    }
    int  Y()    const { return y;    }
    char Icon() const { return icon; }

    /* 移動／畫圖：兩個參數即可，自帶 icon */
    bool setXY(int X, int Y);

    /* 由 main 於程式啟動時呼叫一次，設定地圖指標 */
    static void setMap(Map* m) { mp = m; }
};
