#include "CreatureObject.h"

CreatureObject::CreatureObject(LuaObject* templateData) : TangibleObject(templateData) {
	setLoggingName("CreatureObject");

}

void CreatureObject::parseBaseline3(Message* message) {
	TangibleObject::parseBaseline3(message);


}

