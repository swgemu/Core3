BasiliskAnniversary = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "BasiliskAnniversary",

	anniversaryMobiles = {
		--{planet, template, x, z, y, direction, cell}

		--Chef
		{"naboo", "anniversary_grandmaster_baker", 19.0, 1.6, 12.3, 178, 1697378},

		--Information Broker
		{"tatooine", "anniversary_information_broker", 3274, 5, -4904, 37, 0},

		--Rival Chef
		{"corellia", "anniversary_disaster_of_desserts", 20.1, 1.6, 12.3, 177, 1855549},

	},

	anniversaryDecorationObjects = {
		--{planet, template, x, z, y, cell, direction}

		--Rival Chef
		{"corellia", "object/tangible/furniture/all/frn_all_light_lamp_free_s02.iff", 26.7, 1.3, 4.5, 1855549, 88},
		{"corellia", "object/tangible/furniture/all/frn_all_light_lamp_free_s02.iff", 13.7, 1.3, 10.6, 1855549, -47},
		{"corellia", "object/tangible/furniture/all/frn_all_light_lamp_free_s02.iff", 12.6, 1.3, -18.4, 1855549, -144},
		{"corellia", "object/tangible/furniture/all/frn_all_light_lamp_free_s02.iff", 23.2, 1.6, 15.3, 1855549, 17},
		{"corellia", "object/tangible/furniture/all/frn_all_potted_plants_sml_s05.iff", 13.7, 1.3, 4.7, 1855549, -91},
		{"corellia", "object/tangible/furniture/all/frn_all_potted_plants_sml_s05.iff", 13.7, 1.3, -4.7, 1855549, -134},
		{"corellia", "object/tangible/furniture/decorative/foodcart.iff", 19.0, 1.6, 13.9, 1855549, -106},
		{"corellia", "object/tangible/furniture/all/frn_all_tree_potted_s2.iff", 9.7, 1.0, -3.2, 1855549, 101},
		{"corellia", "object/tangible/furniture/all/frn_all_tree_potted_s2.iff", 9.7, 1.0, 3.1, 1855549, -32},
		{"corellia", "object/tangible/painting/painting_food_baking_s01.iff", 20.76, 3.6, 15.72, 1855549, -90},

	}
}

registerScreenPlay("BasiliskAnniversary", true)

function BasiliskAnniversary:start()
	self:spawnMobiles()
	self:spawnDecorationObjects()

	createEvent(7 * 24 * 60 * 60 * 1000, "BasiliskAnniversary", "despawnEvent", nil, "")
end

function BasiliskAnniversary:spawnMobiles()
	local mobileTable = self.anniversaryMobiles

	for i = 1, #mobileTable, 1 do
		local mobile = mobileTable[i]

		if isZoneEnabled(mobile[1]) then
			--{planet, template, timer, x, z, y, direction, cell}
			local pMobile = spawnMobile(mobile[1], mobile[2], -1, mobile[3], mobile[4], mobile[5], mobile[6], mobile[7])

			if (pMobile ~= nil) then
				local pOid = SceneObject(pMobile):getObjectID()

				if mobile[2] == "anniversary_disaster_of_desserts" then
					createObserver(CREATUREDESPAWNED, "BasiliskAnniversary", "onDespawn", pMobile)
				else
					CreatureObject(pMobile):setPvpStatusBitmask(0)
				end

				writeData(i .. ":anniversaryMob", pOid)
			end
		end
	end
end

function BasiliskAnniversary:spawnDecorationObjects()
	local decoTable = self.anniversaryDecorationObjects

	for i = 1, #decoTable, 1 do
		local sceneObject = decoTable[i]

		if isZoneEnabled(sceneObject[1]) then
			--{planet, template, x, z, y, cell, direction}
			local pScno = spawnSceneObject(sceneObject[1], sceneObject[2], sceneObject[3], sceneObject[4], sceneObject[5], sceneObject[6], math.rad(sceneObject[7]))

			if pScno ~= nil then
				local pScnoOid = SceneObject(pScno):getObjectID()

				writeData(i .. ":anniversaryDeco", pScnoOid)
			end
		end
	end
end

function BasiliskAnniversary:onDespawn(pMobile)
	if pMobile == nil or not SceneObject(pMobile):isAiAgent() then
		return
	end

	createEvent(60 * 1000, "BasiliskAnniversary", "respawn", nil, 3)
	deleteData(3 .. ":anniversaryMob")

	return 1
end

function BasiliskAnniversary:respawn(pMobile, spawnNumber)
	local mobiles = self.anniversaryMobiles
	local npc = mobiles[3]

	local pMob = spawnMobile(npc[1], npc[2], -1, npc[3], npc[4], npc[5], npc[6], npc[7])

	if (pMob ~= nil) then
		local pOid = SceneObject(pMob):getObjectID()

		createObserver(CREATUREDESPAWNED, "BasiliskAnniversary", "onDespawn", pMob)
		writeData(3 .. ":anniversaryMob", pOid)
	end
end


function BasiliskAnniversary:hasCollectionItem(pPlayer)
	if pPlayer == nil then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return false
	end

	local template = "object/tangible/food/foraged/edible_jar_berries.iff"

	local pInvItem = getContainerObjectByTemplate(pInventory, template, true)

	if pInvItem ~= nil then
		return true
	end

	return false
end

function BasiliskAnniversary:setQuestStatus(pPlayer, quest, status)
	if pPlayer == nil then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local string = quest
	local questStatus = status

	if (playerID ~= nil) then
		setQuestStatus(playerID .. string, status)
	end
end

function BasiliskAnniversary:cleanUp(pPlayer)
	if pPlayer == nil then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (playerID ~= nil) then
		removeQuestStatus(playerID .. ":anniversaryWPID_3")
	end
end

function BasiliskAnniversary:grantReward(pPlayer)
	if pPlayer == nil then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pInventory == nil then
		return
	end

	PlayerObject(pGhost):awardBadge(124) --Live Event Badge

	local pReward = giveItem(pInventory, "object/tangible/food/crafted/dessert_air_cake.iff", -1)

	if pReward ~= nil then
		SceneObject(pReward):setCustomObjectName("2021 - Spectacular Basilisk 9th Anniversary Cake")
	end
end

function BasiliskAnniversary:despawnEvent(pMobile, args)
	local mobiles = self.anniversaryMobiles

	for  i = 1, #mobiles, 1 do
		local pMobID = readData(i .. ":anniversaryMob")
		local despawnMob = getSceneObject(pMobID)

		if despawnMob ~= nil then
			if i == 3 then
				dropObserver(CREATUREDESPAWNED, "BasiliskAnniversary", "onDespawn", despawnMob)
			end

			SceneObject(despawnMob):destroyObjectFromWorld()
			deleteData(i .. ":anniversaryMob")
		end
	end

	local decor = self.anniversaryDecorationObjects

	for j = 1, #decor, 1 do
		local pObID = readData(j .. ":anniversaryDeco")
		local pObject = getSceneObject(pObID)

		if pObject ~= nil then
			SceneObject(pObject):destroyObjectFromWorld()
			deleteData(j .. ":anniversaryDeco")
		end
	end

	printf("Basilisk Anniversary Event -- Despawn Complete \n")
end