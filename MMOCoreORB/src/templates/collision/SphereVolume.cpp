#include "SphereVolume.h"

#ifdef OSG_RENDERER
osg::ref_ptr<osg::Node> SphereVolume::draw() const {
	osg::TessellationHints* hints = new osg::TessellationHints;
	hints->setDetailRatio(0.5f);
	osg::Geode* geode = new osg::Geode();
	Vector3 center = bsphere.getCenter();
	geode->addDrawable( new osg::ShapeDrawable( new osg::Sphere(osg::Vec3(center.getX(), center.getY(), center.getZ()), bsphere.getRadius()), hints ) );

	geode->getOrCreateStateSet()->setAttribute( new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE) );

	return geode;
}
#endif