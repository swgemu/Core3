/*
 * AuctionEventsMap.h
 *
 *  Created on: 09/08/2012
 *      Author: victor
 */

#ifndef AUCTIONEVENTSMAP_H_
#define AUCTIONEVENTSMAP_H_

class AuctionEventsMap : public VectorMap<uint64, Reference<Task*> >, public Mutex {

};

#endif /* AUCTIONEVENTSMAP_H_ */
