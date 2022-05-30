#include "RessourceManager.h"

#include <map>

using namespace TP3;

/// <summary>
/// L'instance en cours de l'administrateur de ressources.
/// </summary>
RessourceManager* RessourceManager::instance = nullptr;

/// <summary>
/// Crée un nouveau <see cref="RessourceManager"/>.
/// </summary>
RessourceManager::RessourceManager()
{ 
}

/// <summary>
/// Drétuit un <see cref="RessourceManager"/>.
/// </summary>
RessourceManager::~RessourceManager()
{
}

/// <summary>
/// Détruit toutes les ressources présentes dans l'administrateur de ressource.
/// </summary>
void RessourceManager::clear()
{
	// Delete toutes les textures.
	for (std::map<key, sf::Texture*>::iterator i = textures.begin(); i != textures.end(); i++)
	{
		delete (*i).second;
	}
	textures.clear();
	
	// Delete toutes les musiques.
	for (std::map<key, sf::Music*>::iterator i = musics.begin(); i != musics.end(); i++)
	{
		delete (*i).second;
	}
	musics.clear();

	// Delete tous les drawables.
	for (std::map<key, sf::Drawable*>::iterator i = drawables.begin(); i != drawables.end(); i++)
	{
		delete (*i).second;
	}
	drawables.clear();
}

/// <summary>
/// Retourne l'instance en cours de l'administrateur de ressources.
/// </summary>
/// <returns>L'instance en cours de l'administrateur de ressources.</returns>
RessourceManager* RessourceManager::getInstance()
{
	if (!instance)
	{
		instance = new RessourceManager();
	}

	return instance;
}

/// <summary>
/// Détruit l'instance de l'administrateur de ressources.
/// </summary>
void RessourceManager::deleteInstance()
{
	if (instance != nullptr)
	{
		instance->clear();
		delete instance;
		instance = nullptr;
	}
}

/// <summary>
/// Ajoute une texture.
/// </summary>
/// <param name="path">Le chemin de la texture.</param>
/// <param name="newKey">La clé avec laquelle ajouter la texture.
///												Ce doit être une clé qui n'est pas déjà utilisée.
///												Celle-ci servira à accéder à la texture.</param>
/// <returns>True si l'ajout de la texture s'est faite avec succès; false sinon.</returns>
bool RessourceManager::addTexture(const sf::String& path, key newKey)
{
	sf::Texture* newTexture = new sf::Texture();
	
	if (!newTexture->loadFromFile(path))
	{
		return false;
	}

	size_t size = textures.size();
	textures.insert(std::pair<key, sf::Texture*>(newKey, newTexture));

	if (size == textures.size())
	{
		return false;
	}

	return true;
}

/// <summary>
/// Ajoute une musique.
/// </summary>
/// <param name="path">Le chemin de la musique.</param>
/// <param name="newKey">La clé avec laquelle ajouter la texture.
///												Ce doit être une clé qui n'est pas déjà utilisée.
///												Celle-ci servira à accéder à la musique.</param>
/// <returns>True si l'ajout de la texture s'est faite avec succès; false sinon.</returns>
bool RessourceManager::addMusic(const sf::String& path, const key newKey)
{
	sf::Music* newMusic = new sf::Music();

	if (!newMusic->openFromFile(path))
	{
		return false;
	}

	size_t size = musics.size();
	musics.insert(std::pair<key, sf::Music*>(newKey, newMusic));

	if (size == musics.size())
	{
		return false;
	}

}

/// <summary>
/// Ajoute un texte.
/// </summary>
/// <param name="text">La chaîne de caractère du texte.</param>
/// <param name="newKey">La clé avec laquelle ajouter le texte.
///												Ce doit être une clé qui n'est pas déjà utilisée (soit par un texte ou par un sprite.
///												Celle-ci servira à accéder au texte.</param>
/// <returns>True si l'ajout de la texture s'est faite avec succès; false sinon.</returns>
bool RessourceManager::addText(const sf::String& text, const key newKey)
{
	sf::Text* newText = new sf::Text();

	newText->setString(text);

	size_t size = drawables.size();
	drawables.insert(std::pair<key, sf::Drawable*>(newKey, newText));

	if (size == drawables.size())
	{
		return false;
	}

	return true;
}

/// <summary>
/// Ajoute un sprite.
/// </summary>
/// <param name="textureKey">Une clé de texture existante. La texture sera affectée au sprite.</param>
/// <param name="newKey">La clé avec laquelle ajouter le sprite.
///												Ce doit être une clé qui n'est pas déjà utilisée (soit par un texte ou par un sprite.
///												Celle-ci servira à accéder au sprite.</param>
/// <returns>True si l'ajout de la texture s'est faite avec succès; false sinon.</returns>
bool RessourceManager::addSprite(const key textureKey, const key newKey)
{
	sf::Texture* texture = nullptr;
	try
	{
		texture = getTexture(textureKey);
	}
	catch (std::out_of_range)
	{
		return false;
	}

	sf::Sprite* newSprite = new sf::Sprite(*texture);

	size_t size = drawables.size();
	drawables.insert(std::pair<key, sf::Drawable*>(newKey, newSprite));

	if (size == drawables.size())
	{
		return false;
	}

	return true;
}

/// <summary>
/// Accède à une texture.
/// </summary>
/// <param name="itemKey">Une clé de texture existante.</param>
/// <returns>Un pointeur sur la texture demandée si la clé existe; nullptr sinon.</returns>
sf::Texture* RessourceManager::getTexture(const key itemKey)
{
	if (textures.find(itemKey) != textures.end())
	{
		return textures.at(itemKey);
	}

	return nullptr;
}

/// <summary>
/// Accède à une musique.
/// </summary>
/// <param name="itemKey">Une clé de musique existante.</param>
/// <returns>Un pointeur sur la musique demandée si la clé existe; nullptr sinon.</returns>
sf::Music* RessourceManager::getMusic(const key itemKey)
{
	if (musics.find(itemKey) != musics.end())
	{
		return musics.at(itemKey);
	}

	return nullptr;
}

/// <summary>
/// Accède à un texte.
/// </summary>
/// <param name="itemKey">Une clé de texte existante.</param>
/// <returns>Un pointeur sur le texte demandé si la clé existe; nullptr sinon.</returns>
sf::Text* RessourceManager::getText(const key itemKey)
{
	if (drawables.find(itemKey) != drawables.end())
	{
		try
		{
			return (sf::Text*)drawables.at(itemKey);
		}
		catch (std::bad_cast)
		{
			return nullptr;
		}
	}

	return nullptr;
}

/// <summary>
/// Accède à un sprite.
/// </summary>
/// <param name="itemKey">Une clé de sprite existante.</param>
/// <returns>Un pointeur sur le sprite demandé si la clé existe; nullptr sinon.</returns>
sf::Sprite* RessourceManager::getSprite(const key itemKey)
{
	if (drawables.find(itemKey) != drawables.end())
	{
		try
		{
			return (sf::Sprite*)drawables.at(itemKey);
		}
		catch (std::bad_cast)
		{
			return nullptr;
		}
	}

	return nullptr;
}

/// <summary>
/// Accède à un sprite.
/// </summary>
/// <param name="spriteKey">Une clé de sprite existante.</param>
/// <returns>Un pointeur sur le sprite demandé si la clé existe; nullptr sinon.</returns>
sf::Sprite* RessourceManager::operator[](const key spriteKey)
{
	return getSprite(spriteKey);
}