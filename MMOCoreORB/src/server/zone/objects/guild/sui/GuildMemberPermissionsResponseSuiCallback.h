/*
 * GuildMemberPermissionsResponseSuiCallback.h
 *
 *  Created on: Nov 5, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBERPERMISSIONSRESPONSESUICALLBACK_H_
#define GUILDMEMBERPERMISSIONSRESPONSESUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildMemberPermissionsResponseSuiCallback : public SuiCallback {
public:
	GuildMemberPermissionsResponseSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		uint64 memberID = listBox->getMenuObjectID(index);

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (guildManager == nullptr)
			return;

		ManagedReference<SceneObject*> sceneO = suiBox->getUsingObject().get();

		if (sceneO == nullptr || (!sceneO->isGuildTerminal() && !sceneO->isGuildManagementDroid())) {
			return;
		}

		TangibleObject* tanO = sceneO->asTangibleObject();

		if (tanO == nullptr)
			return;

		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild == nullptr)
			return;

		guildManager->toggleGuildPermission(player, memberID, index, tanO);
	}
};

#endif /* GUILDMEMBERPERMISSIONSRESPONSESUICALLBACK_H_ */
