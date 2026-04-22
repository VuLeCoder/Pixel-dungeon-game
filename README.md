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

## 🎮 Gameplay

Game hoạt động theo cơ chế **turn-based system**:

- Người chơi thực hiện 1 hành động → hệ thống xử lý lượt
- Sau đó quái sẽ hành động
- Mọi thứ đều diễn ra theo lượt, không có real-time combat


## 🎹 Điều khiển

| Phím | Hành động |
|------|----------|
| Q / W / E / A / D / Z / X / C | Di chuyển |
| (1 hành động) | Tương ứng 1 lượt |
| S - (Wait / Skip turn) | Bỏ lượt |


## 🧠 Hệ thống gameplay

### 👁️ Field of View (FOV)
- Người chơi chỉ nhìn thấy khu vực trong tầm nhìn
- Vùng ngoài FOV sẽ bị che khuất / ẩn đi
- Tạo cảm giác khám phá dungeon

### 🤖 AI quái vật
- Quái có thể phát hiện người chơi trong phạm vi nhất định
- Khi phát hiện → chuyển sang trạng thái truy đuổi
- Có logic hành vi theo lượt

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

