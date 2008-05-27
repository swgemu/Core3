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

#ifndef CUSTOMIZATIONVARIABLES_H_
#define CUSTOMIZATIONVARIABLES_H_

#include "system/lang.h"

class CustomizationVariables : private VectorMap<uint8, uint16> {
	uint8 unknown;
	
public:
	CustomizationVariables() : VectorMap<uint8, uint16>() {
		unknown = 1;
		
		setNullValue(0);
		
		setInsertPlan(SortedVector<uint16>::NO_DUPLICATE);
	}
	
	CustomizationVariables& operator=(string& custString) {
		removeAll();
		
		if (custString.size() < 2)
			return *this;
		
		try {
			unknown = (uint8)custString.at(0);
			uint8 type = 0;

			int totalVars = (uint8)custString.at(1);
			int offset = 1;

			for (int i = 0; i < totalVars; ++i) {
				uint16 value;

				uint8 type = (uint8)custString.at(++offset);
				uint8 value1 = (uint8)custString.at(++offset);

				if (value1 == 0xFF)
					value = 0xFF + ((uint16)custString.at(++offset) << 8);
				else
					value = value1;

				setVariable(type, value);
			}
		} catch (...) {
			removeAll();
			//cout << "Exception in CustomizationVariables& operator=(string& custString)\n";
		}
		
		return *this;
	}
	
	void setVariable(uint8 type, uint16 value) {
		drop(type);
		put(type, value);
		//cout << "inserted type:[" << hex << type << "] value:[" << hex << value << "]\n";
	}
	
	uint16 getVariable(uint8 type) {
		return get(type);
	}
	
	uint16 getVariable(int idx) {
		return get(idx);
	}
	
	void getVariable(int idx, uint8& type, uint16& value) {
		VectorMapEntry<uint8, uint16>* entry = SortedVector<VectorMapEntry<uint8, uint16>*>::get(idx);
		
		type = entry->getKey();
		value = entry->getValue();
	}
	
	int getSize() {
		return size();
	}

	void toString(string& ascii) {
		if (size() == 0)
			return;
		
		ascii.clear();
		
		ascii.push_back(unknown);
		ascii.push_back(size());
		
		for (int i = 0; i < size(); ++i) {
			VectorMapEntry<uint8, uint16>* entry = SortedVector<VectorMapEntry<uint8, uint16>*>::get(i);
			
			ascii.push_back(entry->getKey());
			
			if (entry->getValue() > 0xFF) {
				ascii.push_back(0xFF);
				ascii.push_back(entry->getValue() >> 8);
			} else
				ascii.push_back(entry->getValue());
		}
		
		ascii.push_back(0xFF);
		ascii.push_back(0x03);
	}
	
};

#endif /*CUSTOMIZATIONVARIABLES_H_*/
