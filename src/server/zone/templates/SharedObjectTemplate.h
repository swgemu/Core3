/*
 * SharedObjectTemplate.h
 *
 *  Created on: 30/04/2010
 *      Author: victor
 */

#ifndef SHAREDOBJECTTEMPLATE_H_
#define SHAREDOBJECTTEMPLATE_H_

#include "engine/engine.h"

#include "LuaTemplate.h"

class SharedObjectTemplate : public LuaTemplate {
protected:
	String objectName;
	String detailedDescription;
	String lookAtText;

	bool snapToTerrain;
	int containerType;
	int containerVolumeLimit;

	String tintPallete;
	Vector<String> slotDescriptors;
	Vector<String> arrangementDescriptors;
	String appearanceFilename;
	String portalLayoutFilename;
	int totalCellNumber;
	String clientDataFile;

	int collisionMaterialFlags;
	int collisionMaterialPassFlags;
	float scale;
	int collisionMaterialBlockFlags;
	int collisionActionFlags;
	int collisionActionPassFlags;
	int collisionActionBlockFlags;
	int gameObjectType;
	bool sendToClient;
	float scaleThresholdBeforeExtentTest;
	float clearFloraRadius;
	int surfaceType;
	float noBuildRadius;
	bool onlyVisibleInTools;
	float locationReservationRadius;
	uint32 clientObjectCRC;

	String fullTemplateString;

	int templateType;

public:
	const static int SHOT = 0x1;
	const static int STOT = 0x2;
	const static int SBMK = 0x4;
	const static int SBOT = 0x8;
	const static int STAT = 0x10;
	const static int SIOT = 0x20;
	const static int CCLT = 0x40;
	const static int SCOU = 0x80;
	const static int SDSC = 0x100;
	const static int SFOT = 0x200;
	const static int SGRP = 0x400;
	const static int SITN = 0x800;
	const static int SGLD = 0x1000;
	const static int SJED = 0x2000;
	const static int SMSC = 0x4000;
	const static int SMSO = 0x8000;
	const static int SMSD = 0x10000;
	const static int SMLE = 0x20000;
	const static int SPLY = 0x40000;
	const static int RCCT = 0x80000;
	const static int SSHP = 0x100000;
	const static int SUNI = 0x200000;
	const static int SWAY = 0x400000;
	const static int STOK = 0x800000;
	const static int SWOT = 0x1000000;
	const static int SCNC = 0x2000000;
	const static int SCOT = 0x4000000;
	const static int CHARACTERBUILDERTERMINAL = 0x4000001;
	const static int SURVEYTOOL = 0x4000002;
	const static int RESOURCESPAWN = 0x4000003;
	const static int RESOURCECONTAINER = 0x4000004;
	const static int ARMOROBJECT = 0x4000005;
	const static int DEED = 0x4000006;

public:
	SharedObjectTemplate() {

	}

	virtual ~SharedObjectTemplate() {

	}

	void readObject(LuaObject* templateData);

	inline bool isArmorObjectTemplate() const {
		return templateType == ARMOROBJECT;
	}

    inline String getAppearanceFilename() const {
		return appearanceFilename;
	}

    inline float getClearFloraRadius() const {
		return clearFloraRadius;
	}

    inline String getClientDataFile() const {
		return clientDataFile;
	}

    inline int getCollisionActionBlockFlags() const {
		return collisionActionBlockFlags;
	}

    inline int getCollisionActionFlags() const {
		return collisionActionFlags;
	}

    inline int getCollisionActionPassFlags() const {
		return collisionActionPassFlags;
	}

    inline int getCollisionMaterialBlockFlags() const {
		return collisionMaterialBlockFlags;
	}

    inline int getCollisionMaterialFlags() const {
		return collisionMaterialFlags;
	}

    inline int getCollisionMaterialPassFlags() const {
		return collisionMaterialPassFlags;
	}

    inline int getContainerType() const {
		return containerType;
	}

    inline int getContainerVolumeLimit() const {
		return containerVolumeLimit;
	}

    inline String getDetailedDescription() const {
		return detailedDescription;
	}

    inline int getGameObjectType() const {
		return gameObjectType;
	}

    inline float getLocationReservationRadius() const {
		return locationReservationRadius;
	}

    inline String getLookAtText() const {
		return lookAtText;
	}

    inline float getNoBuildRadius() const {
		return noBuildRadius;
	}

    inline String getObjectName() const {
		return objectName;
	}

    inline bool getOnlyVisibleInTools() const {
		return onlyVisibleInTools;
	}

    inline String getPortalLayoutFilename() const {
		return portalLayoutFilename;
	}

