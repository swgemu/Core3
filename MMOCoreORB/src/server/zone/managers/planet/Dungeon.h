#ifndef DUNGEON_H_
#define DUNGEON_H_

#include "engine/engine.h"
#include "engine/util/u3d/Coordinate.h"

class Dungeon : public Object {

	String dungeonZoneName;
	String name;
	Vector<int> cells;
	Vector3 ejectionPoint;

public:
	Dungeon(const String& zoneName) {
		dungeonZoneName = zoneName;
	}

	Dungeon(const String& zoneName, const String& dungeonName, Vector<int> cellList, Vector3 eject) {
			dungeonZoneName = zoneName;
			name = dungeonName;
			cells = cellList;
			ejectionPoint = eject;
	}

	Dungeon(const Dungeon& dun) : Object() {
		dungeonZoneName = dun.dungeonZoneName;
		name = dun.name;
		cells = dun.cells;
		ejectionPoint = dun.ejectionPoint;
	}

	Dungeon& operator= (const Dungeon& dun) {
		if (this == &dun)
			return *this;

		dungeonZoneName = dun.dungeonZoneName;
		name = dun.name;
		cells = dun.cells;
		ejectionPoint = dun.ejectionPoint;

		return *this;
	}

	void readLuaObject(LuaObject* luaObject) {
		name = luaObject->getStringField("name");

		LuaObject cellList = luaObject->getObjectField("cells");

		for (int i = 1; i <= cellList.getTableSize(); ++i) {
			int cell = cellList.getIntAt(i);
			cells.add(cell);
		}

		cellList.pop();

		ejectionPoint.set(
				luaObject->getFloatField("ejectX"),
				luaObject->getFloatField("ejectZ"),
				luaObject->getFloatField("ejectY")
		);
	}

	void setDungeonZoneName(const String& zone){
		dungeonZoneName = zone;
	}

	inline String& getDungeonZoneName() {
		return dungeonZoneName;
	}

	void setName(const String& dungeonName){
		name = dungeonName;
	}

	inline String& getName() {
		return name;
	}

	inline float getEjectionPointX() const {
		return ejectionPoint.getX();
	}

	inline float getEjectionPointY() const {
		return ejectionPoint.getY();
	}

	inline float getEjectionPointZ() const {
		return ejectionPoint.getZ();
	}

	inline Vector3 getEjectionPoint() const {
		return ejectionPoint;
	}

	inline Vector<int> getCells() const {
		return cells;
	}

	/**
	 * Returns true if this dungeon is has the same zone and name that is passed in.
	 */
	inline bool isDungeon(const String& zoneName, const String& dungeonName) {
		return (dungeonZoneName == zoneName && name == dungeonName);
	}

};

#endif /* DUNGEON_H_ */
