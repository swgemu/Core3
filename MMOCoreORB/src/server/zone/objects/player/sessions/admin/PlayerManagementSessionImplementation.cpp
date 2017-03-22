/*
 * PlayerManagementSession.cpp
 *
 *  Created on: April 30, 2012
 *      Author: Kyle
 */

#include "server/zone/objects/player/sessions/admin/PlayerManagementSession.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/sui/PlayerManagementSessionSuiCallback.h"
#include "server/zone/ZoneServer.h"
#include "server/login/account/Account.h"

int PlayerManagementSessionImplementation::initializeSession() {
	ManagedReference<CreatureObject*> admin = this->admin.get();

	if (admin == NULL)
		return cancelSession();

	playerManager = admin->getZoneServer()->getPlayerManager();

	if (targetAccount == NULL)
		return cancelSession();

	return 0;
}

int PlayerManagementSessionImplementation::clearSession() {
	ManagedReference<CreatureObject*> admin = this->admin.get();

	if (admin != NULL) {
		Reference<PlayerObject*> ghost = admin->getPlayerObject();

		if (ghost != NULL) {
			if (accountBox != NULL) {
				if (ghost->hasSuiBox(accountBox->getBoxID())) {
					admin->sendMessage(accountBox->generateCloseMessage());
				}
			}

			if (durationBox != NULL) {
				if (ghost->hasSuiBox(durationBox->getBoxID())) {
					admin->sendMessage(durationBox->generateCloseMessage());
				}
			}

			if (reasonBox != NULL) {
				if (ghost->hasSuiBox(reasonBox->getBoxID())) {
					admin->sendMessage(reasonBox->generateCloseMessage());
				}
			}

			if (summaryBox != NULL) {
				if (ghost->hasSuiBox(summaryBox->getBoxID())) {
					admin->sendMessage(summaryBox->generateCloseMessage());
				}
			}

			if (unbanSummaryBox != NULL) {
				if (ghost->hasSuiBox(unbanSummaryBox->getBoxID())) {
					admin->sendMessage(unbanSummaryBox->generateCloseMessage());
				}
			}
		}

		this->admin = NULL;
	}

	return 0;
}

void PlayerManagementSessionImplementation::ban(const int tablevel, const uint32 galaxy, const String& gname, const String& name) {

	sendAccountInfo();

	banMode = NONE;
	banType = NONE;
	galaxyID = 0;
	galaxyName = gname;
	banExpiration = 0;
	banReason = "";
	targetName = "";

	Locker alocker(targetAccount);

	//Account Ban
	if (tablevel == 0) {

		banMode = ACCOUNT;
		if (targetAccount->isBanned()) {
			sendBanReason(true);
			banType = UNBAN;
		} else {
			sendBanDuration();
			banType = BAN;
		}

	} else if (tablevel == 1) {

		if (galaxy != 0) {
			banMode = GALAXY;
			galaxyID = galaxy;
			GalaxyBanEntry* galaxyBan = targetAccount->getGalaxyBan(galaxy);
			if (galaxyBan != NULL) {
				sendBanReason(true);
				banType = UNBAN;
			}
			else {
				sendBanDuration();
				banType = BAN;
			}
		}

	} else if (tablevel == 2) {

		if (!name.isEmpty()) {
			banMode = CHARACTER;
			galaxyID = galaxy;
			targetName = name;
			CharacterListEntry* entry = targetAccount->getCharacterBan(galaxy, name);
			if(entry != NULL) {
				sendBanReason(true);
				banType = UNBAN;
			} else {
				sendBanDuration();
				banType = BAN;
			}
		}
	}
}

void PlayerManagementSessionImplementation::getPlayerInfo(const int tablevel, const String& firstName) {
	ManagedReference<CreatureObject*> admin = this->admin.get();

	if (admin == NULL)
		return;

	sendAccountInfo();
	banMode = NONE;

	if (tablevel != 2)
		return;

	ManagedReference<CreatureObject*> targetPlayer = NULL;

	if (!firstName.isEmpty())
		targetPlayer = playerManager->getPlayer(firstName);

	if (targetPlayer == NULL) {
		return;
	}

	admin->sendCommand(STRING_HASHCODE("server"), "playerinfo " + firstName);
}

