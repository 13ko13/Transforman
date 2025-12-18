#pragma once
#include <vector>
#include <memory>

enum class TextType
{
	Move,
	Jump,
	Shot,
	ChargeShot,
	Flame,
	Parry
};

class Text;
class TextManager
{
public:
	TextManager();
	void Create(int handle,TextType type);
	void Update();
	void Draw();

private:
	std::vector<int> m_handles;
	std::shared_ptr<Text> m_text;
};