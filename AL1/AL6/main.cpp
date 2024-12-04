#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "AL1_Debug";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef struct Player {
    Vector2 pos;
    float width;
    float height;
    float speed;
    int shootCoolTime;
} Player;

typedef struct Bullet {
    Vector2 pos;
    float width;
    float height;
    float radius;
    float speed;
    int isShoot;
} Bullet;

typedef struct Enemy {
    Vector2 pos;
    float width;
    float height;
    float radius;
    float speed;
    int isAlive;
    int respawnTimer;
} Enemy;

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ���C�u�����̏�����
    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

    // �L�[���͌��ʂ��󂯎�锠
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    //================================================================
    // �ϐ��Ə�����
    //================================================================

    // ���@�̕ϐ�
    Player player;
    player.pos.x = kWindowWidth / 2.0f;
    player.pos.y = kWindowHeight / 2.0f + 256.0f;
    player.width = 32.0f;
    player.height = 32.0f;
    player.speed = 4.0f;
    player.shootCoolTime = 10;

    // �e�̕ϐ�
    Bullet bullet[32];
    for (int i = 0; i < 32; i++) {
        bullet[i].pos.x = -128.0f;
        bullet[i].pos.y = -128.0f;
        bullet[i].width = 8.0f;
        bullet[i].height = 16.0f;
        bullet[i].radius = 8.0f;
        bullet[i].speed = 8.0f;
        bullet[i].isShoot = false;
    }

    // �G�̕ϐ�
    Enemy enemy[8];
    for (int i = 0; i < 8; i++) {
        enemy[i].pos.x = 128.0f + i * 64.0f;
        enemy[i].pos.y = 32.0f + i * 64.0f;
        enemy[i].width = 32.0f;
        enemy[i].height = 32.0f;
        enemy[i].radius = 16.0f;
        enemy[i].speed = 2.0f;
        enemy[i].isAlive = true;
        enemy[i].respawnTimer = 120;
    }

    // �E�B���h�E�́~�{�^�����������܂Ń��[�v
    while (Novice::ProcessMessage() == 0) {
        // �t���[���̊J�n
        Novice::BeginFrame();

        // �L�[���͂��󂯎��
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ���X�V������������
        ///

        //================================================================
        // ���@�̍X�V����
        //================================================================

        // ���@�̈ړ�����
        if (keys[DIK_W]) {
            if (player.pos.y > 0 + player.height / 2.0f) {
                player.pos.y -= player.speed;
            }
        }

        if (keys[DIK_S]) {
            if (player.pos.y < kWindowHeight - player.height / 2.0f) {
                player.pos.y += player.speed;
            }
        }

        if (keys[DIK_A]) {
            if (player.pos.x > 0 + player.width / 2.0f) {
                player.pos.x -= player.speed;
            }
        }

        if (keys[DIK_D]) {
            if (player.pos.x < kWindowWidth - player.width / 2.0f) {
                player.pos.x += player.speed;
            }
        }

        //================================================================
        // �e�̍X�V����
        //================================================================

        // �e�̔��ˏ���
        if (keys[DIK_SPACE]) {

            // ���ˊԊu�̒����p�N�[���^�C���̌v�Z
            if (player.shootCoolTime > 0) {
                player.shootCoolTime--;
            } else {
                player.shootCoolTime = 10;
            }

            // i�Ԗڂ̒e��������Ă��Ȃ������甭�˂���
            if (player.shootCoolTime <= 0) {
                for (int i = 0; i < 32; i++) {
                    if (!bullet[i].isShoot) {
                        bullet[i].isShoot = true;
                        bullet[i].pos.x = player.pos.x;
                        bullet[i].pos.y = player.pos.y;
                        break;
                    }
                }
            }
        }



        // �e���v�Z
        for (int i = 0; i < 32; i++) {
            if (bullet[i].isShoot) {
                // ������ɐi�܂���
                bullet[i].pos.y -= bullet[i].speed;

                // ��ʊO�ɏo���甭�˃t���O��False�ɕύX����
                if (bullet[i].pos.y <= 0 - bullet[i].height / 2.0f) {
                    bullet[i].isShoot = false;
                }
            }
        }

        //================================================================
        // �G�̍X�V����
        //================================================================

        for (int i = 0; i < 8; i++) {
            if (enemy[i].isAlive) {
                enemy[i].pos.x += enemy[i].speed;

                // �ǍۂŔ���
                if (enemy[i].pos.x <= 0 + enemy[i].width / 2.0f ||
                    enemy[i].pos.x >= kWindowWidth - enemy[i].width / 2.0f) {
                    enemy[i].speed *= -1.0f;
                }
            } else {
                if (enemy[i].respawnTimer > 0) {
                    enemy[i].respawnTimer--;
                } else {
                    enemy[i].respawnTimer = 0;
                    enemy[i].isAlive = true;
                }
            }
        }

        //================================================================
        // �����蔻��
        //================================================================

        for (int i = 0; i < 8; i++) {
            if (enemy[i].isAlive) {
                for (int j = 0; j < 32; j++) {
                    if (bullet[j].isShoot) {
                        if (enemy[i].radius + bullet[j].radius >=
                            sqrtf(static_cast<float>(
                                pow(enemy[i].pos.x - bullet[j].pos.x, 2) +
                                pow(enemy[i].pos.y - bullet[j].pos.y, 2)))) {
                            enemy[j].isAlive = false;
                            bullet[i].isShoot = false;
                        }
                    }
                }
            }
        }
        ///
        /// ���X�V���������܂�
        ///

        ///
        /// ���`�揈����������
        ///

        //================================================================
        // �G�̕`�揈��
        //================================================================
        for (int i = 0; i < 8; i++) {
            if (enemy[i].isAlive) {
                Novice::DrawBox(
                    static_cast<int>(enemy[i].pos.x - enemy[i].width / 2.0f),
                    static_cast<int>(enemy[i].pos.y - enemy[i].height / 2.0f),
                    static_cast<int>(enemy[i].width), static_cast<int>(enemy[i].height),
                    0.0f, 0xFFDDDDFF, kFillModeSolid);
            } else {
                if (enemy[i].respawnTimer >= 90) {
                    if (enemy[i].respawnTimer % 2 == 0) {
                        Novice::DrawBox(
                            static_cast<int>(enemy[i].pos.x - enemy[i].width / 2.0f),
                            static_cast<int>(enemy[i].pos.y - enemy[i].height / 2.0f),
                            static_cast<int>(enemy[i].width),
                            static_cast<int>(enemy[i].height), 0.0f, 0xFFDDDDFF,
                            kFillModeSolid);
                    }
                }
            }
        }

        //================================================================
        // �e�̕`�揈��
        //================================================================
        for (int i = 0; i < 32; i++) {
            if (bullet[i].isShoot) {
                Novice::DrawTriangle(
                    static_cast<int>(bullet[i].pos.x),
                    static_cast<int>(bullet[i].pos.y - bullet[i].height / 2.0f),
                    static_cast<int>(bullet[i].pos.x - bullet[i].width / 2.0f),
                    static_cast<int>(bullet[i].pos.y + bullet[i].height / 2.0f),
                    static_cast<int>(bullet[i].pos.x + bullet[i].width / 2.0f),
                    static_cast<int>(bullet[i].pos.y + bullet[i].height / 2.0f),
                    0xFFFFFFFF, kFillModeSolid);
            }
        }

        //================================================================
        // ���@�̕`�揈��
        //================================================================
        Novice::DrawBox(static_cast<int>(player.pos.x - player.width / 2.0f),
            static_cast<int>(player.pos.y - player.height / 2.0f),
            static_cast<int>(player.width),
            static_cast<int>(player.height), 0.0f, 0xDDDDFFFF,
            kFillModeSolid);

        ///
        /// ���`�揈�������܂�
        ///

        // �t���[���̏I��
        Novice::EndFrame();

        // ESC�L�[�������ꂽ�烋�[�v�𔲂���
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ���C�u�����̏I��
    Novice::Finalize();
    return 0;
}