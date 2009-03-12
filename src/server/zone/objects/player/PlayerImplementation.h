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

#include "../../ZoneClientSession.h"

#include "../../packets/object/StfParameter.h"

#include "PlayerObject.h"

#include "professions/SkillBoxMap.h"
#include "professions/SkillBox.h"
#include "professions/XpMap.h"

#include "../terrain/RegionNames.h"

#include "sui/SuiWindowType.h"
#include "sui/SuiBoxImplementation.h"
#include "sui/listbox/SuiListBoxImplementation.h"

#include "../../../chat/room/ChatRoom.h"

#include "Player.h"

#include "../tangible/surveytool/SurveyTool.h"
#include "../tangible/campkit/campsite/CampSite.h"

#include "engine/service/Message.h"

#include "../tangible/Inventory.h"

#include "faction/FactionPointsMap.h"
#include "faction/FactionRankTable.h"
#include "faction/FactionPointList.h"

#include "../../managers/player/PlayerManager.h"
#include "badges/Badges.h"
#include "badges/Badge.h"
#include "EquippedItems.h"

//#include "../tangible/terminal/cloning/CloningTerminal.h"

class PlayerManager;
class ItemManager;
class ProfessionManager;

class PlayerSaveStateEvent;
class CommandQueueAction;
class CommandQueueActionEvent;
class PlayerRecoveryEvent;
class PlayerDigestEvent;
class CenterOfBeingEvent;
class PowerboostEventWane;
class PlayerDisconnectEvent;
class PlayerLogoutEvent;
class InvisibleDelayEvent;
class ForageDelayEvent;
class ForageZone;

class Datapad;

class WaypointObject;
class Guild;
class Certification;

class ResourceContainer;

class ActiveArea;

class PlayerImplementation : public PlayerServant {
	ReferenceSlot<ZoneClientSession> owner;

	int onlineStatus;
	Time logoutTimeStamp;

	uint64 accountID;
	uint64 characterID;
	uint64 baseID;

	String firstName;
	String lastName;

	String firstNameProper;

	String raceFile; //race iff, defines the race file of the character being created.
	uint8 raceID;

	String startingLocation; //start location iff String
	String startingProfession; //starting profession String

	UnicodeString biography; //char biography

	uint8 lotsRemaining;

	// player objects
	PlayerObject* playerObject;
	Datapad* datapad;
	EquippedItems* equippedItems;

	Vector<CommandQueueAction*> commandQueue;
	Time nextAction;
	Time nextTip;

	PlayerDisconnectEvent* disconnectEvent;
	PlayerLogoutEvent* logoutEvent;

	PlayerSaveStateEvent* playerSaveStateEvent;

	PlayerRecoveryEvent* recoveryEvent;
	PlayerDigestEvent* digestEvent;
	Event* changeFactionEvent;

	int itemShift;

	uint8 incapacitationCounter;
	Time firstIncapacitationTime;
	int pvpRating;

	//GM Flags
	bool chatMuted;
	bool immune;
	bool invisible;

	// Faction Stuff
	FactionPointsMap factionPointsMap;

	int factionStatus;

	// Profession stuff
	SkillBoxMap skillBoxes;
	SortedVector<SkillBox*> skillBoxesToSave;
	VectorMap<String, Certification*> certificationList;
	VectorMap<String, int> xpCapList;
	int skillPoints;
	int playerLevel;

	// Foraging
	bool foraging;
	int giveReg;
	int giveBonus;
	int foragePlanet;
	float forageX;
	float forageY;
	ForageDelayEvent* forageDelayEvent;
	Vector<ForageZone*> forageZones;
	Vector<ForageZone*> medForageZones;

	// Draft Schematics
	uint32 draftSchematicUpdateCount;
	VectorMap<uint32, DraftSchematic*> draftSchematicList;

	// Crafting
	CraftingTool* currentCraftingTool;
	DraftSchematic* currentDraftSchematic;
	uint64 currentSchematicID;

	// misc
	ManagedSortedVector<Player> duelList;
	CreatureObject* conversatingCreature;
	SortedVector<ChatRoom*> chatRooms;


	//guild permissions
	uint32 guildPermissionsBitmask;

	float clonePositionX;
	float clonePositionY;

	int regionId;

	bool guildLeader;

	bool centered;

	bool powerboosted;

	bool acceptingBandFlourishes;

	CenterOfBeingEvent* centerOfBeingEvent;

	PowerboostEventWane* powerboostEventWane;

	InvisibleDelayEvent* invisibleDelayEvent;


	float lastTestPositionX;
	float lastTestPositionY;

	// trading
	uint64 tradeRequestedPlayer;
	Vector<ManagedReference<SceneObject> > tradeItems;
	uint32 moneyToTrade;
	bool acceptedTrade;
	bool verifiedTrade;

	// samplig, surveying
	Event* surveyEvent;

	Event* sampleEvent;
	Event* firstSampleEvent;

	// mission vars
	uint32 misoRFC;
	int misoBSB; //mission baseline send bitmask

	String curMisoKeys; //mission keys the player is currently on
	String finMisoKeys; //mission keys the player has completed.

	VectorMap<String, String> missionSaveList;

	// Entertainer - Dance + Music
	Event* entertainerEvent;

	WaypointObject* surveyWaypoint;

	ManagedReference<SurveyTool> surveyTool;
	ManagedReference<SurveyTool> sampleTool;

	bool cancelSample;

	bool surveyErrorMessage;
	bool sampleErrorMessage;

	// SuiEvents
	VectorMap<uint32, SuiBox*> suiBoxes;
	uint32 suiBoxNextID;
	String inputBoxReturnBuffer;
	SuiListBoxVector* suiChoicesList;

	uint64 resourceDeedID;

	uint64 currentStructureID;

	//npc conversation
	String lastNpcConvoMessage;
	String lastNpcConvo;
	Vector<String> lastNpcConvoOptions;

