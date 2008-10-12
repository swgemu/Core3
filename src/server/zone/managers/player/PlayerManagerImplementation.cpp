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

	player->setZoneIndex(5);
	player->setTerrainName(Terrain::getTerrainName(5));

	player->initializePosition(-4908.0f, 6, 4101.0f);

	player->randomizePosition(45);

	int race = Races::getRaceID(player->getRaceFileName());

	player->setObjectCRC(Races::getRaceCRC(race));
	player->setRaceName(Races::getRace(race));
	player->setSpeciesName(Races::getSpecies(race));
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

	string bio = player->getBiography().c_str();
	MySqlDatabase::escapeString(bio);
	string info = "";

	string appearance;
	string playApp;
	player->getCharacterAppearance(playApp);
	BinaryData cust(playApp);
	cust.encode(appearance);

	string hairdata;
	string hairApp;
	player->getHairAppearance(hairApp);
	BinaryData hair(hairApp);
	hair.encode(hairdata);

	player->createBaseStats();

	//Set players HAM stats so they are not default(3k).
	player->resetHAMBars(false);

	try {
		stringstream query;
		query << "INSERT INTO `characters` "
		<< "(`account_id`,`galaxy_id`,`firstname`,`surname`,"
		<< "`appearance`,`professions`,`race`,`gender`,`lots`,"
		<< "`credits_inv`,`credits_bank`,`guild`,`x`,`y`,`z`,`zoneid`,`planet_id`,"
		<< "`lfg`,`helper`,`roleplayer`,`faction_id`,`archived`,`scale`,`biography`,"
		<< "`infofield`,`hair`,`hairData`,`playermodel`,`CRC`,`Title`,"
		<< "`health`,`strength`,`constitution`,"
		<< "`action`,`quickness`,`stamina`,"
		<< "`mind`,`focus`,`willpower`,"
		<< "`PvpRating`, adminLevel"
		<< ") VALUES ("
		<< accountID << "," << galaxyID << ",'"
		<< player->getFirstName() << "','" << player->getLastName() << "','"
		<< appearance.substr(0, appearance.size() - 1) << "','"
		<< player->getStartingProfession() << "'," <<  race << "," << gender << ",10,"
		<< creditsCash << "," << creditsBank << ",0,"
		<< player->getPositionX() << "," << player->getPositionY() << ","
		<< player->getPositionZ() << "," << player->getZoneIndex() << "," << 0//planetID
		<< ",0,0,0,0,0," << player->getHeight() << ","
		<< "'" << bio << "','" << info << "','"
		<< player->getHairObject() << "','" << hairdata.substr(0, hairdata.size() - 1) << "','', '0','',"
		<< player->getBaseHealth() << "," << player->getBaseStrength() << "," << player->getBaseConstitution() << ","
		<< player->getBaseAction() << "," << player->getBaseQuickness() << "," << player->getBaseStamina() << ","
		<< player->getBaseMind() << "," << player->getBaseFocus() << "," << player->getBaseWillpower() << ","
		<< player->getPvpRating() << "," << player->getAdminLevel() << ")";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

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

BaseMessage* PlayerManagerImplementation::checkPlayerName(const string& name, const string& species) {
	NameManager * nm = server->getNameManager();
	BaseMessage* msg = NULL;

	string firstName;
	int idx = name.find(" ");

	if (idx != string::npos)
		firstName = name.substr(0, idx);
	else
		firstName = name.c_str();

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
			player->createItems();
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
		stringstream err;
		err << "unreported exception on PlayerManagerImplementation::attemptPlayerCreation()\n" << e.getMessage() << "\n";
		player->error(err.str());
		player->unlock();
		return new ClientCreateCharacterFailed("name_declined_internal_error"); //something went wrong
	} catch (...) {
		stringstream err;
		err << "unreported exception on PlayerManagerImplementation::attemptPlayerCreation()\n";
		player->error(err.str());
		player->unlock();
		return new ClientCreateCharacterFailed("name_declined_internal_error"); //something went wrong
	}
}

