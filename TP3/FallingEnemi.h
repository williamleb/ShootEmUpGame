#pragma once
#include "RessourceManager.h"
#include "Movable.h"
#include "Destroyable.h"
#include "Activatable.h"
#include"Player.h"
#include "Enemi.h"

using namespace sf;
namespace TP3
{
	class FallingEnemi : public Enemi
	{
	private:
		Player *joueur;
		bool isActive = true;
		const int WIDTH = 16;
		const int HEIGHT = 34;
		static const int FALLING_ENEMI_DEFAULT_SPEED = 50;
		Vector2f deplacement;
		bool top = false;
		// Mécanique de tir.
		static const int NBR_MS_BEFORE_SHOOT = 30;
		int shootTimerInMs = 0;
	public:
		FallingEnemi();
		~FallingEnemi();
		void fire();
		void init(const RessourceManager::key spriteKey, Player *player);
		void update(const float deltaT);
		void draw(RenderWindow& window);
		void activate(const sf::Vector2f& position);
		virtual void getType();
	};
}
