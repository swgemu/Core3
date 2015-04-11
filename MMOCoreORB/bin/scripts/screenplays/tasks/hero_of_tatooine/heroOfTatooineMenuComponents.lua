local ObjectManager = require("managers.object.object_manager")

squillLairMenuComponent = { }

function squillLairMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, "hero_of_tatooine") and not CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine")) then
		menuResponse:addRadialMenuItem(120, 3, "@quest/hero_of_tatooine/system_messages:search") -- Search
	end
end

function squillLairMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end

	if (not CreatureObject(pPlayer):hasScreenPlayState(1, "hero_of_tatooine") or CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine")) then
		return 0
	end

	return ObjectManager.withCreatureObject(pPlayer, function(creature)
		if (selectedID == 120) then
			if (readData(creature:getObjectID() .. ":hero_of_tat:searched_squill_lair") == 1) then
				creature:sendSystemMessage("@quest/hero_of_tatooine/system_messages:already_search")
				return 0
			end

			local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

			if (pInventory == nil) then
				return 0
			end

			if (SceneObject(pInventory):hasFullContainerObjects()) then
				creature:sendSystemMessage("@quest/hero_of_tatooine/system_messages:inventory")
				return 0
			end

			local pSkull = giveItem(pInventory, "object/tangible/loot/quest/hero_of_tatooine/squill_skull.iff", -1)

			if (pSkull == nil) then
				creature:sendSystemMessage("Error: Unable to generate item.")
				return 0
			end

			creature:sendSystemMessage("@quest/hero_of_tatooine/system_messages:receive")
			writeData(creature:getObjectID() .. ":hero_of_tat:searched_squill_lair", 1)
		end
		return 0
	end)
end

explosivesCrateMenuComponent = { }

function explosivesCrateMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return 0
	end

	if (CreatureObject(pPlayer):hasScreenPlayState(1, "hero_of_tatooine_altruism") and not CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine_altruism") and
		getContainerObjectByTemplate(pInventory, "object/tangible/item/quest/hero_of_tatooine/explosives.iff", true) == nil) then
		menuResponse:addRadialMenuItem(120, 3, "@quest/hero_of_tatooine/system_messages:search") -- Search
	end
end

function explosivesCrateMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end

	if (not CreatureObject(pPlayer):hasScreenPlayState(1, "hero_of_tatooine_altruism") or CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine_altruism")) then
		return 0
	end

	return ObjectManager.withCreatureObject(pPlayer, function(creature)
		if (selectedID == 120) then
			local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

			if (pInventory == nil) then
				return 0
			end

			if (SceneObject(pInventory):hasFullContainerObjects()) then
				creature:sendSystemMessage("@quest/hero_of_tatooine/system_messages:altruism_inventory_full")
				return 0
			end

			local pExplosives = giveItem(pInventory, "object/tangible/item/quest/hero_of_tatooine/explosives.iff", -1)

			if (pExplosives == nil) then
				creature:sendSystemMessage("@quest/hero_of_tatooine/system_messages:altruism_null_object")
				return 0
			end

			creature:sendSystemMessage("@quest/hero_of_tatooine/system_messages:altruism_got_object")
			SceneObject(pObject):destroyObjectFromWorld()
		end
		return 0
	end)
end