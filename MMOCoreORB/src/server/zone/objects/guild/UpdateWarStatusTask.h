/*
 * UpdateWarStatusTask.h
 *
 *  Created on: Jun 8, 2012
 *      Author: swgemu
 */

#ifndef UPDATEWARSTATUSTASK_H_
#define UPDATEWARSTATUSTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/ZoneServer.h"

class UpdateWarStatusTask : public Task {
	ZoneServer* server;

	GuildMemberList guild1;
	GuildMemberList guild2;

public:
	UpdateWarStatusTask(ZoneServer* zserv, GuildObject* guild, GuildObject* waringGuild) : Task() {
		guild1 = *guild->getGuildMemberList();
		guild2 = *waringGuild->getGuildMemberList();

		server = zserv;
	}

	void run() {
		//Loop through one map.
		for (int i = 0; i < guild1.size(); ++i) {
			VectorMapEntry<uint64, GuildMemberInfo>* entry = &guild1.elementAt(i);

			ManagedReference<SceneObject*> obj = server->getObject(entry->getKey());

			if (obj == NULL || !obj->isPlayerCreature())
				continue;

			CreatureObject* creo = obj.castTo<CreatureObject*>();

			//Loop through the other map.
			for (int j = 0; j < guild2.size(); ++j) {
				VectorMapEntry<uint64, GuildMemberInfo>* entry2 = &guild2.elementAt(j);

				ManagedReference<SceneObject*> obj2 = server->getObject(entry2->getKey());

				if (obj2 == NULL || !obj2->isPlayerCreature())
					continue;

				CreatureObject* creo2 = obj2.castTo<CreatureObject*>();

				Locker _lock(creo);

				if (creo->isInRange(creo2, ZoneServer::CLOSEOBJECTRANGE)) {
					Locker _crosslock(creo2, creo);
					creo->sendPvpStatusTo(creo2);
					creo2->sendPvpStatusTo(creo);
				}
			}
		}
	}
};


#endif /* UPDATEWARSTATUSTASK_H_ */
