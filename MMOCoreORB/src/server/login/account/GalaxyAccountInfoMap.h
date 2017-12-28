/*
 * GalaxyAccountInfoMap.h
 *
 *  Created on: 4/30/2016
 *      Author: gslomin
 */

#ifndef GALAXYACCOUNTINFOMAP_H_
#define GALAXYACCOUNTINFOMAP_H_

#include "server/login/account/GalaxyAccountInfo.h"
#include "system/lang/ref/Reference.h"
#include "system/util/VectorMap.h"

namespace sys {
namespace io {
class ObjectInputStream;
class ObjectOutputStream;
}  // namespace io
namespace lang {
class String;
}  // namespace lang
}  // namespace sys

class GalaxyAccountInfoMap : public VectorMap<String, Reference<GalaxyAccountInfo*> > {
public:
	GalaxyAccountInfoMap();
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
};

#endif /* #define GALAXYACCOUNTINFOMAP_H_ */
