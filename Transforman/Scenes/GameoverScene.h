#pragma once
#include "Scene.h"
#include "SceneController.h"

class GameoverScene : public Scene
{
	public:
	GameoverScene(SceneController&);
	~GameoverScene();
	void Update(Input&) override;
	void Draw() override;
};