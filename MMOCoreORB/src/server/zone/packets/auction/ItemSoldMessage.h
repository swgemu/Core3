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

#ifndef ITEMSOLDMESSAGE_H_
#define ITEMSOLDMESSAGE_H_

/*
 * Status codes
 * 0  - Sale succeeded
 * 1  - Auctioner is invalid
 * 2  - Invalid item 
 * 3  - Vendor is malfunctioning
 * 4  - Must specify a valid sale price
 * 5  - Invalid sale Duration 
 * 6  - Already for sale
 * 7  - Unknown error
 * 8  - Do not own
 * 9  - Not enough credits (5)
 * 10 - Unknown error
 * 11 - Unknown error
 * 12 - Unknown error
 * 13 - Too many items
 * 14 - Over 20,000 credits
*/

class ItemSoldMessage : public BaseMessage {

public:

	const static int SUCCESS = 0;
	const static int INVALIDAUCTIONER = 1;
	const static int INVALIDITEM = 2;
	const static int VENDORNOTWORKING = 3;
	const static int INVALIDSALEPRICE = 4;
	const static int INVALIDSALEDURATION = 5;
	const static int ALREADYFORSALE = 6;
	const static int UNKNOWNERROR = 7;
	const static int NOTOWN = 8;
	const static int NOTENOUGHCREDITS = 9;
	const static int TOOMANYITEMS = 13;
	const static int OVER20000 = 14;

public:
	ItemSoldMessage(uint64 objectid, int status) {
		insertShort(3);
		insertInt(0x0E61CC92);
		
		insertLong(objectid);
		insertInt(status); 
	}
};

#endif /*ITEMSOLDMESSAGE_H_*/
