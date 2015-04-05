
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

#ifndef INGREDIENTSLOT_H_
#define INGREDIENTSLOT_H_

#include "server/zone/objects/tangible/TangibleObject.h"

class IngredientSlot : public Serializable, public Logger {

protected:

	String slotName;
	String contentType;

	int requiredQuantity;

	bool identical;
	bool optional;

	short clientSlotType;

public:

	enum {
		RESOURCESLOT,
		IDENTICALSLOT,
		MIXEDSLOT,
		OPTIONALIDENTICALSLOT,
		OPTIONALMIXEDSLOT
	};

	// Crafting error messages
	enum {
		OK                       = 0x00,
		NOSERVER                 = 0x01, // No server for Owner
		NOTASSEMBLYSTAGE         = 0x02, // Not in crafting assembly stage
		NOTCUSTOMIZATIONSTAGE    = 0x03, // Not in crafting customization stage
		NOSCHEMATIC              = 0x04, // No Draft Schematic Found
		NOTOOL                   = 0x05, // No Crafting tool Found
		NOMANUFACTURE            = 0x06, // No manufacturing schematic found
		INVALID                  = 0x07, // Invalid Slot Chosen
		INVALIDOPTION            = 0x08, // Invalid Slot Option Chosen
		INVALIDINGREDIENTSIZE    = 0x09, // Invalid ingredient size for slot
		FULL                     = 0x0A, // Slot Full
		INVALIDINGREDIENT        = 0x0B, // Invalid Ingredient
		INGREDIENTNOTININVENTORY = 0x0C, // Ingredient not in inventory
		BADCRATE                 = 0x0D, // Cannot remove resource from crate
		BADRESOURCEFOR           = 0x0E, // Bad resource for Slot
		COMPONENTDAMAGED         = 0x0F, // Component too damaged for use
		NOCOMPONENTTRANSFER      = 0x10, // Cannot transfer componenet
		BADCOMPONENT             = 0x11, // Bad component for slot
		NOINVENTORY              = 0x12, // Inventory Missing
		BADSTATIONHOPPER         = 0x13, // Bad station Hopper
		BADTARGETCONTAINER       = 0x14, // Bad target container
		EMPTYISEMPTY             = 0x15, // Empty slot is empty
		FAILEDRESOURCECREATE     = 0x16, // Cannot create resource container
		EMPTYASSEMBLE            = 0x17, // Trying to assemble with empty slot
		PARTIALASSEMBLE          = 0x18, // Trying to assemble with patially full slot
		PROTOTYPENOTFOUND        = 0x19, // Prototype not found
		BADNAME                  = 0x1A, // Rename object and resend
		MYSTERY                  = 0x1B, // Didn't read this one
		FAILEDTOTRANSFER         = 0x1C, // Failed to transfer resources to station
		WEIRDFAILEDMESSAGE       = 0x1D // Hey nonny nonny tra la la!
	};

public:
	IngredientSlot(){
		requiredQuantity = 0;

		identical = false;
		optional = false;

		clientSlotType = 0;

		setLogging(false);
	}

	IngredientSlot(const IngredientSlot& slot) : Object(), Serializable(), Logger() {
		slotName = slot.slotName;
		requiredQuantity = slot.requiredQuantity;
		identical = slot.identical;
		optional = slot.optional;
		contentType = slot.contentType;

		clientSlotType = slot.clientSlotType;

		setLogging(false);
	}

	~IngredientSlot(){
		//info("Deleting Slot type " + String::valueOf(slottype));
	}

	Object* clone() {
		return ObjectCloner<IngredientSlot>::clone(this);
	}

	Object* clone(void* object) {
		return TransactionalObjectCloner<IngredientSlot>::clone(this);
	}

	int getClientSlotType() {
		return clientSlotType;
	}

	void setOptional(bool value) {
		optional = value;
	}

	bool isOptional() {
		return optional == true;
	}

	void setIdentical(bool value) {
		identical = value;
	}

	bool requiresIdentical() {
		return identical == true;
	}

	void setContentType(const String& value) {
		contentType = value;
	}

	void setQuantityNeeded(int value) {
		requiredQuantity = value;
	}

	int getQuantityNeeded() {
		return requiredQuantity;
	}

	virtual bool add(CreatureObject* player, SceneObject* satchel, ManagedReference<TangibleObject*> tano) {
		return false;
	}

	inline bool removeAll(CreatureObject* player) {
		return returnToParents(player);
	}

	virtual bool returnToParents(CreatureObject* player) {
		return false;
	}

	void setSlotName(const String& name) {
		slotName = name;
	}

	const String& getSlotName() {
		return slotName;
	}

	virtual bool isFull() {
		return false;
	}

	virtual bool isEmpty() {
		return true;
	}

	virtual inline int size() {
		return 0;
	}

	virtual void print(){
	}

	virtual int getSlotQuantity() {
		return -1;
	}

	virtual bool isResourceSlot() {
		return false;
	}

	virtual bool isComponentSlot() {
		return false;
	}


	virtual Vector<uint64> getOIDVector() {
		Vector<uint64> oid;
		return oid;
	}

	virtual Vector<int> getQuantityVector() {
		Vector<int> quantities;
		return quantities;
	}

	virtual SceneObject* getFactoryIngredient() {
		return NULL;
	}


};
#endif /*INGREDIENTSLOT_H_*/
