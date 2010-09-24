/*
 * WaypointObjectImplementation.cpp
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#include "WaypointObject.h"

void WaypointObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	IntangibleObjectImplementation::loadTemplateData(templateData);

	cellID = 0; //?

	unknown = 0;
	planetCRC = 0;

	color = COLOR_BLUE;
	active = 0;

	specialTypeID = 0;
}

void WaypointObjectImplementation::insertToMessage(BaseMessage* msg) {
	msg->writeInt(cellID); // cellID
	msg->writeFloat(positionX);
	msg->writeFloat(positionZ); //Z
	msg->writeFloat(positionY);
	msg->writeLong(unknown); //?
	msg->writeInt(planetCRC);

	customName.toBinaryStream(msg);

	msg->writeLong(getObjectID());
	msg->writeByte(color);
	msg->writeByte(active);
}
