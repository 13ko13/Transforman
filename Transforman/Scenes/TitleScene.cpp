#include "TitleScene.h"
#include <DxLib.h>
#include "../General/Input.h"
#include "SceneController.h"
#include "../Main/Application.h"
#include "GameScene.h"
#include <assert.h>
#include "../../Dxlib_h/EffekseerForDXLib.h"
#include "../SoundManager.h"
#include "../SoundManager.h"

namespace
{
	//フェードにかかるフレーム数
	constexpr int fade_interval = 60;//フェードにかかるフレーム数
	constexpr int a_button_offset_y = 200;//Aボタン画像のYオフセット
	constexpr float title_logo_size = 0.8f;//タイトルロゴの表示サイズ
	constexpr float a_button_size = 0.5f;//Aボタン画像の表示サイズ
	constexpr float effect_pos_x = 500.0f;
	constexpr float effect_pos_y = 500.0f;
}

TitleScene::TitleScene(SceneController& controller) :
	Scene(controller)
{
	//タイトルロゴハンドルに画像のハンドルを渡す
	int handle = -1;

	handle = LoadGraph("img/title/title_logo_2.png");
	assert(handle > -1);	//Nullチェック
	m_handles.push_back(handle);

	handle = LoadGraph("img/title/press_a_button.png");
	assert(handle > -1);	//Nullチェック
	m_handles.push_back(handle);

	//updateとdrawの関数ポインタにFadeInUpdateと
	//FadeDrawを参照させる
	m_update = &TitleScene::UpdateFadeIn;
	m_draw = &TitleScene::DrawFade;

	//frameにfadeにかかる秒数を代入
	m_frame = fade_interval;

	// エフェクトリソースを読み込む
	// ループで無限再生されるエフェクトは、パーティクル自体の生成数が無限だったり、
	// パーティクルの寿命が無限だったりする
	/*effectResourceHandle = LoadEffekseerEffect("Effekseer_Effect/barrior.efk");
	assert(effectResourceHandle > -1);*/

	//BGMを再生
	SoundManager::GetInstance().Play(SoundType::TitleBgm,true);
}

TitleScene::~TitleScene()
{
	//画像ハンドル解放
	for (auto handle : m_handles)
	{
		DeleteGraph(handle);
	}
	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	/*DeleteEffekseerEffect(effectResourceHandle);*/
	m_controller.Init();

	SoundManager::GetInstance().StopSound(SoundType::TitleBgm);
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
		SoundManager::GetInstance().Play(SoundType::Decision);

		m_update = &TitleScene::UpdateFadeOut;
		m_draw = &TitleScene::DrawFade;
		//フェードアウトの最初　念のため　
		m_frame = 0;
		//絶対にreturnする
		return;
	}


	// 再生、生成停止、完全停止
	//switch (effectState)
	//{
	//case EffectState::Stoped:
	//	// 1で再生
	//	if (CheckHitKey(KEY_INPUT_1) && playingEffectHandle < 0)
	//	{
	//		// エフェクトを再生する。
	//		playingEffectHandle = PlayEffekseer2DEffect(effectResourceHandle);
	//	}
	//	break;
	//case EffectState::Shooting:
	//	// 3で完全停止
	//	if (CheckHitKey(KEY_INPUT_3) && playingEffectHandle >= 0)
	//	{
	//		StopEffekseer2DEffect(playingEffectHandle);
	//		playingEffectHandle = -1;
	//		effectState = EffectState::Stoped;
	//	}
	//	break;
	//default:
	//	break;
	//}

		//------------------------------//
		// エフェクトルーチン
		//------------------------------//
	//if (playingEffectHandle >= 0) // 再生中エフェクトのハンドルがあれば.
	//{
	//	// 再生中のエフェクトを移動
	//	SetPosPlayingEffekseer2DEffect(playingEffectHandle, effect_pos_x, effect_pos_x, 0);

	//	// Effekseerにより再生中のエフェクトを更新する。
	//	UpdateEffekseer2D();
	//}
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

	//if (playingEffectHandle >= 0) // 再生中エフェクトのハンドルがあれば.
	//{
	//	// Effekseerにより再生中のエフェクトを描画する。
	//	DrawEffekseer2D();
	//}
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