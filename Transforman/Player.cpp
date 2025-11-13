#include "Player.h"
#include "Geometry.h"
#include <DxLib.h>
#include "GameConstants.h"
#include "PlayerBullet.h"

namespace
{
	constexpr float ground = Graphic::screen_height - 100;	//地面の高さ(仮)
	constexpr float move_speed = 3.0f;							//移動速度
	constexpr float size_width = 40.0f;						//キャラクターの横幅
	constexpr float size_height = 50.0f;					//キャラクターの高さ
	constexpr float graph_width = 40.0f;					//画像の横切り取りサイズ
	constexpr float graph_height = 40.0f;					//画像の縦切り取りサイズ

	constexpr double   draw_scale = 1.5;					//描画スケール			

	constexpr int max_jump_frame = 15;
	constexpr float jump_power = -10.0f;

	constexpr int shot_cooltime = 30;						//ショットのクールタイム
	constexpr int prev_charge_time = 30;					//ショットからチャージショットになるまでの猶予フレーム

	//アニメーション用のグラフのインデックス
	constexpr int graph_index_idle = 0;	
	constexpr int graph_index_walk = 1;
	constexpr int graph_index_damage = 3;
	constexpr int graph_index_deth = 7;
	constexpr int graph_index_jump = 8;
}

Player::Player() :
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
	m_isJumping(false),
	m_isGround(false),
	m_isRight(false),
	m_isCharging(false),
	m_jumpFrame(0),
	m_shotCooltime(0),
	m_state(PlayerState::None),
	m_prevChargeFrame(0)
{
	m_handle = LoadGraph("img/game/Player/player.png");
}

Player::~Player()
{
	DeleteGraph(m_handle);
}

void Player::Init()
{
	m_pos = { Graphic::screen_width / 2,Graphic::screen_height / 2 };
	m_sizeWidth = size_width;
	m_sizeHeight = size_height;
}

void Player::Update()
{
}

void Player::Update(Input& input, std::vector<std::shared_ptr<PlayerBullet>>& pBullets)
{
	m_frame++;
	

	//重力を計算
	Gravity();

	//ジャンプ
	Jump(input);

	//移動
	Move(input);

	//ショットの準備
	PrevShot(input, pBullets);

	//仮の地面を設定
	if (m_pos.y >= ground - 20)
	{
		m_pos.y = ground - 20;
		m_isGround = true;
		m_velocity.y = 0.0f;
	}
	else
	{
		m_isGround = false;
	}

	//None,
	//Idle,
	//Walk,
	//Shot,
	//Jump,
	//ChageShot,
	//Climb,
	//Fire
	switch (m_state)
	{
	case PlayerState::Idle:

		break;
	case PlayerState::Walk:
		break;
	case PlayerState::Shot:
		break;
	case PlayerState::Jump:
		break;
	case PlayerState::ChageShot:
		break;
	case PlayerState::Climb:
		break;
	case PlayerState::Fire:
		break;
	}

	//プレイヤーの左上座標を基準にする

	m_colRect.SetLT(m_pos.x - size_width / 2, m_pos.y - size_height / 2 + 5, size_width, size_height);
}

void Player::Draw()
{
#if _DEBUG
	m_colRect.Draw(0xffffff, false);
	DrawFormatString(0, 0, 0xffffff, "frame:%d", m_frame);
	DrawFormatString(0, 15, 0xffffff, "playerPosY:%f", m_pos.y);
	DrawFormatString(0, 30, 0xffffff, "isRight:%d", m_isRight);
	DrawFormatString(0, 60, 0xffffff, "shotCoolTime:%d", m_shotCooltime);
	DrawFormatString(0, 150, 0xffffff, "prevChargeFrame:%d", m_prevChargeFrame);
#endif

	int srcX = 0;
	int srcY = 0;

	DrawRectRotaGraph(
		static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), //表示位置
		srcX, srcY,												//切り取り開始位置
		graph_width, graph_height,								//切り取りサイズ
		draw_scale, 0.0,											//拡大率、回転角度
		m_handle,											//画像ハンドル
		true,												//透明度
		!m_isRight											//反転
	);
}

