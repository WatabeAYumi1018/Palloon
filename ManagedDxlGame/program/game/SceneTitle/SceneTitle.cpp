#include "../../dxlib_ext/dxlib_ext.h"
#include "SceneTitle.h"
#include "../ScenePlay/scenePlay.h"
#include "../../engine/SceneManager.h"

void SceneTitle::Update(float delta_time) 
{
	sequence_.update(delta_time);
	logoHandle(delta_time);
}

void SceneTitle::Draw(float delta_time) 
{
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_back_hdl, TRUE);

	int logoHeight; // ƒƒS‚Ì‚‚³‚ðŽæ“¾
	GetGraphSize(m_logo_hdl, NULL, &logoHeight); // ƒƒS‚Ì‚‚³‚ðŽæ“¾
	DrawRectExtendGraph(300, 400, 400 + m_current_width, 400 + logoHeight, 0, 0, m_current_width, logoHeight, m_logo_hdl, TRUE);
}

bool SceneTitle::SeqIdle(float delta_time) 
{
	if (sequence_.isStart()) 
	{
		m_back_hdl = LoadGraph("graphics/title/Titleback.jpg");
		m_logo_hdl = LoadGraph("graphics/title/PALLON.png");
		m_current_width = 0;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) 
	{
		auto scene = SceneManager::GetInstance();
		scene->ChangeScene(new ScenePlay());
	}
	return true;
}

void SceneTitle::logoHandle(float delta_time)
{
	// ƒƒS‚Ì•‚ð™X‚É‘‚â‚·
	m_current_width += m_display_time * delta_time;
	if (m_current_width > DXE_WINDOW_WIDTH) m_current_width = DXE_WINDOW_WIDTH;
}