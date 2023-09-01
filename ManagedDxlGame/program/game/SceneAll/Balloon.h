#pragma once
#include "../../engine/GameEngine.h"
#include "GameObject.h"

class Camera;

//複数生成したいけど、自分のクラス内で自分を生成するのは可能なのか審議中
class Balloon : public GameObject{

public:
    Balloon();
    ~Balloon() {}

private:
    tnl::Vector3 m_hover_velocity;        // 垂直速度
    int m_balloon_hdl = 0;                // バルーンの画像ハンドル
    int m_size = 200;                     // バルーンのサイズ
    std::vector<Balloon> balloons;		  // バルーンの配列  

public:
    void Initialize() override;
    void Update(float delta_time) override;
    void Draw(float delta_time, const Camera* camera) override;
    void Spawn();
};