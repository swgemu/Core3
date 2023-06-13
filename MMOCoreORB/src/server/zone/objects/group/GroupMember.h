/*
 * GroupMember.h
 *
 *  Created on: 29/12/2009
 *      Author: victor
 */

#ifndef GROUPMEMBER_H_
#define GROUPMEMBER_H_

#include "engine/engine.h"
#include "engine/util/json_utils.h"

namespace server {
namespace zone {
namespace objects {
namespace group {

class GroupMember : public Object {
	uint64 memberID;
	String memberName;
	uint64 shipID;

public:
	GroupMember() {
		memberID = 0;
		memberName = "";
		shipID = 0;
	}

	GroupMember(uint64 memID, String name, uint64 shipID);

	GroupMember(const GroupMember& obj) : Object() {
		memberID = obj.memberID;
		memberName = obj.memberName;
		shipID = obj.shipID;
	}

	GroupMember& operator=(const GroupMember& obj);

	void to_json(nlohmann::json& j, const GroupMember& m) {
		j["memberID"] = m.memberID;
		j["memberName"] = m.memberName;
		j["shipID"] = m.shipID;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		stream->writeLong(memberID);
		memberName.toBinaryStream(stream);
		stream->writeLong(shipID);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		memberID = stream->readLong();
		memberName.parseFromBinaryStream(stream);
		shipID = stream->readLong();

		return true;
	}

	void updateMemberShipID(uint64 shipid) {
		shipID = shipid;
	}

	uint64 getMemberID() {
		return memberID;
	}

	String getMemberName() {
		return memberName;
	}

	uint64 getMemberShipID() {
		return shipID;
	}
};
}
}
}
}
using namespace server::zone::objects::group;

#endif /* GROUPMEMBER_H_ */
