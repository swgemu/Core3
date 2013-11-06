registerScreenPlay = spy.new(function() end)

package.path = package.path .. ";scripts/managers/jedi/village/?.lua;scripts/managers/jedi/village/mocks?.lua;scripts/screenplays/mocks/?.lua"
require("village_jedi_manager")
local DirectorManagerMocks = require("director_manager_mocks")
local OldManMocks = require("old_man_mocks")
local VillageJediManagerHolocronMocks = require("village_jedi_manager_holocron_mocks")

describe("Village Jedi Manager", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local pSceneObject = { "sceneObjectPointer" }
	local creatureObject
	local playerObject

	setup(function()
		DirectorManagerMocks.setup()
		OldManMocks.setup()
		VillageJediManagerHolocronMocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.teardown()
		OldManMocks.teardown()
		VillageJediManagerHolocronMocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.before_each()
		OldManMocks.before_each()
		VillageJediManagerHolocronMocks.before_each()

		creatureObject = {}
		creatureObject.getPlayerObject = spy.new(function() return pPlayerObject end)
		creatureObject.hasScreenPlayState = spy.new(function() return false end)
		creatureObject.sendSystemMessage = spy.new(function() end)
		creatureObject.setScreenPlayState = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

		playerObject = {}
		playerObject.hasBadge = spy.new(function() return false end)
		DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject
	end)

	describe("Interface functions", function()
		describe("useHolocron", function()
			describe("When called with holocron and creature object", function()
				it("Should call the useHolocron function in the VillageJediManagerHolocron", function()
					VillageJediManager:useHolocron(pSceneObject, pCreatureObject)

					assert.spy(VillageJediManagerHolocron.useHolocron).was.called_with(pSceneObject, pCreatureObject)
				end)
			end)
		end)

		describe("checkForceStatusCommand", function()
			it("Should call getJediProgressionStatus and send the appropriate string id to the player", function()
				local realGetJediProgressionStatus = VillageJediManager.getJediProgressionStatus
				VillageJediManager.getJediProgressionStatus = spy.new(function() return 2 end)

				VillageJediManager:checkForceStatusCommand(pCreatureObject)

				assert.spy(VillageJediManager.getJediProgressionStatus).was.called_with(pCreatureObject)
				assert.spy(creatureObject.sendSystemMessage).was.called_with(creatureObject, "@jedi_spam:fs_progress_2")

				VillageJediManager.getJediProgressionStatus = realGetJediProgressionStatus
			end)
		end)

		describe("onPlayerLoggedIn", function()
			local realCheckAndHandleJediProgression
			local realRegisterObservers

			setup(function()
				realCheckAndHandleJediProgression = VillageJediManager.checkAndHandleJediProgression
				realRegisterObservers = VillageJediManager.registerObservers
			end)

			teardown(function()
				VillageJediManager.checkAndHandleJediProgression = realCheckAndHandleJediProgression
				VillageJediManager.registerObservers = realRegisterObservers
			end)

			before_each(function()
				VillageJediManager.checkAndHandleJediProgression = spy.new(function() end)
				VillageJediManager.registerObservers = spy.new(function() end)
			end)

			describe("When called with a player as argument", function()
				it("Should check and handle the jedi progression of the player", function()
					VillageJediManager:onPlayerLoggedIn(pCreatureObject)

					assert.spy(VillageJediManager.checkAndHandleJediProgression).was.called_with(pCreatureObject)
				end)

				it("Should register observers on the player", function()
					VillageJediManager:onPlayerLoggedIn(pCreatureObject)

					assert.spy(VillageJediManager.registerObservers).was.called_with(pCreatureObject)
				end)
			end)
		end)

		describe("setJediProgressionScreenPlayState", function()
			describe("When called with a player and a state", function()
				it("Should write the state to the village jedi progression screen play state.", function()
					VillageJediManager.setJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE)

					assert.spy(creatureObject.setScreenPlayState).was.called_with(creatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING)
				end)
			end)

			describe("When called with the player pointer equal to nil", function()
				it("Should not write the state to the village jedi progression screen play state.", function()
					VillageJediManager.setJediProgressionScreenPlayState(nil, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE)

					assert.spy(creatureObject.setScreenPlayState).was.not_called()
				end)
			end)
		end)

		describe("hasJediProgressionScreenPlayState", function()
			describe("When called with a player and a state", function()
				it("Should check if the player has the screen play state.", function()
					VillageJediManager.hasJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE)

					assert.spy(creatureObject.hasScreenPlayState).was.called_with(creatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING)
				end)

				it("Should return true if the player has the screen play state.", function()
					creatureObject.hasScreenPlayState = spy.new(function() return true end)

					assert.same(true, VillageJediManager.hasJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE))
				end)

				it("Should return false if the player does not have the screen play state.", function()
					assert.same(false, VillageJediManager.hasJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE))
				end)
			end)

			describe("When called with the player pointer equal to nil", function()
				it("Should return false.", function()
					assert.same(false, VillageJediManager.hasJediProgressionScreenPlayState(nil, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE))
				end)
			end)
		end)
	end)

	describe("Private functions", function()
		describe("countBadgesInListToUpperLimit", function()
			local list = { 1, 2, 3, 4 }
			local currentListItem = 0

			before_each(function()
				currentListItem = 0
			end)

			it("Should check if the player has each badge number in the list", function()
				playerObject.hasBadge = spy.new(function(playerObject, badgeNumber)
					currentListItem = currentListItem + 1
					return badgeNumber == list[currentListItem]
				end)

				assert.is.same(VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, list, 10), 4)

				assert.spy(playerObject.hasBadge).was.called(4)
			end)

			it("Should return the correct number of badges that the player has", function()
				playerObject.hasBadge = spy.new(function(playerObject, badgeNumber)
					return badgeNumber < 3
				end)

				assert.is.same(VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, list, 10), 2)

				assert.spy(playerObject.hasBadge).was.called(4)
			end)

			it("Should abort the counting early if upper limit is reached", function()
				playerObject.hasBadge = spy.new(function(playerObject, badgeNumber)
					return badgeNumber < 4
				end)

				assert.is.same(VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, list, 2), 2)

				assert.spy(playerObject.hasBadge).was.called(2)
			end)
		end)

		describe("countBadges", function()
			it("Should call the countBadgesInListToUpperLimit five times with correct arguments", function()
				local argumentList = {
					{ PROFESSIONBADGES, 1, false },
					{ JEDIBADGES, 3, false },
					{ CONTENTBADGES, 5, false },
					{ DIFFICULTBADGES, 3, false },
					{ EASYBADGES, 5, false }
				}
				local realCountBadgesInListToUpperLimit = VillageJediManager.countBadgesInListToUpperLimit
				VillageJediManager.countBadgesInListToUpperLimit = spy.new(function(pCO, l, n)
					for i = 1, table.getn(argumentList), 1 do
						if argumentList[i][1] == l and argumentList[i][2] == n and pCO == pCreatureObject then
							argumentList[i][3] = true
						end
					end
					return 0
				end)

				assert.is.same(VillageJediManager.countBadges(pCreatureObject), 0)

				assert.is.same(argumentList[1][3] and argumentList[2][3] and argumentList[3][3] and argumentList[4][3] and argumentList[5][3], true)
				assert.spy(VillageJediManager.countBadgesInListToUpperLimit).was.called(5)

				VillageJediManager.countBadgesInListToUpperLimit = realCountBadgesInListToUpperLimit
			end)

			it("Should sum the return values from countBadgesInListToUpperLimit", function()
				local returnList = {
					1, 1, 1, 1, 1,
					2, 2, 2, 2, 2,
					3, 3, 3, 3, 3,
					3, 4, 3, 6, 7
				}
				local returnNo = 0
				local realCountBadgesInListToUpperLimit = VillageJediManager.countBadgesInListToUpperLimit
				VillageJediManager.countBadgesInListToUpperLimit = spy.new(function()
					returnNo = returnNo + 1
					return returnList[returnNo]
				end)

				assert.is.same(VillageJediManager.countBadges(pCreatureObject), 5)
				assert.is.same(VillageJediManager.countBadges(pCreatureObject), 10)
				assert.is.same(VillageJediManager.countBadges(pCreatureObject), 15)
				assert.is.same(VillageJediManager.countBadges(pCreatureObject), 23)

				VillageJediManager.countBadgesInListToUpperLimit = realCountBadgesInListToUpperLimit
			end)
		end)

		describe("getJediProgressionStatus", function()
			it("Should return linear values between 0 and 5 depending on the number of counted badges", function()
				local returnValue = -1
				local realCountBadges = VillageJediManager.countBadges
				VillageJediManager.countBadges = spy.new(function()
					returnValue = returnValue + 1
					return returnValue
				end)

				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 1)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 1)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 1)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 2)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 2)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 2)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 2)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 3)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 3)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 3)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 4)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 4)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 4)
				assert.is.same(VillageJediManager.getJediProgressionStatus(pCreatureObject), 5)

				assert.spy(VillageJediManager.countBadges).was.called(18)

				VillageJediManager.countBadges = realCountBadges
			end)
		end)

		describe("registerObservers", function()
			describe("When called with a player object", function()
				it("Should register an observer for the BADGEAWARDED event on the player.", function()
					VillageJediManager.registerObservers(pCreatureObject)

					assert.spy(createObserver).was.called_with(BADGEAWARDED, "VillageJediManager", "badgeAwardedEventHandler", pCreatureObject)
				end)
			end)
		end)

		describe("checkAndHandleJediProgression", function()
			local realCountBadges
			local realSetJediProgressionScreenPlayState

			setup(function()
				realCountBadges = VillageJediManager.countBadges
				realSetJediProgressionScreenPlayState = VillageJediManager.setJediProgressionScreenPlayState
			end)

			teardown(function()
				VillageJediManager.countBadges = realCountBadges
				VillageJediManager.setJediProgressionScreenPlayState = realSetJediProgressionScreenPlayState
			end)

			before_each(function()
				VillageJediManager.countBadges = spy.new(function() return TOTALNUMBEROFBADGESREQUIRED end)
				VillageJediManager.setJediProgressionScreenPlayState = spy.new(function() end)
			end)

			describe("When called with a player as argument", function()
				it("Should count the number of badges the player has towards the jedi progression.", function()
					VillageJediManager.checkAndHandleJediProgression(pCreatureObject)

					assert.spy(VillageJediManager.countBadges).was.called(1)
				end)

				describe("and the player has all the needed badges", function()
					before_each(function()
						VillageJediManager.countBadges = spy.new(function() return TOTALNUMBEROFBADGESREQUIRED end)
					end)

					it("Should set the village jedi progression screen play state glowing on the player", function()
						VillageJediManager.checkAndHandleJediProgression(pCreatureObject)

						assert.spy(VillageJediManager.setJediProgressionScreenPlayState).was.called_with(pCreatureObject, VILLAGE_JEDI_PROGRESSION_GLOWING)
					end)

					it("Should create an event to spawn the old man", function()
						VillageJediManager.checkAndHandleJediProgression(pCreatureObject)

						assert.spy(OldMan.createSpawnOldManEvent).was.called_with(pCreatureObject)
					end)
				end)

				describe("and the player does not have all the needed badges", function()
					it("Should not create an event to spawn the old man", function()
						VillageJediManager.countBadges = spy.new(function() return TOTALNUMBEROFBADGESREQUIRED - 1 end)

						VillageJediManager.checkAndHandleJediProgression(pCreatureObject)

						assert.spy(OldMan.createSpawnOldManEvent).was.not_called()
					end)
				end)
			end)
		end)
	end)
end)
