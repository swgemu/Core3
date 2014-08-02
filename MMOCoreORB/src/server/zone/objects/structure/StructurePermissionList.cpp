/*
 * StructurePermissionList.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "StructurePermissionList.h"
#include "server/zone/packets/ui/PermissionListCreateMessage.h"
#include "server/zone/ZoneServer.h"

StructurePermissionList::StructurePermissionList() {
	permissionLists.setNoDuplicateInsertPlan();

	//TODO: Load these from the structure template script.
	addList("ADMIN");
	addList("ENTRY");
	addList("HOPPER");
	addList("BAN");
	addList("VENDOR");
}

StructurePermissionList::StructurePermissionList(const StructurePermissionList& spl) : Object() {
	permissionLists = spl.permissionLists;
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

	_name = "ownerName";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<String>::toBinaryStream(&ownerName, stream);
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
	} else if (name == "ownerName") {
		TypeInfo<String>::parseFromBinaryStream(&ownerName, stream);

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

	if (!permissionLists.contains(listName)) {
		return;
	}

	PermissionListCreateMessage* listMsg = new PermissionListCreateMessage(listName);

	SortedVector<String>* list = &permissionLists.get(listName);

	for (int i = 0; i < list->size(); ++i)
		listMsg->addName(list->get(i));

	listMsg->generateMessage();
	creature->sendMessage(listMsg);
}

int StructurePermissionList::togglePermission(const String& listName, const String& playerName, bool caseSensitive) {
	Locker locker(&lock);

	if(playerName == ownerName)
		return CANTCHANGEOWNER;

	if (!permissionLists.contains(listName))
		return LISTNOTFOUND;

	SortedVector<String>* list = &permissionLists.get(listName);

	String name = "";

	if (caseSensitive)
		name = playerName;
	else
		name = playerName.toLowerCase();

	//If they exist, remove them.
	if (list->contains(name)) {
		list->drop(name);
		return REVOKED;
	}

	list->put(name);
	return GRANTED;
}

int StructurePermissionList::grantPermission(const String& listName, const String& playerName, bool caseSensitive) {
	Locker locker(&lock);

	if(playerName == ownerName)
		return CANTCHANGEOWNER;

	if (!permissionLists.contains(listName))
		return LISTNOTFOUND;

	SortedVector<String>* list = &permissionLists.get(listName);

	if (caseSensitive)
		list->put(playerName);
	else
		list->put(playerName.toLowerCase());

	return GRANTED;
}

int StructurePermissionList::revokePermission(const String& listName, const String& playerName, bool caseSensitive) {
	Locker locker(&lock);

	if(playerName == ownerName)
		return CANTCHANGEOWNER;

	if (!permissionLists.contains(listName))
		return LISTNOTFOUND;

	SortedVector<String>* list = &permissionLists.get(listName);

	if (caseSensitive)
		list->drop(playerName);
	else
		list->drop(playerName.toLowerCase());

	return REVOKED;
}

int StructurePermissionList::revokeAllPermissions(const String& playerName, bool caseSensitive) {
	Locker locker(&lock);

	if(playerName == ownerName)
		return CANTCHANGEOWNER;

	for (int i = 0; i < permissionLists.size(); ++i) {
		SortedVector<String>* list = &permissionLists.get(i);

		if (caseSensitive)
			list->drop(playerName);
		else
			list->drop(playerName.toLowerCase());
	}

	return REVOKED;
}

void StructurePermissionList::revokeAllPermissions() {
	Locker locker(&lock);

	for (int i = 0; i < permissionLists.size(); ++i) {
		SortedVector<String>* list = &permissionLists.get(i);

		list->removeAll();

		if (permissionLists.elementAt(i).getKey() == "ADMIN") {
			list->put(ownerName);
		}
	}
}
