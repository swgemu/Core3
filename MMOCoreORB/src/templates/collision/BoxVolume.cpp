#include "BoxVolume.h"

void BoxVolume::read(IffStream *iff) {
	iff->openForm('0001');
	BaseBoundingVolume::read(iff);
	iff->openChunk('BOX ');
	float maxx = iff->getFloat();
	float maxy = iff->getFloat();
	float maxz = iff->getFloat();

	float minx = iff->getFloat();
	float miny = iff->getFloat();
	float minz = iff->getFloat();

	bbox = AABB(Vector3(minx, miny, minz), Vector3(maxx, maxy, maxz));
	iff->closeChunk('BOX ');
	iff->closeForm('0001');
}
#ifdef OSG_RENDERER
osg::ref_ptr<osg::Node> BoxVolume::draw() const {
	Vector3 boxCenter = bbox.center();
	Vector3 boxExtents = bbox.extents();
	osg::Geode* geode = new osg::Geode();
	geode->addDrawable( new osg::ShapeDrawable( new osg::Box(osg::Vec3(boxCenter.getX(), boxCenter.getY(), boxCenter.getZ()), boxExtents.getX()*2, boxExtents.getY()*2, boxExtents.getZ()*2)) );

	geode->getOrCreateStateSet()->setAttribute( new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE) );

	return geode;
}
#endif
