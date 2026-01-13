#include "GameoverScene.h"
#include "../General/Input.h"
#include "GameScene.h"
#include <memory>
#include "../Main/Application.h"
#include <DxLib.h>
#include <cassert>

namespace
{
	//フェードにかかるフレーム数
	constexpr int fade_interval = 100;

	//画像関係
	constexpr float gameover_text_size = 1.0f;//ゲームオーバーのテキスト画像の幅
	constexpr float gameover_background_size = 1.0f;//ゲームオーバーの背景画像の幅
}

GameoverScene::GameoverScene(SceneController& controller) : 
	Scene(controller)
{
	//ゲームオーバーの文字画像ハンドルロード
	int handle = LoadGraph("img/gameover/gameover_text.png");
	assert(handle >= 1);//Nullチェック
	m_handles.push_back(handle);

	//ゲームオーバーの背景画像ハンドルロード
	handle = LoadGraph("img/gameover/Gameover_background.png");
	assert(handle >= 1);//Nullチェック
	m_handles.push_back(handle);

	//updateとdrawの関数ポインタにFadeInUpdateと
	//FadeDrawを参照させる
	m_update = &GameoverScene::UpdateFadeIn;
	m_draw = &GameoverScene::DrawFade;

	//frameにfade中にかかる秒数を代入
	m_frame = fade_interval;

	Init();
}

GameoverScene::~GameoverScene()
{
	//画像ハンドル解放
	for(auto handle : m_handles)
	{
		DeleteGraph(handle);
	}
	
}

void GameoverScene::Init()
{
	//ゲームオーバー背景アニメーション初期化
	m_backgroundAnim.Init(
		m_handles[static_cast<int>(handleNumber::gameoverBackground)],
		0, 
		{1360, 784},
		2,5,
		1.0f,true);
}

void GameoverScene::Update(Input& input)
{
	//現在割り当てられているメンバUpdate系関数を実行する
	(this->*m_update)(input);
}

void GameoverScene::Draw()
{
	//現在割り当てられているメンバDraw系関数を実行する
	(this->*m_draw)();
}

void GameoverScene::UpdateFadeIn(Input&)
{
	//背景アニメーション更新
	m_backgroundAnim.Update();

	//フレームが0以下になったらUpdateとDrawをノーマル状態に切り替える
	m_frame--;
	if (m_frame <= 0)
	{
		m_update = &GameoverScene::UpdateNormal;
		m_draw = &GameoverScene::DrawNormal;
		//絶対にreturnする
		return;
	}
}

void GameoverScene::UpdateNormal(Input& input)
{
	//背景アニメーション更新
	m_backgroundAnim.Update();

	//OKボタンが押されたら関数を
	//切り替えてフェードアウトに入る
	if (input.IsTriggered("ok"))
	{
		m_update = &GameoverScene::UpdateFadeOut;
		m_draw = &GameoverScene::DrawFade;
		//フェードアウトの最初
		m_frame = 0;//念のため

		//絶対return
		return;
	}
}

void GameoverScene::UpdateFadeOut(Input&)
{
	//背景アニメーション更新
	m_backgroundAnim.Update();

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

void GameoverScene::DrawFade()
{
	//ウィンドウサイズを変数に保存
	const auto& wsize = Application::GetInstance().GetWindowSize();

	//仮で文字表示
#ifdef _DEBUG
	DrawFormatString(500, 500, 0xffffff, "GameoverScene");
#endif // _DEBUG
	
	//ゲームオーバーの背景を表示
	m_backgroundAnim.Draw(
		{ static_cast<float>(wsize.w / 2),
		static_cast<float>(wsize.h / 2) }, 
		false);
	//ゲームオーバーのテキストを表示
	DrawRotaGraph(wsize.w / 2, wsize.h / 2, static_cast<double>(gameover_text_size), 0.0f, m_handles[static_cast<int>(handleNumber::gameoverText)], true);


	//値の範囲をいったん0.0～1.0にしておくといろいろと扱いやすくなる
	auto rate = static_cast<float>(m_frame) / static_cast<float>(fade_interval);
	//aブレンド
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * rate));//DxLibのAlphaブレンドが0～255
	//画面全体に黒フィルムをかける
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	//ブレンドしない
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameoverScene::DrawNormal()
{
	//ウィンドウサイズを変数に保存
	const auto& wsize = Application::GetInstance().GetWindowSize();
	
	//ゲームオーバーの背景を表示
	m_backgroundAnim.Draw({ static_cast<float>(wsize.w / 2), static_cast<float>(wsize.h / 2) }, false);
	//ゲームオーバーのテキストを表示
	DrawRotaGraph(wsize.w / 2, wsize.h / 2, static_cast<double>(gameover_text_size), 0.0f, m_handles[static_cast<int>(handleNumber::gameoverText)], true);
}