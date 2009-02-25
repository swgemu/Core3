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

#include "../../objects/player/Races.h"
#include "../../objects/terrain/Terrain.h"

#include "../skills/SkillManager.h"

#include "../../objects/player/PlayerImplementation.h"
#include "../../objects/player/PlayerObjectImplementation.h"

#include "../../objects/creature/Creature.h"
#include "../../objects/creature/mount/MountCreature.h"

#include "../../objects/tangible/weapons/Weapon.h"
#include "../../objects/tangible/weapons/JediWeapon.h"

#include "../../../ServerCore.h"

#include "../../ZoneClientSession.h"
#include "../../ZoneServer.h"

#include "../../objects.h"

#include "../../Zone.h"

#include "PlayerManager.h"
#include "PlayerManagerImplementation.h"

#include "PlayerMapImplementation.h"

#include "../guild/GuildManager.h"
#include "../group/GroupManager.h"
#include "../planet/PlanetManager.h"
#include "../structure/StructureManager.h"
#include "../item/ItemManager.h"
#include "../name/NameManager.h"
#include "../user/UserManager.h"
#include "../../../chat/ChatManager.h"
#include "../../../chat/ChatManagerImplementation.h"

PlayerManagerImplementation::PlayerManagerImplementation(ItemManager* mgr, ZoneProcessServerImplementation* srv) : PlayerManagerServant() {
	playerMap = new PlayerMap(3000);
	playerMap->deploy("PlayerMap");

	itemManager = mgr;

	server = srv;

	xpScale = 1;
}

PlayerManagerImplementation::~PlayerManagerImplementation() {
	playerMap->finalize();
	playerMap = NULL;
}

void PlayerManagerImplementation::stop() {
	playerMap->resetIterator();

	while (playerMap->hasNext()) {
		Player* player = playerMap->next();

		player->wlock();

		ZoneClientSession* client = player->getClient();

		if (client != NULL)
			client->disconnect();

		player->removeUndeploymentEvent();
		player->finalize();

		player->unlock();
	}
}

bool PlayerManagerImplementation::create(Player* player, uint32 sessionkey) {
	int accountID = sessionkey;
	int galaxyID = 2;

	player->setZoneIndex(42);
	player->setTerrainName(Terrain::getTerrainName(42));

	player->initializePosition(27.0f, -3.5f, -165.0f);
	player->setDirection(0, 0, 1, 0);
	//player->setDirection(x,z,y,w);
	//player->initializePosition(-4908.0f, 6, 4101.0f);

	Zone* zne = server->getZoneServer()->getZone(42);
	PlanetManager* planetManager = zne->getPlanetManager();
	StructureManager* structureManager = planetManager->getStructureManager();
	SceneObject* parent = structureManager->getCell(2203318222975uLL); // newbie tutorial skipped
	if (parent != NULL)
		player->setParent(parent, 0xFFFFFFFF);

	//player->randomizePosition(45);

	int race = Races::getRaceID(player->getRaceFileName());

	player->setObjectCRC(Races::getRaceCRC(race));
	player->setRaceName(Races::getRace(race));
	player->setTemplateName(Races::getSpecies(race));
	player->setGender(Races::getGender(race));

	int gender = 0;
	int creditsCash = 100000;
	int creditsBank = 100000;

	if (server->getUserManager()->isAdmin(player->getFirstName()))
		player->setAdminLevel(PlayerImplementation::DEVELOPER);
	else
		player->setAdminLevel(PlayerImplementation::NORMAL);

	player->setCashCredits(creditsCash);
	player->setBankCredits(creditsBank);

	String bio = player->getBiography().toString();
	MySqlDatabase::escapeString(bio);
	String info = "";

	String appearance;
	String playApp;
	player->getCustomizationString(playApp);

	BinaryData cust(playApp);
	cust.encode(appearance);

	String hairdata;
	String hairApp;
	player->getHairAppearance(hairApp);
	BinaryData hair(hairApp);
	hair.encode(hairdata);

	player->createBaseStats();

	//Set players HAM stats so they are not default(3k).
	player->resetHAMBars(false);

	try {
		StringBuffer query;
		query << "INSERT INTO `characters` "
		<< "(`account_id`,`galaxy_id`,`firstname`,`surname`,"
		<< "`appearance`,`professions`,`race`,`gender`,`lots`,"
		<< "`credits_inv`,`credits_bank`,`guild`,`x`,`y`,`z`,`zoneid`,`planet_id`,`parentid`,"
		<< "`lfg`,`helper`,`roleplayer`,`faction_id`,`archived`,`scale`,`biography`,"
		<< "`infofield`,`hair`,`hairData`,`playermodel`,`CRC`,`Title`,"
		<< "`health`,`strength`,`constitution`,"
		<< "`action`,`quickness`,`stamina`,"
		<< "`mind`,`focus`,`willpower`,"
		<< "`PvpRating`, adminLevel, `experience`"
		<< ") VALUES ("
		<< accountID << "," << galaxyID << ",'"
		<< player->getFirstName() << "','" << player->getLastName() << "','"
		<< appearance.subString(0, appearance.length() - 1) << "','"
		<< player->getStartingProfession() << "'," <<  race << "," << gender << ",10,"
		<< creditsCash << "," << creditsBank << ",0,"
		<< player->getPositionX() << "," << player->getPositionY() << ","
		<< player->getPositionZ() << "," << player->getZoneIndex() << "," << 0 << ", 2203318222975" //planetID + parentid (newbie skipped cell)
		<< ",0,0,0,0,0," << player->getHeight() << ","
		<< "'" << bio << "','" << info << "','"
		<< player->getHairObject() << "','" << hairdata.subString(0, hairdata.length() - 1) << "','', '0','',"
		<< player->getBaseHealth() << "," << player->getBaseStrength() << "," << player->getBaseConstitution() << ","
		<< player->getBaseAction() << "," << player->getBaseQuickness() << "," << player->getBaseStamina() << ","
		<< player->getBaseMind() << "," << player->getBaseFocus() << "," << player->getBaseWillpower() << ","
		<< player->getPvpRating() << "," << player->getAdminLevel() << ",'" << player->saveXp() << "')";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		player->setAccountID(accountID);
		player->setCharacterID(res->getLastAffectedRow());

		PlayerObject* playerObject = player->getPlayerObject();
		playerObject->setObjectID(player->getObjectID() + 0x0C);

		server->lock();

		Guild* guild = guildManager->getGuild(0);

		if (guild != NULL) {
			player->setGuild(guild);

			player->setGuildLeader(false);

			player->setGuildPermissions(0);
		}

		server->unlock();

		playerMap->put(player->getFirstName(), player);

		delete res;
	} catch (DatabaseException& e) {
		player->error(e.getMessage());
		return false;
	} catch (...) {
		player->error("unreported exception caught in PlayerManagerImplementation::create");
		return false;
	}

	return true;
}

