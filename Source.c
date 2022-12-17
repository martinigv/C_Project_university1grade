#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
// 2048을 위한 선언
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
// 2048을 위한 선언

// text RPG를 위한 함수들 및 전역변수 선언들
enum PlayerType
{
    Knight = 1,
    Archer = 2,
    Assasin = 3
};

enum MonsterType
{
    Slime = 1,
    Orce = 2,
    Troll = 3
};
int playerType;
int playerHp;
int hpMax;
int playerAttack;
int playerDefence;
int playerLevel = 1;
int playerExp = 0;

int monsterType;
int monsterHp;
int monsterAttack;
int monsterDefence;
int monsterExp;


void startLobby();
void selectJob();
void enterField();
void createMonster();
void enterBattle();
void levelUp(int monsterexp);
void upgradePlayerStat();
void upgradeMonsterStat();

void startLobby()
{
    while (1)
    {
        printf("로비에 입장하셨습니다\n");

        // 직업 선택
        selectJob();

        printf("(1) 필드 입장 (2) 게임 종료\n");
        printf(">> ");
        int input;
        scanf_s("%d", &input);

        if (input == 1)
        {
            // 필드 입장
            enterField();
        }
        else
        {
            return;
        }
    }
}

void selectJob()
{
    while (1)
    {
        printf("직업을 선택해주세요\n");
        printf("(1) 전사 (2) 궁수 (3) 도적\n");
        printf(">>");

        scanf_s("%d", &playerType);

        if (playerType == Knight)
        {
            printf("기사 스폰중\n");
            playerHp = 200;
            hpMax = 200;
            playerAttack = 10;
            playerDefence = 8;
            break;
        }
        else if (playerType == Archer)
        {
            printf("궁수 스폰중\n");
            playerHp = 100;
            hpMax = 100;
            playerAttack = 25;
            playerDefence = 3;
            break;
        }
        else if (playerType == Assasin)
        {
            printf("도적 스폰중\n");
            playerHp = 150;
            hpMax = 150;
            playerAttack = 20;
            playerDefence = 5;
            break;
        }
    }

}

void enterField()
{
    while (1)
    {
        printf("필드에 입장하셨습니다!\n");
        printf("당신의 스텟(HP: %d AD: %d DF: %d)\n", playerHp, playerAttack, playerDefence);

        createMonster();

        printf("(1) 싸운다 (2) 도망친다\n");
        printf(">> ");
        int input;
        scanf_s("%d", &input);

        if (input == 1)
        {
            enterBattle();
            if (playerHp == 0)
                break; // 플레이어 사망 -> 필드 재입장 불가
            if (playerLevel >= 30)
            {
                printf("최대 레벨에 도달하셨습니다. 환생 중 입니다\n");
                break;
            }
        }


    }
}

void createMonster()
{
    monsterType = 1 + rand() % 3;

    switch (monsterType)
    {
    case Slime:
        
        monsterHp = 15;
        monsterAttack = 5;
        monsterDefence = 0;
        monsterExp = 10;
        upgradeMonsterStat();
        printf("슬라임 스폰중 (HP: %d / ATT: %d / DEF: %d)\n", monsterHp, monsterAttack, monsterDefence);
        break;
    case Orce:
        
        monsterHp = 50;
        monsterAttack = 15;
        monsterDefence = 8;
        monsterExp = 50;
        upgradeMonsterStat();
        printf("오크 스폰중 (HP: %d / ATT: %d / DEF: %d)\n", monsterHp, monsterAttack, monsterDefence);
        break;
    case Troll:

        monsterHp = 30;
        monsterAttack = 10;
        monsterDefence = 5;
        monsterExp = 30;
        upgradeMonsterStat();
        printf("트롤 스폰중 (HP: %d / ATT: %d / DEF: %d)\n", monsterHp, monsterAttack, monsterDefence);
        break;

    }
}

