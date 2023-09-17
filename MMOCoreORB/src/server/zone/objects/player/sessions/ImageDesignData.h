/*
 * ImageDesignData.h
 *
 *  Created on: Feb 16, 2011
 *      Author: crush
 */

#ifndef IMAGEDESIGNDATA_H_
#define IMAGEDESIGNDATA_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"

class ImageDesignData : public Object, public Logger {
protected:
	String hairTemplate;
	CustomizationVariables hairCustomizationVariables;

	uint32 sessionID;
	uint32 timestamp;

	uint32 requiredPayment;
	uint32 offeredPayment;

	uint8 designerAccepted;
	uint32 targetAccepted;

	uint8 statMigrationRequested;

	uint32 bodySkillMod;
	uint32 faceSkillMod;
	uint32 markingsSkillMod;
	uint32 hairSkillMod;

	VectorMap<String, float> bodyAttributes;
	VectorMap<String, uint32> colorAttributes;

	String holoEmote;

public:
	ImageDesignData() : sessionID(0), timestamp(0), requiredPayment(0),
		offeredPayment(0), designerAccepted(0), targetAccepted(0), statMigrationRequested(0),
		bodySkillMod(0), faceSkillMod(0), markingsSkillMod(0), hairSkillMod(0) {
	}

	ImageDesignData(const ImageDesignData& idd) : Object() {
		hairTemplate = idd.hairTemplate;
		hairCustomizationVariables = idd.hairCustomizationVariables;
		sessionID = idd.sessionID;
		timestamp = idd.timestamp;
		requiredPayment = idd.requiredPayment;
		offeredPayment = idd.offeredPayment;
		designerAccepted = idd.designerAccepted;
		targetAccepted = idd.targetAccepted;
		statMigrationRequested = idd.statMigrationRequested;
		bodySkillMod = idd.bodySkillMod;
		faceSkillMod = idd.faceSkillMod;
		markingsSkillMod = idd.markingsSkillMod;
		hairSkillMod = idd.hairSkillMod;
		bodyAttributes = idd.bodyAttributes;
		colorAttributes = idd.colorAttributes;
		holoEmote = idd.holoEmote;
	}

	ImageDesignData& operator= (const ImageDesignData& idd) {
		if (this == &idd)
			return *this;

		hairTemplate = idd.hairTemplate;
		hairCustomizationVariables = idd.hairCustomizationVariables;
		sessionID = idd.sessionID;
		timestamp = idd.timestamp;
		requiredPayment = idd.requiredPayment;
		offeredPayment = idd.offeredPayment;
		designerAccepted = idd.designerAccepted;
		targetAccepted = idd.targetAccepted;
		statMigrationRequested = idd.statMigrationRequested;
		bodySkillMod = idd.bodySkillMod;
		faceSkillMod = idd.faceSkillMod;
		markingsSkillMod = idd.markingsSkillMod;
		hairSkillMod = idd.hairSkillMod;
		bodyAttributes = idd.bodyAttributes;
		colorAttributes = idd.colorAttributes;
		holoEmote = idd.holoEmote;

		return *this;
	}

	void parse(Message* message) {
		//info(true) << "ImageDesignData -- Parse: ";

		message->parseAscii(hairTemplate);
		//info(true) << "hairTemplate: " << hairTemplate;

		String customizationString;
		message->parseAscii(customizationString);

		//info(true) << "parsing customization string size:" << customizationString.length();

		hairCustomizationVariables.parseFromClientString(customizationString);

		sessionID = message->parseInt();
		//info(true) << "sessionID: " << sessionID;

		timestamp = message->parseInt();
		//info(true) << "timestamp: " << timestamp;

		requiredPayment = message->parseInt();
		//info(true) << "requiredPayment: " << requiredPayment;

		offeredPayment = message->parseInt();
		//info(true) << "offeredPayment: " << offeredPayment;

		designerAccepted = message->parseByte();
		//info(true) << "DESIGNER --- designerAccepted: " << designerAccepted;

		targetAccepted = message->parseInt();
		//info(true) << "TARTGET -- targetAccepted: " << targetAccepted;

		statMigrationRequested = message->parseByte();
		//info(true) << "statMigrationRequested: " << (statMigrationRequested ? " true" : " false" );

		bodySkillMod = message->parseInt();
		//info(true) << "bodySkillMod: " << bodySkillMod;
		faceSkillMod = message->parseInt();
		//info(true) << "faceSkillMod: " << faceSkillMod;
		markingsSkillMod = message->parseInt();
		//info(true) << "markingsSkillMod: " << markingsSkillMod;
		hairSkillMod = message->parseInt();
		//info(true) << "hairSkillMod: " << hairSkillMod;

		int size = message->parseInt();

		// info(true) << "body parts: " << size;

		for (int i = 0; i < size; ++i) {
			String attr;
			message->parseAscii(attr);

			float val = message->parseFloat();

			bodyAttributes.put(attr, val);

			// info(true) << attr << " " << val;
		}

		size = message->parseInt();

		// info(true) << "color parts: " << size;

		for (int i = 0; i < size; ++i) {
			String attr;
			message->parseAscii(attr);

			uint32 val = message->parseInt();
			// info(true) << attr << " " << val;

			colorAttributes.put(attr, val);
		}

		message->parseAscii(holoEmote);
	}

	void insertToMessage(Message* message) {
		message->insertAscii(hairTemplate);

		String data;
		hairCustomizationVariables.getData(data);
		message->insertAscii(data);

		message->insertInt(sessionID);
		message->insertInt(timestamp);
		message->insertInt(requiredPayment);
		message->insertInt(offeredPayment);
		message->insertByte(designerAccepted);
		message->insertInt(targetAccepted);
		message->insertByte(statMigrationRequested);
		message->insertInt(bodySkillMod);
		message->insertInt(faceSkillMod);
		message->insertInt(markingsSkillMod);
		message->insertInt(hairSkillMod);

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

	inline bool isStatMigrationRequested() {
		return (bool) statMigrationRequested;
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

	inline void setHairAttribute(const String& attr, int val) {
		hairCustomizationVariables.setVariable(attr, val);
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

	inline String getHoloEmote(){
		return holoEmote;
	}
};

#endif /* IMAGEDESIGNDATA_H_ */
