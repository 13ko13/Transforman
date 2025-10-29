#include "TitleScene.h"
#include <DxLib.h>

//フェードにかかるフレーム数
constexpr int fade_interval = 60;

TitleScene::TitleScene(SceneController& controller) :
	Scene(controller)
{
	//タイトルロゴハンドルに画像のハンドルを渡す
	m_titleLogoH = LoadGraph(L"img/title/title_logo.png");

	//updateとdrawの関数ポインタにFadeInUpdateと
	//FadeDrawを参照させる
	m_update = &TitleScene::FadeInUpdate;
	m_draw = &TitleScene::FadeDraw;

	//frameにfadeにかかる秒数を代入
	m_frame = fade_interval;
}

void TitleScene::Update(Input&)
{
}

void TitleScene::Draw()
{
}

void TitleScene::FadeInUpdate(Input&)
{
}

void TitleScene::NormalUpdate(Input&)
{
}

void TitleScene::FadeOutUpdate(Input&)
{
}

void TitleScene::FadeDraw()
{
}

void TitleScene::NormalDraw()
{
}
