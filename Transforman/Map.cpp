#define NOMINMAX
#include "Map.h"
#include "Stages/Stage.h"
#include <DxLib.h>
#include <cassert>
#include "Main/Application.h"
#include "Graphics/Camera.h"
#include "Objects/Player.h"
#include <algorithm>


namespace
{
	constexpr int chip_size = 32;
	constexpr int graph_chip_row = 18;
}

Map::Map(std::shared_ptr<Stage> pStage) :
	m_pStage(pStage),
	m_isStageEnd(false),
	m_scrollX(0.0f),
	m_startChipX(0.0f),
	m_offsetX(0.0f)
{
	m_handle = LoadGraph("img/game/map/mapchip_2.png");
	//チェック
	assert(m_handle >= 0);
}

Map::~Map()
{
}

void Map::Update()
{
}

void Map::Draw(Camera camera)
{
	//ステージデータとマップのサイズを取得
	const auto& stageData = m_pStage->GetAllData();
	const auto& mapSize = m_pStage->GetMapSize();
	//ウィンドウサイズを取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	//画面に表示できるタイル数を計算
	int chipOnScreenW = wsize.w / chip_size;
	int chipOnScreenH = wsize.h / chip_size;

	//カメラの画面左上ワールド座標(ピクセル)から開始列と半端オフセットを計算
	const int worldX = static_cast<int>(camera.GetWorldOriginX());
	const int worldY = static_cast<int>(camera.GetWorldOriginY());
	//チップ開始列を計算
	const int startX = std::clamp(worldX / chip_size, 0, std::max(0, mapSize.w - 1));
	const int startY = std::clamp(worldY / chip_size, 0, std::max(0, mapSize.h - 1));
	//チップのスクロールに対応するための半端オフセットを計算
	const float offsetX = static_cast<float>(-(worldX % chip_size));
	const float offsetY = 0;

	//縦方向(画面に入る行のみ/端の半端も見えるようにするために+1行
	//minで比較しないと、ステージの終端になった時に範囲外アクセスしてしまう
	const int drawRows = std::min(chipOnScreenH + 1, mapSize.h - startY);
	for (int y = 0; y < drawRows; y++)
	{
		//マップの列をインデックスとして保管
		//スクロール対応するためにstartYを足してあげる
		const int idxY = startY + y;
		//マップ外にアクセスしないようにcontinueする
		if (idxY < 0 || idxY >= mapSize.h) continue;

		const int drawCols = std::min(chipOnScreenW + 1, mapSize.w - startX);
		for (int x = 0; x < drawCols; x++)
		{
			//スクロール対応するためにstartXを足してあげる
			const int idxX =  startX + x;
			//マップ外にアクセスしないようにcontinueする
			if (idxX < 0 || idxX >= mapSize.w) continue;

			//現在のチップのIDをstageDataをもとに計算する
			auto chipID = stageData[idxX + idxY * mapSize.w];
			//チップのIDが0の時は透明なのでチップを配置しない
			if (chipID == 0) continue;

			const float posX = static_cast<float>(x * chip_size) + offsetX +
				camera.GetDrawOffset().x;
			const float posY = static_cast<float>(y * chip_size) + offsetY +
				camera.GetDrawOffset().y;
			//どのマップチップを表示するかを計算
			//インデックスを考慮するので余りを出して1行目以外にも対応
			//できるようにする(どこの行にいっても何列目というのがわかる)
			//最後に、これは切り取り位置なのでサイズをかけてあげる
			int srcX = (chipID % graph_chip_row) * chip_size;
			//何行目かがわかればいいので元画像のチップの
			//横に並んでいる数で割ると現在の列がわかる
			//最後に、これは切り取り位置なのでサイズをかけてあげる
			int srcY = (chipID / graph_chip_row) * chip_size;
			
			//描画
			DrawRectRotaGraph(
							posX + chip_size / 2,
							posY + chip_size / 2,
							srcX, srcY,
							chip_size, chip_size,
							1.0, 0.0, m_handle, true);

#ifdef _DEBUG
			//当たり判定
			DrawBoxAA(posX, posY, posX + chip_size, posY + chip_size, 0x00ff00, false);
#endif // _DEBUG

		}
	}
}

bool Map::IsCollision(const Rect hitRect, Rect& chipRect)
{
	//ステージデータとマップのサイズを取得
	const auto& stageData = m_pStage->GetAllData();
	const auto& mapSize = m_pStage->GetMapSize();
	//ウィンドウサイズを取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	//画面に表示できるタイル数を計算
	int chipOnScreenW = wsize.w / chip_size;
	int chipOnScreenH = wsize.h / chip_size;
	for (int y = 0; y < chipOnScreenH; y++)
	{
		//マップの高さを越えたらcontinueする
		if (y >= mapSize.h) continue;
		for (int x = 0; x < chipOnScreenW; x++)
		{
			//マップの幅を越えたらcontinueする	
			if (x >= mapSize.w) continue;
			//現在のチップのIDをstageDataをもとに計算する
			auto chipID = stageData[x + y * mapSize.w];
			//0番は透明なのでcontinueする
			if (chipID == 0) continue;
			int chipLeft = static_cast<int>(x * chip_size);
			int chipRight = static_cast<int>(chipLeft + chip_size);
			int chipTop = static_cast<int>(y * chip_size);
			int chipBottom = static_cast<int>(chipTop + chip_size);

			//絶対に当たらない場合
			if (chipLeft > hitRect.GetRight()) continue;
			if (chipTop > hitRect.GetBottom()) continue;
			if (chipRight < hitRect.GetLeft()) continue;
			if (chipBottom < hitRect.GetTop()) continue;

			//ぶつかったマップチップの矩形を設定する
			chipRect.m_left = static_cast<float>(chipLeft);
			chipRect.m_right = static_cast<float>(chipRight);
			chipRect.m_top = static_cast<float>(chipTop);
			chipRect.m_bottom = static_cast<float>(chipBottom);

			//いずれかのチップに当たっていたら終了する
			return true;
		}
	}
	//どれにも当たっていない
	return false;
}
