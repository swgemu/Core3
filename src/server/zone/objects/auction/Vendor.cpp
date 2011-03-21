/*
 * Vendor.cpp
 *
 *  Created on: Mar 15, 2011
 *      Author: polonel
 */

#include "Vendor.h"
#include "server/zone/managers/object/ObjectManager.h"

Vendor::Vendor() {
	ownerID = 0;
	location = "";
	vendorType = 0;
	vendorRef = NULL;
	initialized = false;

	vendorItems.setNullValue(NULL);
	vendorItems.setNoDuplicateInsertPlan();

	addSerializableVariables();
}

Vendor::Vendor(const Vendor& v) : Object(), Serializable() {
	vendorItems = v.vendorItems;
	ownerID = v.ownerID;
	location = v.location;
	vendorType = v.vendorType;
	initialized = v.initialized;

	addSerializableVariables();
}

Vendor::~Vendor() {

}
