/*
 * MeshData.h
 *
 *  Created on: 04/22/2016
 *      Author: gslomin
 */

#ifndef MESHDATA_H_
#define MESHDATA_H_

#include "engine/engine.h"

class MeshTriangle {
protected:
	int verts[3];

public:
	MeshTriangle() {
		verts[0] = 0;
		verts[1] = 1;
		verts[2] = 2;
	}

	MeshTriangle(int a, int b, int c) {
		verts[0] = a;
		verts[1] = b;
		verts[2] = c;
	}

	MeshTriangle(const MeshTriangle& mesh) {
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

	void set(uint8 index, uint32 value) {
		verts[index] = value;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}

	friend class MeshData;

	friend class MeshAppearanceTemplate;
};

class MeshData : public Object {
protected:
	Vector <Vector3> vertices;
	Vector <MeshTriangle> triangles;

public:
	MeshData() {

	}

	MeshData(const MeshData& data) : Object() {
		vertices = data.vertices;
		triangles = data.triangles;
	}

	void readObject(IffStream* iffStream);

	Vector <Vector3>* getVerts() {
		return &vertices;
	}

	const Vector <Vector3>* getVerts() const {
		return &vertices;
	}

	Vector <MeshTriangle>* getTriangles() {
		return &triangles;
	}

	static Reference<MeshData*> makeCopyNegateZ(const MeshData* mesh, const Matrix4& parentTransform) {
		Reference < MeshData * > newData = new MeshData(*mesh);
		for (auto& vert : newData->vertices) {
			vert.setZ(-vert.getZ());
			vert = vert * parentTransform;
		}
		return newData;
	}

	void transformMeshData(const Matrix4& transform) {
		for (int i = 0; i < vertices.size(); i++) {
			Vector3& vert = vertices.get(i);
			vert = Vector3(vert.getX(), vert.getY(), vert.getZ()) * transform;
		}
	}

	Vector <MeshTriangle>* getMeshWithinBounds(AABB& bounds) const;

	AABB buildAABB() const;

	const Vector <MeshTriangle>* getTriangles() const {
		return &triangles;
	}

	friend class MeshAppearanceTemplate;

};

#endif /* MESHDATA_H_ */
