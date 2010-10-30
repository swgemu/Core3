/*
 * GuildList.h
 *
 *  Created on: Oct 27, 2010
 *      Author: crush
 */

#ifndef GUILDLIST_H_
#define GUILDLIST_H_

#include "engine/engine.h"

#include "server/zone/objects/guild/GuildObject.h"


class GuildList : public VectorMap<uint32, ManagedReference<GuildObject*> > {
public:
	GuildList() : VectorMap<uint32, ManagedReference<GuildObject*> >() {

	}
};


#endif /* GUILDLIST_H_ */
