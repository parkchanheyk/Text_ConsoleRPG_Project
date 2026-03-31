#include "BattleManager.h"
#include "Player.h"
#include "BossMonster.h"
#include "Monster.h"
#include "ConsumeItem.h"
#include "InventoryUI.h"
#include <iostream>
#include <windows.h>
#include <vector>

void BM_Gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, pos);
}

void BattleManager::DrawBattleScene(std::shared_ptr<Player> player, std::shared_ptr<Character> enemy)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // system("cls"); // 호출하는 쪽(LifeCycle)에서 처리하므로 삭제 권장

    BM_Gotoxy(0, 0);
    std::cout << "=======================================================================================" << std::endl;
    std::cout << "                                   [ FINAL BOSS BATTLE ]                               " << std::endl;
    std::cout << "=======================================================================================" << std::endl;

    // --- 아스키 아트 출력 부분 ---

    // 1. 고양이 아트 (왼쪽, 하늘색) - 띄어쓰기를 조절해 모두 정확히 '25칸'으로 맞췄습니다.
    std::vector<std::string> catArtLines = {
        "          |\\---/|       ",
        "          ( o_o )        ",
        "           > ^ <         "
    };

    // 2. 쥐 보스 아트 (오른쪽, 빨간색)
    std::vector<std::string> ratArtLines = {
        "             __             _,-'~^\"-.",
        "           _// )      _,-'~`         `.",
        "         .' ( /`\"-,-'`                 ;",
        "        / 6                             ;",
        "       /           ,             ,-'     ;",
        "      (,__.--.      \\           /        ;",
        "       //'   /`-.\\   |          |        `._________",
        "         _.-'_/`  )  )--...,,,___\\     \\-----------,)",
        "       (((\"~` _.-'.-'           __`-.   )         //",
        "             (((\"`             (((---~\"`         //",
        "                                                ((________________",
        "                                                `----\"\"\"\"~~~~^^^```"
    };

    int startY = 3;
    int maxLines = ratArtLines.size(); // 12줄
    int catOffset = maxLines - catArtLines.size();

    for (int i = 0; i < maxLines; ++i) 
    {
        BM_Gotoxy(0, startY + i);

        // 왼쪽 고양이 출력 (하늘색)
        SetConsoleTextAttribute(hConsole, 11);
        if (i >= catOffset) {
            std::cout << catArtLines[i - catOffset]; // 정확히 25칸 출력
        }
        else {
            // 핵심 수정: 고양이가 없는 줄도 정확히 25칸의 공백을 출력해야 쥐가 안 밀립니다!
            std::cout << "                         ";
        }

        // 중앙 대치 메시지 (흰색)
        SetConsoleTextAttribute(hConsole, 7);
        if (i == maxLines / 2 + 3) {
            std::cout << "     VS      "; // 13칸
        }
        else {
            std::cout << "             "; // 13칸 공백
        }

        // 오른쪽 쥐 출력 (빨간색)
        SetConsoleTextAttribute(hConsole, 4);
        std::cout << ratArtLines[i] << std::endl;
    }

    SetConsoleTextAttribute(hConsole, 7); // 색상 원상복구

    // 핵심 2: 겹침과 스크롤링을 방지하는 커스텀 UI 대시보드
    int statusY = startY + maxLines + 1;

    BM_Gotoxy(0, statusY);
    std::cout << "--------------------------------------------------------------------------------" << std::endl;

    // 첫 번째 줄: 이름 및 레벨 출력
    BM_Gotoxy(2, statusY + 1);
    std::cout << "[플레이어] " << player->getName() << " (Lv." << player->getLevel() << ")";
    BM_Gotoxy(40, statusY + 1);
    std::cout << "| [보스] " << enemy->getName() << " (Lv." << enemy->getLevel() << ")";

    // 두 번째 줄: HP 상태 출력
    BM_Gotoxy(2, statusY + 2);
    std::cout << "HP : " << player->getCurrentHP() << " / " << player->getMaxHP() << "    ";
    BM_Gotoxy(40, statusY + 2);
    std::cout << "| HP : " << enemy->getCurrentHP() << " / " << enemy->getMaxHP() << "    ";

    // 세 번째 줄: 공격력 및 스피드 출력
    BM_Gotoxy(2, statusY + 3);
    std::cout << "ATK: " << player->getATK() << "   SPD: " << player->getSpeed();
    BM_Gotoxy(40, statusY + 3);
    std::cout << "| ATK: " << enemy->getATK() << "   SPD: " << enemy->getSpeed();

    BM_Gotoxy(0, statusY + 4);
    std::cout << "--------------------------------------------------------------------------------" << std::endl;

    // 남은 빈 공간을 지워주는 더미 공백 출력 (잔상 제거용)
    std::cout << "  1. 공격하기 | 2. 인벤토리 | 3. 도망가기 | 선택:                                           " << std::endl;
    std::cout << "                                                                                " << std::endl;

    // 커서를 입력 위치로 되돌림
    BM_Gotoxy(50, statusY + 5);
}

