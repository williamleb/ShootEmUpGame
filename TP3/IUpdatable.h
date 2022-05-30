#pragma once

namespace TP3
{	
	/// <summary>
	/// Représente un objet de jeu qui peut être mis-à-jour.
	/// </summary>
	class IUpdatable
	{
	public:		
		/// <summary>
		/// Met à jour l'objet.
		/// </summary>
		/// <param name="deltaT">Le temps en secondes depuis le dernier appel d'update.</param>
		virtual void update(const float deltaT) = 0;
	};
}