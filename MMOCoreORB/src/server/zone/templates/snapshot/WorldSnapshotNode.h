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
	Vector<WorldSnapshotNode> childNodes;

	uint32 objectID;
	uint32 parentID;
	uint32 nameID;
	uint32 cellid; //cellid in the cells

	Quaternion direction;
	Vector3 position;

	float gameObjectType;
	uint32 unknown2;

public:
	WorldSnapshotNode() : Object(), objectID(0), parentID(0), nameID(0), cellid(0), gameObjectType(0), unknown2(0) {

	}

	WorldSnapshotNode(const WorldSnapshotNode& wsn) : Object() {
		childNodes = wsn.childNodes;
		objectID = wsn.objectID;
		parentID = wsn.parentID;
		nameID = wsn.nameID;
		cellid = wsn.cellid;
		direction = wsn.direction;
		position = wsn.position;
		gameObjectType = wsn.gameObjectType;
		unknown2 = wsn.unknown2;
	}

	WorldSnapshotNode& operator= (const WorldSnapshotNode& wsn) {
		if (this == &wsn)
			return *this;

		childNodes = wsn.childNodes;
		objectID = wsn.objectID;
		parentID = wsn.parentID;
		nameID = wsn.nameID;
		cellid = wsn.cellid;
		direction = wsn.direction;
		position = wsn.position;
		gameObjectType = wsn.gameObjectType;
		unknown2 = wsn.unknown2;

		return *this;
	}

	void parse(IffStream* iffStream) {
		iffStream->openForm('NODE');

		uint32 version = iffStream->getNextFormType();
		Chunk* versionForm = iffStream->openForm(version);

		switch (version) {
		case '0000':
		{
			Chunk* data = iffStream->openChunk('DATA');
			objectID = data->readInt();
			parentID = data->readInt();
			nameID = data->readInt();
			cellid = data->readInt();

			float qw = data->readFloat();
			float qx = data->readFloat();
			float qy = data->readFloat();
			float qz = data->readFloat();

			float x = data->readFloat();
			float z = data->readFloat();
			float y = data->readFloat();

			direction.set(qw, qx, qy, qz);
			position.set(x, z, y);

			gameObjectType = data->readFloat();
			unknown2 = data->readInt();

			iffStream->closeChunk('DATA');
		}
			break;
		default:
			break;
		}

		for (int i = 0; i < versionForm->getChunksSize() - 1; ++i) {
			WorldSnapshotNode childNode;
			childNode.parse(iffStream);

			childNodes.add(childNode);
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

	uint32 getCellID() const {
		return cellid;
	}

	uint32 getUnknown2() const {
		return unknown2;
	}

	inline int getNodeCount() {
		return childNodes.size();
	}

	inline WorldSnapshotNode* getNode(int idx) {
		return &childNodes.get(idx);
	}
};


#endif /* WORLDSNAPSHOTNODE_H_ */
