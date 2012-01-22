/*
 * MobileOutfitGroup.h
 *
 *  Created on: 22/01/2012
 *      Author: victor
 */

#ifndef MOBILEOUTFITGROUP_H_
#define MOBILEOUTFITGROUP_H_

#include "MobileOutfit.h"

class MobileOutfitGroup : public Object {
	Vector<MobileOutfit> outfits;
public:
	MobileOutfitGroup() {

	}

	MobileOutfitGroup(const MobileOutfitGroup& o) : Object() {
		outfits = o.outfits;
	}

	MobileOutfitGroup& operator=(const MobileOutfitGroup& o) {
		if (this == &o)
			return *this;

		outfits = o.outfits;

		return *this;
	}

	void readObject(LuaObject* luaObject) {
		//LuaObject outfit = templateData->getObjectField("outfit");

		for (int i = 1; i <= luaObject->getTableSize(); ++i) {
			LuaObject obj = luaObject->getObjectAt(i);

			MobileOutfit outfit;
			outfit.readObject(&obj);

			obj.pop();
		}
	}

	Vector<MobileOutfit>* getOutfits() {
		return &outfits;
	}

};


#endif /* MOBILEOUTFITGROUP_H_ */
