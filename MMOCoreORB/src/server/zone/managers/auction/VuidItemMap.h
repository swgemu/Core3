/*
 * VuidItemMap.h
 *
 *  Created on: Jun 11, 2012
 *      Author: kyle
 */

#ifndef VUIDITEMMAP_H_
#define VUIDITEMMAP_H_

#include "engine/engine.h"

class VuidItemMap : public VectorMap<VuidString, SortedVector<ManagedReference<AuctionItem*> > > {

};

#endif /* VUIDITEMMAP_H_ */
