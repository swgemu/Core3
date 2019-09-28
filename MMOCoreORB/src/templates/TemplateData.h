/*
 * TemplateData.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef TEMPLATEDATA_H_
#define TEMPLATEDATA_H_

#include "system/lang/Object.h"

class TemplateData : public virtual Object {
public:
	constexpr const static bool is_virtual_object = true;

	virtual ~TemplateData() {

	}
};

#endif /* TEMPLATEDATA_H_ */
