/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#pragma once

#include <functional>
#include "system/lang/Function.h"
#include "server/zone/objects/guild/GuildObject.h"

using GuildObjectIterator = Function<void(GuildObject*)>;
