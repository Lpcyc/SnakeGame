#pragma once
#include "gameobject.h"
#include "snake.h"
#include <utility>
#include <vector>
#include <memory>

// ============================================
// 鐭ヨ瘑鐐癸細鍔ㄦ€佸叧鑱?(Dynamic Binding / Polymorphism)
// --------------------------------------------
// Game绫讳娇鐢℅ameObject鎸囬拡/寮曠敤鏉ョ鐞嗘父鎴忓璞°€?// 閫氳繃铏氬嚱鏁板疄鐜拌繍琛屾椂澶氭€侊紝璋冪敤姝ｇ‘鐨勫璞″疄鐜般€?// ============================================

class Game {
private:
    int width = 50;
    int height = 25;
    int score = 0;
    bool isGameOver = false;
    int defaultSpeed = 3;
    int speed = 3;
    
    // 浣跨敤shared_ptr绠＄悊娓告垙瀵硅薄锛屾紨绀哄姩鎬佸叧鑱?    std::shared_ptr<Snake> snake;
    std::shared_ptr<Food> food;
    
    // 浣跨敤鍩虹被鎸囬拡瀛樺偍娓告垙瀵硅薄锛岀敤浜庢紨绀哄姩鎬佸叧鑱?    std::vector<std::shared_ptr<GameObject>> gameObjects;
    
public:
    enum GameState { MENU, PLAYING, GAMEOVER, PAUSE, EXIT };
    GameState state = MENU;
    static const int delays[7];
    int SPEED_LEVEL_MIN = 1;
    static constexpr int SPEED_LEVEL_MAX = 7;
    
    // ============================================
    // 鐭ヨ瘑鐐癸細鏋勯€犲嚱鏁伴噸杞?(Constructor Overloading)
    // --------------------------------------------
    // 鎻愪緵澶氱鍒濆鍖栨柟寮忥細
    // 1. 榛樿鏋勯€犲嚱鏁帮細浣跨敤榛樿鍦板浘澶у皬
    // 2. 甯﹀湴鍥惧弬鏁扮殑鏋勯€犲嚱鏁帮細鑷畾涔夊湴鍥惧ぇ灏?    // 3. 甯﹀湴鍥惧拰閫熷害鐨勬瀯閫犲嚱鏁帮細鑷畾涔夊湴鍥惧ぇ灏忓拰鍒濆閫熷害
    // ============================================
    Game();
    Game(int w, int h);
    Game(int w, int h, int initialSpeed);
    
    // ============================================
    // 鐭ヨ瘑鐐癸細铏氭瀽鏋勫嚱鏁?(Virtual Destructor)
    // --------------------------------------------
    // 铏界劧Game涓嶆槸鍩虹被锛屼絾浣滀负涓€涓鐞嗗姩鎬佸璞＄殑绫伙紝
    // 浣跨敤铏氭瀽鏋勫嚱鏁版槸鑹ソ鐨勮璁′範鎯紝纭繚娲剧敓绫绘纭噴鏀捐祫婧愩€?    // ============================================
    virtual ~Game();
    
    void generateFood();
    void reset();
    GameState menu();
    GameState playing();
    GameState pause();
    GameState End();
    
    // 娣诲姞娓告垙瀵硅薄鍒扮鐞嗗垪琛?    void addGameObject(std::shared_ptr<GameObject> obj);
    
    // 娓叉煋鎵€鏈夋父鎴忓璞?- 婕旂ず鍔ㄦ€佸叧鑱?    void renderAllObjects() const;
    
private:
    void logic();
    void draw();
    void input();
    void getConsoleSize(int&, int&);
    void drawBorder();
    void gotoxy(int, int);
};
