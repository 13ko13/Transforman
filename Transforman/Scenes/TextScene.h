#pragma once
#include "Scene.h"

class TextScene :  public Scene
{
public:
	TextScene(SceneController& controller);
	void Update(Input& input) override;
	void Draw()override;

private:
	int m_lookIdx;//現在どの画像をみているか
	using UpdateFunc_t = void(TextScene::*)(Input&);
	UpdateFunc_t m_update;
	void AppearUpdate(Input& input);//テキスト出現中
	void NormalUpdate(Input& input);//テキスト表示中
	void DisppearUpdate(Input& input);//テキスト消失中

	using DrawFunc_t = void(TextScene::*)(Input&);
	DrawFunc_t m_draw;
	void IntervalDraw();
};

