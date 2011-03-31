/*
 * WorldSnapshotNode.h
 *
 *  Created on: Mar 31, 2011
 *      Author: crush
 */

#ifndef WORLDSNAPSHOTNODE_H_
#define WORLDSNAPSHOTNODE_H_

#include "engine/engine.h"
#include "engine/util/iffstream/IffStream.h"
#include "engine/util/iffstream/chunks/Chunk.h"

class WorldSnapshotNode : public Object {
	uint32 objectID;
	uint32 parentID;
	uint32 nameID;
	uint32 unknown1;

	Quaternion direction;
	Vector3 position;

	float gameObjectType;
	uint32 unknown2;

public:
	WorldSnapshotNode() : Object() {

	}

	WorldSnapshotNode(const WorldSnapshotNode& wsn) : Object() {
		objectID = wsn.objectID;
		parentID = wsn.parentID;
		nameID = wsn.nameID;
		unknown1 = wsn.unknown1;
		direction = wsn.direction;
		position = wsn.position;
		gameObjectType = wsn.gameObjectType;
		unknown2 = wsn.unknown2;
	}

	WorldSnapshotNode& operator= (const WorldSnapshotNode& wsn) {
		if (this == &wsn)
			return *this;

		objectID = wsn.objectID;
		parentID = wsn.parentID;
		nameID = wsn.nameID;
		unknown1 = wsn.unknown1;
		direction = wsn.direction;
		position = wsn.position;
		gameObjectType = wsn.gameObjectType;
		unknown2 = wsn.unknown2;

		return *this;
	}

	void parse(IffStream* iffStream) {
		iffStream->openForm('NODE');

		uint32 version = iffStream->getNextFormType();
		iffStream->openForm(version);

		switch (version) {
		case '0000':
		{
			Chunk* data = iffStream->openChunk('DATA');
			objectID = data->readInt();
			parentID = data->readInt();
			nameID = data->readInt();
			unknown1 = data->readInt();

			direction.set(data->readFloat(), data->readFloat(), data->readFloat(), data->readFloat());
			position.set(data->readFloat(), data->readFloat(), data->readFloat());

			gameObjectType = data->readFloat();
			unknown2 = data->readInt();

			iffStream->closeChunk('DATA');
		}
			break;
		default:
			break;
		}

		iffStream->closeForm(version);
		iffStream->closeForm('NODE');
	}

	Quaternion getDirection() const {
		return direction;
	}

	float getGameObjectType() const {
		return gameObjectType;
	}

	uint32 getNameID() const {
		return nameID;
	}

	uint32 getObjectID() const {
		return objectID;
	}

	uint32 getParentID() const {
		return parentID;
	}

	Vector3 getPosition() const {
		return position;
	}

	uint32 getUnknown1() const {
		return unknown1;
	}

	uint32 getUnknown2() const {
		return unknown2;
	}
};


#endif /* WORLDSNAPSHOTNODE_H_ */
