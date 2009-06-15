/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "engine/service/proto/BaseMessage.h"

#include "../../ServerCore.h"
#include "SceneObjectImplementation.h"
#include "cell/CellObject.h"
#include "tangible/creature/player/PlayerObject.h"

#include "../packets/object/ObjectMenuResponse.h"
#include "../packets/scene/SceneObjectCloseMessage.h"
#include "../packets/scene/SceneObjectCreateMessage.h"
#include "../packets/scene/SceneObjectDestroyMessage.h"
#include "../packets/scene/UpdateContainmentMessage.h"


SceneObjectImplementation::SceneObjectImplementation(uint64 objectid, int type)
		: SceneObjectServant() {

	objectID = objectid;
	gameObjectType = type;

	initialize();
}

SceneObjectImplementation::~SceneObjectImplementation() {

}


void SceneObjectImplementation::initialize() {
	complexity = 1.0f;
	volume = 0;

	undeployEvent = NULL;
	keepObject = false;

	parent = NULL;
}

/**
 * Serializes (saves) the object to the passed string.
 * \param str The string to append the serialized data.
 */
void SceneObjectImplementation::serialize(String& str) {

}

/**
 * Deserializes (loads) the object from the passed string.
 * \param str The string containing the serialized data.
 */
void SceneObjectImplementation::deserialize(const String& str) {

}


//ORB Methods
bool SceneObject::destroy() {
	bool destroying = ServerCore::getZoneServer()->destroyObject(this);

	if (destroying) {
		//info("destroying object");
		delete this;
	}

	return destroying;
}

bool SceneObjectImplementation::destroy() {
	return _this->destroy();
}

void SceneObjectImplementation::redeploy() {
	info("redeploying object");

	_this->revoke();

	removeUndeploymentEvent();
}

void SceneObjectImplementation::scheduleUndeploy() {
	if (undeployEvent == NULL && !keepObject && server != NULL) {
		info("scheduling uneploy");
		undeployEvent = new UndeploySceneObjectEvent(_this);
		server->addEvent(undeployEvent);
	}
}

void SceneObjectImplementation::undeploy() {
	if (isInQuadTree()) {
		error("Deleting scene object that is in QT");
		raise(SIGSEGV);
	}

	removeUndeploymentEvent();
	/*if (zone != NULL)
	//zone->deleteObject(_this);
	error("object is still in Zone");*/
}

void SceneObjectImplementation::removeUndeploymentEvent() {
	if (undeployEvent != NULL) {
		server->removeEvent(undeployEvent);
		delete undeployEvent;
		undeployEvent = NULL;
	}
}

/*************************************************************************
 * Zone Insertion
 *************************************************************************/
/**
 * This method is called when the object is "inserted" to the zone, meaning that it is ready to
 * be sent to all other objects in the area as well and interact in the world.
 * \param zone The zone to insert the object to.
 */
void SceneObjectImplementation::insertToZone(Zone* zne) {
	zone = zne;

	try {
		zone->lock();
		zone->registerObject(_this);

		if (parent != NULL && parent->isObjectType(CELL)) {
			insertToCell((CellObject*) parent);
			//building->notifyInsertToZone(_this); //TODO: Do we need this.
		} else {
			zone->insert(this);
			zone->inRange(this, 128);
		}

		zone->unlock();
	} catch (...) {
		error("Exception on zone insertion in SceneObjectImplementation.");
		zone->unlock();
	}
}

void SceneObjectImplementation::insertToCell(CellObject* cell) {
	if (isInQuadTree() || !parent->isObjectType(CELL))
		return;

	try {
		cell->lock();
		cell->appendChild(_this);
		//cell->insert(this);
		//cell->inRange(this, 128);
		cell->unlock();
		//cell->notifyInsertToZone(_this);
		linkType = 0xFFFFFFFF;
		//broadcastMessage(link(parent), 128, false);
	} catch (...) {
		error("Exception on insertion to cell in SceneObjectImplementation.");
		cell->unlock();
	}
}