BattleManager::EBattleResult BattleManager::ProcessTurn(std::shared_ptr<Player> player, std::shared_ptr<Character> enemy, int actionInput)
{
    if (actionInput == '1') 
    {
        // 1. 플레이어 공격
        player->attack(enemy);
        if (enemy->getCurrentHP() <= 0) return EBattleResult::PlayerWin;

        // 2. 적 반격
        enemy->attack(player);
        if (player->getCurrentHP() <= 0) return EBattleResult::EnemyWin;
    }
    else if(actionInput == '2') 
    {
		system("cls");

        // 인벤토리 UI 업데이트 및 아이템 사용 처리
        auto selectedItem = InventoryUI::UpdateInventoryUITick(player->GetInventory());

        // 2. 아이템을 선택하고 Enter를 눌렀을 경우 (ESC가 아닐 때)
        if (selectedItem != nullptr)
        {
            // 3. 소비 아이템인지 확인 (다운캐스팅)
			auto consumeItem = std::dynamic_pointer_cast<ConsumeItem>(selectedItem); // 다운캐스팅 시도 (소비 아이템이 아니면 nullptr 반환)

            if (consumeItem)
            {
                system("cls"); // 효과 로그 출력을 위해 화면 정리

                // 4. 아이템 효과 적용 (player는 shared_ptr<Player>이므로 Character* 타입에 자동 호환됩니다.)
                if (consumeItem->ApplyEffect(player))
                {
                    // 5. 사용 성공 시 인벤토리에서 실제 제거 (1개 차감)
                    player->GetInventory()->RemoveItem(selectedItem, 1);

                    std::cout << "\n아이템을 사용했습니다! 적의 공격이 시작됩니다." << std::endl;
                    Sleep(1000);

                    // 6. 아이템 사용도 턴을 소모하므로 적이 반격합니다.
                    std::cout << "\n--- 적의 턴 ---" << std::endl;
                    enemy->attack(player);

                    if (player->getCurrentHP() <= 0) return EBattleResult::EnemyWin;
                }
            }
            else
            {
                system("cls");
                std::cout << "\n[알림] 장비 아이템은 전투 중에 사용할 수 없습니다!" << std::endl;
                Sleep(1000);
            }
        }

        // 전투 화면으로 복귀하기 전 화면 정리
        system("cls");
        return EBattleResult::Progress;
	}

    else if (actionInput == '3') 
    {
        return EBattleResult::Escape; //도망 
    }

	return EBattleResult::Progress; // 전투 계속
}

bool BattleManager::BattleWithMonster(std::shared_ptr<Player> player, std::shared_ptr<Character> enemy)
{
    EBattleResult result = EBattleResult::Progress;
    system("cls");
    std::vector<std::string> catArtLines = {
    R"(          |\---/|       )",
    R"(          ( o_o )        )",
    R"(           > ^ <         )"
    };
    auto monsterPtr = std::dynamic_pointer_cast<Monster>(enemy); // getAsciiArt()에 접근하기 위한 다운캐스팅

    while (result == EBattleResult::Progress)
    {
        BM_Gotoxy(0, 0);

        std::cout << "================= [ 전투 중 ] ===============" << std::endl;
        std::cout << "                 상대: " << enemy->getName() << "" << std::endl;
        std::cout << "==============================================" << std::endl << std::endl;

        for (const std::string& line : catArtLines) {
            std::cout << line << std::endl;
        }

        for (const std::string& line : monsterPtr->getAsciiArt()) {
            std::cout << "                " << line << std::endl;
        }
        
        BM_Gotoxy(0, 12);
        std::cout << "------------------------------------------" << std::endl;
        std::cout << " [ " << player->getName() << " HP: " << player->getCurrentHP() << " ]  VS  ";
        std::cout << " [ " << enemy->getName() << " HP: " << enemy->getCurrentHP() << " ] " << std::endl;
        std::cout << "------------------------------------------" << std::endl;
        std::cout << "  1. 공격하기 | 2. 인벤토리 | 3. 도망가기 | 선택: " << std::endl;

        if (_kbhit())
        {
            int input = _getch();

            // 입력값에 따라 ProcessTurn 실행
            result = ProcessTurn(player, enemy, input);

            // 결과
            if (result == EBattleResult::PlayerWin) {
                std::cout << "\n\n승리했습니다! " << enemy->getName() << "을(를) 물리쳤습니다!" << std::endl;
                // 경험치랑 아이템 드랍 구현
                player->addMoney(monsterPtr->getMoney());
                player->addExp(monsterPtr->getExp());
                Sleep(1500);
                return true;
            }
            else if (result == EBattleResult::EnemyWin) {
                system("cls");
                std::cout << "\n\n   You Died..." << std::endl;
                player->setCurrentHP(player->getMaxHP());
                Sleep(2000);
                return false;
            }
            else if (result == EBattleResult::Escape) {
                system("cls");
                std::cout << "\n\n   쫄?  " << std::endl;
                Sleep(1000);
                return true;
            }
        }
        Sleep(30);
    }

}