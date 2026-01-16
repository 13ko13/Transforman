#include "TitleScene.h"
#include <DxLib.h>
#include "../General/Input.h"
#include "SceneController.h"
#include "../Main/Application.h"
#include "GameScene.h"
#include <assert.h>

namespace
{
	//フェードにかかるフレーム数
	constexpr int fade_interval = 60;//フェードにかかるフレーム数
	constexpr int a_button_offset_y = 200;//Aボタン画像のYオフセット
	constexpr float title_logo_size = 0.8f;//タイトルロゴの表示サイズ
	constexpr float a_button_size = 0.5f;//Aボタン画像の表示サイズ
}

TitleScene::TitleScene(SceneController& controller) :
	Scene(controller)
{
	//タイトルロゴハンドルに画像のハンドルを渡す
	int handle = -1;

	handle = LoadGraph("img/title/title_logo.png");
	assert(handle >= 1);	//Nullチェック
	m_handles.push_back(handle);

	handle = LoadGraph("img/title/press_a_button.png");
	assert(handle >= 1);	//Nullチェック
	m_handles.push_back(handle);

	//updateとdrawの関数ポインタにFadeInUpdateと
	//FadeDrawを参照させる
	m_update = &TitleScene::UpdateFadeIn;
	m_draw = &TitleScene::DrawFade;

	//frameにfadeにかかる秒数を代入
	m_frame = fade_interval;
}

TitleScene::~TitleScene()
{
	//画像ハンドル解放
	for (auto handle : m_handles)
	{
		DeleteGraph(handle);
	}
	m_controller.Init();
} 

void TitleScene::UpdateFadeIn(Input&)
{
	//フレームが0以下になったらUpdateとDrawの関数ポインタに
	//関数を参照させる
	if (--m_frame <= 0)
	{
		m_update = &TitleScene::UpdateNormal;
		m_draw = &TitleScene::DrawNormal;
		m_frame = 0;
		//絶対にreturnをする
		return;
	}
}

void TitleScene::UpdateNormal(Input& input)
{
	m_frame++;
	//okボタンが押されたら
	//関数を切り替えてフェードアウトに入る
	if (input.IsTriggered("ok"))
	{
		m_update = &TitleScene::UpdateFadeOut;
		m_draw = &TitleScene::DrawFade;
		//フェードアウトの最初　念のため　
		m_frame = 0;
		//絶対にreturnする
		return;
	}
}

void TitleScene::UpdateFadeOut(Input&)
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

void TitleScene::DrawFade()
{
	//ウィンドウサイズを変数に保存
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawNormal();

	//値の範囲をいったん0.0～1.0にしておくといろいろと扱いやすくなる
	auto fadeRate = (static_cast<float>(m_frame) / static_cast<float>(fade_interval));
	//aブレンド
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * fadeRate));//DxLibのAlphaブレンドが0～255
	//画面全体に黒フィルムをかける
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	//ブレンドしない
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::DrawNormal()
{
	//ウィンドウサイズを変数に保存
	const auto wsize = Application::GetInstance().GetWindowSize();
	//ロゴを表示
	DrawRotaGraph(wsize.w / 2, wsize.h / 2, static_cast<double>(title_logo_size),
		0.0f, m_handles[static_cast<int>(TitleScene::HandleNumber::TitleLogo)], true);

	int blinkingRate = 175 + 80 * sinf(m_frame * 0.1f);// + 1.0f * 0.5f
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,blinkingRate);//aブレンド
	//「Aボタンでスタート」を表示
	DrawRotaGraph(wsize.w / 2, wsize.h / 2 + a_button_offset_y,
		static_cast<double>(a_button_size), 0.0f, m_handles[static_cast<int>(TitleScene::HandleNumber::Abutton)], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//ブレンドしない
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