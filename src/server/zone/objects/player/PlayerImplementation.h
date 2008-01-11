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

#ifndef PLAYERIMPLEMENTATION_H_
#define PLAYERIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../../db/ServerDatabase.h"

#include "PlayerObject.h"

#include "../../managers/player/SkillBoxMap.h"
#include "professions/XpMap.h"

#include "badges/Badges.h"
#include "../terrain/RegionNames.h"

class PlayerManager;
class ItemManager;
class ProfessionManager;

class ZoneClient;

class CommandQueueAction;
class CommandQueueActionEvent;
class PlayerRecoveryEvent;
class CenterOfBeingEvent;

class Datapad;

class WaypointObject;
class Guild;
class Certification;

#include "../../../chat/room/ChatRoom.h"

#include "Player.h"

class PlayerImplementation : public PlayerServant {
	ZoneClient*	owner;
	
	int onlineStatus;
	Time logoutTimeStamp;
	
	uint64 characterID;
	uint64 baseID;

	string firstName;

	string raceFile; //race iff, defines the race file of the character being created.

	string startingLocation; //start location iff string
	string startingProfession; //starting profession string

	unicode biography; //char biography
	
	// player objects
	PlayerObject* playerObject;
	Datapad* datapad;

	Vector<CommandQueueAction*> commandQueue;
	Time nextAction;

	Event* disconnectEvent;
	Event* logoutEvent;

	PlayerRecoveryEvent* recoveryEvent;
	Event* changeFactionEvent;

	int itemShift;
	
	int deathCount;
	int pvpRating;
	
	// Faction Stuff
	string factionRank;
	uint32 rebelPoints;
	uint32 imperialPoints;
	
	// Profession stuff
	SkillBoxMap skillBoxes;
	SortedVector<SkillBox*> skillBoxesToSave;
	VectorMap<string, Certification*> certificationList;

	int skillPoints;
	
	// misc
	SortedVector<Player*> duelList;
	CreatureObject* conversatingCreature;
	SortedVector<ChatRoom*> chatRooms;
	
	Badges badges;

	float clonePositionX;
	float clonePositionY;
	
	int regionId;
	
	bool guildLeader;
	
	int adminLevel;
	
	bool centered;
	int centeredBonus;
	CenterOfBeingEvent* centerOfBeingEvent;
	
	float lastTestPositionX;
	float lastTestPositionY;
	
	// trading
	uint64 tradeRequestedPlayer;
	Vector<TangibleObject*> tradeItems;
	uint32 moneyToTrade;
	bool acceptedTrade;
	bool verifiedTrade;
	
	// samplig, surveying
	Event* surveyEvent;
	
	Event* sampleEvent;
	Event* firstSampleEvent;
	
	WaypointObject* surveyWaypoint;
	
	SurveyTool* surveyTool;
	
	bool cancelSample;
	
	bool surveyErrorMessage;
	bool sampleErrorMessage;
	
public:
	static const int ONLINE = 1;
	static const int OFFLINE = 2;
	static const int LINKDEAD = 3;
	static const int LOGGINGIN = 4;
	static const int LOGGINGOUT = 5;
	
	static const int CSR = 1;
	static const int DEVELOPER = 2;
	static const int ADMIN = 3;
	
	
public:
	PlayerImplementation();
	PlayerImplementation(uint64 cid);	

	virtual ~PlayerImplementation();

	void init();

	Player* create(ZoneClient* client);
	
	void load(ZoneClient* client);
	void reload(ZoneClient* client);

	void unload();

	void logout(bool doLock = true);
	void userLogout(int msgCounter = 3);
	
	void disconnect(bool closeClient = true, bool doLock = true);

	void clearLogoutEvent() {
		logoutEvent = NULL;
	}

	void createItems();
	void loadItems();
	
	void createBaseStats();
	
	void decayInventory();
	
	void sendToOwner();
	void sendPersonalContainers();
	void sendTo(Player* player, bool doClose = true);

	// spatial methods
	void insertToZone(Zone* zone);
	void reinsertToZone(Zone* zone);

	void updateZone();
	void lightUpdateZone();
	
	void updateZoneWithParent(uint64 Parent);
	void lightUpdateZoneWithParent(uint64 Parent);
	
	void updatePlayerPosition(bool doLightUpdate = false);
	void updateMountPosition();
	
	void removeFromZone(bool doLock = true);
	
	void notifyInsert(QuadTreeEntry* obj);
	void notifyDissapear(QuadTreeEntry* obj);

	void switchMap(int planetid);

	void doWarp(float x, float y, float z = 0, float randomizeDistance = 0);
	
