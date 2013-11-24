local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local GoToLocation = require("quest.tasks.go_to_location")

local testGoToLocation = GoToLocation:new {
	-- Task properties
	taskName = "testGoToLocation",
	taskFinish = spy.new(function() end),
	-- GoToLocation properties
	targetPlanet = "tatooine",
	targetX = 333,
	targetY = 111
}

local TASK_STARTED = 0xABCD

describe("Go To Location", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local creatureObject

	setup(function()
		DirectorManagerMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()
	end)

	describe("Interface functions", function()
		describe("taskStart", function()
			local realTaskStart

			setup(function()
				realTaskStart = testGoToLocation.taskStart
			end)

			teardown(function()
				testGoToLocation.taskStart = realTaskStart
			end)

			before_each(function()
				testGoToLocation.taskStart = spy.new(function() end)
			end)

			describe("When called with a player", function()
				it("Should call the private taskStart function.", function()
					testGoToLocation.taskStart(pCreatureObject)

					assert.spy(testGoToLocation.taskStart).was.called_with(pCreatureObject)
				end)
			end)
		end)

		describe("taskFinish", function()
			local realTaskFinish

			setup(function()
				realTaskFinish = testGoToLocation.taskFinish
			end)

			teardown(function()
				testGoToLocation.taskFinish = realTaskFinish
			end)

			before_each(function()
				testGoToLocation.taskFinish = spy.new(function() end)
			end)

			describe("When called with a player", function()
				it("Should call the private taskFinish function.", function()
					testGoToLocation.taskFinish(pCreatureObject)

					assert.spy(testGoToLocation.taskFinish).was.called_with(pCreatureObject)
				end)
			end)
		end)
	end)

	describe("Event handlers", function()
		describe("handleSpawnEvent", function()
			describe("When called with a player", function()
				local realFinish

				setup(function()
					realFinish = testGoToLocation.finish
				end)

				teardown(function()
					testGoToLocation.finish = realFinish
				end)

				before_each(function()
					testGoToLocation.finish = spy.new(function() end)
				end)

				it("Should check if the player is in a position where the encounter can happen.", function()
					testGoToLocation:handleEvent(pCreatureObject)

					assert.spy(testGoToLocation.finish).was.called_with(pCreatureObject)
				end)
			end)
		end)
	end)

	describe("Private functions", function()
		describe("taskStart", function()
			describe("When called with a player", function()
				local realTargetPlanet
				local realTargetX
				local realTargetY

				setup(function()
					realTargetPlanet = testGoToLocation.targetPlanet
					realTargetX = testGoToLocation.targetX
					realTargetY = testGoToLocation.targetY
				end)

				teardown(function()
					testGoToLocation.targetPlanet = realTargetPlanet
					testGoToLocation.targetX = realTargetX
					testGoToLocation.targetY = realTargetY
				end)

				before_each(function()
					GoToLocation.targetPlanet = "tatooine"
					GoToLocation.targetX = 5
					GoToLocation.targetY = 100
				end)

				it("Should create a spawn observer.", function()
					testGoToLocation:taskStart(pCreatureObject)

					assert.spy(createObserver).was.called_with(ENTEREDAREA, "GoToLocation", "handleEvent", pActiveArea)
				end)
			end)
		end)

		describe("taskFinish", function()
			describe("When called", function()
				--local realError

				setup(function()
					--realError = error
				end)

				teardown(function()
					--error = realError
				end)

				setup(function()
					--error = spy.new(function() end)
				end)

				it("Should generate an error.", function()
					testGoToLocation:taskFinish(pCreatureObject)

					--assert.spy(error).was.called(1)
				end)
			end)
		end)
	end)
end)
