/*
 * MeshAppearanceTemplate.cpp
 *
 *  Created on: 07/12/2010
 *      Author: victor
 */

#include "MeshAppearanceTemplate.h"

#include <osg/Node>
#include <osgViewer/Viewer>

#include <osg/Geometry>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/Texture2D>

#include <osg/LineWidth>
#include <osg/Billboard>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>

#include <osgDB/Registry>
#include <osgDB/ReadFile>

void MeshAppearanceTemplate::parse(IffStream* iffStream) {
	//file = iffStream->getFileName();

	meshes = new Vector<MeshData>();

	iffStream->openForm('MESH');

	uint32 version = iffStream->getNextFormType();
	iffStream->openForm(version);

	AppearanceTemplate::readObject(iffStream);

	parseSPS(iffStream);

	iffStream->closeForm(version);
	iffStream->closeForm('MESH');

	if (meshes->size() != 0) {
		createAABB();
	}

	/*delete meshes;
	meshes = NULL;*/
}

osg::ref_ptr<osg::Node> MeshAppearanceTemplate::draw() {
	/*osg::Group* group = new osg::Group();

	for (int i = 0; i < meshes->size(); i++) {
		group->addChild(meshes->get(i).draw());
	}

	return group;*/

	osg::ref_ptr<osg::Group> rootGroup = new osg::Group();

	for (int i = 0; i < meshes->size(); ++i) {
		MeshData* meshData = &meshes->get(i);

		osg::ref_ptr< osg::Geode > geode( new osg::Geode() );
		//geode->setName(name.toStdString() + ":FloorTriangleNode" + QString::number(i).toStdString());
		osg::ref_ptr<osg::Geometry> geometry( new osg::Geometry() );


		osg::Vec3Array* verts = new osg::Vec3Array();
		osg::Vec4Array* colors = new osg::Vec4Array();

		for( unsigned int i = 0; i < meshData->vertices.size(); ++i ) {
			MeshVertex& vertex = meshData->vertices.get(i);

			float x = vertex.getX();
			float y = vertex.getY();
			float z = vertex.getZ();

			verts->push_back( osg::Vec3( x, y, z ) );

			colors->push_back(osg::Vec4(0.f, 0.5f, 0, 0.5f) );
		}

		geometry->setVertexArray( verts );

		osg::DrawElementsUShort* drawElements =
				new osg::DrawElementsUShort( osg::PrimitiveSet::TRIANGLES );

		// Populate primitive set with indices.
		for( unsigned int j = 0; j < meshData->triangles.size(); ++j ) {
			drawElements->push_back( meshData->triangles.get(j).vertex1 );
			drawElements->push_back( meshData->triangles.get(j).vertex2 );
			drawElements->push_back( meshData->triangles.get(j).vertex3 );
		}

		// Add primitive set to this geometry node.
		geometry->addPrimitiveSet(drawElements);
		geometry->setColorArray(colors);
		geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

		osg::VertexBufferObject *vbo = new osg::VertexBufferObject;
		verts->setVertexBufferObject(vbo);

		osg::ElementBufferObject* ebo = new osg::ElementBufferObject;
		drawElements->setElementBufferObject(ebo);

		geometry->setUseVertexBufferObjects((NULL != vbo));

		geode->addDrawable(geometry.get());

		rootGroup->addChild(geode);
	}

	return rootGroup;
}

void MeshAppearanceTemplate::createAABB() {
	Vector<Triangle*> triangles;

	for (int k = 0; k < meshes->size(); ++k) {
		MeshData* meshData = &meshes->get(k);

		for (int i = 0; i < meshData->triangles.size(); ++i) {
			MeshTriangle* tri = &meshData->triangles.get(i);

			int pointA = tri->vertex1;
			int pointB = tri->vertex2;
			int pointC = tri->vertex3;

			MeshVertex* vert1 = &meshData->vertices.get(pointA);
			MeshVertex* vert2 = &meshData->vertices.get(pointB);
			MeshVertex* vert3 = &meshData->vertices.get(pointC);

			Vector3 trian[3];
			trian[0] = Vector3(vert1->getX(), vert1->getY(), vert1->getZ());
			trian[1] = Vector3(vert2->getX(), vert2->getY(), vert2->getZ());
			trian[2] = Vector3(vert3->getX(), vert3->getY(), vert3->getZ());

			triangles.add(new Triangle(trian));
		}
	}

	//meshes.removeAll();

	//Logger::console.info("creating mesh aabb for triangles " + String::valueOf(triangles.size()), true);

	AABBTreeHeuristic heurData;
	heurData.maxdepth = 4; // maximum depth
	heurData.mintricnt = 5; // minimum triangle count
	heurData.tartricnt = 10; // target triangle count
	heurData.minerror = 0.5f; // minimum error required
	heurData.storePrimitives = true;

	aabbTree = new AABBTree(triangles, 0, heurData);

	AABB& box = aabbTree->getBoundingBox();

	Vector3 center = box.center();
	Vector3 extents = box.extents();
	float radius = extents.length();

	boundingSphere = new Sphere(center, radius);
}

