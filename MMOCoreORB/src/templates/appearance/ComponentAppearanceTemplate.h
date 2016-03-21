/*
 * ComponentAppearanceTemplate.h
 *
 *  Created on: 10/12/2010
 *      Author: victor
 */

#ifndef COMPONENTAPPEARANCETEMPLATE_H_
#define COMPONENTAPPEARANCETEMPLATE_H_

#include "engine/engine.h"
#include "templates/appearance/AppearanceTemplate.h"
#include "templates/manager/TemplateManager.h"

class ComponentMeshAppearanceTemplate : public Object {
	Matrix4 transform;
	AppearanceTemplate *mesh;
public:
	ComponentMeshAppearanceTemplate(Matrix4 transform, AppearanceTemplate *mesh) {
		this->transform = transform;
		this->mesh = mesh;
	}
	
	Matrix4& getTransform() {
		return transform;
	}
	
	AppearanceTemplate* getMeshTemplate() {
		return mesh;
	}
	
	const Matrix4& getTransform() const {
		return transform;
	}
	
	const AppearanceTemplate* getMeshTemplate() const {
		return mesh;
	}
};


class ComponentAppearanceTemplate : public AppearanceTemplate {
	Vector<Reference<ComponentMeshAppearanceTemplate*> > meshes;

public:
	virtual uint32 getType() {
		return 'CMPA';
	}
	ComponentAppearanceTemplate() {
	}

	~ComponentAppearanceTemplate() {
	}
	
	const Vector<Reference<ComponentMeshAppearanceTemplate*> > getComponents() const {
		return meshes;
	}

	void readObject(IffStream* templateData) {
		parse(templateData);
	}
	
	// TODO: This needs to be deprecated IMMEDIATELY it is only here to allow the server to continue compiling
	// This functionality is 100% broken
	AppearanceTemplate* getFirstMesh() {
		return const_cast<AppearanceTemplate*>(meshes.get(0)->getMeshTemplate());
	}

	void parse(IffStream* iffStream) {
		iffStream->openForm('CMPA');

		uint32 version = iffStream->getNextFormType();
		iffStream->openForm(version);

		AppearanceTemplate::readObject(iffStream);
		
		if(iffStream->getNextFormType() == 'RADR') {
			iffStream->openForm('RADR');
			iffStream->closeForm('RADR');
		}

		int subChunks = iffStream->getRemainingSubChunksNumber();// dataChunk->getChunksSize();

		// load *all* components
		for (int i = 0; i < subChunks; ++i) {
			iffStream->openChunk('PART');

			// int var1 = iffStream->getInt();

			/*QString str;
	                    iffStream->getString(str);*/

			String meshFile;
			iffStream->getString(meshFile);

			AppearanceTemplate* templ = TemplateManager::instance()->getAppearanceTemplate("appearance/" + meshFile);
	
			Matrix4 mat;
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 4; y++)
				{
					mat[x][y] = iffStream->getFloat();
				}
			}
			
			meshes.add(new ComponentMeshAppearanceTemplate(mat, templ));
			
			iffStream->closeChunk('PART');
		}

		iffStream->closeForm(version);
		iffStream->closeForm('CMPA');
	}

};

#endif /* COMPONENTAPPEARANCETEMPLATE_H_ */
