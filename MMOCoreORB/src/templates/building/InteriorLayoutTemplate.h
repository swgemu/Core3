/*
 * InteriorLayoutTemplate.h
 *
 *  Created on: 4/20/2016
 *      Author: GSlomin
 */

#ifndef INTERIORLAYOUTTEMPLATE_H_
#define INTERIORLAYOUTTEMPLATE_H_

#include "engine/engine.h"
#include "templates/ChildObject.h"
#include "templates/manager/TemplateManager.h"

class InteriorNode : public Object {
	Matrix4 transform;
	String templateFile;
	String cellName;
public:
	InteriorNode() {
		
	}
	
	void load(IffStream *iff) {
		iff->openChunk('NODE');
		
		iff->getString(templateFile);
		iff->getString(cellName);
		
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 4; y++)
			{
				transform[x][y] = iff->getFloat();
			}
		}
		
		iff->closeChunk('NODE');
	}
	
	const Matrix4& getTransform() {
		return transform;
	}
	
	String getTemplateFile() {
		return templateFile;
	}
	
	String getCellName() {
		return cellName;
	}
};

class InteriorLayoutTemplate : public IffTemplate {
	String name;
	Vector<Reference<InteriorNode*> > children;
public:
	InteriorLayoutTemplate() {

	}
	
	void load_0000(IffStream *iff) {
		Chunk *chunk = iff->openForm('0000');
		for (int i=0; i<chunk->getChunksSize(); i++) {
			Reference<InteriorNode*> node = new InteriorNode;
			node->load(iff);
			children.add(node);
		}
		
		iff->closeForm('0000');
	}
	
	void readObject(IffStream *iff) {
		iff->openForm('INLY');
		uint32 type = iff->getNextFormType();

		switch(type) {
			case '0000':
				load_0000(iff);
				break;
			default:
				TemplateManager::instance()->error("Unknown interior layout type " + String::hexvalueOf((int64)type));
		};
		iff->closeForm('INLY');
		
	}
	
	Vector<Reference<InteriorNode*> >& getChildren() {
		return children;
	}
};

#endif /* INTERIORLAYOUTTEMPLATE_H_ */
