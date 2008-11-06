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

#ifndef ACTIONCREATUREIMPLEMENTATION_H_
#define ACTIONCREATUREIMPLEMENTATION_H_

class MissionManagerImplementation;

class Player;
class SceneObject;

#include "engine/engine.h"

#include "ActionCreature.h"
#include "Action.h"

class ActionCreatureImplementation : public ActionCreatureServant {
	
	VectorMap<string, Action*> actionList; //<action key, action>
	
	string misoKey; //Mission Key
	MissionManagerImplementation* misoMgr;
	
	//Trigger Action Keys:
	string converseKeys;
	string tradeKeys;
	string attackKeys;
	string deathKeys;
	
public:
	ActionCreatureImplementation(uint64 oid, uint32 objCrc, string& creName, string& stf, string& missionKey);
	~ActionCreatureImplementation();
	
	//Action List Manip
	void addAction(string& key, Action* act) {
		actionList.put(key, act);
	}
	
	Action* getAction(string& key) {
		return actionList.get(key);
	}
	
	//Triggers: If an action key is passed, the action will be called when the trigger is pulled
	void onConverse(string tco, Player* player = NULL);
	void onTrade(string ttr);
	void onAttack(string tat);
	void onDeath(string tde);
	
	//Mission Specific:
	bool isMissionNpc(); //Returns true if NPC has a mission assigned to it.
	
	string& getMissionKey() {
		return misoKey;
	}
	
	//Mission Manager:
	inline MissionManagerImplementation* getMisoMgr() {
		return misoMgr;
	}
	
	inline void setMisoMgr(MissionManagerImplementation* tmgr) {
		misoMgr = tmgr;
	}
	
	//Conversation Specific:
	void sendConversationStartTo(SceneObject* obj);
	void selectConversationOption(int option, SceneObject* obj);
	
private:
	
	//Action List Manip
	void dropAction(string& key) {
		actionList.drop(key);
	}
	
	void clearActions() {
		actionList.removeAll();
	}
	
	friend class MissionManagerImplementation;

};

#endif /*ACTIONCREATUREIMPLEMENTATION_H_*/
