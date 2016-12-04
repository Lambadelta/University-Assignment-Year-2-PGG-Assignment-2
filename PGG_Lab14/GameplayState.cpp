#include "GameplayState.h"

GameplayState::GameplayState(Manager* GSManager, SDL_Renderer* Renderer) : Gamestate(GSManager, Renderer)
{

	Name = "Gameplay";

	std::srand((unsigned int)std::time(0));

	tESpawn.setInitialTime(2.f);

	BackgroundP.setMeshObject(OBJLoader.packageModelObject("Assets/models/Background.obj"));
	BackgroundP.initVAO("Assets/shaders/vShader.txt", "Assets/shaders/fShader.txt");
	BackgroundP.initTexture("Assets/images/Background.png");
	BackgroundP.setRotation(-1.564f, 0.f, 0.f);
	BackgroundP.setPosition(0.f, 0.f, -1.f);



	//Load in the player ship mesh, and store it inside the player
	PlayerMesh = OBJLoader.packageModelObject("Assets/models/OrionOBJ.obj");
	Player.setMeshObject(PlayerMesh);
	//Load in the bullet mesh, and store it inside the player to be used for any bullets to prevent reloading the object.
	BulletMesh = OBJLoader.packageModelObject("Assets/models/Bullet.obj");
	Player.setBulletMesh(BulletMesh);
	//Initialize the Vertex Array Object of the Player
	Player.initVAO("Assets/shaders/vShader.txt", "Assets/shaders/fShader.txt");
	Player.initTexture("Assets/images/PlayerTexture.png");
	//Set the rotation, and position of the player
	Player.setRotation(-1.7f, 15.7f, 0.f);
	Player.setPosition(0.0f, -11.5f, 0.0f);
	//Load in the enemy ship mesh, and store it so that any new enemies created can use it.
	EnemyMesh = OBJLoader.packageModelObject("Assets/models/Enemy.obj");
	// Construct a projection matrix for the camera
	Projection = glm::perspective(45.0f, 3.0f / 4.0f, 0.1f, 100.0f);
	// Create a viewing matrix for the camera
	View = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, -1.0f, -30.0f));

	initVisualUI();

	GameMus = Mix_LoadMUS("Assets/music/GameStateMus.wav");
	Laser = Mix_LoadWAV("Assets/music/laser.wav");
	Mix_PlayMusic(GameMus, -1);
	Mix_VolumeMusic(30);
	Mix_VolumeChunk(Laser, 5);
	score = 0;

}

GameplayState::~GameplayState()
{
	Mix_FreeChunk(Laser); 
	Mix_FreeMusic(GameMus);
	vEnemy.clear();

}

void GameplayState::update(float dt)
{
	BackgroundP.update(dt);
	Player.update(dt);
	tESpawn.updateTimer(dt);
	if (tESpawn.expiredTimer())
	{
		spawnEnemy();
		tESpawn.resetTimer();
	}
	for (unsigned int i = 0; i < vEnemy.size(); i++)
	{
		vEnemy[i].update(dt);
	}
	for (unsigned int ii = 0; ii < PlayerHealth.size(); ii++)
	{
		PlayerHealth[ii].update(dt);
	}
	bool AABBbreak = false;
	for (unsigned int j = 0; j < Player.getVBullet().size(); j++)
	{
		for (unsigned int k = 0; k < vEnemy.size(); k++)
		{
			if (checkAABB(Player.getVBullet()[j], vEnemy[k].getXYPos()))
			{
				Player.getVBullet()[j].setAliveStatus(false);
				vEnemy[k].setAliveStatus(false);
				score += 25;
				printf("%i\n", score);
				break;
			}
		}
		if (AABBbreak){ break; }
	}
	AABBbreak = false;
	for (unsigned int p = 0; p < vEnemy.size(); p++)
	{
		for (unsigned int m = 0; m < vEnemy[p].getVBullet().size(); m++)
		{
			if (checkAABB(vEnemy[p].getVBullet()[m], Player.getXYPos()))
			{
				vEnemy[p].getVBullet()[m].setAliveStatus(false);
				Player.setAliveStatus(false);
				break;
			}
		}
		if (AABBbreak){ break; }
	}

	cleanup();
}
	
void GameplayState::draw()
{
	BackgroundP.draw(View, Projection);
	for (unsigned int i = 0; i < Player.getVBullet().size(); i++)
	{
		Player.getVBullet()[i].draw(View, Projection);
	}

	
	Player.draw(View, Projection);

	for (unsigned int j = 0; j < vEnemy.size(); j++)
	{
		vEnemy[j].draw(View, Projection);
		for (unsigned int k = 0; k < vEnemy[j].getVBullet().size(); k++)
		{
			vEnemy[j].getVBullet()[k].draw(View, Projection);
		}
	}

	for (unsigned int ii = 0; ii < PlayerHealth.size(); ii++)
	{
		if (PlayerHealth[ii].getAliveStatus())
		{
			PlayerHealth[ii].draw(View, Projection);
		}
	}

}

