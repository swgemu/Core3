/*
 * ImageDesignData.h
 *
 *  Created on: Feb 16, 2011
 *      Author: crush
 */

#ifndef IMAGEDESIGNDATA_H_
#define IMAGEDESIGNDATA_H_

#include "engine/engine.h"

class ImageDesignData : public Object {
protected:
	String hairTemplate;
	CustomizationVariables hairCustomizationVariables;

	uint32 unknownInt1;
	uint32 timestamp;

	uint32 requiredPayment;
	uint32 offeredPayment;

	uint8 designerAccepted;
	uint32 targetAccepted;

	uint8 statMigrationRequested;

	uint32 unk1;
	uint32 unk2;
	uint32 unk3;
	uint32 unk4;

	VectorMap<String, float> bodyAttributes;
	VectorMap<String, uint32> colorAttributes;

	String holoEmote;

public:
	ImageDesignData() {

	}

	ImageDesignData(const ImageDesignData& idd) : Object() {
		hairTemplate = idd.hairTemplate;
		hairCustomizationVariables = idd.hairCustomizationVariables;
		unknownInt1 = idd.unknownInt1;
		timestamp = idd.timestamp;
		requiredPayment = idd.requiredPayment;
		offeredPayment = idd.offeredPayment;
		designerAccepted = idd.designerAccepted;
		targetAccepted = idd.targetAccepted;
		statMigrationRequested = idd.statMigrationRequested;
		unk1 = idd.unk1;
		unk2 = idd.unk2;
		unk3 = idd.unk3;
		unk4 = idd.unk4;
		bodyAttributes = idd.bodyAttributes;
		colorAttributes = idd.colorAttributes;
		holoEmote = idd.holoEmote;
	}

	ImageDesignData& operator= (const ImageDesignData& idd) {
		if (this == &idd)
			return *this;

		hairTemplate = idd.hairTemplate;
		hairCustomizationVariables = idd.hairCustomizationVariables;
		unknownInt1 = idd.unknownInt1;
		timestamp = idd.timestamp;
		requiredPayment = idd.requiredPayment;
		offeredPayment = idd.offeredPayment;
		designerAccepted = idd.designerAccepted;
		targetAccepted = idd.targetAccepted;
		statMigrationRequested = idd.statMigrationRequested;
		unk1 = idd.unk1;
		unk2 = idd.unk2;
		unk3 = idd.unk3;
		unk4 = idd.unk4;
		bodyAttributes = idd.bodyAttributes;
		colorAttributes = idd.colorAttributes;
		holoEmote = idd.holoEmote;

		return *this;
	}

	void parse(Message* message) {
		message->parseAscii(hairTemplate);

		String customizationString;
		message->parseAscii(customizationString);
		hairCustomizationVariables.parseFromString(customizationString);

		unknownInt1 = message->parseInt();
		timestamp = message->parseInt();

		requiredPayment = message->parseInt();
		offeredPayment = message->parseInt();

		designerAccepted = message->parseByte();
		targetAccepted = message->parseInt();

		statMigrationRequested = message->parseByte();

		unk1 = message->parseInt();
		unk2 = message->parseInt();
		unk3 = message->parseInt();
		unk4 = message->parseInt();

		int size = message->parseInt();

		for (int i = 0; i < size; ++i) {
			String attr;
			message->parseAscii(attr);

			float val = message->parseFloat();

			bodyAttributes.put(attr, val);
		}

		size = message->parseInt();

		for (int i = 0; i < size; ++i) {
			String attr;
			message->parseAscii(attr);

			uint32 val = message->parseInt();
			System::out << attr + String::valueOf(val) << endl;
			colorAttributes.put(attr, val);
		}

		message->parseAscii(holoEmote);
	}

	void insertToMessage(Message* message) {
		message->insertAscii(hairTemplate);

		String data;
		hairCustomizationVariables.getData(data);
		message->insertAscii(data);

		message->insertInt(unknownInt1);
		message->insertInt(timestamp);
		message->insertInt(requiredPayment);
		message->insertInt(offeredPayment);
		message->insertByte(designerAccepted);
		message->insertInt(targetAccepted);
		message->insertByte(statMigrationRequested);
		message->insertInt(unk1);
		message->insertInt(unk2);
		message->insertInt(unk3);
		message->insertInt(unk4);

		int size = bodyAttributes.size();

		message->insertInt(size);

		for (int i = 0; i < size; ++i) {
			VectorMapEntry<String, float>* entry = &bodyAttributes.elementAt(i);

			message->insertAscii(entry->getKey());
			message->insertFloat(entry->getValue());
		}

		size = colorAttributes.size();

		message->insertInt(size);

		for (int i = 0; i < size; ++i) {
			VectorMapEntry<String, uint32>* entry = &colorAttributes.elementAt(i);

			message->insertAscii(entry->getKey());
			message->insertInt(entry->getValue());
		}

		message->insertAscii(holoEmote);
	}

	inline bool isAcceptedByDesigner() {
		return (bool) designerAccepted;
	}

	inline bool isAcceptedByTarget() {
		return (bool) targetAccepted;
	}

	inline uint32 getRequiredPayment() {
		return requiredPayment;
	}

	inline uint32 getOfferedPayment() {
		return offeredPayment;
	}

	inline String getHairTemplate() {
		return hairTemplate;
	}

	inline void setHairAttribute(String& attr, uint32 val) {
		hairCustomizationVariables.setVariable(attr,val);
	}

	inline String getHairCustomizationString() {
		String hairCustomization;
		hairCustomizationVariables.getData(hairCustomization);
		return hairCustomization;
	}

	inline VectorMap<String, float>* getBodyAttributesMap() {
		return &bodyAttributes;
	}

	inline VectorMap<String, uint32>* getColorAttributesMap() {
		return &colorAttributes;
	}
};

#endif /* IMAGEDESIGNDATA_H_ */
