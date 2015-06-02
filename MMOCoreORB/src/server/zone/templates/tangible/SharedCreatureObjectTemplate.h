/*
 * SharedCreatureObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDCREATUREOBJECTTEMPLATE_H_
#define SHAREDCREATUREOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"
#include "../params/VectorParam.h"

class SharedCreatureObjectTemplate: public SharedTangibleObjectTemplate {
protected:
	IntegerParam gender;
	IntegerParam niche;
	IntegerParam species;
	IntegerParam race;

	VectorParam<FloatParam> acceleration;
	VectorParam<FloatParam> speed;
	VectorParam<FloatParam> turnRate;

	StringParam animationMapFilename;

	FloatParam slopeModAngle;
	FloatParam slopeModPercent;
	FloatParam waterModPercent;
	FloatParam stepHeight;
	FloatParam collisionHeight;
	FloatParam collisionRadius;

	StringParam movementDatatable;

	VectorParam<BoolParam> postureAlignToTerrain;

	FloatParam swimHeight;
	FloatParam warpTolerance;
	FloatParam collisionOffsetX;
	FloatParam collisionOffsetZ;
	FloatParam collisionLength;
	FloatParam cameraHeight;

	Vector<int> baseHAM;

public:
	SharedCreatureObjectTemplate() {

	}

	~SharedCreatureObjectTemplate() {

	}

	void readObject(LuaObject* templateData);
	void readObject(IffStream* iffStream);

	void parseVariableData(const String& varName, LuaObject* templateData);

	void parseVariableData(const String& varName, Chunk* data);
	void parseFileData(IffStream* iffStream);

	inline Vector<FloatParam> getAcceleration() const {
		return acceleration.get();
	}

	inline String getAnimationMapFilename() const {
		return animationMapFilename;
	}

	inline Vector<int> getBaseHAM() const {
		return baseHAM;
	}

	inline float getCameraHeight() const {
		return cameraHeight;
	}

	inline float getCollisionHeight() const {
		return collisionHeight;
	}

	inline float getCollisionLength() const {
		return collisionLength;
	}

	inline float getCollisionOffsetX() const {
		return collisionOffsetX;
	}

	inline float getCollisionOffsetZ() const {
		return collisionOffsetZ;
	}

	inline float getCollisionRadius() const {
		return collisionRadius;
	}

	inline int getGender() const {
		return gender;
	}

	inline String getMovementDatatable() const {
		return movementDatatable;
	}

	inline int getNiche() const {
		return niche;
	}

	inline Vector<BoolParam> getPostureAlignToTerrain() const {
		return postureAlignToTerrain.get();
	}

	inline int getRace() const {
		return race;
	}

	inline float getSlopeModAngle() const {
		return slopeModAngle;
	}

	inline float getSlopeModPercent() const {
		return slopeModPercent;
	}

	inline int getSpecies() const {
		return species;
	}

	inline const Vector<FloatParam>& getSpeed() const {
		return speed.get();
	}

	inline float getStepHeight() const {
		return stepHeight;
	}

	inline float getSwimHeight() const {
		return swimHeight;
	}

	inline Vector<FloatParam> getTurnRate() const {
		return turnRate.get();
	}

	inline float getWarpTolerance() const {
		return warpTolerance;
	}

	inline float getWaterModPercent() const {
		return waterModPercent;
	}

	/*void setAcceleration(Vector<float> acceleration) {
		this->acceleration = acceleration;
	}*/

	void setAnimationMapFilename(String animationMapFilename) {
		this->animationMapFilename = animationMapFilename;
	}

	void setBaseHAM(Vector<int> baseHAM) {
		this->baseHAM = baseHAM;
	}

	void setCameraHeight(float cameraHeight) {
		this->cameraHeight = cameraHeight;
	}

	void setCollisionHeight(float collisionHeight) {
		this->collisionHeight = collisionHeight;
	}

	void setCollisionLength(float collisionLength) {
		this->collisionLength = collisionLength;
	}

	void setCollisionOffsetX(float collisionOffsetX) {
		this->collisionOffsetX = collisionOffsetX;
	}

	void setCollisionOffsetZ(float collisionOffsetZ) {
		this->collisionOffsetZ = collisionOffsetZ;
	}

	void setCollisionRadius(float collisionRadius) {
		this->collisionRadius = collisionRadius;
	}

	void setGender(int gender) {
		this->gender = gender;
	}

	void setMovementDatatable(String movementDatatable) {
		this->movementDatatable = movementDatatable;
	}

	void setNiche(int niche) {
		this->niche = niche;
	}

	/*void setPostureAlignToTerrain(Vector<bool> postureAlignToTerrain) {
		this->postureAlignToTerrain = postureAlignToTerrain;
	}*/

	void setRace(int race) {
		this->race = race;
	}

	void setSlopeModAngle(float slopeModAngle) {
		this->slopeModAngle = slopeModAngle;
	}

	void setSlopeModPercent(float slopeModPercent) {
		this->slopeModPercent = slopeModPercent;
	}

	void setSpecies(int species) {
		this->species = species;
	}

	/*void setSpeed(Vector<float> speed) {
		this->speed = speed;
	}*/

	void setStepHeight(float stepHeight) {
		this->stepHeight = stepHeight;
	}

	void setSwimHeight(float swimHeight) {
		this->swimHeight = swimHeight;
	}

	/*void setTurnRate(Vector<float> turnRate) {
		this->turnRate = turnRate;
	}*/

	void setWarpTolerance(float warpTolerance) {
		this->warpTolerance = warpTolerance;
	}

	void setWaterModPercent(float waterModPercent) {
		this->waterModPercent = waterModPercent;
	}

};

#endif /* SHAREDCREATUREOBJECTTEMPLATE_H_ */
