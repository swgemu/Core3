#ifndef ACTIONCREATUREIMPLEMENTATION_H_
#define ACTIONCREATUREIMPLEMENTATION_H_

class Player;
class SceneObject;

#include "ActionCreature.h"
#include "Action.h"

class ActionCreatureImplementation : public ActionCreatureServant {
	
	VectorMap<string, Action*> actionList; //<action key, action>
	
	string misoKey; //Mission Key
	MissionManager* misoMgr;
	
	//Trigger Action Keys:
	string converseKeys;
	string tradeKeys;
	string attackKeys;
	string deathKeys;
	
public:
	ActionCreatureImplementation(uint64 oid, uint32 objCrc, string& creName, string& stf, 
			string& missionKey, MissionManager* mMgr = NULL);
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
	
	MissionManager* getMisoMgr();
	
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

};

#endif /*ACTIONCREATUREIMPLEMENTATION_H_*/
