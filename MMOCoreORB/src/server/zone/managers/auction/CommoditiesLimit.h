/*
 * CommoditiesLimit.h
 *
 *  Created on: Aug 4, 2012
 *      Author: kyle
 */

#ifndef COMMODITIESLIMIT_H_
#define COMMODITIESLIMIT_H_

class CommoditiesLimit : public VectorMap<uint64, Vector<ManagedWeakReference<AuctionItem*> > >, public ReadWriteLock {

};

#endif /* COMMODITIESLIMIT_H_ */
