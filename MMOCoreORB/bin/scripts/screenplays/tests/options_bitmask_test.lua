options_bitmask_test = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("options_bitmask_test", true)

function options_bitmask_test:start()
	if (not isZoneEnabled("simple")) then
		return 0
	end
	
	local pActiveArea1 = spawnActiveArea("simple", "object/active_area.iff", 0, 0, 0, 200, 0)

	if (pActiveArea1 ~= nil) then
		createObserver(ENTEREDAREA, "options_bitmask_test", "notifyEnteredArea1", pActiveArea1)
	end

	for i = -1, 32, 1 do
		local pMobile = spawnMobile("simple", "dolac_legasi", 0, i, 0, 0, 0, 0)
		local mobile = LuaCreatureObject(pMobile)
		
		if (i == -1) then
			mobile:setOptionsBitmask(4224)
		else
			mobile:setOptionsBitmask(2^i)
		end
	end
	
	for i = -1, 32, 1 do
		local pTangible = spawnSceneObject("simple", "object/tangible/gravestone/gravestone01.iff", i * 3, 0, 5, 0, 1, 0, 0, 0)
		local tangible = LuaTangibleObject(pTangible)
		
		if (i == -1) then
			tangible:setOptionsBitmask(0)
		else
			tangible:setOptionsBitmask(2^i)
		end
	end
	
	return 0
end

function options_bitmask_test:notifyEnteredArea1(pActiveArea, pMovingObject)
	if (pMovingObject == nil) then
		return 0
	end
	
	local movingObject = LuaSceneObject(pMovingObject)
	
	local pInventory = movingObject:getSlottedObject("inventory")
	
	for i = -1, 32, 1 do
		local pTangible = giveItem(pInventory, "object/tangible/jedi/jedi_holocron_dark.iff", -1)
		
		if (pTangible == nil) then
			printf("tangible is nil\n")
			return 0
		end
		
		local tangible = LuaTangibleObject(pTangible)
		
		if (i == -1) then
			tangible:setOptionsBitmask(0)
		else
			tangible:setOptionsBitmask(2^i)
		end
	end

	return 0
end
