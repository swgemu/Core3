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

#ifndef FORAGEITEMLIST_H_
#define FORAGEITEMLIST_H_

#include "engine/engine.h"

#include "../../objects/tangible/TangibleObject.h"

class ForageItemList {

protected:

	Vector<TangibleObject*> basicForageItems; //forageGroup1
	Vector<TangibleObject*> rareForageItems; //forageGroup2
	Vector<TangibleObject*> medicalForageFood; //forageGroup3
	Vector<TangibleObject*> basicForageComponents; //forageGroup4
	Vector<TangibleObject*> advancedForageComponents; //forageGroup5
	Vector<TangibleObject*> exceptionalForageComponents; //forageGroup6

public:

	ForageItemList() {

	}

    bool add(TangibleObject* item, int foragegroup) {
    	switch (foragegroup) {
    	case 1:
    		basicForageItems.add(item);
    		break;

    	case 2:
    		rareForageItems.add(item);
    		break;

    	case 3:
    		medicalForageFood.add(item);
    		break;

    	case 4:
    		basicForageComponents.add(item);
    		break;

    	case 5:
    		advancedForageComponents.add(item);
    		break;

    	case 6:
    		exceptionalForageComponents.add(item);
    		break;

    	default:
    		basicForageItems.add(item);
    		break;
    	}

    	return true;
    }

    TangibleObject* get(int foragegroup) {
    	TangibleObject* item;

       	switch (foragegroup) {
        case 1:
        	item = basicForageItems.get(System::random(basicForageItems.size() - 1));
        	return item;

        case 2:
        	item = rareForageItems.get(System::random(rareForageItems.size() - 1));
        	return item;

        case 3:
        	item = medicalForageFood.get(System::random(medicalForageFood.size() - 1));
        	return item;

        case 4:
        	item = basicForageComponents.get(System::random(basicForageComponents.size() - 1));
        	return item;

        case 5:
        	item = advancedForageComponents.get(System::random(advancedForageComponents.size() - 1));
        	return item;

        case 6:
        	item = exceptionalForageComponents.get(System::random(exceptionalForageComponents.size() - 1));
        	return item;

        default:
        	item = basicForageItems.get(System::random(basicForageItems.size() - 1));
        	return item;
        }
    }
};

#endif /*FORAGEITEMLIST_H_*/
