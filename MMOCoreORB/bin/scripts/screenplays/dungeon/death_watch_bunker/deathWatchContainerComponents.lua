local ObjectManager = require("managers.object.object_manager")

deathWatchJetpackCraftingDroid = { }

function deathWatchJetpackCraftingDroid:canAddObject(pDroid, pIngredient, slot)
	if pIngredient == nil then
		return false
	end

	if slot ~= -1 then
		return false
	end

	local pParent = DeathWatchBunkerScreenPlay:getObjOwner(pIngredient)

	return ObjectManager.withCreatureObject(pParent, function(creature)
		local template = SceneObject(pIngredient):getTemplateObjectPath()
		local userid = readData(SceneObject(pDroid):getObjectID() .. ":dwb:user")

		if userid ~= 0 and userid ~= creature:getObjectID() then
			creature:sendSystemMessage("@dungeon/death_watch:same_user_only")
			return false
		end

		if creature:hasSkill(DeathWatchBunkerScreenPlay.terminalSkills[8]) == false then
			creature:sendSystemMessage(DeathWatchBunkerScreenPlay.terminalSkillMessage[4])
			return false
		end

		local droidId = SceneObject(pDroid):getObjectID()
		local hasMineral = readData(droidId .. ":dwb:alummineral")
		local hasJetpackBase = readData(droidId .. ":dwb:jetpackbase")
		local hasJetpackStabilizer = readData(droidId .. ":dwb:jetpackstabilizer")
		local hasDuctedFan = readData(droidId .. ":dwb:ductedfan")
		local hasInjectorTank = readData(droidId .. ":dwb:injectortank")
		local hasDispersionUnit = readData(droidId .. ":dwb:dispersionunit")

		if template == DeathWatchBunkerScreenPlay.bunkerItems.jetPackBase then
			if hasJetpackBase == 0 then
				return true
			else
				creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
			end
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.jetPackStabilizer then
			if hasJetpackStabilizer == 0 then
				return true
			else
				creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
			end
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.ductedFan then
			if hasDuctedFan == 0 then
				return true
			else
				creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
			end
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.injectorTank then
			if hasInjectorTank == 0 then
				return true
			else
				creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
			end
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.dispersionUnit then
			if hasDispersionUnit == 0 then
				return true
			else
				creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
			end
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.alumMineral then
			if hasMineral == 0 then
				return true
			else
				creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
			end
		end
		return false
	end)
end

