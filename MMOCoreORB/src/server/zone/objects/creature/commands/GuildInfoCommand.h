
#ifndef GUILDINFOCOMMAND_H_
#define GUILDINFOCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/guild/GuildObject.h"

class GuildInfoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->getPlayerObject()->isPrivileged())
			return 1;

		ManagedReference<GuildObject*> targetGuild;

		if (!arguments.isEmpty()) {
			ManagedReference<GuildManager*> guildManager = creature->getZoneServer()->getGuildManager();

			targetGuild = guildManager->getGuildFromAbbrev(arguments.toString());
		}

		if (targetGuild == NULL) {
			creature->sendSystemMessage("Invalid Guild abbreviation.");
			return 1;
		}

		Locker crossLocker(targetGuild, creature);

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, 0);

		box->setPromptTitle("Guild Info");

		StringBuffer promptText;
		promptText << "Guild Name: " << targetGuild->getGuildName() << " <" << targetGuild->getGuildAbbrev() << ">" << endl;
		promptText << "Guild ID: " << targetGuild->getGuildID() << endl;

		uint64 leaderID = targetGuild->getGuildLeaderID();
		CreatureObject* leader = creature->getZoneServer()->getObject(leaderID).castTo<CreatureObject*>();

		promptText << "Guild Leader: " << (leader == NULL ? "None" : leader->getFirstName()) << endl;

		bool renamePending = targetGuild->isRenamePending();
		promptText << "Rename Pending?: " << (renamePending ? "yes" : "no") << endl;

		if (renamePending) {
			promptText << "Pending Name: " << targetGuild->getPendingNewName() << " <" << targetGuild->getPendingNewAbbrev() << ">" << endl;

			Time* renameTime = targetGuild->getRenameTime();
			promptText << "Time until rename: " << renameTime->getFormattedTime() << endl;

			uint64 renamerID = targetGuild->getRenamerID();
			CreatureObject* renamer;
			if (renamerID == leaderID) {
				promptText << "Renamer: " << (leader == NULL ? "None" : leader->getFirstName()) << endl;
			} else {
				renamer = creature->getZoneServer()->getObject(renamerID).castTo<CreatureObject*>();
				promptText << "Renamer: " << (renamer == NULL ? "None" : renamer->getFirstName()) << endl;
			}
		}

		promptText << endl << "Guild Members (" << targetGuild->getTotalMembers() << "):" << endl;

		GuildMemberInfo* leaderInfo = targetGuild->getMember(leaderID);
		if (leader != NULL && leaderInfo != NULL) {
			promptText << "\t" << leader->getFirstName() << " (" << leaderInfo->getGuildTitle() << ")" << endl;

			uint8 perms = leaderInfo->getPermissions();
			addPerms(perms, promptText);
		}

		for (int i = 0; i < targetGuild->getTotalMembers(); i++) {
			uint64 memberID = targetGuild->getMember(i);

			if (memberID == leaderID) {
				continue;
			}

			CreatureObject* member = creature->getZoneServer()->getObject(memberID).castTo<CreatureObject*>();
			GuildMemberInfo* memberInfo = targetGuild->getMember(memberID);

			if (member != NULL && memberInfo != NULL) {
				promptText << "\t" << member->getFirstName();

				String title = memberInfo->getGuildTitle();
				if (title.isEmpty()) {
					promptText << endl;
				} else {
					promptText << " (" << title << ")" << endl;
				}

				uint8 perms = memberInfo->getPermissions();
				addPerms(perms, promptText);
			}
		}

		promptText << endl << "Sponsored Players (" << targetGuild->getSponsoredPlayerCount() << "):" << endl;

		for (int i = 0; i < targetGuild->getSponsoredPlayerCount(); i++) {
			uint64 sponsoredID = targetGuild->getSponsoredPlayer(i);

			CreatureObject* sponsored = creature->getZoneServer()->getObject(sponsoredID).castTo<CreatureObject*>();

			if (sponsored != NULL) {

				promptText << "\t" << sponsored->getFirstName() << endl;
			}
		}

		VectorMap<uint64, byte>* waringGuilds = targetGuild->getWaringGuilds();
		promptText << endl << "Waring Guilds (" << waringGuilds->size() << "):" << endl;

		for (int i = 0; i < waringGuilds->size(); i++) {
			uint64 warGuildID = waringGuilds->elementAt(i).getKey();

			GuildObject* warGuild = creature->getZoneServer()->getObject(warGuildID).castTo<GuildObject*>();
			byte status = targetGuild->getWarStatus(warGuildID);
			String statusString;

			if (warGuild != NULL) {
				promptText << "\t" << (char) status << "" << warGuild->getGuildName() << " <" << warGuild->getGuildAbbrev() << ">" << endl;
			}
		}

		box->setPromptText(promptText.toString());

		creature->sendMessage(box->generateMessage());

		return 0;
	}

	static void addPerms(uint8 perms, StringBuffer& text) {
		text << "\t\tPerms: ";

		if (perms == 0x00) {
			text << "None" << endl;
		} else if (perms == 0xFF) {
			text << "All" << endl;
		} else {
			if (perms & 0x01) {
				text << "Mail, ";
			}
			if (perms & 0x02) {
				text << "Sponsor, ";
			}
			if (perms & 0x04) {
				text << "Title, ";
			}
			if (perms & 0x08) {
				text << "Accept, ";
			}
			if (perms & 0x10) {
				text << "Kick, ";
			}
			if (perms & 0x20) {
				text << "War, ";
			}
			if (perms & 0x40) {
				text << "Name, ";
			}
			if (perms & 0x80) {
				text << "Disband, ";
			}
			text << endl;
		}
	}
};


#endif /* GUILDINFOCOMMAND_H_ */