/*************************************************************************
 * Sending of Interfaces
 *************************************************************************/
/**
 * This method sends the appropriate object packets to the player.
 * \param player The player requesting the object.
 * \param doclose Should we close the SceneObjectCreatMessage.
 */
void SceneObjectImplementation::sendTo(PlayerObject* player, bool close) {
}

/**
 * This method sends the packets to a client needed to destroy it on said client.
 * \param player The player who is receiving the destroy packet.
 */
void SceneObjectImplementation::sendDestroyTo(PlayerObject* player) {
}

/**
 * This method sends the requested radial menu to the player, with all options affixed.
 * \param player The player requesting the radial.
 * \param omr The object representing the radial menu.
 */
void SceneObjectImplementation::sendRadialResponseTo(PlayerObject* player, ObjectMenuResponse* omr) {

}

/**
 * This method does something with the stopping of conversation...
 * TODO: Look into this.
 * \param player The player requesting to stop conversation.
 */
void SceneObjectImplementation::sendConversationStopTo(PlayerObject* player) {

}

/**
 * This method sends the Set Name Sui Input Box to the player, allowing them
 * to set a custom name for this object.
 * \param player The player setting the name.
 */
void SceneObjectImplementation::sendCustomNamePromptTo(PlayerObject* player) {

}

/**
 * This method sends a Sui List Box with information about this object.
 * \param player The player requesting the status.
 */
void SceneObjectImplementation::sendStatusTo(PlayerObject* player) {

}


/*************************************************************************
 * Sending of Packets
 *************************************************************************/
void SceneObjectImplementation::close(ZoneClientSession* client) {
	if (client == NULL)
		return;

	BaseMessage* msg = new SceneObjectCloseMessage(_this);
	client->sendMessage(msg);
}

void SceneObjectImplementation::create(ZoneClientSession* client) {
	if (client == NULL)
		return;

	BaseMessage* msg = new SceneObjectCreateMessage(_this);
	client->sendMessage(msg);
}

void SceneObjectImplementation::destroy(ZoneClientSession* client) {
	if (client == NULL)
		return;

	BaseMessage* msg = new SceneObjectDestroyMessage(_this);
	client->sendMessage(msg);
}

void SceneObjectImplementation::link(ZoneClientSession* client, SceneObject* container) {
	if (client == NULL)
		return;

	parent = container;
	container->appendChild(_this);

	BaseMessage* msg = new UpdateContainmentMessage(_this, container, linkType);
	client->sendMessage(msg);
}

/**
 * This method broadcasts the passed packet in a certain range.
 * \param msg The message/packet to be broadcast.
 * \param range The range in which to broadcast the packet.
 * \param dolock Should we lock this object before broadcasting?
 * \param sendself Should we send this packet to this object as well?
 */
void SceneObjectImplementation::broadcastMessage(BaseMessage* msg, int range, bool dolock, bool sendself) {
	if (zone == NULL) {
		delete msg;
		return;
	}

	try {
		//System::out << "CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
		zone->lock(dolock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);
			SceneObject* object = (SceneObject*) scno->_getStub();

			if (object->isPlayer()) {
				PlayerObject* player = (PlayerObject*) object;

				if (range == 128 || isInRange(player, range) || player->getParent() != NULL) {
					if (isPlayer()) {
						PlayerObject* sender = (PlayerObject*) _getStub();

						if (!sendself && (player == sender))
							continue;
					}

					//System::out << "CreatureObject - sending message to player " << player->getFirstName() << "\n";
					player->sendMessage(msg->clone());
				}
			}
		}

		delete msg;
		zone->unlock(dolock);
	} catch (...) {
		error("exception SceneObject::broadcastMessage(Message* msg, int range, bool doLock)");
		zone->unlock(dolock);
	}
//System::out << "finished CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
}

/**
 * This method broadcasts the passed packet in a certain range.
 * \param msg The message/packet to be broadcast.
 * \param range The range in which to broadcast the packet.
 * \param dolock Should we lock this object before broadcasting?
 */
