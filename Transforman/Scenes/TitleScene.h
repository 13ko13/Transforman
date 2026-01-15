#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	TitleScene(SceneController&);
	~TitleScene();
	void Init() override;
	void Update(Input&) override;
	void Draw() override;

private:
	enum class HandleNumber
	{
		TitleLogo,
		Abutton,
		Bbutton,
	};

	std::vector<int> m_handles;//画像ハンドルの配列
	int m_frame;//フェード用のフレーム
	
	//メンバ変数ポインタを使用して内部状態を書き換える
	//update関数とdraw関数を、現在のTitleSceneの状態に合わせて
	//切り替えていく
	void UpdateFadeIn(Input&);//フェードインUpdate
	void UpdateNormal(Input&);//通常状態Update
	void UpdateFadeOut(Input&);//フェードアウトUpdate

	//関数ポインタをつかって状態遷移を楽にする
	using UpdateFunc_t = void(TitleScene::*)(Input&);
	UpdateFunc_t m_update;///updateメンバ関数ポインタ

	void DrawFade();//フェードインDraw
	void DrawNormal();//通常状態Draw

	//関数ポインタをつかって状態遷移を楽にする
	using DrawFunc_t = void(TitleScene::*)();
	DrawFunc_t m_draw;//drawメンバ関数ポインタ
};