	// Stat Migration Targets
	uint32 migrationHealth;
	uint32 migrationStrength;
	uint32 migrationConstitution;
	uint32 migrationAction;
	uint32 migrationQuickness;
	uint32 migrationStamina;
	uint32 migrationMind;
	uint32 migrationFocus;
	uint32 migrationWillpower;

	Vector<String> consentList;

	uint16 characterMask;

	bool imagedesignXpGiven;

	Vector<SkillBox*> teachingSkillList;
	Player* teachingTarget;
	Player* teachingTrainer;
	SkillBox* teachingOffer;

	ActiveArea * activeArea;
	Badges * badges;

	CampSite* camp;
	//Cloning
	CloningFacility* cloningFacility;

public:
	static const int ONLINE = 1;
	static const int OFFLINE = 2;
	static const int LINKDEAD = 3;
	static const int LOGGINGIN = 4;
	static const int LOGGINGOUT = 5;
	static const int LOADING = 6;

	static const int CSR = 1;
	static const int DEVELOPER = 2;
	static const int ADMIN = CSR | DEVELOPER;
	static const int NORMAL = 4;
	static const int QA = 8;
	static const int EC = 16;	
	static const int EMUSTAFF = 64;
	static const int CSRJR = 128;
	static const int ECJR = 256;

	static const int PVPRATING_MIN = 800;
	static const int PVPRATING_DEFAULT = 1200;

	static const int MALE = 0x01;
	static const int FEMALE = 0x02;

	static const int HUMAN = 0x004;
	static const int TRANDOSHAN = 0x008;
	static const int TWILEK = 0x010;
	static const int BOTHAN = 0x020;
	static const int ZABRAK = 0x040;
	static const int RODIAN = 0x080;
	static const int MONCALAMARI = 0x100;
	static const int WOOKIEE = 0x200;
	static const int SULLUSTAN = 0x400;
	static const int ITHORIAN = 0x800;

	static const int NEUTRAL = 0x1000;
	static const int IMPERIAL = 0x2000;
	static const int REBEL = 0x4000;
	static const int COVERT = 0x8000;

	//Guild permission statics
	const static int GUILDMAIL = 1;
	const static int GUILDSPONSOR = 2;
	const static int GUILDTITLE = 4;
	const static int GUILDKICK = 8;
	const static int GUILDACCEPT = 16;
	const static int GUILDWAR = 32;
	const static int GUILDCHANGENAME = 64;
	const static int GUILDDISBAND = 128;

public:
	PlayerImplementation();
	PlayerImplementation(uint64 cid);

	virtual ~PlayerImplementation();

	void initializePlayer();

	void create(ZoneClientSession* client);
	void refuseCreate(ZoneClientSession* client);

	void load(ZoneClientSession* client);
	void reload(ZoneClientSession* client);

	void unload();
	void savePlayerState(bool doSchedule = false);

	void logout(bool doLock = true);
	void userLogout(int msgCounter = 3);

	void disconnect(bool closeClient = true, bool doLock = true);

	void initializeEvents();
	void removeEvents();

	inline void clearLogoutEvent() {
		logoutEvent = NULL;
	}

	inline void clearDigestEvent() {
		digestEvent = NULL;
	}

	inline void clearRecoveryEvent() {
		recoveryEvent = NULL;
	}

	inline void clearSaveStateEvent() {
		playerSaveStateEvent = NULL;
	}

	inline void clearPowerboostEventWane() {
		powerboostEventWane = NULL;
	}

	void loadItems(bool newcharacter = false);

	void saveDatapad(Player* player);

	void updateHair();

	void createBaseStats();

	void decayInventory();
	void resetArmorEncumbrance();

	void makeCharacterMask();

	inline uint16 getCharacterMask() {
		return characterMask;
	}

	//Racial Attribute Limits
	inline uint32 getMinAttribute(uint8 attribute) {
		const uint32 * table = Races::getAttribLimits(raceID);
		return table[attribute * 2];
	}

	inline uint32 getMaxAttribute(uint8 attribute) {
		const uint32 * table = Races::getAttribLimits(raceID);
		return table[attribute * 2 + 1];
	}

