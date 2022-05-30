#include "UserControlled.h"

using namespace TP3;

TP3_structures::stack<UserControlled*> UserControlled::allUserControlled;

/// <summary>
/// Cr�e un nouveau <see cref="UserControlled"/>.
/// </summary>
UserControlled::UserControlled(const GameObject::ObjectType type)
	:Movable(type),
	positionAmongUserControlled(0)
{
}

UserControlled::~UserControlled()
{
}

/// <summary>
/// Retourne le dernier joueur ajout�.
/// </summary>
/// <returns>Le dernier joueur ajout�.</returns>
const UserControlled* UserControlled::getLastUserControlled()
{
	return allUserControlled.top();
}

/// <summary>
/// Ajoute un nouvel objet joueur � la liste des joueurs.
/// </summary>
/// <param name="newUserControlled">Le nouvel objet joueur.</param>
void UserControlled::addUserControlled(UserControlled* newUserControlled)
{
	newUserControlled->positionAmongUserControlled = allUserControlled.size();
	allUserControlled.push(newUserControlled);
}

/// <summary>
/// Enl�ve le dernier objet joueur de la liste des joueurs.
/// </summary>
void UserControlled::removeLastUserControlled()
{
	allUserControlled.pop();
}

/// <summary>
/// D�termine si l'objet le dernier objet apparu de la liste des objets contr�l�s par le joueur.
/// </summary>
/// <returns> <c>true</c> si l'objet est le dernier apparu; <c>false</c> sinon. </returns>
bool UserControlled::isLast() const
{
	return positionAmongUserControlled == allUserControlled.size() - 1;
}

/// <summary>
/// Retourne la position d'apparition de l'objet contr�l� par le joueur.
/// </summary>
/// <returns>La position d'apparition de l'objet contr�l� par le joueur.</returns>
unsigned int UserControlled::getPositionAmongUserControlled() const
{
	return positionAmongUserControlled;
}