bool PlayerManagerImplementation::validateName(const string& cname) {
	if (cname.size() < 1)
		return false;

	string name = cname;
	String::toLower(name);
	try {
		string query = "SELECT * FROM characters WHERE lower(firstname) = \"" + name + "\"";

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
	player->setZoneProcessServer(server);

	loadFromDatabase(player);

	playerMap->put(player->getFirstName(), player);

	return player;
}

void PlayerManagerImplementation::loadFromDatabase(Player* player) {
	ResultSet* character;

	stringstream query;
	query << "SELECT * FROM characters WHERE character_id = " << player->getCharacterID();

	character = ServerDatabase::instance()->executeQuery(query);

	if (!character->next()) {
		stringstream msg;
		msg << "unknown character ID" << player->getCharacterID();

		throw Exception(msg.str());
	}

	player->setFirstName(character->getString(3));
	player->setLastName(character->getString(4));

	string orbname = "Player " + player->getFirstName();
	player->deploy(orbname);

	PlayerObject* playerObject = new PlayerObject(player);

	player->setPlayerObject(playerObject);

	if (player->getLastName() != "")
		player->setCharacterName(player->getFirstName() + " " + player->getLastName());
	else
		player->setCharacterName(player->getFirstName());

	player->setFirstNameProper(player->getFirstName());
	String::toLower(player->getFirstName());

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


	string appearance = character->getString(5);
	BinaryData cust(appearance);
	string custStr;
	cust.decode(custStr);
	player->setCharacterAppearance(custStr);

	string hairData = character->getString(28);
	BinaryData hair(hairData);
	string hData;
	hair.decode(hData);
	player->setHairAppearance(hData);

	int raceID = character->getInt(7);

	player->setRaceID(raceID);
	player->setObjectCRC(Races::getRaceCRC(raceID));
	player->setRaceName(Races::getRace(raceID));
	player->setSpeciesName(Races::getSpecies(raceID));
	player->setGender(Races::getGender(raceID));
	player->setHairObject(character->getString(27));

	player->setFaction(character->getUnsignedInt(21));

	player->setHeight(character->getFloat(23));

	player->setCashCredits(character->getInt(10));
	player->setBankCredits(character->getInt(11));

	//location = character->getString(5);
	player->setStartingProfession(character->getString(6));

	player->setItemShift(character->getUnsignedInt(34));

	string bio = character->getString(24);
	player->setBiography(bio);

	string title = character->getString(32);
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

	PlanetManager* planetManager = zne->getPlanetManager();
	SceneObject* parent = planetManager->getCell(character->getUnsignedLong(33));

	if (parent != NULL)
		player->setParent(parent, 0xFFFFFFFF);

	loadWaypoints(player);

	player->setPvpRating(character->getInt(54));
	player->setAdminLevel(character->getInt(55));

	player->setFactionStatus(character->getInt(58));
	player->setFactionRank(character->getInt(59));

	//Load consent list from database
	loadConsentList(player);
	loadFactionPoints(player);
	delete character;
}

void PlayerManagerImplementation::loadWaypoints(Player* player) {
	stringstream query;
	ResultSet* result = NULL;

	query << "SELECT * FROM waypoints WHERE owner_id = '" << player->getCharacterID() <<"';";

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			string wpName = result->getString(2);

			float x = result->getFloat(3);
			float y = result->getFloat(4);

			string planetName = result->getString(5);
			string internalNote = result->getString(7);
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
		cout << e.getMessage() << endl;
	} catch (...) {
		cout << "unreported exception caught in PlayerManagerImplementation::loadWaypoints\n";
	}

	delete result;
}