	void bounceBack();

	void notifySceneReady();
	
	void sendSystemMessage(const string& message);
	void sendSystemMessage(const string& file, const string& str, uint64 targetid = 0);
	void sendSystemMessage(unicode& message);
	
	//item methods
	void addDatapadItem(SceneObject* item);
	SceneObject* getDatapadItem(uint64 oid);
	void removeDatapadItem(uint64 oid);

	// trade mehtods
	void addTradeItem(TangibleObject* item) {
		for (int i = 0; i < tradeItems.size(); ++i) {
			if (tradeItems.get(i) == item)
				return;
		}
		
		tradeItems.add(item);
		acceptedTrade = verifiedTrade = false;
	}
	
	void clearTradeItems() {
		tradeItems.removeAll();
		acceptedTrade = verifiedTrade = false;
	}
	
	int getTradeSize() {
		return tradeItems.size();
	}
	
	TangibleObject* getTradeItem(int idx) {
		return tradeItems.get(idx);
	}
	
	void setMoneyToTrade(uint32 value) {
		moneyToTrade = value;
		acceptedTrade = verifiedTrade = false;
	}
	
	uint32 getMoneyToTrade() {
		return moneyToTrade;
	}
	
	void setAcceptedTrade(bool val) {
		acceptedTrade = val;
	}
	
	bool hasAcceptedTrade() {
		return acceptedTrade;
	}
	
	void setVerifiedTrade(bool val) {
		verifiedTrade = val;
	}

	bool hasVerifiedTrade() {
		return verifiedTrade;
	}

	// combat methods
	void queueAction(Player* player, uint64 target, uint32 actionCRC, uint32 actionCntr);
	bool doAction(CommandQueueAction* action);

	void clearQueueAction(uint32 actioncntr, float timer = 0.0, uint32 tab1 = 0, uint32 tab2 = 0);
	void deleteQueueAction(uint32 actioncntr);

	void doIncapacitate();
	void changePosture(int post);

	void activateQueueAction(CommandQueueAction* action = NULL);

	void activateRecovery();
	
	void rescheduleRecovery(int time = 3000);
	
	void doRecovery();
	void doStateRecovery();

	void doClone();	
	
	void doCenterOfBeing();
	void removeCenterOfBeing();
	
	void doPeace();

	void lootCorpse();
	
	void kill();


	// buffing methods
	void addBuff(uint32 buffcrc, float time);
	
	void clearBuffs(bool doUpdatePlayer = true);

	// jedi methods
	void calculateForceRegen();

	bool changeForceBar(int32 fp);

	inline bool isJedi() {
		return playerObject->isJedi();
	}
	
	void setForceBar(uint32 fp) {
		playerObject->setForcePower(fp, true);
	}
	
	// faction methods
	void setOvert();
	void setCovert();
	
	void newChangeFactionEvent(uint32 faction);
	
	bool isInDuelWith(Player* targetPlayer, bool doLock = true);
	
	// item methods
	void changeCloth(uint64 itemid);
	void changeWeapon(uint64 itemid);
	
	void setWeaponSkillMods(Weapon* weapon);
	
	void setFactionRank(string fac) {
		factionRank = fac;
	}
	
	// Profession Methods
	void saveProfessions();
	void loadProfessions();
	
	bool trainSkillBox(const string& name);
	void surrenderSkillBox(const string& name);
	
	void resetSkillBoxesIterator() {
		skillBoxes.resetIterator();
	}
	
	int getSkillBoxesSize() {
		return skillBoxes.size();
	}
	
	string& getNextSkillBox() {
		return skillBoxes.getNextValue()->getName();
	}
	
	bool hasNextSkillBox() {
		return skillBoxes.hasNext();
	}

	//PVP Rating stuff.
	void increasePvpRating(int value);
	void decreasePvpRating(int value);

	// duellist manipulation methods	
	void addToDuelList(Player* targetPlayer);

	void removeFromDuelList(Player* targetPlayer);
	
	Player* getDuelListObject(int index) {
		return duelList.get(index);
	}
	
	bool requestedDuelTo(Player* targetPlayer) {
		return duelList.contains(targetPlayer);
	}
	
	bool isDuelListEmpty() {
		return duelList.isEmpty();
	}
	
	int getDuelListSize() {
		return duelList.size();
	}
	
	void clearDuelList();
	
	//Certs
	int getCertificationListSize() {
		return certificationList.size();
	}
	
	string& getCertification(int idx) {
		return certificationList.get(idx)->getName();
	}
	
	// badge methods
	void toggleCharacterBit(uint32 bit);
	
