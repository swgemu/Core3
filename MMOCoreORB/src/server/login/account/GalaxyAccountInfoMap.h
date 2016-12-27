/*
 * GalaxyAccountInfoMap.h
 *
 *  Created on: 4/30/2016
 *      Author: gslomin
 */

#ifndef GALAXYACCOUNTINFOMAP_H_
#define GALAXYACCOUNTINFOMAP_H_

#include "server/login/account/GalaxyAccountInfo.h"

class GalaxyAccountInfoMap : public VectorMap<String, Reference<GalaxyAccountInfo*> > {
public:
	GalaxyAccountInfoMap();
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
};

#endif /* #define GALAXYACCOUNTINFOMAP_H_ */