void PlayerManagementSessionImplementation::sendAccountInfo() {
	ManagedReference<CreatureObject*> admin = this->admin.get();

	if (admin == NULL || accountBox == NULL)
		return;

	Reference<PlayerObject*> ghost = admin->getPlayerObject();

	if (ghost == NULL)
		return;

	admin->sendMessage(accountBox->generateCloseMessage());
	ghost->addSuiBox(accountBox);
	admin->sendMessage(accountBox->generateMessage());
}

void PlayerManagementSessionImplementation::sendBanDuration() {
	ManagedReference<CreatureObject*> admin = this->admin.get();

	if (admin == NULL || accountBox == NULL)
		return;

	Reference<PlayerObject*> ghost = admin->getPlayerObject();

	if (ghost == NULL)
		return;

	if (!ghost->hasSuiBox(accountBox->getBoxID()))
		sendAccountInfo();

	if (durationBox == NULL) {
		durationBox = new SuiInputBox(admin, SuiWindowType::ADMIN_BAN_DURATION);
		durationBox->setPromptTitle("ENTER BAN DURATION");
		durationBox->setPromptText("Enter the duration of ban in years, months, days, hours, minutes\n\nEx: 1y 2m 3d 4h 5M");
		durationBox->setUsingObject(admin);
		durationBox->setCallback(new PlayerManagementSessionSuiCallback(admin->getZoneServer()));
	}

	ghost->addSuiBox(durationBox);
	admin->sendMessage(durationBox->generateMessage());
}

void PlayerManagementSessionImplementation::parseBanDuration(const String& duration) {

	StringTokenizer tokenizer(duration);
	int durationInSeconds = 0;

	try {

		while(tokenizer.hasMoreTokens()) {
			String token;
			tokenizer.getStringToken(token);

			if(token.length() < 2)
				throw Exception();

			char timeframe = token.charAt(token.length() - 1);
			token = token.subString(0, token.length() - 1);
			int units = Integer::valueOf(token);
			int seconds = 0;

			switch(timeframe) {
			case 'y':
				seconds = 60 * 60 * 24 * 365;
				break;
			case 'm':
				seconds = 60 * 60 * 24 * 30;
				break;
			case 'd':
				seconds = 60 * 60 * 24;
				break;
			case 'h':
				seconds = 60 * 60;
				break;
			case 'M':
				seconds = 60;
				break;
			default:
				throw Exception();
				break;
			}

			durationInSeconds += (units * seconds);
		}

		banExpiration = durationInSeconds + time(0);

		if(banReason.isEmpty())
			sendBanReason();
		else
			showBanSummary();

	} catch(Exception& e) {
		sendBanDuration();
	}
}

void PlayerManagementSessionImplementation::sendBanReason(bool unban) {
	ManagedReference<CreatureObject*> admin = this->admin.get();

	if (admin == NULL || accountBox == NULL)
		return;

	Reference<PlayerObject*> ghost = admin->getPlayerObject();

	if (ghost == NULL)
		return;

	if (!ghost->hasSuiBox(accountBox->getBoxID()))
		sendAccountInfo();

	if (reasonBox == NULL) {
		reasonBox = new SuiInputBox(admin, SuiWindowType::ADMIN_BAN_REASON);
		reasonBox->setUsingObject(admin);
		reasonBox->setCallback(new PlayerManagementSessionSuiCallback(admin->getZoneServer()));
	}

	if (unban) {
		reasonBox->setPromptTitle("ENTER UNBAN REASON");
		reasonBox->setPromptText("Enter the reason for unbanning");
	} else {
		reasonBox->setPromptTitle("ENTER BAN REASON");
		reasonBox->setPromptText("Enter the reason for the ban");

	}

	ghost->addSuiBox(reasonBox);
	admin->sendMessage(reasonBox->generateMessage());
}

