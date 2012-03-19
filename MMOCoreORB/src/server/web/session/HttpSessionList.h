/*
 * HttpSessionList.h
 *
 *  Created on: Jun 2, 2011
 *      Author: kyle
 */

#ifndef HTTPSESSIONLIST_H_
#define HTTPSESSIONLIST_H_

#include "engine/engine.h"

using namespace server::web;

namespace server {
namespace web {
namespace session {

class HttpSessionList : public VectorMap<String, HttpSession*> {

public:
	HttpSessionList() {

    }
	virtual ~HttpSessionList() {

	}

};

}
}
}
using namespace server::web::session;

#endif /* HTTPSESSIONLIST_H_ */