    inline Vector<String> getArrangementDescriptors() const {
		return arrangementDescriptors;
	}

    inline float getScale() const {
		return scale;
	}

    inline float getScaleThresholdBeforeExtentTest() const {
		return scaleThresholdBeforeExtentTest;
	}

    inline bool getSendToClient() const {
		return sendToClient;
	}

    inline Vector<String> getSlotDescriptors() const {
		return slotDescriptors;
	}

    inline bool getSnapToTerrain() const {
		return snapToTerrain;
	}

    inline int getSurfaceType() const {
		return surfaceType;
	}

    inline String getTintPallete() const {
		return tintPallete;
	}

    inline int getTotalCellNumber() const {
		return totalCellNumber;
	}

    inline uint32 getClientObjectCRC() {
		return clientObjectCRC;
	}

    inline String getFullTemplateString() {
		return fullTemplateString;
	}

public:
	void setAppearanceFilename(String appearanceFilename) {
		this->appearanceFilename = appearanceFilename;
	}

	void setClearFloraRadius(float clearFloraRadius) {
		this->clearFloraRadius = clearFloraRadius;
	}

	void setClientDataFile(String clientDataFile) {
		this->clientDataFile = clientDataFile;
	}

	void setCollisionActionBlockFlags(int collisionActionBlockFlags) {
		this->collisionActionBlockFlags = collisionActionBlockFlags;
	}

	void setCollisionActionFlags(int collisionActionFlags) {
		this->collisionActionFlags = collisionActionFlags;
	}

	void setCollisionActionPassFlags(int collisionActionPassFlags) {
		this->collisionActionPassFlags = collisionActionPassFlags;
	}

	void setCollisionMaterialBlockFlags(int collisionMaterialBlockFlags) {
		this->collisionMaterialBlockFlags = collisionMaterialBlockFlags;
	}

	void setCollisionMaterialFlags(int collisionMaterialFlags) {
		this->collisionMaterialFlags = collisionMaterialFlags;
	}

	void setCollisionMaterialPassFlags(int collisionMaterialPassFlags) {
		this->collisionMaterialPassFlags = collisionMaterialPassFlags;
	}

	void setContainerType(int containerType) {
		this->containerType = containerType;
	}

	void setContainerVolumeLimit(int containerVolumeLimit) {
		this->containerVolumeLimit = containerVolumeLimit;
	}

	void setDetailedDescription(String detailedDescription) {
		this->detailedDescription = detailedDescription;
	}

	void setGameObjectType(int gameObjectType) {
		this->gameObjectType = gameObjectType;
	}

	void setLocationReservationRadius(float locationReservationRadius) {
		this->locationReservationRadius = locationReservationRadius;
	}

	void setLookAtText(String lookAtText) {
		this->lookAtText = lookAtText;
	}

	void setNoBuildRadius(float noBuildRadius) {
		this->noBuildRadius = noBuildRadius;
	}

	void setObjectName(String objectName) {
		this->objectName = objectName;
	}

	void setOnlyVisibleInTools(bool onlyVisibleInTools) {
		this->onlyVisibleInTools = onlyVisibleInTools;
	}

	void setPortalLayoutFilename(String portalLayoutFilename) {
		this->portalLayoutFilename = portalLayoutFilename;
	}

	void setRrangementDescriptors(Vector<String> rrangementDescriptors) {
		this->arrangementDescriptors = rrangementDescriptors;
	}

	void setScale(float scale) {
		this->scale = scale;
	}

	void setScaleThresholdBeforeExtentTest(float scaleThresholdBeforeExtentTest) {
		this->scaleThresholdBeforeExtentTest = scaleThresholdBeforeExtentTest;
	}

	void setSendToClient(bool sendToClient) {
		this->sendToClient = sendToClient;
	}

	void setSlotDescriptors(Vector<String> slotDescriptors) {
		this->slotDescriptors = slotDescriptors;
	}

	void setSnapToTerrain(bool snapToTerrain) {
		this->snapToTerrain = snapToTerrain;
	}

	void setSurfaceType(int surfaceType) {
		this->surfaceType = surfaceType;
	}

	void setTintPallete(String tintPallete) {
		this->tintPallete = tintPallete;
	}

	void setTotalCellNumber(int totalCellNumber) {
		this->totalCellNumber = totalCellNumber;
	}

	void setFullTemplateString(const String& str) {
		fullTemplateString = str;
	}

public:
	inline virtual bool isSharedBuildingObjectTemplate() {
		return false;
	}

	inline virtual bool isSharedInstallationObjectTemplate() {
		return false;
	}
};


#endif /* SHAREDOBJECTTEMPLATE_H_ */
