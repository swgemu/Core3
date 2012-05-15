/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

/**
 * \file ResourceAttribute.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef RESOURCEATTRIBUTE_H_
#define RESOURCEATTRIBUTE_H_

#include "server/zone/managers/crafting/CraftingManager.h"

/**
 * The resource attribute class stores the name
 * of a resource attribute and the min / max value
 */
class ResourceAttribute {
private:
	String name;
	int minimum;
	int maximum;
	int index;

public:
	/**
	 * Constructor
	 * \param n Name of the Attribute
	 * \param min Minimum Value
	 * \param max Maximum Value
	 */
	ResourceAttribute(const String& n, const int min, const int max) {
		name = n;
		minimum = min;
		maximum = max;
		index = 0;

		setIndex(name);
	}

	/**
	 * Destructor
	 */
	~ResourceAttribute() {

	}

	void setIndex(String name) {

		if(name == "res_decay_resist")
			index = CraftingManager::DR;
		else if(name == "res_quality")
			index = CraftingManager::OQ;
		else if(name == "res_flavor")
			index = CraftingManager::FL;
		else if(name == "res_potential_energy")
			index = CraftingManager::PE;
		else if(name == "res_malleability")
			index = CraftingManager::MA;
		else if(name == "res_toughness")
			index = CraftingManager::UT;
		else if(name == "res_shock_resistance")
			index = CraftingManager::SR;
		else if(name == "res_conductivity")
			index = CraftingManager::CD;
		else if(name == "res_cold_resist")
			index = CraftingManager::CR;
		else if(name == "res_heat_resist")
			index = CraftingManager::HR;
	}

	/**
	 * Returns the name of the Attribute
	 */
	String getName() {
		return name;
	}

	/**
	 * Returns the minimum value of the Attribute
	 */
	int getMinimum() {
		return minimum;
	}

	/**
	 * Returns the maximum value of the Attribute
	 */
	int getMaximum() {
		return maximum;
	}

	int getIndex() {
		return index;
	}
};


#endif /* RESOURCEATTRIBUTE_H_ */
