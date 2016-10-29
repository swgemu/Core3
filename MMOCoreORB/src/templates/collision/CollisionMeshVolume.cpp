#include "CollisionMeshVolume.h"

void CollisionMeshVolume::read(IffStream *iff) {
	try {
		iff->openForm('0000');
		iff->openForm('IDTL');
		iff->openForm('0000');

		Chunk *vertChunk = iff->openChunk('VERT');
		int numVerts = vertChunk->getChunkSize()/12;

		for (int i=0; i<numVerts; i++) {
			float x = iff->getFloat();
			float y = iff->getFloat();
			float z = iff->getFloat();
			verts.add(Vector3(x, y, z));
		}

		iff->closeChunk('VERT');

		Chunk *idxChunk = iff->openChunk('INDX');
		int numIdx = idxChunk->getChunkSize()/4;

		for(int i=0; i<numIdx; i++) {
			indicies.add(iff->getInt());
		}

		iff->closeChunk('INDX');
		iff->closeForm('0000');
		iff->closeForm('IDTL');
		iff->closeForm('0000');
	} catch (Exception& e) {
		e.getMessage();
	}

}
#ifdef OSG_RENDERER
osg::ref_ptr<osg::Node> CollisionMeshVolume::draw() const {
	osg::ref_ptr< osg::Geode > geode( new osg::Geode() );
	//geode->setName(name.toStdString() + ":FloorTriangleNode" + QString::number(i).toStdString());
	osg::ref_ptr<osg::Geometry> geometry( new osg::Geometry() );


	osg::Vec3Array* vertices( new osg::Vec3Array() );

	for( unsigned int i = 0; i < verts.size(); ++i )
	{
		const Vector3& vertex = verts.get(i);
		float x = vertex.getX();
		float y = vertex.getY();
		float z = vertex.getZ();
		vertices->push_back( osg::Vec3( x, y, z ) );
	}

	geometry->setVertexArray( vertices );

	osg::DrawElementsUShort* drawElements =
	new osg::DrawElementsUShort( osg::PrimitiveSet::TRIANGLES );


	// Populate primitive set with indices.
	for( unsigned int j = 0; j < indicies.size(); j++)
	{
		drawElements->push_back( indicies.get(j) );
	}

	// Add primitive set to this geometry node.
	geometry->addPrimitiveSet( drawElements );

	osg::VertexBufferObject *vbo = new osg::VertexBufferObject;
	vertices->setVertexBufferObject( vbo );

	osg::ElementBufferObject* ebo = new osg::ElementBufferObject;
	drawElements->setElementBufferObject( ebo );

	geometry->setUseVertexBufferObjects( ( NULL != vbo ) );
	osg::Vec4Array* colors( new osg::Vec4Array() );

	colors->push_back(osg::Vec4(0, 100, 100, 50));
	geometry->setColorArray( colors);
	geometry->setColorBinding( osg::Geometry::BIND_OVERALL );

	geode->addDrawable( geometry.get() );

	return geode;
}

#endif