BaseMessage* PlayerManagerImplementation::checkPlayerName(const String& name, const String& species) {
	NameManager * nm = server->getNameManager();
	BaseMessage* msg = NULL;

	String firstName;

	int idx = name.indexOf(" ");
	if (idx != -1)
		firstName = name.subString(0, idx);
	else
		firstName = name;

	//Name passes filters, does it already exist?
	if (!validateName(firstName))
		return msg = new ClientCreateCharacterFailed("name_declined_in_use");

	//Check to see if name is valid
	int res = nm->validateName(name, species);

	if (res != NameManagerResult::ACCEPTED) {
		switch (res) {
		case NameManagerResult::DECLINED_EMPTY:
			msg = new ClientCreateCharacterFailed("name_declined_empty");
			break;
		case NameManagerResult::DECLINED_DEVELOPER:
			msg = new ClientCreateCharacterFailed("name_declined_developer");
			break;
		case NameManagerResult::DECLINED_FICT_RESERVED:
			msg = new ClientCreateCharacterFailed("name_declined_fictionally_reserved");
			break;
		case NameManagerResult::DECLINED_PROFANE:
			msg = new ClientCreateCharacterFailed("name_declined_profane");
			break;
		case NameManagerResult::DECLINED_RACE_INAPP:
			msg = new ClientCreateCharacterFailed("name_declined_racially_inappropriate");
			break;
		case NameManagerResult::DECLINED_SYNTAX:
			msg = new ClientCreateCharacterFailed("name_declined_syntax");
			break;
		case NameManagerResult::DECLINED_RESERVED:
			msg = new ClientCreateCharacterFailed("name_declined_reserved");
			break;
		default:
			msg = new ClientCreateCharacterFailed("name_declined_retry");
			break;
		}

		return msg; //Name failed filters
	}

	return msg;
}

bool PlayerManagerImplementation::hasAdminRights(uint32 characterID) {
	try {
		StringBuffer query;
		query << "SELECT adminLevel FROM characters WHERE character_id = " << characterID;

		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		if (result->next()) {
			uint32 adminLevel = result->getInt(0);

			if (adminLevel == PlayerImplementation::NORMAL) {
				delete result;
				return false;
			}
		} else {
			delete result;
			return false;
		}

		delete result;

		return true;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << endl;
		return false;
	} catch (...) {
		System::out << "unreported exception caught in ZonePacketHandler::handleSelectCharacter(Message* pack)\n";
		return false;
	}

	return false;
}

BaseMessage* PlayerManagerImplementation::attemptPlayerCreation(Player* player, ZoneClientSession* client) {
	//Player name is valid, attempt to create player
	BaseMessage* msg = NULL;
	player->info("entering PlayerManagerImplementation::attemptPlayerCreation");

	try {
		player->wlock();

		if (create(player, client->getSessionKey())) {
			BaseMessage* hb = new HeartBeat();
			client->sendMessage(hb);

			msg = new ClientCreateCharacterSuccess(player->getCharacterID());

			Zone* zone = server->getZoneServer()->getZone(player->getZoneIndex());
			player->setZone(zone);

			zone->registerObject(player);

			player->info("trying to createItems and train professions");
			player->loadItems(true);
			player->trainStartingProfession();

			player->unload(); // force a save of items, client will relogin

			zone->deleteObject(player->getObjectID());

			player->info("succesufully created player");

			player->unlock();
		} else {
			client->info("name refused for character creation");

			msg = new ClientCreateCharacterFailed("name_declined_retry");

			player->info("name refused on creation");

			player->unlock();

			player->disconnect();

			player->finalize();
		}

		return msg; //return success or fail packet
	} catch (Exception& e) {
		StringBuffer err;
		err << "unreported exception on PlayerManagerImplementation::attemptPlayerCreation()\n" << e.getMessage() << "\n";
		player->error(err.toString());
		e.printStackTrace();
		player->unlock();
		return new ClientCreateCharacterFailed("name_declined_internal_error"); //something went wrong
	} catch (...) {
		StringBuffer err;
		err << "unreported exception on PlayerManagerImplementation::attemptPlayerCreation()\n";
		player->error(err.toString());
		player->unlock();
		return new ClientCreateCharacterFailed("name_declined_internal_error"); //something went wrong
	}
}

bool PlayerManagerImplementation::validateName(const String& name) {
	if (name.isEmpty())
		return false;

	try {
		String query = "SELECT * FROM characters WHERE lower(firstname) = \""
					   + name.toLowerCase() + "\"";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		bool nameExists = res->next();

		delete res;

		return !nameExists;
	} catch (DatabaseException& e) {
		return false;
	}
}

Player* PlayerManagerImplementation::load(uint64 charid) {
	Player* player = new Player(charid);
	player->initializePlayer();

	player->setZoneProcessServer(server);

	loadFromDatabase(player);

	playerMap->put(player->getFirstName(), player);

	return player;
}

