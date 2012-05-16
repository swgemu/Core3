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

#ifndef RESOURCEWEIGHT_H_
#define RESOURCEWEIGHT_H_

#include "engine/engine.h"

class ResourceWeight : public Object {
private:

	Vector<uint8> properties;
	Vector<short> weights;
	Vector<float> percentages;

	String experimentalTitle;
	String propertyName;

	float minValue, maxValue;
	int precision;

	bool filler;

	short combineType;

public:
	ResourceWeight() {
		filler = true;
	}

	~ResourceWeight() {

	}

	void addProperties(const String& title, const String& name, float min, float max, int prec, short combine) {
		experimentalTitle = title;
		propertyName = name;
		minValue = min;
		maxValue = max;
		precision = prec;
		combineType = combine;

	}

	void addWeight(const String& property, int weight) {
		short propertyValue = convertStringValue(property);
		properties.add(propertyValue);

		if (propertyValue != 0x00)
			weights.add(weight % 16);
		else
			weights.add(0x00);

		recalculatePercentages();
	}

	void recalculatePercentages() {
		float denominator = 0;

		percentages.removeAll();

		for (int i = 0; i < weights.size(); i++) {
			denominator += weights.get(i);
		}

		for (int i = 0; i < weights.size(); i++) {
			float weight = weights.get(i);
			percentages.add(weight / denominator);
		}
	}

	uint8 convertStringValue(const String& property) {

		uint8 expPropType = 0x00;

		if (property == "PO") {
			// nothing needs to be done
		} else if (property == "CR") {
			expPropType = 0x01;
			filler = false;
		} else if (property == "CD") {
			expPropType = 0x02;
			filler = false;
		} else if (property == "DR") {
			expPropType = 0x03;
			filler = false;
		} else if (property == "HR") {
			expPropType = 0x04;
			filler = false;
		} else if (property == "FL") {
			expPropType = 0x05;
			filler = false;
		} else if (property == "MA") {
			expPropType = 0x06;
			filler = false;
		} else if (property == "PE") {
			expPropType = 0x07;
			filler = false;
		} else if (property == "OQ") {
			expPropType = 0x08;
			filler = false;
		} else if (property == "SR") {
			expPropType = 0x09;
			filler = false;
		} else if (property == "UT") {
			expPropType = 0x0A;
			filler = false;
		} else if (property == "BK") {
			expPropType = 0x0B;
			filler = false;
		} else {
			expPropType = 0x00;
		}
		return expPropType;
	}


	void insertBatchToMessage(BaseMessage* msg) {
		if (getTypeAndWeight(0) == 0) {
			msg->insertByte(0);
			//msg->insertByte(0x00);
		} else {
			msg->insertByte(properties.size());

			for (int i = 0; i < properties.size(); i++) {
				msg->insertByte(getBatchTypeAndWeight(i));
			}
		}
	}

	void insertToMessage(BaseMessage* msg) {
		if (getTypeAndWeight(0) == 0) {
			msg->insertByte(0);
			//msg->insertByte(0x00);
		} else {
			msg->insertByte(properties.size());

			for (int i = 0; i < properties.size(); i++) {
				msg->insertByte(getTypeAndWeight(i));
			}
		}
	}

	int getPropertyListSize() {
		return properties.size();
	}

	// Zero is returned if index is out of bounds
	uint8 getTypeAndWeight(int index) {
		if (index < properties.size()) {
			uint8 typeAndWeight =  properties.get(index);

			typeAndWeight = (typeAndWeight << 4);
			typeAndWeight += weights.get(index);

			return typeAndWeight;
		} else
			return 0x00;  // 0
	}

	uint8 getBatchTypeAndWeight(int index) {
		if (index < properties.size()) {
			uint8 typeAndWeight =  properties.get(index);

			typeAndWeight = (typeAndWeight << 4);
			typeAndWeight += 1;

			return typeAndWeight;
		} else
			return 0x00;  // 0
	}

	float getPropertyPercentage(int index) {

		if (index < percentages.size()) {
			return percentages.get(index);

		} else
			return 0x00;  // 0
	}

	String getExperimentalTitle() {
		return experimentalTitle;
	}

	String getPropertyName() {
		return propertyName;
	}

	float getMinValue() {
		return minValue;
	}

	float getMaxValue() {
		return maxValue;
	}

	int getPrecision() {
		return precision;
	}

	bool isFiller() {
		return filler == true;
	}

	short getCombineType() {
		return combineType;
	}

};

#endif /* RESOURCEWEIGHT_H_ */
