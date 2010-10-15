/*
 * AccountMap.h
 *
 *  Created on: Oct 14, 2010
 *      Author: crush
 */

#ifndef ACCOUNTMAP_H_
#define ACCOUNTMAP_H_

#include "engine/engine.h"

namespace server {
namespace login {
namespace account {

	class AccountMap : public VectorMap<uint32, ManagedReference<Account*> >, public ReadWriteLock {

	public:
		AccountMap() : VectorMap<uint32, ManagedReference<Account*> >(), ReadWriteLock("AccountMap") {
			setInsertPlan(VectorMap<uint32, ManagedReference<Account*> >::NO_DUPLICATE);
			setNullValue(NULL);
		}
	};

}
}
}


#endif /* ACCOUNTMAP_H_ */
