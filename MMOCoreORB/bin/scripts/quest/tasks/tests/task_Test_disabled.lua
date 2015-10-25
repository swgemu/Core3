local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local Task = require("quest.tasks.task")

local testTaskName = "testTask"
local TASK_SCREEN_PLAY_STARTED = 0xABCD

local testTask = Task:new {
	taskName = "testTask",
	taskStart = spy.new(function() return true end),
	taskFinish = spy.new(function() return true end)
}

describe("Task", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local creatureObject
	local realTaskName

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
		local realHasTaskStarted
		local realSetTaskStarted
		local realSetTaskFinished
		local realCallFunctionIfNotNil

		setup(function()
			realHasTaskStarted = testTask.hasTaskStarted
			realSetTaskStarted = testTask.setTaskStarted
			realSetTaskFinished = testTask.setTaskFinished
			realCallFunctionIfNotNil = testTask.callFunctionIfNotNil
		end)

		teardown(function()
			testTask.hasTaskStarted = realHasTaskStarted
			testTask.setTaskStarted = realSetTaskStarted
			testTask.setTaskFinished = realSetTaskFinished
			testTask.callFunctionIfNotNil = realCallFunctionIfNotNil
		end)

		before_each(function()
			testTask.hasTaskStarted = spy.new(function() return false end)
			testTask.setTaskStarted = spy.new(function() end)
			testTask.setTaskFinished = spy.new(function() end)
			testTask.callFunctionIfNotNil = spy.new(function() return false end)
		end)

		describe("start", function()
			describe("When called with a player", function()
				it("Should check if the player has the task started.", function()
					testTask:start(pCreatureObject)

					assert.spy(testTask.hasTaskStarted).was.called_with(testTask, pCreatureObject)
				end)

				describe("and the player do not have the task started.", function()
					it("Should call the taskStart function.", function()
						testTask:start(pCreatureObject)

						assert.spy(testTask.callFunctionIfNotNil).was.called_with(testTask, testTask.taskStart, true, pCreatureObject)
					end)

					describe("and the taskStart function returns true", function()
						before_each(function()
							testTask.callFunctionIfNotNil = spy.new(function() return true end)
						end)

						it("Should set the task started on the player.", function()
							testTask:start(pCreatureObject)

							assert.spy(testTask.setTaskStarted).was.called_with(testTask, pCreatureObject)
						end)
					end)

					describe("and the taskStart function returns false", function()
						it("Should not set the task started on the player.", function()
							testTask:start(pCreatureObject)

							assert.spy(testTask.setTaskStarted).was.not_called()
						end)
					end)
				end)

				describe("and the player have already started the task.", function()
					before_each(function()
						testTask.hasTaskStarted = spy.new(function() return true end)
					end)

					it("Should not set the task started on the player.", function()
						testTask:start(pCreatureObject)

						assert.spy(testTask.setTaskStarted).was.not_called()
					end)

					it("Should not call the taskStart function.", function()
						testTask:start(pCreatureObject)

						assert.spy(testTask.callFunctionIfNotNil).was.not_called()
					end)
				end)
			end)
		end)

		describe("finish", function()
			describe("When called with a player", function()
				it("Should check if the player has the task started.", function()
					testTask:finish(pCreatureObject)

					assert.spy(testTask.hasTaskStarted).was.called_with(testTask, pCreatureObject)
				end)

				describe("and the player have started the task.", function()
					before_each(function()
						testTask.hasTaskStarted = spy.new(function() return true end)
					end)

					it("Should call the taskFinish function.", function()
						testTask:finish(pCreatureObject)

						assert.spy(testTask.callFunctionIfNotNil).was.called_with(testTask, testTask.taskFinish, true, pCreatureObject)
					end)

					describe("and taskFinish returns true", function()
						before_each(function()
							testTask.callFunctionIfNotNil = spy.new(function() return true end)
						end)

						it("Should set the task finished on the player.", function()
							testTask:finish(pCreatureObject)

							assert.spy(testTask.setTaskFinished).was.called_with(testTask, pCreatureObject)
						end)
					end)

					describe("and taskFinish returns false", function()
						it("Should not set the task finished on the player.", function()
							testTask:finish(pCreatureObject)

							assert.spy(testTask.setTaskFinished).was.not_called()
						end)
					end)
				end)

				describe("and the player do not have the task started.", function()
					it("Should not set the task finished on the player.", function()
						testTask:finish(pCreatureObject)

						assert.spy(testTask.setTaskFinished).was.not_called()
					end)

					it("Should not call the taskFinish function.", function()
						testTask:finish(pCreatureObject)

						assert.spy(testTask.callFunctionIfNotNil).was.not_called()
					end)
				end)
			end)
		end)
	end)

	describe("Private functions", function()
		describe("hasTaskStarted", function()
			describe("When called with a player", function()
				it("Should check if the player has a screen play state with the task name set.", function()
					testTask:hasTaskStarted(pCreatureObject)

					assert.spy(creatureObject.getScreenPlayState).was.called_with(creatureObject, testTask.taskName)
				end)

				describe("and the screen play state is set", function()
					it("Should return true.", function()
						creatureObject.getScreenPlayState = spy.new(function() return TASK_SCREEN_PLAY_STARTED end)

						assert.is_true(testTask:hasTaskStarted(pCreatureObject))
					end)
				end)

				describe("and the screen play state is not set", function()
					it("Should return false.", function()
						assert.is_false(testTask:hasTaskStarted(pCreatureObject))
					end)
				end)
			end)

			describe("When called with nil as argument", function()
				it("Should return false", function()
					assert.is_false(testTask:hasTaskStarted(pCreatureObject))
				end)
			end)
		end)

		describe("setTaskStarted", function()
			describe("When called with a player", function()
				it("Should set the screen play to the task started value on the player.", function()
					testTask:setTaskStarted(pCreatureObject)

					assert.spy(creatureObject.setScreenPlayState).was.called_with(creatureObject, TASK_SCREEN_PLAY_STARTED, testTask.taskName)
				end)
			end)
		end)

		describe("setTaskFinished", function()
			describe("When called with a player and a value", function()
				it("Should remove the task started value on the screen play state on the player.", function()
					testTask:setTaskFinished(pCreatureObject)

					assert.spy(creatureObject.removeScreenPlayState).was.called_with(creatureObject, TASK_SCREEN_PLAY_STARTED, testTask.taskName)
				end)
			end)
		end)

		describe("callFunctionIfNotNil", function()
			describe("When called with a function and an argument", function()
				it("Should call the function with the argument.", function()
					local theFunction = spy.new(function() end)

					testTask:callFunctionIfNotNil(theFunction, nil, pCreatureObject)

					assert.spy(theFunction).was.called_with(testTask, pCreatureObject)
				end)

				it("Should return what the function returns.", function()
					local returnValue = { "returnValue" }
					local theFunction = spy.new(function() return returnValue end)

					assert.same(returnValue, testTask:callFunctionIfNotNil(theFunction, nil, pCreatureObject))
				end)
			end)

			describe("When called with the function equal to nil", function()
				it("Should return the nil return value.", function()
					local returnValue = { "returnValue" }

					assert.same(returnValue, testTask:callFunctionIfNotNil(nil, returnValue, pCreatureObject))
				end)
			end)
		end)
	end)
end)
