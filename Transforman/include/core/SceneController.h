#pragma once
#include <memory>
#include <list>

//プロトタイプ宣言
class Scene;	
class Input;
class SceneController
{
public:
	/// <summary>
	/// シーンの切り替え
	/// </summary>
	/// <param name="scene">新しいシーン</param>
	void ChangeScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// シーンを新しく積む
	/// </summary>
	/// <param name="scene">積みたいシーン</param>
	void PushScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// 最後に積んだシーンをリストから外す(自動的に解放される)
	/// </summary>
	void PopScene();

	/// <summary>
	/// シーンの初期化を行う
	/// </summary>
	void Init();

	/// <summary>
	/// 内部に持ってるシーンのUpdateを呼び出す
	/// </summary>
	/// <param name="input"></param>
	void Update(Input& input);

	/// <summary>
	/// 内部に持ってるシーンのDrawを呼び出す
	/// </summary>
	void Draw();

private:
	//スタックに積まれているシーンを管理
	//一番最後に積まれたシーンのUpdateのみ実行される
	std::list<std::shared_ptr<Scene>> m_scenes;
};