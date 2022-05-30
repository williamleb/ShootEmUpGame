#include "Inputs.h"

using namespace TP3;

/// <summary>
/// D�truit un <see cref="Inputs"/>.
/// </summary>
Inputs::~Inputs()
{
	deque<PlayerCommand_Base*>::size_type size = commands.size();
	for (deque<PlayerCommand_Base*>::size_type i = 0; i < size; i++)
	{
		delete commands[i];
	}
}

/// <summary>
/// Acc�de aux commandes.
/// </summary>
/// <returns>La liste de commandes.</returns>
const TP3_structures::deque<PlayerCommand_Base*>& Inputs::getCommands() const
{
	return commands;
}

/// <summary>
/// Ajoute une nouvelle commande � la fin de la liste.
/// </summary>
/// <param name="command">La commande � ajouter.</param>
void Inputs::storeCommand(PlayerCommand_Base* command)
{
	commands.push_back(command);
}

/// <summary>
/// Ajoute une nouvelle commande � la fin de la liste et l'ex�cute.
/// </summary>
/// <param name="command">La commande � ajouter et � ex�cuter.</param>
/// <param name="player">Le joueur avec lequel ex�cuter la commande.</param>
void Inputs::storeAndExecute(PlayerCommand_Base* command, UserControlled* player)
{
	storeCommand(command);
	command->execute(player);
}

/// <summary>
/// Retire la premi�re commande de la liste.
/// </summary>
void Inputs::removeCommand()
{
	delete commands.front();
	commands.pop_front();
}