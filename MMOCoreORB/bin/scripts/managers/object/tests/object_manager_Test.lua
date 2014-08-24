local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local ObjectManager = require("managers.object.object_manager")

-- TODO: several of the functions in this module needs more testing to test the return value and that functions are called correctly.

describe("Object Manager", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local pSceneObject = { "sceneObjectPointer" }
	local pCityRegion = { "cityRegionPointer" }
	local pActiveArea = { "activeAreaPointer" }
	local aiAgent = { "aiAgent" }
	local sceneObject = { "sceneObject" }
	local creatureObject = { "creatureObject" }
	local playerObject = { "playerObject" }
	local cityRegion = { "cityRegion" }
	local pInventory = { "inventoryPointer" }
	local activeArea = { "activeArea" }
	local objectId = 12345

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
		DirectorManagerMocks.activeAreas[pActiveArea] = activeArea

		creatureObject.getPlayerObject = spy.new(function() return pPlayerObject end)
		creatureObject.getSlottedObject = spy.new(function() return pInventory end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject
	end)

	describe("withCreatureAiAgent", function()
		it("Should return nil if the creature object pointer is nil to the withCreatureAiAgent function.", function()
			assert.is.Nil(ObjectManager.withCreatureAiAgent(nil, function(sceneObject) end))
		end)

		it("Should call the supplied lambda expression with the AiAgent when calling the withCreatureAiAgent function.", function()
			local aiAgentArgument = nil

			ObjectManager.withCreatureAiAgent(pCreatureObject, function(aiAgent) aiAgentArgument = aiAgent end)
			assert.same(aiAgentArgument, aiAgent)
		end)
	end)

	describe("withSceneObject", function()
		it("Should return nil if the scene object pointer is nil to the withSceneObject function.", function()
			assert.is.Nil(ObjectManager.withSceneObject(nil, function(sceneObject) end))
		end)

		it("Should call the supplied lambda expression with the SceneObject when calling the withSceneObject function.", function()
			local sceneObjectArgument = nil

			ObjectManager.withSceneObject(pSceneObject, function(sceneObject) sceneObjectArgument = sceneObject end)
			assert.same(sceneObjectArgument, sceneObject)
		end)
	end)

	describe("withCreatureObject", function()
		it("Should return nil if the creature object pointer is nil to the withCreatureObject function.", function()
			assert.is.Nil(ObjectManager.withCreatureObject(nil, function(creatureObject) end))
		end)

		it("Should call the supplied lambda expression with the CreatureObject when calling the withCreatureObject function.", function()
			local creatureObjectArgument = nil

			ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject) creatureObjectArgument = creatureObject end)
			assert.same(creatureObjectArgument, creatureObject)
		end)
	end)

	describe("withCreaturePlayerObject", function()
		it("Should return nil if the creature object pointer is nil to the withCreaturePlayerObject function.", function()
			assert.is.Nil(ObjectManager.withCreaturePlayerObject(nil, function(playerObject) end))
		end)

		it("Should return nil if the creature object has a nil pointer to the player object when calling the withCreaturePlayerObject function.", function()
			creatureObject.getPlayerObject = spy.new(function() return nil end)

			assert.is.Nil(ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject) end))
		end)
	end)

	describe("withPlayerObject", function()
		it("Should return nil if the player object pointer is nil to the withPlayerObject function.", function()
			assert.is.Nil(ObjectManager.withPlayerObject(nil, function(playerObject) end))
		end)

		it("Should call the supplied lambda expression with the PlayerObject when calling the withPlayerObject function.", function()
			local playerObjectArgument = nil

			ObjectManager.withPlayerObject(pPlayerObject, function(playerObject) playerObjectArgument = playerObject end)
			assert.same(playerObjectArgument, playerObject)
		end)
	end)

	describe("withCityRegion", function()
		it("Should return nil if the city region pointer is nil to the withCityRegion function.", function()
			assert.is.Nil(ObjectManager.withCityRegion(nil, function(cityRegion) end))
		end)

		it("Should call the supplied lambda expression with the CityRegion when calling the withCityRegion function.", function()
			local cityRegionArgument = nil

			ObjectManager.withCityRegion(pCityRegion, function(cityRegion) cityRegionArgument = cityRegion end)
			assert.same(cityRegionArgument, cityRegion)
		end)
	end)

	describe("withCreatureAndPlayerObject", function()
		it("Should return nil if the creature object pointer is nil to the withCreatureAndPlayerObject function.", function()
			assert.is.Nil(ObjectManager.withCreatureAndPlayerObject(nil, function(creatureObject, playerObject) end))
		end)

		it("Should return nil if the creature object has a nil pointer to the player object when calling the withCreatureAndPlayerObject function.", function()
			creatureObject.getPlayerObject = spy.new(function() return nil end)

			assert.is.Nil(ObjectManager.withCreatureAndPlayerObject(pCreatureObject, function(playerObject) end))
		end)

		it("Should call the supplied lambda expression with the PlayerObject when calling the withCreaturePlayerObject function.", function()
			local playerObjectArgument = nil

			ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject) playerObjectArgument = playerObject end)
			assert.same(playerObjectArgument, playerObject)
		end)

		it("Should call the supplied lambda expression with the CreatureObject and PlayerObject when calling the withCreatureAndPlayerObject function.", function()
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

	describe("withInventoryPointer", function()
		it("Should return nil if the creature object pointer is nil to the withInventoryPointer function.", function()
			assert.is.Nil(ObjectManager.withInventoryPointer(nil, function(pInventory) end))
		end)

		it("Should call the getSlottedObject function with 'inventory' as argument when calling the withInventoryPointer function.", function()
			ObjectManager.withInventoryPointer(pCreatureObject, function() end)

			assert.spy(creatureObject.getSlottedObject).was.called_with(creatureObject, "inventory")
		end)

		it("Should call the supplied lambda expression with the pointer to inventory when calling the withInventoryPointer function.", function()
			local pInventoryArgument = nil

			ObjectManager.withInventoryPointer(pCreatureObject, function(pInventory) pInventoryArgument = pInventory end)
			assert.same(pInventoryArgument, pInventory)
		end)

		it("Should not call the supplied lambda expression with the pointer to inventory when calling the withInventoryPointer function if the creature does not have an inventory.", function()
			local lambdaExpressionCalled = false
			creatureObject.getSlottedObject = spy.new(function() return nil end)

			ObjectManager.withInventoryPointer(pCreatureObject, function(pInventory) lambdaExpressionCalled = true end)
			assert.is_false(lambdaExpressionCalled)
		end)
	end)

	describe("withSceneObjectFromId", function()
		it("Should call getSceneObject with the id.", function()
			ObjectManager.withSceneObjectFromId(objectId, function() end)

			assert.spy(getSceneObject).was.called_with(objectId)
		end)

		describe("and a object is returned from getSceneObject", function()
			before_each(function()
				getSceneObject = spy.new(function() return pSceneObject end)
			end)

			it("Should call the supplied lambda expression witht he returned object as argument", function()
				local sceneObjectArgument = nil

				ObjectManager.withSceneObjectFromId(objectId, function(sceneObject) sceneObjectArgument = sceneObject end)

				assert.same(sceneObject, sceneObjectArgument)
			end)

			it("Should return the value returned from the lambda expression.", function()
				assert.same(234, ObjectManager.withSceneObjectFromId(objectId, function(sceneObject) return 234 end))
			end)
		end)

		describe("and nil is returned from getSceneObject", function()
			it("Should not call the supplied lambda expression.", function()
				local lambdaExpression = spy.new(function() end)

				ObjectManager.withSceneObjectFromId(objectId, lambdaExpression)

				assert.spy(lambdaExpression).was.not_called()
			end)

			it("Should return nil.", function()
				assert.is.Nil(ObjectManager.withSceneObjectFromId(objectId, function() end))
			end)
		end)
	end)

	describe("withActiveAreaObject", function()
		it("Should return nil if the scene object pointer is nil to the withSActiveAreaObject function.", function()
			assert.is.Nil(ObjectManager.withActiveArea(nil, function(activeArea) end))
		end)

		it("Should call the supplied lambda expression with the ActiveArea when calling the withSceneObject function.", function()
			local activeAreaArgument = nil

			ObjectManager.withActiveArea(pActiveArea, function(activeArea) activeAreaArgument = activeArea end)
			assert.same(activeAreaArgument, activeArea)
		end)
	end)
end)
