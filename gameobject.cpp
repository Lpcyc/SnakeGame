#include "gameobject.h"
#include <iostream>

// ============================================
// 鐭ヨ瘑鐐癸細鏋勯€犲嚱鏁伴噸杞?(Constructor Overloading)
// --------------------------------------------
// 鏋勯€犲嚱鏁伴噸杞藉厑璁哥被瀹氫箟澶氫釜鍚屽悕鏋勯€犲嚱鏁帮紝浣嗗弬鏁板垪琛ㄤ笉鍚屻€?// 杩欐彁渚涗簡澶氱瀵硅薄鍒涘缓鏂瑰紡锛岄€傚簲涓嶅悓鍦烘櫙鐨勯渶姹傘€?// 
// 閲嶈浇瑙勫垯锛?// 1. 鍙傛暟鏁伴噺涓嶅悓
// 2. 鍙傛暟绫诲瀷涓嶅悓
// 3. 鍙傛暟椤哄簭涓嶅悓
// ============================================

// 榛樿鏋勯€犲嚱鏁?Food::Food() : position({0, 0}), renderChar('F') {}

// 甯﹀潗鏍囧弬鏁扮殑鏋勯€犲嚱鏁?Food::Food(int x, int y) : position({x, y}), renderChar('F') {}

// 甯﹀潗鏍囧拰鑷畾涔夊瓧绗︾殑鏋勯€犲嚱鏁?Food::Food(int x, int y, char customChar) : position({x, y}), renderChar(customChar) {}

void Food::render() const {
    // 瀹為檯娓叉煋鐢盙ame绫绘帶鍒讹紝杩欓噷鎻愪緵鎺ュ彛
}

std::pair<int, int> Food::getPosition() const {
    return position;
}

bool Food::isAtPosition(int x, int y) const {
    return position.first == x && position.second == y;
}

char Food::getRenderChar() const {
    return renderChar;
}

void Food::setPosition(int x, int y) {
    position = {x, y};
}

// 鍙嬪厓鍑芥暟瀹炵幇 - 鍙互鐩存帴璁块棶Food鐨勭鏈夋垚鍛榩osition鍜宺enderChar
std::ostream& operator<<(std::ostream& os, const Food& food) {
    os << "Food at (" << food.position.first << ", " << food.position.second << ")";
    return os;
}
