/*
 * DetailAppearanceTemplate.h
 *
 *  Created on: 10/12/2010
 *      Author: victor
 */

#ifndef DETAILAPPEARANCETEMPLATE_H_
#define DETAILAPPEARANCETEMPLATE_H_

#include <stddef.h>
#include <algorithm>

#include "system/lang/ref/Reference.h"
#include "system/platform.h"
#include "system/util/Vector.h"
#include "templates/appearance/AppearanceTemplate.h"

class MeshData;
namespace engine {
namespace util {
class IffStream;
namespace u3d {
class IntersectionResult;
class Matrix4;
class Ray;
class Sphere;
class Triangle;
}  // namespace u3d
}  // namespace util
}  // namespace engine
namespace sys {
namespace util {
template <class E> class SortedVector;
}  // namespace util
}  // namespace sys

class DetailAppearanceTemplate : public AppearanceTemplate {
	const AppearanceTemplate* firstMesh;
public:
	virtual uint32 getType() const {
		return 'DTAL';
	}

	DetailAppearanceTemplate() {
		firstMesh = NULL;
	}

	~DetailAppearanceTemplate() {
	}

	void readObject(IffStream* templateData) {
		parse(templateData);
	}

	void parse(IffStream* iffStream);

	virtual bool testCollide(const Sphere& testsphere) const {
		return firstMesh->testCollide(testsphere);
	}

	/**
	 * Checks for intersection against ray, stops on any intersection
	 * @return intersectionDistance, triangle which it intersects
	 */
	virtual bool intersects(const Ray& ray, float distance, float& intersectionDistance, Triangle*& triangle, bool checkPrimitives = false) const {
		return firstMesh->intersects(ray, distance, intersectionDistance, triangle, checkPrimitives);
	}

	/**
	 * Checks for all intersections
	 */
	virtual int intersects(const Ray& ray, float maxDistance, SortedVector<IntersectionResult>& result) const {
		return firstMesh->intersects(ray, maxDistance, result);
	}

	virtual Vector<Reference<MeshData* > > getTransformedMeshData(const Matrix4& parentTransform) const {
		Vector<Reference<MeshData* > > meshes;
		if(firstMesh != NULL)
			meshes.addAll(firstMesh->getTransformedMeshData(parentTransform));
		return meshes;
	}

};

#endif /* DETAILAPPEARANCETEMPLATE_H_ */
