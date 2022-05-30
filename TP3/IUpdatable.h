#pragma once

namespace TP3
{	
	/// <summary>
	/// Repr�sente un objet de jeu qui peut �tre mis-�-jour.
	/// </summary>
	class IUpdatable
	{
	public:		
		/// <summary>
		/// Met � jour l'objet.
		/// </summary>
		/// <param name="deltaT">Le temps en secondes depuis le dernier appel d'update.</param>
		virtual void update(const float deltaT) = 0;
	};
}