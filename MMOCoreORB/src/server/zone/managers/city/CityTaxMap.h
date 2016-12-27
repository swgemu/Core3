/*
 * CityTaxMap.h
 *
 *  Created on: Jul 25, 2012
 *      Author: swgemu
 */

#ifndef CITYTAXMAP_H_
#define CITYTAXMAP_H_

#include "CityTax.h"

class CityTaxMap : public Vector<CityTax> {
public:
	void readObject(LuaObject* luaObject) {
		if (!luaObject->isValidTable())
			return;

		for (int i = 1; i <= luaObject->getTableSize(); ++i) {
			LuaObject obj = luaObject->getObjectAt(i);

			if (obj.isValidTable()) {
				CityTax tax;
				tax.readObject(&obj);
				add(tax);
			}

			obj.pop();
		}
	}
};

#endif /* CITYTAXMAP_H_ */
