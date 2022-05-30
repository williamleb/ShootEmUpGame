#pragma once
#include "FollowedCommands.h"
#include "Structures\deque.h"

namespace TP3
{	
	/// <summary>
	/// Repr�sente l'invocateur pour un objet de type FollowEntity 
	/// (qui repr�sentent une file d'ennemis qui se suivent de fa�on d�cal�e).
	/// </summary>
	class FollowedInputs
	{
		TP3_structures::deque<FollowedCommand_Base*> commands;

	public:
		~FollowedInputs();

		const TP3_structures::deque<FollowedCommand_Base*>& getCommands() const;

		void storeCommand(FollowedCommand_Base* command);
		void storeAndExecute(FollowedCommand_Base* command, FollowEntity* player);
		void removeCommand();
	};
}