/*AABNode* MeshAppearanceTemplate::createNewAABB(float rotationRadians = 0) {

}*/

bool MeshAppearanceTemplate::testCollide(float x, float z, float y, float radius) {
	Vector3 point(x, z, y);

	Sphere sphere(point, radius);

	//Logger::console.info("checking collide in mesh", true);

	return aabbTree->testCollide(sphere);
}

void MeshAppearanceTemplate::parseSPS(IffStream* iffStream) {
	iffStream->openForm('SPS ');
	iffStream->openForm('0001');

	int count = 0;

	iffStream->openChunk('CNT ');

	count = iffStream->getInt();

	iffStream->closeChunk();

	for (int i = 1; i <= count; ++i) {
		parseVertexData(iffStream, i);
	}

	iffStream->closeForm('0001');
	iffStream->closeForm('SPS ');
}

void MeshAppearanceTemplate::parseVertexData(IffStream* iffStream, int idx) {
	int formVersion = 0;'0000';// + idx;

	String idxText = String::valueOf(idx);
	int lengthOfText = idxText.length();

	for (int i = 0; i < 4 - lengthOfText; ++i)
		idxText = "0" + idxText;

	for (int i = 0; i < 4; ++i) {
		char a = idxText.charAt(i);

		formVersion = formVersion << 8;
		formVersion += (int)a;
	}

	iffStream->openForm(formVersion);

	iffStream->openChunk('NAME');

	String shaderName;
	iffStream->getString(shaderName);

	iffStream->closeChunk();

	iffStream->openChunk('INFO');
	iffStream->closeChunk();

	uint32 nextVersion = iffStream->getNextFormType();
	iffStream->openForm(nextVersion);

	iffStream->openChunk('INFO');
	iffStream->closeChunk();

	MeshData meshData;
	meshData.readObject(iffStream);
	meshes->add(meshData);

	iffStream->closeForm(nextVersion);

	iffStream->closeForm(formVersion);
}

void MeshData::readObject(IffStream* iffStream) {
	iffStream->openForm('VTXA');
	iffStream->openForm('0003');
	iffStream->openChunk('INFO');

	iffStream->getInt(); //unk

	int numVertices = iffStream->getInt();

	iffStream->closeChunk();

	Chunk* vertexDataChunk = iffStream->openChunk('DATA');

	int vertexDataChunkSize = vertexDataChunk->getChunkSize();

	int intBytesPerVertex = vertexDataChunkSize / numVertices;

	for (int i = 0; i < numVertices; ++i) {
		MeshVertex vert;
		vert.readObject(iffStream);

		vertices.add(vert);

		vertexDataChunk->shiftOffset(intBytesPerVertex - 12);
	}

	iffStream->closeChunk('DATA');
	iffStream->closeForm('0003');
	iffStream->closeForm('VTXA');

	Chunk* indexData = iffStream->openChunk('INDX');

	int indexCount = iffStream->getInt();

	for (int i = 1; i <= indexCount; i += 3) {
		//triangleIndexes.add(indexData->getUnsignedShort());
		int a = indexData->readShort();
		int b = indexData->readShort();
		int c = indexData->readShort();

		MeshTriangle triangle;
		triangle.vertex1 = a;
		triangle.vertex2 = b;
		triangle.vertex3 = c;

		triangles.add(triangle);
	}

	iffStream->closeChunk();
}