void enterBattle()
{
    while (1)
    {
        int monsterDamaged = playerAttack - monsterDefence; // 몬스터가 입는 데미지(플레이어 턴)
        if (monsterDamaged <= 0) // 데미지가 0 혹은 음수가 나오면 1로 기본피해량 설정
            monsterDamaged = 1;
        monsterHp -= monsterDamaged;
        if (monsterHp < 0)
            monsterHp = 0;

        printf("몬스터의 체력이 %d 남았습니다\n", monsterHp);
        if (monsterHp == 0)
        {
            printf("몬스터를 처지했습니다\n");
            levelUp(monsterExp);
            
            return;
        }

        int playerDamaged = monsterAttack - playerDefence; // 플레이어가 입는 데미지(몬스터 턴)
        if (playerDamaged <= 0)
            playerDamaged = 1;
        playerHp -= playerDamaged;
        if (playerHp < 0)
            playerHp = 0;

        printf("당신의 체력이 %d 남았습니다\n", playerHp);
        if (playerHp == 0)
        {
            printf("당신은 죽었습니다\n");
            printf("게임을 재시작합니다\n");
            playerExp = 0;
            playerLevel = 1;
            break;
        }

    }
}

void levelUp(int monsterexp)
{
    playerExp += monsterexp;
    if (playerExp >= 100)
    {
        playerLevel += playerExp / 100;
        printf("%d 레벨업!\n", (playerExp / 100));
        printf("당신은 %dlv이 되었습니다 축하합니다\n", playerLevel);

        playerExp = playerExp % 100;
        upgradePlayerStat();
        playerHp = hpMax;
    }

}

void upgradePlayerStat()
{
    for (int i = 0; i * 5 <= playerLevel; i++)
    {
        playerAttack += i * 5;
        playerAttack -= (i - 1) * i / 2 * 5;
        playerHp += i * 30;
        playerHp -= (i - 1) * i / 2 * 30;
        hpMax += i * 30;
        hpMax -= (i - 1) * i / 2 * 30;
        playerDefence += i * 2;
        playerDefence -= (i - 1) * i / 2 * 2;
        
        
    }
    
}

void upgradeMonsterStat()
{
    for (int i = 0; i * 5 <= playerLevel; i++)
    {
        monsterAttack += i * 3;
        monsterAttack -= (i - 1) * i / 2 * 3;
        monsterHp += i * 15;
        monsterHp -= (i - 1) * i / 2 * 15;
        monsterDefence += i * 3;
        monsterDefence -= (i - 1) * i / 2 * 3;
    }
}


// text RPG를 위한 함수들 및 전역 변수 선언들

