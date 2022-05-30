#include "Player.h"
#include "GameScene.h"
#include "Sujet.h"
#include "ExplosiveBomb.h"
#include "ShieldAdder.h"
#include "ElectroBomb.h"

using namespace TP3;

Inputs Player::inputs;

/// <summary>
/// Crée un nouveau <see cref="Player"/>.
/// </summary>
Player::Player()
	:UserControlled(GameObject::PLAYER), Destroyable(PLAYER_DEFAULT_LIFE, PLAYER_DEFAULT_LIFE), currentWeapon(nullptr),
	timerAnimation(sf::microseconds(0)), isInvincible(false), timerOFInvincibility(sf::microseconds(0)), animationInvincibility(sf::microseconds(0)), isDisabled(false)
{
}

/// <summary>
/// Détruit le <see cref="Player"/>.
/// </summary>
Player::~Player()
{
	while (!shields.empty())
	{
		delete shields.top();
		shields.pop();
	}

	while (!inputs.getCommands().empty())
	{
		inputs.removeCommand();
	}
}

/// <summary>
/// Initialise le joueur.
/// Cette méthode doit être appelée une fois avant d'utiliser le joueur.
/// </summary>
/// <param name="spriteKey">La clé du sprite (existant) qui sera utilisé par le joueur.</param>
/// <param name="shieldSpriteKey">La clé du sprite (existant) qui sera utilisé comme bouclier.</param>
/// <returns>true si l'initialisation s'est faite correctement; false sinon.</returns>
bool Player::init(const RessourceManager::key spriteKey, const RessourceManager::key shieldSpriteKey)
{
	setSpeed(PLAYER_DEFAULT_SPEED);

	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(ANIM_RECT_WIDTH / 2, ANIM_RECT_HEIGHT / 2);

	this->shieldSpriteKey = shieldSpriteKey;
	RessourceManager::getInstance()->getSprite(shieldSpriteKey)->setOrigin(SHIELD_WIDTH / 2, SHIELD_HEIGHT / 2);

	for (unsigned int i = 0; i < NBR_ANIM; i++)
	{
		animation[i] = sf::IntRect(i * ANIM_RECT_WIDTH, 0, ANIM_RECT_WIDTH, ANIM_RECT_HEIGHT);
	}
	currentRect = &animation[ANIM_IDLE_POSITION];
	timerAnimation = sf::milliseconds(ANIM_IDLE_POSITION * MS_PER_FRAME);
	sprite->setTextureRect(*currentRect);

	addUserControlled(this);

	isDisabled = false;

	setDimension(ANIM_RECT_WIDTH, ANIM_RECT_HEIGHT);
	return true;
}

/// <summary>
/// Gère les inputs du joueur.
/// </summary>
void Player::getInputs()
{
	int moveMap = 0;

	// Si on joue avec une manette...
	if (sf::Joystick::isConnected(0))
	{
		// Déplacements
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) > 50.0f) moveMap |= 1;
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) < -50.0f) moveMap |= 2;
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) > 50.0f) moveMap |= 4;
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) < -50.0f) moveMap |= 8;

		if (sf::Joystick::isButtonPressed(0, 1))
		{
				fire();
		}
	}
	// Sinon, si on joue avec le clavier...
	else
	{
		// Déplacements...
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) moveMap |= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) moveMap |= 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveMap |= 4;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveMap |= 8;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
				fire();
		}

	}

	// Détermine la nouvelle direction.
	sf::Vector2f newDirection = Movable::convertDirection(getDirectionFromInput(moveMap));
	
	// Si la nouvelle direction est différente de l'ancienne...
	if (newDirection != getDirection())
	{
		// On l'ajoute à la liste des inputs.
		sf::Time whenHappened = getGameScene()->getTimeSinceStart();
		inputs.storeAndExecute(new PlayerCommand_ChangeDirection(newDirection, whenHappened), this);
	}

}

