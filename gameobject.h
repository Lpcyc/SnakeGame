#pragma once
#include <utility>
#include <iostream>

// ============================================
// 鐭ヨ瘑鐐癸細铏氬熀绫?(Virtual Base Class)
// --------------------------------------------
// 铏氬熀绫荤敤浜庤В鍐宠彵褰㈢户鎵块棶棰橈紙Diamond Problem锛夈€?// 褰撲袱涓淳鐢熺被缁ф壙鑷悓涓€涓熀绫伙紝鑰岀涓変釜绫诲張鍚屾椂缁ф壙杩欎袱涓淳鐢熺被鏃讹紝
// 濡傛灉涓嶄娇鐢ㄨ櫄缁ф壙锛屼細瀵艰嚧鍩虹被鍦ㄦ渶缁堟淳鐢熺被涓瓨鍦ㄤ袱浠藉壇鏈紝浜х敓浜屼箟鎬с€?// 
// 浣跨敤 virtual 缁ф壙鍚庯紝铏氬熀绫荤殑鎴愬憳鍦ㄦ渶缁堟淳鐢熺被涓彧鏈変竴浠藉壇鏈紝
// 鐢辨渶缁堟淳鐢熺被璐熻矗鍒濆鍖栵紝閬垮厤浜嗘暟鎹啑浣欏拰璁块棶鍐茬獊銆?// ============================================

class GameObject {
public:
    // 铏氭瀽鏋勫嚱鏁?- 鐭ヨ瘑鐐癸細纭繚閫氳繃鍩虹被鎸囬拡鍒犻櫎娲剧敓绫诲璞℃椂姝ｇ‘閲婃斁璧勬簮
    virtual ~GameObject() = default;
    
    // 绾櫄鍑芥暟 - 鐭ヨ瘑鐐癸細鍔ㄦ€佸叧鑱旓紙Dynamic Binding锛?    // 铏氬嚱鏁板厑璁歌繍琛屾椂鏍规嵁瀵硅薄鐨勫疄闄呯被鍨嬭皟鐢ㄥ搴旂殑鍑芥暟瀹炵幇锛?    // 鑰屼笉鏄湪缂栬瘧鏃舵牴鎹寚閽堢被鍨嬪喅瀹氥€傝繖鏄鎬佺殑鏍稿績鏈哄埗銆?    virtual void render() const = 0;
    virtual std::pair<int, int> getPosition() const = 0;
    virtual bool isAtPosition(int x, int y) const = 0;
};

// 鍙覆鏌撴帴鍙?- 浣跨敤铏氱户鎵块伩鍏嶈彵褰㈢户鎵块棶棰?class IRenderable {
public:
    virtual ~IRenderable() = default;
    virtual char getRenderChar() const = 0;
};

// 椋熺墿绫?- 浣跨敤铏氱户鎵胯嚜GameObject鍜孖Renderable
class Food : virtual public GameObject, virtual public IRenderable {
private:
    std::pair<int, int> position;
    char renderChar = 'F';
    
public:
    // 鏋勯€犲嚱鏁伴噸杞?- 鐭ヨ瘑鐐癸細鍚屽悕鍑芥暟閫氳繃鍙傛暟鍒楄〃涓嶅悓瀹炵幇涓嶅悓鍒濆鍖栨柟寮?    Food(); // 榛樿鏋勯€犲嚱鏁?    Food(int x, int y); // 甯﹀潗鏍囧弬鏁扮殑鏋勯€犲嚱鏁?    Food(int x, int y, char customChar); // 甯﹀潗鏍囧拰鑷畾涔夊瓧绗︾殑鏋勯€犲嚱鏁?    
    ~Food() override = default;
    
    void render() const override;
    std::pair<int, int> getPosition() const override;
    bool isAtPosition(int x, int y) const override;
    char getRenderChar() const override;
    
    void setPosition(int x, int y);
    
    // 鍙嬪厓鍑芥暟澹版槑 - 鐭ヨ瘑鐐癸細鍏佽闈炴垚鍛樺嚱鏁拌闂被鐨勭鏈?淇濇姢鎴愬憳
    // 鍙嬪厓鍑芥暟鎵撶牬浜嗗皝瑁咃紝浣嗘彁渚涗簡鐏垫椿鐨勮闂帶鍒讹紝甯哥敤浜庤繍绠楃閲嶈浇
    friend std::ostream& operator<<(std::ostream& os, const Food& food);
};

// 铔囩被鍓嶇疆澹版槑
class Snake;
