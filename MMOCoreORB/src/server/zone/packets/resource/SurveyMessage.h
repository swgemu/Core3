/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SURVEY_H_
#define SURVEY_H_

#include "engine/service/proto/BaseMessage.h"

class SurveyMessage : public BaseMessage {
public:
	int listSize;
	
	SurveyMessage() : BaseMessage() {
		/* Struct
		 * 02 00 // Operand
		 * AC 79 7F 87 // Opcode
		 * INT // Number of resources in list
		 * {
		 * FLOAT // X
		 * FLOAT // Z (00 00 00 00)
		 * FLOAT // Y
		 * FLOAT // Percentage
		 * }
		 */
		
		insertShort(2);
		insertInt(0x877F79AC);
		insertInt(0);
		listSize = 0;
	} 
	
	void add(float loc_x, float loc_y, float percentage) {
		insertFloat(loc_x);
		insertFloat(0);
		insertFloat(loc_y);
		insertFloat(percentage);
		updateSize();
	}
	
	void updateSize() {
		insertInt(10,++listSize);
	}

};
#endif /*SURVEY_H_*/
