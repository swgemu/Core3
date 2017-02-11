
#ifndef LUACITYREGION_H_
#define LUACITYREGION_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace region {
	class CityRegion;

	class LuaCityRegion {
	public:
		static const char className[];
		static Luna<LuaCityRegion>::RegType Register[];

		LuaCityRegion(lua_State *L);
		~LuaCityRegion();

		int _setObject(lua_State* L);
		int _getObject(lua_State* L);
		int isClientRegion(lua_State* L);

	protected:
		CityRegion* _getRealCityRegion() {
			return realObject.get();
		}

	private:
		Reference<CityRegion*> realObject;
	};

}
}
}
}

using namespace server::zone::objects::region;

#endif /* LUACITYREGION_H_ */
