package.path = package.path .. ";scripts/screenplays/?.lua"
require("screenplay")

describe("ScreenPlay", function()
	it("Shall return nil if the creature object pointer is nil to the withCreatureAiAgent function.", function()
		assert.is.Nil(ScreenPlay.withCreatureAiAgent(nil, function(sceneObject) end))
	end)
	it("Shall return nil if the scene object pointer is nil to the withSceneObject function.", function()
		assert.is.Nil(ScreenPlay.withSceneObject(nil, function(sceneObject) end))
	end)

	it("Shall return nil if the creature object pointer is nil to the withCreatureObject function.", function()
		assert.is.Nil(ScreenPlay.withCreatureObject(nil, function(creatureObject) end))
	end)

	it("Shall return nil if the creature object pointer is nil to the withCreaturePlayerObject function.", function()
		assert.is.Nil(ScreenPlay.withCreaturePlayerObject(nil, function(playerObject) end))
	end)

	it("Shall return nil if the player object pointer is nil to the withPlayerObject function.", function()
		assert.is.Nil(ScreenPlay.withPlayerObject(nil, function(playerObject) end))
	end)

	it("Shall return nil if the city region pointer is nil to the withCityRegion function.", function()
		assert.is.Nil(ScreenPlay.withCityRegion(nil, function(cityRegion) end))
	end)

	it("Shall return nil if the creature object pointer is nil to the withCreatureAndPlayerObject function.", function()
		assert.is.Nil(ScreenPlay.withCreatureAndPlayerObject(nil, function(creatureObject, playerObject) end))
	end)

	it("Shall call the supplied lambda expression with the AiAgent when calling the withCreatureAiAgent function.", function()
		local pCreatureObject = { "creatureObjectPointer" }
		local aiAgentCreated = { "sceneObject" }
		local aiAgentArgument = nil
		local realLuaAiAgent = LuaAiAgent
		LuaAiAgent = spy.new(function() return aiAgentCreated end)

		ScreenPlay.withCreatureAiAgent(pCreatureObject, function(aiAgent) aiAgentArgument = aiAgent end)
		assert.same(aiAgentArgument, aiAgentCreated)

		LuaAiAgent = realLuaAiAgent
	end)

	it("Shall call the supplied lambda expression with the SceneObject when calling the withSceneObject function.", function()
		local pSceneObject = { "sceneObjectPointer" }
		local sceneObjectCreated = { "sceneObject" }
		local sceneObjectArgument = nil
		local realLuaSceneObject = LuaSceneObject
		LuaSceneObject = spy.new(function() return sceneObjectCreated end)

		ScreenPlay.withSceneObject(pSceneObject, function(sceneObject) sceneObjectArgument = sceneObject end)
		assert.same(sceneObjectArgument, sceneObjectCreated)

		LuaSceneObject = realLuaSceneObject
	end)

	it("Shall call the supplied lambda expression with the CreatureObject when calling the withCreatureObject function.", function()
		local pCreatureObject = { "creatureObjectPointer" }
		local creatureObjectCreated = { "creatureObject" }
		local creatureObjectArgument = nil
		local realLuaCreatureObject = LuaCreatureObject
		LuaCreatureObject = spy.new(function() return creatureObjectCreated end)

		ScreenPlay.withCreatureObject(pCreatureObject, function(creatureObject) creatureObjectArgument = creatureObject end)
		assert.same(creatureObjectArgument, creatureObjectCreated)

		LuaCreatureObject = realLuaCreatureObject
	end)

	it("Shall call the supplied lambda expression with the PlayerObject when calling the withPlayerObject function.", function()
		local pPlayerObject = { "playerObjectPointer" }
		local playerObjectCreated = { "playerObject" }
		local playerObjectArgument = nil
		local realLuaPlayerObject = LuaPlayerObject
		LuaPlayerObject = spy.new(function() return playerObjectCreated end)

		ScreenPlay.withPlayerObject(pPlayerObject, function(playerObject) playerObjectArgument = playerObject end)
		assert.same(playerObjectArgument, playerObjectCreated)

		LuaPlayerObject = realLuaPlayerObject
	end)

	it("Shall call the supplied lambda expression with the CityRegion when calling the withCityRegion function.", function()
		local pCityRegion = { "cityRegionPointer" }
		local cityRegionCreated = { "cityRegion" }
		local cityRegionArgument = nil
		local realLuaCityRegion = LuaCityRegion
		LuaCityRegion = spy.new(function() return cityRegionCreated end)

		ScreenPlay.withCityRegion(pCityRegion, function(cityRegion) cityRegionArgument = cityRegion end)
		assert.same(cityRegionArgument, cityRegionCreated)

		LuaCityRegion = realLuaCityRegion
	end)

	it("Shall return nil if the creature object has a nil pointer to the player object when calling the withCreaturePlayerObject function.", function()
		local pCreatureObject = { "creatureObjectPointer" }
		local getPlayerObjectSpy = spy.new(function() return nil end)
		local realLuaCreatureObject = LuaCreatureObject
		LuaCreatureObject = spy.new(function() return { getPlayerObject = getPlayerObjectSpy } end)

		assert.is.Nil(ScreenPlay.withCreaturePlayerObject(pCreatureObject, function(playerObject) end))

		LuaCreatureObject = realLuaCreatureObject
	end)

	it("Shall return nil if the creature object has a nil pointer to the player object when calling the withCreatureAndPlayerObject function.", function()
		local pCreatureObject = { "creatureObjectPointer" }
		local getPlayerObjectSpy = spy.new(function() return nil end)
		local realLuaCreatureObject = LuaCreatureObject
		LuaCreatureObject = spy.new(function() return { getPlayerObject = getPlayerObjectSpy } end)

		assert.is.Nil(ScreenPlay.withCreatureAndPlayerObject(pCreatureObject, function(playerObject) end))

		LuaCreatureObject = realLuaCreatureObject
	end)

	it("Shall call the supplied lambda expression with the PlayerObject when calling the withCreaturePlayerObject function.", function()
		local pCreatureObject = { "creatureObjectPointer" }
		local pPlayerObject = { "playerObjectPointer" }
		local playerObjectCreated = { "player" }
		local playerObjectArgument = nil
		local getPlayerObjectSpy = spy.new(function() return pPlayerObject end)
		local realLuaCreatureObject = LuaCreatureObject
		LuaCreatureObject = spy.new(function() return { getPlayerObject = getPlayerObjectSpy } end)
		local realLuaPlayerObject  = LuaPlayerObject 
		LuaPlayerObject = spy.new(function() return playerObjectCreated end)

		ScreenPlay.withCreaturePlayerObject(pCreatureObject, function(playerObject) playerObjectArgument = playerObject end)
		assert.same(playerObjectArgument, playerObjectCreated)

		LuaCreatureObject = realLuaCreatureObject
		LuaPlayerObject = realLuaPlayerObject
	end)

	it("Shall call the supplied lambda expression with the CreatureObject and PlayerObject when calling the withCreatureAndPlayerObject function.", function()
		local pCreatureObject = { "creatureObjectPointer" }
		local creatureObjectArgument = nil
		local pPlayerObject = { "playerObjectPointer" }
		local playerObjectCreated = { "player" }
		local playerObjectArgument = nil
		local getPlayerObjectSpy = spy.new(function() return pPlayerObject end)
		local creatureObjectCreated = { getPlayerObject = getPlayerObjectSpy }
		local realLuaCreatureObject = LuaCreatureObject
		LuaCreatureObject = spy.new(function() return creatureObjectCreated end)
		local realLuaPlayerObject  = LuaPlayerObject 
		LuaPlayerObject = spy.new(function() return playerObjectCreated end)

		ScreenPlay.withCreatureAndPlayerObject(pCreatureObject, function(creatureObject, playerObject) 
			creatureObjectArgument = creatureObject
			playerObjectArgument = playerObject
		end)
		assert.same(creatureObjectArgument, creatureObjectCreated)
		assert.same(playerObjectArgument, playerObjectCreated)

		LuaCreatureObject = realLuaCreatureObject
		LuaPlayerObject = realLuaPlayerObject
	end)
end)