	inline uint32 getMinHealth() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[0];
	}

	inline uint32 getMaxHealth() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[1];
	}

	inline uint32 getMinStrength() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[2];
	}

	inline uint32 getMaxStrength() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[3];
	}

	inline uint32 getMinConstitution() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[4];
	}

	inline uint32 getMaxConstitution() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[5];
	}

	inline uint32 getMinAction() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[6];
	}

	inline uint32 getMaxAction() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[7];
	}

	inline uint32 getMinQuickness() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[8];
	}

	inline uint32 getMaxQuickness() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[9];
	}

	inline uint32 getMinStamina() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[10];
	}

	inline uint32 getMaxStamina() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[11];
	}

	inline uint32 getMinMind() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[12];
	}

	inline uint32 getMaxMind() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[13];
	}

	inline uint32 getMinFocus() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[14];
	}

	inline uint32 getMaxFocus() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[15];
	}

	inline uint32 getMinWillpower() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[16];
	}

	inline uint32 getMaxWillpower() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[17];
	}

	inline uint32 getTotalAttribPoints() {
		const uint32 * table =  Races::getAttribLimits(raceID);
		return table[18];
	}
	void sendToOwner(bool doClose = true);
	void sendPersonalContainers();
	void sendTo(Player* player, bool doClose = true);

	// spatial methods
	void insertToZone(Zone* zone);
	void insertToBuilding(BuildingObject* building, bool doLock = true);
	void reinsertToZone(Zone* zone);

	void updateZone(bool lightUpdate = false);
	//void lightUpdateZone();

	void updateZoneWithParent(uint64 Parent, bool lightUpdate = false);
	//void lightUpdateZoneWithParent(uint64 Parent);

	void updatePlayerPosition(bool doLightUpdate = false);
	void updateMountPosition();

	void removeFromZone(bool doLock = true);
	void removeFromBuilding(BuildingObject* building, bool doLock = true);

	void notifyInsert(QuadTreeEntry* obj);
	void notifyDissapear(QuadTreeEntry* obj);

	void switchMap(int planetid);

	void doWarp(float x, float y, float z = 0, float randomizeDistance = 0, uint64 parentID = 0);

	void bounceBack();

	/**
	* drag will move a target player closer to the player using it.
	* \param targetPlayer Player that will be dragged.
	* \param maxRange The max distance away from the target the player can be for drag to work.
	* \param maxMovement The max amount to move the target toward the dragger per use.
	* \param needsConsent Determines if the player needs consent from the target. Default is true.
	* \param canDragLiveTarget Determines if the player can drag a target that is not dead or incapacitated. Default is false.
	**/
	void drag(Player* targetPlayer, float maxRange, float maxMovement, bool needsConsent = true, bool canDragLiveTarget = false);

	void notifySceneReady();

	void sendSystemMessage(const String& message);
	void sendSystemMessage(const String& file, const String& str, uint64 targetid = 0);
	void sendSystemMessage(const String& file, const String& str, StfParameter * param);
	void sendSystemMessage(UnicodeString& message);

	//Medic & Doctor System Messages
	void sendBattleFatigueMessage(CreatureObject* target);
	void sendHealMessage(CreatureObject* target, int h, int a, int m);

	//item methods
	void addDatapadItem(SceneObject* item);
	SceneObject* getDatapadItem(uint64 oid);
	void removeDatapadItem(uint64 oid);

	void addInventoryItem(TangibleObject* item);
	void addInventoryResource(ResourceContainer* item);

	void equipPlayerItem(TangibleObject* item, bool doUpdate = true);

	SceneObject* getPlayerItem(uint64 oid);

	bool hasItemPermission(TangibleObject* item);

	inline void updateNextTipTime() {
		nextTip.update();
		nextTip.addMiliTime(10000);
	}

	inline bool canTip() {
		return nextTip.isPast();
	}

	// trade mehtods
	void addTradeItem(SceneObject* item) {
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

	SceneObject* getTradeItem(int idx) {
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

	void setInputBoxReturnBuffer(const String& message) {
		inputBoxReturnBuffer = message;
	}

	inline String& getInputBoxReturnBuffer() {
		return inputBoxReturnBuffer;
	}

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	// Stat Migration
	bool migrateStats();

	// HAM getters
	inline uint32 getMigrationHealth() {
		if (migrationHealth == 0)
			migrationHealth = getBaseHealth();
		return migrationHealth;
	}

	inline uint32 getMigrationStrength() {
		if (migrationStrength == 0)
			migrationStrength = getBaseStrength();
		return migrationStrength;
	}

	inline uint32 getMigrationConstitution() {
		if (migrationConstitution == 0)
			migrationConstitution = getBaseConstitution();
		return migrationConstitution;
	}

	inline uint32 getMigrationAction() {
		if (migrationAction == 0)
			migrationAction = getBaseAction();
		return migrationAction;
	}

	inline uint32 getMigrationQuickness() {
		if (migrationQuickness == 0)
			migrationQuickness = getBaseQuickness();
		return migrationQuickness;
	}

	inline uint32 getMigrationStamina() {
		if (migrationStamina == 0)
			migrationStamina = getBaseStamina();
		return migrationStamina;
	}

	inline uint32 getMigrationMind() {
		if (migrationMind == 0)
			migrationMind = getBaseMind();
		return migrationMind;
	}

	inline uint32 getMigrationFocus() {
		if (migrationFocus == 0)
			migrationFocus = getBaseFocus();
		return migrationFocus;
	}

	inline uint32 getMigrationWillpower() {
		if (migrationWillpower == 0)
			migrationWillpower = getBaseWillpower();
		return migrationWillpower;
	}

	// Stat Migration Setters
	inline void setMigrationHealth(uint32 value) {
		migrationHealth = value;
	}

	inline void setMigrationStrength(uint32 value) {
		migrationStrength = value;
	}

	inline void setMigrationConstitution(uint32 value) {
		migrationConstitution = value;
	}

	inline void setMigrationAction(uint32 value) {
		migrationAction = value;
	}

	inline void setMigrationQuickness(uint32 value) {
		migrationQuickness = value;
	}

	inline void setMigrationStamina(uint32 value) {
		migrationStamina = value;
	}

	inline void setMigrationMind(uint32 value) {
		migrationMind = value;
	}

	inline void setMigrationFocus(uint32 value) {
		migrationFocus = value;
	}

	inline void setMigrationWillpower(uint32 value) {
		migrationWillpower = value;
	}

	// combat methods
	void queueFlourish(const String& modifier, uint64 target, uint32 actionCntr);
	void queueAction(Player* player, uint64 target, uint32 actionCRC, uint32 actionCntr, const String& amod);

	void doInstantAction(uint64 target, uint32 actionCRC, uint32 actionCntr, const String& amod);
	bool doAction(CommandQueueAction* action);

	void clearQueueAction(uint32 actioncntr, float timer = 0.0, uint32 tab1 = 0, uint32 tab2 = 0);
	void deleteQueueAction(uint32 actioncntr);

	void doIncapacitate();
	void changePosture(int post);

	void activateQueueAction(CommandQueueAction* action = NULL);

	void activateRecovery();
	void activateSaveStateEvent();

	void rescheduleRecovery(int time = 3000);
	void recoverFromIncapacitation();
	void rescheduleSaveStateEvent(int time);

	void doRecovery();
	void doStateRecovery();

	void activateDigest();
	void doDigest();

	void doCenterOfBeing();
	void removeCenterOfBeing();

	bool doPowerboost();
	void removePowerboost();

	void doPeace();

	void deaggro();

	void lootCorpse(bool lootAll = false);
	void lootObject(Creature* creature, SceneObject* object);

	//Foraging
	void startForaging(int foragetype);
	void finishForaging(int foragetype);
	bool forageMoveCheck(float startx, float starty, int startplanet);
	bool forageZoneCheck(int foragetype);
	int lottery(int mytickets, int totaltickets);
	bool discardForageItems();
	void giveForageItems(int foragetype);

	//mission methods
	uint32 nextMisoRFC() {
		return misoRFC++;
	}

	int checkMisoBSB(int tcb) { //mission baseline send bitmask - check for existance of a set bit.
		return (misoBSB & tcb);
	}

	void setMisoBSB(int tms) { //mission baseline send bitmask
		misoBSB |= tms;
	}

	void addToCurMisoKeys(String& tck) {
		curMisoKeys += (tck + ",");
	}

	bool isOnCurMisoKey(String tmk); //player is currently on the mission key
	void removeFromCurMisoKeys(String tck);

	void addToFinMisoKeys(String& tmp) {
		finMisoKeys += (tmp + ",");
	}

	bool hasCompletedMisoKey(String& tmk);

	void saveMissions();

	void updateMissionSave(String misoKey, const String& dbVar, String& varName, String& varData, bool doLock = false);

	void fillMissionSaveVars();

	// buffing methods
	void addBuff(uint32 buffcrc, float time);
	void clearBuffs(bool doUpdatePlayer = true);

	void updateBuffWindow();

	/**
	 * Calculates the length of time that incapacitation should last. Cannot exceed 1 minute.
	 * \param value The value that the attribute will have at incapacitation.
	 * \param oneTick The amount of one regen tick.
	 * \param attribute The attribute that is causing the incapacitation.
	 * \return Returns the number of seconds until the player should recover from incapacitation.
	 */
	inline uint8 calculateIncapacitationTimer() {
		uint8 attribute = getLowestHAMAttribute();

		//Switch the sign of the value
		int32 value = -getAttribute(attribute);

		if (value < 0)
			return 0;

		uint32 recoveryTime = (value / 5); //In seconds - 3 seconds is recoveryEvent timer

		//Gate recoveryTime: Min time of 10 seconds, Max time of 60 seconds.
		return MIN(MAX(recoveryTime, 10), 60);
	}

	// jedi methods
	void calculateForceRegen();

	bool changeForcePowerBar(int32 fp);

	inline bool isJedi() {
		return playerObject->isJedi();
	}

	void setForcePowerBar(uint32 fp) {
		if (playerObject != NULL)
			playerObject->setForcePowerBar(fp);
	}

	void updateMaxForcePowerBar(bool updateClient = true) {
		if (playerObject != NULL)
			playerObject->updateMaxForcePowerBar(updateClient);
	}

	int getFoodFilling() {
		if (playerObject == NULL)
			return 0;

		return playerObject->getFoodFilling();
	}

	int getDrinkFilling() {
		if (playerObject == NULL)
			return 0;

		return playerObject->getDrinkFilling();
	}

	int getFoodFillingMax() {
		if (playerObject == NULL)
			return 0;

		return playerObject->getFoodFillingMax();
	}

	int getDrinkFillingMax() {
		if (playerObject == NULL)
			return 0;

		return playerObject->getDrinkFillingMax();
	}


	void setFoodFilling(uint32 fill, bool updateClient = true) {
		if (playerObject == NULL)
			return;

		playerObject->setFoodFilling(fill, updateClient);

		if (playerObject->isDigesting())
			activateDigest();
	}

	void setDrinkFilling(uint32 fill, bool updateClient = true) {
		if (playerObject == NULL)
			return;

		playerObject->setDrinkFilling(fill, updateClient);

		if (playerObject->isDigesting())
			activateDigest();
	}

	void changeFoodFilling(uint32 fill, bool updateClient = true) {
		if (playerObject == NULL)
			return;

		playerObject->changeFoodFilling(fill, updateClient);

		if (playerObject->isDigesting())
			activateDigest();
	}

	void changeDrinkFilling(uint32 fill, bool updateClient = true) {
		if (playerObject == NULL)
			return;

		playerObject->changeDrinkFilling(fill, updateClient);

		if (playerObject->isDigesting())
			activateDigest();
	}

	virtual bool isAttackableBy(CreatureObject* creature) {
		if (creature->isPlayer()) {
			if (isInDuelWith((Player*)creature, false))
				return true;
		}

		if (creature->hatesFaction(this->getFaction()))
			return true;

		return (pvpStatusBitmask & CreatureFlag::ATTACKABLE);
	}

	// faction methods
	void setOvert();
	void setCovert();
	void setOnLeave();

	inline bool isOvert() {
		return (factionStatus == 2);
	}

	inline bool isCovert() {
		return (factionStatus == 1);
	}

	inline bool isOnLeave() {
		return (factionStatus == 0);
	}

	void newChangeFactionStatusEvent(uint8 status, uint32 timer);

	bool isInDuelWith(Player* targetPlayer, bool doLock = true);


	// item methods
	void changeCloth(uint64 itemid);
	void changeWeapon(uint64 itemid, bool doUpdate = true);
	void changeArmor(uint64 itemid, bool forced);

	void setWeaponSkillMods(Weapon* weapon);
	void unsetWeaponSkillMods(Weapon* weapon);
	void setWeaponAccuracy(Weapon* weapon);

	void setArmorSkillMods(Armor* armoritem);
	void unsetArmorSkillMods(Armor* armoritem);

	bool setArmorEncumbrance(Armor* armor, bool forced);
	void unsetArmorEncumbrance(Armor* armor);

	void applyAttachment(uint64 attachmentID, uint64 targetID);
	void applyPowerup(uint64 powerupID, uint64 targetID);

	void setPlayerLevel(bool updateLevel);

	void setItemSkillMod(int type, int value);

	// Profession Methods
	void saveProfessions();
	void loadProfessions();
	void trainStartingProfession();
	bool trainSkillBox(const String& name, bool updateClient = true);
	bool surrenderSkillBox(const String& name, bool updateClient = true);
	void surrenderAll();

	void resetSkillBoxesIterator() {
		skillBoxes.resetIterator();
	}

	int getSkillBoxesSize() {
		return skillBoxes.size();
	}

	String& getNextSkillBox() {
		return skillBoxes.getNextValue()->getName();
	}

	bool hasNextSkillBox() {
		return skillBoxes.hasNext();
	}

	// duel list manipulation methods
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

	String& getCertification(int idx) {
		return certificationList.get(idx)->getName();
	}


	// Crafting
	CraftingTool* getCurrentCraftingTool();
	CraftingTool* getCraftingTool(const int type, bool doLock);
	void setCurrentCraftingTool(CraftingTool* ct);
	void clearCurrentCraftingTool();

	void prepareCraftingSession(CraftingTool* ct, DraftSchematic* ds);
	void addIngredientToSlot(TangibleObject* tano, int slot, int counter);
	void removeResourceFromCraft(uint64 resID, int slot, int counter);
	void nextCraftingStage(String test);
	void craftingCustomization(String name, int condition, String customizationString);
	void createPrototype(String count);
	void createSchematic(String count);
	void handleExperimenting(int count, int numRowsAttempted, String expString);


	bool checkCertification(String certification) {
		if (certification == "")
			return true;
		else
			return certificationList.contains(certification);
	}


	//Draft Schematics

	// Draft Schematics granted from a schematicGroupName
	void sendDraftSchematics();
	void addDraftSchematicsFromGroupName(const String& schematicGroupName);
	void subtractDraftSchematicsFromGroupName(const String& schematicGroupName);
	void addDraftSchematic(DraftSchematic* ds);
	void subtractDraftSchematic(DraftSchematic* ds);

	uint32 getDraftSchematicListSize() {
		return draftSchematicList.size();
	}

	uint32 getDraftSchematicUpdateCount(uint32 count) {
		draftSchematicUpdateCount += count;
		return draftSchematicUpdateCount;
	}

	// Get by key
	DraftSchematic* getDraftSchematic(uint32 schematicID);
	// Get by index
	DraftSchematic* getDraftSchematic(int index);
	uint32 getSchematicCRC(int index);


	// badge methods
	void toggleCharacterBit(uint32 bit);

	void awardBadge(uint8 badge);

	void removeBadge(uint8 badge);

	inline bool hasBadge(uint8 badge) {
		return badges->hasBadge(badge);
	}

	// guild methods
	bool setGuild(uint32 gid);
	void setGuild(Guild* gild) {
		guild = gild;
	}

	bool updateGuild(uint32 gid);
	void updateGuild(Guild* guild);
	void loadGuildChat();

	void toggleGuildPermissionsBit(uint32 bit);

	void setGuildPermissions(uint32 bit) {
		guildPermissionsBitmask = bit;
	}

	uint32 getGuildPermissions() {
		return guildPermissionsBitmask;
	}

	bool setGuildPermissionsBit(uint32 bit, bool updateClient = false);
	bool clearGuildPermissionsBit(uint32 bit, bool updateClient = false);

	//Chat
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

	/**
	 * Retrieve the amount of experience of a certain type that the player currently has.
	 * \param xpType The string value for the type of experience to retrieve.
	 * \return The value of experience the player has of type xpType.
	 */
	int getXp(const String& xpType) {
		return playerObject->getExperience(xpType);
	}

	/**
	 * Adds experience of a type to the player's experience pool.
	 * \param xpType The string value for the type of experience to add.
	 * \param xp The value of experience to add.
	 * \param updateClient Boolean to determing whether the client should receive a delta packet for the experience gain.
	 */
	void addXp(const String& xpType, int xp, bool updateClient) {
		playerObject->addExperience(xpType, xp, updateClient);
	}

	/**
	 * Removes experience of a type from the player's experience pool.
         * \param xpType The string value for the type of experience to remove.
	 * \param xp The value of experience to remove.
	 * \param updateClient Boolean to determing whether the client should receive a delta packet for the experience loss.
	 */
	void removeXp(const String& xpType, int xp, bool updateClient) {
		playerObject->removeExperience(xpType, xp, updateClient);
	}

	/**
	 * Loads the experience pool from the database passed as a delimited string.
	 * \param xpStr The string pulled from the database that stores the xp values for the player.
	 */
	void loadXp(const String& xpStr) {
		playerObject->loadExperience(xpStr);
	}

	/**
	 * Writes the current resident xp pool to the database for the player.
	 */
	String& saveXp() {
		return playerObject->saveExperience();
	}

	/**
	 * Calculates the experience cap for a certain xp type, defaults to 2000.
	 * \param xptype The string value for the type of experience to calculate the cap for.
	 * \return The experience cap of the experience type for the player.
	 */
	int getXpTypeCap(String xptype);

	/**
	 * Loads the experience caps for all xp types.
	 */
	void loadXpTypeCap();

	/**
	 * Calculates the player level based on the current weapon equipped, or higher appropriate skills.
	 * Based on a 5-25 level system.
	 * \param xptype The type of experience to calculate if it is not appropriate to use the player's weapon. Okay to pass "".
	 * \return The player level used in calculated experience and consider colors.
	 */
	int calcPlayerLevel(String xptype);

	/**
	 * Adds a skill box to the player's repertoire and calls the appropriate functions to recalculate level and experience cap.
	 * Does not determine if the skill box is appropriate to train.
	 * \param skillBox The skill box to add.
	 * \param updateClient Boolean to determing whether the client should receive a delta packet for the new skill box.
	 */
	void addSkillBox(SkillBox* skillBox, bool updateClient = false);

	/**
	 * Removes a skill box from the player's repertoire and calls the appropriate functions to recalculate level and experience cap.
	 * Does not determine if the skill box is appropriate to drop.
	 * \param skillBox The skill box to remove.
	 * \param updateClient Boolean to determing whether the client should receive a delta packet for the skill box removeal.
	 */
	void removeSkillBox(SkillBox* skillBox, bool updateClient = false);

	/**
	 * Adds a list of weapon/object certifications gained, usually through skillBox training.
	 * \param certs A Vector of certifications that is to be added to the player.
	 * \param updateClient Boolean to determing whether the client should receive a delta packet for the new certifications.
	 */
	void addCertifications(Vector<Certification*>& certs, bool updateClient = false);

	/**
	 * Removes a list of weapon/object certifications, usually through skillBox dropping.
	 * \param certs A Vector of certifications that is to be removed from the player.
	 * \param updateClient Boolean to determing whether the client should receive a delta packet for
	 */
	void removeCertifications(Vector<Certification*>& certs, bool updateClient = false);


	void queueHeal(TangibleObject* medpack, uint32 actionCRC, const String& attribute);

	// waypoint methods
	void addWaypoint(WaypointObject* wp) {
		playerObject->addWaypoint(wp, true);
	}

	bool removeWaypoint(WaypointObject* wp) {
		if  (surveyWaypoint == wp)
			surveyWaypoint = NULL;

		return playerObject->removeWaypoint(wp, true);
	}

	WaypointObject* getWaypoint(uint64 id) {
		return playerObject->getWaypoint(id);
	}

	void updateWaypoint(WaypointObject* wp) {
		playerObject->updateWaypoint(wp);
	}

	void saveWaypoints(Player* player){
		playerObject->saveWaypoints(player);
	}

	WaypointObject* searchWaypoint(Player* play, const String& name, int mode) {
		return playerObject->searchWaypoint(play,name,mode);
	}

	inline bool hasFullInventory() {
		return inventory->isFull();
	}

	// packet methods
	void sendMessage(BaseMessage* msg);
	void sendMessage(StandaloneBaseMessage* msg);
	void broadcastMessageToOthersAround(Player* player, BaseMessage* msg);

	// setters
	void setOnline();

	void setOffline();

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

	void setClient(ZoneClientSession* client) {
		owner = client;
	}

	void sendMail(String& mailSender, UnicodeString& subjectSender, UnicodeString& bodySender, String& charNameSender);

	inline void setStartingLocation(String& loc) {
		startingLocation = loc;
	}

	inline void setRaceFileName(String& name) {
		raceFile = name;
	}

	inline void setRaceID(uint8 id) {
		raceID = id;
	}

	inline void setHairObject(const String& hair) {
		hairObject = hair;
	}

	//inline void setHairData(String& hair) {
	//	hairData = hair;
	//}

	inline void setStartingProfession(const String& prof) {
		startingProfession = prof;
	}

	inline void setBiography(UnicodeString& bio) {
		biography = bio;
	}

	inline void setBiography(const String& bio) {
		biography = bio;
	}

	inline void setLotsRemaining(uint8 lots) {
		lotsRemaining = lots;
	}

	inline void setConversatingCreature(CreatureObject*  conversator) {
		conversatingCreature = conversator;
	}

	inline void setFirstName(const String& name) {
		firstName = name;
	}

	inline void setLastName(const String& name) {
		lastName = name;
	}

	inline void setFirstNameProper(const String& name) {
		firstNameProper = name;
	}

	inline void setAccountID(uint64 id) {
		accountID = id;
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
	//inline String& getHairData() {
	//	return hairData;
	//}

	inline GroupObject* getGroupObject() {
		return group;
	}

	inline bool isOnline() {
		return onlineStatus != OFFLINE && onlineStatus != LINKDEAD;
	}

	inline bool isOffline() {
		return onlineStatus == OFFLINE;
	}

	inline bool isLoading() {
		return onlineStatus == LOADING || onlineStatus == LOGGINGIN;
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

	inline bool isFirstIncapacitationExpired() {
		return firstIncapacitationTime.isPast();
	}

	inline void resetIncapacitationCounter() {
		incapacitationCounter = 0;
	}

	inline void resetFirstIncapacitationTime() {
		if (!isFirstIncapacitation())
			resetIncapacitationCounter();

		firstIncapacitationTime.update();
		firstIncapacitationTime.addMiliTime(900000);
	}

	inline void updateIncapacitationCounter() {
		incapacitationCounter++;

		if (isFirstIncapacitation() || isFirstIncapacitationExpired())
			resetFirstIncapacitationTime();
	}

	inline bool isFirstIncapacitation() {
		return incapacitationCounter == 1;
	}

	inline uint8 getIncapacitationCounter() {
		return incapacitationCounter;
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

	inline uint64 getAccountID() {
		return accountID;
	}

	inline uint64 getCharacterID() {
		return characterID;
	}

	inline String& getFirstName() {
		return firstName;
	}

	inline String& getLastName() {
		return lastName;
	}

	inline String& getFirstNameProper() {
		return firstNameProper;
	}

	inline ZoneClientSession* getClient() {
		return owner;
	}

	inline String& getRaceFileName() {
		return raceFile;
	}

	inline uint8 getRaceID() {
		return raceID;
	}

	inline int getZoneIndex() {
		return zoneID;
	}

	inline Zone* getZone() {
		return zone;
	}

	inline String& getStartingLocation() {
		return startingLocation;
	}

	inline String& getHairObject() {
		return hairObject;
	}

	inline String& getStartingProfession() {
		return startingProfession;
	}

	inline UnicodeString& getBiography() {
		return biography;
	}

	inline uint8 getLotsRemaining() {
		return lotsRemaining;
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

	inline uint32 getForcePowerMax() {
		return getSkillMod("jedi_force_power_max");
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

	inline bool hasSkillBox(String& skillBox) {
		return skillBoxes.containsKey(skillBox);
	}

	inline int getPvpRating() {
		return pvpRating;
	}

	inline void setPvpRating(int value) {
		pvpRating = value;
	}

	inline Badges* getBadges() {
		return badges;
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

	inline void setChangeFactionStatusEvent(Event* eve) {
		changeFactionEvent = eve;
	}

	inline bool getPowerboosted() {
		return powerboosted;
	}

	inline void setPowerboosted(bool pb) {
		powerboosted = pb;
	}

	inline bool isChangingFactionStatus() {
		return changeFactionEvent != NULL;
	}

	inline bool isForaging() {
		return foraging;
	}

	inline bool isAcceptingBandFlourishes() {
		return acceptingBandFlourishes;
	}

	inline void setAcceptingBandFlourishes(bool input) {
		acceptingBandFlourishes = input;
	}

	void setResourceDeedID(uint64 objectID);

	uint64 getResourceDeedID();

	void addSuiBoxChoice(String& choice);

	void removeLastSuiBoxChoice();

	void setSuiBoxChoices(SuiListBoxVector* choicesList);

	SuiListBoxVector* getSuiBoxChoices();

	void clearSuiBoxChoices();

	inline bool hasSuiBox(uint32 boxID) {
		return suiBoxes.contains(boxID);
	}

	inline bool hasSuiBoxWindowType(uint32 windowType) {
		uint32 type = 0;
		for (int i=0; i<suiBoxes.size(); i++) {
			SuiBox* sui = suiBoxes.get(i);
			type = sui->getWindowType();
			if (windowType == type)
				return true;
		}

		return false;
	}

	inline uint32 getSuiBoxFromWindowType(uint32 windowType) {
		uint32 type = 0;
		for (int i=0; i<suiBoxes.size(); i++) {
			SuiBox* sui = suiBoxes.get(i);
			if (windowType == sui->getWindowType())
				return sui->getBoxID();
		}
		return 0;
	}

	/**
	 * This method will send the close packet to the client,
	 * closing any open sui box of the suiBoxType,
	 * and removing it from the player's list of SuiBoxes.
	 * \param boxTypeID The box type id to search for, and close.
	 */
	inline void closeSuiWindowType(uint32 windowType) {
		if (hasSuiBoxWindowType(windowType)) {
			int boxID = getSuiBoxFromWindowType(windowType);
			SuiBox* sui = (SuiBox*) getSuiBox(boxID);

			if (sui != NULL) {
				sendMessage(sui->generateCloseMessage());
				removeSuiBox(boxID);
				sui->finalize();
			}
		}
	}

	void removeSuiBox(uint32 boxID) {
		suiBoxes.drop(boxID);
	}

	SuiBox* getSuiBox(uint32 boxID) {
		return suiBoxes.get(boxID);
	}

	void addSuiBox(SuiBox* sui) {
		uint32 key = sui->getBoxID();
		suiBoxes.put(key, sui);
	}

	uint32 getNewSuiBoxID(uint32 type) {
		return (++suiBoxNextID << 16) + (uint16)type;
	}

	int getSlicingAbility();

	void getPlayersNearYou();

	void sendGuildList();

	void setAdminLevel(int level) {
		playerObject->setAdminLevel(level);
	}

	inline int getAdminLevel() {
		return playerObject->getAdminLevel();
	}

	//GM functions
	inline bool isChatMuted() {
		return chatMuted;
	}

	inline bool isImmune() {
		return immune;
	}

	inline bool isInvisible() {
		return invisible;
	}

	void mutePlayer();
	void toggleImmune();
	void activateInvisible();
	void toggleInvisible();



	// Survey and Sample Functions
	void setSurveyEvent(String& resource_name);
	void setSampleEvent(String& resource_name, bool firstTime = false);
	void stopSample();
	void sendSampleTimeRemaining();

	inline void setSurveyTool(SurveyTool* sTool) {
		surveyTool = sTool;
	}

	inline void setSampleTool(SurveyTool* sTool) {
		sampleTool = sTool;
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

	inline void clearFirstSampleEvent() {
		firstSampleEvent = NULL;
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

	inline SurveyTool* getSampleTool() {
		return sampleTool;
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

	inline void clearEntertainerEvent() {
		entertainerEvent = NULL;
	}

	inline FactionPointList * getFactionList() {
		return factionPointsMap.getFactionList();
	}


	// Entertainer tick
	void setEntertainerEvent();
	void addEntertainerFlourishXp(int xp);
	void addEntertainerHealingXp(int xp);

	//NPC Conversation Methods
	inline void setLastNpcConvStr(const String& conv) {
		lastNpcConvo = conv;
	}

	inline void setLastNpcConvMessStr(const String& mess) {
		lastNpcConvoMessage = mess;
	}

	inline String& getLastNpcConvStr() {
		return lastNpcConvo;
	}

	inline String& getLastNpcConvMessStr() {
		return lastNpcConvoMessage;
	}

	inline String& getLastNpcConvOption(int idx) {
		return lastNpcConvoOptions.get(idx);
	}

	inline void addLastNpcConvOptions(const String& option) {
		lastNpcConvoOptions.add(option);
	}

	inline int countLastNpcConvOptions() {
		return lastNpcConvoOptions.size();
	}

	inline void clearLastNpcConvOptions() {
		lastNpcConvoOptions.removeAll();
	}

	inline void setCurrentStructureID(uint64 oid){
		currentStructureID = oid;
	}

	inline uint64 getCurrentStructureID(){
		return currentStructureID;
	}

	inline int16 getFactionPoints(const String& faction) {
		return factionPointsMap.getFactionPoints(faction);
	}

	inline uint32 getMaxFactionPoints(String faction) {
		if (faction == "imperial" || faction == "rebel") {
			if (getFaction() == faction.hashCode() || getFaction() == 0)
				return FactionRankTable::getFPCap(getFactionRank());
			else
				return 500;
		} else
			return 5000;
	}

	void addFactionPoints(String faction, uint32 points);
	void subtractFactionPoints(String faction, uint32 points);

	inline int getFactionStatus() {
		return factionStatus;
	}

	inline void setFactionStatus(int status) {
		factionStatus = status;
	}

	void delFactionPoints(Player * player, uint32 amount);

	inline void setImagedesignXpGiven(bool given) {
		imagedesignXpGiven = given;
	}

	inline bool getImagedesignXpGiven() {
		return imagedesignXpGiven;
	}

	void teachPlayer(Player* player);

	void setTeachingOffer(String& sBox) {
		teachingOffer = server->getProfessionManager()->getSkillBox(sBox);
	}

	void setTeacher(Player* player) {
		teachingTrainer = player;
	}

	void setStudent(Player* player) {
		teachingTarget = player;
	}

	String& getTeachingOffer() {
		return teachingOffer->getName();
	}

	Player* getTeacher() {
		return teachingTrainer;
	}

	Player* getStudent() {
		return teachingTarget;
	}

	String& getTeachingSkillOption(int idx) {
		return teachingSkillList.get(idx)->getName();
	}

	void clearTeachingSkillOptions() {
		teachingSkillList.removeAll();
	}

	void teachSkill(String& skillname);

	void updateWeather();
	void queueThrow(TangibleObject* throwItem, uint32 actionCRC);

	inline ActiveArea * getActiveArea() {
		return activeArea;
	}

	inline void setActiveArea(ActiveArea * area) {
		activeArea = area;
	}

	void throwTrap(uint64 targetID);
	Armor* getPlayerArmor (int location) {
		if (location > 14 || location < 0)
			return NULL;
		else
			return equippedItems->getArmor(location);
	}

	void removeOldSuiBoxIfPresent(const int suiWindowType);
	void displayMessageoftheDay();

	void setCamp(CampSite* campSite) {
		camp = campSite;
	}

	CampSite* getCamp() {
		return camp;
	}

	bool hasCamp() {
		return camp != NULL;
	}

	uint64 getAvailablePower();
	void removePower(uint64 power);

	inline Vector<TangibleObject*> getInsurableItems() {
		Vector<TangibleObject*> insurableItems;

		for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
			TangibleObject* item = (TangibleObject*) inventory->getObject(i);

			if (item != NULL && item->isInsurable())
				insurableItems.add(item);
		}

		return insurableItems;
	}


	//Sending of Messages
	void sendIncapacitationTimer(uint32 seconds, bool doRecovery = true);
	void sendBankTipConfirm(Player* recipient, uint32 amount);
	void sendConsentList();
	void sendActivateCloneRequest();
	void sendCloningDataStorageConfirm(CloningTerminal* terminal);
	void sendItemInsuranceMenu(InsuranceTerminal* terminal);
	void sendItemInsureAllConfirm(InsuranceTerminal* terminal);
	void sendSlicingMenu(TangibleObject* item);

	//Event Handlers
	void onIncapacitateTarget(CreatureObject* victim);
	void onIncapacitated(SceneObject* attacker);
	void onKilled(SceneObject* killer);
	void onDeath();
	void onDeathblow(Player* victim);
	void onReceiveDeathblow(SceneObject* killer);
	void onPvpRatingGained(Player* victim);
	void onPvpRatingLost(Player* killer);
	void onPvpRatingGainedThrottled();
	void onPvpRatingLostThrottled();
	void onBadgeAwarded(Badge* badge);
	void onBadgeRevoked(Badge* badge);
	void onExperienceGained(const String& xptype, uint32 amount);
	void onExperienceLost(const String& xptype, uint32 amount);
	void onCloneDataStored();
	void onCloneDataAlreadyStored();
	void onClone();
	void onResuscitated(SceneObject* healer);
	void onMakePaymentTo(SceneObject* target, uint32 cost);
	void onMakeBankPaymentTo(SceneObject* target, uint32 cost);
	void onInsufficientFundsAvailable(SceneObject* target, uint32 amount);
	void onInsureItemSuccess(uint64 itemID);
	void onInsureItemFailure(uint64 itemID);
	void onInsureItemInsufficientFunds(uint64 itemID);
	void onInsureItemInvalidTerminal();
	void onInsureAllItemsComplete();
	void onNoValidInsurables();
	void onBankTipSuccessful();

	//Actions
	void incapacitateSelf();
	void die();
	void clone(uint64 facilityID = 0);
	void resuscitate(CreatureObject* patient, bool forced = false);
	void increasePvpRating(Player* victim);
	void increasePvpRating(uint32 amount);
	void decreasePvpRating(Player* killer);
	void decreasePvpRating(uint32 amount);
	bool makePaymentTo(SceneObject* target, uint32 cost, bool notifyPlayer = true);
	bool makeBankPaymentTo(SceneObject* target, uint32 cost, bool notifyPlayer = true);
	void insureItem(InsuranceTerminal* terminal, uint64 itemID, bool notifySuccess = true);
	void insureAllItems(uint64 terminalID);
	bool bankTipStart(Player* recipient, uint32 amount);
	void bankTipFinish(Player* recipient, uint32 amount);
	bool cashTip(Player* recipient, uint32 amount);
	void consent(Player* playerTarget);
	void unconsent(const String& name);

	void cancelRecoveryEvent();

	void crashClient();

	//Setters
	inline void setCloningFacility(CloningFacility* facility) {
		cloningFacility = facility;
		onCloneDataStored();
	}

	inline void addConsentEntry(const String& name) {
		if (!hasConsented(name))
			consentList.add(name);
	}

	inline void removeConsentEntry(const String& name) {
		for (int i = 0; i < consentList.size(); i++) {
			if (consentList.get(i) == name)
				consentList.remove(i);
		};
	}

	//Getters
	inline CloningFacility* getCloningFacility() {
		return cloningFacility;
	}


	inline bool hasConsented(const String& name) {
		for (int i = 0; i < consentList.size(); i++) {
			if (consentList.get(i) == name.toLowerCase())
				return true;
		}

		return false;
	}

	inline bool hasConsentFrom(Player* player) {
		return player->hasConsented(getFirstName().toLowerCase());
	}

	inline uint32 getConsentListSize() {
		return consentList.size();
	}

	inline String& getConsentEntry(int index) {
		return consentList.get(index);
	}

	inline bool isPowerboosted() {
		return powerboosted;
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
