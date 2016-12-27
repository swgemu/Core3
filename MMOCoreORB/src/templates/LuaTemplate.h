/*
 * LuaTemplate.h
 *
 *  Created on: 30/04/2010
 *      Author: victor
 */

#ifndef LUATEMPLATE_H_
#define LUATEMPLATE_H_

#include "templates/TemplateData.h"
#include "engine/lua/LuaObject.h"

class LuaTemplate : public virtual TemplateData {
public:
	virtual void readObject(LuaObject* templateData) = 0;

	virtual ~LuaTemplate() {

	}
};

#endif /* LUATEMPLATE_H_ */
