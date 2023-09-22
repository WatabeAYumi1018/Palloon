#pragma once
#include "Balloon.h"

class BalloonInstruction : public Balloon
{
public:

    BalloonInstruction();
    ~BalloonInstruction() {}

private:
    //-----メンバ変数-----//
    std::map<eInstructionType, int> m_instruction_hdl; // 画像ハンドルのマップ
    std::map<eInstructionType, tnl::Vector3> m_positions; // 各画像の座標を保持するマップ
    eInstructionType m_active_type = eInstructionType::Run; // 描画する画像の種類


public:
    //-----メンバ関数-----//
    void SetPositionForType(eInstructionType type, const tnl::Vector3& pos);

    void Initialize() override;
    void Update(float delta_time) override;
    void Draw(float delta_time, const Camera* camera) override;

    //-----Getter,Setter-----//
    void SetActiveType(eInstructionType active_type) { m_active_type = active_type; }
};
