//
// Created by g on 12/15/17.
//

#include "server/zone/managers/space/SpaceManager.h"
#include "server/zone/managers/object/ObjectManager.h"

void SpaceManagerImplementation::loadLuaConfig() {
    String planetName = zone->getZoneName();

    Lua* lua = new Lua();
    lua->init();

    lua->runFile("scripts/managers/planet_manager.lua");

    //Get's the configuration settings object for this planet.
    LuaObject base = lua->getGlobalObject(planetName);

    if (base.isValidTable()) {
        LuaObject luaObject = base.getObjectField("planetObjects");
        if (!luaObject.isValidTable())
            return;

        for (int i = 1; i <= luaObject.getTableSize(); ++i) {
            lua_State* L = luaObject.getLuaState();
            lua_rawgeti(L, -1, i);

            LuaObject planetObject(L);

            String templateFile = planetObject.getStringField("templateFile");
            info("Attempting to load " + templateFile, true);

            ManagedReference<SceneObject*> obj = ObjectManager::instance()->createObject(templateFile.hashCode(), 0, "");

            if (obj != nullptr) {
                Locker objLocker(obj);

                float x = planetObject.getFloatField("x");
                float y = planetObject.getFloatField("y");
                float z = planetObject.getFloatField("z");
                float ox = planetObject.getFloatField("ox");
                float oy = planetObject.getFloatField("oy");
                float oz = planetObject.getFloatField("oz");
                float ow = planetObject.getFloatField("ow");
                uint64 parentID = planetObject.getLongField("parent");

                obj->initializePosition(x, z, y);
                obj->setDirection(ow, ox, oy, oz);

                ManagedReference<SceneObject*> parent = zone->getZoneServer()->getObject(parentID);

                if (parent != nullptr)
                    parent->transferObject(obj, -1, true);
                else
                    zone->transferObject(obj, -1, true);

                obj->createChildObjects();
            }

            planetObject.pop();
        }
    }
}