void PlayerManagerImplementation::loadFromDatabase(Player* player) {
	ResultSet* character;

/*
	String mcmahon_app;
	String app;
	StringBuffer appstream;
	appstream << 0x02 << 0x24 << 0x17 << 0xC2 << 0xA3 << 0x18 << 0xC3 << 0xBF << 0x01 << 0x1C << 0xC3 << 0xBF << 0x01 << 0x1B << 0xC3 << 0xBD << 0x05 << 0xC3 << 0xBF << 0x01 << 0x1A << 0xC2 << 0x8A << 0x19 << 0xC3 << 0xBF << 0x01 << 0x0D << 0xC3 << 0xA5 << 0x09 << 0xC3 << 0xBF << 0x01 << 0x12 << 0xC3 << 0xBF << 0x01 << 0x13 << 0x38 << 0x20 << 0x7A << 0x10 << 0x38 << 0x21 << 0xC3 << 0xBF << 0x01 << 0x0F << 0xC3 << 0xBF << 0x01 << 0x14 << 0x09 << 0x11 << 0xC3 << 0xBF << 0x01 << 0x0E << 0x42 << 0x03 << 0xC3 << 0x91 << 0x0B << 0x07 << 0x0C << 0xC3 << 0xBF << 0x01 << 0x06 << 0xC2 << 0x8F << 0x08 << 0xC3 << 0xBF << 0x01 << 0x15 << 0xC3 << 0xBF << 0x01 << 0x16 << 0x4C << 0x04 << 0xC3 << 0xBF << 0x02 << 0x07 << 0xC3 << 0xBF << 0x01 << 0x0A << 0xC3 << 0xBF << 0x02 << 0x23 << 0x07 << 0x25 << 0xC3 << 0xBF << 0x01 << 0x24 << 0xC3 << 0xBF << 0x01 << 0x2A << 0xC3 << 0xBF << 0x01 << 0x01 << 0x1D << 0x1D << 0xC3 << 0xBF << 0x01 << 0x1F << 0x0A << 0x1E << 0x01 << 0xC3 << 0xBF << 0x03;
	app = appstream.toString();
	BinaryData myapp(app);
	myapp.encode(mcmahon_app);
	System::out << "appearance String: \"" << mcmahon_app.substr(0, mcmahon_app.size() - 1) << "\"" << endl;


	String mcmahon_hair;
	String hairsss;
	StringBuffer hairstream;
	hairstream << 0x02 << 0x01 << 0x02 << 0x0A << 0xC3 << 0xBF << 0x03;
	hairsss = hairstream.toString();
	BinaryData myhair(hairsss);
	myhair.encode(mcmahon_hair);
	System::out << "hair String: \"" << mcmahon_hair.substr(0, mcmahon_hair.size() - 1) << "\"" << endl;
*/


	StringBuffer query;
	query << "SELECT * FROM characters WHERE character_id = " << player->getCharacterID();

	character = ServerDatabase::instance()->executeQuery(query);

	if (!character->next()) {
		StringBuffer msg;
		msg << "unknown character ID" << player->getCharacterID();

		throw Exception(msg.toString());
	}

	player->setAccountID(character->getInt(1));
	player->setFirstName(character->getString(3));
	player->setLastName(character->getString(4));

	String orbname = "Player " + player->getFirstName();
	player->deploy(orbname);

	PlayerObject* playerObject = new PlayerObject(player);

	player->setPlayerObject(playerObject);

	if (player->getLastName() != "")
		player->setCharacterName(player->getFirstName() + " " + player->getLastName());
	else
		player->setCharacterName(player->getFirstName());

	player->setFirstNameProper(player->getFirstName());

	Zone* zne = server->getZoneServer()->getZone(character->getInt(16));

	player->setZoneIndex(character->getInt(16));
	player->setTerrainName(Terrain::getTerrainName(player->getZoneIndex()));
	player->initializePosition(character->getFloat(13), character->getFloat(15), character->getFloat(14));

	server->lock();

	Guild* guild = guildManager->getGuild(character->getUnsignedInt(12));
	if (guild != NULL) {
		player->setGuild(guild);
		if (guild->getGuildLeader() == player->getCharacterID())
			player->setGuildLeader(true);
		else
			player->setGuildLeader(false);
	}

	server->unlock();

	String appearance = character->getString(5);
	BinaryData cust(appearance);
	String custStr;
	cust.decode(custStr);
	player->setCustomizationString(custStr);

	String hairData = character->getString(28);
	BinaryData hair(hairData);
	String hData;
	hair.decode(hData);
	player->setHairAppearance(hData);

	int raceID = character->getInt(7);

	player->setRaceID(raceID);
	player->setObjectCRC(Races::getRaceCRC(raceID));
	player->setRaceName(Races::getRace(raceID));
	player->setTemplateName(Races::getSpecies(raceID));
	player->setGender(Races::getGender(raceID));
	player->setHairObject(character->getString(27));

	player->setFaction(character->getUnsignedInt(21));

	player->setHeight(character->getFloat(23));

	player->setLotsRemaining(character->getInt(9));
	player->setCashCredits(character->getInt(10));
	player->setBankCredits(character->getInt(11));

	//location = character->getString(5);
	player->setStartingProfession(character->getString(6));

	player->setItemShift(character->getUnsignedInt(34));

	String bio = character->getString(24);
	player->setBiography(bio);

	String title = character->getString(32);
	player->getPlayerObject()->setTitle(title);

	player->setBaseHealth(character->getInt(35));
	player->setBaseStrength(character->getInt(36));
	player->setBaseConstitution(character->getInt(37));
	player->setBaseAction(character->getInt(38));
	player->setBaseQuickness(character->getInt(39));
	player->setBaseStamina(character->getInt(40));
	player->setBaseMind(character->getInt(41));
	player->setBaseFocus(character->getInt(42));
	player->setBaseWillpower(character->getInt(43));

	//Set wounds and shock levels from the database
	player->setHealthWounds(character->getInt(44));
	player->setStrengthWounds(character->getInt(45));
	player->setConstitutionWounds(character->getInt(46));
	player->setActionWounds(character->getInt(47));
	player->setQuicknessWounds(character->getInt(48));
	player->setStaminaWounds(character->getInt(49));
	player->setMindWounds(character->getInt(50));
	player->setFocusWounds(character->getInt(51));
	player->setWillpowerWounds(character->getInt(52));
	player->setShockWounds(character->getInt(53));

	player->setGuildPermissions(character->getInt(56));

	player->resetHAMBars(false);

	player->loadProfessions();
	player->loadXp(character->getString(60)); // put this here to avoid cap confusions

	player->setForcePowerBar(player->getForcePowerMax());

	PlanetManager* planetManager = zne->getPlanetManager();
	StructureManager* structureManager = planetManager->getStructureManager();
	SceneObject* parent = structureManager->getCell(character->getUnsignedLong(33));

	if (parent != NULL)
		player->setParent(parent, 0xFFFFFFFF);

	loadWaypoints(player);

	player->setPvpRating(character->getInt(54));
	player->setAdminLevel(character->getInt(55));

	player->setFactionStatus(character->getInt(58));
	player->setFactionRank(character->getInt(59));

	//Posture
	player->changePosture(character->getInt(61));

	//If a player is incapacitated when the server saves, and subsequently are unloaded from memory, they should be loaded as standing.
	if (player->isIncapacitated())
		player->setPosture(CreaturePosture::UPRIGHT);

	//Set time of death
	player->setTimeOfDeath(character->getUnsignedLong(62));

	player->setCloningFacility(structureManager->getCloningFacility(character->getUnsignedLong(65)));

	//Load consent list from database
	loadConsentList(player);
	loadFactionPoints(player);
	loadBadges(player);

	delete character;
}

void PlayerManagerImplementation::loadWaypoints(Player* player) {
	StringBuffer query;
	ResultSet* result = NULL;

	query << "SELECT * FROM waypoints WHERE owner_id = '" << player->getCharacterID() <<"';";

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			String wpName = result->getString(2);

			float x = result->getFloat(3);
			float y = result->getFloat(4);

			String planetName = result->getString(5);
			String internalNote = result->getString(7);
			bool active = result->getInt(6);

			WaypointObject* wp = new WaypointObject(player, player->getNewItemID());

			wp->setName(wpName);
			wp->setPlanetName(planetName);
			wp->setInternalNote(internalNote);
			wp->setPosition(x, 0.0f, y);
			wp->changeStatus(active);
			player->addWaypoint(wp);
		}
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in PlayerManagerImplementation::loadWaypoints\n";
	}

	delete result;
}