	void addBadgeBitmask(uint32 bitmask);
	
	bool awardBadge(uint32 badgeindex);
	
	// guild methods
	bool setGuild(uint32 gid);
	void setGuild(Guild* gild) {
		guild = gild;
	}

	bool updateGuild(uint32 gid);
	void updateGuild(Guild* guild);
	
	void addChatRoom(ChatRoom* room) {
		chatRooms.put(room);
	}
	
	void removeChatRoom(ChatRoom* room) {
		chatRooms.drop(room);
	}
	
	// skill methods
	void addSkillPoints(int sPoints) {
		skillPoints += sPoints;
	}
	
	void removeSkillPoints(int sPoints) {
		skillPoints -= sPoints;
	}
	
	void addXp(const string& xpType, int xp, bool updateClient) {
		playerObject->addExperience(xpType, xp, updateClient);
	}
	void removeXp(const string& xpType, int xp, bool updateClient) {
		playerObject->removeExperience(xpType, xp, updateClient);
	}
	
	void addSkillBox(SkillBox* skillBox, bool updateClient = false);
	void removeSkillBox(SkillBox* skillBox, bool updateClient = false);
	void addCertifications(Vector<Certification*>& certs, bool updateClient = false);
	void removeCertifications(Vector<Certification*>& certs, bool updateClient = false);

	// waypoint methods
	void addWaypoint(WaypointObject* wp) {
		playerObject->addWaypoint(wp, true);
	}
	
	void removeWaypoint(WaypointObject* wp) {
		playerObject->removeWaypoint(wp, true);
	}
	
	WaypointObject* getWaypoint(uint64 id) {
		return playerObject->getWaypoint(id);
	}

	void launchFirework();

	// packet methods
	void sendMessage(Message* msg);
	void sendMessage(StandaloneMessage* msg);

	// setters
	void setOnline();

	void setOffline() {
		onlineStatus = OFFLINE;
	}

	void setLinkDead();
	
	void setLoggingIn() {
		onlineStatus = LOGGINGIN;
	}

	void setLoggingOut() {
		onlineStatus = LOGGINGOUT;
	}

	void clearDisconnectEvent() {
		disconnectEvent = NULL;
	}

	void setClient(ZoneClient* client) {
		owner = client;
	}
	
	inline void setStartingLocation(string& loc) {
		startingLocation = loc;
	}

	inline void setRaceFileName(string& name) {
		raceFile = name;
	}

	inline void setHairObject(const string& hair) {
		hairObject = hair;
	}
	
	inline void setHairData(string& hair) {
		hairData = hair;
	}

	inline void setStartingProfession(const string& prof) {
		startingProfession = prof;
	}

	inline void setBiography(unicode& bio) {
		biography = bio;
	}
	
	inline void setBiography(const string& bio) {
		biography = bio;
	}
	
	inline void setConversatingCreature(CreatureObject*  conversator) {
		conversatingCreature = conversator;
	}
	
	inline void setFirstName(const string& name) {
		firstName = name;
	}
	
	inline void setCharacterID(uint64 id) {
		characterID = id;
		baseID = id << 32;
		objectID = baseID + 0x15;
	}
	
	inline void setItemShift(uint32 shift) {
		itemShift = shift;		
	}
	
	inline void setLastTestPositionX(float pos) {
		lastTestPositionX = pos;
	}
	
	inline void setLastTestPositionY(float pos) {
		lastTestPositionY = pos;
	}
	
	inline void setTradeRequestedPlayer(uint64 id) {
		tradeRequestedPlayer = id;
	}

	// getters
	inline string& getHairData() {
		return hairData;
	}

	inline GroupObject* getGroupObject() {
		return group;
	}
	
	inline bool isOnline() {
		return onlineStatus != OFFLINE && onlineStatus != LINKDEAD;
	}

	inline bool isOffline() {
		return onlineStatus == OFFLINE;
	}

	inline bool isLinkDead() {
		return onlineStatus == LINKDEAD;
	}

	inline bool isLoggingIn() {
		return onlineStatus == LOGGINGIN;
	}

	inline bool isLoggingOut() {
		return onlineStatus == LOGGINGOUT;
	}
	
	inline float getLastTestPositionX() {
		return lastTestPositionX;
	}
	
	inline float getLastTestPositionY() {
		return lastTestPositionY;
	}
	
	inline CreatureObject* getConversatingCreature() {
		return conversatingCreature;
	}

	inline uint64 getCharacterID() {
		return characterID;
	}

	inline string& getFirstName() {
		return firstName;
	}
	
	inline ZoneClient* getClient() {
		return owner;
	}
	
