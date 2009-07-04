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

#ifndef CAMOKITIMPLEMENTATION_H_
#define CAMOKITIMPLEMENTATION_H_

#include "CamoKit.h"
#include "../../player/Player.h"

class CamoKitImplementation: public CamoKitServant {
protected:
	/*
	 * The planet
	 */
	uint32 planet;

	/*
	 * The uses
	 */
	uint32 usesRemaining;

	/*
	 * The minimum skill requirement.
	 */
	uint32 concealMin;
public:

	/*
	 * Constructor. Like the other item constructors.
	 */
	CamoKitImplementation(unsigned long long oid, unsigned int tempCRC, const UnicodeString& n, const String& tempn);

	/*
	 * Constructor. Like the other item constructors.
	 */
	CamoKitImplementation(Player* player, unsigned int tempCRC, const UnicodeString& n, const String& tempn);

	/*
	 * Initializies the Planet and Conceal Minimum
	 */
	void init();

	/*
	 * Updates the crafting values
	 * \param DraftSchematic - Schematic of item being crafting
	 */
	void updateCraftingValues(DraftSchematic* draftSchematic);

	/*
	 * Uses a charge oh the camo kit. If 0 uses are left, it is removed from the inventory.
	 * \param player The player that uses the camo kit.
	 */
	void useCharge(Player* player);

	/*
	 * Returns the planet on which the camo kit can be used
	 * \return The planet.
	 */
	int getPlanet();

	/*
	 * Returns the remaining uses.
	 * \return The uses.
	 */
	int getUsesRemaining();

	/* Retruns the conceal skill needed to use this camo kit.
	 * \return The minimum skill requirement.
	 */
	int getConcealMin();

	/*
	 * Sets the planet on which the camo kit can be used
	 * \param tp The planet.
	 */
	void setPlanet(const int tp);

	/*
	 * Sets the remaining uses.
	 * \param us The uses.
	 */
	void setUsesRemaining(const int us);

	/*
	 * Sets the conceal skill needed to use this camo kit.
	 * \param min The minimum skill requirement.
	 */
	void setConcealMin(const int min);

	/*
	 * Removes the camo kit from the inventory.
	 * \param player The player.
	 */
	void remove(Player* player);

	/*
	 * Sends camo kits uses to the player.
	 * \param player The player.
	 */
	void sendDeltas(Player* player);

	/*
	 * Generates the camo kit Attributes and sends them to obj.
	 * \param obj The player.
	 */
	void generateAttributes(SceneObject* obj);

	/*
	 * Used in generateAttributes() to generate Attributes.
	 * \param alm The AttributeListMessage that is filled with attributes.
	 */
	void addHeaderAttributes(AttributeListMessage* alm);

	/*
	 * Used in generateAttributes() to generate Attributes.
	 * \param alm The AttributeListMessage that is filled with attributes.
	 */
	void addFooterAttributes(AttributeListMessage* alm);

	/*
	 * Used in generateAttributes() to generate Attributes.
	 * \param alm The AttributeListMessage that is filled with attributes.
	 */
	void addAttributes(AttributeListMessage* alm);

	/*
	 * Parses the camo kits attributes.
	 */
	void parseItemAttributes();
};

#endif /* CAMOKITIMPLEMENTATION2_H_ */
