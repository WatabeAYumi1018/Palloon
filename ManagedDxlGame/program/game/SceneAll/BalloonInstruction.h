#pragma once
#include "Balloon.h"

class BalloonInstruction : public Balloon
{
public:

    BalloonInstruction();
    ~BalloonInstruction() {}

private:
    
    //-----ƒƒ“ƒo•Ï”-----//
    float m_time = 0.0f;
    float m_speed = 0.1f;
    float m_amplitude = 1.0f;

    std::map<eInstructionType, int> m_instruction_hdl;
    std::map<eInstructionType, tnl::Vector3> m_pos_graphics;

    std::vector<float> m_phaseOffsets;
    int m_maxDrawCount = 0;

public:

    //-----ƒƒ“ƒoŠÖ”-----//
    void Initialize() override;
    void Update(float delta_time) override;
    void Draw(float delta_time, const Camera* camera) override;
};
