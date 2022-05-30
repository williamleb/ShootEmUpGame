#include "Weapon.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Repr�sente la sc�ne de jeu qui est pr�sentement jou�e.
/// </summary>
GameScene* Weapon::gameScene = nullptr;

/// <summary>
/// Repr�sente le joueur qui utilise les armes.
/// </summary>
Player* Weapon::player = nullptr;

/// <summary>
/// Change la sc�ne de jeu qui est pr�sentement jou�e pour tous les objets.
/// </summary>
/// <param name="gameScene">La sc�ne de jeu pr�sentement jou�e.</param>
void Weapon::setGameScene(GameScene* gameScene)
{
	Weapon::gameScene = gameScene;
}

/// <summary>
/// Retourne la sc�ne de jeu pr�sentement jou�e.
/// </summary>
/// <returns>La sc�ne de jeu pr�sentement jou�e.</returns>
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
/// Cr�e un nouveau <see cref="Weapon"/>.
/// </summary>
/// <param name="type">Le type de l'arme.</param>
/// <param name="fireRate">Le nombre de millisecondes entre chaque tir.</param>
/// <param name="maxAmmo">Le nombre maximal de balles que contient une arme.</param>
Weapon::Weapon(const WeaponType type, const int fireRate, const unsigned int defaultAmmo, const unsigned int maxAmmo)
	: fireRateInMS(fireRate), fireTimer(sf::microseconds(0)), defaultAmmo(defaultAmmo), maxAmmo(maxAmmo), ammo(defaultAmmo), type(type)
{
}

/// <summary>
/// D�truit un <see cref="Weapon"/>.
/// </summary>
Weapon::~Weapon()
{
}

/// <summary>
/// Met � jour l'arme.
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
/// D�termine si l'arme n'a plus de munitions.
/// </summary>
/// <returns>true si l'arme n'a plus de munitions; false sinon.</returns>
bool Weapon::empty() const
{
	return ammo == 0;
}

/// <summary>
/// Ajoute des munitions � l'arme.
/// </summary>
/// <param name="ammo">Le nombre de munitions � ajouter.</param>
void Weapon::addAmmo(const unsigned int ammo)
{
	// On n'ajoute pas de munition si l'arme en a d�j� une infinit�.
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
/// Ajoute le nombre de munitions par d�faut de l'arme.
/// </summary>
void Weapon::addDefaultAmmo()
{
	addAmmo(defaultAmmo);
}

/// <summary>
/// Enl�ve des munitions � l'arme.
/// </summary>
/// <param name="ammo">Le nombre de munitions � enlever.</param>
void Weapon::loseAmmo(const unsigned int ammo)
{
	// On n'enl�ve pas de munitions si l'arme en a une infinit�.
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
/// D�termine si l'arme tir ou non.
/// Doit �tre appel�e par l'arme avant de tirer.
/// </summary>
/// <returns>true si l'arme tire; false sinon.</returns>
bool Weapon::tryFire()
{
	// L'arme peut tirer si elle a des munitions et que �a
	// fait assez longtemps qu'elle a tir�.
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