	inline string& getRaceFileName() {
		return raceFile;
	}

	inline int getZoneIndex() {
		return zoneID;
	}

	inline Zone* getZone() {
		return zone;
	}

	inline string& getStartingLocation() {
		return startingLocation;
	}

	inline string& getHairObject() {
		return hairObject;
	}

	inline string& getStartingProfession() {
		return startingProfession;
	}

	inline unicode& getBiography() {
		return biography;
	}
	
	inline Datapad* getDatapad() {
		return datapad;
	}
	
	inline uint64 getNewItemID() {
		return baseID + itemShift++;
	}

	inline uint32 getItemShift() {
		return itemShift;
	}

	inline uint32 getForcePower() {
		return playerObject->getForcePower();
	}
	
	inline string& getFactionRank() {
		return factionRank;
	}
	
	inline uint32 getRebelPoints() {
		return rebelPoints;
	}
	
	inline uint32 getImperialPoints() {
		return imperialPoints;
	}
	
	inline int getSkillPoints() {
		return skillPoints;
	}
	
	inline PlayerObject* getPlayerObject() {
		return playerObject;
	}
	
	inline void setPlayerObject(PlayerObject* obj) {
		playerObject = obj;
	}
	
	inline bool hasSkillBox(string& skillBox) {
		return skillBoxes.containsKey(skillBox);
	}
	
	inline int getPvpRating() {
		return pvpRating;
	}
	
	inline Badges* getBadges() {
		return &badges;
	}
	
	inline int getRegionID() {
		return regionId;	
	}
	
	inline uint64 getTradeRequestedPlayer() {
		return tradeRequestedPlayer;
	}
	
	inline void setRegionID(int regId) {
		regionId = regId;	
	}
	
	inline bool isGuildLeader() {
		return guildLeader;	
	}
	
	inline void setGuildLeader(bool value) {
		guildLeader = value;	
	}
	
	inline void setChangeFactionEvent(Event* eve) {
		changeFactionEvent = eve;
	}
	
	inline bool isChangingFaction() {
		return changeFactionEvent != NULL;
	}
	
	void getPlayersNearYou();
	
	void sendGuildList();
	
	void setAdminLevel(int level);
	
	inline int getAdminLevel() {
		return adminLevel;	
	}
	
	// Survey and Sample Functions
	void setSurveyEvent(unicode& resource_name);
	void setSampleEvent(unicode& resource_name, bool firstTime = false);
	void stopSample();
	void sendSampleTimeRemaining();
	
	inline void setSurveyTool(SurveyTool* sTool) {
		surveyTool = sTool;
	}
	
	inline void setSurveyWaypoint(WaypointObject* wpo) {
		surveyWaypoint = wpo;
	}
	
	inline void setCanSurvey() {
		surveyEvent = NULL;
	}
	
	inline void setCanSample() {
		sampleEvent = NULL;
	}
	
	inline void setSurveyErrorMessage() {
		surveyErrorMessage = true;
	}
	
	inline void setSampleErrorMessage() {
		sampleErrorMessage = true;
	}
	
	inline void setCancelSample(bool val) {
		cancelSample = val;
	}
	
	inline SurveyTool* getSurveyTool() {
		return surveyTool;
	}
	
	inline WaypointObject* getSurveyWaypoint() {
		return surveyWaypoint;
	}
	
	inline bool getCanSurvey() {
		return surveyEvent == NULL;
	}
	
	inline bool getCanSample() {
		return sampleEvent == NULL;
	}

	inline bool getSurveyErrorMessage() {
		if (surveyErrorMessage) {
			surveyErrorMessage = false;
			return true;
		}
		return false;
	}
	
	inline bool getSampleErrorMessage() {
		if (sampleErrorMessage) {
			sampleErrorMessage = false;
			return true;
		}
		return false;
	}
	
	inline bool getCancelSample() {
		return cancelSample;
	}
	
	friend class PlayerManager;
	friend class ProfessionManager;
	friend class SkillManager;
	
	friend class CreatureObjectMessage1;
	friend class CreatureObjectMessage4;
	
	friend class PlayerObjectMessage3;
	friend class PlayerObjectMessage6;
	friend class PlayerObjectMessage8;
	friend class PlayerObjectMessage9;
	friend class PlayerObjectDeltaMessage3;
	friend class PlayerObjectDeltaMessage6;
	friend class PlayerObjectDeltaMessage8;
	friend class PlayerObjectDeltaMessage9;
	
	friend class BadgesResponseMessage;
};

#endif /*PLAYERIMPLEMENTATION_H_*/
