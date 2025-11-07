#pragma once
#include "Object.h"

/// <summary>
/// エネミー全体の基底クラス
/// </summary>
class EnemyBase : public Object
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual void Attack() abstract;
private:

protected:

};

