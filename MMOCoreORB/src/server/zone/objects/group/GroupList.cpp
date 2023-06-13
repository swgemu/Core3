/*
 * GroupList.cpp
 */

#include "GroupList.h"
#include "GroupMember.h"

//#define DEBUG_GROUPS

void GroupList::insertToMessage(BaseMessage* msg) const {
	ReadLocker locker(getLock());

#ifdef DEBUG_GROUPS
	info(true) << "GroupList::insertToMessage -- Group Size = " << size() << " Update Counter = " << updateCounter;
#endif

	msg->insertInt(size());
	msg->insertInt(size()); //updateCounter ??

	for (int i = 0; i < size(); ++i) {
		GroupMember* memberInfo = get(i);

		msg->insertLong(memberInfo->getMemberID());
		msg->insertAscii(memberInfo->getMemberName());
#ifdef DEBUG_GROUPS
		info(true) << "Inserting ID: " << memberInfo->getMemberID() << " Name: " << memberInfo->getMemberName();
#endif
	}

	// Insert players ships
	msg->insertInt(size());
	msg->insertInt(size());

	for (int i = 0; i < size(); ++i) {
		GroupMember* memberInfo = get(i);

		msg->insertLong(memberInfo->getMemberShipID());
		msg->insertInt(i);

#ifdef DEBUG_GROUPS
		info(true) << "Inserting Ship ID: " << memberInfo->getMemberShipID() << " Position: " << i;
#endif
	}
}

void GroupList::updateMemberShipID(uint64 memberID, uint64 shipID, DeltaMessage* message) {
	if (memberID == 0)
		return;

#ifdef DEBUG_GROUPS
		info(true) << "updateMemberShipID called - Member ID: " << memberID << " Ship ID: " << shipID;
#endif

	message->startUpdate(0x02);

	message->insertInt(0x01);
	message->insertInt(0x03);

	for (int i = 0; i < size(); ++i) {
		GroupMember* member = get(i);

		if (member == nullptr || member->getMemberID() != memberID)
			continue;

		member->updateMemberShipID(shipID);

		if (message != nullptr) {
			message->insertByte(0x02); // Modify on list
			message->insertShort((uint8)i); // Location on list

			message->insertLong(shipID);
			message->insertInt(i);

#ifdef DEBUG_GROUPS
			info(true) << "ShipID added to Delta 6 message - Member ID: " << memberID << " Ship ID: " << shipID << " Location: " << i;
#endif
		}

		return;
	}
}

bool GroupList::toBinaryStream(ObjectOutputStream* stream) {
	TypeInfo<uint32>::toBinaryStream(&updateCounter, stream);

	Vector<uint64> memberIDs;
	getMemberIdList(memberIDs);

	memberIDs.toBinaryStream(stream);

	return true;
}

bool GroupList::parseFromBinaryStream(ObjectInputStream* stream) {
	TypeInfo<uint32>::parseFromBinaryStream(&updateCounter, stream);

	Vector<uint64> memberIDs;
	memberIDs.parseFromBinaryStream(stream);

	return true;
}

void to_json(nlohmann::json& j, const GroupList& l) {
	Vector<uint64> memberIDs;
	l.getMemberIdList(memberIDs);

	j["updateCounter"] = l.updateCounter;
	j["memberIDs"] = memberIDs;
}

void GroupList::getMemberIdList(Vector<uint64>& memberIDs) const {
	for (int i = 0; i < vector.size(); ++i) {
		GroupMember* memberInfo = vector.getUnsafe(i);

		const auto& memberID = memberInfo->getMemberID();

		memberIDs.emplace(memberID);
	}
}
