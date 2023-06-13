/*
 * GroupMemberShip.h
 */

#ifndef GROUPMEMBERSHIP_H_
#define GROUPMEMBERSHIP_H_

#include "engine/util/json_utils.h"

namespace server {
	namespace zone {
		namespace objects {
			namespace ship {
				class ShipObject;
			}
		}
	}
}

using namespace server::zone::objects::ship;

class GroupMemberShip : public Variable {
	ManagedReference<ShipObject*> ship;

public:
	GroupMemberShip() {
		ship = nullptr;
	}

	GroupMemberShip(const GroupMemberShip& obj) : Variable() {
		ship = obj.ship;
	}

	GroupMemberShip(ShipObject* obj) {
		ship = obj;
	}

	GroupMemberShip& operator=(const GroupMemberShip& obj) {
		if (this == &obj) {
			return *this;
		}

		ship = obj.ship;

		return *this;
	}

	bool operator==(const GroupMemberShip& member) const {
		return ship.get() == member.ship.get();
	}

	bool operator==(ShipObject* member) const {
		return ship.get() == member;
	}

	void operator=(ShipObject* obj) {
		ship = obj;
	}

	Reference<ShipObject*> operator->() const {
		return ship.get();
	}

	Reference<ShipObject*> get() {
		return ship.get();
	}

	operator Reference<ShipObject*>() const {
		return ship.get();
	}

	bool toString(String& str) {
		return ship.toString(str);
	}

	bool parseFromString(const String& str, int version = 0) {
		return ship.parseFromString(str, version);
	}

	friend void to_json(nlohmann::json& j, const GroupMemberShip& m);

	bool toBinaryStream(ObjectOutputStream* stream);

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		ship.parseFromBinaryStream(stream);

		if (ship == nullptr)
			return false;

		String name;

		name.parseFromBinaryStream(stream);

		return true;
	}

};


#endif /* GROUPMEMBERSHIP_H_ */
