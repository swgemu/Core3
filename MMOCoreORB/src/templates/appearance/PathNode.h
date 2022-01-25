/*
 * PathNode.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef PATHNODE_H_
#define PATHNODE_H_

#include "engine/util/u3d/Vector3.h"
#include "templates/appearance/PathEdge.h"

class PathGraph;

class PathNode {
public:
	enum PathNodeType
	{
		CellPortal           = 0,
		CellWaypoint         = 1,
		CellPOI              = 2,

		BuildingEntrance     = 3,
		BuildingCell         = 4,
		BuildingPortal       = 5,

		CityBuildingEntrance = 6,
		CityWaypoint         = 7,
		CityPOI              = 8,
		CityBuilding         = 9,
		CityEntrance         = 10,

		BuildingCellPart     = 11,

		Invalid              = 12,
	};
protected:

	Vector<PathNode*> children;

	uint32 id;
	int var2, globalGraphNodeID;
	PathNodeType type;
	float x, z, y, radius;

	PathGraph* pathGraph;

public:
	PathNode(PathGraph* graph) {
		pathGraph = graph;
		id = 0;
		var2 = globalGraphNodeID = 0;
		type = Invalid;
		x = z = y = radius = 0;
	}

	inline void addChild(PathNode* node) {
		children.add(node);
	}

	void readObject(IffStream* iffStream) {
		id = iffStream->getInt(); // index
		var2 = iffStream->getInt(); // ID
		globalGraphNodeID = iffStream->getInt(); // Key
		type = static_cast<PathNodeType>(iffStream->getInt()); // type

		x = iffStream->getFloat(); // position
		z = iffStream->getFloat();
		y = iffStream->getFloat();
		radius = iffStream->getFloat(); //radius
		if(radius == 0.0f)
			radius = 0.5f;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}

	inline float getX() const {
		return x;
	}

	inline float getY() const {
		return y;
	}

	inline float getZ() const {
		return z;
	}

	/*inline uint32 getID() {
		return id;
	}*/

	uint32 getID() const;

	inline Vector3 getPosition() const {
		return Vector3(x, y, z);
	}

	inline float getRadius() const {
		return radius;
	}

	inline PathNodeType getType() const {
		return type;
	}

	const Vector<PathNode*>* getNeighbors() const {
		return &children;
	}

	inline int getGlobalGraphNodeID() const {
		return globalGraphNodeID;
	}

	inline const PathGraph* getPathGraph() const {
		return pathGraph;
	}

	inline static String typeToString(PathNodeType nodeType) {
		switch (nodeType) {
		case CellPortal:           return "CellPortal";
		case CellWaypoint:         return "CellWaypoint";
		case CellPOI:              return "CellPOI";
		case BuildingEntrance:     return "BuildingEntrance";
		case BuildingCell:         return "BuildingCell";
		case BuildingPortal:       return "BuildingPortal";
		case CityBuildingEntrance: return "CityBuildingEntrance";
		case CityWaypoint:         return "CityWaypoint";
		case CityPOI:              return "CityPOI";
		case CityBuilding:         return "CityBuilding";
		case CityEntrance:         return "CityEntrance";
		case BuildingCellPart:     return "BuildingCellPart";
		case Invalid:              return "Invalid";
		default:
			StringBuffer buf;
			buf << "UnknownType(" << nodeType << ")";
			return buf.toString();
		}
	}

	inline String toString() const {
		StringBuffer buf;

		buf << "PathNode(id: " << id
			<< ", type: " << typeToString(type)
			<< ", x: " << x
			<< ", y: " << y
			<< ", z: " << z
			<< ", radius: " << radius
			<< ", globalGraphNodeID: " << globalGraphNodeID
			<< ")";

		return buf.toString();
	}

	String toStringData() const {
		return toString();
	}
};

#endif /* PATHNODE_H_ */
