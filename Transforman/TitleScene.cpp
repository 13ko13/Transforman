#include "TitleScene.h"
#include <DxLib.h>
#include "Input.h"

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
	if (input.IsTriggerd("ok"))
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
	//ゲームシーンに切り替える

	//ちゃんとreturnする

}

void TitleScene::FadeDraw()
{
	//ウィンドウサイズを変数に保存

	//ロゴを表示

	//値の範囲をいったん0.0～1.0にしておくといろいろと扱いやすくなる

	//aブレンド

	//画面全体に黒フィルムをかける

	//ブレンドしない

}

void TitleScene::NormalDraw()
{
	//ウィンドウサイズを変数に保存

	//ロゴを表示
}

void TitleScene::Update(Input&)
{
	//現在割り当てられているメンバUpdate系関数を実行する
}

void TitleScene::Draw()
{
	//割り当てられているDraw系メンバ関数を実行する
}