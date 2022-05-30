#pragma once

#include <vector>

namespace TP3
{
	class IObservateur;

	using std::vector;
	
	/// <summary>
	/// Représente un objet de jeu sur lequel des observateur peuvent
	/// s'abonner.
	/// </summary>
	class Sujet
	{
	public:
		void ajouterObservateur(IObservateur* observateur);
		void retirerObservateur(IObservateur* observateur);
		virtual void notifierTousLesObservateurs();

	protected:
		vector<IObservateur*> observateurs;
	};
}