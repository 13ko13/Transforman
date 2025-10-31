#pragma once
#include "Scene.h"

class Input;
class GameScene : public Scene
{
public:
	GameScene(SceneController& controller);
	void Update(Input&)override;
	void Draw()override;

private:
	//ƒvƒŒƒCƒ„[î•ñ

};

