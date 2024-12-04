#include <Novice.h>

/////////////////////
////////////////////
////////////////////


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
	float speed;
	float r;
	int jumpCoolTime;
	int jumpCount;
	unsigned int color;
	Corners corners;
	int isOnGround;
	int isAlive;
	Corners tileCorners;
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
	int  isMatch;
	int isLand;
	int isBreak;
	Corners corners;
}Movewall;


//typedef struct Movewall2 {
//	Vector2 pos;
//	Vector2 provPos;
//	Vector2 verocity;
//	Vector2 acceleration;
//	float speed;
//	float r;
//	int isDown;
//	Corners corners;
//}Movewall2;

/*Lift*/
typedef struct Lift {
	Vector2 pos;
	Vector2 provPos;
	Vector2 verocity;
	float widgh;
	float height;
	Corners corners;
}Lift;

// ブロックの当たり判定の関数d
int HitBox(int a[24][43], Corners b) {
	if (a[static_cast<int>(b.LeftTop.y)][static_cast<int>(b.LeftTop.x)] <= 2 && a[static_cast<int>(b.LeftTop.y)][static_cast<int>(b.LeftTop.x)] >= 1 ||
		a[static_cast<int>(b.RightTop.y)][static_cast<int>(b.RightTop.x)] <= 2 && a[static_cast<int>(b.RightTop.y)][static_cast<int>(b.RightTop.x)] >= 1 ||
		a[static_cast<int>(b.LeftDown.y)][static_cast<int>(b.LeftDown.x)] <= 2 && a[static_cast<int>(b.LeftDown.y)][static_cast<int>(b.LeftDown.x)] >= 1 ||
		a[static_cast<int>(b.RightDown.y)][static_cast<int>(b.RightDown.x)] <= 2 && a[static_cast<int>(b.RightDown.y)][static_cast<int>(b.RightDown.x)] >= 1) {


		return 1;
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

//	角の関数
Corners posUpdateTile(Vector2 a, float widgh, float height) {
	Corners c = {};

	c.LeftTop.x = static_cast<int>(a.x);
	c.LeftTop.y = static_cast<int>(a.y);

	c.RightTop.x = static_cast<int>((a.x + widgh - 1));
	c.RightTop.y = static_cast<int>(a.y);

	c.LeftDown.x = static_cast<int>(a.x);
	c.LeftDown.y = static_cast<int>((a.y + height - 0.5f));

	c.RightDown.x = static_cast<int>((a.x + widgh - 1));
	c.RightDown.y = static_cast<int>((a.y + height - 0.5f));

	return c;
}


//矩形の当たり判定
int HitTile(Corners a, Corners b) {
	if (b.LeftTop.x <= a.RightTop.x && a.LeftTop.x < b.RightTop.x) {
		if (b.LeftTop.y <= a.RightDown.y && a.LeftTop.y < b.RightDown.y) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}



const char kWindowTitle[] = "1247_Appleローチ";

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
		5.0f,				//speed
		32.0f,				// radius
		4,					// jumpCoolTime
		0,					// jumpCount
		RED					// color
	};


	player.isAlive = true;


	//********************
	//動かす壁の初期化
	//********************

	//1
	Movewall wall = {
		{200.0f,480.0f},	// pos
		{0.0f,0.0f},		// provPos
		{0.0f,0.0f},		// velocity
		{0.0f,0.8f},		// acceleration
		4.0f,				// speed
		{64.0f},			// radiusY
	};

	wall.isDown = false;
	wall.isMatch = false;
	wall.isLand = false;
	wall.isBreak = false;

	//2
	Movewall wall2 = {
		{450.0f,128.0f},	// pos
		{0.0f,0.0f},		// provPos
		{0.0f,0.0f},		// velocity
		{0.0f,0.8f},		// acceleration
		4.0f,				// speed
		{64.0f},			// radiusY
	};

	wall2.isMatch = false;
	wall2.isBreak = false;

	//3
	Movewall wall3 = {
		{648.0f,128.0f},	// pos
		{0.0f,0.0f},		// provPos
		{0.0f,0.0f},		// velocity
		{0.0f,0.8f},		// acceleration
		4.0f,				// speed
		{64.0f},			// radiusY
	};

	wall3.isMatch = false;
	wall3.isBreak = false;

	//4
	Movewall wall4 = {
	{530.0f,128.0f},	// pos
	{0.0f,0.0f},		// provPos
	{0.0f,0.0f},		// velocity
	{0.0f,0.8f},		// acceleration
	4.0f,				// speed
	{64.0f},			// radiusY
	};

	wall4.isMatch = false;
	wall4.isBreak = false;

	//5
	Movewall wall5 = {
	{950.0f,160.0f},	// pos
	{0.0f,0.0f},		// provPos
	{0.0f,0.0f},		// velocity
	{0.0f,0.8f},		// acceleration
	4.0f,				// speed
	{64.0f},			// radiusY
	};

	wall5.isMatch = false;
	wall5.isBreak = false;

	/*動く床*/
	Lift lift = {
		{832,394},	//pos
		{832,394}, //provPos
		{0.0f,4.0f},//verocity
		224.0f,		//widgh
		16.0f,		//height
	};

	Lift lift2 = {
		{832,554},	//pos
		{832,426}, //provPos
		{0.0f,4.0f},//verocity
		1.0f,		//widgh
		16.0f,		//height
	};

	//********************
	//Enum
	//********************

	enum scene {
		START,
		SELECT,
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

	int stage2Map[24][43] = {

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,1,1,1,1,1,1,1,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,1,1,1,1,1,1,1,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1}

	};


	int stage3Map[24][43] = {

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,6,6,6,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,4,4,4,4,4,1,1,1,1,1,1,1,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,4,4,4,4,4,1,1,1,1,1,1,1,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,7,7,1,1,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,7,7,1,1,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1}

	};




	//*********************
	//サウンドの初期化
	//*********************

	//1
	//int playSH = Novice::LoadAudio("./Resources/Sounds/playBH.mp3");
	//int clearSH = Novice::LoadAudio("./Resources/Sounds/clearBH.mp3");
	//int overSH = Novice::LoadAudio("./Resources/Sounds/overBH.mp3");
	//int breakSH= Novice::LoadAudio("./Resources/Sounds/breakBH.mp3");

	//2
	int playBH = 0;
	int clearBH = 0;
	int overBH = 0;
	//int breakBH = 0;



	/************************
	* 画像の読み込み
	************************/
	int titleGH = Novice::LoadTexture("./Resources./title.png");
	int bgGH = Novice::LoadTexture("./Resources./bg.png");
	int playerRightGH = Novice::LoadTexture("./Resources./playerRight.gif");
	int playerLeftGH = Novice::LoadTexture("./Resources./playerLeft.gif");
	int liftGH = Novice::LoadTexture("./Resources./lift.png");
	int wallGH = Novice::LoadTexture("./Resources./wall.png");
	int goalGH = Novice::LoadTexture("./Resources./goal.png");
	int blockGH = Novice::LoadTexture("./Resources./brock.png");
	int appleGH = Novice::LoadTexture("./Resources./apple.gif");
	/*int selectGH = Novice::LoadTexture("./Resources./select.png");
	int overGH = Novice::LoadTexture("./Resources./over.png");
	int clearGH = Novice::LoadTexture("./Resources./clear.png");
	int ruleGH = Novice::LoadTexture("./Resources./rule.png");*/
	int playerGH = playerRightGH;


	//int isStopP = false;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);



		/*Novice::ScreenPrintf(20, 100, "px=%f", wall.pos.x);

		Novice::ScreenPrintf(20, 130, "px=%f", player.pos.y);*/


		Novice::ScreenPrintf(1000, 600, "scene= %d", scene);

		switch (scene) {




		case START:
			//START更新処理
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = SELECT;
			}

			Novice::DrawSprite(
				0, 0,
				titleGH,
				1.0f,
				1.0f,
				0.0f, WHITE
			);
			//START更新ここまで
			//START描画処理

			//START描画ここまで
			break;

		case SELECT:
			//SELECT更新処理
			/*if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = TUTORIAL;
			}*/

			if (keys[DIK_1] && !preKeys[DIK_1]) {
				scene = STAGE1;
			}


			if (keys[DIK_2] && !preKeys[DIK_2]) {
				scene = STAGE2;
			}

			if (keys[DIK_3] && !preKeys[DIK_3]) {
				scene = STAGE3;
			}


			//SELECT更新ここまで
			//SELECT描画処理

			//SELECT描画ここまで
			break;



		case STAGE1:

			lift.pos.x = 832.0f;

			//*******************
			//サウンド処理
			//*******************


			//サウンド処理
			if (!Novice::IsPlayingAudio(playBH)) {
				//playBH = Novice::PlayAudio(playSH, true, 0.05f);
			}
			if (keys[DIK_C] && !preKeys[DIK_C]) {
				scene = SCORE;
				if (Novice::IsPlayingAudio(playBH)) {
					Novice::StopAudio(playBH);
				}
			}
			if (player.pos.y >= 800) {
				scene = OVER;
				if (Novice::IsPlayingAudio(playBH)) {
					Novice::StopAudio(playBH);
				}
			}
			if (keys[DIK_4] && !preKeys[DIK_4]) {
				scene = SELECT;
				if (Novice::IsPlayingAudio(playBH)) {
					Novice::StopAudio(playBH);
				}
			}



			//壁を壊す音
			//if (wall.isBreak) {
			//	//if (!Novice::IsPlayingAudio(breakBH)) {
			//		breakBH = Novice::PlayAudio(breakSH, false, 0.05f);
			//	//}
			//}							   
			//if (wall2.isBreak) {		   
			//	//if (!Novice::IsPlayingAudio(breakBH)) {
			//		breakBH = Novice::PlayAudio(breakSH, false, 0.05f);
			//	//}
			//}







			//STAGE1更新処理
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = START;
			}


			if (keys[DIK_RIGHT] || keys[DIK_D]) {
				playerGH = playerRightGH;
				player.verocity.x = 3.0f;
			}

			if (keys[DIK_LEFT] || keys[DIK_A]) {
				playerGH = playerLeftGH;
				player.verocity.x = -3.0f;
			}

			if (!keys[DIK_LEFT] && !keys[DIK_A] && !keys[DIK_RIGHT] && !keys[DIK_D]) {
				player.verocity.x = 0.0f;
			}


			player.verocity.y = +16.0f;
			player.provPos.x += player.verocity.x;
			player.provPos.y += player.verocity.y;


			//壁が壊れていない＆指定の座標に壁がある時
			if (!wall2.isBreak) {
				if (wall2.pos.x <= 168 && wall2.isMatch) {
					if (keys[DIK_RIGHT] || keys[DIK_D]) {
						player.verocity.x = 3.0f;
					}

					if (keys[DIK_LEFT] || keys[DIK_A]) {
						player.verocity.x = 0.0f;
					}

					player.verocity.y = +16.0f;
					player.provPos.x += player.verocity.x;
					player.provPos.y += player.verocity.y;
				}
			}

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
					player.jumpCount = 0;
					player.jumpCoolTime = 4;
				} else {
					player.pos.y = player.corners.RightDown.y * 32.0f;
					player.verocity.y += player.acceleration.y + 1.6f;
				}



			} else {
				player.pos.y = player.provPos.y;
				player.verocity.y += player.acceleration.y;
			}


			if (HitBox(stage1Map, player.corners)) {


				player.provPos = player.pos;


				player.provPos.x += player.verocity.x;

				player.corners = posUpdate(player.provPos, player.r);



				// ブロックに横からぶつかったとき、ブロックの横で止まる
				if (HitBox(stage1Map, player.corners)) {
					// プレイヤーの横速度が0より高いとき
					if (player.verocity.x >= 0) {
						// プレイヤーのx座標がブロックにめり込まないよう止まる
						//player.pos.x = player.corners.RightDown.x * 32.0f - player.r;

					} else if (player.verocity.x < 0) {
						//player.pos.x = player.corners.LeftDown.x * 32.0f;
					}


					player.provPos = player.pos;


					player.provPos.y += player.verocity.y;

					player.corners = posUpdate(player.provPos, player.r);


					// ブロックの上下の処理
					if (HitBox(stage1Map, player.corners)) {
						//player.pos.y += 0.8f;
						// プレイヤーの縦速度が0より高いとき
						if (player.verocity.y >= 0) {
							// プレイヤーのy座標がブロックにめり込まないよう止まる
							player.pos.y = player.corners.RightDown.y * 32.0f - player.r;

							// y速度を0にして接地させる
							player.verocity.y = 0.0f;

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

							player.isOnGround = true;

							player.jumpCount = 0;

							player.jumpCoolTime = 4;
						} else {
							player.pos.y = player.corners.RightDown.y * 32.0f;
							if (!HitTile(player.tileCorners, lift.corners)) {
								player.verocity.y += player.acceleration.y + 1.6f;
							}
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


			//2

			//wall.verocity.y = +16.0f;
			wall2.provPos.x += wall2.verocity.x;
			wall2.provPos.y += wall2.verocity.y;

			player.pos = player.provPos;
			player.corners = posUpdateTile(player.provPos, player.r, player.r);


			wall2.corners = posUpdateTile(wall2.provPos, wall2.r, wall2.r);

			if (HitTile(player.corners, wall2.corners)) {

				/*if (isStop) {
					player.verocity.x = 0.0f;
					player.acceleration.x = 0.0f;
				}*/


				//isStop = false;


				if (!wall2.isBreak) {

					player.pos = player.provPos;
					//wall.pos = wall.provPos;
					wall2.pos.x -= wall2.speed;
					if (wall2.pos.x <= 168) {
						wall2.speed = 0.0f;
					}

				}


				//壁を壊す
				if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {

					wall2.isBreak = true;

				}



				wall2.isMatch = true;


			} else {
				player.provPos = player.pos;
				wall2.provPos = wall2.pos;
				wall2.isMatch = false;
			}








			//********************
			//壁とplayerの当たり判定
			//********************

			//wall.verocity.y = +16.0f;
			wall.provPos.x += wall.verocity.x;
			wall.provPos.y += wall.verocity.y;

			//player.pos = player.provPos;
			player.corners = posUpdateTile(player.provPos, player.r, player.r);


			wall.corners = posUpdateTile(wall.provPos, wall.r, wall.r);

			if (HitTile(player.corners, wall.corners)) {

				/*if (isStop) {
					player.verocity.x = 0.0f;
					player.acceleration.x = 0.0f;
				}*/


				//isStop = false;


				if (!wall.isBreak) {
					player.pos = player.provPos;
					//wall.pos = wall.provPos;
					wall.pos.x += wall.speed;

				}


				//壁を壊す
				if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {

					wall.isBreak = true;

				}

				wall.isMatch = true;



			} else {
				player.provPos = player.pos;
				wall.provPos = wall.pos;
				wall.isMatch = false;
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
				wall.isLand = true;
			}

			if (wall.isLand) {
				for (int i = 0; i < 24; i++) {
					for (int j = 0; j < 43; j++) {
						if (stage1Map[i][j] == 7) {
							stage1Map[i][j] = 1;

						}
					}
				}
			}


			/*リフト*/


			player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);



			if (lift.pos.y <= 40) {
				lift.verocity.y *= -1.0f;
			} else if (lift.pos.y >= 680) {
				lift.verocity.y *= -1.0f;
			}
			lift.pos.y += lift.verocity.y;

			lift.corners = posUpdateTile(lift.pos, lift.widgh, lift.height);

			if (HitTile(lift.corners, player.tileCorners)) {

				//if(player.tileCorners.RightDown.y<=lift.corners.LeftTop.y+0.5f){
				player.provPos.y = lift.corners.RightTop.y - player.r;
				player.pos.y = player.provPos.y;
				player.verocity.y = 0;
				player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);
				//}
			} else {
				player.verocity.y += player.acceleration.y;
				player.provPos = player.pos;
				player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);
			}

			if (player.pos.y >= 800) {
				scene = OVER;
			}

			//

			//STAGE1更新ここまで

			//STAGE1描画処理



			//背景
			Novice::DrawSprite(
				0, 0,
				bgGH,
				1.0f,
				1.0f,
				0.0f, WHITE
			);

			// マップ
			for (int i = 0; i < 24; i++) {
				for (int j = 0; j < 43; j++) {
					if (stage1Map[i][j] == 1) {
						Novice::DrawSprite(
							j * 32,
							i * 32,
							blockGH,
							1.0f,
							1.0f,
							0.0f,
							WHITE
						);
					} else if (stage1Map[i][j] == 5) {
						Novice::DrawSprite(
							j * 32,
							i * 32,
							appleGH,
							1.0f,
							1.0f,
							0.0f,
							WHITE
						);
					} else if (stage1Map[i][j] == 6) {
						Novice::DrawSprite(
							j * 32,
							i * 32,
							goalGH,
							1.0f,
							1.0f,
							0.0f,
							WHITE
						);
					}
				}
			}

			// 0→無
	// 1→床
	// 2→動く、壊す壁
	// 3→永久欠番
	// 4→リフト
	// 5→リンゴ
	// 6→ゴール
	// 7→永久欠番


			//壁
			if (!wall.isBreak) {
				Novice::DrawSprite(
					int(wall.pos.x), int(wall.pos.y),
					wallGH,
					1.0f,
					1.0f,
					0.0f, WHITE
				);
			}


			if (!wall2.isBreak) {
				Novice::DrawSprite(
					int(wall2.pos.x), int(wall2.pos.y),
					wallGH,
					1.0f,
					1.0f,
					0.0f, WHITE
				);
			}

			//リフト
			for (int i = 0; i < 7; i++) {
				Novice::DrawSprite(
					int(lift.pos.x) + i * 32,
					int(lift.pos.y),
					liftGH,
					1.0f,
					1.0f,
					0.0f,
					WHITE
				);
			}

			Novice::DrawSprite(
				int(player.pos.x), int(player.pos.y),
				playerGH,
				1.0f,
				1.0f,
				0.0f, WHITE
			);




			Novice::ScreenPrintf(20, 20, "wall.pos.x:%f", wall.pos.x);
			Novice::ScreenPrintf(20, 35, "wall.pos.Y:%f", wall.pos.y);
			Novice::ScreenPrintf(10, 50, "lift.LeftUp.x=%d", lift.corners.LeftTop.x);
			Novice::ScreenPrintf(10, 65, "lift.RightDown.x=%d", lift.corners.RightDown.x);
			Novice::ScreenPrintf(10, 80, "player.LeftUp.x=%d", player.tileCorners.LeftTop.x);
			Novice::ScreenPrintf(10, 95, "player.RightDown.x=%d", player.tileCorners.RightDown.x);
			Novice::ScreenPrintf(10, 110, "lift.LeftUp.y=%d", lift.corners.LeftTop.y);
			Novice::ScreenPrintf(10, 125, "lift.RightDown.y=%d", lift.corners.RightDown.y);
			Novice::ScreenPrintf(10, 140, "player.LeftUp.y=%d", player.tileCorners.LeftTop.y);
			Novice::ScreenPrintf(10, 155, "player.RightDown.y=%d", player.tileCorners.RightDown.y);
			Novice::ScreenPrintf(10, 170, "isHit=%d", HitTile(lift.corners, player.corners));
			Novice::ScreenPrintf(10, 185, "lift.widgh=%f", lift.widgh);
			Novice::ScreenPrintf(10, 200, "lift.height=%f", lift.height);
			Novice::ScreenPrintf(1000, 10, "wall2.pos.x= %f", wall2.pos.x);
			Novice::ScreenPrintf(1000, 30, "wall2.pos.y= %f", wall2.pos.y);
			Novice::ScreenPrintf(1000, 50, "player.pos.x= %f", player.pos.x);
			Novice::ScreenPrintf(1000, 70, "player.pos.y= %f", player.pos.y);
			Novice::ScreenPrintf(1000, 90, "player.ver.x= %f", player.verocity.x);
			Novice::ScreenPrintf(1000, 110, "player.ver.y= %f", player.verocity.y);
			Novice::ScreenPrintf(1000, 130, "player.speed= %f", player.speed);
			Novice::ScreenPrintf(1000, 150, "isBreak1= %d", wall.isBreak);
			Novice::ScreenPrintf(1000, 170, "isBreak2= %d", wall.isBreak);
			Novice::ScreenPrintf(1000, 190, "isMatch1= %d", wall.isMatch);
			Novice::ScreenPrintf(1000, 210, "isMatch2= %d", wall2.isMatch);
			//STAGE1描画ここまで
			//STAGE1描画ここまで
			//STAGE1描画ここまで
			break;

		case STAGE2:
			//STAGE2更新処理

			//*******************
			//サウンド処理
			//*******************


			//サウンド処理
			if (!Novice::IsPlayingAudio(playBH)) {
				//playBH = Novice::PlayAudio(playSH, true, 0.05f);
			}
			if (keys[DIK_C] && !preKeys[DIK_C]) {
				scene = SCORE;
				if (Novice::IsPlayingAudio(playBH)) {
					Novice::StopAudio(playBH);
				}
			}
			if (keys[DIK_O] && !preKeys[DIK_O]) {
				scene = OVER;
				if (Novice::IsPlayingAudio(playBH)) {
					Novice::StopAudio(playBH);
				}
			}
			if (keys[DIK_4] && !preKeys[DIK_4]) {
				scene = SELECT;
				if (Novice::IsPlayingAudio(playBH)) {
					Novice::StopAudio(playBH);
				}
			}

			//壁を壊す音
			/*if (wall3.isBreak) {
				if (!Novice::IsPlayingAudio(breakBH)) {
					breakBH = Novice::PlayAudio(breakSH, true, 0.05f);
				}
			}*/




			lift.pos.x = 384.0f;
			lift.widgh = 160.0f;
			lift2.pos.x = 832.0f;
			lift2.widgh = 160.0f;

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = START;
			}

			if (keys[DIK_3] && !preKeys[DIK_3]) {
				scene = STAGE3;
			}


			if (keys[DIK_RIGHT] || keys[DIK_D]) {
				playerGH = playerRightGH;
				player.verocity.x = 3.0f;
			}

			if (keys[DIK_LEFT] || keys[DIK_A]) {
				playerGH = playerLeftGH;
				player.verocity.x = -3.0f;
			}

			if (!keys[DIK_LEFT] && !keys[DIK_A] && !keys[DIK_RIGHT] && !keys[DIK_D]) {
				player.verocity.x = 0.0f;
			}


			player.verocity.y = +16.0f;
			player.provPos.x += player.verocity.x;
			player.provPos.y += player.verocity.y;


			//壁が壊れていない＆指定の座標に壁がある時
			if (!wall3.isBreak) {
				if (wall3.pos.x >= 736 && wall3.isMatch) {
					if (keys[DIK_RIGHT] || keys[DIK_D]) {
						player.verocity.x = 0.0f;
					}

					if (keys[DIK_LEFT] || keys[DIK_A]) {
						player.verocity.x = -3.0f;
					}

					player.verocity.y = +16.0f;
					player.provPos.x += player.verocity.x;
					player.provPos.y += player.verocity.y;
				}
			}

			player.corners = posUpdate(player.provPos, player.r);

			// ブロックの上下の処理
			if (HitBox(stage2Map, player.corners)) {
				// プレイヤーの縦速度が0より高いとき
				if (player.verocity.y >= 0) {
					// プレイヤーのy座標がブロックにめり込まないよう止まる
					player.pos.y = player.corners.RightDown.y * 32.0f - player.r;

					// y速度を0にして接地させる
					player.verocity.y = 0.0f;
					player.isOnGround = true;
					player.jumpCount = 0;
					player.jumpCoolTime = 4;
				} else {
					player.pos.y = player.corners.RightDown.y * 32.0f;
					player.verocity.y += player.acceleration.y + 1.6f;
				}



			} else {
				player.pos.y = player.provPos.y;
				player.verocity.y += player.acceleration.y;
			}


			if (HitBox(stage2Map, player.corners)) {


				player.provPos = player.pos;


				player.provPos.x += player.verocity.x;

				player.corners = posUpdate(player.provPos, player.r);



				// ブロックに横からぶつかったとき、ブロックの横で止まる
				if (HitBox(stage2Map, player.corners)) {
					// プレイヤーの横速度が0より高いとき
					if (player.verocity.x >= 0) {
						// プレイヤーのx座標がブロックにめり込まないよう止まる
						//player.pos.x = player.corners.RightDown.x * 32.0f - player.r;

					} else if (player.verocity.x < 0) {
						//player.pos.x = player.corners.LeftDown.x * 32.0f;
					}


					player.provPos = player.pos;


					player.provPos.y += player.verocity.y;

					player.corners = posUpdate(player.provPos, player.r);


					// ブロックの上下の処理
					if (HitBox(stage2Map, player.corners)) {
						//player.pos.y += 0.8f;
						// プレイヤーの縦速度が0より高いとき
						if (player.verocity.y >= 0) {
							// プレイヤーのy座標がブロックにめり込まないよう止まる
							player.pos.y = player.corners.RightDown.y * 32.0f - player.r;

							// y速度を0にして接地させる
							player.verocity.y = 0.0f;

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
					if (HitBox(stage2Map, player.corners)) {

						if (player.verocity.y >= 0) {

							player.pos.y = player.corners.RightDown.y * 32.0f - player.r;


							player.verocity.y = 0.0f;

							player.isOnGround = true;

							player.jumpCount = 0;

							player.jumpCoolTime = 4;
						} else {
							player.pos.y = player.corners.RightDown.y * 32.0f;
							if (!HitTile(player.tileCorners, lift.corners)) {
								player.verocity.y += player.acceleration.y + 1.6f;
							}
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

			//*************
			//wall3
			//*************

			//wall.verocity.y = +16.0f;
			wall3.provPos.x += wall3.verocity.x;
			wall3.provPos.y += wall3.verocity.y;

			player.pos = player.provPos;
			player.corners = posUpdateTile(player.provPos, player.r, player.r);


			wall3.corners = posUpdateTile(wall3.provPos, wall3.r, wall3.r);

			if (HitTile(player.corners, wall3.corners)) {

				/*if (isStop) {
					player.verocity.x = 0.0f;
					player.acceleration.x = 0.0f;
				}*/


				//isStop = false;


				if (!wall3.isBreak) {

					player.pos = player.provPos;
					//wall.pos = wall.provPos;
					wall3.pos.x += wall3.speed;


					if (wall3.pos.x >= 736) {
						wall3.speed = 0.0f;
					}

				}


				//壁を壊す
				if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {

					wall3.isBreak = true;

				}



				wall3.isMatch = true;


			} else {
				player.provPos = player.pos;
				wall3.provPos = wall3.pos;
				wall3.isMatch = false;
			}








			//********************
			//壁とplayerの当たり判定
			//********************

			//wall.verocity.y = +16.0f;
			//wall.provPos.x += wall.verocity.x;
			//wall.provPos.y += wall.verocity.y;

			////player.pos = player.provPos;
			//player.corners = posUpdateTile(player.provPos, player.r, player.r);


			//wall.corners = posUpdateTile(wall.provPos, wall.r, wall.r);

			//if (HitTile(player.corners, wall.corners)) {

			//	/*if (isStop) {
			//		player.verocity.x = 0.0f;
			//		player.acceleration.x = 0.0f;
			//	}*/


			//	//isStop = false;


			//	if (!isBreak) {
			//		player.pos = player.provPos;
			//		//wall.pos = wall.provPos;
			//		wall.pos.x += wall.speed;

			//	}


			//	//壁を壊す
			//	if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {

			//		isBreak = true;

			//	}

			//	wall.isMatch = true;



			//} else {
			//	player.provPos = player.pos;
			//	wall.provPos = wall.pos;
			//	wall.isMatch = false;
			//}




			////*******************
			////壁を地面に埋める
			////*******************
			//if (wall.pos.x >= 384.0f) {
			//	wall.pos.x = 384.0f;
			//	wall.isDown = true;
			//}

			//if (wall.isDown) {
			//	wall.speed = 14.0f;
			//	wall.pos.y += wall.speed;
			//}

			//if (wall.pos.y >= 544.0f) {
			//	wall.isDown = false;
			//	wall.speed = 0.0f;
			//	wall.pos.x = 384.0f;
			//	wall.pos.y = 544.0f;
			//	isLand = true;
			//}

			//if (isLand) {
			//	for (int i = 0; i < 23; i++) {
			//		for (int j = 0; j < 43; j++) {
			//			if (stage1Map[i][j] == 7) {
			//				stage1Map[i][j] = 1;

			//			}
			//		}
			//	}
			//}


			/*リフト*/


			player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);



			if (lift.pos.y <= 40) {
				lift.verocity.y *= -1.0f;
			} else if (lift.pos.y >= 680) {
				lift.verocity.y *= -1.0f;
			}
			lift.pos.y += lift.verocity.y;

			lift.corners = posUpdateTile(lift.pos, lift.widgh, lift.height);

			if (HitTile(lift.corners, player.tileCorners)) {

				//if(player.tileCorners.RightDown.y<=lift.corners.LeftTop.y+0.5f){
				player.provPos.y = lift.corners.RightTop.y - player.r;
				player.pos.y = player.provPos.y;
				player.verocity.y = 0;
				player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);
				//}
			} else {
				player.verocity.y += player.acceleration.y;
				player.provPos = player.pos;
				player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);
			}

			/*リフト*/

			if (lift2.pos.y <= 40) {
				lift2.verocity.y *= -1.0f;
			} else if (lift2.pos.y >= 680) {
				lift2.verocity.y *= -1.0f;
			}
			lift2.pos.y += lift2.verocity.y;

			lift2.corners = posUpdateTile(lift2.pos, lift2.widgh, lift2.height);

			if (HitTile(lift2.corners, player.tileCorners)) {

				//if(player.tileCorners.RightDown.y<=lift2.corners.LeftTop.y+0.5f){
				player.provPos.y = lift2.corners.RightTop.y - player.r;
				player.pos.y = player.provPos.y;
				player.verocity.y = 0;
				player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);
				//}
			} else {
				player.verocity.y += player.acceleration.y;
				player.provPos = player.pos;
				player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);
			}

			if (player.pos.y >= 800) {
				scene = OVER;
			}





			//STAGE2更新ここまで
			//STAGE2描画処理



			//

			//背景
			Novice::DrawSprite(
				0, 0,
				bgGH,
				1.0f,
				1.0f,
				0.0f, WHITE
			);

			// マップ
			for (int i = 0; i < 24; i++) {
				for (int j = 0; j < 43; j++) {
					if (stage2Map[i][j] == 1) {
						Novice::DrawSprite(
							j * 32,
							i * 32,
							blockGH,
							1.0f,
							1.0f,
							0.0f,
							WHITE
						);
					} else if (stage2Map[i][j] == 5) {
						Novice::DrawSprite(
							j * 32,
							i * 32,
							appleGH,
							1.0f,
							1.0f,
							0.0f,
							WHITE
						);
					} else if (stage2Map[i][j] == 6) {
						Novice::DrawSprite(
							j * 32,
							i * 32,
							goalGH,
							1.0f,
							1.0f,
							0.0f,
							WHITE
						);
					}
				}
			}


			/*for (int i = 0; i < 25; i++) {
				for (int j = 0; j < 43; j++) {
					if (stage1Map[i][j] == 5) {
						Novice::DrawBox(
							j * 32,
							i * 32,
							32,
							32,
							0.0f,
							GREEN,
							kFillModeSolid
						);
					}
				}
			}*/

			//壁
			/*if (!isBreak) {
				Novice::DrawBox(
					int(wall.pos.x), int(wall.pos.y),
					int(wall.r), int(wall.r),
					0.0f, BLUE,
					kFillModeSolid
				);
			}*/

			if (!wall3.isBreak) {
				Novice::DrawSprite(
					int(wall3.pos.x), int(wall3.pos.y),
					wallGH,
					1.0f,
					1.0f,
					0.0f, WHITE
				);
			}

			//リフト
			//リフト
			for (int i = 0; i < 5; i++) {
				Novice::DrawSprite(
					int(lift.pos.x) + i * 32,
					int(lift.pos.y),
					liftGH,
					1.0f,
					1.0f,
					0.0f,
					WHITE
				);
			}

			for (int i = 0; i < 5; i++) {
				Novice::DrawSprite(
					int(lift2.pos.x) + i * 32,
					int(lift2.pos.y),
					liftGH,
					1.0f,
					1.0f,
					0.0f,
					WHITE
				);
			}

			Novice::DrawSprite(
				int(player.pos.x), int(player.pos.y),
				playerGH,
				1.0f,
				1.0f,
				0.0f, WHITE
			);





			Novice::ScreenPrintf(20, 20, "wall.pos.x:%f", wall.pos.x);
			Novice::ScreenPrintf(20, 35, "wall.pos.Y:%f", wall.pos.y);
			Novice::ScreenPrintf(10, 50, "lift.LeftUp.x=%d", lift.corners.LeftTop.x);
			Novice::ScreenPrintf(10, 65, "lift.RightDown.x=%d", lift.corners.RightDown.x);
			Novice::ScreenPrintf(10, 80, "player.LeftUp.x=%d", player.tileCorners.LeftTop.x);
			Novice::ScreenPrintf(10, 95, "player.RightDown.x=%d", player.tileCorners.RightDown.x);
			Novice::ScreenPrintf(10, 110, "lift.LeftUp.y=%d", lift.corners.LeftTop.y);
			Novice::ScreenPrintf(10, 125, "lift.RightDown.y=%d", lift.corners.RightDown.y);
			Novice::ScreenPrintf(10, 140, "player.LeftUp.y=%d", player.tileCorners.LeftTop.y);
			Novice::ScreenPrintf(10, 155, "player.RightDown.y=%d", player.tileCorners.RightDown.y);
			Novice::ScreenPrintf(10, 170, "isHit=%d", HitTile(lift.corners, player.corners));
			Novice::ScreenPrintf(10, 185, "lift.widgh=%f", lift.widgh);
			Novice::ScreenPrintf(10, 200, "lift.height=%f", lift.height);
			Novice::ScreenPrintf(1000, 10, "wall2.pos.x= %f", wall2.pos.x);
			Novice::ScreenPrintf(1000, 30, "wall2.pos.y= %f", wall2.pos.y);
			Novice::ScreenPrintf(1000, 50, "player.pos.x= %f", player.pos.x);
			Novice::ScreenPrintf(1000, 70, "player.pos.y= %f", player.pos.y);
			Novice::ScreenPrintf(1000, 90, "player.ver.x= %f", player.verocity.x);
			Novice::ScreenPrintf(1000, 110, "player.ver.y= %f", player.verocity.y);
			Novice::ScreenPrintf(1000, 130, "player.speed= %f", player.speed);
			Novice::ScreenPrintf(1000, 150, "isBreak1= %d", wall.isBreak);
			Novice::ScreenPrintf(1000, 170, "isBreak2= %d", wall2.isBreak);
			Novice::ScreenPrintf(1000, 190, "isMatch1= %d", wall.isMatch);
			Novice::ScreenPrintf(1000, 210, "isMatch2= %d", wall2.isMatch);
			Novice::ScreenPrintf(1000, 230, "isMatch3= %d", wall3.isMatch);
			Novice::ScreenPrintf(1000, 250, "wall3.pos.x: %f", wall3.pos.x);

			//壁
						/*if (!isBreak) {
							Novice::DrawBox(
								int(wall.pos.x), int(wall.pos.y),
								int(wall.r), int(wall.r),
								0.0f, BLUE,
								kFillModeSolid
							);
						}*/

						/*if (!wall3.isBreak) {
							Novice::DrawBox(
								int(wall3.pos.x), int(wall3.pos.y),
								int(wall3.r), int(wall3.r),
								0.0f, BLUE,
								kFillModeSolid
							);
						}*/



			Novice::DrawSprite(
				int(player.pos.x), int(player.pos.y),
				playerGH,
				1.0f,
				1.0f,
				0.0f, WHITE
			);




			Novice::ScreenPrintf(20, 20, "wall.pos.x:%f", wall.pos.x);
			Novice::ScreenPrintf(20, 35, "wall.pos.Y:%f", wall.pos.y);
			Novice::ScreenPrintf(10, 50, "lift.LeftUp.x=%d", lift.corners.LeftTop.x);
			Novice::ScreenPrintf(10, 65, "lift.RightDown.x=%d", lift.corners.RightDown.x);
			Novice::ScreenPrintf(10, 80, "player.LeftUp.x=%d", player.tileCorners.LeftTop.x);
			Novice::ScreenPrintf(10, 95, "player.RightDown.x=%d", player.tileCorners.RightDown.x);
			Novice::ScreenPrintf(10, 110, "lift.LeftUp.y=%d", lift.corners.LeftTop.y);
			Novice::ScreenPrintf(10, 125, "lift.RightDown.y=%d", lift.corners.RightDown.y);
			Novice::ScreenPrintf(10, 140, "player.LeftUp.y=%d", player.tileCorners.LeftTop.y);
			Novice::ScreenPrintf(10, 155, "player.RightDown.y=%d", player.tileCorners.RightDown.y);
			Novice::ScreenPrintf(10, 170, "isHit=%d", HitTile(lift.corners, player.corners));
			Novice::ScreenPrintf(10, 185, "lift.widgh=%f", lift.widgh);
			Novice::ScreenPrintf(10, 200, "lift.height=%f", lift.height);
			Novice::ScreenPrintf(1000, 10, "wall2.pos.x= %f", wall2.pos.x);
			Novice::ScreenPrintf(1000, 30, "wall2.pos.y= %f", wall2.pos.y);
			Novice::ScreenPrintf(1000, 50, "player.pos.x= %f", player.pos.x);
			Novice::ScreenPrintf(1000, 70, "player.pos.y= %f", player.pos.y);
			Novice::ScreenPrintf(1000, 90, "player.ver.x= %f", player.verocity.x);
			Novice::ScreenPrintf(1000, 110, "player.ver.y= %f", player.verocity.y);
			Novice::ScreenPrintf(1000, 130, "player.speed= %f", player.speed);
			Novice::ScreenPrintf(1000, 150, "isBreak1= %d", wall.isBreak);
			Novice::ScreenPrintf(1000, 170, "isBreak2= %d", wall2.isBreak);
			Novice::ScreenPrintf(1000, 190, "isMatch1= %d", wall.isMatch);
			Novice::ScreenPrintf(1000, 210, "isMatch2= %d", wall2.isMatch);
			Novice::ScreenPrintf(1000, 230, "isMatch3= %d", wall3.isMatch);






			//STAGE2描画ここまで
			break;

		case STAGE3:
			//STAGE3更新処理


			//*******************
			//サウンド処理
			//*******************


			//サウンド処理
			if (!Novice::IsPlayingAudio(playBH)) {
				//playBH = Novice::PlayAudio(playSH, true, 0.05f);
			}
			if (keys[DIK_C] && !preKeys[DIK_C]) {
				scene = SCORE;
				if (Novice::IsPlayingAudio(playBH)) {
					Novice::StopAudio(playBH);
				}
			}
			if (keys[DIK_O] && !preKeys[DIK_O]) {
				scene = OVER;
				if (Novice::IsPlayingAudio(playBH)) {
					Novice::StopAudio(playBH);
				}
			}
			if (keys[DIK_4] && !preKeys[DIK_4]) {
				scene = SELECT;
				if (Novice::IsPlayingAudio(playBH)) {
					Novice::StopAudio(playBH);
				}
			}


			lift.pos.x = 320.0f;
			lift.widgh = 96.0f;
			lift2.pos.x = 704.0f;
			lift2.widgh = 128.0f;


			//壁を壊す音
			/*if (wall4.isBreak) {
				if (!Novice::IsPlayingAudio(breakBH)) {
					breakBH = Novice::PlayAudio(breakSH, true, 0.05f);
				}
			}
			if (wall5.isBreak) {
				if (!Novice::IsPlayingAudio(breakBH)) {
					breakBH = Novice::PlayAudio(breakSH, true, 0.05f);
				}
			}*/


			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = START;
			}

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = START;
			}


			if (keys[DIK_RIGHT] || keys[DIK_D]) {
				playerGH = playerRightGH;
				player.verocity.x = 3.0f;
			}

			if (keys[DIK_LEFT] || keys[DIK_A]) {
				playerGH = playerLeftGH;
				player.verocity.x = -3.0f;
			}

			if (!keys[DIK_LEFT] && !keys[DIK_A] && !keys[DIK_RIGHT] && !keys[DIK_D]) {
				player.verocity.x = 0.0f;
			}

			player.verocity.y = +16.0f;
			player.provPos.x += player.verocity.x;
			player.provPos.y += player.verocity.y;


			//壁が壊れていない＆指定の座標に壁がある時
			if (!wall4.isBreak) {
				if (wall4.pos.x && wall4.isMatch) {
					if (keys[DIK_RIGHT] || keys[DIK_D]) {
						player.verocity.x = 0.0f;
					}

					if (keys[DIK_LEFT] || keys[DIK_A]) {
						player.verocity.x = -3.0f;
					}

					player.verocity.y = +16.0f;
					player.provPos.x += player.verocity.x;
					player.provPos.y += player.verocity.y;
				}
			}

			player.corners = posUpdate(player.provPos, player.r);

			// ブロックの上下の処理
			if (HitBox(stage3Map, player.corners)) {
				// プレイヤーの縦速度が0より高いとき
				if (player.verocity.y >= 0) {
					// プレイヤーのy座標がブロックにめり込まないよう止まる
					player.pos.y = player.corners.RightDown.y * 32.0f - player.r;

					// y速度を0にして接地させる
					player.verocity.y = 0.0f;
					player.isOnGround = true;
					player.jumpCount = 0;
					player.jumpCoolTime = 4;
				} else {
					player.pos.y = player.corners.RightDown.y * 32.0f;
					player.verocity.y += player.acceleration.y + 1.6f;
				}



			} else {
				player.pos.y = player.provPos.y;
				player.verocity.y += player.acceleration.y;
			}


			if (HitBox(stage3Map, player.corners)) {


				player.provPos = player.pos;


				player.provPos.x += player.verocity.x;

				player.corners = posUpdate(player.provPos, player.r);



				// ブロックに横からぶつかったとき、ブロックの横で止まる
				if (HitBox(stage3Map, player.corners)) {
					// プレイヤーの横速度が0より高いとき
					if (player.verocity.x >= 0) {
						// プレイヤーのx座標がブロックにめり込まないよう止まる
						//player.pos.x = player.corners.RightDown.x * 32.0f - player.r;

					} else if (player.verocity.x < 0) {
						//player.pos.x = player.corners.LeftDown.x * 32.0f;
					}


					player.provPos = player.pos;


					player.provPos.y += player.verocity.y;

					player.corners = posUpdate(player.provPos, player.r);


					// ブロックの上下の処理
					if (HitBox(stage3Map, player.corners)) {
						//player.pos.y += 0.8f;
						// プレイヤーの縦速度が0より高いとき
						if (player.verocity.y >= 0) {
							// プレイヤーのy座標がブロックにめり込まないよう止まる
							player.pos.y = player.corners.RightDown.y * 32.0f - player.r;

							// y速度を0にして接地させる
							player.verocity.y = 0.0f;

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
					if (HitBox(stage3Map, player.corners)) {

						if (player.verocity.y >= 0) {

							player.pos.y = player.corners.RightDown.y * 32.0f - player.r;


							player.verocity.y = 0.0f;

							player.isOnGround = true;

							player.jumpCount = 0;

							player.jumpCoolTime = 4;
						} else {
							player.pos.y = player.corners.RightDown.y * 32.0f;
							if (!HitTile(player.tileCorners, lift.corners)) {
								player.verocity.y += player.acceleration.y + 1.6f;
							}
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



			//wall5

			//wall.verocity.y = +16.0f;
			wall5.provPos.x += wall5.verocity.x;
			wall5.provPos.y += wall5.verocity.y;

			player.pos = player.provPos;
			player.corners = posUpdateTile(player.provPos, player.r, player.r);


			wall5.corners = posUpdateTile(wall5.provPos, wall5.r, wall5.r);

			if (HitTile(player.corners, wall5.corners)) {

				/*if (isStop) {
					player.verocity.x = 0.0f;
					player.acceleration.x = 0.0f;
				}*/


				//isStop = false;


				if (!wall5.isBreak) {

					player.pos = player.provPos;
					//wall.pos = wall.provPos;
					wall5.pos.x += wall5.speed;
					/*if (wall5.pos.x <= 168) {
						wall5.speed = 0.0f;
					}*/

				}


				//壁を壊す
				if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {

					wall5.isBreak = true;

				}



				wall5.isMatch = true;


			} else {
				player.provPos = player.pos;
				wall5.provPos = wall5.pos;
				wall5.isMatch = false;
			}


			//*******************
			//壁を地面に埋める
			//*******************
			if (wall5.pos.x >= 1088.0f) {
				wall5.pos.x += wall5.speed;
			}

			if (wall5.pos.x >= 1216.0f) {
				wall5.speed = 0;
				wall5.pos.x = 1216.0f;
				wall5.isDown = true;
			}

			if (wall5.isDown) {
				wall5.speed = 14.0f;
				wall5.pos.y += wall5.speed;
			}

			if (wall5.pos.y >= 544.0f) {
				wall5.isDown = false;
				wall5.speed = 0.0f;
				wall5.pos.x = 1216.0f;
				wall5.pos.y = 544.0f;
				wall5.isLand = true;
			}

			if (wall5.isLand) {
				for (int i = 0; i < 24; i++) {
					for (int j = 0; j < 47; j++) {
						if (stage3Map[i][j] == 7) {
							stage3Map[i][j] = 1;

						}
					}
				}
			}


			//*************
			//wall4
			//*************

			//wall.verocity.y = +16.0f;
			wall4.provPos.x += wall4.verocity.x;
			wall4.provPos.y += wall4.verocity.y;

			player.pos = player.provPos;
			player.corners = posUpdateTile(player.provPos, player.r, player.r);


			wall4.corners = posUpdateTile(wall4.provPos, wall4.r, wall4.r);

			if (HitTile(player.corners, wall4.corners)) {

				/*if (isStop) {
					player.verocity.x = 0.0f;
					player.acceleration.x = 0.0f;
				}*/


				//isStop = false;






				if (!wall4.isBreak) {

					player.pos = player.provPos;
					//wall.pos = wall.provPos;
					wall4.pos.x += wall4.speed;

					if (wall4.pos.x >= 608) {
						wall4.speed = 0.0f;
					}

				}


				//壁を壊す
				if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {

					wall4.isBreak = true;

				}



				wall4.isMatch = true;


			} else {
				player.provPos = player.pos;
				wall4.provPos = wall4.pos;
				wall4.isMatch = false;
			}




			//********************
			//壁とplayerの当たり判定
			//********************

			//wall.verocity.y = +16.0f;
			//wall.provPos.x += wall.verocity.x;
			//wall.provPos.y += wall.verocity.y;

			////player.pos = player.provPos;
			//player.corners = posUpdateTile(player.provPos, player.r, player.r);


			//wall.corners = posUpdateTile(wall.provPos, wall.r, wall.r);

			//if (HitTile(player.corners, wall.corners)) {

			//	/*if (isStop) {
			//		player.verocity.x = 0.0f;
			//		player.acceleration.x = 0.0f;
			//	}*/


			//	//isStop = false;


			//	if (!isBreak) {
			//		player.pos = player.provPos;
			//		//wall.pos = wall.provPos;
			//		wall.pos.x += wall.speed;

			//	}


			//	//壁を壊す
			//	if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {

			//		isBreak = true;

			//	}

			//	wall.isMatch = true;



			//} else {
			//	player.provPos = player.pos;
			//	wall.provPos = wall.pos;
			//	wall.isMatch = false;
			//}




			////*******************
			////壁を地面に埋める
			////*******************
			//if (wall.pos.x >= 384.0f) {
			//	wall.pos.x = 384.0f;
			//	wall.isDown = true;
			//}

			//if (wall.isDown) {
			//	wall.speed = 14.0f;
			//	wall.pos.y += wall.speed;
			//}

			//if (wall.pos.y >= 544.0f) {
			//	wall.isDown = false;
			//	wall.speed = 0.0f;
			//	wall.pos.x = 384.0f;
			//	wall.pos.y = 544.0f;
			//	isLand = true;
			//}

			//if (isLand) {
			//	for (int i = 0; i < 23; i++) {
			//		for (int j = 0; j < 43; j++) {
			//			if (stage1Map[i][j] == 7) {
			//				stage1Map[i][j] = 1;

			//			}
			//		}
			//	}
			//}


			/*リフト*/


			player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);



			if (lift.pos.y <= 40) {
				lift.verocity.y *= -1.0f;
			} else if (lift.pos.y >= 680) {
				lift.verocity.y *= -1.0f;
			}
			lift.pos.y += lift.verocity.y;

			lift.corners = posUpdateTile(lift.pos, lift.widgh, lift.height);

			if (HitTile(lift.corners, player.tileCorners)) {

				//if(player.tileCorners.RightDown.y<=lift.corners.LeftTop.y+0.5f){
				player.provPos.y = lift.corners.RightTop.y - player.r;
				player.pos.y = player.provPos.y;
				player.verocity.y = 0;
				player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);
				//}
			} else {
				player.verocity.y += player.acceleration.y;
				player.provPos = player.pos;
				player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);
			}




			if (lift2.pos.y <= 40) {
				lift2.verocity.y *= -1.0f;
			} else if (lift2.pos.y >= 680) {
				lift2.verocity.y *= -1.0f;
			}
			lift2.pos.y += lift2.verocity.y;

			lift2.corners = posUpdateTile(lift2.pos, lift2.widgh, lift2.height);

			if (HitTile(lift2.corners, player.tileCorners)) {

				//if(player.tileCorners.RightDown.y<=lift2.corners.LeftTop.y+0.5f){
				player.provPos.y = lift2.corners.RightTop.y - player.r;
				player.pos.y = player.provPos.y;
				player.verocity.y = 0;
				player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);
				//}
			} else {
				player.verocity.y += player.acceleration.y;
				player.provPos = player.pos;
				player.tileCorners = posUpdateTile(player.provPos, player.r, player.r);
			}


			if (keys[DIK_3] && !preKeys[DIK_3]) {
				scene = STAGE3;
			}





			//STAGE3更新ここまで
			//STAGE3描画処理

			//背景
			Novice::DrawSprite(
				0, 0,
				bgGH,
				1.0f,
				1.0f,
				0.0f, WHITE
			);


			// マップ
				// マップ
			for (int i = 0; i < 24; i++) {
				for (int j = 0; j < 43; j++) {
					if (stage3Map[i][j] == 1) {
						Novice::DrawSprite(
							j * 32,
							i * 32,
							blockGH,
							1.0f,
							1.0f,
							0.0f,
							WHITE
						);
					} else if (stage3Map[i][j] == 5) {
						Novice::DrawSprite(
							j * 32,
							i * 32,
							appleGH,
							1.0f,
							1.0f,
							0.0f,
							WHITE
						);
					} else if (stage3Map[i][j] == 6) {
						Novice::DrawSprite(
							j * 32,
							i * 32,
							goalGH,
							1.0f,
							1.0f,
							0.0f,
							WHITE
						);
					}
				}
			}


			/*for (int i = 0; i < 25; i++) {
				for (int j = 0; j < 43; j++) {
					if (stage1Map[i][j] == 5) {
						Novice::DrawBox(
							j * 32,
							i * 32,
							32,
							32,
							0.0f,
							GREEN,
							kFillModeSolid
						);
					}
				}
			}*/

			//壁
			/*if (!isBreak) {
				Novice::DrawBox(
					int(wall.pos.x), int(wall.pos.y),
					int(wall.r), int(wall.r),
					0.0f, BLUE,
					kFillModeSolid
				);
			}*/

			if (!wall5.isBreak) {
				Novice::DrawSprite(
					int(wall5.pos.x), int(wall5.pos.y),
					wallGH,
					1.0f,
					1.0f,
					0.0f, WHITE
				);
			}

			//リフト
			for (int i = 0; i < 3; i++) {
				Novice::DrawSprite(
					int(lift.pos.x) + i * 32,
					int(lift.pos.y),
					liftGH,
					1.0f,
					1.0f,
					0.0f,
					WHITE
				);
			}

			for (int i = 0; i < 4; i++) {
				Novice::DrawSprite(
					int(lift2.pos.x) + i * 32,
					int(lift2.pos.y),
					liftGH,
					1.0f,
					1.0f,
					0.0f,
					WHITE
				);
			}

			Novice::DrawSprite(
				int(player.pos.x), int(player.pos.y),
				playerGH,
				1.0f,
				1.0f,
				0.0f, WHITE
			);





			Novice::ScreenPrintf(20, 20, "wall.pos.x:%f", wall.pos.x);
			Novice::ScreenPrintf(20, 35, "wall.pos.Y:%f", wall.pos.y);
			Novice::ScreenPrintf(10, 50, "lift.LeftUp.x=%d", lift.corners.LeftTop.x);
			Novice::ScreenPrintf(10, 65, "lift.RightDown.x=%d", lift.corners.RightDown.x);
			Novice::ScreenPrintf(10, 80, "player.LeftUp.x=%d", player.tileCorners.LeftTop.x);
			Novice::ScreenPrintf(10, 95, "player.RightDown.x=%d", player.tileCorners.RightDown.x);
			Novice::ScreenPrintf(10, 110, "lift.LeftUp.y=%d", lift.corners.LeftTop.y);
			Novice::ScreenPrintf(10, 125, "lift.RightDown.y=%d", lift.corners.RightDown.y);
			Novice::ScreenPrintf(10, 140, "player.LeftUp.y=%d", player.tileCorners.LeftTop.y);
			Novice::ScreenPrintf(10, 155, "player.RightDown.y=%d", player.tileCorners.RightDown.y);
			Novice::ScreenPrintf(10, 170, "isHit=%d", HitTile(lift.corners, player.corners));
			Novice::ScreenPrintf(10, 185, "lift.widgh=%f", lift.widgh);
			Novice::ScreenPrintf(10, 200, "lift.height=%f", lift.height);
			Novice::ScreenPrintf(1000, 10, "wall2.pos.x= %f", wall2.pos.x);
			Novice::ScreenPrintf(1000, 30, "wall2.pos.y= %f", wall2.pos.y);
			Novice::ScreenPrintf(1000, 50, "player.pos.x= %f", player.pos.x);
			Novice::ScreenPrintf(1000, 70, "player.pos.y= %f", player.pos.y);
			Novice::ScreenPrintf(1000, 90, "player.ver.x= %f", player.verocity.x);
			Novice::ScreenPrintf(1000, 110, "player.ver.y= %f", player.verocity.y);
			Novice::ScreenPrintf(1000, 130, "player.speed= %f", player.speed);
			Novice::ScreenPrintf(1000, 150, "isBreak1= %d", wall.isBreak);
			Novice::ScreenPrintf(1000, 170, "isBreak2= %d", wall2.isBreak);
			Novice::ScreenPrintf(1000, 190, "isMatch1= %d", wall.isMatch);
			Novice::ScreenPrintf(1000, 210, "isMatch2= %d", wall2.isMatch);
			Novice::ScreenPrintf(1000, 230, "isMatch3= %d", wall3.isMatch);
			Novice::ScreenPrintf(1000, 250, "wall3.pos.x: %f", wall3.pos.x);

			//壁
						/*if (!isBreak) {
							Novice::DrawBox(
								int(wall.pos.x), int(wall.pos.y),
								int(wall.r), int(wall.r),
								0.0f, BLUE,
								kFillModeSolid
							);
						}*/

			if (!wall4.isBreak) {
				Novice::DrawSprite(
					int(wall4.pos.x), int(wall4.pos.y),
					wallGH,
					1.0f,
					1.0f,
					0.0f, WHITE
				);
			}



			Novice::DrawSprite(
				int(player.pos.x), int(player.pos.y),
				playerGH,
				1.0f,
				1.0f,
				0.0f, WHITE
			);


			//STAGE3描画ここまで
			break;

		case SCORE:
			//SCORE更新処理

			//****************
			//サウンド処理
			//****************

			if (!Novice::IsPlayingAudio(clearBH)) {
				//clearBH = Novice::PlayAudio(clearSH, false, 0.1f);
			}
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = SELECT;
				if (Novice::IsPlayingAudio(clearBH)) {
					Novice::StopAudio(clearBH);
				}
			}



			//SCORE更新ここまで
			//SCORE描画処理

			//SCORE描画ここまで
			break;

		case OVER:
			//OVER更新処理

			if (!Novice::IsPlayingAudio(overBH)) {
				//overBH = Novice::PlayAudio(overSH, true, 0.1f);
			}
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = SELECT;
				if (Novice::IsPlayingAudio(overBH)) {
					Novice::StopAudio(overBH);
				}
			}


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