/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHOWFLYTEXT_H_
#define SHOWFLYTEXT_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/scene/SceneObject.h"

class ShowFlyText : public ObjectControllerMessage {
public:
	ShowFlyText(SceneObject* creo, const String& file, const String& aux, uint8 red, uint8 green, uint8 blue, float size)
			: ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x1BD) {
		insertLong(creo->getObjectID()); // Target object ID

		insertAscii(file.toCharArray()); // StringId file
		insertInt(0); // Spacer
		insertAscii(aux.toCharArray()); // StringId entry
		insertFloat(size); // Scale, 1.0 for broadcasted, 0 for none.
		insertByte(red); // R
		insertByte(green); // G
		insertByte(blue); // B

		 /* enum Flags
		  * {
		  * 0x0001, -- Only shown on target.
		  * 0x0002, -- show in chat box?
		  * 0x0004, -- ???
		  */
		insertByte(5); // FLAGS. 5 = Displayed on target, possible bitmask of 1+4?
		
	}

};

#endif /*SHOWFLYTEXT_H_*/
