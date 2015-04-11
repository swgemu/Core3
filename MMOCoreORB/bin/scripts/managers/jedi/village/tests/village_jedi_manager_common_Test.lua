local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")

local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")

describe("Village Jedi Manager Common", function()
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
		creatureObject.hasScreenPlayState = spy.new(function() return false end)
		creatureObject.setScreenPlayState = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject
	end)

	describe("Interface functions", function()
		describe("setJediProgressionScreenPlayState", function()
			describe("When called with a player and a state", function()
				it("Should write the state to the village jedi progression screen play state.", function()
					VillageJediManagerCommon.setJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE)

					assert.spy(creatureObject.setScreenPlayState).was.called_with(creatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING)
				end)
			end)

			describe("When called with the player pointer equal to nil", function()
				it("Should not write the state to the village jedi progression screen play state.", function()
					VillageJediManagerCommon.setJediProgressionScreenPlayState(nil, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE)

					assert.spy(creatureObject.setScreenPlayState).was.not_called()
				end)
			end)
		end)

		describe("hasJediProgressionScreenPlayState", function()
			describe("When called with a player and a state", function()
				it("Should check if the player has the screen play state.", function()
					VillageJediManagerCommon.hasJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE)

					assert.spy(creatureObject.hasScreenPlayState).was.called_with(creatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING)
				end)

				it("Should return true if the player has the screen play state.", function()
					creatureObject.hasScreenPlayState = spy.new(function() return true end)

					assert.same(true, VillageJediManagerCommon.hasJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE))
				end)

				it("Should return false if the player does not have the screen play state.", function()
					assert.same(false, VillageJediManagerCommon.hasJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE))
				end)
			end)

			describe("When called with the player pointer equal to nil", function()
				it("Should return false.", function()
					assert.same(false, VillageJediManagerCommon.hasJediProgressionScreenPlayState(nil, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE))
				end)
			end)
		end)
	end)
end)
