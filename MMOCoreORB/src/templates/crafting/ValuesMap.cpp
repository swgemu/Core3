/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ValuesMap.h"

float ValuesMap::VALUENOTFOUND = -999999;

void ValuesMap::addExperimentalProperty(const String& title, const String& subtitle,
		const float min, const float max, const int precision, const bool filler, const int combine) {
	Subclasses* subclasses;

	if (contains(title)) {
		subclasses = get(title);

		subclasses->addSubtitle(subtitle, min, max, precision, filler, combine);
	} else {
		subclasses = new Subclasses(title, subtitle, min, max, precision, filler, combine);

		put(title, subclasses);
	}
}

String& ValuesMap::getExperimentalPropertyTitle(const String& subtitle) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int j = 0; j < subclasses->size(); ++j) {
			values = subclasses->get(j);

			if (values->getName() == subtitle) {
				return subclasses->getClassTitle();
			}
		}
	}

	return EMPTY;
}

String& ValuesMap::getExperimentalPropertyTitle(const int i) {
	Subclasses* subclasses = get(i);

	if (subclasses != NULL) {
		return subclasses->getClassTitle();
	}

	return EMPTY;
}

String& ValuesMap::getVisibleExperimentalPropertyTitle(const int i) {
	Subclasses* subclasses;
	int counter = -1;
	String title;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		if (!subclasses->hasAllHiddenItems())
			counter++;

		if (counter == i)
			return subclasses->getClassTitle();
	}

	return EMPTY;
}

String& ValuesMap::getExperimentalPropertySubtitlesTitle(const int i) {
	Subclasses* subclasses;
	int count = 0;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		if (count + subclasses->size() <= i) {
			count += subclasses->size();
		} else {
			return subclasses->getClassTitle();
		}
	}

	return EMPTY;
}

String& ValuesMap::getExperimentalPropertySubtitle(const int i) {
	Subclasses* subclasses;
	int count = 0;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		if (count + subclasses->size() <= i) {
			count += subclasses->size();
		} else {
			count = i - count;

			Values* values = subclasses->get(count);

			return values->getName();
		}
	}

	return EMPTY;
}

String& ValuesMap::getExperimentalPropertySubtitle(const String& title, const int i) {
	Subclasses* subclasses = get(title);

	if (subclasses != NULL)
		return subclasses->get(i)->getName();
	else
		return EMPTY;
}

int ValuesMap::getExperimentalPropertySubtitleSize() {
	Subclasses* subclasses;
	int subtitleSize = 0;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		subtitleSize += subclasses->size();
	}

	return subtitleSize;
}

int ValuesMap::getExperimentalPropertySubtitleSize(const String& title) {
	Subclasses* subclasses = get(title);

	if (subclasses != NULL)
		return subclasses->size();

	return (int)VALUENOTFOUND;
}

bool ValuesMap::hasProperty(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return true;
			}
		}
	}

	return false;
}

bool ValuesMap::isHidden(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->isFiller();
			}
		}
	}

	return false;
}

void ValuesMap::setHidden(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setFiller(true);
			}
		}
	}
}

void ValuesMap::unsetHidden(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setFiller(false);
			}
		}
	}
}

short ValuesMap::getCombineType(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getCombineType();
			}
		}
	}

	return (int)VALUENOTFOUND;
}

void ValuesMap::setCurrentValue(const String& attribute, const float value) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setValue(value);
				return;
			}
		}
	}
}

void ValuesMap::setCurrentValue(const String& attribute, const float value, const float min, const float max) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setMaxValue(max);
				values->setMinValue(min);

				values->setValue(value);
				return;
			}
		}
	}
}

float ValuesMap::getCurrentValue(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getValue();
			}
		}
	}

	return VALUENOTFOUND;
}

float ValuesMap::getCurrentValue(const int i) {
	Subclasses* subclasses;
	int count = 0;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		if (count + subclasses->size() <= i) {
			count += subclasses->size();
		} else {
			count = i - count;

			Values* values = subclasses->get(count);

			return values->getValue();
		}
	}

	return VALUENOTFOUND;
}

