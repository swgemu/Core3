/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYCLIENTEFFECTLOC_H_
#define PLAYCLIENTEFFECTLOC_H_

#include "engine/service/proto/BaseMessage.h"

class PlayClientEffectLoc : public BaseMessage {
public:
	int listSize;
	
	PlayClientEffectLoc(const String& file, const String& zoneName,
			float x, float z, float y, uint64 cell = 0,
			int terrainDelta = 0, const String& label = "") : BaseMessage(), listSize(0) {
		/* Struct
		 * 09 00 // Operand
		 * 74 9E 94 02 // Opcode
		 * A_STRING (effect)
		 * A_STRING (planet)
		 * FLOAT // X
		 * FLOAT // Z
		 * FLOAT // Y
		 * 00 00 00 00 00 00 00 00
		 * 00 00 00 00
		 */
		insertShort(9);
		insertInt(0x02949E74);
		insertAscii(file);
		insertAscii(zoneName);
		insertFloat(x);
		insertFloat(z);
		insertFloat(y);
		insertLong(cell);
		insertInt(terrainDelta);
		insertAscii(label);
	} 

};
#endif /*PLAYCLIENTEFFECTLOC_H_*/