void PlayerManagerImplementation::updateGuildStatus(Player* player) {
	//This function makes sure, that a player, which was removed from a guild while being offline,
	//is not re-inserted as a guildmember again on loading from cache

	player->info("Entering PlayerManagerImplementation::updateGuildStatus(Player* player)");

	ResultSet* character;
	stringstream query;

	try {
		query << "SELECT guild FROM characters WHERE character_id = " << player->getCharacterID();

		character = ServerDatabase::instance()->executeQuery(query);

	} catch (DatabaseException& e) {
		cout << "DB Exception in PlayerManagerImplementation::updateGuildStatus(Player* player):" << endl << e.getMessage() << endl;
		player->info("DB ERROR: Catch #1 from PlayerManagerImplementation::updateGuildStatus(Player* player)");

		return;

	} catch (...) {
		cout << "unreported exception caught in PlayerManagerImplementation::updateGuildStatus\n";
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
					cout << "DEFAULT guild in table GUILDS (DB) is not ID 0 ! Edit table and set DEFAULT GUILD to ID 0!\n";

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
	/*player->unlock();

	Player* playerToInform = NULL;
	PlayerObject* toInformObject = NULL;

	try {
		player->info("Entering PlayerManagerImplementation::updateOtherFriendlists(Player* player, bool status)");

		string loggingInName = player->getFirstName();
		String::toLower(loggingInName);

		playerMap->lock();

		playerMap->resetIterator(false);

		while (playerMap->hasNext(false)) {
			playerToInform = playerMap->next(false);

			if (playerToInform == player)
				continue;

			try {
				playerToInform->wlock(playerMap);

				toInformObject = playerToInform->getPlayerObject();

				if (toInformObject != NULL) {
					for (int i = 0; i < toInformObject->getFriendsList()->getCount(); ++i) {
						if (toInformObject->getFriendsList()->getFriendsName(i) == loggingInName) {

							if (playerToInform->isOnline()) {
								FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(loggingInName, "Core3", status);
								playerToInform->sendMessage(notifyStatus);
								break;
							}

						}
					}
				}

				playerToInform->unlock();
			} catch (...) {
				playerToInform->error("unreported exception caught in PlayerManagerImplementation::updateOtherFriendlists");
				playerToInform->unlock();
			}

		}

		playerMap->unlock();
	} catch (...) {
		player->error("Unreported exception in PlayerManagerImplementation::updateOtherFriendlists(Player* player, bool status)");

		playerMap->unlock();
	}

	player->info("Clean exit from PlayerManagerImplementation::updateOtherFriendlists(Player* player, bool status)");
	player->wlock();*/
}

void PlayerManagerImplementation::unload(Player* player) {
	save(player);

	playerMap->remove(player->getFirstName());
}

void PlayerManagerImplementation::save(Player* player) {
	string biography = player->getBiography().c_str();
	MySqlDatabase::escapeString(biography);

	stringstream query;
	query << "UPDATE characters SET x=" << player->getPositionX() << ",y=" << player->getPositionY()
	<< ",z=" << player->getPositionZ()
	<< ",zoneid=" << player->getZoneIndex()
	<< ",faction_id=" << player->getFaction()
	<< ",biography=\'" << biography << "\'"
	<< ",Title=" << "'" << player->getPlayerObject()->getCurrentTitle() << "'"
	<< ",Guild=" << "'" << player->getGuildID() << "'"
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
	<< ",factionRank=" << (int)player->getFactionRank()
	<< " WHERE character_id=" << player->getCharacterID() << ";";
	try {
		ServerDatabase::instance()->executeStatement(query);
	} catch(DatabaseException& e) {
		cerr << "Failed to unload character: " << player->getFirstName() << "\n";
		cout << e.getMessage() << endl;
	}

	player->saveProfessions();
	saveFactionPoints(player);

	//Update the database with the consentlist info
	updateConsentList(player);
}

void PlayerManagerImplementation::loadFactionPoints(Player* player) {
	stringstream query;
	query << "SELECT * FROM character_faction_points WHERE character_id = " << player->getCharacterID() << ";";
	try {
		ResultSet * res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			string faction = res->getString(1);
			int points = res->getInt(2);

			if (points >= 0)
				player->addFactionPoints(faction, points);
			else
				player->subtractFactionPoints(faction, abs(points));
		}

		delete res;
	} catch(DatabaseException& e) {
		cerr << "Failed to load FactionPoints: " << player->getFirstName() << endl;
		cout << e.getMessage() << endl;
	}
}

void PlayerManagerImplementation::saveFactionPoints(Player* player) {

	FactionPointList * list = player->getFactionList();

	try {
		for (int i = 0; i < list->size(); i++) {
			string faction = list->get(i);
			int points = player->getFactionPoints(faction);
			stringstream hash;
			hash << faction << player->getCharacterID();
			stringstream query;
			query << "INSERT INTO character_faction_points VALUES(";
			query << player->getCharacterID() << ", '";
			query << faction << "', " << points << ", MD5('";
			query << hash.str() << "')) ON DUPLICATE KEY UPDATE faction_points = " << points;

			ServerDatabase::instance()->executeStatement(query);
		}

	} catch(DatabaseException& e) {
		cerr << "Failed to save FactionPoints: " << player->getFirstName() << endl;
		cout << e.getMessage() << endl;
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
		cout << "Unreported exception caught in PlayerManagerImplementation::handleAbortTradeMessage(Player* player)\n";
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
		cout << "Unreported exception caught in PlayerManagerImplementation::handleAcceptTransactionMessage(Player* player)\n";
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
		cout << "Unreported exception caught in PlayerManagerImplementation::handleUnAcceptTransactionMessage(Player* player)\n";
	}
}

