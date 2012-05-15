/*
 * ResourceServlet.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#ifndef RESOURCESERVLET_H_
#define RESOURCESERVLET_H_

#include "../Servlet.h"

class ResourceServlet: public Servlet {
public:
	ResourceServlet(String context);
	virtual ~ResourceServlet();
};

#endif /* RESOURCESERVLET_H_ */
