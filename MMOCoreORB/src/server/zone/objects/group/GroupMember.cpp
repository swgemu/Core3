/*
* GroupMember.cpp
*/

#include "GroupMember.h"

GroupMember::GroupMember(uint64 memberid, String name, uint64 shipid) : Object() {
	memberID = memberid;
	memberName = name;
	shipID = shipid;
}

GroupMember& GroupMember::operator=(const GroupMember& memInf) {
	if (this == &memInf)
		return *this;

	memberID = memInf.memberID;
	memberName = memInf.memberName;
	shipID = memInf.shipID;

	return *this;
}