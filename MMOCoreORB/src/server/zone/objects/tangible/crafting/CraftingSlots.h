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

#ifndef CRAFTINGSLOTS_H_
#define CRAFTINGSLOTS_H_


class CraftingSlots {

	Vector<TangibleObject*> objects;
	
public:
	CraftingSlots(){
		
	}
	~CraftingSlots(){
	
		cleanup();
		
	}
	
	inline void init(const int size){
		
		cleanup();
		
		TangibleObject* tano = NULL;
		
		for(int i = 0; i < size; ++i){
			
			objects.add(tano);
			
		}
	}
	
	inline void cleanup(){
		
		TangibleObject* tano;
		
		for(int i = 0; i < objects.size(); ++i){
			
			tano = objects.get(i);
			
			if(tano != NULL){
				
				tano->setContainer(NULL);
				tano->finalize();
				
			}
			
			tano = NULL;
			
		}
		
		objects.removeAll();
		
	}
	
	inline int size(){
		
		return objects.size();
		
	}
	
	inline void setIngredientInSlot(int slot, TangibleObject* tano){
		
		objects.set(slot, tano);
		
	}
	
	inline void clearIngredientInSlot(int slot){
		
		objects.set(slot, NULL);
		
	}
	
	inline TangibleObject* getIngredientInSlot(int slot){
		
		return objects.get(slot);
		
	}
	
	void toString(){
		
		TangibleObject* tano;
		for(int i = 0;i < objects.size(); ++i){
			
			tano = objects.get(i);
			
			cout << "Slot " << i << " *******************" << endl;
			
			if(tano == NULL){
				
				cout << "Slot is NULL" << endl;

			} else {
				
				cout << "Name: " << tano->getName().c_str() << endl;
				
				if(tano->isResource()){
				
					cout << "Quantity: " << ((ResourceContainer*)tano)->getContents() << endl;
					
				} else {
					
					cout << "Quantity: " << tano->getObjectCount() << endl;
					
				}

			}
	
		}
		
	}

};
#endif /*CRAFTINGSLOTS_H_*/
