#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Player.h" // 앞서 만든 플레이어 클래스
#include "ItemBase.h"
#include "Shop.h"
#include "ShopUI.h"
#include "Money.h"
#include "Inventory.h"

// 입력 키코드 매크로 지정
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

// 게임의 현재 상태를 관리하는 열거형
enum class EGameState {
    Village,    // 마을 (평화로운 1조)
    Shop,       // 상점 (고양이 잡화점)
    Inventory,  // 인벤토리 (구현 예정)
    Dungeon,    // 던전 (깊은 숲)
    BossBattle, // 보스 전투 (구현 예정)
    Exit        // 게임 종료
};

// Player 클래스의 상세 구현을 헤더에서 숨기기 위한 전방 선언
class Player;
class ItemBase;
class Shop;
class ShopUI;
class Money;

class LifeCycle {
private:
    // 1. 시스템 제어 및 상태 변수
    bool isRunning;
    EGameState currentState;
    int distance; // 던전 이동 거리

    // 2. 키 코드 상수 (상태 핸들러에서 공용으로 사용)
    //static const int KEY_UP = 72;
    //static const int KEY_DOWN = 80;
    //static const int KEY_LEFT = 75;
    //static const int KEY_RIGHT = 77;
    //static const int KEY_ESC = 27;

    // 3. 게임 데이터 자원
    std::unique_ptr<Player> mainPlayer; // 스마트 포인터를 이용한 플레이어 관리
    std::shared_ptr<Inventory> testInventory;   // UI 테스트 전용 인벤토리 객체
    std::unique_ptr<Shop> shop; // 상점 관리
    std::unique_ptr<ShopUI> shopUI; // 상점 UI
    std::unique_ptr<Money> money;
    std::string background;             // 던전 배경 문자열
    std::vector<std::string> catArt;    // 고양이 아스키 아트

    // 4. 내부 로직 처리 함수 (Private)
    void Gotoxy(int x, int y);
    void HandleVillage();
    void HandleShop();
    void HandleDungeon();
	void HandleInventory(); // 구현 예정
	void HandleBossBattle(); // 구현 예정

public:
    // 생성자와 소멸자
    LifeCycle();
    ~LifeCycle(); // 중요: unique_ptr의 안전한 삭제를 위해 .cpp에서 정의합니다.

    // 게임 루프 필수 함수
    void BeginPlay();
    void Tick();
    void EndPlay();

    // 상태 확인 함수
    bool IsRunning() const;
};