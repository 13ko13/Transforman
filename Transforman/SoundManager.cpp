#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager& SoundManager::GetInstance()
{
	//static‚ÅéŒ¾‚µ‚Ä‚»‚ê‚ğ•Ô‚·
	static SoundManager instance;
	return instance;
}

SoundManager::~SoundManager()
{
}

void SoundManager::PlaySound()
{

}

void SoundManager::StopSound()
{
}

