local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local Glowing = require("managers.jedi.village.glowing")
local OldManEncounterMocks = require("managers.jedi.village.mocks.old_man_encounter_mocks")
local VillageJediManagerCommonMocks = require("managers.jedi.village.mocks.village_jedi_manager_common_mocks")

local testGlowing = Glowing:new {}

describe("Village Jedi Manager - Glowing", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local creatureObject
	local playerObject

	setup(function()
		DirectorManagerMocks.mocks.setup()
		VillageJediManagerCommonMocks.mocks.setup()
		OldManEncounterMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
		VillageJediManagerCommonMocks.mocks.teardown()
		OldManEncounterMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()
		VillageJediManagerCommonMocks.mocks.before_each()
		OldManEncounterMocks.mocks.before_each()

		creatureObject = {}
		creatureObject.getPlayerObject = spy.new(function() return pPlayerObject end)
		creatureObject.sendSystemMessage = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

		playerObject = {}
		playerObject.hasBadge = spy.new(function() return false end)
		DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject
	end)

	describe("Interface functions", function()
		describe("checkForceStatusCommand", function()
			it("Should call getJediProgressionStatus and send the appropriate string id to the player", function()
				local realGetJediProgressionStatus = testGlowing.getJediProgressionStatus
				testGlowing.getJediProgressionStatus = spy.new(function() return 2 end)

				testGlowing:checkForceStatusCommand(pCreatureObject)

				assert.spy(testGlowing.getJediProgressionStatus).was.called_with(testGlowing, pCreatureObject)
				assert.spy(creatureObject.sendSystemMessage).was.called_with(creatureObject, "@jedi_spam:fs_progress_2")

				testGlowing.getJediProgressionStatus = realGetJediProgressionStatus
			end)
		end)

		describe("onPlayerLoggedIn", function()
			local realIsGlowing
			local realRegisterObservers

			setup(function()
				realIsGlowing = testGlowing.isGlowing
				realRegisterObservers = testGlowing.registerObservers
			end)

			teardown(function()
				testGlowing.isGlowing = realIsGlowing
				testGlowing.registerObservers = realRegisterObservers
			end)

			before_each(function()
				testGlowing.isGlowing = spy.new(function() return false end)
				testGlowing.registerObservers = spy.new(function() end)
			end)

			describe("When called with a player as argument", function()
				it("Should check if the player is glowing or not.", function()
					testGlowing:onPlayerLoggedIn(pCreatureObject)

					assert.spy(testGlowing.isGlowing).was.called_with(testGlowing, pCreatureObject)
				end)

				describe("and the player is glowing", function()
					it("Should not register observers on the player.", function()
						testGlowing.isGlowing = spy.new(function() return true end)

						testGlowing:onPlayerLoggedIn(pCreatureObject)

						assert.spy(testGlowing.registerObservers).was.not_called()
					end)
				end)

				describe("and the player is not glowing", function()
					it("Should register observers on the player.", function()
						testGlowing:onPlayerLoggedIn(pCreatureObject)

						assert.spy(testGlowing.registerObservers).was.called_with(testGlowing, pCreatureObject)
					end)
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

				assert.is.same(testGlowing:countBadgesInListToUpperLimit(pCreatureObject, list, 10), 4)

				assert.spy(playerObject.hasBadge).was.called(4)
			end)

			it("Should return the correct number of badges that the player has", function()
				playerObject.hasBadge = spy.new(function(playerObject, badgeNumber)
					return badgeNumber < 3
				end)

				assert.is.same(testGlowing:countBadgesInListToUpperLimit(pCreatureObject, list, 10), 2)

				assert.spy(playerObject.hasBadge).was.called(4)
			end)

			it("Should abort the counting early if upper limit is reached", function()
				playerObject.hasBadge = spy.new(function(playerObject, badgeNumber)
					return badgeNumber < 4
				end)

				assert.is.same(testGlowing:countBadgesInListToUpperLimit(pCreatureObject, list, 2), 2)

				assert.spy(playerObject.hasBadge).was.called(2)
			end)
		end)

		describe("countBadges", function()
			local realCountBadgesInListToUpperLimit

			setup(function()
				realCountBadgesInListToUpperLimit = testGlowing.countBadgesInListToUpperLimit
			end)

			teardown(function()
				testGlowing.countBadgesInListToUpperLimit = realCountBadgesInListToUpperLimit
			end)

			it("Should call the countBadgesInListToUpperLimit five times with correct arguments", function()
				local argumentList = {
					{ PROFESSIONBADGES, 1, false },
					{ JEDIBADGES, 3, false },
					{ CONTENTBADGES, 5, false },
					{ DIFFICULTBADGES, 2, false },
					{ EASYBADGES, 5, false }
				}

				testGlowing.countBadgesInListToUpperLimit = spy.new(function(self, pCO, l, n)
					for i = 1, table.getn(argumentList), 1 do
						if argumentList[i][1] == l and argumentList[i][2] == n and pCO == pCreatureObject then
							argumentList[i][3] = true
						end
					end
					return 0
				end)

				assert.is.same(testGlowing:countBadges(pCreatureObject), 0)

				assert.is.same(argumentList[1][3] and argumentList[2][3] and argumentList[3][3] and argumentList[4][3] and argumentList[5][3], true)
				assert.spy(testGlowing.countBadgesInListToUpperLimit).was.called(5)
			end)

			it("Should sum the return values from countBadgesInListToUpperLimit", function()
				local returnList = {
					1, 1, 1, 1, 1,
					2, 2, 2, 2, 2,
					3, 3, 3, 3, 3,
					3, 4, 3, 6, 7
				}
				local returnNo = 0

				testGlowing.countBadgesInListToUpperLimit = spy.new(function()
					returnNo = returnNo + 1
					return returnList[returnNo]
				end)

				assert.is.same(testGlowing:countBadges(pCreatureObject), 5)
				assert.is.same(testGlowing:countBadges(pCreatureObject), 10)
				assert.is.same(testGlowing:countBadges(pCreatureObject), 15)
				assert.is.same(testGlowing:countBadges(pCreatureObject), 23)
			end)
		end)

		describe("getJediProgressionStatus", function()
			it("Should return linear values between 0 and 5 depending on the number of counted badges", function()
				local returnValue = -1
				local realCountBadges = testGlowing.countBadges
				testGlowing.countBadges = spy.new(function()
					returnValue = returnValue + 1
					return returnValue
				end)

				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 1)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 1)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 1)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 2)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 2)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 2)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 3)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 3)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 3)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 4)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 4)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 4)
				assert.is.same(testGlowing:getJediProgressionStatus(pCreatureObject), 5)

				assert.spy(testGlowing.countBadges).was.called(17)

				testGlowing.countBadges = realCountBadges
			end)
		end)

		describe("registerObservers", function()
			describe("When called with a player object", function()
				it("Should register an observer for the BADGEAWARDED event on the player.", function()
					testGlowing:registerObservers(pCreatureObject)

					assert.spy(createObserver).was.called_with(BADGEAWARDED, "Glowing", "badgeAwardedEventHandler", pCreatureObject)
				end)
			end)
		end)

		describe("isGlowing", function()
			local realCountBadges

			setup(function()
				realCountBadges = testGlowing.countBadges
			end)

			teardown(function()
				testGlowing.countBadges = realCountBadges
			end)

			before_each(function()
				testGlowing.countBadges = spy.new(function() return TOTALNUMBEROFBADGESREQUIRED end)
			end)

			describe("When called with a player as argument", function()
				it("Should count the number of badges the player has towards the jedi progression.", function()
					testGlowing:isGlowing(pCreatureObject)

					assert.spy(testGlowing.countBadges).was.called(1)
				end)

				describe("and the player has all the needed badges", function()
					before_each(function()
						testGlowing.countBadges = spy.new(function() return TOTALNUMBEROFBADGESREQUIRED end)
					end)

					it("Should set the village jedi progression screen play state glowing on the player.", function()
						testGlowing:isGlowing(pCreatureObject)

						assert.spy(VillageJediManagerCommonMocks.setJediProgressionScreenPlayState).was.called_with(pCreatureObject, VILLAGE_JEDI_PROGRESSION_GLOWING)
					end)

					it("Should start the old man encounter.", function()
						testGlowing:isGlowing(pCreatureObject)

						assert.spy(OldManEncounterMocks.start).was.called_with(OldManEncounterMocks, pCreatureObject)
					end)
				end)

				describe("and the player does not have all the needed badges", function()
					it("Should not start the old man encounter.", function()
						testGlowing.countBadges = spy.new(function() return TOTALNUMBEROFBADGESREQUIRED - 1 end)

						testGlowing:isGlowing(pCreatureObject)

						assert.spy(OldManEncounterMocks.start).was.not_called()
					end)
				end)
			end)
		end)
	end)
end)
