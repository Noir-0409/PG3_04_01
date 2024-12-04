#include <Novice.h>


//********************
//構造体
//********************

//Vector2
typedef struct Vector2 {
	float x;
	float y;
}Vector2;

// ブロックに使うベクトル
typedef struct IntVector2 {
	int x;
	int y;
}IntVector2;

// ブロック
typedef struct Corners {
	IntVector2 LeftTop;
	IntVector2 RightTop;
	IntVector2 LeftDown;
	IntVector2 RightDown;
}Corners;

//Player
typedef struct Player {
	Vector2 pos;
	Vector2 provPos;
	Vector2 verocity;
	Vector2 acceleration;
	Vector2 anotherPos;
	float r;
	int jumpCoolTime;
	int jumpCount;
	Corners corners;
	int isOnGround;
	int isMove;
	int isAlive;
	int isWave;
	int isAttack;
}Player;

/*Movewall*/
typedef struct Movewall {
	Vector2 pos;
	Vector2 provPos;
	Vector2 verocity;
	Vector2 acceleration;
	float speed;
	float r;
	int isDown;
	Corners corners;
}Movewall;

typedef struct Movewall2 {
	Vector2 pos;
	Vector2 provPos;
	Vector2 verocity;
	Vector2 acceleration;
	float speed;
	float r;
	int isDown;
	Corners corners;
}Movewall2;

// ブロックの当たり判定の関数d
int HitBox(int a[24][43], Corners b) {
	if (a[static_cast<int>(b.LeftTop.y)][static_cast<int>(b.LeftTop.x)] <= 2 && a[static_cast<int>(b.LeftTop.y)][static_cast<int>(b.LeftTop.x)] >= 1 ||
		a[static_cast<int>(b.RightTop.y)][static_cast<int>(b.RightTop.x)] <= 2 && a[static_cast<int>(b.RightTop.y)][static_cast<int>(b.RightTop.x)] >= 1 ||
		a[static_cast<int>(b.LeftDown.y)][static_cast<int>(b.LeftDown.x)] <= 2 && a[static_cast<int>(b.LeftDown.y)][static_cast<int>(b.LeftDown.x)] >= 1 ||
		a[static_cast<int>(b.RightDown.y)][static_cast<int>(b.RightDown.x)] <= 2 && a[static_cast<int>(b.RightDown.y)][static_cast<int>(b.RightDown.x)] >= 1) {


		return 1;
	} else if (a[static_cast<int>(b.LeftTop.y)][static_cast<int>(b.LeftTop.x)] == 5 ||
		a[static_cast<int>(b.RightTop.y)][static_cast<int>(b.RightTop.x)] == 5 ||
		a[static_cast<int>(b.LeftDown.y)][static_cast<int>(b.LeftDown.x)] == 5 ||
		a[static_cast<int>(b.RightDown.y)][static_cast<int>(b.RightDown.x)] == 5) {

		return 2;

	} else {
		return 0;
	}
}

//	角の関数
Corners posUpdate(Vector2 a, float b) {
	Corners c;

	c.LeftTop.x = static_cast<int>(a.x / 32.0f);
	c.LeftTop.y = static_cast<int>(a.y / 32.0f);

	c.RightTop.x = static_cast<int>((a.x + b - 1) / 32.0f);
	c.RightTop.y = static_cast<int>(a.y / 32.0f);

	c.LeftDown.x = static_cast<int>(a.x / 32.0f);
	c.LeftDown.y = static_cast<int>((a.y + b - 0.5f) / 32.0f);

	c.RightDown.x = static_cast<int>((a.x + b - 1) / 32.0f);
	c.RightDown.y = static_cast<int>((a.y + b - 0.5f) / 32.0f);

	return c;
}

