#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "Gamestate.h"
#include "Manager.h"
#include "Loader.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "BackgroundPlane.h"
#include "SDL_mixer.h"
#include "Creditsstate.h"

class GameplayState : public Gamestate
{
public:
	GameplayState(Manager*, SDL_Renderer*);
	~GameplayState();


	bool EventHandle();
	void update(float);
	void draw();
	void spawnEnemy();
	void initVisualUI();
	bool checkAABB(Bullet&, PVector&);
	void cleanup();
	float randNum(int, int);

private:
	PlayerEntity Player;
	std::vector<EnemyEntity> vEnemy;
	std::vector<BackgroundPlane> PlayerHealth;
	Loader OBJLoader;

	Object EnemyMesh;
	Object BulletMesh;
	Object PlayerMesh;
	Object PlayerHealthUI;

	BackgroundPlane BackgroundP;
	BackgroundPlane UI;

	glm::mat4 Projection;
	glm::mat4 View;
	Timer tESpawn;
	int score;

	Mix_Music* GameMus;
	Mix_Chunk* Laser;

};

#endif