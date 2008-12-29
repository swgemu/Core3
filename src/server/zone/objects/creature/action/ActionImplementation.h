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

#ifndef ACTIONIMPLEMENTATION_H_
#define ACTIONIMPLEMENTATION_H_

#include "system/lang.h"

#include "ActionCreature.h"
#include "ActionCreatureImplementation.h"

#include "../../player/Player.h"

class ActionImplementation : public ActionServant {
	
	SceneObject* parentObject;
	VectorMap<uint32, String> conversationList; //Option Responses
	
	int actionMask;
	int preRequisites;
	
	//Do-The-Action Vars:
	
	//Move Coordinates: <use coordinate class>
	
	//Patrol: <see patrol funcs in CreatureImpl>
	
	//Converse:
		//Option Responses. <screenID, screenStr> 
	    //String Syntax: "Left Box Text~Option1Text|O2|O3"
		VectorMap<String, String> convoScreens;
		//Conversation Option Links. <"screenID,OptionNumber","nextScreenID,actionKey(if applicable)">
		VectorMap<String, String> convoOptLink;
	
	//Say:
		String sayText; //Say text
		
	//Give Item:
		
	//Give Mission:
		String giveMissionKey;
	
public:
	const static int TYPE_MOVE = 1;
	const static int TYPE_PATROL = 2;
	const static int TYPE_CONVERSE = 4;
	const static int TYPE_SAY = 8;
	const static int TYPE_GIVEITEM = 16;
	const static int TYPE_TAKEITEM = 32;
	const static int TYPE_GIVEMISSION = 64;
	const static int TYPE_COMPMISSION = 128;
	const static int TYPE_FAILMISSION = 256;

/*public:
	const static int PREREQ_HASMISSION = 1;
	*/
	
public:
	ActionImplementation(SceneObject* po, int actMask, int tpr);
	~ActionImplementation();
	
	void setPrereq(int tpr) {
		preRequisites = 0;
		preRequisites |= tpr;
	}
	
	void setActionMask(int tat) {
		actionMask |= tat;
	}
	
	void execAction(Player* player);
	
	void addConvoScreen(String screenID, String leftBoxText, int numOptions, String Options, String optLinks);
	
private:
	void carryConversation(Player* player);
	void sendConvoScreen(Player* player, String& screenID);
	bool prereqCheck(Player* player);
};

#endif /*ACTIONIMPLEMENTATION_H_*/
