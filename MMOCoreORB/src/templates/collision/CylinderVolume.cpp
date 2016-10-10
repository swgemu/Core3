#include "CylinderVolume.h"

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
#ifdef OSG_RENDERER
osg::ref_ptr<osg::Node> CylinderVolume::draw() const {
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
#endif