#pragma once
#include "PlayerCommands.h"
#include "Structures\deque.h"

namespace TP3
{
	/// <summary>
	/// Représente l'invocateur pour un objet de type UserControlled 
	/// (utilisée par les options pour reproduire les mouvements du joueur).
	/// </summary>
	class Inputs
	{
		TP3_structures::deque<PlayerCommand_Base*> commands;

	public:		
		~Inputs();

		const TP3_structures::deque<PlayerCommand_Base*>& getCommands() const;

		void storeCommand(PlayerCommand_Base* command);
		void storeAndExecute(PlayerCommand_Base* command, UserControlled* player);
		void removeCommand();
	};
}