/*
 * GroupList.h
 */

#ifndef GROUPLIST_H_
#define GROUPLIST_H_

#include "engine/engine.h"
#include "engine/util/json_utils.h"

#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "GroupMember.h"

class GroupList : public DeltaVector<GroupMember*>, public Logger {
private:
	void getMemberIdList(Vector<uint64>& memberIDs) const;

public:
	bool toBinaryStream(ObjectOutputStream* stream) override;
	bool parseFromBinaryStream(ObjectInputStream* stream) override;

	friend void to_json(nlohmann::json& j, const GroupList& l);

	void insertToMessage(BaseMessage* msg) const override;

	void updateMemberShipID(uint64 memberID, uint64 shipID, DeltaMessage* message = nullptr);

	void removeMember(uint64 memberID) {
		if (memberID == 0)
			return;

		for (int i = 0; i < size(); ++i) {
			GroupMember* member = get(i);

			if (member == nullptr || member->getMemberID() != memberID)
				return;

			remove(i);
			return;
		}
	}

	uint64 getMemberID(int indx) {
		if (indx < 0 || indx >= size())
			return 0;

		GroupMember* member = get(indx);

		if (member == nullptr)
			return 0;

		return member->getMemberID();
	}

	String getMemberName(int indx) {
		if (indx < 0 || indx >= size())
			return 0;

		GroupMember* member = get(indx);

		if (member == nullptr)
			return 0;

		return member->getMemberName();
	}

	uint64 getMemberShipID(int indx) {
		if (indx < 0 || indx >= size())
			return 0;

		GroupMember* member = get(indx);

		if (member == nullptr)
			return 0;

		return member->getMemberShipID();
	}
};

using namespace server::zone::objects::group;

#endif /* GROUPLIST_H_ */
