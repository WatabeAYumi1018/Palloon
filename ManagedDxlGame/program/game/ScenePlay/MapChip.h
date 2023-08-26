#pragma once

class MapChip {

	// ---- メンバ変数 ---- //
public:
	int m_map_chip_id;				// マップチップID
	int m_graphic_handle;			// マップチップ画像のハンドル
	float m_image_angle_deg;		// 画像角度(右回り正)
	float m_image_size_cofficient;	// 画像サイズ倍率（MapManagerで計算値を格納)
	//eMapType m_map_type;			// マップチップの種類

	// ---- メンバ関数 ---- //

};
