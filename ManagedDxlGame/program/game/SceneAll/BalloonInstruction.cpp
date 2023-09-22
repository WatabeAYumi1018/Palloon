#include "BalloonInstruction.h"

BalloonInstruction::BalloonInstruction() : Balloon()
{
    Initialize();

    m_size = 300;
}

void BalloonInstruction::Initialize()
{
    m_instruction_hdl[eInstructionType::Run] = LoadGraph("graphics/instruction/instruction_run.png");
    m_instruction_hdl[eInstructionType::Roll] = LoadGraph("graphics/instruction/instruction_roll.png");
    m_instruction_hdl[eInstructionType::Float] = LoadGraph("graphics/instruction/instruction_float.png");
    m_instruction_hdl[eInstructionType::Stamp] = LoadGraph("graphics/instruction/instruction_stamp.png");
    m_instruction_hdl[eInstructionType::Fire] = LoadGraph("graphics/instruction/instruction_fire.png");
    m_instruction_hdl[eInstructionType::Beam] = LoadGraph("graphics/instruction/instruction_beam.png");
}

void BalloonInstruction::Draw(float delta_time, const Camera* camera)
{
    for (auto& pair : m_instruction_hdl)
 {
        eInstructionType type = pair.first;
        int hdl = pair.second;
        tnl::Vector3 pos = m_positions[type];
        DrawExtendGraph(pos.x, pos.y, pos.x + m_size, pos.y + m_size, hdl, TRUE);
    }
}

void BalloonInstruction::Update(float delta_time)
{
	Balloon::Update(delta_time);

    for (int i = 0; i < static_cast<int>(eInstructionType::Max); ++i)
    {
        SetPositionForType(static_cast<eInstructionType>(i), tnl::Vector3(i * m_size, 0, 0));
    }

}

void BalloonInstruction::SetPositionForType(eInstructionType type, const tnl::Vector3& pos)
{
    m_positions[type] = pos;
}
