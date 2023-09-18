#pragma once
#include "../../engine/sceneBase.h"
#include "../SceneAll/GameObject.h"

//scene内で必要な全ての要素を管理するクラス
//★Mapと同様、現状は期限内完成を優先し、同じ内容で素材の異なる複数コピークラスを作成。
//★このままでは再利用性が皆無のため、後日改めて修正し、ひとつのステージにまとめる実装に変更する。

class Camera;
class BackGround;
class Map1;
class Collision;
class ClearBalloon;
class EnemyLoad;
class Player;
class Enemy;
class EffectPlayer;

class ScenePlay1 : public SceneBase 
{
public:
	ScenePlay1();
	virtual ~ScenePlay1();

	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time) override;
	void Finalize() override;

	//-----メンバ変数-----//
	BackGround *m_backGround=nullptr;
	Camera*m_camera=nullptr;
	Map1*m_map=nullptr;
	Collision *m_collision=nullptr;
	ClearBalloon *m_clearBalloon=nullptr;
	EnemyLoad* m_enemyLoad = nullptr;
	Player *m_player = nullptr;
	Enemy* m_enemy = nullptr;

private:
	
	bool m_is_change_scene = false;

	std::list<GameObject*> m_gameObjects;
	tnl::Sequence<ScenePlay1> m_sequence = tnl::Sequence<ScenePlay1>(this, &ScenePlay1::SeqSceneIdle);
	
	std::list<Enemy*> m_enemies;					// 敵のリスト
	std::map<int, sEnemyInfo> m_enemyInfos;			// 敵の情報リスト
	std::list<EffectPlayer*> m_effects;				/*エフェクト*/

	std::list<Enemy*> m_enemiesRemoveList;			/*削除予定の敵*/
	std::list<EffectPlayer*> m_effectsRemoveList;	/*削除予定のエフェクト*/

	void InitEnemy();
	void CreateEffect();
	bool SeqSceneIdle(float delta_time);

	void CollisionCheck(float delta_time);
	bool ClearCheckErea();
	void RemoveAndDeleteEffect(EffectPlayer *effectPlayer);
	void RemoveAndDeleteEnemy(Enemy *enemy);
	void RemoveAndDelete();
};