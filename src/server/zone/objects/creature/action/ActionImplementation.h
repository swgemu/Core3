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

#include "events/ActionDelayExecutionEvent.h"

class ActionImplementation : public ActionServant {

	String actionKey;

	SceneObject* parentObject;
	ActionCreature* parentCreature;

	int execCount; //Number of times the action has been executed

	//Startup Variables:
	float delayTime;

	////////////////////////////
	//Prerequisite:
	////////////////////////////

	bool hasActionParent;
	bool hasLairParent;

	int preRequisites;

	//prereq:HASMISSION:
		String hasMisoKey;

	//prereq:killcountlimit
		//NPC says: "Come back to me when you have reached ___ kills".
		//Npc conversation will call this action as a prereq for mission complete
		//Reminder of format for kill_count_vars in db: "killedCrc=numStr" "23252=2"
		//THIS PRAM IS SET ONLY FOR THE CONVO NPCS THAT GIVE THE MISSION AWARD
		String killCountLimitList;

	////////////////////////////
	//Action:
	////////////////////////////

	int actionMask;

	//Action:Move: <use coordinate class>

	//Action:patrol: <see patrol funcs in CreatureImpl>

	//Action:Converse:
		VectorMap<uint32, String> conversationList; //Option Responses
		//Option Responses. <screenID, screenStr>
	    //String Syntax: "Left Box Text~Option1Text|O2|O3"
		VectorMap<String, String> convoScreens;
		//Conversation Option Links. <"screenID,OptionNumber","nextScreenID,actionKey(if applicable)">
		VectorMap<String, String> convoOptLink;

	//Action:Say:
		String sayText; //Say text

	//Action:giveItem:
		TangibleObject* giveItemObj;

	//Action:takeItem:
		uint32 takeItemCrc;
		String takeItemName;
		bool takeItemUseParentMiso;
		String takeItemWithMisoKey;

	//Action:giveMission:
		String giveMissionKey;

	//Action:addKill
		//ALL WE HAVE TO DO HERE IS UPDATE THE DBVAR IN PLAYERIMPL

public:
	//Action mask types, if modified, change in registerGlobals and header for mission manager
	const static int TYPE_MOVE = 1;
	const static int TYPE_PATROL = 2;
	const static int TYPE_CONVERSE = 4;
	const static int TYPE_SAY = 8;
	const static int TYPE_GIVEITEM = 16;
	const static int TYPE_TAKEITEM = 32;
	const static int TYPE_GIVEMISSION = 64;
	const static int TYPE_COMPMISSION = 128;
	const static int TYPE_FAILMISSION = 256;
	const static int TYPE_ADDKILL = 512;

	//Action Prereq mask:
	const static int MEET_HASMISSION = 1;
	const static int MEET_KILLCOUNTLIMIT = 2;

public:
	ActionImplementation(SceneObject* po, String tky, int actMask, int tpr);
	~ActionImplementation();

	inline void setActionKey(String& tky) {
		actionKey = tky;
	}

	String& getActionKey() {
		return actionKey;
	}

	////////////////////////////
	//Prerequisite:
	////////////////////////////

	inline void setPrereq(int tpr) {
		preRequisites |= tpr;
	}

	//prereq:hasMission:
	inline void setMeetHasMission(String& tstr) {
		hasMisoKey = tstr;
	}

	//prereq:killCountLimitList
	inline void setMeetKillLimitList(String& tlist) {
		killCountLimitList = tlist;
	}


	////////////////////////////
	//Action:
	////////////////////////////

	inline void setActionMask(int tat) {
		actionMask |= tat;
	}

	void execAction(Player* player);

	//Action:Conversation:
	void addConvoScreen(String screenID, String leftBoxText, int numOptions, String Options, String optLinks);

	//Action:giveItem:
	void setGiveItem(TangibleObject* tempTano);

	//Action:takeItem:
	void setTakeItem(uint32 crc, String itemname, bool useParentMisoKey, String withMisoKey);

private:

	////////////////////////////
	//Action:
	////////////////////////////

	//Action:Conversation
	void carryConversation(Player* player);
	void sendConvoScreen(Player* player, String& screenID);

	////////////////////////////
	//Prerequisite:
	////////////////////////////

	void verifyParent();

	bool prereqCheck(Player* player);
};

#endif /*ACTIONIMPLEMENTATION_H_*/