void PlayerManagerImplementation::handleVerifyTradeMessage(Player* player) {
	try {
		player->wlock();

		player->setVerifiedTrade(true);

		uint64 targID = player->getTradeRequestedPlayer();
		SceneObject* obj = server->getZoneServer()->getObject(targID);

		if (obj != NULL && obj->isPlayer()) {
			Player* receiver = (Player*)obj;

			try {
				receiver->wlock(player);

				if (receiver->hasVerifiedTrade()) {
					for (int i = 0; i < player->getTradeSize(); ++i) {
						TangibleObject* item = player->getTradeItem(i);
						moveItem(player, receiver, item);
					}

					for (int i = 0; i < receiver->getTradeSize(); ++i) {
						TangibleObject* item = receiver->getTradeItem(i);
						moveItem(receiver, player, item);
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
				cout << "Excepion in PlayerManagerImplementation::handleVerifyTradeMessage\n";
				receiver->unlock();
			}
		}

		player->unlock();
	} catch (...) {
		player->unlock();
		cout << "Unreported exception caught in PlayerManagerImplementation::handleVerifyTradeMessage(Player* player)\n";
	}
}

void PlayerManagerImplementation::moveItem(Player* sender, Player* receiver, TangibleObject* item) {
	// Pre: both players locked
	Inventory* recvInventory = receiver->getInventory();

	if (recvInventory->isFull()) {
		sender->sendSystemMessage("Your targets inventory is full");
		receiver->sendSystemMessage("You dont have enough space in your inventory");

		return;
	}

	ItemManager* itemManager = server->getItemManager();

	if (item->isInstrument() && sender->isPlayingMusic()) {
		receiver->sendSystemMessage("Your target cant do this right now");
		sender->sendSystemMessage("You cant do this while playing music");

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
	stringstream playertxt;
	stringstream targettxt;

	playertxt << "You gave a " << item->getName().c_str() << " to " << target->getFirstName() << ".";
	targettxt << getFirstName() << " gave you a " << item->getName().c_str() << ".";

	sendSystemMessage(playertxt.str());
	target->sendSystemMessage(targettxt.str());*/
}

void PlayerManagerImplementation::doBankTip(Player* sender, Player* receiver, uint32 tipAmount, bool updateTipTo) {
	//Pre: sender wlocked
	float tax = tipAmount * .05;

	if (!sender->verifyBankCredits(tipAmount + (int) tax)) {
		sender->sendSystemMessage("You lack the required funds to do that. (Bank Tip.)");
		return;
	}

	try {
		receiver->wlock(sender);

		receiver->addBankCredits(tipAmount);
		sender->subtractBankCredits(tipAmount + (int) tax);

		sender->sendSystemMessage("The Galactic Empire has collected a 5%  tax from your bank tip. This does not effect the amount recived by the other party. Thank you for your cooperation.");

		//Now we send the tipper an email.

		//This will be the same in both emails, so only declare it once.
		string mailSender;
		mailSender = "System";

		string charNameSender = sender->getFirstName();

		unicode subjectSender("RECIEPT FOR BANK TIP");
		stringstream ss;
		ss << "You have sent a bank tip of " << tipAmount << " credits to " << receiver->getFirstName() << "." << endl;
		ss << "The Following is a summary of your charges:" << endl << endl ;
		ss << "Tip Amount: " << tipAmount << " credits" << endl;
		ss << "Imperial Tax: " << (int) tax << " credits" << endl;
		ss << endl << "Total Charges: " << (int) (tipAmount + tax) << " credits";
		unicode bodySender(ss.str());

		ChatManager* chatManager = server->getChatManager();
		chatManager->sendMail(mailSender, subjectSender, bodySender, charNameSender);

		if (updateTipTo == true) {
			//This is where we notify the other player with mail + sys message.
			//But we have to make sure they are online first. Passed in the method.
			string charNameReceiver = receiver->getFirstName();

			unicode subjectReceiver("BANK TIP RECEIVED");
			stringstream ss2;
			ss2 << "You have received a bank tip of " << tipAmount << " credits from " << sender->getFirstName() << ".";
			unicode bodyReceiver(ss2.str());

			//Email the player you bank tipped.
			chatManager->sendMail(mailSender, subjectReceiver, bodyReceiver, charNameReceiver);
		}

		receiver->unlock();
	} catch (...) {
		cout << "Unreported exception caught in PlayerManagerImplementation::doBankTip\n";
		receiver->unlock();
	}
}

void PlayerManagerImplementation::doCashTip(Player* sender, Player* receiver, uint32 tipAmount, bool updateTipTo) {
	// Pre: sender wlocked
	if (!sender->verifyCashCredits(tipAmount)) {
		sender->sendSystemMessage("You lack the required funds to do that. (Cash Tip.)");
		return;
	}

	try {
		receiver->wlock(sender);

		receiver->addCashCredits(tipAmount);

		sender->subtractCashCredits(tipAmount);
		sender->sendSystemMessage("You have successfully cash tipped.");

		if (updateTipTo == true) {
			//This is where we notify the other player with mail + sys message.
			//But we have to make sure they are online first. Passed in the method.
			stringstream ss;
			ss << "You have been tipped " << tipAmount << " credits by " << sender->getFirstName() << ".";
			receiver->sendSystemMessage(ss.str());
		}

		receiver->unlock();
	} catch (...) {
		cout << "Unreported exception caught in PlayerManagerImplementation::doCashTip\n";
		receiver->unlock();
	}
}

bool PlayerManagerImplementation::modifyOfflineBank(Player* sender, string receiverName, uint32 creditAmount) {
	//First we need to get the current bank credits.
	if (!sender->verifyBankCredits(creditAmount)) {
		sender->sendSystemMessage("You lack the required funds to do that. (Bank Tip.)");
		return false;
	}

	String::toLower(receiverName);
	MySqlDatabase::escapeString(receiverName);

	stringstream query;
	query << "SELECT * FROM characters WHERE lower(firstname) = '" << receiverName << "'";
	ResultSet* character;

	try {
		character = ServerDatabase::instance()->executeQuery(query);
	} catch (DatabaseException& e) {
		cout << "PlayerManagerImplementation::modifyOfflineBank: failed SQL query: " << query << "\n";
		return false;
	}

	if (!character->next()) {
		delete character;
		/*stringstream msg;
		msg << "unknown character name" << receiverName;
		throw Exception(msg.str());*/
		return false;
	}

	//Grab the current credits.
	uint32 currentBankCredits = character->getInt(11);

	//we can dump it now.
	delete character;

	//Our new credits amount.
	uint32 newBankCredits = currentBankCredits + creditAmount;

	//Now we need to update the db.
	stringstream query2;
	query2 << "UPDATE characters SET credits_bank=" << newBankCredits
	<< " WHERE lower(firstname)='" << receiverName << "';";

	try {
		ServerDatabase::instance()->executeStatement(query2);
	} catch(DatabaseException& e) {
		cout << "PlayerManagerImplementation::modifyOfflineBank: failed SQL UPDATE: " << query2 << "\n";
		return false;
	}

	//now we need to modify the online tippers credits.
	sender->subtractBankCredits(creditAmount);

	return true;
}

bool PlayerManagerImplementation::modifyRecipientOfflineBank(string recipient, uint32 creditAmount) {
	//First we need to get the current bank credits.
	String::toLower(recipient);
	MySqlDatabase::escapeString(recipient);

	Player* play = getPlayer(recipient);

	if (play != NULL) {
		// player online. handle directly
		play->addBankCredits(creditAmount);
		return true;
	}

	stringstream query;
	query << "SELECT * FROM characters WHERE lower(firstname) = '" << recipient << "'";
	ResultSet* character;

	try {
		character = ServerDatabase::instance()->executeQuery(query);
	} catch(DatabaseException& e) {
		cout << "PlayerManagerImplementation::modifyRecipientOfflineBank. Failed SQL query: " << query << "\n";
		return false;
	}

	if (!character->next()) {
		delete character;
		/*stringstream msg;
		msg << "unknown character name (recipient)" << recipient;
		throw Exception(msg.str());*/
		return false;
	}

	//Grab the current credits.
	uint32 currentBankCredits = character->getInt(11);

	//we can dump it now.
	delete character;

	//Our new credits amount.
	uint32 newBankCredits = currentBankCredits + creditAmount;

	//Now we need to update the db.
	stringstream query2;
	query2 << "UPDATE characters SET credits_bank='" << newBankCredits
	<< "' WHERE lower(firstname)='" << recipient << "'";

	try {
		ServerDatabase::instance()->executeStatement(query2);
	} catch (DatabaseException& e) {
		cout << "PlayerManagerImplementation::modifyRecipientOfflineBank: failed SQL UPDATE: " << query2.str() << "\n";
		cout << e.getMessage() << endl;
		return false;
	}

	return true;
}

void PlayerManagerImplementation::loadConsentList(Player* player) {
	if (player == NULL)
		return;

	stringstream query;

	query << "SELECT LOWER(B.firstname) AS targetName FROM consentlist A, characters B WHERE A.character_id = " << player->getCharacterID() << " AND B.character_id = A.target_id;";
	ResultSet* targetlist;

	try {
		targetlist = ServerDatabase::instance()->executeQuery(query);

		while (targetlist->next()) {
			string targetName = targetlist->getString(0);
			player->giveConsent(targetName);
		}

		delete targetlist;
	} catch (DatabaseException& e) {
		cout << "ServerDatabase error retrieving consentlist for character_id: " << player->getCharacterID() << endl;
		cout << e.getMessage();
		return;
	} catch (...) {
		cout << "unreported exception caught in PlayerManagerImplementation::loadConsentList" << endl;
		return;
	}
}

void PlayerManagerImplementation::updateConsentList(Player* player) {
	if (player == NULL)
		return;

	//Remove all previous database entries for Consent List for this Player
	stringstream query;
	query << "DELETE FROM consentlist WHERE character_id = " << player->getCharacterID() << ";";
	ServerDatabase::instance()->executeStatement(query);

	int size = player->getConsentSize();

	if (size > 0) {
		query.str("");
		query << "INSERT INTO consentlist (character_id, target_id) VALUES ";

		stringstream insertSets;

		for (int i=0; i < size; i++) {
			insertSets << "(" << player->getCharacterID() << ",IFNULL((SELECT character_id FROM characters WHERE firstname = '" << player->getConsentEntry(i) << "'),0))";
			if (i < size - 1)
				insertSets << ",";
		}

		query << insertSets.str() << ";";

		try {
			ServerDatabase::instance()->executeStatement(query);
		} catch (DatabaseException& e) {
			cout << e.getMessage() << endl;
			player->error(e.getMessage());
		} catch (...) {
			cout << "Unhandled exception in PlayerManagerImplementation::updateConsentList()" << endl;
			player->error("Unhandled exception in PlayerManagerImplementation::updateConsentList()");
		}
	}
}

void PlayerManagerImplementation::updatePlayerCreditsToDatabase(Player* player) {
	if (player == NULL)
		return;

	stringstream query;

	query << "UPDATE characters set credits_inv='" << player->getCashCredits() <<
	"', credits_bank='" << player->getBankCredits() << "' WHERE character_id='" <<
	player->getCharacterID() << "'";

	try {
		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException e) {
		cout << "PlayerManagerImplementation::updatePlayerCreditsToDatabase: failed SQL update: " << query.str() << "\n";
	}
}

void PlayerManagerImplementation::updatePlayerCreditsFromDatabase(Player* player) {
	if (player == NULL)
		return;

	try {
		player->wlock();

		stringstream query;

		query << "SELECT credits_inv,credits_bank FROM characters WHERE character_id = '" << player->getCharacterID() << "'";
		ResultSet* rs = NULL;

		try {
			rs = ServerDatabase::instance()->executeQuery(query);
		} catch(DatabaseException& e) {
			cout << "PlayerManagerImplmentation::updatePlayerCredits: failed SQL query: " << query.str() << "\n";
			cout << e.getMessage();
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
		cout << "unreported exception caught in PlayerManager::updatePlayerCreditsFromDatabase\n";
	}
}

void PlayerManagerImplementation::updatePlayerAppearanceToDatabase(Player* player) {
	if (player == NULL)
		return;

	string appearance;
	string playApp;
	player->getCharacterAppearance(playApp);
	BinaryData cust(playApp);
	cust.encode(appearance);

	string hairdata;
	string hairApp;
	player->getHairAppearance(hairApp);
	BinaryData hair(hairApp);
	hair.encode(hairdata);

	stringstream query;

	query	<< "UPDATE characters set appearance='" << appearance.substr(0, appearance.size() - 1)
	<< "', hair='" << player->getHairObject()
	<< "', hairData='" << hairdata.substr(0, hairdata.size() - 1) << "' "
	<< " WHERE character_id = " << player->getCharacterID();

	try {
		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		cout << "PlayerManagerImplementation::updatePlayerAppearanceToDatabase: failed SQL update: " << query.str() << "\n";
		cout << e.getMessage();
	}
}

void PlayerManagerImplementation::updatePlayerBaseHAMToDatabase(Player* player) {
	if (player == NULL)
		return;

	stringstream query;

	query	<< "UPDATE characters set "
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
		cout << "PlayerManagerImplementation::updatePlayerBaseHAMToDatabase: failed SQL update: " << query.str() << "\n";
		cout << e.getMessage();
	}
}
