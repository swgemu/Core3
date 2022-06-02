#ifndef INSTALLATIONRESOURCEDATA_H_
#define INSTALLATIONRESOURCEDATA_H_

class InstallationResourceData : public Object {
	String name, parentName;
	uint64 id;
	uint8 efficiency;

public:
	InstallationResourceData() {
		id = 0;
		efficiency = 0;
		name = "";
		parentName = "";
	}

	InstallationResourceData(const String& name, uint64 id, const String& parentName, uint8 efficiency) {
		this->name = name;
		this->id = id;
		this->parentName = parentName;
		this->efficiency = efficiency;
	}

	InstallationResourceData(const InstallationResourceData& dataCopy) : Object() {
		name = dataCopy.name;
		id = dataCopy.id;
		parentName = dataCopy.parentName;
		efficiency = dataCopy.efficiency;
	}

	InstallationResourceData& operator=(const InstallationResourceData& dataCopy) {
		if (this == &dataCopy)
			return *this;

		name = dataCopy.name;
		id = dataCopy.id;
		parentName = dataCopy.parentName;
		efficiency = dataCopy.efficiency;

		return *this;
	}

	inline const String& getName() const {
		return name;
	}

	inline const String& getParentName() const {
		return parentName;
	}

	inline int getId() const {
		return id;
	}

	inline uint8 getEfficiency() const {
		return efficiency;
	}
};

#endif /* INSTALLATIONRESOURCEDATA_H_ */
