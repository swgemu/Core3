local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local PersistentEvent = require("quest.tasks.persistent_event")

describe("Persistent Event", function()
	local pCreatureObject = { "creatureObjectPointer" }

	setup(function()
		DirectorManagerMocks.mocks.setup()

		PersistentEvent.exposePrivateFunctions()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()

		PersistentEvent.hidePrivateFunctions()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()
	end)

	describe("Interface functions", function()
		describe("taskStart", function()
			local realTaskStart

			setup(function()
				realTaskStart = PersistentEvent.private.taskStart
			end)

			teardown(function()
				PersistentEvent.private.taskStart = realTaskStart
			end)

			before_each(function()
				PersistentEvent.private.taskStart = spy.new(function() end)
			end)

			describe("When called with a player", function()
				it("Should call the private taskStart function.", function()
					PersistentEvent.taskStart(pCreatureObject)

					assert.spy(PersistentEvent.private.taskStart).was.called_with(pCreatureObject)
				end)
			end)
		end)

		describe("taskFinish", function()
			local realTaskFinish

			setup(function()
				realTaskFinish = PersistentEvent.private.taskFinish
			end)

			teardown(function()
				PersistentEvent.private.taskFinish = realTaskFinish
			end)

			before_each(function()
				PersistentEvent.private.taskFinish = spy.new(function() end)
			end)

			describe("When called with a player", function()
				it("Should call the private taskFinish function.", function()
					PersistentEvent.taskFinish(pCreatureObject)

					assert.spy(PersistentEvent.private.taskFinish).was.called_with(pCreatureObject)
				end)
			end)
		end)
	end)

	describe("Event handlers", function()
		describe("handleSpawnEvent", function()
			describe("When called with a player", function()
				local realFinish

				setup(function()
					realFinish = PersistentEvent.finish
				end)

				teardown(function()
					PersistentEvent.finish = realFinish
				end)

				before_each(function()
					PersistentEvent.finish = spy.new(function() end)
				end)

				it("Should check if the player is in a position where the encounter can happen.", function()
					PersistentEvent.global:handleEvent(pCreatureObject)

					assert.spy(PersistentEvent.finish).was.called_with(pCreatureObject)
				end)
			end)
		end)
	end)

	describe("Private functions", function()
		describe("taskStart", function()
			describe("When called with a player", function()
				local realMinTime
				local realMaxTime
				local eventTime = 10

				setup(function()
					realMinTime = PersistentEvent.minimumTimeUntilEncounter
					realMaxTime = PersistentEvent.maximumTimeUntilEncounter
				end)

				teardown(function()
					PersistentEvent.minimumTimeUntilEncounter = realMinTime
					PersistentEvent.maximumTimeUntilEncounter = realMaxTime
				end)

				before_each(function()
					PersistentEvent.minimumTimeUntilEncounter = eventTime
					PersistentEvent.maximumTimeUntilEncounter = eventTime
				end)

				it("Should create a spawn event.", function()
					PersistentEvent.private.taskStart(pCreatureObject)

					assert.spy(createEvent).was.called_with(true, eventTime, "PersistentEventPublicEventsAndObservers", "handleEvent", pCreatureObject)
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
					PersistentEvent.private.taskFinish(pCreatureObject)

					assert.spy(error).was.called(1)
				end)
			end)
		end)
	end)
end)
