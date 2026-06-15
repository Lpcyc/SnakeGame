# 璐悆铔囷紙鎺у埗鍙扮増锛?
涓€涓?C++ 鎺у埗鍙拌椽鍚冭泧娓告垙锛岄噸鐐瑰湪浜?*鏁版嵁缁撴瀯閫夋嫨**銆?*宸ョ▼鍖栬璁?*鍜?*鐘舵€佹満搴旂敤**鐨勭粌鎵嬮」鐩€?
## 閲嶆瀯鏂板鍐呭

鏈閲嶆瀯閲嶇偣娣诲姞浜嗕互涓?C++ 闈㈠悜瀵硅薄鏍稿績鐭ヨ瘑鐐癸細

- [鏋勯€犲嚱鏁伴噸杞絔(#1-鏋勯€犲嚱鏁伴噸杞?constructor-overloading)
- [铏氭瀽鏋勫嚱鏁癩(#2-铏氭瀽鏋勫嚱鏁?virtual-destructor)
- [鍙嬪厓鍑芥暟](#3-鍙嬪厓鍑芥暟-friend-function)
- [鍔ㄦ€佸叧鑱擼(#4-鍔ㄦ€佸叧鑱?dynamic-binding)
- [铏氬熀绫籡(#5-铏氬熀绫?virtual-base-class)

## 鍔熻兘

- **缁忓吀鐜╂硶涓庡弻杞ㄦ帶鍒?*锛氭敮鎸佹柟鍚戦敭鍜?WASD 鎺у埗锛屽悓鍚戣繛鎸夊彲鍔犻€熴€?- **鍔ㄦ€佺獥鍙ｄ笌鍦板浘閫傞厤**锛氬惎鍔ㄦ椂鑷姩妫€娴嬪綋鍓嶆帶鍒跺彴绐楀彛澶у皬锛屾敮鎸佺敤鎴疯嚜瀹氫箟鍦板浘瀹介珮锛屽苟鍐呯疆闃茶秺鐣岃嚜鍔ㄨ鍓繚鎶ゃ€?- **鐘舵€佹満鐢熷懡鍛ㄦ湡**锛氬寘鍚富鑿滃崟銆佹父鎴忎腑銆佹殏鍋溿€佹父鎴忕粨鏉熷畬鏁寸姸鎬佹祦杞€?- **闃插崱姝婚鐗╃敓鎴?*锛氬悗鏈熻泧韬彉闀挎椂涓嶄細鍑虹幇闅忔満鏁版寰幆锛屽叏灞忓崰婊℃椂瑙﹀彂"YOU WIN!"鑳滃埄鍒ゅ畾銆?- **鏋佽嚧娓叉煋浣撻獙**锛氱函灞€閮ㄥ埛鏂帮紝鏃?`system("cls")` 闂儊闂锛涚粨鏉熻嚜鍔ㄦ仮澶嶅厜鏍囷紝榛樿鏀寔 UTF-8 涓枃鏄剧ず銆?
## 杩愯鏂规硶

### 缂栬瘧
```bash
g++ -std=c++11 main.cpp game.cpp gameobject.cpp snake.cpp map.cpp -o snake.exe
```

鎴栦娇鐢?CMake锛?```bash
mkdir build && cd build
cmake ..
make
```

### 杩愯
```bash
snake.exe
```

### 鐜瑕佹眰

- Windows 鎿嶄綔绯荤粺
- MinGW / Visual Studio 缂栬瘧鍣?- 鎺у埗鍙扮獥鍙ｅ缓璁笉灏忎簬 50脳25

## 鎿嶄綔璇存槑

| 鎸夐敭 | 鍔熻兘 |
| --- | --- |
| `鈫慲 `鈫揱 `鈫恅 `鈫抈 | 绉诲姩鏂瑰悜锛堟帹鑽愶紝鏃犺緭鍏ユ硶鍐茬獊锛?|
| `W` `A` `S` `D` | 绉诲姩鏂瑰悜锛堟敞鎰忛渶鍦ㄨ嫳鏂囪緭鍏ユ硶涓嬶級 |
| `绌烘牸 (Space)` | 鏆傚仠 / 鎭㈠娓告垙 |
| 鍚屽悜鏂瑰悜閿?| 娓告垙鍔犻€?|
| 鍙嶅悜鏂瑰悜閿?| 娓告垙鍑忛€燂紙鎯╃綒鏈哄埗锛?|
| `?` (`Shift`+`/` ) | 娓告垙涓€斿己鍒惰繑鍥炰富鑿滃崟 |
| `X` | 閫€鍑烘父鎴?/ 鍦ㄦ殏鍋滈〉闈㈤€€鍥炶彍鍗?|

## 鎶€鏈疄鐜颁笌璁捐鍐崇瓥锛堥潰璇曞噯澶囷級

**Q1锛氫负浠€涔堢敤 `deque` 鑰屼笉鏄?`vector` 鎴?`list`锛?*
- `vector` 澶撮儴鎻掑叆鏃堕棿澶嶆潅搴︿负 O(n)锛屼笉閫傚悎棰戠箒鍦ㄥご閮ㄦ搷浣滅殑璐悆铔囧満鏅€?- `list` 涓ょ鎿嶄綔 O(1)锛屼絾鍐呭瓨涓嶈繛缁紝瀵?CPU 缂撳瓨涓嶅弸濂斤紝涓旀瘡涓妭鐐瑰涓や釜鎸囬拡鐨勫唴瀛樺紑閿€銆?- `deque` 涓ょ鎿嶄綔 O(1)锛屽唴瀛樺垎娈佃繛缁紝鏈€瀹岀編濂戝悎璐悆铔?澶村灏惧噺"鐨勬粦鍔ㄩ渶姹傘€?
**Q2锛氬浣曞鐞嗘覆鏌撻棯鐑佷笌娈嬪奖闂锛?*
- **闃查棯鐑?*锛氭憭寮冧綆鏁堢殑鍏ㄥ眬娓呭睆 `system("cls")`锛屼娇鐢?Windows API 鐨?`SetConsoleCursorPosition` 瀹氫綅鍏夋爣锛屽彧鍦ㄦ湁鍙樺寲鐨勫湴鏂硅緭鍑哄瓧绗︺€?- **娓呮畫褰?*锛氬湪 `logic()` 涓垹闄よ泧灏惧墠锛岄€氳繃 `deleteAbletail = snake.back()` 璁板綍鏃у熬宸翠綅缃€傚湪 `draw()` 娓叉煋鏃跺璇ュ潗鏍囪緭鍑轰竴娆＄┖鏍?" " 杩涜绮惧噯鎿﹂櫎銆?
**Q3锛氭父鎴忓悗鏈熻泧韬嚑涔庡崰婊″叏灞忔椂锛岄殢鏈虹敓鎴愰鐗╁崱姝绘€庝箞瑙ｅ喅锛?*
- 鏀惧純鏆村姏鐨勭函闅忔満鐚滃潗鏍囷紙While姝诲惊鐜娴嬶級锛岄噰鐢?*绌洪棿鏀堕泦娉?*銆?- 姣忔鐢熸垚椋熺墿鏃讹紝閬嶅巻鍦板浘鎺掓煡铔囪韩锛屽皢鎵€鏈夌┖闂插潗鏍囧瓨鍏?`std::vector<std::pair<int, int>> freeSpaces`銆傜劧鍚庣洿鎺ヤ粠 `freeSpaces` 涓?`rand()` 閫夊彇涓€涓笅鏍囥€?- 姝ゅ锛屽鏋滃彂鐜?`freeSpaces.empty()`锛屽垯椤虹悊鎴愮珷鍦拌Е鍙?娓告垙鑳滃埄"閫昏緫銆?
**Q4锛氫负浠€涔堝紩鍏ユ灇涓惧拰鐘舵€佹満锛?*
- 娓告垙鍖呭惈鑿滃崟銆佽繘琛屻€佹殏鍋溿€佺粨鏉熺瓑澶氫釜鐜妭锛屼娇鐢?`enum GameState` 閰嶅悎 `switch-case` 杩涜璋冨害锛岃涓诲嚱鏁?`main()` 閫昏緫鏋佸害绮剧畝銆?- 鍚勪釜鐘舵€佸皝瑁呬负鐙珛鐨勫嚱鏁帮紙濡?`showMenu`, `playing`, `isPause`, `gameEnd`锛夛紝瀹炵幇楂樺唴鑱氫綆鑰﹀悎锛屾柟渚垮悗鏈熺淮鎶ゅ拰鎵╁睍銆?
## C++ 鐭ヨ瘑鐐硅瑙?
### 1. 鏋勯€犲嚱鏁伴噸杞?(Constructor Overloading)

**浣嶇疆**锛歚game.h` (Game 绫?, `snake.h` (Snake 绫?, `gameobject.h` (Food 绫?

**姒傚康**锛氭瀯閫犲嚱鏁伴噸杞藉厑璁哥被瀹氫箟澶氫釜鍚屽悕鏋勯€犲嚱鏁帮紝浣嗗弬鏁板垪琛ㄤ笉鍚屻€傝繖鎻愪緵浜嗗绉嶅璞″垱寤烘柟寮忥紝閫傚簲涓嶅悓鍦烘櫙鐨勯渶姹傘€?
**浠ｇ爜绀轰緥**锛?```cpp
class Game {
public:
    Game();                          // 榛樿鏋勯€犲嚱鏁?    Game(int w, int h);              // 甯﹀湴鍥惧弬鏁扮殑鏋勯€犲嚱鏁?    Game(int w, int h, int speed);   // 甯﹀湴鍥惧拰閫熷害鐨勬瀯閫犲嚱鏁?};

// 浣跨敤绀轰緥锛?Game game1;              // 榛樿澶у皬
Game game2(80, 40);      // 鑷畾涔夊湴鍥?Game game3(80, 40, 5);   // 鑷畾涔夊湴鍥惧拰閫熷害
```

**閲嶈浇瑙勫垯**锛?- 鍙傛暟鏁伴噺涓嶅悓
- 鍙傛暟绫诲瀷涓嶅悓
- 鍙傛暟椤哄簭涓嶅悓

### 2. 铏氭瀽鏋勫嚱鏁?(Virtual Destructor)

**浣嶇疆**锛歚gameobject.h` (GameObject 绫?, `snake.h` (Snake 绫?, `game.h` (Game 绫?

**姒傚康**锛氬綋绫荤敤浣滃熀绫绘椂锛屾瀽鏋勫嚱鏁板簲璇ュ０鏄庝负 `virtual`銆傝繖鏍烽€氳繃鍩虹被鎸囬拡鍒犻櫎娲剧敓绫诲璞℃椂锛屼細鍏堣皟鐢ㄦ淳鐢熺被鏋愭瀯鍑芥暟锛屽啀璋冪敤鍩虹被鏋愭瀯鍑芥暟锛岀‘淇濊祫婧愭纭噴鏀俱€?
**浠ｇ爜绀轰緥**锛?```cpp
class GameObject {
public:
    virtual ~GameObject() = default;  // 铏氭瀽鏋勫嚱鏁?};

class Snake : virtual public GameObject {
public:
    virtual ~Snake() {  // 娲剧敓绫昏櫄鏋愭瀯鍑芥暟
        body.clear();   // 娓呯悊璧勬簮
    }
};

// 瀹夊叏鍒犻櫎锛?GameObject* obj = new Snake();
delete obj;  // 姝ｇ‘璋冪敤 Snake::~Snake() 鐒跺悗 GameObject::~GameObject()
```

**涓轰粈涔堥噸瑕?*锛?- 濡傛灉鍩虹被鏋愭瀯鍑芥暟涓嶆槸铏氬嚱鏁帮紝閫氳繃鍩虹被鎸囬拡鍒犻櫎娲剧敓绫诲璞℃椂锛屽彧浼氳皟鐢ㄥ熀绫绘瀽鏋勫嚱鏁帮紝瀵艰嚧娲剧敓绫昏祫婧愭硠婕忋€?
### 3. 鍙嬪厓鍑芥暟 (Friend Function)

**浣嶇疆**锛歚snake.h` (Snake 绫?, `gameobject.h` (Food 绫?

**姒傚康**锛氬弸鍏冨嚱鏁颁笉鏄被鐨勬垚鍛樺嚱鏁帮紝浣嗗彲浠ヨ闂被鐨勭鏈夊拰淇濇姢鎴愬憳銆傚弸鍏冨叧绯绘槸鍗曞悜鐨勶紝涓嶇户鎵匡紝涓嶄紶閫掋€?
**浠ｇ爜绀轰緥**锛?```cpp
class Snake {
private:
    std::deque<std::pair<int, int>> body;
    Direction dir;
    
public:
    // 澹版槑鍙嬪厓绫?    friend class Game;
    
    // 澹版槑鍙嬪厓鍑芥暟
    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);
};

// 鍙嬪厓鍑芥暟瀹炵幇 - 鍙互鐩存帴璁块棶绉佹湁鎴愬憳
std::ostream& operator<<(std::ostream& os, const Snake& snake) {
    os << "Snake length: " << snake.body.size();  // 璁块棶绉佹湁鎴愬憳 body
    return os;
}
```

**浣跨敤鍦烘櫙**锛?- 杩愮畻绗﹂噸杞斤紙濡?`<<` 杈撳嚭杩愮畻绗︼級
- 闇€瑕佽闂鏈夋暟鎹殑杈呭姪鍑芥暟
- 绱у瘑鑰﹀悎鐨勭被锛堝 Game 闇€瑕佽闂?Snake 鍐呴儴鐘舵€侊級

### 4. 鍔ㄦ€佸叧鑱?(Dynamic Binding / Polymorphism)

**浣嶇疆**锛歚gameobject.h` (GameObject 绫?, `game.h` (Game 绫?, `game.cpp` (Game::renderAllObjects)

**姒傚康**锛氬姩鎬佸叧鑱旓紙鍔ㄦ€佺粦瀹氾級鏄寚绋嬪簭杩愯鏃舵牴鎹璞＄殑瀹為檯绫诲瀷锛岃€屼笉鏄寚閽?寮曠敤鐨勫０鏄庣被鍨嬶紝鏉ュ喅瀹氳皟鐢ㄥ摢涓嚱鏁般€傝繖鏄鎬佺殑鏍稿績鏈哄埗銆?
**浠ｇ爜绀轰緥**锛?```cpp
class GameObject {
public:
    virtual void render() const = 0;  // 绾櫄鍑芥暟
    virtual std::pair<int, int> getPosition() const = 0;
};

class Snake : virtual public GameObject {
public:
    void render() const override { /* 铔囩殑娓叉煋閫昏緫 */ }
    std::pair<int, int> getPosition() const override { return showHead(); }
};

class Food : virtual public GameObject {
public:
    void render() const override { /* 椋熺墿鐨勬覆鏌撻€昏緫 */ }
    std::pair<int, int> getPosition() const override { return position; }
};

// 鍔ㄦ€佸叧鑱旀紨绀猴細
std::vector<std::shared_ptr<GameObject>> objects;
objects.push_back(std::make_shared<Snake>());
objects.push_back(std::make_shared<Food>());

for (const auto& obj : objects) {
    obj->render();  // 杩愯鏃舵牴鎹疄闄呯被鍨嬭皟鐢?Snake::render 鎴?Food::render
}
```

**瀹炵幇鏈哄埗**锛?- 缂栬瘧鍣ㄤ负姣忎釜鍖呭惈铏氬嚱鏁扮殑绫诲垱寤鸿櫄鍑芥暟琛紙vtable锛?- 瀵硅薄鍖呭惈铏氬嚱鏁拌〃鎸囬拡锛坴ptr锛?- 杩愯鏃堕€氳繃 vptr 鏌ユ壘姝ｇ‘鐨勫嚱鏁板湴鍧€

### 5. 铏氬熀绫?(Virtual Base Class)

**浣嶇疆**锛歚gameobject.h` (GameObject, IRenderable), `snake.h` (Snake 绫?

**姒傚康**锛氳櫄鍩虹被鐢ㄤ簬瑙ｅ喅鑿卞舰缁ф壙闂锛圖iamond Problem锛夈€傚綋涓や釜娲剧敓绫荤户鎵胯嚜鍚屼竴涓熀绫伙紝鑰岀涓変釜绫诲張鍚屾椂缁ф壙杩欎袱涓淳鐢熺被鏃讹紝浣跨敤 virtual 缁ф壙鍙互纭繚鍩虹被鍦ㄦ渶缁堟淳鐢熺被涓彧鏈変竴浠藉壇鏈€?
**浠ｇ爜绀轰緥**锛?```cpp
class GameObject {  // 铏氬熀绫?public:
    virtual ~GameObject() = default;
    virtual void render() const = 0;
};

class IRenderable {  // 鍙︿竴涓櫄鍩虹被
public:
    virtual ~IRenderable() = default;
    virtual char getRenderChar() const = 0;
};

// 浣跨敤铏氱户鎵?class Snake : virtual public GameObject, virtual public IRenderable {
public:
    void render() const override;
    char getRenderChar() const override;
};

class Food : virtual public GameObject, virtual public IRenderable {
public:
    void render() const override;
    char getRenderChar() const override;
};

// 濡傛灉瀛樺湪杩欐牱鐨勭户鎵匡紙婕旂ず鑿卞舰缁ф壙锛夛細
class SpecialObject : public Snake, public Food {
    // 鐢变簬浣跨敤浜嗚櫄缁ф壙锛孏ameObject 鍜?IRenderable 鍙湁涓€浠藉壇鏈?    // 閬垮厤浜嗕簩涔夋€у拰鏁版嵁鍐椾綑
};
```

**鑿卞舰缁ф壙闂**锛?```
     GameObject
    /          \
 Snake        Food
    \          /
     SpecialObject
```

**涓嶄娇鐢ㄨ櫄缁ф壙鐨勯棶棰?*锛?- `SpecialObject` 浼氬寘鍚袱浠?`GameObject` 鎴愬憳
- 璁块棶 `GameObject` 鎴愬憳鏃朵骇鐢熶簩涔夋€?- 鏁版嵁鍐椾綑锛屾氮璐瑰唴瀛?
**浣跨敤铏氱户鎵跨殑濂藉**锛?- 鍩虹被鎴愬憳鍦ㄦ渶缁堟淳鐢熺被涓彧鏈変竴浠?- 鐢辨渶缁堟淳鐢熺被璐熻矗鍒濆鍖栬櫄鍩虹被
- 閬垮厤璁块棶鍐茬獊鍜屾暟鎹啑浣?
## 椤圭洰缁撴瀯

```text
SnakeGame/
鈹溾攢鈹€ main.cpp          # 绋嬪簭鍏ュ彛
鈹溾攢鈹€ game.h            # 娓告垙绫诲畾涔?鈹溾攢鈹€ game.cpp          # 娓告垙绫诲疄鐜?鈹溾攢鈹€ gameobject.h      # 娓告垙瀵硅薄鍩虹被銆佽櫄鍩虹被銆丗ood绫?鈹溾攢鈹€ gameobject.cpp    # Food绫诲疄鐜?鈹溾攢鈹€ snake.h           # 铔囩被瀹氫箟
鈹溾攢鈹€ snake.cpp         # 铔囩被瀹炵幇
鈹溾攢鈹€ map.h             # 鍦板浘绫伙紙棰勭暀锛?鈹溾攢鈹€ map.cpp           # 鍦板浘绫伙紙棰勭暀锛?鈹溾攢鈹€ CMakeLists.txt    # CMake 鏋勫缓閰嶇疆
鈹溾攢鈹€ README.md         # 椤圭洰璇存槑鏂囨。
鈹斺攢鈹€ .gitignore
```

## 寰呮敼杩涳紙TODO锛?
- [x] **鍒嗘枃浠剁粍缁囦唬鐮?*锛氬皢浠ｇ爜鎷嗗垎涓哄涓枃浠舵彁楂樺彲缁存姢鎬с€?- [ ] **鏈€楂樺垎璁板綍**锛氬鍔犳湰鍦版枃浠惰鍐欙紙濡傚瓨鍏?`.dat` 鎴?`.json` 鏂囦欢锛夛紝瀹炵幇鏈€楂樺垎鎸佷箙鍖栦繚瀛樸€?- [ ] **浜や簰浼樺寲**锛氭嫤鎴笉鍚堢悊鐨勬柟鍚戣緭鍏ワ紙濡傛鍦ㄥ悜鍙崇Щ鍔ㄦ椂锛岀洿鎺ュ拷鐣ュ悜宸︾殑鎸夐敭锛夛紝鑰屼笉鏄粰浜堝噺閫熸儵缃氥€?
## 浣滆€?
Lpcyc

## 璁稿彲璇?
MIT
