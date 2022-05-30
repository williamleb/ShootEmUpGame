#include "FollowedInputs.h"
#include <iostream>

using namespace TP3;

/// <summary>
/// Détruit un <see cref="FollowedInputs"/>.
/// </summary>
FollowedInputs::~FollowedInputs()
{
	deque<FollowedCommand_Base*>::size_type size = commands.size();
	for (deque<FollowedCommand_Base*>::size_type i = 0; i < size; i++)
	{
		delete commands[i];
	}
}

/// <summary>
/// Accède aux commandes.
/// </summary>
/// <returns>La liste de commandes.</returns>
const TP3_structures::deque<FollowedCommand_Base*>& FollowedInputs::getCommands() const
{
	return commands;
}

/// <summary>
/// Ajoute une nouvelle commande à la fin de la liste.
/// </summary>
/// <param name="command">La commande à ajouter.</param>
void FollowedInputs::storeCommand(FollowedCommand_Base* command)
{
	commands.push_back(command);
}

/// <summary>
/// Ajoute une nouvelle commande à la fin de la liste et l'exécute.
/// </summary>
/// <param name="command">La commande à ajouter et à exécuter.</param>
/// <param name="entity">L'ennemi avec lequel exécuter la commande.</param>
void FollowedInputs::storeAndExecute(FollowedCommand_Base* command, FollowEntity* entity)
{
	storeCommand(command);
	command->execute(entity);
}

/// <summary>
/// Retire la première commande de la liste.
/// </summary>
void FollowedInputs::removeCommand()
{
	delete commands.front();
	commands.pop_front();
}