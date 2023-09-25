#include "Wind.h"
#include "../../SceneAll/Music/MusicManager.h"

Wind::Wind() : m_wind_strength(0.0f), m_direction(1), m_time(0.0f)
{
    MusicManager::GetInstance().LoadSE("wind", "music/wind.wav");
}

void Wind::Update(float delta_time)
{
    m_time += delta_time;

    switch (s_wind_state)
    {
    case sWindState::Blowing:

        if (m_time > BLOWING_TIME)
        {
            m_time = 0.0f;
            m_wind_strength = 0.0f;  // •—‚ğ~‚ß‚é
            s_wind_state = sWindState::Stopped;
        }
        break;

    case sWindState::Stopped:

        if (m_time > STOPPED_TIME)
        {
            MusicManager::GetInstance().PlaySE("wind");

            m_time = 0.0f;
            m_wind_strength = 0.5f;  // •—‚ğ‚©‚¹‚éi—v’²®j
            m_direction = (rand() % 2) == 0 ? 1 : -1;
            s_wind_state = sWindState::Blowing;
        }
        break;
    }
}
