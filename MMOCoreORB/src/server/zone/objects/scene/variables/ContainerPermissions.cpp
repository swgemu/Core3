/*
 * ContainerPermissions.cpp
 *
 *  Created on: 02/02/2012
 *      Author: victor
 */

#include "ContainerPermissions.h"

ContainerPermissions::ContainerPermissions() : groupPermissions(3, 1), ownerID(0), inheritPermissionsFromParent(true) {
	groupPermissions.put(String("owner").hashCode(), 0xFFFF0000);

	groupPermissions.setNullValue((uint32)MOVECONTAINER << 16);
}

void ContainerPermissions::setDefaultAllowPermission(uint16 permission) {
	uint32 defaultPermissions = groupPermissions.getNullValue();
	uint32 fullPerm = ((uint32)permission) << 16;

	if (!(defaultPermissions & fullPerm)) {
		defaultPermissions |= fullPerm;

		groupPermissions.setNullValue(defaultPermissions);
	}
}

void ContainerPermissions::clearDefaultAllowPermission(uint16 permission) {
	uint32 fullPerm = (uint32)permission << 16;
	uint64 oldPerm = groupPermissions.getNullValue();

	if (oldPerm & fullPerm) {
		oldPerm -= fullPerm;

		groupPermissions.setNullValue(oldPerm);
	}
}

void ContainerPermissions::setDefaultDenyPermission(uint16 permission) {
	uint32 defaultPermissions = groupPermissions.getNullValue();

	if (!(defaultPermissions & permission)) {
		defaultPermissions |= permission;

		groupPermissions.setNullValue(defaultPermissions);
	}
}

void ContainerPermissions::clearDefaultDenyPermission(uint16 permission) {
	uint32 oldPerm = groupPermissions.getNullValue();

	if ((oldPerm & permission)) {
		oldPerm -= permission;

		groupPermissions.setNullValue(oldPerm);
	}
}

bool ContainerPermissions::hasPermission(const String& group, uint16 permission) {
	return hasPermission(group.hashCode(), permission);
}

uint16 ContainerPermissions::getAllowPermissions(const String& group) {
	return getAllowPermissions(group.hashCode());
}

uint16 ContainerPermissions::getDenyPermissions(const String& group) {
	return getDenyPermissions(group.hashCode());
}

void ContainerPermissions::setAllowPermission(const String& group, uint16 permission) {
	setAllowPermission(group.hashCode(), permission);
}

void ContainerPermissions::setDenyPermission(const String& group, uint16 permission) {
	setDenyPermission(group.hashCode(), permission);
}

void ContainerPermissions::clearAllowPermission(const String& group, uint16 permission) {
	clearAllowPermission(group, permission);
}

void ContainerPermissions::clearDenyPermission(const String& group, uint16 permission) {
	clearDenyPermission(group.hashCode(), permission);
}

bool ContainerPermissions::hasPermission(uint32 group, uint16 permission) {
	uint32 fullPerm = groupPermissions.get(group);

	uint16 allow = (uint16)(fullPerm >> 16);
	uint16 deny = (uint16)(fullPerm & 0x0000FFFF);

	return permission & (allow & ~deny);
}

bool ContainerPermissions::hasOwnerPermission(uint16 permission) {
	return hasPermission("owner", permission);
}

void ContainerPermissions::setAllowPermission(uint32 group, uint16 permission) {
	uint32 oldPerm = groupPermissions.get(group);
	uint32 fullPerm = ((uint32)permission) << 16;

	if (!(oldPerm & fullPerm)) {
		oldPerm |= fullPerm;

		groupPermissions.put(group, oldPerm);
	}
}

void ContainerPermissions::setDenyPermission(uint32 group, uint16 permission) {
	uint32 oldPerm = groupPermissions.get(group);

	if (!(oldPerm & permission)) {
		oldPerm |= permission;

		groupPermissions.put(group, oldPerm);
	}
}

void ContainerPermissions::clearAllowPermission(uint32 group, uint16 permission) {
	uint32 fullPerm = (uint32)permission << 16;
	uint64 oldPerm = groupPermissions.get(group);

	if (oldPerm & fullPerm) {
		oldPerm -= fullPerm;

		groupPermissions.put(group, oldPerm);
	}
}

void ContainerPermissions::clearDenyPermission(uint32 group, uint16 permission) {
	uint32 oldPerm = groupPermissions.get(group);

	if ((oldPerm & permission)) {
		oldPerm -= permission;

		groupPermissions.put(group, oldPerm);
	}
}

bool ContainerPermissions::toBinaryStream(ObjectOutputStream* stream) {
	TypeInfo<HashTable<uint32, uint32> >::toBinaryStream(&groupPermissions, stream);
	TypeInfo<uint64>::toBinaryStream(&ownerID, stream);
	TypeInfo<bool>::toBinaryStream(&inheritPermissionsFromParent, stream);

	return true;
}

bool ContainerPermissions::parseFromBinaryStream(ObjectInputStream* stream) {
	TypeInfo<HashTable<uint32, uint32> >::parseFromBinaryStream(&groupPermissions, stream);
	TypeInfo<uint64>::parseFromBinaryStream(&ownerID, stream);
	TypeInfo<bool>::parseFromBinaryStream(&inheritPermissionsFromParent, stream);

	return true;
}
