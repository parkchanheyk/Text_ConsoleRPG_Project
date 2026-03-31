#include "LifeCycle.h"
#include "Player.h"     
#include "BossMonster.h"   
#include "BattleManager.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "ConsumeItem.h"    // ConsumeItem, HPPotionItem
#include "InventoryUI.h"
#include "EquipItem.h"

using namespace std;

// 마을 전용 고양이 애니메이션 프레임 (2개)
const vector<string> catFrame1 = {
    "      /\\____/\\        ",
    "     ( ' W ' ) = > = >",
    "     ( >              ",
    "     /     )          ",
    "     (/---\\)          "
};

const vector<string> catFrame2 = {
    "      /\\____/\\        ",
    "     ( ' W ' )        ",
    "     ( >      = > = > ",
    "     /     )          ",
    "     (/---\\)          "
};

LifeCycle::LifeCycle() : currentState(EGameState::Village), isRunning(true), distance(0)
{
    mainPlayer = std::make_shared<Player>("나비", "고양이 기사");

    shop = std::make_unique<Shop>();
    shopUI = std::make_unique<ShopUI>();

    auto scroll = std::make_shared<ExpScroll>
        (
            "초급 경험치 스크롤",
            50,
            1
        );
    auto sword = std::make_shared<EquipItem>
        (
            "낡고 녹슨 검",
            50,
            50,
            200,
            100
        );

    auto smallPotion = std::make_shared<HPPotionItem>
        (
            "소형 체력 포션",
            10,
            1,
            50
        );

    mainPlayer->GetInventory()->AddItem(scroll, 3);
    mainPlayer->GetInventory()->AddItem(smallPotion, 10);
    mainPlayer->GetInventory()->AddItem(sword, 1);

    shop->addStock(smallPotion, 100);
    shop->addStock(scroll, 100);
    shop->addStock(sword, 10);

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

void LifeCycle::HandleVillage() {
    // 1. 상단 타이틀 (특수 기호 제거)
    Gotoxy(0, 0);
    cout << "================================================================================" << endl;
    Gotoxy(26, 1);
    cout << "--- [ 마을 : 평화로운 1조 ] ---" << endl;
    Gotoxy(0, 2);
    cout << "================================================================================" << endl;

    // 2. 좌측 고양이 출력 (500ms마다 프레임 전환)
    static int frameCount = 0;
    static ULONGLONG lastTime = GetTickCount64();
    ULONGLONG currentTime = GetTickCount64();

    if (currentTime - lastTime > 100) {
        frameCount = (frameCount + 1) % 2;
        lastTime = currentTime;
    }

    const vector<string>& currentCat = (frameCount == 0) ? catFrame1 : catFrame2;

    int catX = 8;
    int catY = 7;
    // 고양이는 하늘색으로 출력 (색상 코드 11)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    for (size_t i = 0; i < currentCat.size(); ++i) {
        Gotoxy(catX, catY + (int)i);
        cout << currentCat[i];
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 흰색 복구

    int infoX = 45;
    int infoY = 5;

    Gotoxy(infoX, infoY);     cout << "* STATUS *";
    Gotoxy(infoX, infoY + 2); cout << "NAME   : " << mainPlayer->getName();
    Gotoxy(infoX, infoY + 3); cout << "LEVEL  : " << mainPlayer->getLevel();
    Gotoxy(infoX, infoY + 4); cout << "HEALTH : " << mainPlayer->getCurrentHP();
    Gotoxy(infoX, infoY + 5); cout << "GOLD   : " << mainPlayer->GetMoney()->getCurrentMoney() << " G";
	Gotoxy(infoX, infoY + 6); cout << "EXP    : " << mainPlayer->getExp() << " EXP";


    int menuY = infoY + 9;
    Gotoxy(infoX, menuY);     cout << "* ACTIONS *";
    Gotoxy(infoX, menuY + 2); cout << "1. 상점";
    Gotoxy(infoX, menuY + 3); cout << "2. 인벤토리";
    Gotoxy(infoX, menuY + 4); cout << "3. 던전";
    Gotoxy(infoX, menuY + 5); cout << "4. 보스전";
    Gotoxy(infoX, menuY + 6); cout << "5. EXIT GAME";

    Gotoxy(infoX, menuY + 8);
    cout << "SELECT > ";

    // 4. 입력 처리
    if (_kbhit()) {
        int input = _getch();
        system("cls");
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
    bool stay = shopUI->updateShopTick(*shop, mainPlayer);

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

    // 플레이어의 인벤토리에 대하여 null값 확인
    if (mainPlayer->GetInventory() != nullptr)
    {
        // 플레이어 인벤토리의 UI 출력
        std::shared_ptr<ItemBase> selectedItem = InventoryUI::UpdateInventoryUITick(mainPlayer->GetInventory());

        // 선택된 아이템 nullptr 검사
        if (selectedItem != nullptr)
        {
            // 선택한 아이템이 사용 가능한 타입인지 확인
            if (std::shared_ptr<IApplicablePattern> usableItem = dynamic_pointer_cast<IApplicablePattern>(selectedItem))
            {
                // 인벤토리에서 해당 아이템 1개 제거
                if (mainPlayer->GetInventory()->RemoveItem(selectedItem) == true)
                {
                    // 효과 적용
                    usableItem->ApplyEffect(this->mainPlayer);
                }
            }
        }
    }

    system("cls");
    currentState = EGameState::Village;
}

void LifeCycle::HandleDungeon() { // 플레이어의 이동 거리를 관리하여 배경이 움직이는 효과를 구현합니다. 향후 몬스터 등장과 전투 시스템도 추가할 예정입니다.
    Gotoxy(0, 0);
    // 횡스크롤 렌더링
    // 몬스터 5마리 확률을 담는 구조체
    struct SpawnTable
    {
        int monster[5];
    };
    // 거리별 난이도 미리 세팅
    map<int, SpawnTable> levelDesign =
    {
        { 0,   {{70, 25, 0, 0, 5}} },  // 0m~ 뚱냥이 70% 불독 30% 럭키 5%
        { 150, {{10, 50, 30, 5, 5}} }, // 150m~ 뚱냥이 10% 불독 50% 고스트 30% 골렘 5% 럭키 5%
        { 300, {{0, 0, 60, 30, 10}} }, // 300m~ 고스트 60% 골렘 30% 럭키 10%
        { 450, {{0, 0, 0, 80, 20}} }  // 450m~ 골렘 80% 럭키 20%
    };

    int spawnPoint = (distance / 30) * 30; // 내 위치를 30미터 단위로 체크
    // 내 캐릭터가 30미터 단위(몬스터가 있는 위치)에 있고 몬스터의 인식 범위(9m)내에 있으면 true
    bool isMonsterZone = (distance >= 30 && (distance % 30 >= 0 && distance % 30 < 10));

    // 몬스터 생성
	if (isMonsterZone)
	{
		if (defeatedPoints.find(spawnPoint) != defeatedPoints.end())
		{
			currentMonster = nullptr; // 처치된 곳이면 몬스터 없음
		}
		else
		{
			auto it = dungeonMonsters.find(spawnPoint);  // 해당 지점에 몬스터가 이미 있는지 확인

			if (it == dungeonMonsters.end())             // 몬스터가 없다면
			{
				// 거리마다 섹션 나누기
				int currentSection = 0;
				if (distance >= 450)
				{
					currentSection = 450;
				}
				else if (distance >= 300)
				{
					currentSection = 300;
				}
				else if (distance >= 150)
				{
					currentSection = 150;
				}
				else
				{
					currentSection = 0;
				}

				SpawnTable table = levelDesign[currentSection]; // 미리 설정해둔 섹션별 확률을 구조체 변수에 넣어줌

				// 가중치 기반(거리에 따른 몬스터 확률) 랜덤 선택 (0 ~ 99)
				int dice = rand() % 100;      // 랜덤한 값 저장
				int cumulative = 0;           // 누적 값
				int selectedIndex = 0;        // 뽑힌 몬스터의 인덱스

				for (int i = 0; i < 5; i++)
				{
					cumulative += table.monster[i];   // 계속 더하기 때문에 마지막엔 무조건 100이 돼서 뽑힘
					if (dice < cumulative)
					{
						selectedIndex = i;
						break;
					}
				}
				unique_ptr<Monster> newMonster; // 새로운 몬스터 생성

				switch (selectedIndex)
				{
				case 0: newMonster = make_unique<Chonkycat>(); break;
				case 1: newMonster = make_unique<Bulldog>(); break;
				case 2: newMonster = make_unique<Ghost>(); break;
				case 3: newMonster = make_unique<Golem>(); break;
				case 4: newMonster = make_unique<LuckyMonster>(); break;
				}
				dungeonMonsters[spawnPoint] = std::move(newMonster);
				battleTimer = 0.0f; // 몬스터가 나타나면 타이머 초기화
			}
			// 현재 화면에 보여줄 몬스터 포인터 설정
			currentMonster = dungeonMonsters[spawnPoint];
		}

	}
    else
    {
        currentMonster = nullptr;   // 해당 구간을 벗어나면 화면에 보여줄 몬스터가 없으니 nullptr
    }

    // 몬스터와 전투
    if (currentMonster) {
        battleTimer += 0.03f; // tick의 sleep(30)에 맞춰 대략적인 시간 누적 (약 1~2초 설정)

        if (battleTimer >= 1.0f) { // 약 1초 마주치면 전투 발생
            
            system("cls");
            cout << "\n\n\n          " << currentMonster->getName() << "와(과) 전투 시작!" << endl;
            Sleep(1000);

            // 현재 마주친 몬스터 정보를 전달(추후 BattleManager에서 구현)
            BattleManager::BattleWithMonster(mainPlayer, currentMonster);
            // 전투 후 map에서 삭제
            dungeonMonsters.erase(spawnPoint);
            // 끝나면 몬스터 없애기
            defeatedPoints.insert(spawnPoint);
            currentMonster = nullptr;
            battleTimer = 0.0f;
            return;
        }
    }

    // 던전 출력
    cout << "================= [ 던전 ] ===============" << endl;
    cout << "      거리: " << distance << "m | [ESC] 도망가기   " << endl;
    cout << "==========================================" << endl << endl;

    for (const string& line : catArt)
    {
        cout << "     " << line << endl;
    }

    // 몬스터 출력
    if (currentMonster)
    {
        cout << "   [!!!] 눈 앞에 " << currentMonster->getName() << "등장!     " << endl;

        // 몬스터 아스키 아트 출력
        for (const string& line : currentMonster->getAsciiArt()) {
            cout << "                " << line << endl;
        }

        // 화면 고정을 위해서 젤 큰 몬스터(불독) 크기에 맞게
        int paddingLines = 7 - 1 - currentMonster->getAsciiArt().size();
        for (int i = 0; i < paddingLines; i++) cout << endl;
    }
    else
    {
        // 몬스터가 없을 때도 정확히 7줄을 출력해서 높이를 맞춤
        for (int i = 0; i < 7; i++)
        {
            cout << "                                        " << endl;
        }
    }

    cout << endl;
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
            // ESC를 누를 때 고양이(주인공)가 이동한 거리 리셋
            distance = 0;
            // ESC를 누를 때 dungeonMonsters 클리어
            dungeonMonsters.clear();
            // ESC를 누를 때 defeatedPoints 클리어
            defeatedPoints.clear();
            currentState = EGameState::Village;
        }
    }

}

