local GoToTheater = require("quest.tasks.go_to_theater")
local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")

local testGoToTheater = GoToTheater:new {
	taskName = "testGoToTheater",
	minimumDistance = 768,
	maximumDistance = 1280
}

describe("GoToTheater", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local positionX = 1234
	local positionY = 5678
	local minDistance = 768
	local maxDistance = 1280
	local creatureObject

	setup(function()
		DirectorManagerMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()

		creatureObject = {}
		creatureObject.setScreenPlayState = spy.new(function() end)
		creatureObject.getScreenPlayState = spy.new(function() return 0 end)
		creatureObject.getWorldPositionX = spy.new(function() return positionX end)
		creatureObject.getWorldPositionY = spy.new(function() return positionY end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

	end)

	describe("start", function()
		describe("When called with a player", function()
			it("Should find a spawn point for the theater.", function()
				testGoToTheater:start(pCreatureObject)

				assert.spy(getSpawnPoint).was.called_with(pCreatureObject, positionX, positionY, minDistance, maxDistance)
			end)

			it("Should spawn the theater at the spawn point.", function()
			end)

			it("Should spawn the mobiles at the theater.", function()
			end)

			it("Should setup and active area at the spawn point.", function()
			end)

			it("Should generate an active waypoint for the player to the theater.", function()
			end)

			it("Should schedule a despawn of the theater.", function()
			end)
		end)
	end)
end)
