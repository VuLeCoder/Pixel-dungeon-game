# 🧩 Pixel Dungeon (C++ + Raylib)

Một phiên bản nhỏ của [*Pixel Dungeon*](https://store.steampowered.com/app/365900/Pixel_Dungeon/?l=vietnamese) do nhóm mình làm lại tương tự bằng **C++** sử dụng **Raylib**. Game thuộc thể loại **roguelike turn-based**, nơi bạn khám phá dungeon, chiến đấu với quái và sống sót.

---

## 📁 Cấu trúc project
```
├── assets/                 # Tài nguyên game (ảnh, animation, map...)
├── src/                    # Source code chính
│   ├── engine/             # Core engine (scene, asset, effect...)
│   ├── world/              # World, entity, system
│   ├── scenes/             # Các scene (menu, game, idle...)
│   ├── ui/                 # UI hệ thống
│   └── main.cpp
├── external/
│   └── raylib/             # Thư viện raylib
├── CMakeLists.txt
└── README.md
```
---

## ⚙️ Yêu cầu
Trước khi build project, bạn cần cài:
- C++ compiler hỗ trợ C++17 (GCC / Clang / MSVC)
- CMake >= 3.15
- Git (để clone project)
- raylib (đã được include dưới dạng subdirectory) 

---

## 🚀 Cách build & chạy

### 1. Clone project
```bash
git clone https://github.com/VuLeCoder/Pixel-dungeon-game
cd Pixel-dungeon-game
```
### 2. Clone thư viện raylib
```bash
mkdir external
git clone https://github.com/raysan5/raylib.git external/raylib
```
### 3. Compile game
```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```
### 4. Run game
Chạy tệp .exe trong thư mục *build/*, thường sẽ là
```bash
PIXEL_DUNGEON.exe
```

