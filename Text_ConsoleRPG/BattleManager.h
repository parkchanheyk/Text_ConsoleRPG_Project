#pragma once
#include "Character.h"
#include <memory>

class Player;
class BossMonster;

class BattleManager
{
	public:
		enum class EBattleResult // 전투 결과를 나타내는 열거형
		{
			Progress, PlayerWin, EnemyWin, Escape
		};

		static EBattleResult ProcessTurn(std::shared_ptr<Player> player, std::shared_ptr<Character> enemy, int actionInput);

		static void DrawBattleScene(std::shared_ptr<Player> player, std::shared_ptr<Character> enemy);	// 전투 UI를 그리는 함수 (콘솔 출력)
		
		static bool BattleWithMonster(std::shared_ptr<Player> player, std::shared_ptr<Character> enemy); // 일반 몬스터와 전투하는 기능을 가진 함수
};