void Player::notifier(Sujet* sujet)
{
	if (GameObject* object = dynamic_cast<GameObject*>(sujet))
	{
		GameObject::ObjectType type = object->getType();

		// Si c'est une bombe explosive, le joueur perds de la vie plus il est près.
		if (type == GameObject::EXPLOSIVE_BOMB)
		{
			ExplosiveBomb* bomb = dynamic_cast<ExplosiveBomb*>(object);

			float distanceX = abs(object->getPosition().x - getPosition().x);
			float distanceY = abs(object->getPosition().y - getPosition().y);

			float distance = sqrtf(distanceX * distanceX + distanceY * distanceY);
			float dommage = ExplosiveBomb::MAX_DAMAGE - (distance / 50);

			if (dommage < 0)
			{
				dommage = 0;
			}

			damage(dommage, bomb->getColor());
		}
		// Si c'est une bombe électromagnétique, on désactive les tirs du joueur pendant quelques instants.
		else if (type == GameObject::ELECTRO_BOMB)
		{
			ElectroBomb* bomb = dynamic_cast<ElectroBomb*>(object);

			if (GameObject::isEnemy(bomb->getPicker()->getType()))
			{
				isDisabled = true;
				timerDisability = sf::milliseconds(ElectroBomb::MS_OF_DISABILITY);
			}
		}
		// Si c'est un ajout d'option, un option est ajouté au jeu.
		else if (type == GameObject::OPTION_ADDER)
		{
			getGameScene()->activateObject(ObjectType::OPTION, getPosition());
		}
		// Si c'est un ajout de bouclier, un bouclier est ajouté au joueur.
		else if (type == GameObject::SHIELD_ADDER)
		{
			ShieldAdder* shieldAdder = dynamic_cast<ShieldAdder*>(object);

			Shield* newShield = new Shield(shieldAdder->getColor());
			newShield->ajouterObservateur(this);

			shields.push(newShield);
		}

	}
	// Si c'est un bouclier, on notifie les observateurs 
	else if (Shield* shield = dynamic_cast<Shield*>(sujet))
	{
		notifierTousLesObservateurs();
	}
}

/// <summary>
/// Retourne la vie du bouclier sur le dessus de la pile des boucliers.
/// </summary>
/// <returns>La vie du bouclier sur le dessus de la pile des boucliers.</returns>
unsigned int Player::getLastShieldLife() const
{
	if (!shields.empty())
	{
		return shields.top()->getLife();
	}
	else
	{
		return 0;
	}
}

/// <summary>
/// Retourne la direction associée à l'input du joueur.
/// </summary>
/// <param name="moveMap">L'input du joueur.</param>
/// <returns>La direction associée à l'input.</returns>
Movable::Direction Player::getDirectionFromInput(int moveMap)
{
	switch (moveMap)
	{
		// Droite
	case 1:
		return Movable::RIGHT;
		break;
		// Gauche
	case 2:
		return Movable::LEFT;
		break;
		// Droite + Gauche
	case 3:
		return Movable::IDLE;
		break;
		// Haut
	case 4:
		return Movable::UP;
		break;
		// Haut + Droite
	case 5:
		return Movable::UP_RIGHT;
		break;
		// Haut + Gauche
	case 6:
		return Movable::UP_LEFT;
		break;
		// Haut + Droite + Gauche
	case 7:
		return Movable::UP;
		break;
		// Bas
	case 8:
		return Movable::DOWN;
		break;
		// Bas + Droite
	case 9:
		return Movable::DOWN_RIGHT;
		break;
		// Bas + Gauche
	case 10:
		return Movable::DOWN_LEFT;
		break;
		// Bas + Droite + Gauche
	case 11:
		return Movable::DOWN;
		break;
		// Bas + Haut
	case 12:
		return Movable::IDLE;
		break;
		// Bas + Haut + Droite
	case 13:
		return Movable::RIGHT;
		break;
		// Bas + Haut + Gauche
	case 14:
		return Movable::LEFT;
		break;
		// Bas + Haut + Droite + Gauche
	case 15:
		return Movable::IDLE;
		break;
		// Aucune commande de mouvement.
	default:
		return Movable::IDLE;
		break;
	}
}