void ValuesMap::lockValue(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->lockValue();
				return;
			}
		}
	}
}

void ValuesMap::unlockValue(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->unlockValue();
				return;
			}
		}
	}
}

void ValuesMap::resetValue(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->resetValue();
				return;
			}
		}
	}
}

void ValuesMap::setCurrentPercentage(const String& subtitle, float value) {
	float max = 0.0f;

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == subtitle) {
				max = values->getMaxPercentage();

				if (value > max)
					values->setPercentage(max);
				else
					values->setPercentage(value);

				return;
			}
		}
	}
}

void ValuesMap::setCurrentPercentage(const String& subtitle, float value, float max) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == subtitle) {
				values->setMaxPercentage(max);

				if (value > max)
					values->setPercentage(max);
				else
					values->setPercentage(value);

				return;
			}
		}
	}
}

float ValuesMap::getCurrentPercentage(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getPercentage();
			}
		}
	}

	return VALUENOTFOUND;
}

float ValuesMap::getCurrentPercentage(const int i) {
	Subclasses* subclasses;
	int count = 0;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		if (count + subclasses->size() <= i) {
			count += subclasses->size();
		} else {
			count = i - count;

			Values* values = subclasses->get(count);

			return values->getPercentage();
		}
	}

	return VALUENOTFOUND;
}

float ValuesMap::getCurrentVisiblePercentage(const String title) {
	Subclasses* subclasses = get(title);

	if (subclasses == NULL)
		return -1;

	Values* values;
	float value = 0;

	// shouldnt this show the avg so with 1 item who cares, but more than 1 we wanna should avg of all not the LAST one
	for (int j = 0; j < subclasses->size(); ++j) {
		values = subclasses->get(j);

		if (values->getMinValue() != values->getMaxValue() &&
				values->getMaxPercentage() <= 1.0f && !values->isFiller()) {

			float item = values->getPercentage();

			if (item > value)
				value = item;
		}
	}

	return value;
}

void ValuesMap::setMaxPercentage(const String& attribute, float value) {
	float max;

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setMaxPercentage(value);
				return;
			}
		}
	}
}

float ValuesMap::getMaxPercentage(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getMaxPercentage();
			}
		}
	}

	return VALUENOTFOUND;
}

float ValuesMap::getMaxPercentage(const int i) {
	Subclasses* subclasses;
	int count = 0;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		if (count + subclasses->size() <= i) {
			count += subclasses->size();
		} else {
			count = i - count;

			Values* values = subclasses->get(count);

			return values->getMaxPercentage();
		}
	}

	return VALUENOTFOUND;
}

float ValuesMap::getMaxVisiblePercentage(const int i) {
	String title = getVisibleExperimentalPropertyTitle(i);
	Subclasses* subclasses = get(title);
	Values* values;

	float value = 0;
	float count = 0;

	for (int j = 0; j < subclasses->size(); ++j) {
		values = subclasses->get(j);

		if (values->getMinValue() != values->getMaxValue() &&
				values->getMaxPercentage() <= 1.0f && !values->isFiller()) {

			if (values->getMaxPercentage() > value)
				value = values->getMaxPercentage();
		}
	}

	return value;
}

float ValuesMap::getMinValue(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getMinValue();
			}
		}
	}

	return VALUENOTFOUND;
}

float ValuesMap::getMaxValue(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getMaxValue();
			}
		}
	}

	return VALUENOTFOUND;
}

void ValuesMap::setMinValue(const String& attribute, const float value) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setMinValue(value);
			}
		}
	}
}

void ValuesMap::setMaxValue(const String& attribute, const float value) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setMaxValue(value);
			}
		}
	}
}

int ValuesMap::getPrecision(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getPrecision();
			}
		}
	}

	return (int)VALUENOTFOUND;
}

void ValuesMap::setPrecision(const String& attribute, const int value) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < size(); ++j) {
		subclasses = get(j);

		for (int i = 0; i < subclasses->size(); ++i) {
			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setPrecision(value);
			}
		}
	}
}
