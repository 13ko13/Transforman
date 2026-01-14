#include "ClearScene.h"
#include "../General/Input.h"
#include "GameScene.h"
#include <memory>
#include "../Main/Application.h"
#include <DxLib.h>
#include <cassert>

namespace
{
	//フェードにかかるフレーム数
	constexpr int fade_interval = 70;

	//画像関係
	constexpr float clear_text_size = 1.0f;//クリアシーンのテキスト画像の幅
	constexpr float clear_background_size = 1.0f;//クリアシーンの背景画像の幅
	constexpr int textgraph_srcX = 2816;//テキスト画像の切り取りサイズX
}

ClearScene::ClearScene(SceneController& controller) :
	Scene(controller)
{
	//クリアシーンの文字画像ハンドルロード
	int handle = LoadGraph("img/clear/clear_text.png");
	assert(handle >= 1);//Nullチェック
	m_handles.push_back(handle);

	//クリアシーンの背景画像ハンドルロード
	handle = LoadGraph("img/clear/clear_background.png");
	assert(handle >= 1);//Nullチェック
	m_handles.push_back(handle);

	//PressA画像ハンドルロード
	handle = LoadGraph("img/clear/press_a_button.png");
	assert(handle >= 1);
	m_handles.push_back(handle);

	//updateとdrawの関数ポインタにFadeInUpdateと
	//FadeDrawを参照させる
	m_update = &ClearScene::UpdateFadeIn;
	m_draw = &ClearScene::DrawFade;

	//frameにfade中にかかる秒数を代入
	m_frame = fade_interval;	//初期化関数呼び出し
	Init();
}

ClearScene::~ClearScene()
{
	//画像ハンドル解放
	for (auto handle : m_handles)
	{
		DeleteGraph(handle);
	}
}

void ClearScene::Init()
{
	//クリアシーン背景アニメーション初期化
	m_backgroundAnim.Init(
		m_handles[static_cast<int>(handleNumber::clearBackground)],0,
		{ 2816, 1536 },
		1, 7,
		0.5f, true);

	//クリアシーンテキストアニメーション初期化
	m_clearTextAnim.Init(
		m_handles[static_cast<int>(handleNumber::clearText)],0,
		{ 1376,768 },
		1, 5,
		0.5f, true);
}

void ClearScene::Update(Input& input)
{
	//現在割り当てられているメンバUpdate系関数を実行する
	(this->*m_update)(input);
}

void ClearScene::Draw()
{
	//現在割り当てられているメンバDraw系関数を実行する
	(this->*m_draw)();
}

void ClearScene::UpdateFadeIn(Input&)
{
	//背景アニメーション更新
	m_backgroundAnim.Update();
	//文字アニメーション更新
	m_clearTextAnim.Update();

	//フレームが0以下になったらUpdateとDrawをノーマル状態に切り替える
	m_frame--;
	if (m_frame <= 0)
	{
		m_update = &ClearScene::UpdateNormal;
		m_draw = &ClearScene::DrawNormal;
		//絶対にreturnする
		return;
	}
}

void ClearScene::UpdateNormal(Input& input)
{
	//背景アニメーション更新
	m_backgroundAnim.Update();
	//テキストアニメーション更新
	m_clearTextAnim.Update();

	//OKボタンが押されたら関数を
	//切り替えてフェードアウトに入る
	if (input.IsTriggered("ok"))
	{
		m_update = &ClearScene::UpdateFadeOut;
		m_draw = &ClearScene::DrawFade;
		//フェードアウトの最初
		m_frame = 0;//念のため

		//絶対return
		return;
	}
}

void ClearScene::UpdateFadeOut(Input&)
{
	//背景アニメーション更新
	m_backgroundAnim.Update();
	//テキストアニメーション更新
	m_clearTextAnim.Update();

	//フレームを++してfade_intervalを超えたら
	m_frame++;
	if (m_frame >= fade_interval)
	{
		//ゲームシーンに切り替える
		m_controller.ChangeScene(std::make_shared<GameScene>(m_controller));
		//ちゃんとreturn
		return;//大事
	}
}

void ClearScene::DrawFade()
{
	//ウィンドウサイズを変数に保存
	const auto& wsize = Application::GetInstance().GetWindowSize();

	//仮で文字表示
#ifdef _DEBUG
	DrawFormatString(500, 500, 0xffffff, "ClearScene");
#endif // _DEBUG

	//クリアシーンの背景を表示
	m_backgroundAnim.Draw(
		{ static_cast<float>(wsize.w / 2),
		static_cast<float>(wsize.h / 2) },
		false);

	//テキストの表示
	m_clearTextAnim.Draw(
		{ static_cast<float>(wsize.w / 2),
		static_cast<float>(wsize.h / 2) },
		false);

	//値の範囲をいったん0.0～1.0にしておくといろいろと扱いやすくなる
	auto rate = static_cast<float>(m_frame) / static_cast<float>(fade_interval);
	//aブレンド
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * rate));//DxLibのAlphaブレンドが0～255
	//画面全体に黒フィルムをかける
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	//ブレンドしない
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ClearScene::DrawNormal()
{
	//ウィンドウサイズを変数に保存
	const auto& wsize = Application::GetInstance().GetWindowSize();

	//クリアシーンの背景を表示
	m_backgroundAnim.Draw({ static_cast<float>(wsize.w / 2), static_cast<float>(wsize.h / 2) }, false);

	//テキストの表示
	m_clearTextAnim.Draw(
						{ static_cast<float>(wsize.w / 2),
						static_cast<float>(wsize.h / 2) },
						false);
}