void SceneObjectImplementation::broadcastMessage(StandaloneBaseMessage* msg, int range, bool dolock) {
	if (zone == NULL) {
		delete msg;
		return;
	}

	try {
		//System::out << "SceneObjectImplementation::broadcastMessage(Message* msg, int range, bool doLock)\n";
		zone->lock(dolock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);
			SceneObject* object = (SceneObject*) scno->_getStub();

			if (object->isPlayer()) {
				PlayerObject* player = (PlayerObject*) object;

				if (range == 128|| isInRange(player, range) || player->getParent() != NULL) {
					//System::out << "CreatureObject - sending message to player " << player->getFirstName() << "\n";
					player->sendMessage((StandaloneBaseMessage*)msg->clone());
				}
			}
		}

		delete msg;
		zone->unlock(dolock);
	} catch (...) {
		error("exception SceneObjectImplementation::broadcastMessage(Message* msg, int range, bool doLock)");
		zone->unlock(dolock);
	}

	//System::out << "finished SceneObjectImplementation::broadcastMessage(Message* msg, int range, bool doLock)\n";
}

/**
 * This method broadcasts a series of packets within a certain range.
 * \param msgs The messages/packets to be broadcast.
 * \param range The range in which to broadcast the packet.
 * \param dolock Should we lock this object before broadcasting?
 */
void SceneObjectImplementation::broadcastMessages(Vector<BaseMessage*>& msgs, int range, bool dolock) {
	if (zone == NULL) {
		for (int j = 0; j < msgs.size(); ++j) {
			Message* msg = msgs.get(j);
			delete msg;
		}

		msgs.removeAll();
		return;
	}

	try {
		//System::out << "CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)\n";
		zone->lock(dolock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

			if (object->isPlayer()) {
				PlayerObject* player = (PlayerObject*) object;

				if (range == 128 || isInRange(player, range) || player->getParent() != NULL) {
					for (int j = 0; j < msgs.size(); ++j) {
						BaseMessage* msg = msgs.get(j);
						player->sendMessage(msg->clone());
					}
				}
			}
		}

		for (int j = 0; j < msgs.size(); ++j) {
			Message* msg = msgs.get(j);
			delete msg;
		}

		msgs.removeAll();
		zone->unlock(dolock);
		//System::out << "finished CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)\n";
	} catch (...) {
		error("exception CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)");
		zone->unlock(dolock);
	}
}

/*************************************************************************
 * General Actions
 *************************************************************************/
/**
 * When an object is "used" via the radial, double clicked, or accessed via hotkey, this method
 * defines its use procedure.
 * \param player The player who has requested use of this object.
 */
void SceneObjectImplementation::use(PlayerObject* player) {
}

/**
 * When a player attempts to pickup an object, this method is called.
 * \param player The player who is attempting to pickup this object.
 */
void SceneObjectImplementation::pickup(PlayerObject* player) {
	if (!player->isPrivileged())
		return;
}

/**
 * When a player attempts to drop an object, this method is called.
 * \param player The player who is attempting to drop this object.
 */
void SceneObjectImplementation::drop(PlayerObject* player) {
	if (!player->isPrivileged())
		return;
}

/**
 * When a player attempts to destroy an item via radial menu or dragging it out of the container to the world.
 * \param player The player who is attempting to destroy this object.
 */
void SceneObjectImplementation::destroyObject(PlayerObject* player) {
	//TODO: Confirm that the object is actually in player's inventory first.
	//TODO: Self destruction instructions.
}

/**
 * When a player attempts to open an object's container. For example, a corpse or inventory.
 * \param player The player attempting to open this object.
 */
void SceneObjectImplementation::open(PlayerObject* player) {
	//TODO: Confirm that the player has permission to open this container.
}

/**
 * When a player attempts to "activate" an object. This may be a different
 * sequence of events than use().
 * \param player The player that is attempting to activate this object.
 */
