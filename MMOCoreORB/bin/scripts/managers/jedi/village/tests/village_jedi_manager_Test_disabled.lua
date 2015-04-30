local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local GlowingMocks = require("managers.jedi.village.mocks.glowing_mocks")
local VillageJediManager = require("managers.jedi.village.village_jedi_manager")
local VillageJediManagerHolocronMocks = require("managers.jedi.village.mocks.village_jedi_manager_holocron_mocks")
local SithShadowEncounterMocks = require("managers.jedi.village.mocks.sith_shadow_encounter_mocks")
local SithShadowIntroTheaterMocks = require("managers.jedi.village.mocks.sith_shadow_intro_theater_mocks")

describe("Village Jedi Manager", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local pSceneObject = { "sceneObjectPointer" }
	local creatureObject
	local playerObject

	setup(function()
		DirectorManagerMocks.mocks.setup()
		GlowingMocks.mocks.setup()
		VillageJediManagerHolocronMocks.setup()
		SithShadowEncounterMocks.mocks.setup()
		SithShadowIntroTheaterMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
		GlowingMocks.mocks.teardown()
		VillageJediManagerHolocronMocks.teardown()
		SithShadowEncounterMocks.mocks.teardown()
		SithShadowIntroTheaterMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()
		GlowingMocks.mocks.before_each()
		VillageJediManagerHolocronMocks.before_each()
		SithShadowEncounterMocks.mocks.before_each()
		SithShadowIntroTheaterMocks.mocks.before_each()

		creatureObject = {}
		creatureObject.sendSystemMessage = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

		playerObject = {}
		playerObject.hasBadge = spy.new(function() return false end)
		DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject
	end)

	describe("Interface functions", function()
		describe("useItem", function()
			describe("When called with holocron and creature object", function()
				it("Should call the useHolocron function in the VillageJediManagerHolocron", function()
					VillageJediManager:useItem(pSceneObject, ITEMHOLOCRON, pCreatureObject)

					assert.spy(VillageJediManagerHolocron.useHolocron).was.called_with(pSceneObject, pCreatureObject)
				end)
			end)

			describe("When called with a waypoint datapad and creature object", function()
				it("Should call the useWaypointDatapad function in the SithShadowEncounter", function()
					VillageJediManager:useItem(pSceneObject, ITEMWAYPOINTDATAPAD, pCreatureObject)

					assert.spy(SithShadowEncounterMocks.useWaypointDatapad).was.called_with(SithShadowEncounterMocks, pSceneObject, pCreatureObject)
				end)
			end)

			describe("When called with a theater datapad and creature object", function()
				it("Should call the useTheaterDatapad function in the SithShadowIntroTheater", function()
					VillageJediManager:useItem(pSceneObject, ITEMTHEATERDATAPAD, pCreatureObject)

					assert.spy(SithShadowIntroTheaterMocks.useTheaterDatapad).was.called_with(SithShadowIntroTheaterMocks, pSceneObject, pCreatureObject)
				end)
			end)
		end)

		describe("checkForceStatusCommand", function()
			it("Should call checkForceStatusCommand in the glowing module.", function()
				VillageJediManager:checkForceStatusCommand(pCreatureObject)

				assert.spy(GlowingMocks.checkForceStatusCommand).was.called_with(GlowingMocks.realObject, pCreatureObject)
			end)
		end)

		describe("onPlayerLoggedIn", function()
			describe("When called with a player as argument", function()
				it("Should call the onPlayerLoggedIn function in the Glowing module with the player as argument.", function()
					VillageJediManager:onPlayerLoggedIn(pCreatureObject)

					assert.spy(GlowingMocks.onPlayerLoggedIn).was.called_with(GlowingMocks.realObject, pCreatureObject)
				end)
			end)
		end)
	end)

	describe("Private functions", function()
	end)
end)
