#include "SceneController.h"
#include "Scene.h"

void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
{
	//もし、リストが空の場合、普通に代入でChangeSceneしようとすると
	//当然emptyの箱に対してChangeしようとするので、クラッシュします
	//このため、最初にemptyかどうかをチェックします
	if (m_scenes.empty())
	{
		///最初は要素がないため
		//空っぽの場合には指定の要素をpushします
		//少なくとも1つは積まれている状態にします
		m_scenes.push_back(scene);
	}
	else
	{
		m_scenes.back() = scene;
	}
}

void SceneController::PushScene(std::shared_ptr<Scene> scene)
{
	//新しいシーンを末尾に積みます(下から積む？)
	m_scenes.push_back(scene);
}

void SceneController::PopScene()
{
	//末尾のシーンを削除する
	m_scenes.pop_back();
}

void SceneController::Init()
{
	//末尾の要素に対してInitする
	m_scenes.back()->Init();
}

void SceneController::Update(Input& input)
{
	//末尾の要素に対してUpdateする
	m_scenes.back()->Update(input);
}

void SceneController::Draw()
{
	//Updateだけ止めてすべてDraw
	//ポーズしたときにプレイ背景は残る
	for (auto& scene : m_scenes)
	{
		scene->Draw();
	}
}