void PlayerManagerImplementation::updateGuildStatus(Player* player) {
	//This function makes sure, that a player, which was removed from a guild while being offline,
	//is not re-inserted as a guildmember again on loading from cache

	player->info("Entering PlayerManagerImplementation::updateGuildStatus(Player* player)");

	ResultSet* character;
	StringBuffer query;

	try {
		query << "SELECT guild FROM characters WHERE character_id = " << player->getCharacterID();

		character = ServerDatabase::instance()->executeQuery(query);

	} catch (DatabaseException& e) {
		System::out << "DB Exception in PlayerManagerImplementation::updateGuildStatus(Player* player):" << endl << e.getMessage() << endl;
		player->info("DB ERROR: Catch #1 from PlayerManagerImplementation::updateGuildStatus(Player* player)");

		return;

	} catch (...) {
		System::out << "unreported exception caught in PlayerManagerImplementation::updateGuildStatus\n";
		player->info("ERROR: Exit via catch #2 from PlayerManagerImplementation::updateGuildStatus(Player* player)");

		return;
	}


	if (character->next()) {
		if (character->getInt(0) == 0) {

			try {
				server->lock();

				uint64 defGuild = 0;

				Guild * guild = player->getGuild();

				if (guild != NULL) {
					ChatRoom* room = guild->getGuildChat();

					if (room != NULL)
						room->removePlayer(player, false);
				} else
					System::out << "DEFAULT guild in table GUILDS (DB) is not ID 0 ! Edit table and set DEFAULT GUILD to ID 0!\n";

				player->setGuild(defGuild);
				player->updateGuild(defGuild);
				player->setGuildLeader(false);
				player->setGuildPermissions(0);

				server->unlock();
			} catch (...) {
				player->info("ERROR: Executed catch #3 in PlayerManagerImplementation::updateGuildStatus(Player* player)");

				server->unlock();
			}
		}
	}

	player->info("Clean exit from PlayerManagerImplementation::updateGuildStatus(Player* player)");
}

void PlayerManagerImplementation::updateOtherFriendlists(Player* player, bool status) {
	PlayerObject* playerObject = player->getPlayerObject();
	if (playerObject == NULL)
		return;

	if (player->isOnline())
		populateReverseFriendList(player);

	sendUpdateMessagesToFriends(player, status);

}

void PlayerManagerImplementation::populateReverseFriendList(Player* player) {
	PlayerObject* playerObject = player->getPlayerObject();

	try {
		StringBuffer query;

		query << "SELECT * from friendlist_reverse where charID = " << player->getCharacterID() << ";";

		ResultSet* gotMe = ServerDatabase::instance()->executeQuery(query);

		while (gotMe->next())
			playerObject->pokeReverseFriendList(gotMe->getUnsignedLong(1));

		delete gotMe;

	} catch (DatabaseException& e) {
		System::out << "DB Exception at PlayerManagerImplementation::updateOtherFriendlists \n" << e.getMessage();
		return;

	} catch (...) {
		System::out << "unreported exception at PlayerManagerImplementation::updateOtherFriendlists\n";
		return;
	}
}

void PlayerManagerImplementation::sendUpdateMessagesToFriends(Player* player, bool status) {
	PlayerObject* playerObject = player->getPlayerObject();

	Player* playerToInform = NULL;

	uint64 poid;

	try {
		player->info("Starting messaging at PlayerManagerImplementation::sendUpdateMessagesToFriends");

		String loggingInName = player->getFirstName().toLowerCase();

		Zone* zone = player->getZone();
		if (zone == NULL)
			return;

		int listSize = playerObject->getReverseFriendListSize();

		for (int i = 0; i < listSize; ++i) {
			poid = playerObject->getReverseFriendListEntry(i);

			SceneObject* sco = zone->lookupObject(poid);

			if (sco != NULL) {
				if (sco->isPlayer()) {
					playerToInform = (Player*) sco;

					if (playerToInform->isOnline()) {
						FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(loggingInName, "Core3", status);
						playerToInform->sendMessage(notifyStatus);
					}
				}
			}
		}

	} catch (...) {
		player->error("Unreported exception in PlayerManagerImplementation::sendUpdateMessagesToFriends");
		return;
	}
	player->info("Clean exit from PlayerManagerImplementation::sendUpdateMessagesToFriends");
}

void PlayerManagerImplementation::unload(Player* player) {
	save(player);

	playerMap->remove(player->getFirstName());
}

void PlayerManagerImplementation::save(Player* player) {
	String biography = player->getBiography().toString();
	MySqlDatabase::escapeString(biography);

	uint64 cloningFacilityID = 0;
	CloningFacility* cloningFacility = player->getCloningFacility();

	if (cloningFacility != NULL)
		cloningFacilityID = cloningFacility->getObjectID();

	StringBuffer query;
	query << "UPDATE characters SET x=" << player->getPositionX() << ",y=" << player->getPositionY()
	<< ",z=" << player->getPositionZ()
	<< ",zoneid=" << player->getZoneIndex()
	<< ",faction_id=" << player->getFaction()
	<< ",biography=\'" << biography << "\'"
	<< ",Title=" << "'" << player->getPlayerObject()->getCurrentTitle() << "'"
	<< ",Guild=" << "'" << player->getGuildID() << "'"
	<< ",lots=" << player->getLotsRemaining()
	<< ",credits_inv=" << "'" << player->getCashCredits() << "'"
	<< ",credits_bank=" << "'" << player->getBankCredits() << "'"
	<< ",parentid=" << "'" << player->getParentID() << "'"
	<< ",itemShift=" << player->getItemShift()
	<< ",HealthWounds=" << player->getHealthWounds()
	<< ",StrengthWounds=" << player->getStrengthWounds()
	<< ",ConstitutionWounds=" << player->getConstitutionWounds()
	<< ",ActionWounds=" << player->getActionWounds()
	<< ",QuicknessWounds=" << player->getQuicknessWounds()
	<< ",MindWounds=" << player->getMindWounds()
	<< ",FocusWounds=" << player->getFocusWounds()
	<< ",WillpowerWounds=" << player->getWillpowerWounds()
	<< ",BattleFatigue=" << player->getShockWounds()
	<< ",AdminLevel=" << player->getAdminLevel()
	<< ",PvpRating=" << player->getPvpRating()
	<< ",guildpermission=" << player->getGuildPermissions()
	<< ",factionStatus=" << (int) player->getFactionStatus()
	<< ",factionRank=" << (int) player->getFactionRank()
	<< ",experience=" << "'" << player->saveXp() << "'"
	<< ",posture=" << (int) player->getPosture()
	<< ",timeOfDeath=" << (uint64) player->getTimeOfDeath()
	<< ",cloningFacility=" << (uint64) cloningFacilityID
	<< " WHERE character_id=" << player->getCharacterID() << ";";
	try {
		ServerDatabase::instance()->executeStatement(query);
	} catch(DatabaseException& e) {
		System::out << "Failed to unload character: " << player->getFirstName() << "\n";
		System::out << e.getMessage() << endl;
	}

	player->saveProfessions();
	saveFactionPoints(player);
	saveBadges(player);

	//Update the database with the consentlist info
	updateConsentList(player);
}

void PlayerManagerImplementation::loadFactionPoints(Player* player) {
	StringBuffer query;
	query << "SELECT * FROM character_faction_points WHERE character_id = " << player->getCharacterID() << ";";
	try {
		ResultSet * res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			String faction = res->getString(1);
			int points = res->getInt(2);

			if (points >= 0)
				player->addFactionPoints(faction, points);
			else
				player->subtractFactionPoints(faction, abs(points));
		}

		delete res;
	} catch(DatabaseException& e) {
		System::out << "Failed to load FactionPoints: " << player->getFirstName() << endl;
		System::out << e.getMessage() << endl;
	}
}

