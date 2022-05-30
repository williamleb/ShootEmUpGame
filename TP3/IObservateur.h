/* Fichier ti� du code exemple fourni en classe */
#pragma once

namespace TP3
{
	class Sujet;
	
	/// <summary>
	/// Repr�sente un objet qui peut s'abonner � un sujet.
	/// </summary>
	class IObservateur
	{
	public:		
		/// <summary>
		/// Notifie l'objet qu'un �v�nement s'est produit.
		/// </summary>
		/// <param name="sujet">Le sujet qui a appel� l'�v�nement.</param>
		virtual void notifier(Sujet* sujet) = 0;
	};

}