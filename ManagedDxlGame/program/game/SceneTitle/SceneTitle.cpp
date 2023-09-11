#include "../../dxlib_ext/dxlib_ext.h"
#include "SceneTitle.h"
#include "../ScenePlay/scenePlay.h"
#include "../../engine/SceneManager.h"

void SceneTitle::Update(float delta_time) 
{
	sequence_.update(delta_time);
}

void SceneTitle::Draw(float delta_time) 
{
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, title_back_gif, TRUE);
}

// ƒ€[ƒr[‚ðÄ¶ó‘Ô‚É‚µ‚Ü‚·
bool SceneTitle::SeqIdle(float delta_time) 
{
	if (sequence_.isStart()) 
	{
		title_back_gif = LoadGraph("graphics/Titleback.jpg");
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) 
	{
		auto scene = SceneManager::GetInstance();
		scene->ChangeScene(new ScenePlay());
	}
	return true;
}
