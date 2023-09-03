#include "../../../wta_library/wta_IsIntersectCalc.h"
#include "../Character/Character.h"
#include "../Character/Player/Player.h"
#include "../Character/Enemy/Enemy.h"
#include "../Map/Map.h"
#include "Collision.h"

Collision::Collision() : m_lastCharaPos(0.0f, 0.0f, 0.0f)
{

}

tnl::Vector3 Collision::GetCharacterMapChipPos(const tnl::Vector3& charaPos, const Map* map)
{
    //�L�����̈ʒu����O���b�h���W���擾
    float chip_x = charaPos.x / map->MAP_CHIP_SIZE;
    float chip_y = charaPos.y / map->MAP_CHIP_SIZE;

    return tnl::Vector3(chip_x, chip_y, 0.0f);
}

std::vector<sCollisionInfo> Collision::GetRowChips(int chip_x, int i, int range, const Map* map)
{
    std::vector<sCollisionInfo> rowChips;

    //�L�����̍��W������͂̃}�b�v�`�b�v���擾
    for (int j = chip_x - range; j <= chip_x + range; ++j)
    {
        //�͈͊O�͖���
        if (j < 0 || j >= map->GetCollisionInfo()[i].size())
        {
            continue;
        }

        sCollisionInfo info = map->GetCollisionInfo()[i][j];

        //�����蔻�肪�Ȃ��ꍇ�͖���
        if (info.s_type != eCollisionType::None)
        {
            rowChips.emplace_back(info);
        }
    }
    return rowChips;
}

bool Collision::IsRowCollisionExists(const std::vector<sCollisionInfo>& rowChips)
{
    //�󂶂�Ȃ��ꍇ�̂ݐ�ɐi��
    return !rowChips.empty();
}

//�L�����N�^�[�̎��͂̃}�b�v�`�b�v���擾����(�����蔻�菈���y���̂���)
//��ʓI�ɃL�����𒆐S��(2*range+1)*(2*range+1)�͈̔͂̃}�b�v�`�b�v���擾����
std::vector<std::vector<sCollisionInfo>> Collision::GetSurroundingChips(Character* chara, Map* map, int range)
{
    tnl::Vector3 currentPos = chara->GetPos();
    //���݂̍��W����O�̍��W�������āA�}�b�v�`�b�v�̃T�C�Y��菬�����ꍇ�̓L���b�V����Ԃ�
    if ((currentPos - m_lastCharaPos).length() < map->MAP_CHIP_SIZE)
    {
        return m_cachedChips;
    }

    std::vector<std::vector<sCollisionInfo>> chips;

    //�L�����̍��W����O���b�h���W���擾
    tnl::Vector3 chipPos = GetCharacterMapChipPos(currentPos, map);

    for (int i = chipPos.y - range; i <= chipPos.y + range; ++i)
    {
        //�͈͊O�͖���
        if (i < 0 || i >= map->GetCollisionInfo().size())
        {
            continue;
        }

        auto rowChips = GetRowChips(chipPos.x, i, range, map);

        if (IsRowCollisionExists(rowChips))
        {
            chips.emplace_back(rowChips);
        }
    }

    m_cachedChips = chips;
    m_lastCharaPos = currentPos;

    return chips;
}

//��`�Ƃ̓����蔻��v�Z
void Collision::CheckBoxCollision(Character* chara, Map* map, const std::vector<std::vector<sCollisionInfo>>& surroundingChips)
{
    for (const auto& row : surroundingChips)
    {
        for (const auto& info : row)
        {
            if (info.s_type == eCollisionType::None)
            {
                continue;
            }
            tnl::Vector3 nearly_point = tnl::GetNearestRectPoint(info.s_pos, info.s_size, info.s_size, chara->GetPos());

            if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
            {
                tnl::Vector3 normalize = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
                chara->SetPos(nearly_point + normalize * chara->GetSize());
                //�Փˉ�������
                DrawStringEx(0, 70, -1, "boxhit");
            }
        }
    }
}

