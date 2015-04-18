/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHOWFLYTEXT_H_
#define SHOWFLYTEXT_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/scene/SceneObject.h"

namespace server {
namespace zone {
namespace packets {
namespace object {


class ShowFlyText : public ObjectControllerMessage {
public:
	ShowFlyText(SceneObject* creo, const String& file, const String& aux, uint8 red, uint8 green, uint8 blue)
			: ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x1BD) {
		insertLong(creo->getObjectID());
		
		insertAscii(file.toCharArray());
		insertInt(0);		
		insertAscii(aux.toCharArray());
		insertInt(0);
		insertByte(red);
		insertByte(green);
		insertByte(blue);
		insertByte(5);// unk
	}

};

}
}
}
}

#endif /*SHOWFLYTEXT_H_*/
