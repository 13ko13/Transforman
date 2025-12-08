#pragma once
#include "Bullet.h"
#include "../General/Input.h"
#include <memory>
#include "../Utility/Geometry.h"
#include "../Collider/Rect.h"

enum class BulletType
{
	Normal,
	Charge,
	Fire
};

class EnemyBase;
class PlayerBullet : public Bullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	void Init() override;
	void Update(GameContext& ctx) override;
	void Draw(std::shared_ptr<Camera> pCamera) override;

	void SetIsRight(bool isRight) { m_isRight = isRight; }
	void SetType(BulletType bulletType) { m_bulletType = bulletType; }

	/// <summary>
	/// ‰Î‰Š•úË‚ğ‘Å‚Â‚Æ‚¢‚¤–½—ß‚ª”ò‚Î‚³‚ê‚½‚Æ‚«‚ÉŒÄ‚ÔŠÖ”
	/// </summary>
	void OnFlame();

private:
	bool m_isRight;
	BulletType m_bulletType;
	Rect m_rect; 

	//‰Š‚ªÁ‚¦‚é‚Ü‚Å‚Ì•b”
	float m_flameLifeTime;
};
