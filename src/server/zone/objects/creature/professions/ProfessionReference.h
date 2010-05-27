/*
 * ProfessionReference.h
 *
 *  Created on: 26/05/2010
 *      Author: victor
 */

#ifndef PROFESSIONREFERENCE_H_
#define PROFESSIONREFERENCE_H_

#include "Profession.h"
#include "server/zone/managers/professions/ProfessionManager.h"

class ProfessionReference : public Reference<Profession*> {
	public:
		ProfessionReference() : Reference<Profession*>() {
		}

		ProfessionReference(const ProfessionReference& ref) : Reference<Profession*>(ref) {
		}

		ProfessionReference(Profession* obj) : Reference<Profession*>(obj) {
		}

		ProfessionReference& operator=(const ProfessionReference& ref) {
			if (this == &ref)
				return *this;

			Reference<Profession*>::updateObject(ref.object);

			return *this;
		}

		void setProfession(Profession* obj) {
			Reference<Profession*>::updateObject(obj);
		}

		Profession* operator=(Profession* obj) {
			Reference<Profession*>::updateObject(obj);

			return obj;
		}

		int compareTo(const ProfessionReference& ref) const {
			return Reference<Profession*>::object->compareTo(ref.object);
		}

		bool toString(String& str) {
			if (Reference<Profession*>::get() != NULL)
				str = String::valueOf((Reference<Profession*>::get())->getName());
			else
				str = String::valueOf(0);

			return true;
		}

		bool parseFromString(const String& str, int version = 0) {
			Profession* obj = ProfessionManager::instance()->getProfession(str);

			Reference<Profession*>::updateObject(obj);

			if (obj == NULL)
				return false;

			return true;
		}

		bool toBinaryStream(ObjectOutputStream* stream) {
			Profession* object = Reference<Profession*>::get();

			if (object != NULL)
				object->getName().toBinaryStream(stream);
			else
				String("0").toBinaryStream(stream);

			return true;
		}

		bool parseFromBinaryStream(ObjectInputStream* stream) {
			String name;
			name.parseFromBinaryStream(stream);

			Profession* obj = ProfessionManager::instance()->getProfession(name);
			*this = obj;

			if (obj == NULL)
				return false;

			return true;
		}
};

#endif /* PROFESSIONREFERENCE_H_ */
