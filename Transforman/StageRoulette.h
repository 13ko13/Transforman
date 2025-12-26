#pragma once
#include <vector>

/// <summary>
/// ステージIDのプールから重複なしで
/// 指定した数のステージの中からランダムに
/// ステージを抽選し、1ずつ供給するルーレット管理クラス
/// </summary>
class StageRoulette
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pool">抽選元のステージのID配列</param>
	/// <param name="count">抽選するステージの数</param>
	StageRoulette(const std::vector<int>& pool, std::size_t count = 3);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageRoulette();

	/// <summary>
	/// 次のステージが残っているかどうか
	/// </summary>
	/// <returns></returns>
	bool HasNext() const;

	/// <summary>
	/// 次のステージIDを返す(次がない場合は-1を返す)
	/// </summary>
	/// <returns>次のステージID</returns>
	int Next();

	/// <summary>
	/// 今回抽選する総数を返す
	/// </summary>
	/// <returns>抽選するステージの総数</returns>
	std::size_t TotalCount() const;
};

