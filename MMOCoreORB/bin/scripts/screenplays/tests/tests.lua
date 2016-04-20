Tests = {}

function Tests:stop()
	writeSharedMemory("runTests", 0)
end

function Tests:start()
	writeSharedMemory("runTests", 1)
end

function Tests:addPlayer(spawnPoint)
	if readSharedMemory("testPlayer") ~= 0 then
		local player = getSceneObject(readSharedMemory("testPlayer"))
		SceneObject(player):destroyObjectFromWorld()
		deleteSharedMemory("testPlayer")
	end

	local player = spawnSceneObject("creature_test", "object/creature/player/human_male.iff", spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, 0)

	if player == nil then
		AiAgent(agent):info("Error creating player (return nil) in Tests:aiMoveTest.")
		return
	end

	if not SceneObject(player):isPlayerCreature() then
		AiAgent(agent):info("Did not create a PlayerCreature in Tests:aiMoveTest.")
		SceneObject(player):destroyObjectFromWorld()
		return
	end

	writeSharedMemory("testPlayer", SceneObject(player):getObjectID())
end

function Tests:aiMoveTest()
	-- in a test zone, create a creature at a point, and have it move to another
	-- point. Do this outside (we can try to create an inside test later).
	local spawnPoint = getSpawnPoint("creature_test", 0, 0, 0, 100)
	local agent = spawnMobile("creature_test", "bark_mite", 0, spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, 0)

	if agent == nil then
		AiAgent(agent):info("Error creating agent (return nil) in Tests:aiMoveTest.")
		return
	end

	if not SceneObject(agent):isAiAgent() then
		AiAgent(agent):info("Did not create an AiAgent in Tests:aiMoveTest.")
		SceneObject(agent):destroyObjectFromWorld()
		return
	end

	if AiAgent(agent):getNumberOfPlayersInRange() == 0 then
		Tests:addPlayer(spawnPoint)
	end

	AiAgent(agent):setAiTemplate("")
	AiAgent(agent):stopWaiting()
	AiAgent(agent):setWait(0)
	AiAgent(agent):setFollowState(4) -- Patrolling

	local moveTarget = getSpawnPoint("creature_test", 10, 0, 0, 100)
	AiAgent(agent):setNextPosition(moveTarget[1],moveTarget[2],moveTarget[3], 0)
	AiAgent(agent):executeBehavior()
	AiAgent(agent):info("Pathing to: (" .. moveTarget[1] .. ", " .. moveTarget[2] .. ", " .. moveTarget[3] .. ")")
	
	local args = moveTarget[1] .. "," .. moveTarget[2] .. "," .. moveTarget[3]
	createEvent(2000, "Tests", "aiMoveEvent", agent, args)
end

function Tests:aiMoveEvent(agent, coords)
	if agent == nil then
		AiAgent(agent):info("nil AiAgent in Tests:aiMoveEvent().")
		return
	end

	if not SceneObject(agent):isAiAgent() then
		AiAgent(agent):info("agent is not an AiAgent in Tests:aiMoveEvent().");
		return
	end

	AiAgent(agent):info("Agent location: (" .. SceneObject(agent):getPositionX() .. ", " .. SceneObject(agent):getPositionZ() .. ", " .. SceneObject(agent):getPositionY() .. ")")

	if AiAgent(agent):getNumberOfPlayersInRange() == 0 then
		Tests:addPlayer(spawnPoint)
	end

	x, z, y = coords:match("([^,]+),([^,]+),([^,]+)")
	if SceneObject(agent):getDistanceToPosition(x, z, y) > 0.15 and readSharedMemory("runTests") == 1 then
		createEvent(2000, "Tests", "aiMoveEvent", agent, coords)
		AiAgent(agent):executeBehavior()
	else
		AiAgent(agent):info("Destination Reached.")
		SceneObject(agent):destroyObjectFromWorld()
	end
end

function Tests:aiAggroTest()
	-- in a test zone, create a creature at a point, and have it move to another
	-- point. Do this outside (we can try to create an inside test later).
	-- TODO: use creature_test zone (won't load due to being version 0013)
	local spawnPoint = getSpawnPoint("creature_test", 0, 0, 0, 100)
	local agent = spawnMobile("creature_test", "acklay", 0, spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, 0)

	if agent == nil then
		AiAgent(agent):info("Error creating agent (return nil) in Tests:aiMoveTest.")
		return
	end

	if not SceneObject(agent):isAiAgent() then
		AiAgent(agent):info("Did not create an AiAgent in Tests:aiMoveTest.")
		SceneObject(agent):destroyObjectFromWorld()
		return
	end

	Tests:addPlayer(spawnPoint)

	AiAgent(agent):setAiTemplate("")
	AiAgent(agent):stopWaiting()
	AiAgent(agent):setWait(0)
	AiAgent(agent):executeBehavior()

	AiAgent(agent):info("Starting aggro test.")

	createEvent(2000, "Tests", "aiAggroEvent", agent, "")
end

function Tests:aiAggroEvent(agent, args)
	if agent == nil then
		AiAgent(agent):info("nil AiAgent in Tests:aiAggroEvent().")
		return
	end

	if not SceneObject(agent):isAiAgent() then
		AiAgent(agent):info("agent is not an AiAgent in Tests:aiAggroEvent().");
		return
	end
	
	if readSharedMemory("testPlayer") ~= 0 then
		local player = getSceneObject(readSharedMemory("testPlayer"))
		if CreatureObject(player):isDead() or CreatureObject(player):isIncapacitated() then
			SceneObject(player):info("I have been killed!")
			SceneObject(player):destroyObjectFromWorld()
			return
		end
	end

	AiAgent(agent):info("Target OID: " .. AiAgent(agent):getTargetID() .. " FollowState: " .. AiAgent(agent):getFollowState())

	if AiAgent(agent):getTargetID() == 0 and readSharedMemory("runTests") == 1 then
		createEvent(2000, "Tests", "aiAggroEvent", agent, "")
	else
		if AiAgent(agent):getTargetID() > 0 then AiAgent(agent):info("Acklay Aggroed.") end
		SceneObject(agent):destroyObjectFromWorld()
	end
end