// hangman을 위한 함수
void scoreforhangman(int count)
{
    if (count == 0)
    {
        printf("\t┌─┐\n");
        printf("\t    │\n");
        printf("\t    │\n");
        printf("\t    │\n");
        printf("\t    ┴\n");
    }
    else if (count == 1)
    {
        printf("\t ┌──┐\n");
        printf("\t ○ │\n");
        printf("\t    │\n");
        printf("\t    │\n");
        printf("\t    ┴\n");
    }
    else if (count == 2)
    {
        printf("\t ┌──┐\n");
        printf("\t ○ │\n");
        printf("\t │  │\n");
        printf("\t    │\n");
        printf("\t    ┴\n");
    }
    else if (count == 3)
    {
        printf("\t ┌──┐\n");
        printf("\t ○ │\n");
        printf("\t/│  │\n");
        printf("\t    │\n");
        printf("\t    ┴\n");
    }
    else if (count == 4)
    {
        printf("\t ┌──┐\n");
        printf("\t ○ │\n");
        printf("\t/│\\ │\n");
        printf("\t    │\n");
        printf("\t    ┴\n");
    }
    else if (count == 5)
    {
        printf("\t ┌──┐\n");
        printf("\t ○ │\n");
        printf("\t/│\\ │\n");
        printf("\t /  │\n");
        printf("\t    ┴\n");
    }
    else if (count == 6)
    {
        printf("\t ┌──┐\n");
        printf("\t ○ │\n");
        printf("\t/│\\ │\n");
        printf("\t / \\│\n");
        printf("\t    ┴\n");
    }
}
int hangman()
{
    int select;
    int num = 25;
    char word[25][15] = {
       {"apple"}, {"cat"}, {"dog"}, {"banana"}, {"culture"}, {"effort"}, {"address"}, {"autumn"},
       {"between"}, {"bridge"}, {"cloud"}, {"dolphin"}, {"dream"}, {"eraser"}, {"family"}, {"garden"}, {"ground"},
       {"guitar"}, {"hamburger"}, {"home"}, {"jungle"}, {"knife"}, {"library"}, {"mirror"}
    };
    srand(time(NULL));
    select = rand() % num;

    char problem[15] = { 0, };
    char answer[15] = { 0, };
    char char_answer[3];
    char wrong_word[15] = { 0, };


    int len_answer;
    int count = 0;

    len_answer = strlen(word[select]);
    strcpy(problem, word[select]);

    for (int i = 0; i < len_answer; i++)
    {
        answer[i] = '_';
        printf("%c", answer[i]);
    }

    while (1)
    {
        printf("\n단어를 입력해 주세요: ");
        scanf("%s", &char_answer);
        int right = 0;

        for (int i = 0; i < len_answer; i++)
        {
            if (problem[i] == char_answer[0])
            {
                answer[i] = problem[i];
                right = 1;
            }

        }

        if (right == 0)
        {
            printf("없는 문자에요!\n");
            strcat(wrong_word, &char_answer);
            printf(" 답이 아닌 단어 : %s ", &wrong_word);
            puts("\n");
            count++;
            scoreforhangman(count);
        }

        for (int i = 0; i < len_answer; i++)
        {
            printf("%c", answer[i]);
        }
        printf("\n");
        if (strcmp(answer, problem) == 0)
        {
            printf("정답!\n");
            break;
        }
        if (count == 6)
        {
            printf("기회를 다 써버렸어요\n");
            printf("정답은 \"%s\" 였습니다\n", problem);
            break;
        }
    }
    return 0;
}
// hangman을 위한 함수

// 2048을 위한 함수들 및 전역 변수 선언들
int score = 0;
int board[5][5] = {
   {0,0,0,0,0},
   {0,0,0,0,0},
   {0,0,0,0,0},
   {0,0,0,0,0},
   {0,0,0,0,0}
};
void draw(void);
void new_num(void);
void check_game_over(void);

void draw(void) {
    int i, j;
    system("cls");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (board[i][j] == 0) printf("    .");
            else printf("%5d", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Score : %d \n", score);
}
void new_num(void) {
    int i, j;
    int cnt;
    int* p0[25] = { 0 };
    for (i = 0, cnt = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            if (board[i][j] == 0) {
                p0[cnt] = &board[i][j];
                cnt++;
            }
    }
    *p0[rand() % (cnt)] = (rand() % 100 < 80) ? 2 : 4;
}
void new_num2(void) {
    int i, j;
    int cnt;
    int* p0[25] = { 0 };
    for (i = 0, cnt = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            if (board[i][j] == 0) {
                p0[cnt] = &board[i][j];
                cnt++;
            }
    }
    *p0[rand() % (cnt)] = (rand() % 100 < 80) ? 4 : 8;
}
void check_game_over(void) {
    int i, j;
    for (i = 0; i < 5; i++) for (j = 0; j < 5; j++) if (board[i][j] == 0) return;
    for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) if (board[i][j] == board[i + 1][j] || board[i][j] == board[i][j + 1]) return;
    for (i = 0; i < 4; i++) if (board[i][4] == board[i + 1][4]) return;
    for (j = 0; j < 4; j++) if (board[4][j] == board[4][j + 1]) return;
    printf("Game Over..");
    exit(0);
}
// 2048을 위한 함수들 및 전역 변수 선언들

