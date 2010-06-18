/*
 * MapLocationTable.h
 *
 *  Created on: 18/06/2010
 *      Author: victor
 */

#ifndef MAPLOCATIONTABLE_H_
#define MAPLOCATIONTABLE_H_

#include "MapLocationEntry.h"

class MapLocationTable : public VectorMap<uint64, MapLocationEntry>, public ReadWriteLock {

};

#endif /* MAPLOCATIONTABLE_H_ */
