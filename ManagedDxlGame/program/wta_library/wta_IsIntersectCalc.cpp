#include "wta_IsIntersectCalc.h"
#include <fstream>
#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"

namespace wta {

	//    //画像ファイルをロードする
	//    int loadAnimLoopFile(const char* path) {
	//        std::string folderPath = path;
	//        //WIN32_FIND_DATA構造体：Windowsでファイル検索を行う際に使用されるデータ構造体
	//        //Windows APIのファイル検索関数であるFindFirstFileやFindNextFileを使用する際
	//        //検索結果のファイル情報を格納するために使われる
	//        WIN32_FIND_DATA findData;
	//        //ファイル検索を開始する
	//        HANDLE hFind = FindFirstFile((folderPath + "/*").c_str(), &findData);
	//        //ファイルが見つからなかった場合は終了する
	//        if (hFind == INVALID_HANDLE_VALUE) { return 1; }
	//        do {
	//            //ファイルのみを取得(ライブラリでなければ)
	//            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
	//                //ファイル名を取得
	//                std::string fileName = findData.cFileName;
	//                //ファイルのフルパスを取得
	//                std::string fullPath = folderPath + "/" + fileName;
	//                //画像をロード
	//                Imgs.emplace_back(LoadGraph(fullPath.c_str()));
	//            }
	//        } while (FindNextFile(hFind, &findData) != 0);
	//        //ファイル検索を終了する
	//        FindClose(hFind);
	//        //画像の枚数を取得
	//        NumImgs = static_cast<int>(Imgs.size());
	//
	//        return 0;
	//    }
	//
	//    //画像をループ描画する
	//    int drawAnimLoopFile(float delta_time, tnl::Vector3 pos, int path_hdl, float angle, float scale) {
	//        elapsedTime += delta_time;
	//        //経過時間がフレーム時間を超えた場合
	//        if (elapsedTime >= frameDuration) {
	//            elapsedTime -= frameDuration;
	//            ++currentFrame;
	//            //ループする(余りの数でループ)
	//            if (LoopFlag) { currentFrame %= NumImgs; }
	//            //ループしない
	//            else if (currentFrame >= NumImgs) { currentFrame = NumImgs - 1; }
	//        }
	//        DrawRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), 1.0f, tnl::ToRadian(-45), Imgs[currentFrame], TRUE);
	//
	//        return 0;
	//    }
	//}
	
