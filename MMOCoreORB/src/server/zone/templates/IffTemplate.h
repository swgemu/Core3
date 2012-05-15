/*
 * IffTemplate.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef IFFTEMPLATE_H_
#define IFFTEMPLATE_H_

#include "engine/engine.h"
#include "engine/util/iffstream/IffStream.h"
#include "TemplateData.h"

class IffTemplate : public virtual TemplateData {
public:
	virtual void readObject(IffStream* templateData) = 0;

	virtual ~IffTemplate() {

	}
};

#endif /* IFFTEMPLATE_H_ */
