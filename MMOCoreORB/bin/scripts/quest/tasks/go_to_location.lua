-- This script is for going to a specified location on a planet.

go_to_location = Task:new {
	taskName = "go_to_location",
	taskStart = startLocation,
	taskFinish = endLocation
}


-- Start the task of going to a location.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param target is usually a planet. (Required)
-- @param parameter1 is the X coordinate of the waypoint.
-- @param parameter2 is the Y coordinate of the waypoint.
function go_to_location.startLocation(pCreatureObject, target, parameter1, parameter2) 

	if (not isZoneEnabled(target)) then	
		return
	end
	
	task.setTaskStarted(pCreatureObject)

	local creatureObject = LuaCreatureObject(pCreatureObject)
	local height = getTerrainHeight(creatureObject, parameter1, parameter2)

	local pActiveArea = spawnSceneObject(target, "object/active_area.iff", parameter1, height, parameter2, 0, 0, 0, 0, 0)

	if (pActiveArea ~= nil) then
		local activeArea = LuaActiveArea(pActiveArea)
		activeArea:setRadius(64)
		activeArea:setNoBuildArea(true)
		createObserver(ENTEREDAREA, "go_to_location", "notifyEnteredArea", pActiveArea)
	end
	
end

-- Notifying entering the active area.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param target is usually a planet. (Required)
-- @param parameter1 is the X coordinate of the waypoint.
-- @param parameter2 is the Y coordinate of the waypoint.
function go_to_location:notifyEnteredArea(pActiveArea, pMovingObject)

	local movingObject = LuaSceneObject(pMovingObject)

	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
		
		if (task.hasTaskStarted(pMovingObject) then
			go_to_location.endLocation(pCreatureObject)

			local activeArea = LuaActiveArea(pActiveArea)
			activeArea:destroyObjectFromWorld()
			activeArea:destroyObjectFromDatabase()
		end
	end

end

-- Quest finished.
-- @param pCreatureObject pointer to the creature object of the player.
function go_to_location.endLocation(pCreatureObject) 

	task.setTaskFinished(pCreatureObject)
end
