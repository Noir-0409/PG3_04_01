#include <stdio.h>
int main() {
    int isConsoleEnd = 1;
    int playerHp = 100;
    int enemyAttack = 70;


    printf("�G�̍U��!%d�̃_���[�W\n", enemyAttack);
    playerHp -= enemyAttack;

    printf("�v���C���[�̎c��̗� : %d\n", playerHp);

    if (playerHp <= 0); {
        printf("�͐s�����E�E�E");
    }
    printf("\n�I�����邽�߂ɂ͐�������͂�Enter�L�[�������Ă�������...");
    scanf_s("%d", &isConsoleEnd);

    return 0;
}
