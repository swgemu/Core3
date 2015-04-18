/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TANGIBLEOBJECTMESSAGE6_H_
#define TANGIBLEOBJECTMESSAGE6_H_

#include "../BaseLineMessage.h"

#include "server/zone/objects/tangible/TangibleObject.h"

class TangibleObjectMessage6 : public BaseLineMessage {
public:
	TangibleObjectMessage6(TangibleObject* tano, uint32 objType = 0x54414E4F, uint16 opcnt = 0x02)
			: BaseLineMessage(tano->getObjectID(), objType, 6, opcnt) {
		insertInt(0x76); // 0x3D in creos

		insertDefenders(tano);

		setSize();
	}

	void insertDefenders(TangibleObject* tano) {
		DeltaVector<ManagedReference<SceneObject*> >* defenderList = tano->getDefenderList();
		defenderList->insertToMessage(this);
	}

};

#endif /*TANGIBLEOBJECTMESSAGE6_H_*/