void PlayerManagementSessionImplementation::setBanReason(const String& reason) {
	banReason = reason;

	Database::escapeString(banReason);

	if (reason.isEmpty()) {
		sendBanReason(banType == UNBAN);
		return;
	}

	if (banType == BAN)
		showBanSummary();
	else
		showUnbanSummary();
}

void PlayerManagementSessionImplementation::showBanSummary() {
	ManagedReference<CreatureObject*> admin = this->admin.get();

	if (admin == NULL)
		return;

	Reference<PlayerObject*> ghost = admin->getPlayerObject();

	if (ghost == NULL)
		return;

	Locker alocker(targetAccount);

	if (summaryBox == NULL) {
		summaryBox = new SuiListBox(admin, SuiWindowType::ADMIN_BAN_SUMMARY);

		summaryBox->setOkButton(true, "@ok");
		summaryBox->setCancelButton(true, "@cancel");
		summaryBox->setCallback(new PlayerManagementSessionSuiCallback(admin->getZoneServer()));
		summaryBox->setUsingObject(admin);

		summaryBox->setPromptTitle("Ban Summary");

		summaryBox->addMenuItem("Change Duration", 0);
		summaryBox->addMenuItem("Change Reason", 0);
		summaryBox->addMenuItem("\\#FF0000Complete Ban", 0);
	}


	StringBuffer summary;
	summary << "Banning ";
	if (banMode == ACCOUNT && targetAccount != NULL)
		summary << " Account: " << targetAccount->getUsername() <<  endl;
	else if (banMode == GALAXY && galaxyID != 0)
		summary << " From " << galaxyName << " Galaxy" <<  endl;
	else if (banMode == CHARACTER && !targetName.isEmpty())
		summary << " Character: " << targetName <<  endl;

	summary << getBanDuration(banExpiration) << endl;
	summary << "Ban Reason: "<< banReason << endl;
	summaryBox->setPromptText(summary.toString());

	ghost->addSuiBox(summaryBox);
	admin->sendMessage(summaryBox->generateMessage());
}

void PlayerManagementSessionImplementation::showUnbanSummary() {
	ManagedReference<CreatureObject*> admin = this->admin.get();

	if (admin == NULL)
		return;

	Reference<PlayerObject*> ghost = admin->getPlayerObject();

	if (ghost == NULL)
		return;

	Locker alocker(targetAccount);

	if (unbanSummaryBox == NULL) {
		unbanSummaryBox = new SuiMessageBox(admin, SuiWindowType::ADMIN_UNBAN_SUMMARY);

		unbanSummaryBox->setOkButton(true, "@ok");
		unbanSummaryBox->setCancelButton(true, "@cancel");
		unbanSummaryBox->setCallback(new PlayerManagementSessionSuiCallback(admin->getZoneServer()));
		unbanSummaryBox->setUsingObject(admin);

		unbanSummaryBox->setPromptTitle("Unban Summary");
	}


	StringBuffer summary;
	summary << "Unbanning ";
	if (banMode == ACCOUNT && targetAccount != NULL) {
		summary << " Account: " << targetAccount->getUsername() <<  endl;
		banExpiration = targetAccount->getBanExpires();
	} else if (banMode == GALAXY && galaxyID != 0) {
		GalaxyBanEntry* galaxyBan = targetAccount->getGalaxyBan(galaxyID);
		if (galaxyBan != NULL) {
			banExpiration = galaxyBan->getBanExpiration();
		}
		summary << " From " << galaxyName << " Galaxy" <<  endl;
	} else if (banMode == CHARACTER && !targetName.isEmpty()) {
		summary << " Character: " << targetName <<  endl;
		CharacterListEntry* entry = targetAccount->getCharacterBan(galaxyID, targetName);
		if (entry != NULL) {
			banExpiration = entry->getBanExpiration();
		}
	}

	summary << getBanDuration(banExpiration) << endl;
	summary << "Unban Reason: "<< banReason << endl;

	unbanSummaryBox->setPromptText(summary.toString());

	ghost->addSuiBox(unbanSummaryBox);
	admin->sendMessage(unbanSummaryBox->generateMessage());
}

