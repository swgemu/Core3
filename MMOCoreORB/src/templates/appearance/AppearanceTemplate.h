/*
 * AppearanceTemplate.h
 *
 *  Created on: 11/12/2010
 *      Author: victor
 */

#ifndef APPEARANCETEMPLATE_H_
#define APPEARANCETEMPLATE_H_

#include "templates/collision/BoundingVolumeFactory.h"
#include "templates/appearance/MeshData.h"

class AppearanceTemplate : public Object {
	String floorName;
	String fileName;
	BaseBoundingVolume* volume;
	BaseBoundingVolume* collisionVolume;
public:

	virtual uint32 getType() const {
		return 'APPR';
	}

	const String& getFloorMesh() const {
		return floorName;
	}

	const BaseBoundingVolume* getBoundingVolume() const {
		return volume;
	}

	const BaseBoundingVolume* getCollisionVolume() const {
		return collisionVolume;
	}

	const String& getFileName() const {
		return fileName;
	}

	virtual bool testCollide(const Sphere& testsphere) const = 0;

	/**
	 * Checks for intersection against ray, stops on any intersection
	 * @return intersectionDistance, triangle which it intersects
	 */
	virtual bool intersects(const Ray& ray, float distance, float& intersectionDistance, Triangle*& triangle,
							bool checkPrimitives = false) const = 0;

	/**
	 * Checks for all intersections
	 */
	virtual int intersects(const Ray& ray, float maxDistance, SortedVector <IntersectionResult>& result) const = 0;


	virtual void readObject(IffStream* iffStream) {

		fileName = iffStream->getFileName();

		iffStream->openForm('APPR');
		uint32 formType = iffStream->getNextFormType();
		if (formType == '0003') {
			iffStream->openForm('0003');
			volume = BoundingVolumeFactory::getVolume(iffStream);
			collisionVolume = BoundingVolumeFactory::getVolume(iffStream);


			iffStream->openForm('HPTS');

			// Skip loading hardpoints
			iffStream->closeForm('HPTS');

			iffStream->openForm('FLOR');
			iffStream->openChunk('DATA');
			bool hasFloor = iffStream->getByte();
			if (hasFloor)
				iffStream->getString(floorName);
			iffStream->closeChunk('DATA');
			iffStream->closeForm('FLOR');

			iffStream->closeForm('0003');
		} else {
			String msg = "AppearanceTemplate::readObject unknown version (" + String::hexvalueOf(
					(int64) formType) + ")";
			throw Exception(msg);
		}
		iffStream->closeForm('APPR');

	}

	virtual ~AppearanceTemplate() {
		delete volume;
		delete collisionVolume;
	}

	virtual Vector <Reference<MeshData*>> getTransformedMeshData(const Matrix4& parentTransform) const = 0;
};

#endif /* APPEARANCETEMPLATE_H_ */