void PlayerManagerImplementation::saveFactionPoints(Player* player) {

	FactionPointList * list = player->getFactionList();

	try {
		for (int i = 0; i < list->size(); i++) {
			String faction = list->get(i);
			int points = player->getFactionPoints(faction);
			StringBuffer hash;
			hash << faction << player->getCharacterID();
			StringBuffer query;
			query << "INSERT INTO character_faction_points VALUES(";
			query << player->getCharacterID() << ", '";
			query << faction << "', " << points << ", MD5('";
			query << hash.toString() << "')) ON DUPLICATE KEY UPDATE faction_points = " << points;

			ServerDatabase::instance()->executeStatement(query);
		}

	} catch(DatabaseException& e) {
		System::out << "Failed to save FactionPoints: " << player->getFirstName() << endl;
		System::out << e.getMessage() << endl;
	}
}

void PlayerManagerImplementation::loadBadges(Player* player) {
	Badges * badges = player->getBadges();
	StringBuffer query;
	query << "SELECT * FROM character_badge WHERE character_id = " << player->getCharacterID() << ";";
	try {
		ResultSet * res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			for (int i=0; i < 5; i++) {
				badges->setBitmask(i, res->getInt(i + 1));
			}

			badges->setNumBadges(res->getInt(6));

			for (int i=0; i < 6; i++) {
				badges->setTypeCount(i, res->getInt(i + 6));
			}
		}

		delete res;
	} catch(DatabaseException& e) {
		System::out << "Failed to load Badges: " << player->getFirstName() << endl;
		System::out << e.getMessage() << endl;
	}
}

void PlayerManagerImplementation::saveBadges(Player* player) {

	Badges * badges = player->getBadges();

	try {

		StringBuffer query;
		query << "REPLACE INTO character_badge VALUES(";
		query << player->getCharacterID() << ",";
		query << badges->getBitmask(0) << "," << badges->getBitmask(1) << "," << badges->getBitmask(2) << "," << badges->getBitmask(3) << "," << badges->getBitmask(4) << ",";
		query << badges->getNumBadges() << "," << badges->getTypeCount(0) << "," << badges->getTypeCount(1) << "," << badges->getTypeCount(2) << "," ;
		query << badges->getTypeCount(3) << "," << badges->getTypeCount(4) << "," << badges->getTypeCount(5) << ");";


		ServerDatabase::instance()->executeStatement(query);


	} catch(DatabaseException& e) {
		System::out << "Failed to save Badges: " << player->getFirstName() << endl;
		System::out << e.getMessage() << endl;
	}
}
void PlayerManagerImplementation::handleAbortTradeMessage(Player* player, bool doLock) {
	try {
		player->wlock(doLock);

		uint64 targID = player->getTradeRequestedPlayer();
		SceneObject* obj = server->getZoneServer()->getObject(targID);

		AbortTradeMessage* msg = new AbortTradeMessage();

		if (obj != NULL && obj->isPlayer()) {
			Player* receiver = (Player*)obj;

			receiver->sendMessage(msg->clone());

			receiver->wlock(player);

			receiver->clearTradeItems();
			receiver->setTradeRequestedPlayer(0);
			receiver->setAcceptedTrade(false);
			receiver->setVerifiedTrade(false);
			receiver->setMoneyToTrade(0);

			receiver->unlock();
		}

		player->sendMessage(msg->clone());

		delete msg;

		player->clearTradeItems();
		player->setTradeRequestedPlayer(0);
		player->setAcceptedTrade(false);
		player->setVerifiedTrade(false);
		player->setMoneyToTrade(0);

		player->unlock(doLock);
	} catch (...) {
		player->unlock(doLock);
		System::out << "Unreported exception caught in PlayerManagerImplementation::handleAbortTradeMessage(Player* player)\n";
	}
}

void PlayerManagerImplementation::handleAddItemMessage(Player* player, uint64 itemID) {
	try {
		player->wlock();

		SceneObject* object = player->getInventoryItem(itemID);

		if (object != NULL) {
			if (object->isTangible()) {
				TangibleObject* item = (TangibleObject*)object;

				if (item->isEquipped()) {
					handleAbortTradeMessage(player, false);
					player->sendSystemMessage("container_error_message", "container20"); //You can't trade equipped items!

					player->unlock();
					return;
				}

				uint64 targID = player->getTradeRequestedPlayer();
				SceneObject* obj = server->getZoneServer()->getObject(targID);

				if (obj != NULL && obj->isPlayer()) {
					Player* receiver = (Player*)obj;

					try {
						receiver->wlock(player);

						Inventory* recvInventory = receiver->getInventory();

						if (recvInventory->isFull()) {
							receiver->unlock();

							handleAbortTradeMessage(player, false);

							player->sendSystemMessage("Your targets inventory is full");
							receiver->sendSystemMessage("You dont have enough space in your inventory");

							player->unlock();
							return;
						}

						receiver->unlock();

						player->addTradeItem(item);

						item->sendTo(receiver);

						AddItemMessage* msg = new AddItemMessage(itemID);
						receiver->sendMessage(msg);
					} catch (...) {
						receiver->error("unreported exception caught in PlayerManagerImplementation::handleAddItemMessage");
						receiver->unlock();
					}
				}
			}
		} else{
			SceneObject* object = player->getDatapadItem(itemID);

			if (object != NULL){
				if (object->isIntangible()){
					IntangibleObject* item = (IntangibleObject*)object;

					uint64 targID = player->getTradeRequestedPlayer();
					SceneObject* obj = server->getZoneServer()->getObject(targID);

					if (obj != NULL && obj->isPlayer()) {
						Player* receiver = (Player*)obj;

						try {
							receiver->wlock(player);

							Datapad* recvDatapad = receiver->getDatapad();

							/*if (recvDatapad->isFull()) {
								receiver->unlock();

								handleAbortTradeMessage(player, false);

								player->sendSystemMessage("Your targets inventory is full");
								receiver->sendSystemMessage("You dont have enough space in your inventory");

								player->unlock();
								return;
							}*/

							receiver->unlock();

							player->addTradeItem(item);

							item->sendTo(receiver);

							AddItemMessage* msg = new AddItemMessage(itemID);
							receiver->sendMessage(msg);
						} catch (...) {
							receiver->error("unreported exception caught in PlayerManagerImplementation::handleAddItemMessage");
							receiver->unlock();
						}
					}
				}
			}
		}

		player->unlock();
	} catch (...) {
		player->unlock();
		player->error("Unreported exception caught in PlayerManagerImplementation::handleAddItemMessage(Player* player, uint64 itemID)");
	}
}