void PlayerManagementSessionImplementation::completeBan() {
	ManagedReference<CreatureObject*> admin = this->admin.get();

	if (admin == NULL)
		return;

	Reference<PlayerObject*> ghost = admin->getPlayerObject();

	if (ghost == NULL)
		return;

	String message = "";

	/// Update account to check for changes
	Locker locker(targetAccount);
	targetAccount->updateAccount();

	if (banMode == ACCOUNT) {

		/// Check for account status changes
		if ((banType == BAN && targetAccount->isBanned()) ||
				(banType == UNBAN && !targetAccount->isBanned())) {

			admin->sendSystemMessage("This account has been changed since you started modifying it, please check changes and try again");

			admin->sendMessage(accountBox->generateCloseMessage());
			cancelSession();
			return;
		}

		if (targetAccount->isBanned()) {
			StringBuffer reason;
			reason << targetAccount->getBanAdmin() << "=" << targetAccount->getBanReason() << "|" << ghost->getAccountID() << "=" << banReason;
			message = playerManager->unbanAccount(ghost, targetAccount, reason.toString());
		} else
			message = playerManager->banAccount(ghost, targetAccount, banExpiration - time(0), banReason);

	} else if (banMode == GALAXY) {

		GalaxyBanEntry* galaxyBan = targetAccount->getGalaxyBan(galaxyID);

		/// Check for galaxy ban status changes
		if ((banType == BAN && galaxyBan != NULL) ||
				(banType == UNBAN && galaxyBan == NULL)) {

			admin->sendSystemMessage("This account has been changed since you started modifying it, please check changes and try again");

			admin->sendMessage(accountBox->generateCloseMessage());
			cancelSession();
			return;
		}

		if (galaxyBan != NULL) {
			StringBuffer reason;
			reason << galaxyBan->getBanAdmin() << "=" << galaxyBan->getBanReason() << "|" << ghost->getAccountID() << "=" << banReason;
			message = playerManager->unbanFromGalaxy(ghost, targetAccount, galaxyID, reason.toString());
		} else
			message = playerManager->banFromGalaxy(ghost, targetAccount, galaxyID, banExpiration - time(0), banReason);

	} else if (banMode == CHARACTER){

		CharacterListEntry* entry = targetAccount->getCharacterBan(galaxyID, targetName);

		/// Check for player ban status changes
		if ((banType == BAN && entry != NULL) ||
				(banType == UNBAN && entry == NULL)) {

			admin->sendSystemMessage("This account has been changed since you started modifying it, please check changes and try again");

			admin->sendMessage(accountBox->generateCloseMessage());
			cancelSession();
			return;
		}

		if (entry != NULL) {
			StringBuffer reason;
			reason << entry->getBanAdmin() << "=" << entry->getBanReason() << "|" << ghost->getAccountID() << "=" << banReason;
			message = playerManager->unbanCharacter(ghost, targetAccount, targetName, galaxyID, reason.toString());
		} else
			message = playerManager->banCharacter(ghost, targetAccount, targetName, galaxyID, banExpiration - time(0), banReason);

	}

	admin->sendSystemMessage(message);
	//sendAccountInfo();
	admin->sendMessage(accountBox->generateCloseMessage());
	cancelSession();
}

String PlayerManagementSessionImplementation::getBanDuration(uint32 timestamp) {
	StringBuffer reason;
	int totalBan = timestamp - time(0);

	int daysBanned = floor((float)totalBan / 60.f / 60.f / 24.f);
	totalBan -= (daysBanned * 60 * 60 * 24);

	int hoursBanned = floor(((float)totalBan / 60.0f) / 60.f);
	totalBan -= (hoursBanned * 60 * 60);

	int minutesBanned = floor((float)totalBan / 60.0f);
	totalBan -= (minutesBanned * 60);


	reason << "Time remaining: ";

	if (daysBanned > 0)
		reason << daysBanned << " Days ";

	if (hoursBanned > 0)
		reason << hoursBanned << " Hours ";

	if (minutesBanned > 0)
		reason << minutesBanned << " Minutes ";

	reason << totalBan << " Seconds\n";

	return reason.toString();
}
