#include "LifeCycle.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "ConsumeItem.h"    // ConsumeItem, HPPotionItem
#include "InventoryUI.h"

using namespace std;

// 마을 전용 고양이 애니메이션 프레임 (2개)
const vector<string> catFrame1 = {
    "    |\\---/|  ",
    "    ( o_o )  ",
    "     > ^ <   "
};

const vector<string> catFrame2 = {
    "    |\\---/|  ",
    "    ( >_< )  ", // 눈 깜빡임
    "     > v <   "  // 입 모양 변경
};

LifeCycle::LifeCycle() : currentState(EGameState::Village), isRunning(true), distance(0)
{
    mainPlayer = std::make_unique<Player>("나비", "고양이 기사");
    shop = std::make_unique<Shop>();
    money = std::make_unique<Money>(1000);
    shopUI = std::make_unique<ShopUI>();

    testInventory = std::make_shared<Inventory>(5);

    auto potion = std::make_shared<ItemBase>(
        EItemType::Consume,
        "포션",
        99,
        25,
        50
    );
    auto sword = std::make_shared<ItemBase>(
        EItemType::Equip,
        "검",
        1,
        25,
        50
    );

    testInventory->AddItem(potion, 99);
    testInventory->AddItem(sword, 1);


    shop->addStock(potion, 10);
    shop->addStock(sword, 1);
    // 배경 패턴 초기화 (멤버 변수 사용)
    background = ".... ^ .... _ .... * .... ^ .... _ .... * .... ^ .... _ .... * .... ^ ....";

    // 고양이 아트 초기화 (벡터 사용)
    catArt.push_back("    |\\---/|  ");
    catArt.push_back("    ( o_o )  ");
    catArt.push_back("     > ^ <   ");
}

// 커서 이동 함수
void LifeCycle::Gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, pos);
}

// 커서 비활성화 설정
void LifeCycle::BeginPlay() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // 커서를 보이지 않게 설정
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    system("cls"); // 시작 시 화면 한 번 초기화
}

void LifeCycle::Tick() {
    // 1. 현재 상태에 따른 핸들러 호출
    switch (currentState) {
    case EGameState::Village:    HandleVillage();   break; // 메뉴
    case EGameState::Shop:       HandleShop();      break;
    case EGameState::Dungeon:    HandleDungeon();   break;
	case EGameState::Inventory:  HandleInventory(); break; 
	case EGameState::BossBattle: HandleBossBattle(); break; 
        
        if (_kbhit() && _getch() == KEY_ESC) currentState = EGameState::Village;
        break;
    }

    Sleep(30); // 프레임 제한
}

// --- 각 상태별 로직 및 렌더링 ---

void LifeCycle::HandleVillage() { // 마을 메뉴와 고양이 애니메이션을 함께 출력합니다.
    Gotoxy(0, 0);
    cout << "===================================" << endl;
    cout << "          [ 평화로운 1조 ]          " << endl;
    cout << "===================================" << endl;
    cout << "  1. 상점 방문" << endl;
    cout << "  2. 인벤토리 확인" << endl;
    cout << "  3. 던전 입장 (이동 연습)" << endl;
    cout << "  4. 보스 레이드 도전" << endl;
    cout << "  5. 게임 종료" << endl;

    static int frameCount = 0;
    static ULONGLONG lastTime = GetTickCount64(); // 마지막으로 프레임이 바뀐 시간

    ULONGLONG currentTime = GetTickCount64();

    // 500ms(0.5초)마다 프레임 전환
    if (currentTime - lastTime > 500) {
        frameCount = (frameCount + 1) % 2; // 0, 1을 번갈아 가며 출력
        lastTime = currentTime;
    }

    // 현재 프레임에 맞는 고양이 출력
    const vector<string>& currentCat = (frameCount == 0) ? catFrame1 : catFrame2;

    // 메뉴 아래 적절한 위치에 출력
    Gotoxy(0, 9);
    for (const string& line : currentCat) {
        cout << "         " << line << endl; // 공백으로 중앙 정렬 효과
    }

    mainPlayer->printStatus(); // 플레이어 상태 출력

    cout << "  선택: ";


    if (_kbhit()) {
        int input = _getch();
        system("cls"); // 화면 전환 시 클리어
        switch (input) {
        case '1': currentState = EGameState::Shop; break;
        case '2': currentState = EGameState::Inventory; break;
        case '3': currentState = EGameState::Dungeon; break;
        case '4': currentState = EGameState::BossBattle; break;
        case '5': isRunning = false; break;
        }
    }
}

void LifeCycle::HandleShop()
{
    Gotoxy(0, 0);

    // ShopUI 결과 받기
    bool stay = ShopUI::updateShopTick(*shop, *money);

    // false면 마을로 복귀
    if (!stay)
    {
        system("cls");
        currentState = EGameState::Village;
        return;
    }
}

void LifeCycle::HandleInventory() { // 플레이어의 인벤토리 정보를 받아서 아이템 목록을 보여주는 기능을 구현할 예정입니다.
    Gotoxy(0, 0);
    //cout << "==========================================" << endl;
    //cout << "                [ 인벤토리 ]               " << endl;
    //cout << "==========================================" << endl;
    //cout << "  (아이템 목록 준비 중...)" << endl << endl;
    //cout << "  [ESC] 마을로 돌아가기" << endl;
    //cout << "==========================================" << endl;
    if (testInventory != nullptr)
    {
        //testInventory->PrintInventory();
        InventoryUI::UpdateInventoryUITick(testInventory);
    }

    //if (_kbhit() && _getch() == KEY_ESC) {
    //    system("cls");
    //    currentState = EGameState::Village;
    //}
    system("cls");
    currentState = EGameState::Village;
}

void LifeCycle::HandleDungeon() { // 플레이어의 이동 거리를 관리하여 배경이 움직이는 효과를 구현합니다. 향후 몬스터 등장과 전투 시스템도 추가할 예정입니다.
    Gotoxy(0, 0);
    // 횡스크롤 렌더링
    cout << "================= [ 던전 ] ================" << endl;
    cout << "      거리: " << distance << "m | [ESC] 마을로     " << endl;
    cout << "==========================================" << endl << endl;

    for (const string& line : catArt) {
        cout << "     " << line << endl;
    }

    string currentView = background.substr(distance % 20, 40);
    cout << " " << currentView << endl;
    cout << "------------------------------------------" << endl;

    // 던전 전용 입력 처리
    if (_kbhit()) {
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_RIGHT) distance++;
            else if (key == KEY_LEFT && distance > 0) distance--;
        }
        else if (key == KEY_ESC) {
            system("cls");
            currentState = EGameState::Village;
        }
    }
}

void LifeCycle::HandleBossBattle() { // 향후 보스 몬스터와의 전투 시스템을 구현할 예정입니다. 현재는 전투 준비 화면만 표시합니다.
    Gotoxy(0, 0);
    cout << "==========================================" << endl;
    cout << "                [ 보스 전투 ]               " << endl;
    cout << "==========================================" << endl;
    cout << "  (보스 전투 준비 중...)" << endl << endl;
    cout << "  [ESC] 마을로 돌아가기" << endl;
    cout << "==========================================" << endl;
    if (_kbhit() && _getch() == KEY_ESC) {
        system("cls");
        currentState = EGameState::Village;
    }
}   


void LifeCycle::EndPlay() {
    system("cls");
    cout << "게임을 종료합니다. 플레이해주셔서 감사합니다!" << endl;
}

bool LifeCycle::IsRunning() const {
    return isRunning;
}

LifeCycle::~LifeCycle() = default;