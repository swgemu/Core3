/*
 * CamoKitImplementation2.h
 *
 *  Created on: Oct 20, 2008
 *      Author: swgdev
 */

#ifndef CAMOKITIMPLEMENTATION_H_
#define CAMOKITIMPLEMENTATION_H_

#include "CamoKit.h"
#include "../../player/Player.h"

class CamoKitImplementation: public CamoKitServant {
protected:
	uint32 planet;
	uint32 usesRemaining;
	uint32 concealMin;
public:

	CamoKitImplementation(unsigned long long oid, unsigned int tempCRC, const UnicodeString& n, const String& tempn);

	CamoKitImplementation(Player* player, unsigned int tempCRC, const UnicodeString& n, const String& tempn);

	void useCharge(Player* player);

	int getPlanet();

	int getUsesRemaining();

	int getConcealMin();

	void setPlanet(const int tp);

	void setUsesRemaining(const int us);

	void setConcealMin(const int min);

	void remove(Player* player);

	void sendDeltas(Player* player);

	void generateAttributes(SceneObject* obj);
	void addHeaderAttributes(AttributeListMessage* alm);
	void addFooterAttributes(AttributeListMessage* alm);
	void addAttributes(AttributeListMessage* alm);

	void parseItemAttributes();
};

#endif /* CAMOKITIMPLEMENTATION2_H_ */
