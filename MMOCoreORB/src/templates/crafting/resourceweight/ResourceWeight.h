/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESOURCEWEIGHT_H_
#define RESOURCEWEIGHT_H_

#include "system/lang.h"
#include "engine/service/proto/BaseMessage.h"

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
	ResourceWeight() : minValue(0), maxValue(0), precision(0), filler(true), combineType(0) {
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