// 메인함수
int main()
{

    printf("(1)TextRPG (2)Hangman (3) 2048\n");
    printf(">> ");
    int input;
    scanf_s("%d", &input);

    switch (input)
    {
    case 1:
    {
        srand((unsigned int)time(NULL));

        startLobby();
        break;
    }

    case 2:
    {
        printf("-----게임 시작!-----\n");
        hangman();

        break;
    }



    case 3:
    {
        new_num();
        new_num();
        draw();
        while (1) {
            int i, j, r, k = 0;
            int key;
            int act = 0;
            key = _getch();
            if (key == 0xE0 || key == 0) {
                key = _getch();
                switch (key) {
                case LEFT:
                    for (i = 0, act = 0; i < 5; i++) {
                        for (j = 1; j <= 4; j++) {
                            for (r = j; r > 0; r--) {
                                if (board[i][r] == 0 || board[i][r] > 10000) break;
                                if (board[i][r - 1] != 0 && board[i][r - 1] != board[i][r]) break;
                                if (board[i][r - 1] == 0) board[i][r - 1] = board[i][r];
                                else if (board[i][r] == board[i][r - 1]) {
                                    board[i][r - 1] *= 2;
                                    board[i][r - 1] += 10000;
                                    score += 2 * (board[i][r]);
                                }
                                board[i][r] = 0;
                                act++;
                                k++;
                            }
                        }
                    }
                    break;
                case RIGHT:
                    for (i = 0, act = 0; i < 5; i++) {
                        for (j = 3; j >= 0; j--) {
                            for (r = j; r < 4; r++) {
                                if (board[i][r] == 0 || board[i][r] > 10000) break;
                                if (board[i][r + 1] != 0 && board[i][r + 1] != board[i][r]) break;
                                if (board[i][r + 1] == 0) board[i][r + 1] = board[i][r];
                                else if (board[i][r] == board[i][r + 1]) {
                                    board[i][r + 1] *= 2;
                                    board[i][r + 1] += 10000;
                                    score += 2 * (board[i][r]);
                                }
                                board[i][r] = 0;
                                act++;
                                k++;
                            }
                        }
                    }
                    break;
                case UP:
                    for (j = 0, act = 0; j < 5; j++) {
                        for (i = 1; i <= 4; i++) {
                            for (r = i; r > 0; r--) {
                                if (board[r][j] == 0 || board[r][j] > 10000) break;
                                if (board[r - 1][j] != 0 && board[r - 1][j] != board[r][j]) break;
                                if (board[r - 1][j] == 0) board[r - 1][j] = board[r][j];
                                else if (board[r][j] == board[r - 1][j]) {
                                    board[r - 1][j] *= 2;
                                    board[r - 1][j] += 10000;
                                    score += 2 * (board[r][j]);
                                }
                                board[r][j] = 0;
                                act++;
                                k++;
                            }
                        }
                    }
                    break;
                case DOWN:
                    for (j = 0, act = 0; j < 5; j++) {
                        for (i = 3; i >= 0; i--) {
                            for (r = i; r < 4; r++) {
                                if (board[r][j] == 0 || board[r][j] > 10000) break;
                                if (board[r + 1][j] != 0 && board[r + 1][j] != board[r][j]) break;
                                if (board[r + 1][j] == 0) board[r + 1][j] = board[r][j];
                                else if (board[r][j] == board[r + 1][j]) {
                                    board[r + 1][j] *= 2;
                                    board[r + 1][j] += 10000;
                                    score += 2 * (board[r][j]);
                                }
                                board[r][j] = 0;
                                act++;
                                k++;
                            }
                        }
                    }
                    break;
                }
            }
            for (i = 0; i < 5; i++) {
                for (j = 0; j < 5; j++) {
                    if (board[i][j] > 10000)
                        board[i][j] -= 10000;
                }
            }
            if (act > 0 && k < 100) {
                new_num();
                draw();
                check_game_over();
            }
            else if (act > 0 && k >= 100)
            {
                new_num2();
                draw();
                check_game_over();
            }
        }

        break;
    }
    default:
        break;
    }

    return 0;

}