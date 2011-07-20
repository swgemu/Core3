/*
 * GuildSponsoredOptionsSuiCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef GUILDSPONSOREDOPTIONSSUICALLBACK_H_
#define GUILDSPONSOREDOPTIONSSUICALLBACK_H_

class GuildSponsoredOptionsSuiCallback : public SuiCallback {
public:
	GuildSponsoredOptionsSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (guildManager == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isTerminal())
			return;

		Terminal* terminal = (Terminal*) obj.get();

		if (!terminal->isGuildTerminal())
			return;

		GuildTerminal* guildTerminal = (GuildTerminal*) terminal;

		ManagedReference<GuildObject*> guild = guildTerminal->getGuildObject();

		if (guild == NULL || !guild->hasAcceptPermission(player->getObjectID())) {
			player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
			return;
		}

		SuiListBox* listBox = (SuiListBox*) suiBox;

		uint64 playerID = listBox->getMenuObjectID(index);

		//Whether they accept, or decline, we are removing them from the sponsored list.
		guild->removeSponsoredPlayer(playerID);
		guildManager->removeSponsoredPlayer(playerID);

		if (index == 0) //If they accepted, then ...
			guildManager->acceptSponsoredPlayer(player, playerID);
	}
};

#endif /* GUILDSPONSOREDOPTIONSSUICALLBACK_H_ */
