# ⚔️ [프로젝트 이름: (미정)]

> **Visual Studio 2022와 C++로 구현된 정통 텍스트 RPG** > 객체 지향 프로그래밍(OOP)을 활용하여 설계된 탄탄한 로직의 콘솔 모험기입니다.

---

## 📝 프로젝트 개요
이 프로젝트는 **C++**를 사용하여 개발된 텍스트 기반 RPG입니다. **Visual Studio 2022** 환경에서 작업되었으며, 클래스 상속, 다형성, 파일 입출력 등 C++의 핵심 기능을 활용하여 안정적인 게임 엔진을 구축하는 것을 목표로 합니다.

## 🌟 주요 특징
* **C++ OOP 설계:** `Character`, `Monster`, `Item`, `Inventory` 등의 클래스 구조를 통한 효율적인 데이터 관리.
* **확장성:** 상속과 다형성을 활용하여 새로운 직업이나 몬스터를 쉽게 추가할 수 있는 구조.
* **정통 텍스트 감성:** 화려한 그래픽 대신 텍스트 중심의 몰입감 있는 게임 플레이 제공.

---

## 🚀 시작하기

### 개발 환경 (Prerequisites)
* **IDE:** Visual Studio 2022
* **Compiler:** MSVC (Microsoft Visual C++)
* **C++ Standard:** C++17 또는 C++20 권장

### 설치 및 실행 방법
1. **저장소를 클론합니다.**
   ```bash
   git clone [https://github.com/parkchanheyk/Text_ConsoleRPG_Project.git](https://github.com/parkchanheyk/Text_ConsoleRPG_Project.git)
   ```
2. Visual Studio 2022에서 `[프로젝트명].sln` 파일을 엽니다.
3. 상단 솔루션 구성에서 **Release** 또는 **Debug**를 선택하고 **x64** 아키텍처를 확인합니다.
4. `F5` 키를 눌러 빌드 후 실행합니다.

---

## 📂 프로젝트 구조
C++ 프로젝트 특성에 맞춘 권장 구조입니다.

```plaintext
├── ProjectName/
│   ├── Headers/            # .h 헤더 파일 (클래스 선언)
│   │   ├── Character.h
│   │   ├── Monster.h
│   │   ├── Inventory.h
│   │   └── GameManager.h
│   ├── Sources/            # .cpp 소스 파일 (로직 구현)
│   │   ├── Character.cpp
│   │   ├── Monster.cpp
│   │   ├── Inventory.cpp
│   │   └── Main.cpp        # 진입점
│   └── Data/               # 세이브 파일 및 게임 데이터 (.txt / .dat)
├── ProjectName.sln         # Visual Studio 솔루션 파일
└── README.md
```

---

## 🛠 기술 스택
* **Language:** C++
* **Toolchain:** MSVC 143 (Visual Studio 2022)
* **Libraries:** * `<iostream>`: 콘솔 입출력
    * `<vector>`, `<map>`: 데이터 관리 (STL)
    * `<string>`: 문자열 처리
    * `<fstream>`: 데이터 저장 및 로드

---

## 🎮 주요 기능 구현 예정
- [ ] 플레이어 직업별 고유 스킬 시스템
- [ ] 아이템 인벤토리 및 장착 시스템
- [ ] 랜덤 맵 생성 또는 층별 던전 시스템
- [ ] 턴제 몬스터 (단순 패턴 공격)

---

## 👤 개발자 정보
* **개발팀:** CH2 1조
* **GitHub:** [parkchanheyk/Text_ConsoleRPG_Project](https://github.com/parkchanheyk/Text_ConsoleRPG_Project)

---

### 💡 팀 협업 팁 (Visual Studio)
* **.gitignore 설정:** `Debug/`, `Release/`, `.vs/` 등 빌드 결과물과 로컬 설정 파일이 GitHub에 올라가지 않도록 주의하세요.
* **코드 컨벤션:** 조원들과 변수 명명 규칙(예: CamelCase 또는 snake_case)을 통일하면 코드를 합칠 때 훨씬 수월합니다.
```

---

**추가 팁:**
* 프로젝트 이름이 정해지면 `#` 옆의 이름을 수정해 보세요.
* 구현이 완료된 기능은 `[ ]`를 `[x]`로 바꿔서 진행 상황을 표시할 수 있습니다.

이 프로젝트를 진행하면서 특정 클래스(예: 다형성을 활용한 몬스터 시스템)의 설계 예시 코드가 필요하시면 언제든 말씀해 주세요!
