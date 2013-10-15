package.path = package.path .. ";scripts/managers/?.lua"
require("jedi_manager")

describe("Jedi Manager", function()
	it("Shall return nil if the creature object pointer is nil to the withCreatureObject function.", function()
		assert.is.Nil(JediManager.withCreatureObject(nil, function(creatureObject) end))
	end)

	it("Shall return nil if the creature object pointer is nil to the withCreaturePlayerObject function.", function()
		assert.is.Nil(JediManager.withCreaturePlayerObject(nil, function(playerObject) end))
	end)

	it("Shall return nil if the player object pointer is nil to the withPlayerObject function.", function()
		assert.is.Nil(JediManager.withPlayerObject(nil, function(playerObject) end))
	end)

	it("Shall return nil if the creature object pointer is nil to the withCreatureAndPlayerObject function.", function()
		assert.is.Nil(JediManager.withCreatureAndPlayerObject(nil, function(creatureObject, playerObject) end))
	end)

	it("Shall call the supplied lambda expression with the CreatureObject when calling the withCreatureObject function.", function()
		local creaturePointer = { "creaturePointer" }
		local creatureObjectCreated = { "creature" }
		local creatureObjectArgument = nil
		LuaCreatureObject = spy.new(function() return creatureObjectCreated end)

		JediManager.withCreatureObject(creaturePointer, function(creatureObject) creatureObjectArgument = creatureObject end)
		assert.same(creatureObjectArgument, creatureObjectCreated)
	end)

	it("Shall call the supplied lambda expression with the PlayerObject when calling the withPlayerObject function.", function()
		local playerPointer = { "playerPointer" }
		local playerObjectCreated = { "player" }
		local playerObjectArgument = nil
		LuaPlayerObject = spy.new(function() return playerObjectCreated end)

		JediManager.withPlayerObject(playerPointer, function(playerObject) playerObjectArgument = playerObject end)
		assert.same(playerObjectArgument, playerObjectCreated)
	end)

	it("Shall return nil if the creature object has a nil pointer to the player object when calling the withCreaturePlayerObject function.", function()
		local creaturePointer = { "creaturePointer" }
		local getPlayerObjectSpy = spy.new(function() return nil end)
		LuaCreatureObject = spy.new(function() return { getPlayerObject = getPlayerObjectSpy } end)

		assert.is.Nil(JediManager.withCreaturePlayerObject(creaturePointer, function(playerObject) end))
	end)

	it("Shall return nil if the creature object has a nil pointer to the player object when calling the withCreatureAndPlayerObject function.", function()
		local creaturePointer = { "creaturePointer" }
		local getPlayerObjectSpy = spy.new(function() return nil end)
		LuaCreatureObject = spy.new(function() return { getPlayerObject = getPlayerObjectSpy } end)

		assert.is.Nil(JediManager.withCreatureAndPlayerObject(creaturePointer, function(playerObject) end))
	end)

	it("Shall call the supplied lambda expression with the PlayerObject when calling the withCreaturePlayerObject function.", function()
		local creaturePointer = { "creaturePointer" }
		local playerPointer = { "playerPointer" }
		local playerObjectCreated = { "player" }
		local playerObjectArgument = nil
		local getPlayerObjectSpy = spy.new(function() return playerPointer end)
		LuaCreatureObject = spy.new(function() return { getPlayerObject = getPlayerObjectSpy } end)
		LuaPlayerObject = spy.new(function() return playerObjectCreated end)

		JediManager.withCreaturePlayerObject(creaturePointer, function(playerObject) playerObjectArgument = playerObject end)
		assert.same(playerObjectArgument, playerObjectCreated)
	end)

	it("Shall call the supplied lambda expression with the CreatureObject and PlayerObject when calling the withCreatureAndPlayerObject function.", function()
		local creaturePointer = { "creaturePointer" }
		local creatureObjectArgument = nil
		local playerPointer = { "playerPointer" }
		local playerObjectCreated = { "player" }
		local playerObjectArgument = nil
		local getPlayerObjectSpy = spy.new(function() return playerPointer end)
		local creatureObjectCreated = { getPlayerObject = getPlayerObjectSpy }
		LuaCreatureObject = spy.new(function() return creatureObjectCreated end)
		LuaPlayerObject = spy.new(function() return playerObjectCreated end)

		JediManager.withCreatureAndPlayerObject(creaturePointer, function(creatureObject, playerObject) 
			creatureObjectArgument = creatureObject
			playerObjectArgument = playerObject
		end)
		assert.same(creatureObjectArgument, creatureObjectCreated)
		assert.same(playerObjectArgument, playerObjectCreated)
	end)
end)
