/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LAIROBJECTMESSAGE3_H_
#define LAIROBJECTMESSAGE3_H_

#include "../BaseLineMessage.h"

#include "../tangible/TangibleObjectMessage3.h"

class LairObject;

class LairObjectMessage3 : public TangibleObjectMessage3 {
public:
	LairObjectMessage3(LairObject* tano)
			: TangibleObjectMessage3(tano, 0x54414E4F, 0x0D) {

		setSize();
	}
};

#endif /*LAIROBJECTMESSAGE3_H_*/
