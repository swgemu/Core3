/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TANGIBLEOBJECTMESSAGE3_H_
#define TANGIBLEOBJECTMESSAGE3_H_

#include "server/zone/packets/BaseLineMessage.h"

#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/scene/variables/StringId.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/player/PermissionLevelList.h"

class TangibleObjectMessage3 : public BaseLineMessage {
public:
	TangibleObjectMessage3(TangibleObject* tano, uint32 objType = 0x54414E4F, uint16 opcnt = 0x0B)
			: BaseLineMessage(tano->getObjectID(), objType, 3, opcnt) {
		insertFloat(tano->getComplexity());

		StringId* stringId = tano->getObjectName();

		insertStringId(stringId);

		if (tano->isPlayerCreature()) {
			Reference<PlayerObject*> ghost = (static_cast<CreatureObject*>(tano))->getPlayerObject();

			if (ghost != NULL && ghost->hasGodMode()) {
				UnicodeString name = tano->getCustomObjectName();
				UnicodeString tag = PermissionLevelList::instance()->getPermissionTag(ghost->getAdminLevel());
				insertUnicode(name + " \\#ffff00[" + tag + "]\\#.");
			} else {
				insertUnicode(tano->getCustomObjectName());
			}

		} else {
			insertUnicode(tano->getCustomObjectName());
		}

		insertInt(tano->getVolume());

		String app;
		tano->getCustomizationString(app);
		insertAscii(app);

		AutoDeltaSet<int>* visibleComponents = tano->getVisibleComponents();
		visibleComponents->insertToMessage(this);

		insertInt(tano->getOptionsBitmask());

		insertInt(tano->getUseCount()); //item count

		insertInt(int(tano->getConditionDamage()));
		insertInt(tano->getMaxCondition());

		insertByte(tano->getObjectVisible());

		setSize();
	}

};

#endif /*TANGIBLEOBJECTMESSAGE3_H_*/
