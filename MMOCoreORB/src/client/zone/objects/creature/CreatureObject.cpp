#include "CreatureObject.h"

#include "zone/objects/tangible/TangibleObject.h"

namespace engine {
namespace lua {
class LuaObject;
}  // namespace lua
namespace service {
class Message;
}  // namespace service
}  // namespace engine

CreatureObject::CreatureObject(LuaObject* templateData) : TangibleObject(templateData) {
	setLoggingName("CreatureObject");

	actionCount = 0;
}

void CreatureObject::parseBaseline3(Message* message) {
	TangibleObject::parseBaseline3(message);


}

