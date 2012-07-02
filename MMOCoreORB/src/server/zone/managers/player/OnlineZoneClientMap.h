/*
 * OnlineZoneClientMap.h
 *
 *  Created on: 11/06/2012
 *      Author: victor
 */

#ifndef ONLINEZONECLIENTMAP_H_
#define ONLINEZONECLIENTMAP_H_

#include "engine/engine.h"
#include "server/zone/ZoneClientSession.h"
#include "server/db/ServerDatabase.h"

class OnlineZoneClientMap : public HashTable<uint32, Vector<Reference<ZoneClientSession*> > > {
protected:
  HashTable<String, Reference<SortedVector<uint32>*> > ips;
  ReadWriteLock mutex;
public:

  void addAccount(const String& ip, uint32 accountId) {
      
      StringBuffer query;
      query << " insert into account_ips (account_id, ip) values(" << accountId << ", '" << ip << "');";
      ServerDatabase::instance()->executeStatement(query);
      
      Locker locker(&mutex);
      Reference<SortedVector<uint32>* > account = ips.get(ip);
      
      if (account == NULL) {
        account = new SortedVector<uint32>();        
        account->setNoDuplicateInsertPlan();
        account->put(accountId);
        
        ips.put(ip, account);
      } else {
        account->put(accountId);
      }      
      //account->put(ip);      
  }
  
  void accountLoggedOut(const String& ip, uint32 accountId) {
       StringBuffer query;
       query << " insert into account_ips (account_id, ip, logout) values(" << accountId << ", '" << ip << "'," << 1 << ");";
       ServerDatabase::instance()->executeStatement(query);
       
       Locker locker(&mutex);
       
       Reference<SortedVector<uint32>* > account = ips.get(ip);
       
       if (account == NULL)
         return;
         
        account->drop(accountId);
       
 
       if (account->size() == 0)
         ips.remove(ip);                  
  }
  
  SortedVector<uint32> getAccountsLoggedIn(const String& ip) {
    mutex.rlock();
    
    SortedVector<uint32> ret;
    Reference<SortedVector<uint32>*> accounts = ips.get(ip);
    
    if (accounts != NULL)
      ret.addAll(*accounts);
    
    mutex.runlock();
    
    return ret;    
  } 
  
  int getDistinctIps() {
    return ips.size();
  }
  
  
  
  
};


#endif /* ONLINEZONECLIENTMAP_H_ */
