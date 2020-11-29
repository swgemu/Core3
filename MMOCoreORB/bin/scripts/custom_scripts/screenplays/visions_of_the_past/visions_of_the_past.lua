VisionsOfThePast = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "VisionsOfThePast",

	lootRespawnTime = 2 * 60 * 1000 -- 2 minutes

}

registerScreenPlay("VisionsOfThePast", true)

function VisionsOfThePast:start()
	self:spawnMobiles()
	self:spawnCollectionObjects()
	self:spawnDecorationObjects()
end

function VisionsOfThePast:spawnMobiles()
	local mobileTable = visionsMobiles

	for i = 1, #mobileTable, 1 do
		local mobile = mobileTable[i]

		if isZoneEnabled(mobile[1]) then
			--{planet, template, timer, x, z, y, direction, cell}
			local pMobile = spawnMobile(mobile[1], mobile[2], -1, mobile[3], mobile[4], mobile[5], math.rad(mobile[6]), 0)

			if (pMobile ~= nil) then
				CreatureObject(pMobile):setPvpStatusBitmask(0)
			end
		end
	end
end

function VisionsOfThePast:spawnCollectionObjects()
	local scnOTable = visionsCollectionObjects

	for i = 1, #scnOTable, 1 do
		local spawnedSceneObject = LuaSceneObject(nil)
		local sceneObject = scnOTable[i]

		if isZoneEnabled(sceneObject[1]) then
			--{planet, template, x, z, y, cell, direction}
			local pSceneObject = spawnSceneObject(sceneObject[1], sceneObject[2], sceneObject[3], sceneObject[4], sceneObject[5], sceneObject[6], math.rad(sceneObject[7]))

			if (pSceneObject ~= nil) then
				spawnedSceneObject:_setObject(pSceneObject)
				SceneObject(pSceneObject):setCustomObjectName("Deathstar Debris")
				self:setLootBoxPermissions(pSceneObject)
				writeData(spawnedSceneObject:getObjectID() .. ":visions:wreckage:", i)
				createEvent(1000, "VisionsOfThePast", "spawnCollectionItems", pSceneObject, "")
				createObserver(OBJECTRADIALUSED, "VisionsOfThePast", "itemLooted", pSceneObject)
			end
		end
	end
end

function VisionsOfThePast:spawnDecorationObjects()
	local decoTable = visionsDecorationObjects

	for i = 1, #decoTable, 1 do
		local sceneObject = decoTable[i]
		
		if isZoneEnabled(sceneObject[1]) then
			--{planet, template, x, z, y, cell, direction}
			spawnSceneObject(sceneObject[1], sceneObject[2], sceneObject[3], sceneObject[4], sceneObject[5], sceneObject[6], math.rad(sceneObject[7]))
		end
	end
end

function VisionsOfThePast:setLootBoxPermissions(pContainer)
	SceneObject(pContainer):setContainerInheritPermissionsFromParent(false)
	SceneObject(pContainer):setContainerDefaultDenyPermission(MOVEIN)
	SceneObject(pContainer):setContainerDefaultAllowPermission(OPEN + MOVEOUT)
end

function VisionsOfThePast:spawnCollectionItems(pSceneObject)
	if (pSceneObject == nil) then
		return
	end

	if (SceneObject(pSceneObject):getContainerObjectsSize() == 0) then
		deleteData(SceneObject(pSceneObject):getObjectID() .. ":visions:wreckage:")

		createLoot(pSceneObject, "visions_quest_loot_group", 1, false)
		if getRandomNumber(100) > 75 then
			createLoot(pSceneObject, "visions_quest_loot_group", 1, false)
		end
	end
end

function VisionsOfThePast:itemLooted(pSceneObject, pCreature, radialID)
	if (radialID ~= 16) then
		return 0
	end
	
	if objectId ~= nil then
		if readData(objectID .. ":visions:spawned:") ~= 1 then
			local boxId = readData(objectID .. ":visions:wreckage:")
			writeData(objectID .. ":visions:spawned:", 1)

			createEvent(self.lootRespawnTime, "VisionsOfThePast", "spawnCollectionItems", pSceneObject, "")
		end
	end
	return 0
end

function VisionsOfThePast:hasCollectionItem(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return false
	end

	local templates = {
		"object/tangible/mission/quest_item/singular_nak_q2_needed.iff",
		"object/tangible/theme_park/alderaan/act2/decoder_comp_screen.iff"
	}
	

	for i = 1, #templates, 1 do
		local pInvItem = getContainerObjectByTemplate(pInventory, templates[i], true)

		if pInvItem ~= nil then
			return true
		end
	end

	return false
end
