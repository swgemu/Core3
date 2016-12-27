/*
 * HuntingTargetEntry.h
 *
 *  Created on: Aug 27, 2010
 *      Author: da
 */

#ifndef HUNTINGTARGETENTRY_H_
#define HUNTINGTARGETENTRY_H_

class HuntingTargetEntry : public Object {
private:
	String templatePrimary;
	String templateSecondary;

public:
	HuntingTargetEntry() {
		templatePrimary = "";
		templateSecondary = "";
	}

	HuntingTargetEntry(const String& temp1, const String& temp2) {
		templatePrimary = temp1;
		templateSecondary = temp2;
	}

	String getPrimary() {
		return templatePrimary;
	}

	String getSecondary() {
		return templateSecondary;
	}

	int compareTo(const HuntingTargetEntry& entry) const {
		if (templatePrimary.hashCode() < entry.templatePrimary.hashCode())
			return 1;
		else if (templatePrimary.hashCode() > entry.templatePrimary.hashCode())
			return -1;

		return 0;
	}
};

#endif /* HUNTINGTARGETENTRY_H_ */
