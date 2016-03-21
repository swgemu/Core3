#ifndef CLIENTMESHAPPEARANCE_H_
#define CLIENTMESHAPPEARANCE_H_
#include "engine/engine.h"
#include "ClientAppearance.h"
#include "templates/appearance/MeshAppearanceTemplate.h"
#include "templates/appearance/AppearanceTemplate.h"

class ClientMeshAppearance : public ClientAppearance {
	Vector<Reference<MeshData*> > meshes;
	std::vector<osg::ref_ptr<osg::Geometry> > geometry;
	
	osg::ref_ptr<osg::Geode> geode;
	
public:
	ClientMeshAppearance(AppearanceTemplate *tmpl) : ClientAppearance(tmpl) {
		MeshAppearanceTemplate *mesh = cast<MeshAppearanceTemplate*>(tmpl);
		assert(mesh != NULL);
		
		geode = new osg::Geode();
		meshes = mesh->getMeshes();
		
		for (int i=0; i<meshes.size(); i++) {
			osg::ref_ptr<osg::Geometry> geo = createMeshGeometry(meshes.get(i)).get();
			
			geode->addDrawable(geo.get());
			geometry.push_back(geo.get());
		}
		
	}
	
	virtual osg::ref_ptr<osg::Node> draw() {
		osg::ref_ptr<osg::Group> group(new osg::Group);
		group->addChild(geode);
		return group;
	}
	
	
	static osg::ref_ptr<osg::Geometry> createMeshGeometry(MeshData* meshData) {
		
		osg::ref_ptr<osg::Geometry> geometry(new osg::Geometry);
		
		osg::Vec3Array* verts( new osg::Vec3Array() );
		
		Vector<Vector3>& vertices = *meshData->getVerts();
		
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
		
		Vector<MeshTriangle>& triangles = *meshData->getTriangles();
		
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
};

#endif
