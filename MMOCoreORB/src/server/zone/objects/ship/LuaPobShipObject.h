#ifndef LUAPOBSHIPOBJECT_H_
#define LUAPOBSHIPOBJECT_H_

#include "engine/engine.h"
#include "server/zone/objects/tangible/LuaTangibleObject.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {

class PobShipObject;

class LuaPobShipObject : public LuaTangibleObject {
public:
	// Constants
	static const char className[];
	static Luna<LuaPobShipObject>::RegType Register[];

	// Initialize the pointer
	LuaPobShipObject(lua_State* L);
	~LuaPobShipObject();

	int _setObject(lua_State* L);
	int repairInteriorComponent(lua_State* L);

private:
	PobShipObject* realObject;
};

} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship;

#endif /*LUAPOBSHIPOBJECT_H_ */