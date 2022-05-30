/* Fichier tié du code exemple fourni en classe */
#pragma once

namespace TP3
{
	class Sujet;
	
	/// <summary>
	/// Représente un objet qui peut s'abonner à un sujet.
	/// </summary>
	class IObservateur
	{
	public:		
		/// <summary>
		/// Notifie l'objet qu'un événement s'est produit.
		/// </summary>
		/// <param name="sujet">Le sujet qui a appelé l'événement.</param>
		virtual void notifier(Sujet* sujet) = 0;
	};

}