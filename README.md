# Frog-cpp🐸 – Console Version

113-2 程式設計期末專題  
> 使用 C++ 製作的小型 Console 遊戲  
> 實作內容包含：即時輸入、物件導向、Bonus 生成功能、勝利／失敗判定

---

## 🔧 編譯方式（for Windows）
建議使用 g++ (MinGW 或 WSL 環境) 編譯：

```bash
g++ -std=c++17 -Wall -O2 -pthread *.cpp -o frogger
./frogger
```
🎮 遊戲玩法說明
鍵位	功能說明
↑ ↓ ← →	控制青蛙移動
F	青蛙
C / M	汽車 / 機車，碰撞會扣命
B	Bonus，吃到加 5 分

每回合限時 60 秒

青蛙要從地圖底部走到最上方才能過關

被車撞或時間歸零 → Game Over

過關會顯示 "YOU WIN!!"，否則 "GAME OVER"

🧱 程式架構
GameObject: 抽象父類，所有物件共用

Map: 管理地圖資料與畫面重繪

Vehicle: 車輛（車／機車）的基底類

Frog: 玩家控制的角色

Bonus: 吃分加分的物件

UML 結構圖詳見 doc/class_diagram.png，簡報在 doc/ 目錄下。

🧪 特色功能
使用 <conio.h> 實作鍵盤即時輸入（getch()）

std::vector<GameObject*> 管理所有物件

使用 chrono 控制倒數計時與 Bonus 存活時間

每隔 5 frame 嘗試生成 Bonus，最多 3 個

不同難度會影響車速（easy / hard）

📁 專案檔案結構
project/
├─ src/              # 所有程式碼檔案
│  ├─ main.cpp
│  ├─ Map.cpp / .h
│  ├─ Entity.cpp / .h
│  ├─ Vehicle.cpp / .h
├─ doc/              # 說明用文件
│  ├─ class_diagram.png
│  └─ slides.pdf
├─ assets/           # Demo 錄影與截圖
│  ├─ demo.mp4
│  └─ screenshot.png
└─ README.md


📌 備註
遊戲採 Console 輸出，非圖形化介面

無使用第三方套件

編譯需支援 C++17
