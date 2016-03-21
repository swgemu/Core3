#include "CreatureObject.h"

CreatureObject::CreatureObject(SharedObjectTemplate* templateData) : TangibleObject(templateData) {
	setLoggingName("CreatureObject");

	actionCount = 0;
}

void CreatureObject::parseBaseline3(Message* message) {
	TangibleObject::parseBaseline3(message);


}

