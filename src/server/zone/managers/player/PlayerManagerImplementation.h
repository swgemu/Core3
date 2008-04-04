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

#ifndef PLAYERMANAGERIMPLEMENTATION_H_
#define PLAYERMANAGERIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../../db/ServerDatabase.h"

#include "PlayerMap.h"

#include "../../ZoneProcessServerImplementation.h"

#include "PlayerManager.h"

#include "../../packets.h"

class ProfessionManager;
class ItemManager;

class GuildManager;

class Player;
class PlayerImplementation;

class PlayerManagerImplementation : public PlayerManagerServant {
	ZoneProcessServerImplementation* server;
	
	PlayerMap* playerMap;

	ItemManager* itemManager;
	
	GuildManager* guildManager;
	
private:
	Player* loadFromDatabase(PlayerImplementation* player);
	void loadWaypoints(PlayerImplementation* player);

public:
	PlayerManagerImplementation(ItemManager* mgr, ZoneProcessServerImplementation* srv);
	~PlayerManagerImplementation();

	void stop();
	
	bool create(Player* player, uint32 sessionkey);	
	bool validateName(string& cname);

	Player* load(uint64 charid);

	void unload(Player* player);

	void doBankTip(Player* sender, Player* receiver, uint32 tipAmount, bool updateTipTo);
	void doCashTip(Player* sender, Player* receiver, uint32 tipAmount, bool updateTipTo);
	bool modifyOfflineBank(Player* sender, string playerName, uint32 creditAmount);
	bool modifyRecipientOfflineBank(string recipient, uint32 creditAmount);
	void updatePlayerCreditsFromDatabase(Player* player);
	void updatePlayerCreditsToDatabase(Player* player);
	
	void handleAbortTradeMessage(Player* player, bool doLock = true);
	void handleAddItemMessage(Player* player, uint64 itemID);
	void handleGiveMoneyMessage(Player* player, uint32 value);
	void handleAcceptTransactionMessage(Player* player);
	void handleUnAcceptTransactionMessage(Player* player);
	void handleVerifyTradeMessage(Player* player);
	
	void moveItem(Player* sender, Player* receiver, TangibleObject* item);

	inline void setGuildManager(GuildManager* gmanager) {
		guildManager = gmanager;
	}

	inline PlayerMap* getPlayerMap() {
		return playerMap;
	}

	inline Player* getPlayer(string& name) {
		return playerMap->get(name);
	}
	
	inline Player* putPlayer(Player* player) {
		return playerMap->put(player->getFirstName(), player);
	}
	
	inline GuildManager* getGuildManager() {
		return guildManager;
	}
	
};

#endif /*PLAYERMANAGERIMPLEMENTATION_H_*/
