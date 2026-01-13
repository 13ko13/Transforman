#include "GameoverScene.h"
#include "../General/Input.h"
#include "GameScene.h"
#include <memory>
#include "../Main/Application.h"
#include <DxLib.h>

namespace
{
	//フェードにかかるフレーム数
	constexpr int fade_interval = 60;
}

GameoverScene::GameoverScene(SceneController& controller) : 
	Scene(controller),
	m_gameoverTextH(-1)
{
	//ToDo:ゲームオーバーの文字画像ハンドルロード
	//ToDo:アサート

	//updateとdrawの関数ポインタにFadeInUpdateと
	//FadeDrawを参照させる
	m_update = &GameoverScene::UpdateFadeIn;
	m_draw = &GameoverScene::DrawFade;

	//frameにfade中にかかる秒数を代入
	m_frame = fade_interval;
}

GameoverScene::~GameoverScene()
{
	//Todo:画像ハンドル解放

	m_controller.Init();//シーンコントローラーの初期化
}

void GameoverScene::Init()
{
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
	//仮で文字表示
	DrawFormatString(500, 500, 0xffffff, "GameoverScene");

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
	//ロゴを表示
	DrawRotaGraph(wsize.w / 2, wsize.h / 2, 0.5, 0.0f, m_gameoverTextH, true);
}

void GameoverScene::DrawNormal()
{
	//ウィンドウサイズを変数に保存
	const auto wsize = Application::GetInstance().GetWindowSize();
	//ロゴを表示
	DrawRotaGraph(wsize.w / 2, wsize.h / 2, 0.5, 0.0f, m_gameoverTextH, true);
}
