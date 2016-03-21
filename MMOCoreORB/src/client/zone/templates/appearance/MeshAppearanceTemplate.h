/*
 * MeshAppearanceTemplate.h
 *
 *  Created on: 07/12/2010
 *      Author: victor
 */

#ifndef MESHAPPEARANCETEMPLATE_H_
#define MESHAPPEARANCETEMPLATE_H_

#include "engine/engine.h"
#include "AppearanceTemplate.h"
#include <osg/Node>
#include <osg/Geometry>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>
#include <osg/BlendFunc>

//enum Flags {
//	VB_None = 0x0,
//	VB_translate = 0x1,
//	VB_scale = 0x2,
//	VB_normal = 0x4,
//	VB_color0 = 0x8,
//	VB_color1 = 0x10,
//	VB_pointScale = 0x20,
//	
//	VB_TexCoordCountMask0 = 0x0,
//	VB_TexCoordCountMask1 = 0x100,
//	VB_TexCoordCountMask2 = 0x200,
//	VB_TexCoordCountMask3 = 0x300,
//	VB_TexCoordCountMask4 = 0x400,
//	VB_TexCoordCountMask5 = 0x500,
//	VB_TexCoordCountMask6 = 0x600,
//	VB_TexCoordCountMask7 = 0x700,
//	VB_TexCoordCountMask8 = 0x800,
//	
//	VB_TexCoordSet0_1d = 0x0,
//	VB_TexCoordSet0_2d = 0x10000,
//	VB_TexCoordSet0_3d = 0x20000,
//	VB_TexCoordSet0_4d = 0x30000,
//	VB_TexCoordSet1_1d = 0x00000,
//	VB_TexCoordSet1_2d = 0x40000,
//	VB_TexCoordSet1_3d = 0x80000,
//	VB_TexCoordSet1_4d = 0xC0000,
//	
//	VB_TexCoordSet2_1d = 0x0,
//	VB_TexCoordSet2_2d = 0x1000000,
//	VB_TexCoordSet2_3d = 0x2000000,
//	VB_TexCoordSet2_4d = 0x3000000,
//	VB_TexCoordSet3_1d = 0x0000000,
//	VB_TexCoordSet3_2d = 0x4000000,
//	VB_TexCoordSet3_3d = 0x8000000,
//	VB_TexCoordSet3_4d = 0xC000000,
//	
//	VB_TexCoordSet4_1d = 0x0,
//	VB_TexCoordSet4_2d = 0x100000000,
//	VB_TexCoordSet4_3d = 0x200000000,
//	VB_TexCoordSet4_4d = 0x300000000,
//	VB_TexCoordSet5_1d = 0x000000000,
//	VB_TexCoordSet5_2d = 0x400000000,
//	VB_TexCoordSet5_3d = 0x800000000,
//	VB_TexCoordSet5_4d = 0xC00000000,
//	
//	VB_TexCoordSet6_1d = 0x0,
//	VB_TexCoordSet6_2d = 0x10000000000,
//	VB_TexCoordSet6_3d = 0x20000000000,
//	VB_TexCoordSet6_4d = 0x30000000000,
//	VB_TexCoordSet7_1d = 0x00000000000,
//	VB_TexCoordSet7_2d = 0x40000000000,
//	VB_TexCoordSet7_3d = 0x80000000000,
//	VB_TexCoordSet7_4d = 0xC0000000000
//};

namespace osg {
	class Node;
}
class MeshVertex : public Object {
public:
	Vector3 position;
	float w;
	Vector3 normal;
	float u[8];
	float v[8];

public:
	MeshVertex() : position(0, 0, 0), normal(0, 0, 0) {

	}

	MeshVertex(const MeshVertex& vert) : Object() {
		position = vert.position;
		w = vert.w;
		normal = vert.normal;
		for (int i=0; i<8; i++) {
			u[i] = vert.u[i];
			v[i] = vert.v[i];
		}
	}

	void readObject(IffStream* iffStream) {
		float x = iffStream->getFloat();
		float y = iffStream->getFloat();
		float z = iffStream->getFloat();
		position = Vector3(x, y, z);

	}

	inline float getX() const {
		return position.getX();
	}

	inline float getY() const {
		return position.getY();
	}

	inline float getZ() const {
		return position.getZ();
	}

	friend class MeshAppearanceTemplate;
	friend class MeshData;
};

class MeshTriangle : public Object {
protected:
	int vertex1, vertex2, vertex3;

public:
	MeshTriangle() : vertex1(0), vertex2(0), vertex3(0) {

	}

	MeshTriangle(const MeshTriangle& mesh) : Object() {
		vertex1 = mesh.vertex1;
		vertex2 = mesh.vertex2;
		vertex3 = mesh.vertex3;
	}

	friend class MeshData;
	friend class MeshAppearanceTemplate;
};

class MeshData : public Object {
protected:
	Vector<MeshVertex> vertices;
	Vector<MeshTriangle> triangles;

public:
	MeshData() {

	}

	MeshData(const MeshData& data) : Object(){
		vertices = data.vertices;
		triangles = data.triangles;
	}

	void readObject(IffStream* iffStream);
	
	osg::ref_ptr<osg::Node> draw();

	friend class MeshAppearanceTemplate;

};

class MeshAppearanceTemplate : public AppearanceTemplate, Logger {
	Vector<MeshData>* meshes;
	//Vector<Triangle> triangles;

	AABBTree* aabbTree;
	Sphere* boundingSphere;
	//String file;

public:
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
	
	virtual Vector<MeshData*> getTransformedMeshData(Matrix4 transform);
	
	osg::ref_ptr<osg::Node> draw();

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

};

#endif /* MESHAPPEARANCETEMPLATE_H_ */
