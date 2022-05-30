#include "Sujet.h"
#include "IObservateur.h"

using namespace TP3;

/// <summary>
/// Ajoute un observateur � l'objet.
/// </summary>
/// <param name="observateur">Le nouvel observateur.</param>
void Sujet::ajouterObservateur(IObservateur* observateur)
{
	//Si l'observateur n'est pas d�j� dans la liste...
	if (!(std::find(observateurs.begin(), observateurs.end(), observateur) != observateurs.end()))
	{
		observateurs.push_back(observateur);
	}
}

/// <summary>
/// Retire un observateur � l'objet.
/// </summary>
/// <param name="observateur">L'observateur � retirer.</param>
void Sujet::retirerObservateur(IObservateur* observateur)
{
	//Pour retirer un observateur de la liste.  Deux pointeurs qui pointent � la m�me adresse sont �gaux.
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
/// Notifie tous les observateurs qui sont abonn�s au sujet.
/// </summary>
void Sujet::notifierTousLesObservateurs()
{
	for (int i = 0; i < observateurs.size(); i++)
	{
		observateurs[i]->notifier(this);
	}
}