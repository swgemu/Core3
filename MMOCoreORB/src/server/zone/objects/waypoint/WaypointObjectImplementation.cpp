/*
 * WaypointObjectImplementation.cpp
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/intangible/IntangibleObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "system/lang/String.h"
#include "system/lang/UnicodeString.h"

class SharedObjectTemplate;
namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
}  // namespace objects
}  // namespace zone
}  // namespace server

void WaypointObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	IntangibleObjectImplementation::loadTemplateData(templateData);

	cellID = 0; //?

	unknown = 0;
	planetCRC = 0;

	color = COLOR_BLUE;
	active = 0;

	specialTypeID = 0;
}

String WaypointObjectImplementation::getDetailedDescription() {
	if (detailedDescription.isEmpty())
		return SceneObjectImplementation::getDetailedDescription();

	return detailedDescription;
}

void WaypointObjectImplementation::insertToMessage(BaseMessage* msg) {
	msg->writeInt(cellID); // cellID
	msg->writeFloat(getPositionX());
	msg->writeFloat(getPositionZ()); //Z
	msg->writeFloat(getPositionY());
	msg->writeLong(unknown); //?
	msg->writeInt(planetCRC);

	customName.toBinaryStream(msg);

	msg->writeLong(getObjectID());
	msg->writeByte(color);
	msg->writeByte(active);
}

void WaypointObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	IntangibleObjectImplementation::fillAttributeList(alm, object);

	if (questDetails.length() > 0)
		alm->insertAttribute("quest_details", questDetails);
}
