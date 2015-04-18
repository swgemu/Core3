/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef VENDOROUTFITMANAGER_H_
#define VENDOROUTFITMANAGER_H_

#include "engine/engine.h"
#include "Outfit.h"

namespace server {
namespace zone {
	class ZoneProcessServer;
}
}

using namespace server::zone;

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
