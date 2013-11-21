local Task = require("quest.tasks.task")
local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")

local testTaskName = "testTask"
local TASK_SCREEN_PLAY_STARTED = 0xABCD

describe("Task", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local creatureObject

	setup(function()
		Task.taskName = testTaskName
		DirectorManagerMocks.mocks.setup()

		Task.exposePrivateFunctions()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()

		Task.hidePrivateFunctions()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()

		Task.taskStart = spy.new(function() end)
		Task.taskFinish = spy.new(function() end)

		creatureObject = {}
		creatureObject.getScreenPlayState = spy.new(function() return false end)
		creatureObject.removeScreenPlayState = spy.new(function() end)
		creatureObject.setScreenPlayState = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject
	end)

	describe("Interface functions", function()
		describe("start", function()
			describe("When called with a player", function()
				local realHasTaskStarted
				local realSetTaskStarted

				setup(function()
					realHasTaskStarted = Task.private.hasTaskStarted
					realSetTaskStarted = Task.private.setTaskStarted
				end)

				teardown(function()
					Task.private.hasTaskStarted = realHasTaskStarted
					Task.private.setTaskStarted = realSetTaskStarted
				end)

				before_each(function()
					Task.private.hasTaskStarted = spy.new(function() return false end)
					Task.private.setTaskStarted = spy.new(function() end)
				end)

				it("Should check if the player has the task started.", function()
					Task.start(pCreatureObject)

					assert.spy(Task.private.hasTaskStarted).was.called_with(pCreatureObject)
				end)

				describe("and the player do not have the task started.", function()
					it("Should set the task started on the player.", function()
						Task.start(pCreatureObject)

						assert.spy(Task.private.setTaskStarted).was.called_with(pCreatureObject)
					end)

					it("Should call the taskStart function.", function()
						Task.start(pCreatureObject)

						assert.spy(Task.taskStart).was.called_with(pCreatureObject)
					end)
				end)

				describe("and the player have already started the task.", function()
					before_each(function()
						Task.private.hasTaskStarted = spy.new(function() return true end)
					end)

					it("Should not set the task started on the player.", function()
						Task.start(pCreatureObject)

						assert.spy(Task.private.setTaskStarted).was.not_called()
					end)

					it("Should not call the taskStart function.", function()
						Task.start(pCreatureObject)

						assert.spy(Task.taskStart).was.not_called()
					end)
				end)
			end)
		end)

		describe("finish", function()
			describe("When called with a player", function()
				local realHasTaskStarted
				local realSetTaskFinished

				setup(function()
					realHasTaskStarted = Task.private.hasTaskStarted
					realSetTaskFinished = Task.private.setTaskFinished
				end)

				teardown(function()
					Task.private.hasTaskStarted = realHasTaskStarted
					Task.private.setTaskFinished = realSetTaskFinished
				end)

				before_each(function()
					Task.private.hasTaskStarted = spy.new(function() return false end)
					Task.private.setTaskFinished = spy.new(function() end)
				end)

				it("Should check if the player has the task started.", function()
					Task.finish(pCreatureObject)

					assert.spy(Task.private.hasTaskStarted).was.called_with(pCreatureObject)
				end)

				describe("and the player have started the task.", function()
					before_each(function()
						Task.private.hasTaskStarted = spy.new(function() return true end)
					end)

					it("Should set the task finished on the player.", function()
						Task.finish(pCreatureObject)

						assert.spy(Task.private.setTaskFinished).was.called_with(pCreatureObject)
					end)

					it("Should call the taskFinish function.", function()
						Task.finish(pCreatureObject)

						assert.spy(Task.taskFinish).was.called_with(pCreatureObject)
					end)
				end)

				describe("and the player do not have the task started.", function()
					it("Should not set the task finished on the player.", function()
						Task.finish(pCreatureObject)

						assert.spy(Task.private.setTaskFinished).was.not_called()
					end)

					it("Should not call the taskFinish function.", function()
						Task.finish(pCreatureObject)

						assert.spy(Task.taskFinish).was.not_called()
					end)
				end)
			end)
		end)
	end)

	describe("Private functions", function()
		describe("hasTaskStarted", function()
			describe("When called with a player", function()
				it("Should check if the player has a screen play state with the task name set.", function()
					Task.private.hasTaskStarted(pCreatureObject)

					assert.spy(creatureObject.getScreenPlayState).was.called_with(creatureObject, testTaskName)
				end)

				describe("and the screen play state is set", function()
					it("Should return true.", function()
						creatureObject.getScreenPlayState = spy.new(function() return TASK_SCREEN_PLAY_STARTED end)

						assert.is_true(Task.private.hasTaskStarted(pCreatureObject))
					end)
				end)

				describe("and the screen play state is not set", function()
					it("Should return false.", function()
						assert.is_false(Task.private.hasTaskStarted(pCreatureObject))
					end)
				end)
			end)

			describe("When called with nil as argument", function()
				it("Should return false", function()
					assert.is_false(Task.private.hasTaskStarted(pCreatureObject))
				end)
			end)
		end)

		describe("setTaskStarted", function()
			describe("When called with a player", function()
				it("Should set the screen play to the task started value on the player.", function()
					Task.private.setTaskStarted(pCreatureObject)

					assert.spy(creatureObject.setScreenPlayState).was.called_with(creatureObject, TASK_SCREEN_PLAY_STARTED, testTaskName)
				end)
			end)
		end)

		describe("setTaskFinished", function()
			describe("When called with a player and a value", function()
				it("Should remove the task started value on the screen play state on the player.", function()
					Task.private.setTaskFinished(pCreatureObject)

					assert.spy(creatureObject.removeScreenPlayState).was.called_with(creatureObject, TASK_SCREEN_PLAY_STARTED, testTaskName)
				end)
			end)
		end)
	end)
end)
