package.path = package.path .. ";scripts/managers/?.lua"
JediManager = require("jedi_manager")

jediManagerName = "VillageJediManager"

USEDHOLOCRON = "used_holocron"
HOLOCRONCOOLDOWNTIME = 24 * 60 * 60 * 1000 -- 24 hours

VillageJediManager = JediManager:new {
	jediManagerName = jediManagerName,
	jediProgressionType = VILLAGEJEDIPROGRESSION,
	startingEvent = nil,
}

-- Check if the player can use the holocron.
-- @param pCreatureObject pointer to the creature object of the player who tries to use the holocron.
-- @return true if the player can use the holocron.
function VillageJediManager.canUseHolocron(pCreatureObject)
	return VillageJediManager.withCreatureAndPlayerObject(pCreatureObject, function(creatureObject, playerObject) 
		return playerObject:isJedi() and not creatureObject:checkCooldownRecovery(USEDHOLOCRON)
	end)
end

-- Checks if the player can replenish the force or not.
-- @param pCreatureObject pointer to the creature object of the player who should be checked.
-- @return true if the player can replenish the force.
function VillageJediManager.canReplenishForce(pCreatureObject)
	return VillageJediManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		return playerObject:getForcePower() < playerObject:getForcePowerMax()
	end)
end

-- Use the holocron on the player.
-- @param pSceneObject pointer to the scene object of the holocron.
-- @param pCreatureObject pointer to the creature object of the player who is using the holocron.
function VillageJediManager.useTheHolocron(pSceneObject, pCreatureObject)
	VillageJediManager.withCreatureAndPlayerObject(pCreatureObject, function(creatureObject, playerObject) 
		-- The holocrom hums softly as you feel your Force power replenish.
		creatureObject:sendSystemMessage("@jedi_spam:holocron_force_replenish")
		playerObject:setForcePower(playerObject:getForcePowerMax());
		creatureObject:addCooldown(USEDHOLOCRON, HOLOCRONCOOLDOWNTIME)
	end)
	local sceneObject = LuaSceneObject(pSceneObject)
	sceneObject:destroyObjectFromWorld()
end

-- Send message to the player that he cannot replenish the force.
-- @param pCreatureObject pointer to the creature object of the player that tries to use the holocron.
function VillageJediManager.cannotReplenishForce(pCreatureObject)
	VillageJediManager.withCreatureObject(pCreatureObject, function(creatureObject)
		-- You are already at your maximum Force power.
		creatureObject:sendSystemMessage("@jedi_spam:holocron_force_max")
	end)
end

-- Send message to the player that he cannot use the holocron.
-- @param pCreatureObject pointer to the creature object of the player that tries to use the holocron.
function VillageJediManager.cannotUseHolocron(pCreatureObject)
	VillageJediManager.withCreatureObject(pCreatureObject, function(creatureObject)
		-- The holocron hums briefly, but otherwise does nothing.
		creatureObject:sendSystemMessage("@jedi_spam:holocron_no_effect")
	end)
end

-- Handling of the useHolocron event.
-- @param pSceneObject pointer to the holocron object.
-- @param pCreatureObject pointer to the creature object that used the holocron.
function VillageJediManager:useHolocron(pSceneObject, pCreatureObject)
	if VillageJediManager.canUseHolocron(pCreatureObject) then
		if VillageJediManager.canReplenishForce(pCreatureObject) then
			VillageJediManager.useTheHolocron(pSceneObject, pCreatureObject)
		else
			VillageJediManager.cannotReplenishForce(pCreatureObject)
		end
	else
		VillageJediManager.cannotUseHolocron(pCreatureObject)
	end
end

return VillageJediManager
