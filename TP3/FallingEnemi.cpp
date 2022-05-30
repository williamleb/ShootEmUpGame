#include "FallingEnemi.h"
#include "GameScene.h"
using namespace TP3;

FallingEnemi::FallingEnemi()
	:Enemi()
{
}

FallingEnemi::~FallingEnemi()
{
}

void FallingEnemi::fire()
{
	GameScene* game = getGameScene();

	if (shootTimerInMs >= NBR_MS_BEFORE_SHOOT)
	{

		game->activateMovable(GameObject::RED_LAZER, getPosition(), Movable::LEFT);
		shootTimerInMs = 0;
	}


}

void FallingEnemi::init(const RessourceManager::key spriteKey, Player *player)
{
	setDimension(WIDTH, HEIGHT);
	shootTimerInMs = 0;
	joueur = player;
	setSpeed(FALLING_ENEMI_DEFAULT_SPEED);
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	setPosition(700, 0);
}



void FallingEnemi::update(const float deltaT)
{
	setState(Enemy::State::Moving);
	deplacement.y = 1;
	Movable::setDirection(deplacement);
	fire();
	Movable::update(deltaT);
	shootTimerInMs++;

}

void FallingEnemi::draw(sf::RenderWindow & window)
{
	Movable::draw(window);
}

void FallingEnemi::activate(const sf::Vector2f& position)
{
	setPosition(position);
	Activatable::activate();
}

void TP3::FallingEnemi::getType()
{
}