	//---------------------------------------------------------------------------------------------
	//円と矩形の当たり判定計算
	bool IsIntersectCircleBox(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& box, const int boxSize) {
		int boxSize_half = boxSize >> 1;					//矩形のサイズの半分（ビットシフト操作)
		int circle_squared = CircleSize * CircleSize;		//円の半径の2乗
		//①矩形の上下左右辺の座標を求める
		int left_x = box.x - boxSize_half;
		int top_y = box.y - boxSize_half;
		int right_x = left_x + boxSize;
		int bottom_y = top_y + boxSize;
		//②円の中心が矩形の内側にあるかどうかを判定する
		if (left_x <= circle.x && circle.x <= right_x && top_y <= circle.y && circle.y <= bottom_y) { return true; }	//円の中心が矩形の内側にある
		//③円の中心が矩形の外側にある場合、円の中心と矩形の各辺との距離を求める
		//③-1円の中心と矩形の各辺との距離を求める
		int dist_left_x = left_x - circle.x;		//左辺
		int dist_right_x = circle.x - right_x;		//右辺
		int dist_top_y = top_y - circle.y;			//上辺
		int dist_bottom_y = circle.y - bottom_y;	//下辺
		//③-2円の中心と矩形の各辺との距離が円の半径より小さいかどうかを判定する
		if (dist_left_x >= 0 && dist_left_x <= CircleSize) { return true; }
		if (dist_right_x >= 0 && dist_right_x <= CircleSize) { return true; }
		if (dist_top_y >= 0 && dist_top_y <= CircleSize) { return true; }
		if (dist_bottom_y >= 0 && dist_bottom_y <= CircleSize) { return true; }
		//④矩形の4隅の座標
		int corners[4][2] = {
			{left_x, top_y},       // 左上
			{right_x, top_y},      // 右上
			{left_x, bottom_y},    // 左下
			{right_x, bottom_y}    // 右下
		};
		//矩形の4隅の座標が円の内側にあるかどうかを判定する
		for (int i = 0; i < 4; i++) {
			int distance_squared = (corners[i][0] - circle.x) * (corners[i][0] - circle.x) +
				(corners[i][1] - circle.y) * (corners[i][1] - circle.y);
			if (distance_squared <= circle_squared) { return true; }
		}
		return false;
	}
	//---------------------------------------------------------------------------------------------
	//円と線分の当たり判定計算
	bool IsIntersectCircleLine(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& lineStart, const tnl::Vector3& lineEnd) {
		int circle_squared = CircleSize * CircleSize;		//円の半径の2乗
		//①線分の始点と終点のベクトルを求める
		tnl::Vector3 lineVec = lineEnd - lineStart;
		//②線分の始点から円の中心までのベクトルを求める
		tnl::Vector3 circleVec = circle - lineStart;
		//③線分の長さの2乗を求める
		float lineLengthPow = lineVec.x * lineVec.x + lineVec.y * lineVec.y;
		//④線分の始点から円の中心までの距離を求める（内積）
		float dotProduct = lineVec.x * circleVec.x + lineVec.y * circleVec.y;
		//⑤線分上の交点を計算
		float t = dotProduct / lineLengthPow;
		//⑥tが0~1の間にある場合：線分上に交点が存在する
		if (t >= 0 && t <= 1.0f) {
			//⑥-1交点から円の中心までの距離を計算
			tnl::Vector3 intersectionPoint;
			intersectionPoint.x = lineStart.x + t * lineVec.x;
			intersectionPoint.y = lineStart.y + t * lineVec.y;
			//⑥-2距離の2乗を計算
			float distanceSquared = (intersectionPoint.x - circle.x) * (intersectionPoint.x - circle.x) +
				(intersectionPoint.y - circle.y) * (intersectionPoint.y - circle.y);
			//⑥-3円の半径の2乗より小さい場合：円と線分は重なる
			if (distanceSquared <= circle_squared) { return true; }
		}
		//⑦tが外にある場合（線分両端の点と円の当たり判定を計算する）
		else {
			//⑦-1線分の始点と円の中心の距離を計算
			tnl::Vector3 distance_start = lineStart - circle;
			//⑦-2線分の終点と円の中心の距離を計算
			tnl::Vector3 distance_end = lineEnd - circle;
			//⑦-3それぞれの長さを計算
			float distance_start_squared = distance_start.x * distance_start.x + distance_start.y * distance_start.y;
			float distance_end_squared = distance_end.x * distance_end.x + distance_end.y * distance_end.y;
			//⑦-4円の半径の2乗より小さい場合、円と線分は重なる
			if (distance_start_squared <= circle_squared || distance_end_squared <= circle_squared) { return true; }
		}
		return false;
	}
	//---------------------------------------------------------------------------------------------
	//円同士の当たり判定計算
	bool IsIntersectCircleCircle(const tnl::Vector3& circle01, const int CircleSize01, const tnl::Vector3& circle02, const int CircleSize02) {
		//①円の半径の和を計算
		int radius_sum = CircleSize01 + CircleSize02;
		//②円の中心同士の距離を計算
		tnl::Vector3 distance = circle01 - circle02;
		//③円の中心同士の距離の2乗を計算
		float distance_squared = distance.x * distance.x + distance.y * distance.y;
		//④円の半径の和の2乗より小さい場合、円同士は重なる
		if (distance_squared <= radius_sum * radius_sum) { return true; }

		return false;
	}
}