#include "BoundingVolumes.h"

void BaseBoundingVolume::read(IffStream *iff) {
	iff->openForm('EXSP');
	iff->openForm('0001');
	iff->openChunk('SPHR');
	float x = iff->getFloat();
	float y = iff->getFloat();
	float z = iff->getFloat();
	
	float radius = iff->getFloat();
	iff->closeChunk('SPHR');
	iff->closeForm('0001');
	iff->closeForm('EXSP');
}


void BoxVolume::read(IffStream *iff) {
	iff->openForm('0001');
	BaseBoundingVolume::read(iff);
	iff->openChunk('BOX ');
	float minx = iff->getFloat();
	float miny = iff->getFloat();
	float minz = iff->getFloat();
	
	float maxx = iff->getFloat();
	float maxy = iff->getFloat();
	float maxz = iff->getFloat();
	bbox = AABB(Vector3(minx, miny, minz), Vector3(maxx, maxy, maxz));
	iff->closeChunk('BBOX');
	iff->closeForm('0001');
}

osg::ref_ptr<osg::Node> BoxVolume::draw() {
	return bbox.draw();
}

void CompositeVolume::read(IffStream *iff) {
	iff->openForm('0000');
	uint32 chunks = iff->getSubChunksNumber();
	for(int i=0; i<chunks; i++) {
			BaseBoundingVolume *volume = BoundingVolumeList::getVolume(iff);
			volumes.add(volume);
	}
	iff->closeForm('0000');
}

osg::ref_ptr<osg::Node> CompositeVolume::draw() {
	osg::ref_ptr<osg::Group> group(new osg::Group);
	
	for(int i=0; i<volumes.size(); i++) {
		group->addChild(volumes.get(i)->draw());
	}
	return group;
}

void ComponentVolume::read(IffStream* iff) {
	iff->openForm('0000');
	iff->openForm('CPST');
	CompositeVolume::read(iff);
	iff->closeForm('CPST');
	iff->closeForm('0000');
}



void DetailVolume::read(IffStream* iff) {
	iff->openForm('0000');
	iff->openForm('CPST');
	CompositeVolume::read(iff);
	iff->closeForm('CPST');
	iff->closeForm('0000');
}
osg::ref_ptr<osg::Node> DetailVolume::draw() {
	osg::ref_ptr<osg::Group> group(new osg::Group);
	
	for(int i=1; i<volumes.size(); i++) {
		group->addChild(volumes.get(i)->draw());
	}
	return group;
}
void MeshVolume::read(IffStream *iff) {
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
	} catch (Exception e) {
		e.getMessage();
	}

}

osg::ref_ptr<osg::Node> MeshVolume::draw() {
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

void CylinderVolume::read(IffStream *iff) {
	iff->openForm('0000');
	iff->openChunk('CYLN');
	float x = iff->getFloat();
	float y = iff->getFloat();
	float z = iff->getFloat();
	float radius = iff->getFloat();
	height = iff->getFloat();
	base = Sphere(Vector3(x, y, z), radius);
	iff->closeChunk('CYLN');
	iff->closeForm('0000');
}

osg::ref_ptr<osg::Node> CylinderVolume::draw() {
	osg::Group* group = new osg::Group();
	osg::Geode* geode = new osg::Geode();
	geode->setName("BBOX");
	
	Vector3 mid = base.getCenter();
	osg::MatrixTransform * transform  = new osg::MatrixTransform( );
	
	osg::Matrix mat = osg::Matrix::rotate(osg::DegreesToRadians(90.f), 1, 0, 0);
	transform->setMatrix(mat);
	
	osg::ref_ptr<osg::ShapeDrawable> drawable = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(mid.getX(), mid.getY(), mid.getZ()), base.getRadius(), height), NULL);
	drawable->setColor(osg::Vec4(255, 0, 0, 255));
	geode->addDrawable(drawable);
	geode->getOrCreateStateSet()->setAttribute( new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE) );
	
	transform->addChild(geode);
	group->addChild(transform);
	return group;
}

osg::ref_ptr<osg::Node> SphereVolume::draw() {
	return getBoundingSphere().draw();
}

BaseBoundingVolume* BoundingVolumeList::getVolume(IffStream *iff) {
	static Logger logger;
	
	BaseBoundingVolume *volume = NULL;
	uint32 type = iff->getNextFormType();
	switch(type) {
		case 'NULL':
			iff->openForm('NULL');
			iff->closeForm('NULL');
			return NULL;
		case 'EXBX':
			volume = new BoxVolume();
			break;
		case 'CPST':
			volume = new CompositeVolume();
			break;
		case 'CMSH':
			volume = new MeshVolume();
			break;
		case 'CMPT':
			volume = new ComponentVolume();
			break;
		case 'DTAL':
			volume = new DetailVolume();
			break;
		case 'XCYL':
			volume = new CylinderVolume();
			break;
		case 'EXSP':
			volume = new SphereVolume();
			volume->read(iff);
			return volume;
		default: {
			logger.error(iff->getFileName() + " - INVALID VOLUME TYPE " + String::hexvalueOf((int64)type));
			iff->openForm(type);
			iff->closeForm(type);
			return NULL;
		}
	}
	iff->openForm(type);
	volume->read(iff);
	iff->closeForm(type);
	
	return volume;
}
