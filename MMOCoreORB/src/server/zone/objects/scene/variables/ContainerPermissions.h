/*
 * ContainerPermissions.h
 *
 *  Created on: 01/02/2012
 *      Author: victor
 */

#ifndef CONTAINERPERMISSIONS_H_
#define CONTAINERPERMISSIONS_H_

#include "engine/engine.h"

/**
 * Permissions: highest 16 bits allow, lowest 16 bits deny
 */
namespace server {
 namespace zone {
  namespace objects {
   namespace scene {
    namespace variables {

    class ContainerPermissions : public Variable {
    	HashTable<uint32, uint32> groupPermissions;
    	uint64 ownerID;
    	bool inheritPermissionsFromParent;

    public:
    	const static uint16 OPEN = 1;
    	const static uint16 MOVEIN = 1 << 1;
    	const static uint16 MOVEOUT = 1 << 2;
    	const static uint16 MOVECONTAINER = 1 << 3;

    	ContainerPermissions();

    	bool hasPermission(const String& group, uint16 permission);

    	uint16 getAllowPermissions(const String& group);
    	uint16 getDenyPermissions(const String& group);

    	void setAllowPermission(const String& group, uint16 permission);
    	void setDenyPermission(const String& group, uint16 permission);
    	void clearAllowPermission(const String& group, uint16 permission);
    	void clearDenyPermission(const String& group, uint16 permission);

    	bool hasPermission(uint32 group, uint16 permission);
    	bool hasOwnerPermission(uint16 permission);

    	void setAllowPermission(uint32 group, uint16 permission);
    	void setDenyPermission(uint32 group, uint16 permission);
    	void clearAllowPermission(uint32 group, uint16 permission);
    	void clearDenyPermission(uint32 group, uint16 permission);

    	void setDefaultAllowPermission(uint16 permission);
    	void clearDefaultAllowPermission(uint16 permission);

    	void setDefaultDenyPermission(uint16 permission);
    	void clearDefaultDenyPermission(uint16 permission);

    	bool toBinaryStream(ObjectOutputStream* stream);
    	bool parseFromBinaryStream(ObjectInputStream* stream);

    	uint64 getOwnerID() {
    		return ownerID;
    	}

    	bool hasInheritPermissionsFromParent() {
    		return inheritPermissionsFromParent;
    	}

    	uint16 getAllowPermissions(uint32 group) {
    		return (uint16)(groupPermissions.get(group) >> 16);
    	}

    	uint16 getDenyPermissions(uint32 group) {
    		return (uint16)(groupPermissions.get(group) & 0x0000FFFF);
    	}

    	uint32 getFullPermissions(uint32 group) {
    		return groupPermissions.get(group);
    	}

    	uint32 getFullPermissions(const String& group) {
    		return groupPermissions.get(group.hashCode());
    	}

    	void setOwner(uint64 id) {
    		ownerID = id;
    	}

    	void setInheritPermissionsFromParent(bool val) {
    		inheritPermissionsFromParent = val;
    	}

    };

    }
   }
  }
 }
}

using namespace server::zone::objects::scene::variables;

#endif /* CONTAINERPERMISSIONS_H_ */
