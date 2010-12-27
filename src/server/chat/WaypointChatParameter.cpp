/*
 * WaypointChatParameter.cpp
 *
 *  Created on: Nov 12, 2010
 *      Author: crush
 */


#include "WaypointChatParameter.h"
#include "server/zone/objects/waypoint/WaypointObject.h"

WaypointChatParameter::WaypointChatParameter() {
	addSerializableVariables();
}

WaypointChatParameter::WaypointChatParameter(WaypointObject* waypoint) {
	addSerializableVariables();

	set(waypoint);
}

WaypointChatParameter::WaypointChatParameter(const WaypointChatParameter& par) : Object(), ChatParameter(), Serializable() {
	addSerializableVariables();

	waypointName = par.waypointName;
	pointerParameter = par.pointerParameter;
	cellID = par.cellID;
	planetCRC = par.planetCRC;
	positionX = par.positionX;
	positionY = par.positionY;
	positionZ - par.positionZ;
	color = par.color;
	active = par.active;
	unknownInt = par.unknownInt;
}

void WaypointChatParameter::addToPacketStream(Message* packet) {
	packet->insertInt(unknownInt);
	packet->insertFloat(positionX);
	packet->insertFloat(positionZ);
	packet->insertFloat(positionY);
	packet->insertLong(0); //pointerParameter (always added as 0 though afaik)
	packet->insertInt(planetCRC);
	packet->insertUnicode(waypointName);
	packet->insertLong(cellID);
	packet->insertByte(color);
	packet->insertByte((byte) active);
}

void WaypointChatParameter::parse(Message* message) {
	unknownInt = message->parseInt();
	positionX = message->parseFloat();
	positionZ = message->parseFloat();
	positionY = message->parseFloat();
	pointerParameter = message->parseLong();
	planetCRC = message->parseInt();
	message->parseUnicode(waypointName);
	cellID = message->parseLong();
	color = message->parseByte();
	active = message->parseByte();
}

void WaypointChatParameter::set(WaypointObject* obj) {
	positionX = obj->getPositionX();
	positionY = obj->getPositionY();
	positionZ = obj->getPositionZ();
	pointerParameter = obj->getObjectID();
	cellID = obj->getParentID();
	color = obj->getColor();
	active = obj->isActive();
	planetCRC = obj->getPlanetCRC();
	waypointName = obj->getCustomName();
	unknownInt = 0;
}

void WaypointChatParameter::set(const UnicodeString& name, float x, float z, float y, uint32 planetcrc, uint64 pointer, uint64 cellid, byte clr, bool actv) {
	positionX = x;
	positionY = y;
	positionZ = z;
	pointerParameter = pointer;
	cellID = cellid;
	color = clr;
	active = actv;
	planetCRC = planetcrc;
	waypointName = name;
	unknownInt = 0;
}
