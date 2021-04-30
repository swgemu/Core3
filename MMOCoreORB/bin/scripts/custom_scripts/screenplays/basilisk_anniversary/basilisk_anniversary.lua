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
		{"corellia", "object/tangible/furniture/all/frn_all_light_lamp_free_s02.iff", -472.6, 29.2, -4659.2, 0, 0},
		{"corellia", "object/tangible/furniture/all/frn_all_light_lamp_free_s02.iff", -466.4, 29.2, -4646.2, 0, 0},
		{"corellia", "object/tangible/furniture/all/frn_all_light_lamp_free_s02.iff", -457.4, 29.3, -2659.3, 0, 179},
		{"corellia", "object/tangible/furniture/all/frn_all_potted_plants_sml_s05.iff", -465.1, 29.0, -4661.7, 0, -133},
		{"corellia", "object/tangible/furniture/all/frn_all_potted_plants_sml_s05.iff", -458.8, 29.0, -4661.7, 0, 125},
		{"corellia", "object/tangible/furniture/decorative/foodcart.iff", -476.2, 29.6, -4654.4, 0, 145},
		{"corellia", "object/tangible/furniture/decorative/fruit_assorted.iff", -473.4, 30.6, -4652.8, 0, 90},
		{"corellia", "object/tangible/furniture/decorative/kitchen_utensils.iff", -473.5, 30.6, -4650.5, 0, 90},
		{"corellia", "object/tangible/furniture/decorative/stuffed_fish.iff", -473.3, 30.6, -4653.1, 0, 129},
		{"corellia", "object/tangible/furniture/decorative/portable_stove.iff", -473.4, 30.6, -4655.5, 0, 115},
		{"corellia", "object/tangible/furniture/decorative/bottle_fat.iff", -473.5, 30.6, -4654.5, 0, 87},

	}
}

registerScreenPlay("BasiliskAnniversary", true)

function BasiliskAnniversary:start()
	self:spawnMobiles()
	self:spawnDecorationObjects()
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

	--createEvent(60 * 1000, "BasiliskAnniversary", "despawnEvent", nil, "")
	-- 7 * 24 * 60 * 60 * 1000
end

function BasiliskAnniversary:spawnDecorationObjects()
	local decoTable = self.anniversaryDecorationObjects

	for i = 1, #decoTable, 1 do
		local sceneObject = decoTable[i]

		if isZoneEnabled(sceneObject[1]) then
			--{planet, template, x, z, y, cell, direction}
			local pScno = spawnSceneObject(sceneObject[1], sceneObject[2], sceneObject[3], sceneObject[4], sceneObject[5], sceneObject[6], math.rad(sceneObject[7]))

			if pScno ~= nil then
				local pOid = SceneObject(pScno):getObjectID()

				writeData(i .. ":anniversaryDeco", pOid)
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
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return false
	end

	local template = "object/tangible/food/foraged/shared_edible_jar_berries.iff"

	local pInvItem = getContainerObjectByTemplate(pInventory, templates, true)

	if pInvItem ~= nil then
		return true
	end
end

function BasiliskAnniversary:setQuestStatus(pPlayer, quest, status)
	local playerID = SceneObject(pPlayer):getObjectID()
	local string = quest
	local questStatus = status

	if (playerID ~= nil) then
		setQuestStatus(playerID .. string, status)
	end
end

function BasiliskAnniversary:cleanUp(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	if (playerID ~= nil) then
		removeQuestStatus(playerID .. ":anniversaryWpID_2")
		removeQuestSTatus(playerID .. ":anniversaryWPID_3")
	end
end

function BasiliskAnniversary:grantReward(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil or pInventory == nil then
		return
	end

	PlayerObject(pGhost):awardBadge(124) --Live Event Badge

	local pReward = giveItem(pInventory, "object/tangible/food/crafted/dessert_air_cake.iff", -1)

	if pReward ~= nil then
		SceneObject(pReward):setCustomObjectName("2021 - Spectacular Basilisk 9th Anniversary Cake")
	end
end

function BasiliskAnniversary:despawnEvent(pMobile, args)
	--To Do: depawnMobiles, depsawnDeco

	printf(" despawnEvent called!! \n")

	local mobiles = self.anniversaryMobiles

	for  i = 1, #mobiles, 1 do
		printf("Despawning mob \n")


		local pMobID = readData(i .. ":anniversaryMob")
		local despawbMob = getSceneObject(pMobID)

		if despawnMob ~= nil then
			printf("Despawning mob ~= nil \n")

			if i == 3 then
				dropObserver(CREATUREDESPAWNED, "BasiliskAnniversary", "onDespawn", despawnMob)
			end

			SceneObject(despawnMob):destroyObjectFromWorld()
			deleteData(i .. ":anniversaryMob")
		end
	end

	local decor = self.anniversaryDecorationObjects

	for j = 1, #decor, 1 do
		printf("Despawning decoration \n")

		local pOid = readData(j .. ":anniversayDeco")
		local pObject = getSceneObject(pOid)

		if pObject ~= nil then
			SceneObject(pObject):destroyObjectFromWorld()
			deleteData(j .. ":anniversaryDeco")
		end
	end

end