void SceneObjectImplementation::activate(PlayerObject* player) {

}

/**
 * When a player attempts to "deactivate" an object.
 * \param player The player that is attempting to deactivate this object.
 */
void SceneObjectImplementation::deactivate(PlayerObject* player) {

}

/**
 * Compares the local gameObjectType to the type passed in variable "type"
 * \param type type to compare with
 * \param similar Default: false. If true, will return true if object inherits the object specified in variable "type"
 */
bool SceneObjectImplementation::isObjectType(int type, bool similar) {
	if (similar)
		return (gameObjectType & type);
	else
		return (gameObjectType == type);

	/*

	if(!similar)
		return type == gameObjectType;

	// If similar is true, check inheritance relationship
	switch(type) {
	case INTANGIBLE:
		if(gameObjectType >= 0x800 && gameObjectType <= 0x80B && (!(gameObjectType >= 0x01 && gameObjectType <= 0x04)))
			return true;
		break;
	// Tangible & children:
	case TANGIBLE:
		if((!(gameObjectType >= 0x800 && gameObjectType <= 0x80B)) && (!(gameObjectType >= 0x01 && gameObjectType <= 0x04)))
			return true;
		break;
	case BUILDING:
		if(gameObjectType >= 200 && gameObjectType <= 203)
			return true;
		break;
	case CREATURE:
		if(gameObjectType >= 400 && gameObjectType <= 403)
			return true;
		break;
	case INSTALLATION:
		if(gameObjectType >= 0x1000 && gameObjectType <= 0x1005)
			return true;
		break;
	case TOOL:
		if(gameObjectType >= 0x8000 && gameObjectType <= 0x8005)
			return true;
		break;
	case VEHICLE:
		if(gameObjectType >= 0x10000 && gameObjectType <= 0x10001)
			return true;
		break;
	case WEAPON:
		if(gameObjectType >= 0x20000 && gameObjectType <= 0x2000E)
			return true;
		break;
	case COMPONENT:
		if(gameObjectType >= 0x40000 && gameObjectType <= 0x4000D)
			return true;
		break;
	case POWERUP:
		if(gameObjectType >= 0x80000 && gameObjectType <= 0x80006)
			return true;
		break;
	case RESOURCECONTAINER:
		if(gameObjectType >= 0x400000 && gameObjectType <= 0x40000B)
			return true;
		break;
	case DEED:
		if(gameObjectType >= 0x800000 && gameObjectType <= 0x400006)
			return true;
		break;
	case WEARABLE:
		if(gameObjectType >= 0x1000000 && gameObjectType <= 0x1000013)
			return true;
		break;
	case SHIP:
		if(gameObjectType >= 0x2000000 && gameObjectType <= 0x2000001)
			return true;
		break;
	case SCENE:
		return true;
		break;
	default:
		return false;
		break;
	}

	return false;
	*/
}





//Generic Radial Responses
void SceneObjectImplementation::onRadialMenu1(PlayerObject* player) {

}

void SceneObjectImplementation::onRadialMenu2(PlayerObject* player) {

}

void SceneObjectImplementation::onRadialMenu3(PlayerObject* player) {

}

void SceneObjectImplementation::onRadialMenu4(PlayerObject* player) {

}

void SceneObjectImplementation::onRadialMenu5(PlayerObject* player) {

}

void SceneObjectImplementation::onRadialMenu6(PlayerObject* player) {

}

void SceneObjectImplementation::onRadialMenu7(PlayerObject* player) {

}

void SceneObjectImplementation::onRadialMenu8(PlayerObject* player) {

}

void SceneObjectImplementation::onRadialMenu9(PlayerObject* player) {

}

void SceneObjectImplementation::onRadialMenu10(PlayerObject* player) {

}

/*************************************************************************
 * Event Handlers
 *************************************************************************/
void SceneObjectImplementation::onDragDrop(PlayerObject* player, SceneObject* target) {

}
