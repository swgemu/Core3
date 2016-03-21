/*
 * MeshAppearanceTemplate.h
 *
 *  Created on: 07/12/2010
 *      Author: victor
 */

#ifndef MESHAPPEARANCETEMPLATE_H_
#define MESHAPPEARANCETEMPLATE_H_

#include "engine/engine.h"
#include "templates/appearance/AppearanceTemplate.h"

class MeshTriangle : public Object {
protected:
	int verts[3];

public:
	MeshTriangle() {
		verts[0] = 0;
		verts[1] = 1;
		verts[2] = 2;
	}

	MeshTriangle(const MeshTriangle& mesh) : Object() {
		verts[0] = mesh.verts[0];
		verts[1] = mesh.verts[1];
		verts[2] = mesh.verts[2];
	}
	
	const int* getVerts() const {
		return verts;
	}
	
	const int* getVerts() {
		return verts;
	}

	friend class MeshData;
	friend class MeshAppearanceTemplate;
};

class MeshData : public Object {
protected:
	Vector<Vector3> vertices;
	Vector<MeshTriangle> triangles;

public:
	MeshData() {

	}

	MeshData(const MeshData& data) : Object(){
		vertices = data.vertices;
		triangles = data.triangles;
	}

	void readObject(IffStream* iffStream);
	
	Vector<Vector3>* getVerts() {
		return &vertices;
	}
	
	const Vector<Vector3>* getVerts() const {
		return &vertices;
	}
	
	Vector<MeshTriangle>* getTriangles() {
		return &triangles;
	}

	const Vector<MeshTriangle>* getTriangles() const {
		return &triangles;
	}

	friend class MeshAppearanceTemplate;

};

class MeshAppearanceTemplate : public AppearanceTemplate {
	Vector<Reference<MeshData*> > meshes;
	//Vector<Triangle> triangles;

	AABBTree* aabbTree;
	Sphere* boundingSphere;
	//String file;

public:
	virtual uint32 getType() {
		return 'MESH';
	}
	MeshAppearanceTemplate() {
		aabbTree = NULL;
		meshes = NULL;
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

	bool testCollide(float x, float z, float y, float radius);

	AppearanceTemplate* getFirstMesh() {
		return this;
	}

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
	
	Vector<Reference<MeshData*> > getMeshes() {
		return meshes;
	}

};

#endif /* MESHAPPEARANCETEMPLATE_H_ */
