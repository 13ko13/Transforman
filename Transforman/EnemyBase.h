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

	virtual void Init() abstract;
	virtual void Upbate() abstract;
	virtual void Draw() abstract;

	virtual void Attack() abstract;
private:

protected:

};

