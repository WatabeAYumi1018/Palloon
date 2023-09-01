#pragma once
#include "GameEngine.h"
#include "GameObject.h"

class PlayCamera;

//ゲームオブジェクト型にすると、描画位置がずれるため…。
//クラス型関係なく、レイヤー関係を調整することはできるのだろうか…。
class Balloon : public GameObject{

public:
    Balloon();
    ~Balloon() {}

private:
    tnl::Vector3 m_hover_velocity;        // 垂直速度
    int m_balloon_hdl = 0;                // バルーンの画像ハンドル
    int m_size = 200;                      // バルーンのサイズ
    std::vector<Balloon> balloons;		  // バルーンの配列  
public:
    void Initialize() override;
    void Update(float delta_time) override;
    void Draw(float delta_time, const PlayCamera* camera) override;
    void Spawn();
};