void PlayerManagerImplementation::handleGiveMoneyMessage(Player* player, uint32 value) {
	try {
		player->wlock();

		uint32 currentMoney = player->getCashCredits();

		if (value > currentMoney)
			value = currentMoney;

		player->setMoneyToTrade(value);

		uint64 targID = player->getTradeRequestedPlayer();
		SceneObject* obj = server->getZoneServer()->getObject(targID);

		if (obj != NULL && obj->isPlayer()) {
			Player* receiver = (Player*)obj;

			GiveMoneyMessage* msg = new GiveMoneyMessage(value);
			receiver->sendMessage(msg);
		}

		player->unlock();
	} catch (...) {
		player->unlock();
		player->error("Unreported exception in PlayerManagerImplementation::hanleGiveMoneyMessage(Player* player, uint32 value)");
	}
}

void PlayerManagerImplementation::handleAcceptTransactionMessage(Player* player) {
	try {
		player->wlock();

		player->setAcceptedTrade(true);

		uint64 targID = player->getTradeRequestedPlayer();
		SceneObject* obj = server->getZoneServer()->getObject(targID);

		if (obj != NULL && obj->isPlayer()) {
			Player* receiver = (Player*)obj;

			AcceptTransactionMessage* msg = new AcceptTransactionMessage();
			receiver->sendMessage(msg);
		}

		player->unlock();
	} catch (...) {
		player->unlock();
		System::out << "Unreported exception caught in PlayerManagerImplementation::handleAcceptTransactionMessage(Player* player)\n";
	}
}

void PlayerManagerImplementation::handleUnAcceptTransactionMessage(Player* player) {
	try {
		player->wlock();

		player->setAcceptedTrade(false);

		uint64 targID = player->getTradeRequestedPlayer();
		SceneObject* obj = server->getZoneServer()->getObject(targID);

		if (obj != NULL && obj->isPlayer()) {
			Player* receiver = (Player*)obj;

			UnAcceptTransactionMessage* msg = new UnAcceptTransactionMessage();
			receiver->sendMessage(msg);
		}

		player->unlock();
	} catch (...) {
		player->unlock();
		System::out << "Unreported exception caught in PlayerManagerImplementation::handleUnAcceptTransactionMessage(Player* player)\n";
	}
}

void PlayerManagerImplementation::handleVerifyTradeMessage(Player* player) {
	try {
		player->wlock();

		player->setVerifiedTrade(true);

		uint64 targID = player->getTradeRequestedPlayer();
		ManagedReference<SceneObject> obj = server->getZoneServer()->getObject(targID);

		if (obj != NULL && obj->isPlayer()) {
			Player* receiver = (Player*)obj.get();

			try {
				receiver->wlock(player);

				if (receiver->hasVerifiedTrade()) {
					for (int i = 0; i < player->getTradeSize(); ++i) {
						ManagedReference<SceneObject> item = player->getTradeItem(i);
						if (item->isTangible()){
							TangibleObject* tano = (TangibleObject*) item.get();
							moveItem(player, receiver, tano);
						} else {
							IntangibleObject* itno = (IntangibleObject*) item.get();
							moveItem(player, receiver, itno);
						}
					}

					for (int i = 0; i < receiver->getTradeSize(); ++i) {
						ManagedReference<SceneObject> item = receiver->getTradeItem(i);
						if (item->isTangible()){
							TangibleObject* tano = (TangibleObject*) item.get();
							moveItem(player, receiver, tano);
						} else {
							IntangibleObject* itno = (IntangibleObject*) item.get();
							moveItem(player, receiver, itno);
						}
					}

					uint32 giveMoney = player->getMoneyToTrade();

					if (giveMoney > 0) {
						player->subtractCashCredits(giveMoney);
						receiver->addCashCredits(giveMoney);
					}

					giveMoney = receiver->getMoneyToTrade();

					if (giveMoney > 0) {
						receiver->subtractCashCredits(giveMoney);
						player->addCashCredits(giveMoney);
					}

					receiver->clearTradeItems();
					receiver->setTradeRequestedPlayer(0);
					receiver->setAcceptedTrade(false);
					receiver->setVerifiedTrade(false);
					receiver->setMoneyToTrade(0);

					player->clearTradeItems();
					player->setTradeRequestedPlayer(0);
					player->setAcceptedTrade(false);
					player->setVerifiedTrade(false);
					player->setMoneyToTrade(0);

					TradeCompleteMessage* msg = new TradeCompleteMessage();
					receiver->sendMessage(msg->clone());
					player->sendMessage(msg->clone());

					delete msg;
				}

				receiver->unlock();
			} catch (...) {
				System::out << "Exception in PlayerManagerImplementation::handleVerifyTradeMessage\n";
				receiver->unlock();
			}
		}

		player->unlock();
	} catch (...) {
		player->unlock();
		System::out << "Unreported exception caught in PlayerManagerImplementation::handleVerifyTradeMessage(Player* player)\n";
	}
}

void PlayerManagerImplementation::moveItem(Player* sender, Player* receiver, TangibleObject* item) {
	// Pre: both players locked
	Inventory* recvInventory = receiver->getInventory();

	if (recvInventory->isFull()) {
		sender->sendSystemMessage("Your targets inventory is full");
		receiver->sendSystemMessage("You don't have enough space in your inventory");

		return;
	}

	ItemManager* itemManager = server->getItemManager();

	if (item->isInstrument() && sender->isPlayingMusic()) {
		receiver->sendSystemMessage("Your target can't do this right now");
		sender->sendSystemMessage("You can't do this while playing music");

		return;
	}

	item->setEquipped(false);
	sender->removeInventoryItem(item->getObjectID());

	item->sendDestroyTo(sender);

	((CreatureObject*)receiver)->addInventoryItem(item);
	item->sendTo(receiver);

	if (item->isPersistent()) {
		item->setUpdated(true);
		itemManager->savePlayerItem(receiver, item);
	}
	/*
	StringBuffer playertxt;
	StringBuffer targettxt;

	playertxt << "You gave a " << item->getName().toCharArray() << " to " << target->getFirstName() << ".";
	targettxt << getFirstName() << " gave you a " << item->getName().toCharArray() << ".";

	sendSystemMessage(playertxt.toString());
	target->sendSystemMessage(targettxt.toString());*/
}

void PlayerManagerImplementation::moveItem(Player* sender, Player* receiver, IntangibleObject* item) {
	// Pre: both players locked
	Datapad* recvDatapad = receiver->getDatapad();

	/*if (recvDatapad->isFull()) {
		sender->sendSystemMessage("Your targets datapad is full");
		receiver->sendSystemMessage("You don't have enough space in your datapad");

		return;
	}*/

	ItemManager* itemManager = server->getItemManager();

	SceneObject* scno = item->getWorldObject();

	if (scno != NULL){
		if (scno->isNonPlayerCreature()){
			Creature* creature = (Creature*) scno;
			if (creature->isMount()){
				MountCreature* mount = (MountCreature*) scno;

				//if (sender->isMounted() || sender->getMount() != NULL) { getMount() if they have it out but not riding it
				if (sender->isMounted()){
					receiver->sendSystemMessage("Your target can't do this right now");
					sender->sendSystemMessage("You can't trade mounts while mounted");

					return;
				} else{
					mount->setLinkedCreature(receiver);
					UpdateContainmentMessage* ucm = new UpdateContainmentMessage(mount, recvDatapad, 0xFFFFFFFF);
					receiver->sendMessage(ucm);
				}
			}
		}
	}

	//item->setEquipped(false);
	sender->removeDatapadItem(item->getObjectID());

	item->sendDestroyTo(sender);

	receiver->addDatapadItem((SceneObject*) item);
	item->sendTo(receiver);

	//if (item->isPersistent()) {
		//item->setUpdated(true);?
		itemManager->savePlayerDatapadItem(receiver, item);
	//}
	/*
	StringBuffer playertxt;
	StringBuffer targettxt;

	playertxt << "You gave a " << item->getName().toCharArray() << " to " << target->getFirstName() << ".";
	targettxt << getFirstName() << " gave you a " << item->getName().toCharArray() << ".";

	sendSystemMessage(playertxt.toString());
	target->sendSystemMessage(targettxt.toString());*/
}

