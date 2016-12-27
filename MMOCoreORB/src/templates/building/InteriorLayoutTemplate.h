/*
 * InteriorLayoutTemplate.h
 *
 *  Created on: 4/20/2016
 *      Author: GSlomin
 */

#ifndef INTERIORLAYOUTTEMPLATE_H_
#define INTERIORLAYOUTTEMPLATE_H_

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

		transform[0][0] = iff->getFloat();
		transform[1][0] = iff->getFloat();
		transform[2][0] = iff->getFloat();
		transform[3][0] = iff->getFloat();

		transform[0][1] = iff->getFloat();
		transform[1][1] = iff->getFloat();
		transform[2][1] = iff->getFloat();
		transform[3][1] = iff->getFloat();

		transform[0][2] = iff->getFloat();
		transform[1][2] = iff->getFloat();
		transform[2][2] = iff->getFloat();
		transform[3][2] = iff->getFloat();

		iff->closeChunk('NODE');
	}

	const Matrix4& getTransform() {
		return transform;
	}

	const String& getTemplateFile() {
		return templateFile;
	}

	const String& getCellName() {
		return cellName;
	}
};

class InteriorLayoutTemplate : public IffTemplate {
	String name;
	Vector<Reference<InteriorNode*> > children;
public:
	InteriorLayoutTemplate() {

	}

	void readObject(IffStream *iff) {
		iff->openForm('INLY');
		uint32 type = iff->getNextFormType();

		if(type == '0000') {
			Chunk *chunk = iff->openForm('0000');
			for (int i=0; i<chunk->getChunksSize(); i++) {
				Reference<InteriorNode*> node = new InteriorNode;
				node->load(iff);
				children.add(node);
			}

			iff->closeForm('0000');
		} else {
			//TemplateManager::instance()->error("Unknown interior layout type " + String::hexvalueOf((int64)type));
		}

		iff->closeForm('INLY');
	}

	const Vector<Reference<InteriorNode*> >& getChildren() const {
		return children;
	}
};

#endif /* INTERIORLAYOUTTEMPLATE_H_ */
