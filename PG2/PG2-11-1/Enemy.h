#pragma once
class Enemy
{
public:	// メンバ関数
	
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="posX">X座標</param>
	/// <param name="posY">Y座標</param>
	/// <param name="speedX">移動速度X</param>
	/// <param name="speedY">移動速度Y</param>
	Enemy(int posX, int posY, int speedX, int speedY);

	int GetposX_() { return posX_; }
	int GetposY_() { return posY_; }
	//int GetspeedX_() { return speedX_; };
	//int GetspeedY_() { return speedY_; };
	int Getradius_() { return radius_; };

	//void SetposX_(int posX_) { this->posX_ = posX_; }
	//void SetposY_(int posY_) { this->posY_ = posY_; }
	void SetspeedX_(int speedX) {speedX_ = speedX; }
	void SetspeedY_(int speedY) {speedY_ = speedY; }
	//void Setradius_(int radius_) { this->radius_ = radius_; }

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private:	// メンバ変数
	int posX_;
	int posY_;
	int speedX_;
	int speedY_;
	int radius_;
};

