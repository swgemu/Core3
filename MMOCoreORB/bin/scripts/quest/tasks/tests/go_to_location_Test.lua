local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local GoToLocation = require("quest.tasks.go_to_location")

describe("Go To Location", function()
	local pCreatureObject = { "creatureObjectPointer" }

	setup(function()
		DirectorManagerMocks.mocks.setup()

		GoToLocation.exposePrivateFunctions()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()

		GoToLocation.hidePrivateFunctions()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()
	end)

	describe("Interface functions", function()
		describe("taskStart", function()
			local realTaskStart

			setup(function()
				realTaskStart = GoToLocation.private.taskStart
			end)

			teardown(function()
				GoToLocation.private.taskStart = realTaskStart
			end)

			before_each(function()
				GoToLocation.private.taskStart = spy.new(function() end)
			end)

			describe("When called with a player", function()
				it("Should call the private taskStart function.", function()
					GoToLocation.taskStart(pCreatureObject)

					assert.spy(GoToLocation.private.taskStart).was.called_with(pCreatureObject)
				end)
			end)
		end)

		describe("taskFinish", function()
			local realTaskFinish

			setup(function()
				realTaskFinish = GoToLocation.private.taskFinish
			end)

			teardown(function()
				GoToLocation.private.taskFinish = realTaskFinish
			end)

			before_each(function()
				GoToLocation.private.taskFinish = spy.new(function() end)
			end)

			describe("When called with a player", function()
				it("Should call the private taskFinish function.", function()
					GoToLocation.taskFinish(pCreatureObject)

					assert.spy(GoToLocation.private.taskFinish).was.called_with(pCreatureObject)
				end)
			end)
		end)
	end)

	describe("Event handlers", function()
		describe("handleSpawnEvent", function()
			describe("When called with a player", function()
				local realFinish

				setup(function()
					realFinish = GoToLocation.finish
				end)

				teardown(function()
					GoToLocation.finish = realFinish
				end)

				before_each(function()
					GoToLocation.finish = spy.new(function() end)
				end)

				it("Should check if the player is in a position where the encounter can happen.", function()
					GoToLocation.global:handleEvent(pCreatureObject)

					assert.spy(GoToLocation.finish).was.called_with(pCreatureObject)
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
					realTargetPlanet = GoToLocation.targetPlanet
					realTargetX = GoToLocation.targetX
					realTargetY = GoToLocation.targetY
				end)

				teardown(function()
					GoToLocation.targetPlanet = realTargetPlanet
					GoToLocation.targetX = realTargetX
					GoToLocation.targetY = realTargetY
				end)

				before_each(function()
					GoToLocation.targetPlanet = "tatooine"
					GoToLocation.targetX = 5
					GoToLocation.targetY = 100
				end)

				it("Should create a spawn observer.", function()
					GoToLocation.private.taskStart(pCreatureObject)

					assert.spy(createObserver).was.called_with(ENTEREDAREA, "GoToLocationPublicEventsAndObservers", "handleEvent", pActiveArea)
				end)
			end)
		end)

		describe("taskFinish", function()
			describe("When called", function()
				local realError

				setup(function()
					realError = error
				end)

				teardown(function()
					error = realError
				end)

				setup(function()
					error = spy.new(function() end)
				end)

				it("Should generate an error.", function()
					GoToLocation.private.taskFinish(pCreatureObject)

					assert.spy(error).was.called(1)
				end)
			end)
		end)
	end)
end)
