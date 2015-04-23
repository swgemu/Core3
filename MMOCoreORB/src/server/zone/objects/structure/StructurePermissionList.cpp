/*
 * StructurePermissionList.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "StructurePermissionList.h"
#include "server/zone/packets/ui/PermissionListCreateMessage.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/managers/player/PlayerManager.h"

StructurePermissionList::StructurePermissionList() {
	permissionLists.setNoDuplicateInsertPlan();
	idPermissionLists.setNoDuplicateInsertPlan();
	ownerID = 0;

	//TODO: Load these from the structure template script.
	addList("ADMIN");
	addList("ENTRY");
	addList("HOPPER");
	addList("BAN");
	addList("VENDOR");
}

StructurePermissionList::StructurePermissionList(const StructurePermissionList& spl) : Object(), permissionLists(spl.permissionLists),
		idPermissionLists(spl.idPermissionLists), ownerName(spl.ownerName), ownerID(spl.ownerID), lock() {
}

bool StructurePermissionList::toBinaryStream(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);

	return true;
}

int StructurePermissionList::writeObjectMembers(ObjectOutputStream* stream) {
	String _name;
	int _offset;
	uint32 _totalSize;

	_name = "permissionLists";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<VectorMap<String, SortedVector<String> > >::toBinaryStream(&permissionLists, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "idPermissionLists";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<VectorMap<String, SortedVector<uint64> > >::toBinaryStream(&idPermissionLists, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "ownerName";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<String>::toBinaryStream(&ownerName, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "ownerID";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<uint64>::toBinaryStream(&ownerID, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	String emptyName; // making it serialize the same way as Serializable so bas doesnt have to update all the objects

	_name = "_className";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<String>::toBinaryStream(&emptyName, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	return 3;
}

bool StructurePermissionList::readObjectMember(ObjectInputStream* stream, const String& name) {
	if (name == "permissionLists") {
		TypeInfo<VectorMap<String, SortedVector<String> > >::parseFromBinaryStream(&permissionLists, stream);

		return true;
	} else if (name == "idPermissionLists") {
		TypeInfo<VectorMap<String, SortedVector<uint64> > >::parseFromBinaryStream(&idPermissionLists, stream);

		return true;
	} else if (name == "ownerName") {
		TypeInfo<String>::parseFromBinaryStream(&ownerName, stream);

		return true;
	} else if (name == "ownerID") {
		TypeInfo<uint64>::parseFromBinaryStream(&ownerID, stream);

		return true;
	}

	return false;
}

bool StructurePermissionList::parseFromBinaryStream(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();

	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);

		uint32 _varSize = stream->readInt();

		int _currentOffset = stream->getOffset();

		if(readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	return true;
}

void StructurePermissionList::sendTo(CreatureObject* creature, const String& listName) {
	ZoneServer* zoneServer = creature->getZoneServer();

	ReadLocker locker(&lock);

	if (!idPermissionLists.contains(listName)) {
		return;
	}

	PermissionListCreateMessage* listMsg = new PermissionListCreateMessage(listName);

	SortedVector<uint64>* list = &idPermissionLists.get(listName);
	Vector<uint64> invalidIDs;

	for (int i = 0; i < list->size(); ++i) {
		Reference<SceneObject*> object = zoneServer->getObject(list->get(i));

		if (object != NULL && object->isPlayerCreature()) {
			CreatureObject* player = object.castTo<CreatureObject*>();
			String name = player->getFirstName();
			listMsg->addName(name);
		} else if (object != NULL && object->isGuildObject()) {
			GuildObject* guild = object.castTo<GuildObject*>();
			String name = "guild:" + guild->getGuildAbbrev();
			listMsg->addName(name);
		} else {
			invalidIDs.add(list->get(i));
		}
	}

	for (int i = 0; i < invalidIDs.size(); i++) {
		list->drop(invalidIDs.get(i));
	}

	listMsg->generateMessage();
	creature->sendMessage(listMsg);
}

int StructurePermissionList::togglePermission(const String& listName, const uint64 objectID) {
	Locker locker(&lock);

	if(objectID == ownerID)
		return CANTCHANGEOWNER;

	if (!idPermissionLists.contains(listName))
		return LISTNOTFOUND;

	SortedVector<uint64>* list = &idPermissionLists.get(listName);

	//If they exist, remove them.
	if (list->contains(objectID)) {
		list->drop(objectID);
		return REVOKED;
	}

	list->put(objectID);
	return GRANTED;
}

int StructurePermissionList::grantPermission(const String& listName, const uint64 objectID) {
	Locker locker(&lock);

	if(objectID == ownerID)
		return CANTCHANGEOWNER;

	if (!idPermissionLists.contains(listName))
		return LISTNOTFOUND;

	SortedVector<uint64>* list = &idPermissionLists.get(listName);

	list->put(objectID);

	return GRANTED;
}

int StructurePermissionList::revokePermission(const String& listName, const uint64 objectID) {
	Locker locker(&lock);

	if(objectID == ownerID)
		return CANTCHANGEOWNER;

	if (!idPermissionLists.contains(listName))
		return LISTNOTFOUND;

	SortedVector<uint64>* list = &idPermissionLists.get(listName);

	list->drop(objectID);

	return REVOKED;
}

int StructurePermissionList::revokeAllPermissions(const uint64 objectID) {
	Locker locker(&lock);

	if(objectID == ownerID)
		return CANTCHANGEOWNER;

	for (int i = 0; i < idPermissionLists.size(); ++i) {
		SortedVector<uint64>* list = &idPermissionLists.get(i);

		list->drop(objectID);
	}

	return REVOKED;
}

void StructurePermissionList::revokeAllPermissions() {
	Locker locker(&lock);

	for (int i = 0; i < idPermissionLists.size(); ++i) {
		SortedVector<uint64>* list = &idPermissionLists.get(i);

		list->removeAll();

		if (idPermissionLists.elementAt(i).getKey() == "ADMIN") {
			list->put(ownerID);
		}
	}
}

void StructurePermissionList::migrateLists(ZoneServer* zoneServer, uint64 ownerObjectID) {
	Locker locker(&lock);

	ManagedReference<GuildManager*> guildManager = zoneServer->getGuildManager();
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	for (int i = 0; i < permissionLists.size(); i++) {
		String listName = permissionLists.elementAt(i).getKey();
		addList(listName);

		SortedVector<String>* list = &permissionLists.get(i);

		for (int j = 0; j < list->size(); j++) {
			String name = list->get(j);

			if (name.beginsWith("guild:")) {
				String abbrev = name.replaceAll("guild:","");

				if (abbrev == "" || !guildManager->guildAbbrevExists(abbrev)) {
					continue;
				}

				ManagedReference<GuildObject*> guild = guildManager->getGuildFromAbbrev(abbrev);

				if (guild == NULL) {
					continue;
				}

				grantPermission(listName, guild->getObjectID());

			} else {
				if (!playerManager->existsName(name)) {
					continue;
				}

				ManagedReference<CreatureObject*> player = playerManager->getPlayer(name);

				if (player == NULL || !player->isPlayerCreature()) {
					continue;
				}

				grantPermission(listName, player->getObjectID());
			}
		}
	}

	ownerID = ownerObjectID;

	permissionLists.removeAll();
}
