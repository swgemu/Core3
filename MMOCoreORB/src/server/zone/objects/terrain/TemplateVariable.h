/*
 * TemplateVariable.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef TEMPLATEVARIABLE_H_
#define TEMPLATEVARIABLE_H_

#include "engine/engine.h"

template <int version> struct Version {
   enum { value = version };
};


template <int formType> struct FormType {
   enum { value =  formType};
};

class IffTemplateVariable {
public:
	virtual ~IffTemplateVariable() {

	}

	virtual void readObject(engine::util::IffStream* iffStream) = 0;
};

template<int formType>
class TemplateVariable : public virtual IffTemplateVariable {

public:

	virtual ~TemplateVariable() {

	}

	void readObject(engine::util::IffStream* iffStream) {
		if (iffStream->openForm(formType) == NULL)
			throw Exception("Incorrect form type " + String::valueOf(formType));

		parseFromIffStream(iffStream);

		iffStream->closeForm(formType);
	}

	virtual void parseFromIffStream(engine::util::IffStream* iffStream) {

	}


};


#endif /* TEMPLATEVARIABLE_H_ */
