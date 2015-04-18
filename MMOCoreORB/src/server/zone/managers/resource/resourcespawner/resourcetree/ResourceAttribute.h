/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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
