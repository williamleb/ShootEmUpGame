#pragma once
#include <climits>

namespace TP3
{	
	/// <summary>
	/// Un destroyable est un objet qui possède des points de vie dans le jeu.
	/// </summary>
	class Destroyable
	{
		const unsigned int maxLife;

		unsigned int lifePts;

	public:		
		Destroyable(const unsigned int life = 0, const unsigned int maxLife = UINT_MAX);

		bool isDestroyed();

		virtual void damage(const unsigned int life);
		virtual void heal(const unsigned int life);

		int getLife() const;

		void resetLife(const unsigned int life);
	};
}