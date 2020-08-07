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
	BaseBoundingVolume* volume = nullptr;
	BaseBoundingVolume* collisionVolume = nullptr;
	VectorMap<String, Matrix4> hardpoints;
public:

	virtual uint32 getType() const {
		return 'APPR';
	}

	const String& getFloorMesh() const {
		return floorName;
	}

	const VectorMap<String, Matrix4>& getHardpoints() const {
		return hardpoints;
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

	String toString(Matrix4& mat) {
		char buffer[512];
		sprintf(buffer, "\n[% 05.3f, % 05.3f, % 05.3f, % 05.3f]\n[% 05.3f, % 05.3f, % 05.3f, % 05.3f]\n[% 05.3f, % 05.3f, % 05.3f, % 05.3f]\n[% 05.3f, % 05.3f, % 05.3f, % 05.3f]",
		mat[0][0], mat[0][1], mat[0][2], mat[0][3], mat[1][0], mat[1][1], mat[1][2], mat[1][3], mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
		return String(buffer);
	}

	virtual void readObject(IffStream* iffStream) {

		fileName = iffStream->getFileName();

		iffStream->openForm('APPR');
		uint32 formType = iffStream->getNextFormType();
		if (formType == '0003') {
			iffStream->openForm('0003');
			volume = BoundingVolumeFactory::getVolume(iffStream);
			collisionVolume = BoundingVolumeFactory::getVolume(iffStream);


			Chunk *chunk = iffStream->openForm('HPTS');
            try {
                int numHardpoints = chunk->getChunksSize();
                for (int i = 0; i < numHardpoints; i++) {
                    iffStream->openChunk('HPNT');
                    Matrix4 transform;
                    transform[0][0] = iffStream->getFloat();
                    transform[1][0] = iffStream->getFloat();
                    transform[2][0] = iffStream->getFloat();
                    transform[3][0] = iffStream->getFloat();

                    transform[0][1] = iffStream->getFloat();
                    transform[1][1] = iffStream->getFloat();
                    transform[2][1] = iffStream->getFloat();
                    transform[3][1] = iffStream->getFloat();

                    transform[0][2] = iffStream->getFloat();
                    transform[1][2] = iffStream->getFloat();
                    transform[2][2] = iffStream->getFloat();
                    transform[3][2] = iffStream->getFloat();

                    String name;
                    iffStream->getString(name);
                    hardpoints.put(name, transform);
					Logger::console.info(fileName + " Loading hardpoint: " + name + " Transform: " + toString(transform), true);
                    iffStream->closeChunk('HPNT');
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

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
