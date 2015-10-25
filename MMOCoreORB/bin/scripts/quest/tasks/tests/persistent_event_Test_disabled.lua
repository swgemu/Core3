local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local PersistentEvent = require("quest.tasks.persistent_event")

local testPersistentEvent = PersistentEvent:new {
	-- Task properties
	taskName = "testPersistentEvent",
	taskFinish = spy.new(function() return true end),
	-- PersistentEvent properties
	minimumTimeUntilEvent = 10,
	maximumTimeUntilEvent = 10,
	handlerName = "TestPersistentEvent",
	handlerFunction = "handleEventTest"
}

local TASK_STARTED = 0xABCD

describe("Persistent Event", function()
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

		creatureObject = {}
		creatureObject.getScreenPlayState = spy.new(function() return false end)
		creatureObject.removeScreenPlayState = spy.new(function() end)
		creatureObject.setScreenPlayState = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject
	end)

	describe("Interface functions", function()
		describe("start", function()
			local realTaskStart

			setup(function()
				realTaskStart = testPersistentEvent.taskStart
			end)

			teardown(function()
				testPersistentEvent.taskStart = realTaskStart
			end)

			before_each(function()
				testPersistentEvent.taskStart = spy.new(function() return true end)
			end)

			describe("When called with a player", function()
				it("Should call the private taskStart function.", function()
					testPersistentEvent:start(pCreatureObject)

					assert.spy(testPersistentEvent.taskStart).was.called_with(testPersistentEvent, pCreatureObject)
				end)
			end)
		end)

		describe("finish", function()
			local realTaskFinish

			setup(function()
				realTaskFinish = testPersistentEvent.taskFinish
			end)

			teardown(function()
				testPersistentEvent.taskFinish = realTaskFinish
			end)

			before_each(function()
				testPersistentEvent.taskFinish = spy.new(function() return true end)
				creatureObject.getScreenPlayState = spy.new(function() return TASK_STARTED end)
			end)

			describe("When called with a player", function()
				it("Should call the private taskFinish function.", function()
					testPersistentEvent:finish(pCreatureObject)

					assert.spy(testPersistentEvent.taskFinish).was.called_with(testPersistentEvent, pCreatureObject)
				end)
			end)
		end)
	end)

	describe("Event handlers", function()
		describe("handleEvent", function()
			describe("When called with a player", function()
				it("Should generate an error.", function()
					local callFunctionWithErrors = function() testPersistentEvent:handleEvent(pCreatureObject) end

					assert.has.errors(callFunctionWithErrors)
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
					testPersistentEvent:taskStart(pCreatureObject)

					assert.spy(createEvent).was.called_with(true, eventTime, testPersistentEvent.handlerName, testPersistentEvent.handlerFunction, pCreatureObject)
				end)
			end)
		end)
	end)
end)
