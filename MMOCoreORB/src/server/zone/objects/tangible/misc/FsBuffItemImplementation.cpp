#include "server/zone/objects/tangible/misc/FsBuffItem.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/BuffAttribute.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

void FsBuffItemImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	menuResponse->addRadialMenuItem(68, 3, "@quest/force_sensitive/utils:use_special_effect");
}

int FsBuffItemImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (!isASubChildOf(player))
		return 0;

	if (selectedID == 68) {
		uint32 buffCRC = getBuffCRC();

		if (player->hasBuff(buffCRC)) {
			player->sendSystemMessage("@quest/force_sensitive/utils:have_buff");
			return 0;
		}

		if (!player->checkCooldownRecovery("fs_buff_item_" + BuffAttribute::getName(buffAttribute))) {
			player->sendSystemMessage("@quest/force_sensitive/utils:timer_not_up");
			return 0;
		}

		Reference<Buff*> buff = new Buff(player, buffCRC, buffDuration, BuffType::MEDICAL);

		Locker locker(buff);

		buff->setAttributeModifier(buffAttribute, buffValue);

		player->addBuff(buff);

		player->sendSystemMessage("@quest/force_sensitive/utils:buff_applied");

		player->addCooldown("fs_buff_item_" + BuffAttribute::getName(buffAttribute), reuseTime);
	}

	return 1;
}

void FsBuffItemImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	if (!player->checkCooldownRecovery("fs_buff_item_" + BuffAttribute::getName(buffAttribute))) {
		Time* timeRemaining = player->getCooldownTime("fs_buff_item_" + BuffAttribute::getName(buffAttribute));
		alm->insertAttribute("reuse_time", getTimeString(timeRemaining->miliDifference() * -1));
	} else {
		alm->insertAttribute("reuse_time", "0");
	}

	alm->insertAttribute("examine_dot_attribute", BuffAttribute::getName(buffAttribute, true));
	alm->insertAttribute("potency", buffValue);
	alm->insertAttribute("duration", getTimeString(buffDuration * 1000));
}

uint32 FsBuffItemImplementation::getBuffCRC() {
	switch (buffAttribute) {
	case 0: return BuffCRC::MEDICAL_ENHANCE_HEALTH;
	case 1: return BuffCRC::MEDICAL_ENHANCE_STRENGTH;
	case 2: return BuffCRC::MEDICAL_ENHANCE_CONSTITUTION;
	case 3: return BuffCRC::MEDICAL_ENHANCE_ACTION;
	case 4: return BuffCRC::MEDICAL_ENHANCE_QUICKNESS;
	case 5: return BuffCRC::MEDICAL_ENHANCE_STAMINA;
	case 6: return BuffCRC::PERFORMANCE_ENHANCE_DANCE_MIND;
	case 7: return BuffCRC::PERFORMANCE_ENHANCE_MUSIC_FOCUS;
	case 8: return BuffCRC::PERFORMANCE_ENHANCE_MUSIC_WILLPOWER;
	case 9: return BuffCRC::MEDICAL_ENHANCE_POISON;
	case 10: return BuffCRC::MEDICAL_ENHANCE_DISEASE;
	default: return BuffCRC::MEDICAL_ENHANCE_HEALTH;
	}
}

String FsBuffItemImplementation::getTimeString(uint32 timestamp) {
	int seconds = timestamp / 1000;

	int hours = seconds / 3600;
	seconds -= hours * 3600;

	int minutes = seconds / 60;
	seconds -= minutes * 60;

	StringBuffer buffer;

	if (hours > 0)
		buffer << hours << "h ";

	if (minutes > 0)
		buffer << minutes << "m ";

	if (seconds > 0)
		buffer << seconds << "s";

	return buffer.toString();
}
