local SithShadowIntroTheater = require("managers.jedi.village.sith_shadow_intro_theater")
local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")

describe("SithShadowIntroTheater", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pSpawnedMobile1 = { "spawnedMobile1Pointer" }
	local pSpawnedMobile2 = { "spawnedMobile2Pointer" }
	local spawnedMobile1
	local spawnedMobile2
	local spawnedMobilesList = { pSpawnedMobile1, pSpawnedMobile2 }

	setup(function()
		DirectorManagerMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()

		spawnedMobile1 = {}
		spawnedMobile1.setFollowObject = spy.new(function() end)
		DirectorManagerMocks.aiAgents[pSpawnedMobile1] = spawnedMobile1

		spawnedMobile2 = {}
		spawnedMobile2.setFollowObject = spy.new(function() end)
		DirectorManagerMocks.aiAgents[pSpawnedMobile2] = spawnedMobile2
	end)

	describe("onEnteredActiveArea", function()
		describe("When a player enters the active area", function()
			it("Should set all spawned sith shadows to attack the player.", function()
				SithShadowIntroTheater:onEnteredActiveArea(pCreatureObject, spawnedMobilesList)

				assert.spy(spawnedMobile1.setFollowObject).was.called_with(spawnedMobile1, pCreatureObject)
				assert.spy(spawnedMobile2.setFollowObject).was.called_with(spawnedMobile2, pCreatureObject)
			end)
		end)
	end)
end)
