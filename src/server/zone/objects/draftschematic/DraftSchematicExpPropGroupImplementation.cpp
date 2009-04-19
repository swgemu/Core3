/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
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

In addition, as a special exception, the copyright holders of Engine3minValue
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

#include "DraftSchematicExpPropGroupImplementation.h"

#include "../../packets/object/ObjectControllerMessage.h"

DraftSchematicExpPropGroupImplementation::DraftSchematicExpPropGroupImplementation(String Title, String Subtitle)
	: DraftSchematicExpPropGroupServant() {

	title = Title;

	subtitle = Subtitle;

	expPropGroupListSize = 0;

	filler = true;

	minValue = 0.f;
	maxValue = 0.f;

	decimalPrecision = 0;
}
DraftSchematicExpPropGroupImplementation::DraftSchematicExpPropGroupImplementation(
		DraftSchematicExpPropGroup* group) :
	DraftSchematicExpPropGroupServant() {

	minValue = group->getMinValue();
	maxValue = group->getMaxValue();

	decimalPrecision = group->getPrecision();

	filler = group->isFiller();

	expPropGroupListSize = 0;

	title = group->getTitle();
	subtitle = group->getSubtitle();

	for (int i = 0; i < group->getKeyCount(); ++i) {
		keys.add(group->getKey(i));
		expPropGroupListSize++;
	}

	for (int i = 0; i < group->getExpPropTypesSize(); ++i) {
		expPropTypes.put(group->getExpPropTypesKey(i),
				group->getExpPropTypesValue(i));
	}

	for (int i = 0; i < group->getExpPropWeightsSize(); ++i) {
		expPropWeights.put(group->getExpPropWeightsKey(i),
				group->getExpPropWeightsValue(i));
	}

	for (int i = 0; i < group->getExpPropWeightPercentagesSize(); ++i) {
		expPropWeightPercentages.put(group->getExpPropWeightPercentagesKey(i),
				group->getExpPropWeightPercentagesValue(i));
	}
}

DraftSchematicExpPropGroupImplementation::~DraftSchematicExpPropGroupImplementation(){

		keys.removeAll();

		expPropTypes.removeAll();
		expPropWeights.removeAll();
		expPropWeightPercentages.removeAll();

	}

void DraftSchematicExpPropGroupImplementation::addExperimentalProperty(const String& experimentalPropertyType,
		uint32 weight, float min, float max, int precision) {

	if(minValue != min)
		minValue = min;

	if(maxValue != max)
		maxValue = max;

	if(decimalPrecision != precision)
		decimalPrecision = precision;

	uint8 expPropType = 0x00;

	if (experimentalPropertyType == "PO") {
		// nothing needs to be done
	} else if (experimentalPropertyType == "CR") {
		expPropType = 0x01;
		filler = false;
	} else if (experimentalPropertyType == "CD") {
		expPropType = 0x02;
		filler = false;
	} else if (experimentalPropertyType == "DR") {
		expPropType = 0x03;
		filler = false;
	} else if (experimentalPropertyType == "HR") {
		expPropType = 0x04;
		filler = false;
	} else if (experimentalPropertyType == "FL") {
		expPropType = 0x05;
		filler = false;
	} else if (experimentalPropertyType == "MA") {
		expPropType = 0x06;
		filler = false;
	} else if (experimentalPropertyType == "PE") {
		expPropType = 0x07;
		filler = false;
	} else if (experimentalPropertyType == "OQ") {
		expPropType = 0x08;
		filler = false;
	} else if (experimentalPropertyType == "SR") {
		expPropType = 0x09;
		filler = false;
	} else if (experimentalPropertyType == "UT") {
		expPropType = 0x0A;
		filler = false;
	} else if (experimentalPropertyType == "BK") {
		expPropType = 0x0B;
		filler = false;
	} else if (experimentalPropertyType == "XX"){
		expPropType = 0x00;
	} else {
		System::out << "Incorrect Experimental Property.  Experimental Property given was: " << experimentalPropertyType;
		return;
	}

	expPropTypes.put(experimentalPropertyType, expPropType);

	if (expPropType != 0x00)
		expPropWeights.put(experimentalPropertyType, weight % 16);
	else
		expPropWeights.put(experimentalPropertyType, 0x00);

	keys.add(experimentalPropertyType);

	expPropGroupListSize++;

	RecalculatePercentages();
}

/* ---------------------------
	Types using their byte representation:
	0 Potency
	1 CR
	2 CD
	3 DR
	4 HR
	5 FL
	6 MA
	7 PE
	8 OQ
	9 SR
	A UT
	B Bulk
	C obj_attr_n[]:
	D obj_attr_n[]:
	E obj_attr_n[]:
	F obj_attr_n[]:

	------------------------------- */

void DraftSchematicExpPropGroupImplementation::sendToPlayer(ObjectControllerMessage* msg) {
	if (getTypeAndWeight(0) == 0) {
		msg->insertByte(0);
		//msg->insertByte(0x00);
	} else {
		msg->insertByte(expPropGroupListSize);

		for (int i = 0; i < expPropGroupListSize; i++) {
			msg->insertByte(getTypeAndWeight(i));
		}
	}
}

void DraftSchematicExpPropGroupImplementation::sendBatchToPlayer(ObjectControllerMessage* msg) {
	if (getTypeAndWeight(0) == 0) {
		msg->insertByte(0);
		//msg->insertByte(0x00);
	} else {
		msg->insertByte(expPropGroupListSize);

		for (int i = 0; i < expPropGroupListSize; i++) {
			msg->insertByte(getBatchTypeAndWeight(i));
		}
	}
}

// Zero is returned if index is out of bounds
uint8 DraftSchematicExpPropGroupImplementation::getTypeAndWeight(uint32 index) {
	if (index < expPropTypes.size()) {
		uint8 typeAndWeight =  expPropTypes.get(index);

		typeAndWeight = (typeAndWeight << 4);
		typeAndWeight += expPropWeights.get(index);

		return typeAndWeight;
	} else
		return 0x00;  // 0
}

uint8 DraftSchematicExpPropGroupImplementation::getBatchTypeAndWeight(uint32 index) {
	if (index < expPropTypes.size()) {
		uint8 typeAndWeight =  expPropTypes.get(index);

		typeAndWeight = (typeAndWeight << 4);
		typeAndWeight += 1;

		return typeAndWeight;
	} else
		return 0x00;  // 0
}

void DraftSchematicExpPropGroupImplementation::RecalculatePercentages() {
	float denominator = 0;

	for (int i = 0; i < expPropWeights.size(); i++) {
		denominator += expPropWeights.get(i);
	}

	expPropWeightPercentages.removeAll();

	if (expPropWeights.size() == expPropTypes.size()) {
		for (int i = 0; i < expPropWeights.size(); i++) {
			float weight = expPropWeights.get(i);
			expPropWeightPercentages.put(keys.get(i), weight / denominator);
		}
	} else {
		System::out << "\nError recalculating percentages for experimental properties.\n(Experimental Property types and weights lists"
		"are not the same size)\n";
	}
}
