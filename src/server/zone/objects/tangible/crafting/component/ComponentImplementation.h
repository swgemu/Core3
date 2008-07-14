/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/
 
#ifndef COMPONENTIMPLEMENTATION_H_
#define COMPONENTIMPLEMENTATION_H_
 
#include "../../../../packets.h"
#include "Component.h"
 
class CreatureObject;
class SceneObject;
class Player;
 
class ComponentImplementation : public ComponentServant {
protected:


public:
	static const int CLOTHING = 1; // Clothing and Armor Crafting Tool
	static const int FOOD = 2; // Food and Chemical Crafting Tool
	static const int GENERIC = 3; // Generic Crafting Tool
	static const int JEDI = 4; // Lightsaber Crafting Tool
	static const int SPACE = 5; // Starship Crafting Tool
	static const int STRUCTURE = 6; // Structure and Furniture Crafting Tool
	static const int WEAPON = 7; // Weapon Droid and General Item Crafting Tool
 
public:
	ComponentImplementation(uint64 object_id, uint32 tempCRC, const unicode& n, const string& tempn);
	ComponentImplementation(CreatureObject* creature, uint32 tempCRC, const unicode& n, const string& tempn);
	
	~ComponentImplementation();
 
	void init();

	void generateAttributes(SceneObject* player);
 
	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);
	
	int useObject(Player* player);
	
	void sendTo(Player* player, bool doClose);
	
	Component* cloneComponent(Component* oldComp, uint64 oid);
	
};
 
#endif /*COMPONENTIMPLEMENTATION_H_*/
