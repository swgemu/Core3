/*
 * Servlet.h
 *
 *  Created on: May 31, 2011
 *      Author: kyle
 */

#ifndef SERVLET_H_
#define SERVLET_H_

#include "engine/engine.h"

class Servlet : Logger {
public:
	Servlet(String context);
	virtual ~Servlet();

	virtual String generatePage() = 0;

};

#endif /* SERVLET_H_ */
