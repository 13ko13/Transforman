#include "Map.h"
#include "Stages/Stage.h"
#include <DxLib.h>
#include <cassert>
#include "Main/Application.h"

namespace
{
	constexpr int chip_size = 16;
	constexpr int graph_chip_row = 18;
}

Map::Map(std::shared_ptr<Stage> pStage) :
	m_pStage(pStage),
	m_isStageEnd(false),
	m_scrollX(0.0f),
	m_startChipX(0.0f),
	m_offsetX(0.0f)
{
	m_handle = LoadGraph("img/game/map/mapchip.png");
	//チェック
	assert(m_handle >= 0);
}

Map::~Map()
{
}

void Map::Update()
{
	//プレイヤーの移動やゲーム進行に応じてスクロール量を計算
	//m_scrollXはピクセル単位で管理
	m_scrollX += 1.0f;
	//表示開始チップのインデックスを計算
	m_startChipX = m_scrollX / chip_size;
	m_offsetX = m_scrollX % chip_size;
}

void Map::Draw()
{
	//ステージデータとマップのサイズを取得
	const auto& stageData = m_pStage->GetAllData();
	const auto& mapSize = m_pStage->GetMapSize();
	//ウィンドウサイズを取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	//画面に表示できるタイル数を計算
	int chipOnScreenW = wsize.w / chip_size + 1;
	int chipOnScreenH = wsize.h / chip_size;
	//画面の縦に表示できるチップ分ループを回す
	for (int y = 0; y < chipOnScreenH; y++)
	{
		//マップの列をインデックスとして保管
		int idxY = y;
		//マップの高さを越えたらcontinueする
		if (y >= mapSize.h) continue;
		//画面の横に表示できるチップ分ループを回す
		for (int x = 0; x < chipOnScreenW; x++)
		{

			//スクロールに合わせて現在表示すべき列
			int idxX = m_startChipX + x;
			//マップの幅を越えたらcontinueする	
			if (x >= mapSize.w) continue;
			//現在のチップのIDをstageDataをもとに計算する
			auto chipID = stageData[idxX + idxY * mapSize.w];
			//チップのIDが0の時は透明なのでチップを配置しない
			if (chipID == 0) continue;
			//どのマップチップを表示するかを計算
			//インデックスを考慮するので余りを出して1行目以外にも対応
			//できるようにする(どこの行にいっても何列目というのがわかる)
			//最後に、これは切り取り位置なのでサイズをかけてあげる
			int srcX = (chipID % graph_chip_row) * chip_size;
			//何行目かがわかればいいので元画像のチップの
			//横に並んでいる数で割ると現在の列がわかる
			//最後に、これは切り取り位置なのでサイズをかけてあげる
			int srcY = (chipID / graph_chip_row) * chip_size;
			//描画位置をスクロール補正ありで計算する
			float posX = x * chip_size - m_offsetX;
			float posY = y * chip_size;
			//描画
			DrawRectRotaGraph(
							posX, posY,
							srcX, srcY,
							chip_size, chip_size,
							1.0, 0.0, m_handle, true);
		}
	}
}