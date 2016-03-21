#include "ClientMeshAppearance.h"

osg::ref_ptr<osg::Geometry> createMeshGeometry(const MeshData* meshData) {
		
	osg::ref_ptr<osg::Geometry> geometry(new osg::Geometry);

	osg::Vec3Array* verts( new osg::Vec3Array() );

	const Vector<Vector3>& vertices = *meshData->getVerts();

	for( unsigned int i = 0; i < vertices.size(); ++i )
	{
		const Vector3& vertex = vertices.get(i);
		float x = vertex.getX();
		float y = vertex.getY();
		float z = vertex.getZ();
		verts->push_back( osg::Vec3( x, y, z ) );
	}

	geometry->setVertexArray( verts );

	osg::DrawElementsUShort* drawElements =
	new osg::DrawElementsUShort( osg::PrimitiveSet::TRIANGLES );

	const Vector<MeshTriangle>& triangles = *meshData->getTriangles();

	// Populate primitive set with indices.
	for( unsigned int j = 0; j < triangles.size(); ++j )
	{
		const int* verts = triangles.get(j).getVerts();
		
		drawElements->push_back( verts[0] );
		drawElements->push_back( verts[1] );
		drawElements->push_back( verts[2] );
	}

	// Add primitive set to this geometry node.
	geometry->addPrimitiveSet( drawElements );

	osg::VertexBufferObject *vbo = new osg::VertexBufferObject;
	verts->setVertexBufferObject( vbo );

	osg::ElementBufferObject* ebo = new osg::ElementBufferObject;
	drawElements->setElementBufferObject( ebo );

	geometry->setUseVertexBufferObjects( ( NULL != vbo ) );
	osg::Vec4Array* colors( new osg::Vec4Array() );

	colors->push_back(osg::Vec4(0, 100, 0, 50));
	geometry->setColorArray( colors);
	geometry->setColorBinding( osg::Geometry::BIND_OVERALL );

	return geometry;
}