//�����Ƃ̓����蔻��
void Collision::CheckLineCollision(Character* chara, Map* map, const std::vector<std::vector<sCollisionInfo>>& surroundingChips)
{
    for (const auto& row : surroundingChips)
    {
        for (const auto& info : row)
        {
            if (info.s_type == eCollisionType::None || info.s_type == eCollisionType::Box)
            {
                continue;
            }
            tnl::Vector3 nearly_point =

                tnl::GetNearestPointLine
                (
                    chara->GetPos(),
                    { info.s_pos.x - (info.s_size >> 1),info.s_pos.y + (info.s_size >> 1),0 },
                    { info.s_pos.x + (info.s_size >> 1),info.s_pos.y - (info.s_size >> 1),0 }
            );

            if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
            {
                tnl::Vector3 normalize = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
                chara->SetPos(nearly_point + normalize * chara->GetSize());
                //�Փˉ�������
                DrawStringEx(0, 90, -1, "linehit");
            }
        }
    }
}

////�����蔻��ɉ����ĕ��򏈗�
void Collision::CollisionCalculate(Character* chara, Map* map, int range) {
    //����͈͓��̃}�b�v�`�b�v���擾
    auto surroundingChips = GetSurroundingChips(chara, map, range);

    for (const auto& row : surroundingChips)
    {
        for (const auto& info : row)
        {
            // �����蔻��̃^�C�v�Ɋ�Â��ď���
            switch (info.s_type)
            {
            case eCollisionType::Box:

                CheckBoxCollision(chara, map, surroundingChips);

                break;

            case eCollisionType::Line:

                CheckLineCollision(chara, map, surroundingChips);

                break;

            default:
                break;
            }
        }
    }
}

void Collision::CollisionCharacter(Player* player, Enemy* enemy)
{
    tnl::Vector3 player_pos = player->GetPos();
    float player_size = player->GetSize();

    tnl::Vector3 enemy_pos = enemy->GetPos();
    float enemy_size = enemy->GetSize();

    // 2�̃L�����N�^�[���Փ˂��Ă��邩�`�F�b�N
    if (wta::IsIntersectCircleCircle(player_pos, player_size, enemy_pos, enemy_size))
    {
        tnl::Vector3 diff = enemy_pos - player_pos;

        //�Փ˂���2�̃L�����N�^�[�Ԃ̋���
        float distance = diff.length();

        //�Փ˂̓x�������v�Z
        float overlap = (player_size + enemy_size) - distance;

        //�����x�N�g���𐳋K��
        diff = tnl::Vector3::Normalize(diff);

        //�v���C���[��K�؂Ȉʒu�Ɉړ�
        player->SetPos(player_pos - diff * overlap);
    }
}

//-----------------------------�������Ă�������--------------------------------//

////�L�����N�^�[�ʒu���擾���A�}�b�vID���瓖���蔻��̃^�C�v���擾
////eCollisionType CollisionCalc::GetCollisionTypeMap(Character* chara, MapChip* mapChip) {
//eCollisionType CollisionCalc::GetCollisionTypeMap(int px, int py, MapChip* mapChip) {
//    // �L�����N�^�[�̃��[���h���W���}�b�v�̃O���b�h���W�ɕϊ�
//    int chara_x = px / mapChip->MAP_CHIP_SIZE;
//    int chara_y = py / mapChip->MAP_CHIP_SIZE;
//
//    int mx[3] = { chara_x - 1, chara_x, chara_x + 1 };
//    int my[3] = { chara_y - 1, chara_y, chara_y + 1 };
//
//    for (int i = 0; i < 3; ++i) {
//        for (int k = 0; k < 3; ++k) {
//            if (mx[k] < 0) continue;
//            if (mx[k] >= mapChip->MAP_CHIP_SIZE) continue;
//            if (mx[i] < 0) continue;
//            if (mx[i] >= mapChip->MAP_CHIP_SIZE) continue;
//
//            int cellId = mapChip->GetChipId(mx[k], my[i]);
//            if (-1 != cellId) {
//                DrawStringEx(10, 10, -1, "m = %d", cellId);
//                return mapChip->GetCollisionTypeById(cellId);
//            }
//        }
//    }
//    return eCollisionType::eCollision_None;
//
//}