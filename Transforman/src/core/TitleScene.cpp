#include "TitleScene.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"
#include "Application.h"
#include "GameScene.h"
#include <assert.h>

//フェードにかかるフレーム数
constexpr int fade_interval = 60;

TitleScene::TitleScene(SceneController& controller) :
	Scene(controller)
{
	//タイトルロゴハンドルに画像のハンドルを渡す
	m_titleLogoH = LoadGraph("img/title/title_logo.png");
	assert(m_titleLogoH >= 1);	//Nullチェック

	//updateとdrawの関数ポインタにFadeInUpdateと
	//FadeDrawを参照させる
	m_update = &TitleScene::FadeInUpdate;
	m_draw = &TitleScene::FadeDraw;

	//frameにfadeにかかる秒数を代入
	m_frame = fade_interval;
}

TitleScene::~TitleScene()
{
	m_controller.Init();
}

void TitleScene::FadeInUpdate(Input&)
{
	//フレームが0以下になったらUpdateとDrawの関数ポインタに
	//関数を参照させる
	if (--m_frame <= 0)
	{
		m_update = &TitleScene::NormalUpdate;
		m_draw = &TitleScene::NormalDraw;
		//絶対にreturnをする
		return;
	}
}

void TitleScene::NormalUpdate(Input& input)
{
	//okボタンが押されたら
	//関数を切り替えてフェードアウトに入る
	if (input.IsTriggered("ok"))
	{
		m_update = &TitleScene::FadeOutUpdate;
		m_draw = &TitleScene::FadeDraw;
		//フェードアウトの最初　念のため　
		m_frame = 0;
		//絶対にreturnする
		return;
	}
}

void TitleScene::FadeOutUpdate(Input&)
{
	//フレームを++してfade_intervalを超えたら
	if (++m_frame >= fade_interval)
	{
		//ゲームシーンに切り替える
		m_controller.ChangeScene(std::make_shared<GameScene>(m_controller));
		//ちゃんとreturnする
		return;//大事
	}
}

void TitleScene::FadeDraw()
{
	//ウィンドウサイズを変数に保存
	const auto& wsize = Application::GetInstance().GetWindowSize();
	//ロゴを表示
	DrawRotaGraph(wsize.w / 2, wsize.h / 2, 0.5, 0.0f, m_titleLogoH, true);
	//値の範囲をいったん0.0～1.0にしておくといろいろと扱いやすくなる
	auto rate = static_cast<float>(m_frame) / static_cast<float>(fade_interval);
	//aブレンド
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);//DxLibのAlphaブレンドが0～255
	//画面全体に黒フィルムをかける
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	//ブレンドしない
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	//ウィンドウサイズを変数に保存
	const auto wsize = Application::GetInstance().GetWindowSize();
	//ロゴを表示
	DrawRotaGraph(wsize.w / 2, wsize.h / 2, 0.5, 0.0f, m_titleLogoH, true);
}

void TitleScene::Init()
{

}

void TitleScene::Update(Input& input)
{
	//現在割り当てられているメンバUpdate系関数を実行する
	(this->*m_update)(input);
}

void TitleScene::Draw()
{
	//割り当てられているDraw系メンバ関数を実行する
	(this->*m_draw)();
}