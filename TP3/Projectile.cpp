#include "Projectile.h"
#include "GameScene.h"
#include <cassert>
#include "RessourceManager.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="Projectile"/>.
/// </summary>
/// <param name="type">Le type du projectile.</param>
/// <param name="speed">La vitesse du projectile.</param>
/// <param name="power">Les dégâts infligés par le projectile.</param>
/// <param name="health">La vie du projectile.</param>
/// <param name="faction">La faction du projectile.</param>
Projectile::Projectile(const ObjectType type, const float speed, const int power, const unsigned int health, const ProjectileFaction faction)
	: Movable(type), Destroyable(health, health), faction(faction), power(power)
{
	assert(isProjectile(type) && "Le type donnée doit en être un de projectile.");

	setSpeed(speed);
}

/// <summary>
/// Crée un nouveau <see cref="Projectile"/>.
/// </summary>
/// <param name="type">Le type du projectile.</param>
/// <param name="speed">La vitesse du projectile.</param>
/// <param name="power">Les dégâts infligés par le projectile.</param>
/// <param name="faction">La faction du projectile.</param>
/// <param name="health">La vie du projectile.</param>
Projectile::Projectile(const ObjectType type, const float speed,const int power, const ProjectileFaction faction, const unsigned int health)
	: Movable(type), Destroyable(health, health), faction(faction), power(power)
{
	assert(isProjectile(type) && "Le type donnée doit en être un de projectile.");

	setSpeed(speed);
}

/// <summary>
/// Détruit un <see cref="Projectile"/>.
/// </summary>
Projectile::~Projectile()
{
}

/// <summary>
/// Active le projectile.
/// </summary>
/// <param name="position">La position à laquelle activer le projectile.</param>
void Projectile::activate(const sf::Vector2f& position)
{
	setPosition(position);
	Activatable::activate();
	/*sf::Music *music = ressourceManager->getMusic(SOUND_BLASTER_FIRE);
	music->play();*/
}

/// <summary>
/// Endommage le projectile d'un certain nombre de points de vie.
/// </summary>
/// <param name="life">Le nombre de points de vie perdus par le projectile.</param>
void Projectile::damage(const unsigned int life)
{
	Destroyable::damage(life);

	// Si le projectile vient d'être détruit, on le désactive.
	if (isDestroyed())
	{
		deactivate();
	}
}

/// <summary>
/// Retourne la faction du projectile.
/// </summary>
/// <returns>La faction du projectile.</returns>
Projectile::ProjectileFaction Projectile::getFaction() const
{
	return faction;
}

/// <summary>
/// Retourne les dégâts infligés par le projectile.
/// </summary>
/// <returns>Les dégats infligés par le projectile.</returns>
int Projectile::getPower()
{
	return power;
}



/// <summary>
/// Update le projectile selon le temps écoulé.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void Projectile::update(const float deltaT)
{
	if (isActivated())
	{
		Movable::update(deltaT);
		// Le projectile se désactive s'il sort de la scène.
		sf::Vector2f pos = getPosition();
		sf::Vector2f halfSize = getDimension() * 0.5f;
		GameScene* game = getGameScene();
		// Limites horizontales.
		if (pos.x + halfSize.x < game->GAME_LEFT)
		{
			deactivate();
		}
		else if (pos.x - halfSize.x >= game->GAME_LEFT + game->GAME_WIDTH)
		{
			deactivate();
		}

		pos = getPosition();

		// Limites vertivales.
		if (pos.y + halfSize.y < game->GAME_TOP)
		{
			deactivate();
		}
		else if (pos.y - halfSize.y >= game->GAME_TOP + game->GAME_HEIGHT)
		{
			deactivate();
		}
	}
}

/// <summary>
/// Affiche le projectile.
/// </summary>
/// <param name="window">La fenêtre sur laquelle afficher le projectile.</param>
void Projectile::draw(sf::RenderWindow& window)
{
	if (isActivated())
	{
		Movable::draw(window);
	}
}