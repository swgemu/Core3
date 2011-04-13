/*
 * SharedCreatureObjectTemplate.cpp
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#include "SharedCreatureObjectTemplate.h"


void SharedCreatureObjectTemplate::readObject(LuaObject* templateData) {
	SharedTangibleObjectTemplate::readObject(templateData);

	gender = templateData->getIntField("gender");
	species = templateData->getIntField("species");
	niche = templateData->getIntField("niche");
	race = templateData->getIntField("race");
	slopeModPercent = templateData->getFloatField("slopeModPercent");
	slopeModAngle = templateData->getFloatField("slopeModAngle");
	swimHeight = templateData->getFloatField("swimHeight");
	waterModPercent = templateData->getFloatField("waterModPercent");
	stepHeight = templateData->getFloatField("stepHeight");
	collisionHeight = templateData->getFloatField("collisionHeight");
	collisionRadius = templateData->getFloatField("collisionRadius");
	warpTolerance = templateData->getFloatField("warpTolerance");
	collisionOffsetX = templateData->getFloatField("collisionOffsetX");
	collisionOffsetZ = templateData->getFloatField("collisionOffsetZ");
	collisionLength = templateData->getFloatField("collisionLength");
	cameraHeight = templateData->getFloatField("cameraHeight");

	animationMapFilename = templateData->getStringField("animationMapFilename");
	movementDatatable = templateData->getStringField("movementDatatable");

	LuaObject post = templateData->getObjectField("postureAlignToTerrain");

	for (int i = 1; i <= post.getTableSize(); ++i) {
		postureAlignToTerrain.add(post.getIntAt(i));
	}

	post.pop();

	LuaObject turns = templateData->getObjectField("turnRate");

	for (int i = 1; i <= turns.getTableSize(); ++i) {
		turnRate.add(turns.getFloatAt(i));
	}

	turns.pop();

	LuaObject hams = templateData->getObjectField("baseHAM");

	for (int i = 1; i <= hams.getTableSize(); ++i) {
		baseHAM.add(hams.getIntAt(i));
	}

	hams.pop();

	LuaObject accel = templateData->getObjectField("acceleration");

	for (int i = 1; i <= accel.getTableSize(); ++i) {
		acceleration.add(accel.getFloatAt(i));
	}

	accel.pop();

	LuaObject speedTempl = templateData->getObjectField("speed");

	for (int i = 1; i <= speedTempl.getTableSize(); ++i) {
		speed.add(speedTempl.getFloatAt(i));
	}

	speedTempl.pop();

	LuaObject lootGroups = templateData->getObjectField("lootGroup");

	for (int i = 1; i <= lootGroups.getTableSize(); ++i) {
		lootGroup.add(lootGroups.getIntAt(i));
	}

	lootGroups.pop();

}

