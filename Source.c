#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
// 2048�� ���� ����
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
// 2048�� ���� ����

// text RPG�� ���� �Լ��� �� �������� �����
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
int playerAttack;
int plyaerDefence;
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
void upgradestat();

void startLobby()
{
    while (1)
    {
        printf("�κ� �����ϼ̽��ϴ�\n");

        // ���� ����
        selectJob();

        printf("(1) �ʵ� ���� (2) ���� ����");
        int input;
        scanf_s("%d", &input);

        if (input == 1)
        {
            // �ʵ� ����
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
        printf("������ �������ּ���\n");
        printf("(1) ���� (2) �ü� (3) ����\n");
        printf(">>");

        scanf_s("%d", &playerType);

        if (playerType == Knight)
        {
            printf("��� ������\n");
            playerHp = 200;
            playerAttack = 10;
            plyaerDefence = 8;
            break;
        }
        else if (playerType == Archer)
        {
            printf("�ü� ������\n");
            playerHp = 100;
            playerAttack = 25;
            plyaerDefence = 3;
            break;
        }
        else if (playerType == Assasin)
        {
            printf("���� ������\n");
            playerHp = 150;
            playerAttack = 20;
            plyaerDefence = 5;
            break;
        }
    }

}

void enterField()
{
    while (1)
    {
        printf("�ʵ忡 �����ϼ̽��ϴ�!\n");
        printf("����� ����(HP: %d AD: %d DF: %d)\n", playerHp, playerAttack, plyaerDefence);

        createMonster();

        printf("(1) �ο�� (2) ����ģ��\n");
        printf(">> ");
        int input;
        scanf_s("%d", &input);

        if (input == 1)
        {
            enterBattle();
            if (playerHp == 0)
                break; // �÷��̾� ��� -> �ʵ� ������ �Ұ�
        }


    }
}

void createMonster()
{
    monsterType = 1 + rand() % 3;

    switch (monsterType)
    {
    case Slime:
        printf("������ ������ (HP: 15 / ATT: 5 / DEF: 0)\n");
        monsterHp = 15;
        monsterAttack = 5;
        monsterDefence = 0;
        monsterExp = 10;
        if (playerLevel >= 5)
            break;
    case Orce:
        printf("��ũ ������ (HP: 50 / ATT: 15 / DEF: 15)\n");
        monsterHp = 50;
        monsterAttack = 15;
        monsterDefence = 8;
        monsterExp = 50;

        break;
    case Troll:
        printf("Ʈ�� ������ (HP: 30 / ATT: 10 / DEF: 5)\n");
        monsterHp = 30;
        monsterAttack = 10;
        monsterDefence = 5;
        monsterExp = 30;

        break;

    }
}

void enterBattle()
{
    while (1)
    {
        int monsterDamaged = playerAttack - monsterDefence; // ���Ͱ� �Դ� ������(�÷��̾� ��)
        if (monsterDamaged <= 0) // �������� 0 Ȥ�� ������ ������ 1�� �⺻���ط� ����
            monsterDamaged = 1;
        monsterHp -= monsterDamaged;
        if (monsterHp < 0)
            monsterHp = 0;

        printf("������ ü���� %d ���ҽ��ϴ�\n", monsterHp);
        if (monsterHp == 0)
        {
            printf("���͸� ó���߽��ϴ�\n");
            levelUp(monsterExp);

            return;
        }

        int playerDamaged = monsterAttack - plyaerDefence; // �÷��̾ �Դ� ������(���� ��)
        if (playerDamaged <= 0)
            playerDamaged = 1;
        playerHp -= playerDamaged;
        if (playerHp < 0)
            playerHp = 0;

        printf("����� ü���� %d ���ҽ��ϴ�\n", playerHp);
        if (playerHp == 0)
        {
            printf("����� �׾����ϴ�\n");
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
        printf("%d ������!\n", (playerExp / 100));
        printf("����� %dlv�� �Ǿ����ϴ� �����մϴ�\n", playerLevel);

        playerExp = monsterexp % 100;
        upgradestat();
    }

}

void upgradestat()
{
    for (int i = 1; playerLevel >= i * 5; i++) // 5, 10, 15 ... 100�� �� ������ Ȯ���ϴ� �ͺ��� �ݺ����� ���°� �� ���ٰ� �Ǵ��ߴ�.
    {
        playerAttack += i * 5;               // �÷��̾� ���� ���(������ 5, 10, 15 ...5�� ����� �� ��)
        playerAttack -= (i - 1) * i / 2 * 5; // �� ���� ���ִ� ������ 15������ �� 15�� �÷��ִ°� �����ε�, 
        // �ݺ��� ������ 5(1+2+3)�� �÷��ְ� �ǹǷ� 5(1+2)�� ���� ���ִ� ���̴�. 
        playerHp += i * 30;
        playerHp -= (i - 1) * i / 2 * 30;
        plyaerDefence += i * 2;
        plyaerDefence -= (i - 1) * i / 2 * 2;

        monsterAttack += i * 3; // ���͵鵵 ��ȭ��
        monsterAttack -= (i - 1) * i / 2 * 3;
        monsterHp += i * 15;
        monsterHp -= (i - 1) * i / 2 * 15;
        monsterDefence += i * 2;
        monsterDefence -= (i - 1) * i / 2 * 2;
    }
}
// text RPG�� ���� �Լ��� �� ���� ���� �����

// hangman�� ���� �Լ�
void scoreforhangman(int count)
{
    if (count == 0)
    {
        printf("\t������\n");
        printf("\t    ��\n");
        printf("\t    ��\n");
        printf("\t    ��\n");
        printf("\t    ��\n");
    }
    else if (count == 1)
    {
        printf("\t ��������\n");
        printf("\t �� ��\n");
        printf("\t    ��\n");
        printf("\t    ��\n");
        printf("\t    ��\n");
    }
    else if (count == 2)
    {
        printf("\t ��������\n");
        printf("\t �� ��\n");
        printf("\t ��  ��\n");
        printf("\t    ��\n");
        printf("\t    ��\n");
    }
    else if (count == 3)
    {
        printf("\t ��������\n");
        printf("\t �� ��\n");
        printf("\t/��  ��\n");
        printf("\t    ��\n");
        printf("\t    ��\n");
    }
    else if (count == 4)
    {
        printf("\t ��������\n");
        printf("\t �� ��\n");
        printf("\t/��\\ ��\n");
        printf("\t    ��\n");
        printf("\t    ��\n");
    }
    else if (count == 5)
    {
        printf("\t ��������\n");
        printf("\t �� ��\n");
        printf("\t/��\\ ��\n");
        printf("\t /  ��\n");
        printf("\t    ��\n");
    }
    else if (count == 6)
    {
        printf("\t ��������\n");
        printf("\t �� ��\n");
        printf("\t/��\\ ��\n");
        printf("\t / \\��\n");
        printf("\t    ��\n");
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
        printf("\n�ܾ �Է��� �ּ���: ");
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
            printf("���� ���ڿ���!\n");
            strcat(wrong_word, &char_answer);
            printf(" ���� �ƴ� �ܾ� : %s ", &wrong_word);
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
            printf("����!\n");
            break;
        }
        if (count == 6)
        {
            printf("��ȸ�� �� ����Ⱦ��\n");
            printf("������ \"%s\" �����ϴ�\n", problem);
            break;
        }
    }
    return 0;
}


// hangman�� ���� �Լ�

// 2048�� ���� �Լ��� �� ���� ���� �����
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
// 2048�� ���� �Լ��� �� ���� ���� �����

// �����Լ�
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
        printf("-----���� ����!-----\n");
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