void Player::Jump(Input& input)
{
	if (input.IsTriggered("jump") && m_isGround
		&& !m_isJumping)
	{
		//地面にいる状態でジャンプボタンを押されるとジャンプ
		// 可能状態になる
		m_isJumping = true;
	}
	//ジャンプを入力した、かつ、ジャンプ可能状態だったら
	if (input.IsPressed("jump") && m_isJumping)
	{
		m_jumpFrame++;
		m_isGround = false;
		if (m_jumpFrame < max_jump_frame)
		{
			m_velocity.y = jump_power;
		}
	}
	else
	{
		m_jumpFrame = 0;
		m_isJumping = false;
	}
}

void Player::Move(Input& input)
{
	m_pos += m_velocity;

	Vector2 dir = { 0.0f,0.0f };//プレイヤーの速度ベクトル
	if (input.IsPressed("right"))
	{
		dir.x = 1.0f;
		m_isRight = true;
	}
	if (input.IsPressed("left"))
	{
		dir.x = -1.0f;
		m_isRight = false;
	}

	//ディレクションを正規化してプレイヤーのスピードをかけて
	//ポジションに足してあげる移動処理
	m_pos += dir.Normalized() * move_speed;
}

void Player::Shot(std::vector<std::shared_ptr<PlayerBullet>>& pBullets)
{
	for (auto& bullet : pBullets)
	{
		if (!bullet->GetIsAlive())
		{
			//弾が存在していない場合、弾を発射する
			if (m_isRight)
			{
				//右向き
				bullet->SetPos({ m_pos.x + size_width / 2, m_pos.y });
			}
			else
			{
				//左向き
				bullet->SetPos({ m_pos.x - size_width / 2 , m_pos.y });
			}
			bullet->SetType(BulletType::Normal);
			bullet->SetIsAlive(true);
			bullet->SetIsRight(m_isRight);
			break;	//1発撃ったらループを抜ける
		}
	}
}

void Player::ChargeShot(std::vector<std::shared_ptr<PlayerBullet>>& pBullets)
{
	for (auto& bullet : pBullets)
	{
		if (!bullet->GetIsAlive())
		{
			//弾が存在していない場合、弾を発射する
			if (m_isRight)
			{
				//右向き
				bullet->SetPos({ m_pos.x + size_width / 2, m_pos.y });
			}
			else
			{
				//左向き
				bullet->SetPos({ m_pos.x - size_width / 2 , m_pos.y });
			}
			bullet->SetType(BulletType::Charge);
			bullet->SetIsAlive(true);
			bullet->SetIsRight(m_isRight);
			break;	//1発撃ったらループを抜ける
		}
	}
}

void Player::PrevShot(Input& input, std::vector<std::shared_ptr<PlayerBullet>>& pBullets)
{
	m_shotCooltime--;
	if (m_shotCooltime < 0)
	{
		//クールタイムを更新して0以下になったら
		//ショット可能状態にする
		m_shotCooltime = 0;
	}
	//ボタンが一定フレーム以上
	//長押しされたらチャージショットの判定にする
	//チャージショットの猶予時間を超えたらチャージショット
	//それ以外は通常ショット
	if (input.IsPressed("shot"))
	{
		m_prevChargeFrame++;
		m_isCharging = true;
#if _DEBUG
		DrawFormatString(0, 180, 0xffffff, "チャージ中！");
#endif
	}
	if (input.IsReleased("shot"))
	{
		if (m_prevChargeFrame > prev_charge_time)
		{
			//チャージショット
			ChargeShot(pBullets);
			m_shotCooltime = shot_cooltime;
			m_prevChargeFrame = 0;
			m_isCharging = false;
		}
		else
		{
			//通常ショット
			Shot(pBullets);
			m_shotCooltime = shot_cooltime;
			m_prevChargeFrame = 0;
		}
	}
}
