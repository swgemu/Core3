local ObjectManager = require("managers.object.object_manager")

HeroOfTatooineScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	courageSpawns = { { -861, 4557 }, { -159, 5040 }, { -1264, 5379 }, { -695, 4506 }, { 16, 4068 }, { -533, 4314 }, { -1023, 5214 }, { -318, 4477 }, { -443, 4970 },
		{ -1183, 4647 }, { -575, 4985 }, { -1618, 5272 }, { -97, 5025 }, { -471, 4715 }, { -991, 5887 }, { -998, 5240 }, { -500, 4600 }, { -1131, 6185 } },

	eventChangeTime = getRandomNumber(20, 30) * 60 * 1000 -- 20-30 minutes
}

registerScreenPlay("HeroOfTatooineScreenPlay", true)

function HeroOfTatooineScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:initEvents()
	end
end

function HeroOfTatooineScreenPlay:spawnMobiles()
	local pHermit = spawnMobile("tatooine", "hermit_quest",0,36.5,-69,-103.7,0,7125586)
	writeData("hero_of_tat:hermit_id", SceneObject(pHermit):getObjectID())
end

function HeroOfTatooineScreenPlay:initEvents()
	if (not hasServerEvent("HeroOfTatCourage")) then
		self:createCourageEvent()
	end
end

function HeroOfTatooineScreenPlay:createCourageEvent()
	local eventID = createServerEvent(self.eventChangeTime, "HeroOfTatooineScreenPlay", "doCourageChange", "HeroOfTatCourage")
end

function HeroOfTatooineScreenPlay:doCourageChange()
	local hermitId = readData("hero_of_tat:hermit_id")
	local pHermit = getSceneObject(hermitId)

	if (pHermit == nil) then
		printf("Error in HeroOfTatooineScreenPlay, unable to find hermit object.\n")
		return 0
	end

	local mobId = readData("hero_of_tat:courage_mob_id")
	local mobLoc = readData("hero_of_tat:courage_mob_loc")
	local pCourageMob

	if (mobId ~= 0) then
		pCourageMob = getSceneObject(mobId)
	end

	-- Reschedule respawn if boar is in combat or dead
	if (pCourageMob ~= nil and (AiAgent(pCourageMob):isInCombat() or CreatureObject(pCourageMob):isDead())) then
		self:createCourageEvent()
		return 0
	elseif (pCourageMob ~= nil) then
		SceneObject(pCourageMob):destroyObjectFromWorld()
	end

	local newLoc = getRandomNumber(1, table.getn(self.courageSpawns))

	if (newLoc == mobLoc) then
		if (newLoc == table.getn(self.courageSpawns)) then
			newLoc = newLoc - 1
		else
			newLoc = newLoc + 1
		end
	end

	writeData("hero_of_tat:courage_mob_loc", newLoc)

	local z = getTerrainHeight(pHermit, self.courageSpawns[newLoc][1], self.courageSpawns[newLoc][2])
	local pBoar = spawnMobile("tatooine", "wild_bladeback_boar", 0, self.courageSpawns[newLoc][1], z, self.courageSpawns[newLoc][2], getRandomNumber(360) - 180, 0)

	if (pBoar ~= nil) then
		createObserver(OBJECTDESTRUCTION, "HeroOfTatooineScreenPlay", "notifyDefeatedBoar", pBoar)
		writeData("hero_of_tat:courage_mob_id", SceneObject(pBoar):getObjectID())
	else
		printf("Error in HeroOfTatooineScreenPlay:doCourageChange, unable to spawn boar.\n")
	end

	self:createCourageEvent()
end

function HeroOfTatooineScreenPlay:notifyDefeatedBoar(pVictim, pAttacker)
	if (CreatureObject(pAttacker):hasScreenPlayState(2, "hero_of_tatooine") ~= 1 or CreatureObject(pAttacker):hasScreenPlayState(16, "hero_of_tatooine") == 1) then
		if (CreatureObject(pAttacker):hasScreenPlayState(16, "hero_of_tatooine") == 1) then
			CreatureObject(pAttacker):sendSystemMessage("@quest/hero_of_tatooine/system_messages:courage_already_have_mark")
		end
		self:clearInventory(pVictim)		
		return 0
	end

	local pInventory = CreatureObject(pVictim):getSlottedObject("inventory")

	if pInventory == nil then
		return 0
	end
	
	if (SceneObject(pInventory):getContainerObjectsSize() > 0) then
		local pItem = SceneObject(pInventory):getContainerObject(0)

		if pItem ~= nil then
			local item = SceneObject(pItem)
			createObserver(ITEMLOOTED, "HeroOfTatooineScreenPlay", "notifyMarkOfCourageLooted", pItem)
		end
		CreatureObject(pAttacker):sendSystemMessage("@quest/hero_of_tatooine/system_messages:courage_notice_object")
	end
end

function HeroOfTatooineScreenPlay:clearInventory(pCreature)
	ObjectManager.withCreatureObject(pCreature, function(creature)
		local pInventory = creature:getSlottedObject("inventory")

		if pInventory == nil then
			return 0
		end
		ObjectManager.withSceneObject(pInventory, function(inventory)
			local numberOfItems = inventory:getContainerObjectsSize()
			for i = 0, numberOfItems - 1, 1 do
				local pItem = inventory:getContainerObject(0)
				SceneObject(pItem):destroyObjectFromWorld()
				SceneObject(pItem):destroyObjectFromDatabase()
			end
		end)
	end)
end

function HeroOfTatooineScreenPlay:notifyMarkOfCourageLooted(pItem, pLooter)
	if pItem == nil or pLooter == nil then
		return 0
	end

	CreatureObject(pLooter):setScreenPlayState(16, "hero_of_tatooine")
end