#include "Weapon.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Représente la scène de jeu qui est présentement jouée.
/// </summary>
GameScene* Weapon::gameScene = nullptr;

/// <summary>
/// Représente le joueur qui utilise les armes.
/// </summary>
Player* Weapon::player = nullptr;

/// <summary>
/// Change la scène de jeu qui est présentement jouée pour tous les objets.
/// </summary>
/// <param name="gameScene">La scène de jeu présentement jouée.</param>
void Weapon::setGameScene(GameScene* gameScene)
{
	Weapon::gameScene = gameScene;
}

/// <summary>
/// Retourne la scène de jeu présentement jouée.
/// </summary>
/// <returns>La scène de jeu présentement jouée.</returns>
GameScene* Weapon::getGameScene()
{
	return Weapon::gameScene;
}

/// <summary>
/// Change le joueur qui utilise les armes.
/// </summary>
/// <param name="gameScene">Le joueur qui utilise les armes.</param>
void Weapon::setPlayer(Player* player)
{
	Weapon::player = player;
}

/// <summary>
/// Retourne le joueur qui utilise les armes.
/// </summary>
/// <returns>Le joueur qui utilise les armes.</returns>
Player* Weapon::getPlayer()
{
	return Weapon::player;
}

/// <summary>
/// Crée un nouveau <see cref="Weapon"/>.
/// </summary>
/// <param name="type">Le type de l'arme.</param>
/// <param name="fireRate">Le nombre de millisecondes entre chaque tir.</param>
/// <param name="maxAmmo">Le nombre maximal de balles que contient une arme.</param>
Weapon::Weapon(const WeaponType type, const int fireRate, const unsigned int defaultAmmo, const unsigned int maxAmmo)
	: fireRateInMS(fireRate), fireTimer(sf::microseconds(0)), defaultAmmo(defaultAmmo), maxAmmo(maxAmmo), ammo(defaultAmmo), type(type)
{
}

/// <summary>
/// Détruit un <see cref="Weapon"/>.
/// </summary>
Weapon::~Weapon()
{
}

/// <summary>
/// Met à jour l'arme.
/// </summary>
/// <param name="deltaT">Le temps en secondes depuis le dernier appel d'update.</param>
void Weapon::update(const float deltaT)
{
	fireTimer += sf::seconds(deltaT);
}

/// <summary>
/// Retourne le nombre de munitions.
/// </summary>
/// <returns>Le nombre de munition restantes.</returns>
unsigned int Weapon::getAmmo() const
{
	return ammo;
}

/// <summary>
/// Détermine si l'arme n'a plus de munitions.
/// </summary>
/// <returns>true si l'arme n'a plus de munitions; false sinon.</returns>
bool Weapon::empty() const
{
	return ammo == 0;
}

/// <summary>
/// Ajoute des munitions à l'arme.
/// </summary>
/// <param name="ammo">Le nombre de munitions à ajouter.</param>
void Weapon::addAmmo(const unsigned int ammo)
{
	// On n'ajoute pas de munition si l'arme en a déjà une infinité.
	if (this->ammo != INFINITE_AMMO)
	{
		if (this->ammo + ammo > maxAmmo)
		{
			this->ammo = maxAmmo;
		}
		else
		{
			this->ammo += ammo;
		}
	}
}

/// <summary>
/// Ajoute le nombre de munitions par défaut de l'arme.
/// </summary>
void Weapon::addDefaultAmmo()
{
	addAmmo(defaultAmmo);
}

/// <summary>
/// Enlève des munitions à l'arme.
/// </summary>
/// <param name="ammo">Le nombre de munitions à enlever.</param>
void Weapon::loseAmmo(const unsigned int ammo)
{
	// On n'enlève pas de munitions si l'arme en a une infinité.
	if (ammo != INFINITE_AMMO)
	{
		if (ammo > this->ammo)
		{
			this->ammo = 0;
		}
		else
		{
			this->ammo -= ammo;
		}
	}
}

/// <summary>
/// Détermine si l'arme tir ou non.
/// Doit être appelée par l'arme avant de tirer.
/// </summary>
/// <returns>true si l'arme tire; false sinon.</returns>
bool Weapon::tryFire()
{
	// L'arme peut tirer si elle a des munitions et que ça
	// fait assez longtemps qu'elle a tiré.
	if (fireTimer.asMilliseconds() >= fireRateInMS && ammo > 0)
	{
 		fireTimer = sf::microseconds(0);
		return true;
	}

	return false;
}

/// <summary>
/// Retourne le type de l'arme.
/// </summary>
/// <returns>Le type de l'arme.</returns>
Weapon::WeaponType Weapon::getType()
{
	return type;
}