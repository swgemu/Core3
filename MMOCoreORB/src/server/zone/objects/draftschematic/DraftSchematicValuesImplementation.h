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

#ifndef DRAFTSCHEMATICVALUESIMPLEMENTATION_H_
#define DRAFTSCHEMATICVALUESIMPLEMENTATION_H_


#include "../../packets.h"

#include "DraftSchematicAttribute.h"
#include "DraftSchematicValues.h"
#include "DraftSchematic.h"

class DraftSchematicValuesImplementation : public DraftSchematicValuesServant {

	Vector<string> experimentalPropertyTitles;
	
	VectorMap<string, float> completeCurrentValuesMap;
	Vector<string> valuesToSend;
	
	VectorMap<string, float> currentExperimentalPercentagesMap;
	VectorMap<string, float> maxExperimentalPercentagesMap;
	
public:
	DraftSchematicValuesImplementation() : DraftSchematicValuesServant() {
		
	}
	~DraftSchematicValuesImplementation(){
		
		experimentalPropertyTitles.removeAll();	
		completeCurrentValuesMap.removeAll();	
		valuesToSend.removeAll();		
		currentExperimentalPercentagesMap.removeAll();
		maxExperimentalPercentagesMap.removeAll();
		
	}
	// Experimental Titles
	inline void addExperimentalPropertyTitle(const string& title){
		experimentalPropertyTitles.add(title);
		currentExperimentalPercentagesMap.put(title, 0);
		maxExperimentalPercentagesMap.put(title, 0);
	}
	
	inline string& getExperimentalPropertyTitle(const int i){
		
		return experimentalPropertyTitles.get(i);
		
	}
	
	inline int getExperimentalPropertyTitleSize(){
		
		return experimentalPropertyTitles.size();
		
	}
	
	inline void setCurrentValue(const string& attribute, const float value){
		
		if(completeCurrentValuesMap.contains(attribute)){
			completeCurrentValuesMap.drop(attribute);
		}
		completeCurrentValuesMap.put(attribute, value);
		
	}
	
	int getValuesToSendSize(){
		
		return valuesToSend.size();
		
	}
	
	string& getValuesToSend(const int i){
		
		return valuesToSend.get(i);
		
	}
	
	float getCurrentValue(const string& attribute){
		
		return completeCurrentValuesMap.get(attribute);
		
	}
	
	float getCurrentValue(const int index){
		
		return completeCurrentValuesMap.get(index);
		
	}
	
	inline void setCurrentPercentage(const string& attribute, const float value){
		
		float max;
		
		if(currentExperimentalPercentagesMap.contains(attribute)){			
			currentExperimentalPercentagesMap.drop(attribute);
		}
		
		max = maxExperimentalPercentagesMap.get(attribute);
		
		if(value > max)	
			currentExperimentalPercentagesMap.put(attribute, max);
		else
			currentExperimentalPercentagesMap.put(attribute, value);
		
	}
	
	float getCurrentPercentage(const string& attribute){
		
		return currentExperimentalPercentagesMap.get(attribute);
		
	}
	float getCurrentPercentage(const int index){
		
		return currentExperimentalPercentagesMap.get(index);
		
	}
	
	inline void setMaxPercentage(const string& attribute, const float value){
		
		if(maxExperimentalPercentagesMap.contains(attribute)){
			maxExperimentalPercentagesMap.drop(attribute);
		}
		maxExperimentalPercentagesMap.put(attribute, value);
		
	}

	float getMaxPercentage(const string& attribute){
		
		return maxExperimentalPercentagesMap.get(attribute);
		
	}
	float getMaxPercentage(const int index){
		
		return maxExperimentalPercentagesMap.get(index);
		
	}
	
	void recalculateValues(DraftSchematic * draftSchematic){
		
		string experimentalPropTitle, attributeName;
		float percentage, min, max, newValue, oldValue;
		DraftSchematicAttribute * attrib;
		
		for(int i = 0; i < draftSchematic->getAttributesToSetListSize(); ++i){
			
			attrib = draftSchematic->getAttributeToSet(i);
			experimentalPropTitle = attrib->getAttributeExperimentalProperty();
			
			attributeName = attrib->getAttributeName();
			min = attrib->getMinValue();
			max = attrib->getMaxValue();
			percentage = getCurrentPercentage(experimentalPropTitle);

			oldValue = completeCurrentValuesMap.get(attributeName);
			
			if(experimentalPropTitle == "null"){
				newValue = max;
			} else {
				newValue = (percentage * (max - min)) + min;
			}

			if (newValue != oldValue) {

				setCurrentValue(attributeName, newValue);
				valuesToSend.add(attributeName);

			}

		}
	}
	
	
	// Clear
	inline void clear(){
		valuesToSend.removeAll();
	}
	
	inline void clearAll(){
		completeCurrentValuesMap.removeAll();	
		valuesToSend.removeAll();		
		currentExperimentalPercentagesMap.removeAll();
		maxExperimentalPercentagesMap.removeAll();
	}
	
	
};

#endif /*DRAFTSCHEMATICVALUESIMPLEMENTATION_H_*/
