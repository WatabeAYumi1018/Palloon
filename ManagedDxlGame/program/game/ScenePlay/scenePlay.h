#pragma once
#include "../../engine/sceneBase.h"
#include "../SceneAll/GameObject.h"

class Camera;
class BackGround;
class Map;
class Collision;
class EnemyLoad;
class Player;
class Enemy;
class EffectPlayer;

class ScenePlay : public SceneBase 
{
public:
	ScenePlay();
	virtual ~ScenePlay();

	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time) override;
	void Finalize() override;

	//-----メンバ変数-----//
	BackGround *m_backGround=nullptr;
	Camera*m_camera=nullptr;
	Map *m_map=nullptr;
	Collision *m_collision=nullptr;
	EnemyLoad* m_enemyLoad = nullptr;
	Player *m_player = nullptr;

private:
	
	std::list<GameObject*> m_gameObjects;
	tnl::Sequence<ScenePlay> m_sequence = tnl::Sequence<ScenePlay>(this, &ScenePlay::SeqSceneIdle);
	
	std::list<Enemy*> m_enemies;					// 敵のリスト
	std::map<int, sEnemyInfo> m_enemyInfos;			// 敵の情報リスト
	std::list<EffectPlayer*> m_effects;				/*エフェクト*/

	std::list<Enemy*> m_enemiesRemoveList;			/*削除予定の敵*/
	std::list<EffectPlayer*> m_effectsRemoveList;	/*削除予定のエフェクト*/

	void InitEnemy();
	void CreateEffect();
	bool SeqSceneIdle(float delta_time);

	void CollisionCheck();
	void RemoveAndDeleteEffect(EffectPlayer *effectPlayer);
	void RemoveAndDeleteEnemy(Enemy *enemy);
	void RemoveAndDelete();

	//遷移後、back,Map,UI,Player,Enemyなどを描画する
	//現在のシーンで描画するグラフィックを変える
	int m_graph_hdl = 0;
};