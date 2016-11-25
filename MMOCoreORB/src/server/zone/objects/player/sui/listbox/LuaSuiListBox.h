
#ifndef LUASUILISTBOX_H_
#define LUASUILISTBOX_H_

#include "engine/engine.h"
#include "server/zone/objects/player/sui/LuaSuiBox.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace sui {
namespace listbox {
	class SuiListBox;

	class LuaSuiListBox : public LuaSuiBox {
	public:
		static const char className[];
		static Luna<LuaSuiListBox>::RegType Register[];

		LuaSuiListBox(lua_State *L);
		~LuaSuiListBox();

		int _setObject(lua_State* L);

		int getMenuSize(lua_State* L);
		int getMenuItemName(lua_State* L);
		int getMenuObjectID(lua_State* L);

	private:
		Reference<SuiListBox*> realObject;
	};

}
}
}
}
}
}

using namespace server::zone::objects::player::sui::listbox;


#endif /* LUASUILISTBOX_H_ */