void PlayerManagerImplementation::doBankTip(Player* sender, Player* receiver, uint32 tipAmount, bool updateTipTo) {
	//Pre: sender wlocked
	float tax = tipAmount * .05;
	StfParameter* params = new StfParameter();
	params->addDI(tipAmount);
	params->addTT(receiver->getObjectID());

	if (!sender->verifyBankCredits(tipAmount + (int) tax)) {
		sender->sendSystemMessage("base_player", "prose_tip_nsf_bank", params); //You lack the bank funds to wire %DI credits to %TT.
		delete params;
		return;
	}

	try {
		receiver->wlock(sender);

		receiver->addBankCredits(tipAmount);
		sender->subtractBankCredits(tipAmount + (int) tax);

		sender->sendSystemMessage("The Galactic Empire has collected a 5%  tax from your bank tip. This does not effect the amount recived by the other party. Thank you for your cooperation.");

		//Now we send the tipper an email.

		//This will be the same in both emails, so only declare it once.
		String mailSender;
		mailSender = "System";

		String charNameSender = sender->getFirstName();

		UnicodeString subjectSender("RECIEPT FOR BANK TIP");
		StringBuffer ss;
		ss << "You have sent a bank tip of " << tipAmount << " credits to " << receiver->getFirstName() << "." << endl;
		ss << "The Following is a summary of your charges:" << endl << endl ;
		ss << "Tip Amount: " << tipAmount << " credits" << endl;
		ss << "Imperial Tax: " << (int) tax << " credits" << endl;
		ss << endl << "Total Charges: " << (int) (tipAmount + tax) << " credits";
		UnicodeString bodySender(ss.toString());

		ChatManager* chatManager = server->getChatManager();
		chatManager->sendMail(mailSender, subjectSender, bodySender, charNameSender);

		if (updateTipTo == true) {
			//This is where we notify the other player with mail + sys message.
			//But we have to make sure they are online first. Passed in the method.
			String charNameReceiver = receiver->getFirstName();

			UnicodeString subjectReceiver("BANK TIP RECEIVED");
			StringBuffer ss2;
			ss2 << "You have received a bank tip of " << tipAmount << " credits from " << sender->getFirstName() << ".";
			UnicodeString bodyReceiver(ss2.toString());

			//Email the player you bank tipped.
			chatManager->sendMail(mailSender, subjectReceiver, bodyReceiver, charNameReceiver);
		}

		receiver->unlock();
	} catch (...) {
		System::out << "Unreported exception caught in PlayerManagerImplementation::doBankTip\n";
		receiver->unlock();
	}
}

void PlayerManagerImplementation::doCashTip(Player* sender, Player* receiver, uint32 tipAmount, bool updateTipTo) {
	// Pre: sender wlocked
	StfParameter* params = new StfParameter();
	params->addDI(tipAmount);
	params->addTT(receiver->getObjectID());
	if (!sender->verifyCashCredits(tipAmount)) {
		sender->sendSystemMessage("base_player", "prose_tip_nsf_cash", params); //You lack the cash funds to tip %DI credits to %TT.
		delete params;
		return;
	}

	try {
		receiver->wlock(sender);

		receiver->addCashCredits(tipAmount);

		sender->subtractCashCredits(tipAmount);

		sender->sendSystemMessage("base_player", "prose_tip_pass_self", params); //You successfully tip %DI credits to %TT.

		if (updateTipTo == true) {
			//This is where we notify the other player with mail + sys message.
			//But we have to make sure they are online first. Passed in the method.
			params->addTT(sender->getObjectID());
			receiver->sendSystemMessage("base_player", "prose_tip_pass_target", params);
		}

		receiver->unlock();
	} catch (...) {
		System::out << "Unreported exception caught in PlayerManagerImplementation::doCashTip\n";
		receiver->unlock();
	}

	delete params;
}

bool PlayerManagerImplementation::modifyOfflineBank(Player* sender, String receiverName, uint32 creditAmount) {
	//First we need to get the current bank credits.
	if (!sender->verifyBankCredits(creditAmount)) {
		sender->sendSystemMessage("base_player", "prose_tip_nsf_bank"); //You lack the bank funds to wire %DI credits to %TT.
		return false;
	}

	receiverName = receiverName.toLowerCase();

	MySqlDatabase::escapeString(receiverName);

	StringBuffer query;
	query << "SELECT * FROM characters WHERE lower(firstname) = '" << receiverName << "'";

	ResultSet* character;

	try {
		character = ServerDatabase::instance()->executeQuery(query);
	} catch (DatabaseException& e) {
		System::out << "PlayerManagerImplementation::modifyOfflineBank: failed SQL query: "
					<< query.toString() << "\n";

		return false;
	}

	if (!character->next()) {
		delete character;

		/*StringBuffer msg;
		msg << "unknown character name" << receiverName;
		throw Exception(msg.toString());*/

		return false;
	}

	//Grab the current credits.
	uint32 currentBankCredits = character->getInt(11);

	//we can dump it now.
	delete character;

	//Our new credits amount.
	uint32 newBankCredits = currentBankCredits + creditAmount;

	//Now we need to update the db.
	StringBuffer query2;
	query2 << "UPDATE characters SET credits_bank=" << newBankCredits
		   << " WHERE lower(firstname)='" << receiverName << "';";

	try {
		ServerDatabase::instance()->executeStatement(query2);
	} catch(DatabaseException& e) {
		System::out << "PlayerManagerImplementation::modifyOfflineBank: failed SQL UPDATE: "
					<< query2.toString() << "\n";
		return false;
	}

	//now we need to modify the online tippers credits.
	sender->subtractBankCredits(creditAmount);

	return true;
}

