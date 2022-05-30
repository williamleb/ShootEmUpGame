#include "Sujet.h"
#include "IObservateur.h"

using namespace TP3;

/// <summary>
/// Ajoute un observateur à l'objet.
/// </summary>
/// <param name="observateur">Le nouvel observateur.</param>
void Sujet::ajouterObservateur(IObservateur* observateur)
{
	//Si l'observateur n'est pas déjà dans la liste...
	if (!(std::find(observateurs.begin(), observateurs.end(), observateur) != observateurs.end()))
	{
		observateurs.push_back(observateur);
	}
}

/// <summary>
/// Retire un observateur à l'objet.
/// </summary>
/// <param name="observateur">L'observateur à retirer.</param>
void Sujet::retirerObservateur(IObservateur* observateur)
{
	//Pour retirer un observateur de la liste.  Deux pointeurs qui pointent à la même adresse sont égaux.
	for (int i = 0; i < observateurs.size(); i++)
	{
		if (observateurs[i] == observateur)
		{
			observateurs.erase(observateurs.begin() + i);
			return;
		}
	}
}

/// <summary>
/// Notifie tous les observateurs qui sont abonnés au sujet.
/// </summary>
void Sujet::notifierTousLesObservateurs()
{
	for (int i = 0; i < observateurs.size(); i++)
	{
		observateurs[i]->notifier(this);
	}
}