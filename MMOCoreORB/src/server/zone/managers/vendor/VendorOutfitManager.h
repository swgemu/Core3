/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef VENDOROUTFITMANAGER_H_
#define VENDOROUTFITMANAGER_H_

#include "Outfit.h"
#include "engine/log/Logger.h"
#include "engine/util/Singleton.h"
#include "system/lang/Object.h"
#include "system/lang/String.h"
#include "system/lang/ref/Reference.h"
#include "system/util/VectorMap.h"

namespace server {
namespace zone {
namespace managers {
namespace vendor {

class VendorOutfitManager : public Singleton<VendorOutfitManager>, public Logger, public Object {
	VectorMap<String, Reference<Outfit*> > outfits;

public:
	VendorOutfitManager() {

	}

	~VendorOutfitManager() {

	}

	void initialize();

	void loadLuaOutfits();

	inline VectorMap<String, Reference<Outfit*> >* getOutfits() {
		return &outfits;
	}

	inline String& getOutfitName(int idx) {
		return outfits.elementAt(idx).getKey();
	}

	inline Reference<Outfit*> getOutfit(int idx) {
		return outfits.get(idx);
	}

	inline Reference<Outfit*> getOutfit(const String& key) {
		return outfits.get(key);
	}

};

}
}
}
}

using namespace server::zone::managers::vendor;

#endif /* VENDOROUTFITMANAGER_H_ */