bool PlayerManagerImplementation::modifyRecipientOfflineBank(String recipient, uint32 creditAmount) {
	//First we need to get the current bank credits.
	recipient = recipient.toLowerCase();

	MySqlDatabase::escapeString(recipient);

	Player* play = getPlayer(recipient);

	if (play != NULL) {
		// player online. handle directly
		play->addBankCredits(creditAmount);
		return true;
	}

	StringBuffer query;
	query << "SELECT * FROM characters WHERE lower(firstname) = '" << recipient << "'";

	ResultSet* character;

	try {
		character = ServerDatabase::instance()->executeQuery(query);
	} catch(DatabaseException& e) {
		System::out << "PlayerManagerImplementation::modifyRecipientOfflineBank. Failed SQL query: "
					<< query.toString() << "\n";

		return false;
	}

	if (!character->next()) {
		delete character;

		/*StringBuffer msg;
		msg << "unknown character name (recipient)" << recipient;
		throw Exception(msg.toString());*/

		return false;
	}

	//Grab the current credits.
	uint32 currentBankCredits = character->getInt(11);

	//we can dump it now.
	delete character;

	//Our new credits amount.
	uint32 newBankCredits = currentBankCredits + creditAmount;

	//Now we need to update the db.
	StringBuffer query2;
	query2 << "UPDATE characters SET credits_bank='" << newBankCredits
		   << "' WHERE lower(firstname)='" << recipient << "'";

	try {
		ServerDatabase::instance()->executeStatement(query2);
	} catch (DatabaseException& e) {
		System::out << "PlayerManagerImplementation::modifyRecipientOfflineBank: failed SQL UPDATE: "
					<< query2.toString() << "\n";

		System::out << e.getMessage() << endl;

		return false;
	}

	return true;
}

void PlayerManagerImplementation::loadConsentList(Player* player) {
	if (player == NULL)
		return;

	StringBuffer query;

	query << "SELECT LOWER(B.firstname) AS targetName FROM consentlist A, characters B WHERE A.character_id = " << player->getCharacterID() << " AND B.character_id = A.target_id;";
	ResultSet* targetlist;

	try {
		targetlist = ServerDatabase::instance()->executeQuery(query);

		while (targetlist->next()) {
			String targetName = targetlist->getString(0);
			player->addConsentEntry(targetName);
		}

		delete targetlist;
	} catch (DatabaseException& e) {
		System::out << "ServerDatabase error retrieving consentlist for character_id: " << player->getCharacterID() << endl;
		System::out << e.getMessage();
		return;
	} catch (...) {
		System::out << "unreported exception caught in PlayerManagerImplementation::loadConsentList" << endl;
		return;
	}
}

void PlayerManagerImplementation::updateConsentList(Player* player) {
	if (player == NULL)
		return;

	//Remove all previous database entries for Consent List for this Player
	StringBuffer query;
	query << "DELETE FROM consentlist WHERE character_id = " << player->getCharacterID() << ";";

	ServerDatabase::instance()->executeStatement(query);

	int size = player->getConsentListSize();
	if (size > 0) {
		query.deleteAll();
		query << "INSERT INTO consentlist (character_id, target_id) VALUES ";

		StringBuffer insertSets;

		for (int i=0; i < size; i++) {
			insertSets << "(" << player->getCharacterID() << ",IFNULL((SELECT character_id FROM characters WHERE firstname = '" << player->getConsentEntry(i) << "'),0))";

			if (i < size - 1)
				insertSets << ",";
		}

		query << insertSets.toString() << ";";

		try {
			ServerDatabase::instance()->executeStatement(query);
		} catch (DatabaseException& e) {
			player->error(e.getMessage());
		} catch (...) {
			player->error("Unhandled exception in PlayerManagerImplementation::updateConsentList()");
		}
	}
}

void PlayerManagerImplementation::updatePlayerCreditsToDatabase(Player* player) {
	if (player == NULL)
		return;

	StringBuffer query;
	query << "UPDATE characters set credits_inv='" << player->getCashCredits()
		  << "', credits_bank='" << player->getBankCredits() << "' WHERE character_id='"
		  << player->getCharacterID() << "'";

	try {
		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException e) {
		System::out << "PlayerManagerImplementation::updatePlayerCreditsToDatabase: failed SQL update: " << query.toString() << "\n";
	}
}

void PlayerManagerImplementation::updatePlayerCreditsFromDatabase(Player* player) {
	if (player == NULL)
		return;

	try {
		player->wlock();

		StringBuffer query;

		query << "SELECT credits_inv,credits_bank FROM characters WHERE character_id = '" << player->getCharacterID() << "'";
		ResultSet* rs = NULL;

		try {
			rs = ServerDatabase::instance()->executeQuery(query);
		} catch(DatabaseException& e) {
			System::out << "PlayerManagerImplmentation::updatePlayerCredits: failed SQL query: " << query.toString() << "\n";
			System::out << e.getMessage();
			player->unlock();
			return;
		}

		if (!rs->next()) {
			player->unlock();
			delete rs;
			return;
		}

		int creditsinv = rs->getInt(0);
		int creditsbank = rs->getInt(1);

		player->setCashCredits(creditsinv);
		player->setBankCredits(creditsbank);

		BaseMessage* mess = new PlayerMoneyResponseMessage(player);
		player->sendMessage(mess);

		player->unlock();

		delete rs;
	} catch (...) {
		player->unlock();
		System::out << "unreported exception caught in PlayerManager::updatePlayerCreditsFromDatabase\n";
	}
}

void PlayerManagerImplementation::updatePlayerAppearanceToDatabase(Player* player) {
	if (player == NULL)
		return;

	String appearance;
	String playApp;
	player->getCustomizationString(playApp);
	BinaryData cust(playApp);
	cust.encode(appearance);

	String hairdata;
	String hairApp;
	player->getHairAppearance(hairApp);
	BinaryData hair(hairApp);
	hair.encode(hairdata);

	StringBuffer query;

	query << "UPDATE characters set appearance='" << appearance.subString(0, appearance.length() - 1)
		  << "', hair='" << player->getHairObject()
		  << "', hairData='" << hairdata.subString(0, hairdata.length() - 1) << "' "
		  << " WHERE character_id = " << player->getCharacterID();

	try {
		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		System::out << "PlayerManagerImplementation::updatePlayerAppearanceToDatabase: failed SQL update: "
					<< query.toString() << "\n";

		System::out << e.getMessage();
	}
}

void PlayerManagerImplementation::updatePlayerBaseHAMToDatabase(Player* player) {
	if (player == NULL)
		return;

	StringBuffer query;
	query << "UPDATE characters set "
		  << "`health` = " << player->getBaseHealth()
		  << ",`strength` = " << player->getBaseStrength()
		  << ",`constitution` = " << player->getBaseConstitution()
		  << ",`action` = " << player->getBaseAction()
		  << ",`quickness` = " << player->getBaseQuickness()
		  << ",`stamina` = " << player->getBaseStamina()
		  << ",`mind` = " << player->getBaseMind()
		  << ",`focus` = " << player->getBaseFocus()
		  << ",`willpower` = " << player->getBaseWillpower()
		  << " WHERE character_id = " << player->getCharacterID();

	try {
		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		System::out << "PlayerManagerImplementation::updatePlayerBaseHAMToDatabase: failed SQL update: "
					<< query.toString() << "\n";

		System::out << e.getMessage();
	}
}
