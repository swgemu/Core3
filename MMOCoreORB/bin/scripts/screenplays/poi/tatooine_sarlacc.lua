local ObjectManager = require("managers.object.object_manager")

tatooine_sarlacc_screenplay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("tatooine_sarlacc_screenplay", true)

function tatooine_sarlacc_screenplay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnActiveAreas()
	end
end

function tatooine_sarlacc_screenplay:spawnActiveAreas()
	local pWarningArea = spawnSceneObject("tatooine", "object/active_area.iff", -6174.25, 20, -3360.97, 0, 0, 0, 0, 0)
	local pDiseaseArea = spawnSceneObject("tatooine", "object/active_area.iff", -6174.25, 20, -3360.97, 0, 0, 0, 0, 0)
	
	ObjectManager.withActiveArea(pDiseaseArea, function(diseaseArea)
		diseaseArea:setRadius(50)
		createObserver(ENTEREDAREA, "tatooine_sarlacc_screenplay", "notifyEnteredSarlaccDisease", pDiseaseArea)
	end)
	ObjectManager.withActiveArea(pWarningArea, function(warningArea)
		warningArea:setRadius(100)
		createObserver(ENTEREDAREA, "tatooine_sarlacc_screenplay", "notifyEnteredSarlaccWarning", pWarningArea)
	end)
end

function tatooine_sarlacc_screenplay:notifyEnteredSarlaccDisease(pActiveArea, pMovingObject)
	printf("disease aa triggered\n")
	ObjectManager.withSceneObject(pMovingObject, function(movingObject)
		ObjectManager.withCreatureObject(pMovingObject, function(player)
			if (self:hasProtectiveCoveralls(pMovingObject) == false) then
				ObjectManager.withSceneObject(pActiveArea, function(activeArea)
					player:addDotState(DISEASED, math.random(20) + 30, HEALTH, 1000 * 60 * 60, 2000, activeArea:getObjectID(), 0)
					player:sendSystemMessage("@mob/sarlacc:sarlacc_dot") --You suddenly feel weak and sick.
				end)
			end
		end)
	end)
	return 0
end

function tatooine_sarlacc_screenplay:notifyEnteredSarlaccWarning(pActiveArea, pMovingObject)
	printf("warning aa triggered\n")
	ObjectManager.withSceneObject(pMovingObject, function(movingObject)
		ObjectManager.withCreatureObject(pMovingObject, function(player)
			player:sendSystemMessage("@mob/sarlacc:sarlacc_poison") --The air is thick with the smell of rot and disease.
		end)
	end)
	return 0
end

function tatooine_sarlacc_screenplay:hasProtectiveCoveralls(pPlayer)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local pInventory = player:getSlottedObject("inventory")
		local pItem = getContainerObjectByTemplate(pInventory, "object/tangible/wearables/bodysuit/bodysuit_sarlacc_coverall.iff", true)
		if pItem ~= nil then
			return true
		else
			return false
		end
	end)
end