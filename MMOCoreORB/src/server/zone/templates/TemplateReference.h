/*
 * TemplateReference.h
 *
 *  Created on: 16/07/2010
 *      Author: victor
 */

#ifndef TEMPLATEREFERENCE_H_
#define TEMPLATEREFERENCE_H_

#include "server/zone/managers/templates/TemplateManager.h"

template<class O> class TemplateReference : public Reference<O> {
public:
	TemplateReference() : Reference<O>() {
	}

	TemplateReference(TemplateReference& ref) : Reference<O>(ref) {
	}

	TemplateReference(const TemplateReference& ref) : Reference<O>(ref) {
	}

	TemplateReference(const O obj) : Reference<O>(obj) {
	}

	TemplateReference& operator=(const TemplateReference& ref) {
		if (this == &ref)
			return *this;

		Reference<O>::updateObject(ref);

		return *this;
	}

	bool operator==(const TemplateReference& ref) {
		return Reference<O>::get() == ref.get();
	}

	bool operator==(const O ref) {
		return Reference<O>::get() == ref;
	}

	bool toString(String& str) {
		if (Reference<O>::get() != NULL)
			str = String::valueOf((Reference<O>::get())->getServerObjectCRC());
		else
			str = String::valueOf(0);

		return true;
	}

	bool parseFromString(const String& str, int version = 0) {
		SharedObjectTemplate* obj = TemplateManager::instance()->getTemplate(UnsignedLong::valueOf(str));

		if (obj == NULL) {
			Reference<O>::updateObject(NULL);
			return false;
		}

		Reference<O>::updateObject((O) obj);

		return true;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		O object = Reference<O>::get();

		if (object != NULL)
			stream->writeInt(object->getServerObjectCRC());
		else
			stream->writeInt(0);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		uint32 oid = stream->readInt();

		SharedObjectTemplate* obj = TemplateManager::instance()->getTemplate(oid);

		if (obj == NULL) {
			Reference<O>::updateObject(NULL);
			return false;
		}

		Reference<O>::updateObject((O) obj);

		return true;
	}
};


#endif /* TEMPLATEREFERENCE_H_ */
