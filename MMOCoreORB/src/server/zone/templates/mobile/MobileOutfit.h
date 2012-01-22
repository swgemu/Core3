/*
 * MobileOutfit.h
 *
 *  Created on: 22/01/2012
 *      Author: victor
 */

#ifndef MOBILEOUTFIT_H_
#define MOBILEOUTFIT_H_

#include "engine/engine.h"

class OutfitTangibleObject : public Object {
	String objectTemplate;
	VectorMap<String, uint8> customizationVariables;
public:
	OutfitTangibleObject() {

	}

	OutfitTangibleObject(const OutfitTangibleObject& o) : Object() {
		objectTemplate = o.objectTemplate;
		customizationVariables = o.customizationVariables;
	}

	OutfitTangibleObject& operator=(const OutfitTangibleObject& o) {
		if (this == &o)
			return *this;

		objectTemplate = o.objectTemplate;
		customizationVariables = o.customizationVariables;

		return *this;
	}

	void readObject(LuaObject* luaObject) {
		objectTemplate = luaObject->getStringField("objectTemplate");

		LuaObject table = luaObject->getObjectField("customizationVariables");

		for (int i = 1; i <= table.getTableSize(); ++i) {
			LuaObject var = table.getObjectAt(i);

			String name = var.getStringAt(1);
			uint8 val = var.getIntAt(2);

			customizationVariables.put(name, val);

			var.pop();
		}

		table.pop();
	}

	String getObjectTemplate() {
		return objectTemplate;
	}

	VectorMap<String, uint8>* getCustomizationVariables() {
		return &customizationVariables;
	}
};

class MobileOutfit : public Object {
	Vector<OutfitTangibleObject> objects;
public:
	MobileOutfit() {

	}

	MobileOutfit(const MobileOutfit& o) : Object() {
		objects = o.objects;
	}

	MobileOutfit& operator=(const MobileOutfit& o) {
		if (this == &o)
			return *this;

		objects = o.objects;

		return *this;
	}

	void readObject(LuaObject* luaObject) {
		for (int i = 1; i < luaObject->getTableSize(); ++i) {
			LuaObject obj = luaObject->getObjectAt(i);

			MobileOutfit outfit;
			outfit.readObject(&obj);

			obj.pop();
		}
	}

	Vector<OutfitTangibleObject>* getObjects() {
		return &objects;
	}

};

#endif /* MOBILEOUTFIT_H_ */