void GameplayState::spawnEnemy()
{
	EnemyEntity Enemy;
	Enemy.setMeshObject(EnemyMesh);
	Enemy.setBulletMesh(BulletMesh);
	//Initialize the Vertex Array Object of the Enemy
	Enemy.initVAO("Assets/shaders/vShader.txt", "Assets/shaders/fShader.txt");
	Enemy.initTexture("Assets/images/EnemyTexture.png");
	//Setting the Position, and Rotation to ensure Enemies are facing player
	Enemy.setRotation(-1.7f, -15.7f, 0.f);
	Enemy.setPosition(randNum(-8,8), 20.5f, 0.0f);
	Enemy.setExit();
	vEnemy.push_back(Enemy);
}

void GameplayState::initVisualUI()
{
	PlayerHealthUI = OBJLoader.packageModelObject("Assets/models/PHealth.obj");
	for (int i = 0; i < 3; i++)
	{
		BackgroundPlane newHealthIcon;
		newHealthIcon.setMeshObject(PlayerHealthUI);
		newHealthIcon.initVAO("Assets/shaders/vShader.txt", "Assets/shaders/fShader.txt");
		newHealthIcon.initTexture("Assets/images/PlayerTexture.png");
		newHealthIcon.setRotation(-1.7f, 15.7f, 0.f);
		newHealthIcon.setPosition(-9.5f + (i * 2), -10.5f, 5.0f);
		newHealthIcon.setSpin(true);
		PlayerHealth.push_back(newHealthIcon);

	}
}

bool GameplayState::checkAABB(Bullet& BO, PVector& EO)
{
	float X1min = BO.getXYPos().x;
	float X1max = BO.getXYPos().x + 0.1f;
	float Y1min = BO.getXYPos().y;
	float Y1max = BO.getXYPos().y + 0.1f;

	float X2min = EO.x;
	float X2max = EO.x + 5.f;
	float Y2min = EO.y;
	float Y2max = EO.y + 2.5f;

	if (X1max < X2min || X1min > X2max)
	{
		return false;
	}
	if (Y1max < Y2min || Y1min > Y2max)
	{
		return false;
	}

	return true;
}

void GameplayState::cleanup()
{
	for (unsigned int j = 0; j < vEnemy.size(); j++)
	{
		for (unsigned int m = 0; m < vEnemy[j].getVBullet().size(); m++)
		{
			if (!vEnemy[j].getVBullet()[m].getAliveStatus())
			{
				vEnemy[j].getVBullet().erase(vEnemy[j].getVBullet().begin() + m);
			}
		}
		if (!vEnemy[j].getAliveStatus())
		{
			vEnemy.erase(vEnemy.begin() + j);
			break;
		}
	}
	for (unsigned int i = 0; i < Player.getVBullet().size(); i++)
	{
		if (!Player.getVBullet()[i].getAliveStatus())
		{
			Player.getVBullet().erase(Player.getVBullet().begin() + i);
		}
	}
	if (!Player.getAliveStatus())
	{
		if (Player.getLives() > 0)
		{
			PlayerHealth[Player.getLives() - 1].setAliveStatus(false);
			Player.subLives(1);
			Player.setAliveStatus(true);
		}
		if (Player.getLives() <= 0)
		{

			GSManager->setMenuStatus(true);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			GSManager->Add(new Creditsstate(GSManager, renderer, score));
		}
	}
}

float GameplayState::randNum(int min, int max)
{
	float random = (float)(std::rand() % (max - min) + min);
	return random;
}

bool GameplayState::EventHandle()
{
	/************************************************************************/
	/* Event Loop                                                           */
	/************************************************************************/
	SDL_Event eve;
	while (SDL_PollEvent(&eve))
	{
		switch (eve.type)
		{
		case SDL_QUIT:
			GSManager->setGameStatus(false);
			break;
		case SDL_KEYDOWN:
			switch (eve.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				GSManager->setGameStatus(false);
				break;
			case SDLK_LEFT:
				Player.movePLeft(true);
				break;
			case SDLK_RIGHT:
				Player.movePRight(true);
				break;
			case SDLK_a:
				Player.movePLeft(true);
				break;
			case SDLK_d:
				Player.movePRight(true);
				break;
			case SDLK_SPACE:
				Player.shootBullet();
				Mix_PlayChannel(-1, Laser, 0);
				break;
			}
			break;
		case SDL_KEYUP:
			switch (eve.key.keysym.sym)
			{
			case SDLK_LEFT:
				Player.movePLeft(false);
				break;
			case SDLK_RIGHT:
				Player.movePRight(false);
				break;
			case SDLK_a:
				Player.movePLeft(false);
				break;
			case SDLK_d:
				Player.movePRight(false);
				break;
			}
			break;
		}
	}
	return true;
}


