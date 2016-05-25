/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MONEYMANAGER_H_
#define MONEYMANAGER_H_

#include "engine/engine.h"
#include "MoneyAccount.h"

class MoneyManager : public Singleton<MoneyManager>, public Logger, public Object {
	VectorMap<int, Reference<MoneyAccount*> > moneyAccounts;

public:
	enum {
		NONE,
		CH,
		CHARACTER_CREATION,
		NEWBIE_TUTORIAL,
		CUSTOMER_SERVICE,
		MISSION_SYSTEM_DYNAMIC,
		MISSION_SYSTEM_PLAYER,
		BOUNTY_SYSTEM,
		CLONING_SYSTEM,
		INSURANCE_SYSTEM,
		TRAVEL_SYSTEM,
		SHIPPING_SYSTEM,
		BAZAAR_SYSTEM,
		DISPENSER_SYSTEM,
		SKILL_TRAINING_SYSTEM,
		REBEL_FACTION,
		IMPERIAL_FACTION,
		JABBAS_PALACE,
		POI_SYSTEM, // ??
		CORPSE_EXPIRATION, // No longer used (No Player Corpses)
		TESTING, // Unused?
		STRUCTURE_MAINTENANCE,
		TIP_SURCHARGE,
		VENDOR_MAINTENANCE,
		NPC_LOOT,
		JUNK_DEALER,
		CANTINA_DRINK,
		BETA_TEST, // Not used (obviously)
		BAD_GROUP_COIN_SPLIT, // Extra credits from splitting group rewards
		GAMBLING_SLOT_STANDARD, // Gambling - Standard Slots
		GAMBLING_ROULETTE, // Gambling - Roulette
		GAMBLING_CARDS_SABAAC, // Gambling, Sabaac
		VEHICLE_REPAIRS,
		RELIC_DEALER, // ??
		NEW_PLAYER_QUESTS,
		FINES, // Contraband fines, stormtrooper respect fines
		BANK
	};

	MoneyManager();

	void loadData();
};

#endif /*MONEYMANAGER_H_*/
