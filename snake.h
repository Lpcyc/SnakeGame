#pragma once
#include "gameobject.h"
#include <deque>

// ============================================
// 鐭ヨ瘑鐐癸細铏氬熀绫?(Virtual Base Class)
// --------------------------------------------
// Snake绫诲悓鏃剁户鎵縂ameObject鍜孖Renderable涓や釜铏氬熀绫汇€?// 濡傛灉灏嗘潵鏈夊叾浠栫被涔熺户鎵胯繖涓や釜鍩虹被锛屽苟涓旀煇涓被鍚屾椂缁ф壙Snake鍜孎ood锛?// 浣跨敤virtual缁ф壙鍙互纭繚GameObject鍜孖Renderable鍦ㄦ渶缁堟淳鐢熺被涓彧瀛樺湪涓€浠姐€?// ============================================

class Snake : virtual public GameObject, virtual public IRenderable {
public:
    // 灏嗘灇涓剧Щ鍒?public 浠ヤ究 Game 绫讳娇鐢?    enum Direction { UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4 };
    
private:
    std::deque<std::pair<int, int>> body;
    char renderChar = 'O';
    
    Direction dir = RIGHT;
    
    std::pair<int, int> prevTail;
    
public:
    // ============================================
    // 鐭ヨ瘑鐐癸細鏋勯€犲嚱鏁伴噸杞?(Constructor Overloading)
    // --------------------------------------------
    // 鎻愪緵澶氱鍒濆鍖栨柟寮忥細
    // 1. 榛樿鏋勯€犲嚱鏁帮細鍒涘缓榛樿闀垮害鐨勮泧
    // 2. 甯﹀湴鍥惧弬鏁扮殑鏋勯€犲嚱鏁帮細鍦ㄥ湴鍥句腑蹇冨垱寤鸿泧
    // 3. 甯﹂暱搴﹀弬鏁扮殑鏋勯€犲嚱鏁帮細鑷畾涔夊垵濮嬮暱搴?    // 4. 甯﹁嚜瀹氫箟娓叉煋瀛楃鐨勬瀯閫犲嚱鏁帮細浣跨敤鑷畾涔夊瓧绗︽樉绀鸿泧
    // ============================================
    
    // 榛樿鏋勯€犲嚱鏁?    Snake();
    
    // 甯﹀湴鍥惧楂樼殑鏋勯€犲嚱鏁?    Snake(int width, int height);
    
    // 甯﹀湴鍥惧楂樺拰鍒濆闀垮害鐨勬瀯閫犲嚱鏁?    Snake(int width, int height, int initialLength);
    
    // 甯﹀湴鍥惧楂樸€佸垵濮嬮暱搴﹀拰鑷畾涔夋覆鏌撳瓧绗︾殑鏋勯€犲嚱鏁?    Snake(int width, int height, int initialLength, char customChar);
    
    // ============================================
    // 鐭ヨ瘑鐐癸細铏氭瀽鏋勫嚱鏁?(Virtual Destructor)
    // --------------------------------------------
    // 褰撶被鐢ㄤ綔鍩虹被鏃讹紝鏋愭瀯鍑芥暟搴旇澹版槑涓簐irtual銆?    // 杩欐牱閫氳繃鍩虹被鎸囬拡鍒犻櫎娲剧敓绫诲璞℃椂锛屼細鍏堣皟鐢ㄦ淳鐢熺被鏋愭瀯鍑芥暟锛?    // 鍐嶈皟鐢ㄥ熀绫绘瀽鏋勫嚱鏁帮紝纭繚璧勬簮姝ｇ‘閲婃斁銆?    // ============================================
    virtual ~Snake();
    
    // 铏氬嚱鏁板疄鐜?- 鍔ㄦ€佸叧鑱?    void render() const override;
    std::pair<int, int> getPosition() const override;
    bool isAtPosition(int x, int y) const override;
    char getRenderChar() const override;
    
    void pushHead(std::pair<int, int> newHead);
    void popTail();
    int getLength() const;
    bool isOccupying(int x, int y) const;
    std::pair<int, int> showHead() const;
    std::pair<int, int> getTail() const;
    Direction getDir() const;
    void setDir(Direction dir);
    bool logic(int width, int height, int& score);
    
    // 鑾峰彇涓婁竴娆″垹闄ょ殑灏惧反浣嶇疆
    std::pair<int, int> getPrevTail() const;
    
    // ============================================
    // 鐭ヨ瘑鐐癸細鍙嬪厓鍑芥暟 (Friend Function)
    // --------------------------------------------
    // 鍙嬪厓鍑芥暟涓嶆槸绫荤殑鎴愬憳鍑芥暟锛屼絾鍙互璁块棶绫荤殑绉佹湁鍜屼繚鎶ゆ垚鍛樸€?    // 杩欓噷澹版槑Game绫讳负鍙嬪厓锛屽厑璁窯ame绫荤洿鎺ヨ闂甋nake鐨勭鏈夌姸鎬併€?    // 鍙嬪厓鍏崇郴鏄崟鍚戠殑锛屼笉缁ф壙锛屼笉浼犻€掋€?    // ============================================
    friend class Game;
    
    // 鍙嬪厓鍑芥暟锛氶噸杞借緭鍑鸿繍绠楃
    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);
};
