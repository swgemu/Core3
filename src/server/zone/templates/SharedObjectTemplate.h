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

public:
	SharedObjectTemplate() {

	}

	virtual ~SharedObjectTemplate() {

	}

	void readObject(LuaObject* templateData);

    String getAppearanceFilename() const {
		return appearanceFilename;
	}

	float getClearFloraRadius() const {
		return clearFloraRadius;
	}

	String getClientDataFile() const {
		return clientDataFile;
	}

	int getCollisionActionBlockFlags() const {
		return collisionActionBlockFlags;
	}

	int getCollisionActionFlags() const {
		return collisionActionFlags;
	}

	int getCollisionActionPassFlags() const {
		return collisionActionPassFlags;
	}

	int getCollisionMaterialBlockFlags() const {
		return collisionMaterialBlockFlags;
	}

	int getCollisionMaterialFlags() const {
		return collisionMaterialFlags;
	}

	int getCollisionMaterialPassFlags() const {
		return collisionMaterialPassFlags;
	}

	int getContainerType() const {
		return containerType;
	}

	int getContainerVolumeLimit() const {
		return containerVolumeLimit;
	}

	String getDetailedDescription() const {
		return detailedDescription;
	}

	int getGameObjectType() const {
		return gameObjectType;
	}

	float getLocationReservationRadius() const {
		return locationReservationRadius;
	}

	String getLookAtText() const {
		return lookAtText;
	}

	float getNoBuildRadius() const {
		return noBuildRadius;
	}

	String getObjectName() const {
		return objectName;
	}

	bool getOnlyVisibleInTools() const {
		return onlyVisibleInTools;
	}

	String getPortalLayoutFilename() const {
		return portalLayoutFilename;
	}

	Vector<String> getArrangementDescriptors() const {
		return arrangementDescriptors;
	}

	float getScale() const {
		return scale;
	}

	float getScaleThresholdBeforeExtentTest() const {
		return scaleThresholdBeforeExtentTest;
	}

	bool getSendToClient() const {
		return sendToClient;
	}

	Vector<String> getSlotDescriptors() const {
		return slotDescriptors;
	}

	bool getSnapToTerrain() const {
		return snapToTerrain;
	}

	int getSurfaceType() const {
		return surfaceType;
	}

	String getTintPallete() const {
		return tintPallete;
	}

	int getTotalCellNumber() const {
		return totalCellNumber;
	}

	uint32 getClientObjectCRC() {
		return clientObjectCRC;
	}

	String getFullTemplateString() {
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

};


#endif /* SHAREDOBJECTTEMPLATE_H_ */
