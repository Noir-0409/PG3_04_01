#include <stdio.h>
int main() {
    int isConsoleEnd = 1;
    int playerHp = 100;
    int enemyAttack = 70;


    printf("敵の攻撃!%dのダメージ\n", enemyAttack);
    playerHp -= enemyAttack;

    printf("プレイヤーの残り体力 : %d\n", playerHp);

    if (playerHp <= 0); {
        printf("力尽きた・・・");
    }
    printf("\n終了するためには数字を入力しEnterキーを押してください...");
    scanf_s("%d", &isConsoleEnd);

    return 0;
}