//矩形の当たり判定
int HitTile(Corners a, Corners b) {
	if (b.LeftTop.x <= a.RightTop.x && a.LeftTop.x <= b.RightTop.x) {
		if (b.LeftTop.y <= a.RightDown.y && a.LeftTop.y <= b.RightDown.y) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

//角の関数
Corners posUpdateTile(Vector2 a, float b) {
	Corners c = {};

	c.LeftTop.x = static_cast<int>(a.x);
	c.LeftTop.y = static_cast<int>(a.y);

	c.RightTop.x = static_cast<int>((a.x + b - 1));
	c.RightTop.y = static_cast<int>(a.y);

	c.LeftDown.x = static_cast<int>(a.x);
	c.LeftDown.y = static_cast<int>((a.y + b - 0.5f));

	c.RightDown.x = static_cast<int>((a.x + b - 1));
	c.RightDown.y = static_cast<int>((a.y + b - 0.5f));

	return c;
}



const char kWindowTitle[] = "LC1C_14_サクマ_シン_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//********************
	//初期化
	//********************

	//********************
	//Player
	//********************

	Player player = {
		{100.0f,600.0f},	// pos
		{0.0f,0.0f},		// provPos
		{0.0f,0.0f},		// velocity
		{0.0f,0.8f},		// acceleration
		{0.0f,0.0f},		// anotherPos
		32.0f,				// radius
		4,					// jumpCoolTime
		0,					// jumpCount
	};

	player.isMove = false;
	player.isAlive = true;
	player.isWave = false;
	//player.isAttack = false;
	//player.isMove = false;
	//int wbTimer = 120;

	//********************
	//動かす壁の初期化
	//********************

	Movewall wall = {
		{200.0f,480.0f},	// pos
		{0.0f,0.0f},		// provPos
		{0.0f,0.0f},		// velocity
		{0.0f,0.8f},		// acceleration
		4.0f,				// speed
		{64.0f},			// radiusY
	};

	wall.isDown = false;

	Movewall2 wall2 = {
		{450.0f,128.0f},	// pos
		{0.0f,0.0f},		// provPos
		{0.0f,0.0f},		// velocity
		{0.0f,0.8f},		// acceleration
		4.0f,				// speed
		{64.0f},			// radiusY
	};

	//wall2.isDown = false;

	//********************
	//Enum
	//********************

	enum scene {
		START,
		SELECT,
		TUTORIAL,
		CREGIT,
		STAGE1,
		STAGE2,
		STAGE3,
		SCORE,
		OVER
	};

	int scene = START;

	int stage1Map[24][43] = {

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,7,7,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1}

	};

	int stage2Map[25][25] = {

		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	int stage3Map[25][25] = {

		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	/*int isBreak = false;
	int isPush = false;*/

	int isLand = false;
	//int isStop = true;
	int isBreak = false;
	int isBreak2 = false;


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);



		Novice::ScreenPrintf(20, 70, "scene=%d", scene);
		Novice::ScreenPrintf(20, 100, "px=%f", wall.pos.x);

		Novice::ScreenPrintf(20, 130, "px=%f", player.pos.y);

		switch (scene) {
		case START:
			//START更新処理
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = SELECT;
			}
			//START更新ここまで
			//START描画処理

			//START描画ここまで
			break;

		case SELECT:
			//SELECT更新処理
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = TUTORIAL;
			}
			//SELECT更新ここまで
			//SELECT描画処理

			//SELECT描画ここまで
			break;

		case TUTORIAL:
			//TUTORIAL更新処理
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = STAGE1;
			}
			//TUTORIAL更新ここまで
			//TUTORIAL描画処理

			//TUTORIAL描画ここまで
			break;

		case STAGE1:
			//STAGE1更新処理
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = START;
			}

			if (keys[DIK_RIGHT] || keys[DIK_D]) {
				player.verocity.x = 3.0f;
			}

			if (keys[DIK_LEFT] || keys[DIK_A]) {
				player.verocity.x = -3.0f;
			}

			if (!keys[DIK_LEFT] && !keys[DIK_A] && !keys[DIK_RIGHT] && !keys[DIK_D]) {
				player.verocity.x = 0.0f;
			}


			player.verocity.y = +16.0f;
			player.provPos.x += player.verocity.x;
			player.provPos.y += player.verocity.y;

			player.corners = posUpdate(player.provPos, player.r);
			if (HitBox(stage1Map, player.corners)) {


				player.provPos = player.pos;


				player.provPos.x += player.verocity.x;

				player.corners = posUpdate(player.provPos, player.r);



				// ブロックに横からぶつかったとき、ブロックの横で止まる
				if (HitBox(stage1Map, player.corners)) {
					// プレイヤーの横速度が0より高いとき
					if (player.verocity.x > 0) {
						// プレイヤーのx座標がブロックにめり込まないよう止まる
						player.pos.x = player.corners.RightDown.x * 32.0f - player.r;

					} else {
						player.pos.x = player.corners.RightDown.x * 32.0f;
					}


					player.provPos = player.pos;


					player.provPos.y += player.verocity.y;

					player.corners = posUpdate(player.provPos, player.r);


					// ブロックの上下の処理
					if (HitBox(stage1Map, player.corners)) {
						// プレイヤーの縦速度が0より高いとき
						if (player.verocity.y >= 0) {
							// プレイヤーのy座標がブロックにめり込まないよう止まる
							player.pos.y = player.corners.RightDown.y * 32.0f - player.r;

							// y速度を0にして接地させる
							player.verocity.y = 0.0f;
							player.isOnGround = true;
						} else {
							player.pos.y = player.corners.RightDown.y * 32.0f;
							player.verocity.y += player.acceleration.y + 1.6f;
						}

					} else {
						player.pos.y = player.provPos.y;
					}


					// 横からブロックにぶつかっていないとき
				} else {
					player.pos = player.provPos;

					player.provPos = player.pos;


					player.provPos.y += player.verocity.y;

					player.corners = posUpdate(player.provPos, player.r);


					// ブロックの上下の処理
					if (HitBox(stage1Map, player.corners)) {

						if (player.verocity.y >= 0) {

							player.pos.y = player.corners.RightDown.y * 32.0f - player.r;


							player.verocity.y = 0.0f;

						} else {
							player.pos.y = player.corners.RightDown.y * 32.0f;
							player.verocity.y += player.acceleration.y + 1.6f;
						}


					} else {
						player.pos.y = player.provPos.y;
					}
				}
			} else {
				player.pos = player.provPos;
			}


			player.provPos = player.pos;
			player.pos.x += player.verocity.x;
			player.verocity.y += player.acceleration.y;



			//********************
			//壁とplayerの当たり判定
			//********************

			//wall.verocity.y = +16.0f;
			wall.provPos.x += wall.verocity.x;
			wall.provPos.y += wall.verocity.y;

			//player.pos = player.provPos;
			player.corners = posUpdateTile(player.provPos, player.r);


			wall.corners = posUpdateTile(wall.provPos, wall.r);

			if (HitTile(player.corners, wall.corners)) {

				/*if (isStop) {
					player.verocity.x = 0.0f;
					player.acceleration.x = 0.0f;
				}*/


				//isStop = false;


				if (!isBreak) {
					player.pos = player.provPos;
					//wall.pos = wall.provPos;
					wall.pos.x += wall.speed;
				}


				//壁を壊す
				if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {

					isBreak = true;

				}



			} else {
				player.provPos = player.pos;
				wall.provPos = wall.pos;
			}




			//*******************
			//壁を地面に埋める
			//*******************
			if (wall.pos.x >= 384.0f) {
				wall.pos.x = 384.0f;
				wall.isDown = true;
			}

			if (wall.isDown) {
				wall.speed = 14.0f;
				wall.pos.y += wall.speed;
			}

			if (wall.pos.y >= 544.0f) {
				wall.isDown = false;
				wall.speed = 0.0f;
				wall.pos.x = 384.0f;
				wall.pos.y = 544.0f;
				isLand = true;
			}

			if (isLand) {
				for (int i = 0; i < 23; i++) {
					for (int j = 0; j < 250; j++) {
						if (stage1Map[i][j] == 7) {
							stage1Map[i][j] = 1;

						}
					}
				}
			}

			player.provPos = player.pos;
			//player.pos.x += player.verocity.x;
			//player.verocity.y += player.acceleration.y;

			//2

			//wall.verocity.y = +16.0f;
			wall2.provPos.x += wall2.verocity.x;
			wall2.provPos.y += wall2.verocity.y;

			player.pos = player.provPos;
			player.corners = posUpdateTile(player.provPos, player.r);


			wall2.corners = posUpdateTile(wall2.provPos, wall2.r);

			if (HitTile(player.corners, wall2.corners)) {

				/*if (isStop) {
					player.verocity.x = 0.0f;
					player.acceleration.x = 0.0f;
				}*/


				//isStop = false;


				if (!isBreak2) {
					player.pos = player.provPos;
					//wall.pos = wall.provPos;
					wall2.pos.x -= wall2.speed;
				}


				//壁を壊す
				if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {

					isBreak2 = true;

				}



			} else {
				player.provPos = player.pos;
				wall2.provPos = wall2.pos;
			}





			//STAGE1更新ここまで

			//STAGE1描画処理
			// マップ
			for (int i = 0; i < 25; i++) {
				for (int j = 0; j < 250; j++) {
					if (stage1Map[i][j] == 1) {
						Novice::DrawBox(
							j * 32,
							i * 32,
							32,
							32,
							0.0f,
							0x524b24ff,
							kFillModeSolid
						);
					}
				}
			}



			//壁
			if (!isBreak) {
				Novice::DrawBox(
					int(wall.pos.x), int(wall.pos.y),
					int(wall.r), int(wall.r),
					0.0f, BLUE,
					kFillModeSolid
				);
			}

			if (!isBreak2) {
				Novice::DrawBox(
					int(wall2.pos.x), int(wall2.pos.y),
					int(wall2.r), int(wall2.r),
					0.0f, BLUE,
					kFillModeSolid
				);
			}


			Novice::DrawBox(
				int(player.pos.x), int(player.pos.y),
				32, 32,
				0.0f, RED,
				kFillModeSolid
			);

			Novice::ScreenPrintf(20, 20, "wall.pos.x:%f", wall.pos.x);
			Novice::ScreenPrintf(20, 35, "wall.pos.Y:%f", wall.pos.y);
			//STAGE1描画ここまで
			//STAGE1描画ここまで
			break;

		case STAGE2:
			//STAGE2更新処理

			//STAGE2更新ここまで
			//STAGE2描画処理

			//STAGE2描画ここまで
			break;

		case STAGE3:
			//STAGE3更新処理

			//STAGE3更新ここまで
			//STAGE3描画処理

			//STAGE3描画ここまで
			break;

		case OVER:
			//OVER更新処理

			//OVER更新ここまで
			//OVER描画処理

			//OVER描画ここまで
			break;
		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}