/// <summary>
/// Update le joueur selon le temps écoulé.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void Player::update(const float deltaT)
{
	// Met à jour la période où le joueur ne peut pas tirer.
	if (isDisabled)
	{
		timerDisability -= sf::seconds(deltaT);

		if (timerDisability.asMilliseconds() <= 0)
		{
			isDisabled = false;
		}
	}

	// Met à jour la période d'invincibilité.
	if (isInvincible)
	{
		timerOFInvincibility -= sf::seconds(deltaT);
		animationInvincibility += sf::seconds(deltaT);

		if (timerOFInvincibility.asMilliseconds() <= 0)
		{
			isInvincible = 0;
		}
	}
	// On enlève seulement des commandes si c'est le dernier joueur.
	if (isLast())
	{
		// S'il y a des commandes...
		if (!inputs.getCommands().empty())
		{
			// Si ça fait assez longtemps que la commande est stockée...
			if ((getGameScene()->getTimeSinceStart().asMilliseconds() - inputs.getCommands().front()->whenHappened.asMilliseconds()) > MS_BEFORE_COMMAND_REMOVAL)
			{
				// On l'enlève.
				inputs.removeCommand();
			}
		}
	}

	UserControlled::update(deltaT);
	animate(deltaT);

	// On fait tourner le bouclier.
	RessourceManager::getInstance()->getSprite(shieldSpriteKey)->rotate(2);
	
	adjustIntoMap();
}

/// <summary>
/// Affiche le joueur sur la fenêtre de jeu.
/// </summary>
/// <param name="window">La fenêtre sur laquelle afficher le joueur.</param>
void Player::draw(sf::RenderWindow& window)
{
	// Fait clignoter le joueur s'il est invisible.
	if (isInvincible)
	{
		if ((animationInvincibility.asMilliseconds() % MS_BEFORE_FLASHING_INVINCIBILITY) <= (MS_BEFORE_FLASHING_INVINCIBILITY * 0.5f))
		{
			RessourceManager::getInstance()->getSprite(getSpriteKey())->setTextureRect(*currentRect);
			UserControlled::draw(window);
		}
	}
	else
	{
		RessourceManager::getInstance()->getSprite(getSpriteKey())->setTextureRect(*currentRect);
		UserControlled::draw(window);
	}

	if (!shields.empty())
	{
		sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(shieldSpriteKey);
		sprite->setColor(shields.top()->getColor());
		sprite->setPosition(getPosition());
		window.draw(*sprite);
	}
}

/// <summary>
/// Change l'arme du joueur.
/// </summary>
/// <param name="weapon">L'arme.</param>
void Player::changeWeapon(Weapon* weapon)
{
	currentWeapon = weapon;
}

/// <summary>
/// Change la direction du joueur.
/// </summary>
/// <param name="direction">La nouvelle direction du joueur.</param>
void Player::changeDirection(const sf::Vector2f direction)
{
	setDirection(direction);
}

/// <summary>
/// Fait tirer le joueur avec son arme.
/// </summary>
void Player::fire()
{
	if (!isDisabled)
	{
		if (currentWeapon)
		{
			currentWeapon->fire();
		}
	}
}

/// <summary>
/// Ajuste la position du joueur pour qu'il reste toujours dans les limites du niveau.
/// </summary>
void Player::adjustIntoMap()
{
	sf::Vector2f pos = getPosition();
	sf::Vector2f halfSize = getDimension() * 0.5f;
	GameScene* game = getGameScene();

	// Limites horizontales.
	if (pos.x - halfSize.x < game->GAME_LEFT)
	{
		setPosition(game->GAME_LEFT + halfSize.x, pos.y);
	}
	else if (pos.x + halfSize.x >= game->GAME_LEFT + game->GAME_WIDTH)
	{
		setPosition(game->GAME_LEFT + game->GAME_WIDTH - halfSize.x - 1, pos.y);
	}

	pos = getPosition();

	// Limites vertivales.
	if (pos.y - halfSize.y < game->GAME_TOP)
	{
		setPosition(pos.x, game->GAME_TOP + halfSize.y);
	}
	else if (pos.y + halfSize.y >= game->GAME_TOP + game->GAME_HEIGHT)
	{
		setPosition(pos.x, game->GAME_TOP + game->GAME_HEIGHT - halfSize.y - 1);
	}
}

