/*
 * GroupShipList.h
*/

#ifndef GROUPSHIPLIST_H_
#define GROUPSHIPLIST_H_

#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "GroupMemberShip.h"

class GroupShipList : public DeltaVector<GroupMemberShip> {

};

#endif /* GROUPSHIPLIST_H_ */
