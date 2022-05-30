#pragma once
#include <SFML/Graphics.hpp>

/*
* File:   BitmaskManager.h
* Author: Nick (original version), ahnonay (SFML2 compatibility)
* https://github.com/SonarSystems/SFML-Box2D-Tutorials/tree/master/SFML/Tutorial%20013%20-%20Pixel%20Perfect%20Collision%20Detection
*/

class BitmaskManager
{
public:
	~BitmaskManager() 
	{
		std::map<const sf::Texture*, unsigned char*>::const_iterator end = bitmasks.end();
		for (std::map<const sf::Texture*, unsigned char*>::const_iterator iter = bitmasks.begin(); iter != end; iter++)
			delete[] iter->second;
	}

	unsigned char getPixel(const unsigned char* mask, const sf::Texture* tex, unsigned int x, unsigned int y) 
	{
		if (x>tex->getSize().x || y>tex->getSize().y)
			return 0;

		return mask[x + y*tex->getSize().x];
	}

	unsigned char* getMask(const sf::Texture* tex) 
	{
		unsigned char* mask;
		std::map<const sf::Texture*, unsigned char*>::iterator pair = bitmasks.find(tex);

		if (pair == bitmasks.end())
		{
			sf::Image img = tex->copyToImage();
			mask = createMask(tex, img);
		}
		else
			mask = pair->second;

		return mask;
	}

	unsigned char* createMask(const sf::Texture* tex, const sf::Image& img) 
	{
		unsigned char* mask = new unsigned char[tex->getSize().y*tex->getSize().x];

		for (unsigned int y = 0; y<tex->getSize().y; y++)
		{
			for (unsigned int x = 0; x<tex->getSize().x; x++)
				mask[x + y*tex->getSize().x] = img.getPixel(x, y).a;
		}

		bitmasks.insert(std::pair<const sf::Texture*, unsigned char*>(tex, mask));

		return mask;
	}

private:
	std::map<const sf::Texture*, unsigned char*> bitmasks;
};
