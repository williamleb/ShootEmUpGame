#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

namespace TP3
{
	/// <summary>
	/// Un wrapper autour de structures de données contenant des ressources SFML.
	/// Son utilité est d'aider à gérer les différentes ressources d'une scène.
	/// L'administrateur de ressource est un singleton.
	/// </summary>
	/// <seealso cref="map" />
	class RessourceManager
	{
	public:
		using key = unsigned int;

	private:
		std::map<key, sf::Drawable*> drawables;
		std::map<key, sf::Texture*> textures;
		std::map<key, sf::Music*> musics;

		RessourceManager();
		RessourceManager(const RessourceManager&) = delete;
		RessourceManager& operator=(const RessourceManager&) = delete;

		static RessourceManager* instance;
	public:

		~RessourceManager();
		void clear();

		static RessourceManager* getInstance();
		static void deleteInstance();

		bool addTexture(const sf::String& path, const key newKey);
		bool addMusic(const sf::String& path, const key newKey);
		bool addText(const sf::String& text, const key newKey);
		bool addSprite(const key textureKey, const key newKey);

		sf::Texture* getTexture(const key itemKey);
		sf::Music* getMusic(const key itemKey);
		sf::Text* getText(const key itemKey);
		sf::Sprite* getSprite(const key itemKey);
		sf::Sprite* operator[](const key);
	};
}