/// <summary>
/// Endommage le joueur.
/// </summary>
/// <param name="life">Le dommage fait au joueur.</param>
void Player::damage(const unsigned int life)
{
	damage(life, sf::Color::White);
}

/// <summary>
/// Endommage le joueur.
/// </summary>
/// <param name="life">Le dommage fait au joueur.</param>
/// <param name="dammageColor">La couleur de ce qui a fait le dommage au joueur.</param>
void Player::damage(const unsigned int life, const sf::Color& dammageColor)
{
	if (!isInvincible)
	{
		int lifePtsToRemove = life;

		// Tant qu'il reste des points de vie à enlever...
		while (lifePtsToRemove > 0)
		{
			// Si on n'a pas de bouclier...
			if (shields.empty())
			{
				// Le joueur se prend directement les dégats.
				Destroyable::damage(lifePtsToRemove);
				lifePtsToRemove = 0;
			}
			// Si on a un bouclier...
			else
			{
				// Les points de vie à enlever diminuent selon la vie restante du bouclier.
				lifePtsToRemove -= shields.top()->getLife();
				// Et le bouclier se prend du dommage.
				shields.top()->damage(life, dammageColor);

				// Si le bouclier est détruit...
				if (shields.top()->isDestroyed())
				{
					// On l'enlève de la pile des boucliers.
					delete shields.top();
					shields.pop();
				}
			}
		}
	}
}

/// <summary>
/// Retourne les inputs du joueur.
/// </summary>
/// <returns>Les inputs du joueur.</returns>
Inputs& Player::getPlayerInputs()
{
	return inputs;
}

/// <summary>
/// Anime le vaisseau du joueur.
/// </summary>
void Player::animate(const float deltaT)
{
	if (getDirection().y < 0)
	{
		timerAnimation = timerAnimation - sf::seconds(deltaT) < sf::microseconds(0) ? sf::microseconds(0) : timerAnimation - sf::seconds(deltaT);
	}
	else if (getDirection().y > 0)
	{
		timerAnimation = timerAnimation + sf::seconds(deltaT) > sf::milliseconds(NBR_ANIM * MS_PER_FRAME - 1) ? sf::milliseconds(NBR_ANIM * MS_PER_FRAME - 1) : timerAnimation + sf::seconds(deltaT);
	}
	else
	{
		if (timerAnimation < sf::milliseconds(ANIM_IDLE_POSITION * MS_PER_FRAME))
		{
			timerAnimation += sf::seconds(deltaT);

			if (timerAnimation > sf::milliseconds(ANIM_IDLE_POSITION * MS_PER_FRAME))
			{
				timerAnimation = sf::milliseconds(ANIM_IDLE_POSITION * MS_PER_FRAME);
			}
		}
		else if (timerAnimation > sf::milliseconds(ANIM_IDLE_POSITION * MS_PER_FRAME))
		{
			timerAnimation -= sf::seconds(deltaT);

			if (timerAnimation < sf::milliseconds(ANIM_IDLE_POSITION * MS_PER_FRAME))
			{
				timerAnimation = sf::milliseconds(ANIM_IDLE_POSITION * MS_PER_FRAME);
			}
		}
	}

	currentRect = &animation[timerAnimation.asMilliseconds() / MS_PER_FRAME];
}

/// <summary>
/// Détermine une période d'invincibilité pour le joueur.
/// </summary>
/// <param name="milliseconds">Le nombre de millisecondes d'invincibilité.</param>
void Player::setInvincivility(const unsigned int milliseconds)
{
	if (!isInvincible)
	{
		timerOFInvincibility = sf::milliseconds(milliseconds);
		isInvincible = true;
	}
}