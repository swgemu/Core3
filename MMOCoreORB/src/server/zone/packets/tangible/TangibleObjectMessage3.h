/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TANGIBLEOBJECTMESSAGE3_H_
#define TANGIBLEOBJECTMESSAGE3_H_

#include "../BaseLineMessage.h"

#include "server/zone/objects/tangible/TangibleObject.h"
#include "../../objects/scene/variables/StringId.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "../../managers/player/PermissionLevelList.h"

class TangibleObjectMessage3 : public BaseLineMessage {
public:
	TangibleObjectMessage3(TangibleObject* tano, uint32 objType = 0x54414E4F, uint16 opcnt = 0x0B)
			: BaseLineMessage(tano->getObjectID(), objType, 3, opcnt) {
		insertFloat(tano->getComplexity());

		StringId* stringId = tano->getObjectName();

		insertStringId(stringId);

		if (tano->isPlayerCreature()) {
			ManagedReference<PlayerObject*> ghost = (cast<CreatureObject*>(tano))->getPlayerObject();

			if (ghost != NULL && ghost->isPrivileged()) {
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

		int count = tano->getDisplayedUseCount();

		insertInt(count); //item count

		insertInt(int(tano->getConditionDamage()));
		insertInt(tano->getMaxCondition());

		insertByte(tano->getObjectVisible());

		setSize();
	}

};

#endif /*TANGIBLEOBJECTMESSAGE3_H_*/
