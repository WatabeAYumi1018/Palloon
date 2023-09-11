#include "../game/ScenePlay/Camera/Camera.h"
#include "../game/SceneAll/Balloon.h"

Balloon::Balloon() : GameObject(tnl::Vector3(0, 0, 0))
{
    Initialize();
}

void Balloon::Initialize()
{
    // バルーンの画像をロード
    m_balloon_hdl = LoadGraph("graphics/balloon/balloon_red.png");
    //画面の幅に基づいてランダムなX位置を設定
    m_pos.x = rand() % 640;
    //画面の下部からランダムな位置で開始
    m_pos.y = 480 + rand() % 100;
    //1から3の間でランダムな上向き速度
    m_hover_velocity = -(rand() % 3 + 1);
}

void Balloon::Update(float delta_time)
{
    //Spawn();
    m_pos.y += m_hover_velocity.y;

    //ふわふわさせるための小さいランダムな変動を加える
    m_hover_velocity.y += (rand() % 3 - 1) * 0.1f;
}

void Balloon::Draw(float delta_time, const Camera* camera)
{
    //カメラの位置に合わせて描画位置をずらす
    tnl::Vector3 draw_pos = m_pos - camera->GetTarget() +
        tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

    DrawExtendGraph(draw_pos.x, draw_pos.y, draw_pos.x + m_size, draw_pos.y + m_size, m_balloon_hdl, TRUE);
}

void Balloon::Finalize()
{
	// バルーンの画像を削除
	DeleteGraph(m_balloon_hdl);
}
