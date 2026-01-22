#include "Application.h"
#include "DxLib.h"
#include "../General/Input.h"
#include "../Scenes/SceneController.h"
#include <memory>
#include "../Scenes/TitleScene.h"
#include "../General/GameConstants.h"
#include "EffekseerForDXLib.h"
#include "../SoundManager.h"

namespace
{
	constexpr int effect_num = 8000;
	constexpr int desition_volume = 70;//決定音の音量
	constexpr int normal_shot_vol = 70;//通常ショットの音量
	constexpr int game_bgm_volume = 60;//ゲームシーンBGMの音量
	constexpr int title_bgm_volume = 60;//タイトルシーンBGMの音量
	constexpr int boss_shot_volume = 50;//ボスのショット時のSEの音量
	constexpr int player_charge_vol = 50;//プレイヤーのチャージ音
}

Application::Application():
	m_windowSize{Graphic::screen_width,Graphic::screen_height}
{

}

Application::~Application()
{

}

Application& Application::GetInstance()
{
	//staticで宣言してそれを返す
	static Application instance;
	return instance;
}

bool Application::Init()
{
	SetGraphMode(m_windowSize.w, m_windowSize.h, Graphic::color_bit);
	//ウィンドwモード設定
	ChangeWindowMode(true);
	//ゲーム名
	SetWindowText("TransforMan");

	if (DxLib_Init() == -1)
	{
		return false;
	}

	//エフェクシアを使用する際に必ず設定する
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Effekseerを初期化する。
		// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(effect_num) == -1)
	{
		DxLib_End();
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
		// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseerに2D描画の設定をする。
	Effekseer_Set2DSetting(Graphic::screen_width, Graphic::screen_height);

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	//サウンドマネージャーの初期化
	auto& sm = SoundManager::GetInstance();
	sm.Load(SoundType::Decision, "Sound/SE/decision.wav", desition_volume, false);
	sm.Load(SoundType::NormalShot, "Sound/SE/normal_shot.wav", normal_shot_vol, false);
	sm.Load(SoundType::GameBgm, "Sound/BGM/game.mp3", game_bgm_volume, true);
	sm.Load(SoundType::TitleBgm, "Sound/BGM/title.mp3", title_bgm_volume, true);
	sm.Load(SoundType::BossShot , "Sound/SE/boss_shot.wav", boss_shot_volume, false);
	sm.Load(SoundType::PlayerCharge, "Sound/SE/player_charge.wav", player_charge_vol, false);

	return true;
}

void Application::Run()
{
	SetDrawScreen(DX_SCREEN_BACK);
	Input input;//入力のためのオブジェクト 
	SceneController controller;//シーンを管理するオブジェクト
	controller.ChangeScene(std::make_shared<TitleScene>(controller));
	controller.Init();

	while (ProcessMessage() != -1)
	{
		auto startTime = GetNowHiPerformanceCount();

		ClearDrawScreen();
		input.Update();//入力状態の更新

		//シーンの更新
		controller.Update(input);
		//シーンの描画
		controller.Draw();
		ScreenFlip();
		//ESCキーが押されたらウィンドウを閉じる
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		while (GetNowHiPerformanceCount() - startTime < 16667)
		{

		}
	}
}

void Application::Terminate()
{
	Effkseer_End();// Effekseerを終了する。
	DxLib_End();
}

const Size& Application::GetWindowSize() const
{
	return m_windowSize;
}
