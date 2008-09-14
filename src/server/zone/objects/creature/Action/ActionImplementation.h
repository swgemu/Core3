#ifndef ACTIONIMPLEMENTATION_H_
#define ACTIONIMPLEMENTATION_H_

#include "system/lang.h"

#include "ActionCreature.h"
#include "ActionCreatureImplementation.h"

#include "../../player/Player.h"

class ActionImplementation : public ActionServant {
	
	SceneObject* parentObject;
	VectorMap<uint32, string> conversationList; //Option Responses
	
	int actionMask;
	int preRequisites;
	
	//Do-The-Action Vars:
	
	//Move Coordinates: <use coordinate class>
	
	//Patrol: <see patrol funcs in CreatureImpl>
	
	//Converse:
		//Option Responses. <screenID, screenStr> 
	    //String Syntax: "Left Box Text~Option1Text|O2|O3"
		VectorMap<string, string> convoScreens;
		//Conversation Option Links. <"screenID,OptionNumber","nextScreenID,actionKey(if applicable)">
		VectorMap<string, string> convoOptLink;
	
	//Say:
		string sayText; //Say text
		
	//Give Item:
		
	//Give Mission:
		string giveMissionKey;
	
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
	
	void addConvoScreen(string screenID, string leftBoxText, int numOptions, string Options, string optLinks);
	
private:
	void carryConversation(Player* player);
	void sendConvoScreen(Player* player, string& screenID);
	bool prereqCheck(Player* player);
};

#endif /*ACTIONIMPLEMENTATION_H_*/
