/*
 * LuaSuiBox.h
 *
 *  Created on: 27/01/2012
 *      Author: xyborn
 */

#ifndef LUASUIBOX_H_
#define LUASUIBOX_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace sui {
	class SuiBox;

	class LuaSuiBox {
	public:
		static const char className[];
		static Luna<LuaSuiBox>::RegType Register[];

		LuaSuiBox(lua_State *L);
		~LuaSuiBox();

		int _setObject(lua_State* L);

		int getUsingObject(lua_State* L);
	private:
		Reference<SuiBox*> realObject;
	};

}
}
}
}
}

using namespace server::zone::objects::player::sui;


#endif /* LUASUIBOX_H_ */