function deathWatchJetpackCraftingDroid:transferObject(pDroid, pIngredient, slot)
	if (pIngredient == nil) then
		return 0
	end

	if slot ~= -1 then
		return 0
	end

	local pParent = DeathWatchBunkerScreenPlay:getObjOwner(pIngredient)

	ObjectManager.withSceneObject(pDroid, function(terminal)
		local template = SceneObject(pIngredient):getTemplateObjectPath()

		local terminalId = terminal:getObjectID()

		if template == DeathWatchBunkerScreenPlay.bunkerItems.jetPackBase then
			writeData(terminalId .. ":dwb:jetpackbase", 1)
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.jetPackStabilizer then
			writeData(terminalId .. ":dwb:jetpackstabilizer", 1)
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.ductedFan then
			writeData(terminalId .. ":dwb:ductedfan", 1)
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.injectorTank then
			writeData(terminalId .. ":dwb:injectortank", 1)
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.dispersionUnit then
			writeData(terminalId .. ":dwb:dispersionunit", 1)
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.alumMineral then
			writeData(terminalId .. ":dwb:alummineral", 1)
		end

		createEvent(100, "DeathWatchBunkerScreenPlay", "destroyIngredient", pIngredient)

		local hasMineral = readData(terminalId .. ":dwb:alummineral")
		local hasJetpackBase = readData(terminalId .. ":dwb:jetpackbase")
		local hasJetpackStabilizer = readData(terminalId .. ":dwb:jetpackstabilizer")
		local hasDuctedFan = readData(terminalId .. ":dwb:ductedfan")
		local hasInjectorTank = readData(terminalId .. ":dwb:injectortank")
		local hasDispersionUnit = readData(terminalId .. ":dwb:dispersionunit")

		local userid = readData(terminalId .. ":dwb:user")
		if userid == 0 then
			writeData(terminalId .. ":dwb:user", CreatureObject(pParent):getObjectID())
			writeData(CreatureObject(pParent):getObjectID() .. ":dwb:terminal", terminalId)
		end

		if (hasMineral == 1 and hasJetpackBase == 1 and hasJetpackStabilizer == 1 and hasDuctedFan == 1 and hasInjectorTank == 1 and hasDispersionUnit == 1) then
			CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:starting_to_craft")
			writeData(terminalId .. ":dwb:currentlycrafting", 1)
			writeData(terminalId .. ":dwb:targetitemindex", 1)

			local spawn = deathWatchSpecialSpawns["jetpackattack1"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = deathWatchSpecialSpawns["jetpackattack2"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = deathWatchSpecialSpawns["jetpackattack3"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = deathWatchSpecialSpawns["jetpackattack4"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])

			local spawn = deathWatchSpecialSpawns["droidengineerattack1"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = deathWatchSpecialSpawns["droidengineerattack2"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = deathWatchSpecialSpawns["droidengineerattack3"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = deathWatchSpecialSpawns["droidengineerattack4"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])

			DeathWatchBunkerScreenPlay:startCraftingProcess(pParent, pDroid)
		else
			CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:items_still_needed")
			if hasJetpackBase == 0 then
				CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:jetpack_base")
			end

			if hasJetpackStabilizer == 0 then
				CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:stabilizer")
			end

			if hasDuctedFan == 0 then
				CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:ducted_fan")
			end

			if hasInjectorTank == 0 then
				CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:fuel_injector")
			end

			if hasDispersionUnit == 0 then
				CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:dispersion")
			end

			if hasMineral == 0 then
				CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:alum_mineral")
			end
		end
	end)
end

function deathWatchJetpackCraftingDroid:removeObject(droid, ingredient, slot)
	return false
end

deathWatchCraftingDroid = { }

function deathWatchCraftingDroid:canAddObject(pDroid, pIngredient, slot)
	if pIngredient == nil then
		return false
	end

	if slot ~= -1 then
		return false
	end

	local pParent = DeathWatchBunkerScreenPlay:getObjOwner(pIngredient)

	local terminalId = SceneObject(pDroid):getObjectID()
	local number = readData(terminalId .. ":dwb:craftingterminal")
	local template = SceneObject(pIngredient):getTemplateObjectPath()

	local userid = readData(terminalId .. ":dwb:user")

	if userid ~= 0 and userid ~= CreatureObject(pParent):getObjectID() then
		CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:same_user_only")
		return false
	end

	if CreatureObject(pParent):hasSkill(DeathWatchBunkerScreenPlay.terminalSkills[number + 4]) == false then
		CreatureObject(pParent):sendSystemMessage(DeathWatchBunkerScreenPlay.terminalSkillMessage[number])
		return false
	end

	local hasMineral = readData(terminalId .. ":dwb:alummineral")
	local hasBL = readData(terminalId .. ":dwb:binary")
	local hasPLC = readData(terminalId .. ":dwb:protective")
	local hasArmorPart = readData(terminalId .. ":dwb:bharmorpart")

	if template == DeathWatchBunkerScreenPlay.bunkerItems.binaryLiquid then
		if hasBL == 0 then
			return true
		else
			CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:already_has_component")
		end
	elseif template == DeathWatchBunkerScreenPlay.bunkerItems.protectiveLiquid then
		if hasPLC == 0 then
			return true
		else
			CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:already_has_component")
		end
	elseif template == DeathWatchBunkerScreenPlay.bunkerItems.alumMineral then
		if hasMineral == 0 then
			return true
		else
			CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:already_has_component")
		end
	else
		local table = DeathWatchBunkerScreenPlay.requiredDoorItems[number + 4]
		for i,v in ipairs(table) do
			if template == v then
				if hasArmorPart == 0 then
					return true
				else
					CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:making_something_else")
				end
			end
		end
	end

	return false
end

function deathWatchCraftingDroid:transferObject(pDroid, pIngredient, slot)
	if (pIngredient == nil) then
		return 0
	end

	if slot ~= -1 then
		return 0
	end

	local pParent = DeathWatchBunkerScreenPlay:getObjOwner(pIngredient)
	local template = SceneObject(pIngredient):getTemplateObjectPath()

	return ObjectManager.withSceneObject(pDroid, function(terminal)
		local terminalId = terminal:getObjectID()
		local number = readData(terminalId .. ":dwb:craftingterminal")

		if template == DeathWatchBunkerScreenPlay.bunkerItems.binaryLiquid then
			writeData(terminalId .. ":dwb:binary", 1)
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.protectiveLiquid then
			writeData(terminalId .. ":dwb:protective", 1)
		elseif template == DeathWatchBunkerScreenPlay.bunkerItems.alumMineral then
			writeData(terminalId .. ":dwb:alummineral", 1)
		else
			local table = DeathWatchBunkerScreenPlay.requiredDoorItems[number + 4]
			for i,v in ipairs(table) do
				if template == v then
					writeData(terminalId .. ":dwb:bharmorpart", 1)
					writeData(terminalId .. ":dwb:targetitemindex", i)
				end
			end
			if (readData(terminalId .. ":dwb:bharmorpart") ~= 1) then
				return 0
			end
		end

		createEvent(100, "DeathWatchBunkerScreenPlay", "destroyIngredient", pIngredient)

		local hasMineral = readData(terminalId .. ":dwb:alummineral")
		local hasBL = readData(terminalId .. ":dwb:binary")
		local hasPLC = readData(terminalId .. ":dwb:protective")
		local hasArmorPart = readData(terminalId .. ":dwb:bharmorpart")

		local userid = readData(terminalId .. ":dwb:user")
		if userid == 0 then
			writeData(terminalId .. ":dwb:user", CreatureObject(pParent):getObjectID())
			writeData(CreatureObject(pParent):getObjectID() .. ":dwb:terminal", terminalId)
		end

		if (hasMineral == 1 and hasBL == 1 and hasPLC == 1 and hasArmorPart == 1) then
			CreatureObject(pParent):sendSystemMessage("@dungeon/death_watch:starting_to_craft")
			writeData(terminalId .. ":dwb:currentlycrafting", 1)
			if number == 1 then
				local spawn = deathWatchSpecialSpawns["armorattack1"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = deathWatchSpecialSpawns["armorattack2"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = deathWatchSpecialSpawns["armorattack3"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = deathWatchSpecialSpawns["armorattack4"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			elseif number == 2 then
				local spawn = deathWatchSpecialSpawns["droidengineerattack1"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = deathWatchSpecialSpawns["droidengineerattack2"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = deathWatchSpecialSpawns["droidengineerattack3"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = deathWatchSpecialSpawns["droidengineerattack4"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			elseif number == 3 then
				local spawn = deathWatchSpecialSpawns["tailorattack1"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = deathWatchSpecialSpawns["tailorattack2"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = deathWatchSpecialSpawns["tailorattack3"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = deathWatchSpecialSpawns["tailorattack4"]
				spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			end

			DeathWatchBunkerScreenPlay:startCraftingProcess(pParent, pDroid)
		else
			ObjectManager.withCreatureObject(pParent, function(creature)
				creature:sendSystemMessage("@dungeon/death_watch:items_still_needed")
				if hasBL == 0 then
					creature:sendSystemMessage("@dungeon/death_watch:binary_liquid")
				end

				if hasPLC == 0 then
					creature:sendSystemMessage("@dungeon/death_watch:emulsifier")
				end

				if hasArmorPart == 0 then
					creature:sendSystemMessage(DeathWatchBunkerScreenPlay.partStrings[number])
				end

				if hasMineral == 0 then
					creature:sendSystemMessage("@dungeon/death_watch:alum_mineral")
				end
			end)
		end

		return 0
	end)
end

function deathWatchCraftingDroid:removeObject(droid, ingredient, slot)
	return false
end