void LifeCycle::HandleBossBattle() { // 향후 보스 몬스터와의 전투 시스템을 구현할 예정입니다. 현재는 전투 준비 화면만 표시합니다.

	static std::shared_ptr<BossMonster> boss = std::make_shared<BossMonster>(); // 보스 몬스터 객체를 생성하여 관리

    Gotoxy(0, 0);

    BattleManager::DrawBattleScene(mainPlayer, boss);

    // 2. 입력 및 전투 로직 처리
    if (_kbhit()) {
        int input = _getch();

        // 전투 매니저가 한 턴을 계산함
        auto result = BattleManager::ProcessTurn(mainPlayer, boss, input);

        // 3. 결과에 따른 후처리
        if (result == BattleManager::EBattleResult::PlayerWin) {
            std::cout << "\n승리했습니다! 마을로 돌아갑니다." << std::endl;
            boss = std::make_shared<BossMonster>(); // 보스 리셋
            Sleep(1500); system("cls"); currentState = EGameState::Village;
        }
        else if (result == BattleManager::EBattleResult::EnemyWin) {
            std::cout << "\n패배했습니다... 체력을 회복하고 다시 도전하세요." << std::endl;
			mainPlayer->death(); // 사망 처리 (문구 출력)
            mainPlayer->setCurrentHP(mainPlayer->getMaxHP()); // 체력 회복
            Sleep(1500); system("cls"); currentState = EGameState::Village;
        }
        else if (result == BattleManager::EBattleResult::Escape) {
            system("cls"); currentState = EGameState::Village;
        }
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