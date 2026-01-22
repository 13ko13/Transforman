#pragma once

enum class SoundType
{
	Decision,//決定
};

class SoundManager
{
private:
	SoundManager();//newも変数宣言もできないようにする
	SoundManager(const SoundManager& sm) = delete;//コピーコンストラクタを削除
	void operator=(const SoundManager& sm) = delete;//代入を削除

public:
	~SoundManager();

	/// <summary>
	/// SoundManagerのシングルトンインスタンスを取得する
	/// </summary>
	/// <returns>SoundManagerのインスタンス</returns>
	/// <note>SoundManagerの実体はこの関数内部で生成され、ずっととどまり続ける
	static SoundManager& GetInstance();

	/// <summary>
	/// 音を再生する
	/// </summary>
	void PlaySound();

	/// <summary>
	/// 音を停止する
	/// </summary>
	void StopSound();
};

