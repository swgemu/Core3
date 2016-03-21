#ifndef CLIENTCOMPONENTAPPEARANCE_H_
#define CLIENTCOMPONENTAPPEARANCE_H_

#include "ClientAppearance.h"
#include "templates/appearance/ComponentAppearanceTemplate.h"
#include "client/zone/managers/appearance/AppearanceManager.h"

class ClientComponentMeshAppearance : public Object {
	ClientAppearance *appearance;
	Matrix4 transform;
public:
	ClientComponentMeshAppearance(Matrix4 transform, AppearanceTemplate *mesh){
		this->transform = transform;
		appearance = AppearanceManager::instance()->getAppearance(mesh);
	}
	
	ClientAppearance* getAppearance() const {
		return appearance;
	}
	
	const Matrix4& getTransform() const {
		return transform;
	}
	
	Matrix4 getTransform() {
		return transform;
	}
};

class ClientComponentAppearance : public ClientAppearance {
	
	Vector<Reference<ClientComponentMeshAppearance*> > components;
	
public:
	
	ClientComponentAppearance(AppearanceTemplate *tmpl) : ClientAppearance(tmpl) {
		ComponentAppearanceTemplate *comp = cast<ComponentAppearanceTemplate*>(tmpl);
		assert(comp != NULL);
		const Vector<Reference<ComponentMeshAppearanceTemplate*> > templateComponents =  comp->getComponents();
		
		for(int i=0; i<templateComponents.size(); i++) {
			ComponentMeshAppearanceTemplate *comp = templateComponents.get(i);
			components.add(new ClientComponentMeshAppearance(comp->getTransform(), comp->getMeshTemplate()));
		}
	}
	
	virtual osg::ref_ptr<osg::Node> draw()  {
		osg::ref_ptr<osg::Group> group(new osg::Group);
		
		for(int i=0; i<components.size(); i++) {
			osg::MatrixTransform * transform  = new osg::MatrixTransform( );
			const ClientComponentMeshAppearance *mesh = components.get(i);
			
			Matrix4 ourTransform = mesh->getTransform();
			
			osg::Matrix matrix(ourTransform[0][0], ourTransform[0][1], ourTransform[0][2], ourTransform[0][3],
							   ourTransform[1][0], ourTransform[1][1], ourTransform[1][2], ourTransform[2][3],
							   ourTransform[2][0], ourTransform[2][1], ourTransform[2][2], ourTransform[1][3],
							   0, 0, 0, 1);
			
			
			transform->setMatrix(matrix);
			
			transform->addChild(mesh->getAppearance()->draw());
			
			group->addChild(transform);
			
		}
		
		return group;
	}
	
	virtual Vector<Reference<MeshData* > > getTransformedMeshData() {
		Vector<Reference<MeshData*> > transformedMeshData;
		for(int i=0; i<components.size(); i++) {
			ClientComponentMeshAppearance *mesh = components.get(i);
			
			Matrix4 ourTransform = mesh->getTransform();
			Vector<Reference<MeshData* > > data = mesh->getAppearance()->getTransformedMeshData();
			
			for(int j=0; j<data.size(); j++) {
				MeshData *mesh = data.get(i);
				//mesh->transformMeshData(ourTransform);
				transformedMeshData.add(mesh);
			}
		}
		
		return transformedMeshData;
	}
};
#endif
