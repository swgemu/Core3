#ifndef CLIENTDETAILAPPEARANCE_H_
#define CLIENTDETAILAPPEARANCE_H_
#include "ClientAppearance.h"
#include "templates/appearance/DetailAppearanceTemplate.h"

class ClientDetailAppearance : public ClientAppearance{
	Vector<ClientAppearance*> lodMeshes;
public:
	ClientDetailAppearance(AppearanceTemplate *tmpl) : ClientAppearance(tmpl) {
		DetailAppearanceTemplate *dtal = cast<DetailAppearanceTemplate*>(tmpl);
		assert(dtal != NULL);
		
		AppearanceTemplate *child = dtal->getFirstMesh();
		
		ClientAppearance *appearance = AppearanceManager::instance()->getAppearance(child);
		assert(appearance != NULL);
		
		lodMeshes.add(appearance);
	}
	
	osg::ref_ptr<osg::Node> draw() {
		osg::ref_ptr<osg::Group> group(new osg::Group);
		
		for (int i=0; i<lodMeshes.size(); i++) {
			group->addChild(lodMeshes.get(i)->draw());
		}
		
		return group;
	}
	
	virtual Vector<Reference<MeshData* > > getTransformedMeshData() {
		Vector<Reference<MeshData* > > meshes;
		if(lodMeshes.size() > 0)
			meshes.addAll(lodMeshes.get(0)->getTransformedMeshData());
		
		return meshes;
	}
};
#endif
