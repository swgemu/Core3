/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef VALUESCLASSES_H_
#define VALUESCLASSES_H_

#include "engine/engine.h"

class Values {
	VectorMap<string, float> values;
	string name;

public:
	Values(const string& n) {
		name = n;

		values.put("maxPercentage", 0.0f);
		values.put("currentPercentage", 0.0f);
		values.put("currentValue", 0.0f);
	}

	~Values(){
		values.removeAll();
	}

	inline float getPercentage() {
		return values.get("currentPercentage");
	}

	inline float getValue() {
		return values.get("currentValue");
	}

	inline float getMaxPercentage() {
		return values.get("maxPercentage");
	}

	inline string& getName() {
		return name;
	}

	inline void setValue(const float value) {
		if (values.contains("currentValue")) {
			values.drop("currentValue");
		}

		values.put("currentValue", value);
	}

	inline void setMaxPercentage(const float value) {
		if (values.contains("maxPercentage")) {
			values.drop("maxPercentage");
		}

		values.put("maxPercentage", value);
	}

	inline void setPercentage(const float value) {
		if (values.contains("currentPercentage")) {
			values.drop("currentPercentage");
		}

		values.put("currentPercentage", value);
	}
};

class Subclasses {
	VectorMap<string, Values*> valueList;
	float avePercentage;
	string name, className;

public:
	Subclasses(const string& title, const string& subtitle) {
		className = title;

		name = subtitle;

		Values* values = new Values(subtitle);

		valueList.put(subtitle, values);
	}

	~Subclasses(){
		for (int i = 0; i < valueList.size(); ++i)
			delete valueList.get(i);

		valueList.removeAll();
	}

	void addSubtitle(const string& s) {

		if (!valueList.contains(s)) {
			Values* values = new Values(s);

			valueList.put(s, values);
		}
	}

	inline Values* get(const int i){
		return valueList.get(i);
	}

	inline Values* get(const string& subTitle) {
		return valueList.get(subTitle);
	}

	inline int size(){
		return valueList.size();
	}

	inline float getPercentage(const string& subTitle) {
		Values* values = valueList.get(subTitle);
		return values->getPercentage();
	}

	inline float getMaxPercentage(const string& subTitle) {
		Values* values = valueList.get(subTitle);
		return values->getMaxPercentage();
	}

	inline float getValue(const string& subTitle) {
		Values* values = valueList.get(subTitle);
		return values->getValue();
	}

	inline string& getName() {
		return name;
	}

	inline string& getClassName() {
		return className;
	}

	inline void setMaxPercentage(const string& subtitle, const float value) {
		Values* values = valueList.get(subtitle);
		values->setMaxPercentage(value);

	}

	inline void setValue(const string& subtitle, const float value) {
		Values* values = valueList.get(subtitle);
		values->setValue(value);
	}

	inline void setPercentage(const string& subtitle, const float value) {
		Values* values = valueList.get(subtitle);
		values->setPercentage(value);
	}

	void toString(){
		Values* tempValues;

		for (int i = 0;i < valueList.size(); ++i) {

			tempValues = valueList.get(i);

			cout << "Property Name: " << tempValues->getName() << endl;
			cout << "Max % " << tempValues->getMaxPercentage() << endl;
			cout << "Current % " << tempValues->getPercentage() << endl;
			cout << "Current Value " << tempValues->getValue() << endl;
		}
	}
};

#endif /*VALUESCLASSES_H_*/
