/*
 * MeshAppearanceTemplate.h
 *
 *  Created on: 07/12/2010
 *      Author: victor
 */

#ifndef MESHAPPEARANCETEMPLATE_H_
#define MESHAPPEARANCETEMPLATE_H_

#include "templates/appearance/AppearanceTemplate.h"
#include "templates/appearance/MeshData.h"

class MeshAppearanceTemplate : public AppearanceTemplate {
	Vector<Reference<MeshData*> > meshes;
	//Vector<Triangle> triangles;

	AABBTree* aabbTree;
	Sphere* boundingSphere;
	//String file;

public:
	virtual uint32 getType() const {
		return 'MESH';
	}
	MeshAppearanceTemplate() {
		aabbTree = NULL;
		boundingSphere = NULL;
	}

	~MeshAppearanceTemplate() {
		delete aabbTree;
		aabbTree = NULL;

		delete boundingSphere;
		boundingSphere = NULL;
	}

	void createAABB();

	void readObject(IffStream* templateData) {
		parse(templateData);
	}

	void parse(IffStream* iffStream);
	void parseSPS(IffStream* iffStream);
	void parseVertexData(IffStream* iffStream, int idx);

	bool testCollide(float x, float z, float y, float radius) const;

	inline void getTriangles(Vector<Triangle*>& triangles) {
		if (aabbTree != NULL)
			aabbTree->getTriangles(triangles);
	}

	/*inline String& getFileName() {
		return file;
	}*/

	inline AABBTree* getAABBTree() {
		return aabbTree;
	}

	inline Sphere* getBoundingSphere() {
		return boundingSphere;
	}

	const Vector<Reference<MeshData*> >& getMeshes() const {
		return meshes;
	}

	virtual bool testCollide(const Sphere& testsphere) const {
		return aabbTree->testCollide(testsphere);
	}

	/**
	 * Checks for intersection against ray, stops on any intersection
	 * @return intersectionDistance, triangle which it intersects
	 */
	virtual bool intersects(const Ray& ray, float distance, float& intersectionDistance, Triangle*& triangle, bool checkPrimitives = false) const {
		return aabbTree->intersects(ray, distance, intersectionDistance, triangle, checkPrimitives);
	}

	/**
	 * Checks for all intersections
	 */
	virtual int intersects(const Ray& ray, float maxDistance, SortedVector<IntersectionResult>& result) const {
		return aabbTree->intersects(ray, maxDistance, result);
	}

	virtual Vector<Reference<MeshData* > > getTransformedMeshData(const Matrix4& parentTransform) const {
		Vector<Reference<MeshData* > > newMeshes;
		for(int i=0; i<meshes.size(); i++) {
			newMeshes.emplace(MeshData::makeCopyNegateZ(meshes.get(i), parentTransform));
		}
		return newMeshes;
	}
};

#endif /* MESHAPPEARANCETEMPLATE_H_ */
