local ObjectManager = require("managers.object.object_manager")
local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")

describe("Object Manager", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local pSceneObject = { "sceneObjectPointer" }
	local pCityRegion = { "cityRegionPointer" }
	local aiAgent = { "aiAgent" }
	local sceneObject = { "sceneObject" }
	local creatureObject = { "creatureObject" }
	local playerObject = { "playerObject" }
	local cityRegion = { "cityRegion" }

	setup(function()
		DirectorManagerMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()

		DirectorManagerMocks.aiAgents[pCreatureObject] = aiAgent
		DirectorManagerMocks.sceneObjects[pSceneObject] = sceneObject
		DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject
		DirectorManagerMocks.cityRegions[pCityRegion] = cityRegion

		creatureObject.getPlayerObject = spy.new(function() return pPlayerObject end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject
	end)

	it("Shall return nil if the creature object pointer is nil to the withCreatureAiAgent function.", function()
		assert.is.Nil(ObjectManager.withCreatureAiAgent(nil, function(sceneObject) end))
	end)
	it("Shall return nil if the scene object pointer is nil to the withSceneObject function.", function()
		assert.is.Nil(ObjectManager.withSceneObject(nil, function(sceneObject) end))
	end)

	it("Shall return nil if the creature object pointer is nil to the withCreatureObject function.", function()
		assert.is.Nil(ObjectManager.withCreatureObject(nil, function(creatureObject) end))
	end)

	it("Shall return nil if the creature object pointer is nil to the withCreaturePlayerObject function.", function()
		assert.is.Nil(ObjectManager.withCreaturePlayerObject(nil, function(playerObject) end))
	end)

	it("Shall return nil if the player object pointer is nil to the withPlayerObject function.", function()
		assert.is.Nil(ObjectManager.withPlayerObject(nil, function(playerObject) end))
	end)

	it("Shall return nil if the city region pointer is nil to the withCityRegion function.", function()
		assert.is.Nil(ObjectManager.withCityRegion(nil, function(cityRegion) end))
	end)

	it("Shall return nil if the creature object pointer is nil to the withCreatureAndPlayerObject function.", function()
		assert.is.Nil(ObjectManager.withCreatureAndPlayerObject(nil, function(creatureObject, playerObject) end))
	end)

	it("Shall call the supplied lambda expression with the AiAgent when calling the withCreatureAiAgent function.", function()
		local aiAgentArgument = nil

		ObjectManager.withCreatureAiAgent(pCreatureObject, function(aiAgent) aiAgentArgument = aiAgent end)
		assert.same(aiAgentArgument, aiAgent)
	end)

	it("Shall call the supplied lambda expression with the SceneObject when calling the withSceneObject function.", function()
		local sceneObjectArgument = nil

		ObjectManager.withSceneObject(pSceneObject, function(sceneObject) sceneObjectArgument = sceneObject end)
		assert.same(sceneObjectArgument, sceneObject)
	end)

	it("Shall call the supplied lambda expression with the CreatureObject when calling the withCreatureObject function.", function()
		local creatureObjectArgument = nil

		ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject) creatureObjectArgument = creatureObject end)
		assert.same(creatureObjectArgument, creatureObject)
	end)

	it("Shall call the supplied lambda expression with the PlayerObject when calling the withPlayerObject function.", function()
		local playerObjectArgument = nil

		ObjectManager.withPlayerObject(pPlayerObject, function(playerObject) playerObjectArgument = playerObject end)
		assert.same(playerObjectArgument, playerObject)
	end)

	it("Shall call the supplied lambda expression with the CityRegion when calling the withCityRegion function.", function()
		local cityRegionArgument = nil

		ObjectManager.withCityRegion(pCityRegion, function(cityRegion) cityRegionArgument = cityRegion end)
		assert.same(cityRegionArgument, cityRegion)
	end)

	it("Shall return nil if the creature object has a nil pointer to the player object when calling the withCreaturePlayerObject function.", function()
		creatureObject.getPlayerObject = spy.new(function() return nil end)

		assert.is.Nil(ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject) end))
	end)

	it("Shall return nil if the creature object has a nil pointer to the player object when calling the withCreatureAndPlayerObject function.", function()
		creatureObject.getPlayerObject = spy.new(function() return nil end)

		assert.is.Nil(ObjectManager.withCreatureAndPlayerObject(pCreatureObject, function(playerObject) end))
	end)

	it("Shall call the supplied lambda expression with the PlayerObject when calling the withCreaturePlayerObject function.", function()
		local playerObjectArgument = nil

		ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject) playerObjectArgument = playerObject end)
		assert.same(playerObjectArgument, playerObject)
	end)

	it("Shall call the supplied lambda expression with the CreatureObject and PlayerObject when calling the withCreatureAndPlayerObject function.", function()
		local creatureObjectArgument = nil
		local playerObjectArgument = nil

		ObjectManager.withCreatureAndPlayerObject(pCreatureObject, function(creatureObject, playerObject)
			creatureObjectArgument = creatureObject
			playerObjectArgument = playerObject
		end)
		assert.same(creatureObjectArgument, creatureObject)
		assert.same(playerObjectArgument, playerObject)
	end)
end)
