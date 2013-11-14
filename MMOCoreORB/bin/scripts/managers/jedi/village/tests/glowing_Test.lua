local Glowing = require("managers.jedi.village.glowing")
local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local OldManMocks = require("managers.jedi.village.mocks.old_man_mocks")
local VillageJediManagerCommonMocks = require("managers.jedi.village.mocks.village_jedi_manager_common_mocks")

describe("Village Jedi Manager - Glowing", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local creatureObject
	local playerObject

	setup(function()
		DirectorManagerMocks.setup()
		VillageJediManagerCommonMocks.mocks.setup()
		OldManMocks.mocks.setup()

		Glowing.exposePrivateFunctions()
	end)

	teardown(function()
		DirectorManagerMocks.teardown()
		VillageJediManagerCommonMocks.mocks.teardown()
		OldManMocks.mocks.teardown()

		Glowing.hidePrivateFunctions()
	end)

	before_each(function()
		DirectorManagerMocks.before_each()
		VillageJediManagerCommonMocks.mocks.before_each()
		OldManMocks.mocks.before_each()

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
				local realGetJediProgressionStatus = Glowing.private.getJediProgressionStatus
				Glowing.private.getJediProgressionStatus = spy.new(function() return 2 end)

				Glowing.checkForceStatusCommand(pCreatureObject)

				assert.spy(Glowing.private.getJediProgressionStatus).was.called_with(pCreatureObject)
				assert.spy(creatureObject.sendSystemMessage).was.called_with(creatureObject, "@jedi_spam:fs_progress_2")

				Glowing.private.getJediProgressionStatus = realGetJediProgressionStatus
			end)
		end)

		describe("onPlayerLoggedIn", function()
			local realIsGlowing
			local realRegisterObservers

			setup(function()
				realIsGlowing = Glowing.private.isGlowing
				realRegisterObservers = Glowing.private.registerObservers
			end)

			teardown(function()
				Glowing.private.isGlowing = realIsGlowing
				Glowing.private.registerObservers = realRegisterObservers
			end)

			before_each(function()
				Glowing.private.isGlowing = spy.new(function() return false end)
				Glowing.private.registerObservers = spy.new(function() end)
			end)

			describe("When called with a player as argument", function()
				it("Should check if the player is glowing or not.", function()
					Glowing.onPlayerLoggedIn(pCreatureObject)

					assert.spy(Glowing.private.isGlowing).was.called_with(pCreatureObject)
				end)

				describe("and the player is glowing", function()
					it("Should not register observers on the player.", function()
						Glowing.private.isGlowing = spy.new(function() return true end)

						Glowing.onPlayerLoggedIn(pCreatureObject)

						assert.spy(Glowing.private.registerObservers).was.not_called()
					end)
				end)

				describe("and the player is not glowing", function()
					it("Should register observers on the player.", function()
						Glowing.onPlayerLoggedIn(pCreatureObject)

						assert.spy(Glowing.private.registerObservers).was.called_with(pCreatureObject)
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

				assert.is.same(Glowing.private.countBadgesInListToUpperLimit(pCreatureObject, list, 10), 4)

				assert.spy(playerObject.hasBadge).was.called(4)
			end)

			it("Should return the correct number of badges that the player has", function()
				playerObject.hasBadge = spy.new(function(playerObject, badgeNumber)
					return badgeNumber < 3
				end)

				assert.is.same(Glowing.private.countBadgesInListToUpperLimit(pCreatureObject, list, 10), 2)

				assert.spy(playerObject.hasBadge).was.called(4)
			end)

			it("Should abort the counting early if upper limit is reached", function()
				playerObject.hasBadge = spy.new(function(playerObject, badgeNumber)
					return badgeNumber < 4
				end)

				assert.is.same(Glowing.private.countBadgesInListToUpperLimit(pCreatureObject, list, 2), 2)

				assert.spy(playerObject.hasBadge).was.called(2)
			end)
		end)

		describe("countBadges", function()
			local realCountBadgesInListToUpperLimit

			setup(function()
				realCountBadgesInListToUpperLimit = Glowing.private.countBadgesInListToUpperLimit
			end)

			teardown(function()
				Glowing.private.countBadgesInListToUpperLimit = realCountBadgesInListToUpperLimit
			end)

			it("Should call the countBadgesInListToUpperLimit five times with correct arguments", function()
				local argumentList = {
					{ PROFESSIONBADGES, 1, false },
					{ JEDIBADGES, 3, false },
					{ CONTENTBADGES, 5, false },
					{ DIFFICULTBADGES, 3, false },
					{ EASYBADGES, 5, false }
				}

				Glowing.private.countBadgesInListToUpperLimit = spy.new(function(pCO, l, n)
					for i = 1, table.getn(argumentList), 1 do
						if argumentList[i][1] == l and argumentList[i][2] == n and pCO == pCreatureObject then
							argumentList[i][3] = true
						end
					end
					return 0
				end)

				assert.is.same(Glowing.private.countBadges(pCreatureObject), 0)

				assert.is.same(argumentList[1][3] and argumentList[2][3] and argumentList[3][3] and argumentList[4][3] and argumentList[5][3], true)
				assert.spy(Glowing.private.countBadgesInListToUpperLimit).was.called(5)
			end)

			it("Should sum the return values from countBadgesInListToUpperLimit", function()
				local returnList = {
					1, 1, 1, 1, 1,
					2, 2, 2, 2, 2,
					3, 3, 3, 3, 3,
					3, 4, 3, 6, 7
				}
				local returnNo = 0

				Glowing.private.countBadgesInListToUpperLimit = spy.new(function()
					returnNo = returnNo + 1
					return returnList[returnNo]
				end)

				assert.is.same(Glowing.private.countBadges(pCreatureObject), 5)
				assert.is.same(Glowing.private.countBadges(pCreatureObject), 10)
				assert.is.same(Glowing.private.countBadges(pCreatureObject), 15)
				assert.is.same(Glowing.private.countBadges(pCreatureObject), 23)
			end)
		end)

		describe("getJediProgressionStatus", function()
			it("Should return linear values between 0 and 5 depending on the number of counted badges", function()
				local returnValue = -1
				local realCountBadges = Glowing.private.countBadges
				Glowing.private.countBadges = spy.new(function()
					returnValue = returnValue + 1
					return returnValue
				end)

				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 0)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 1)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 1)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 1)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 2)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 2)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 2)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 2)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 3)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 3)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 3)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 4)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 4)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 4)
				assert.is.same(Glowing.private.getJediProgressionStatus(pCreatureObject), 5)

				assert.spy(Glowing.private.countBadges).was.called(18)

				Glowing.private.countBadges = realCountBadges
			end)
		end)

		describe("registerObservers", function()
			describe("When called with a player object", function()
				it("Should register an observer for the BADGEAWARDED event on the player.", function()
					Glowing.private.registerObservers(pCreatureObject)

					assert.spy(createObserver).was.called_with(BADGEAWARDED, "Glowing", "badgeAwardedEventHandler", pCreatureObject)
				end)
			end)
		end)

		describe("isGlowing", function()
			local realCountBadges

			setup(function()
				realCountBadges = Glowing.private.countBadges
			end)

			teardown(function()
				Glowing.private.countBadges = realCountBadges
			end)

			before_each(function()
				Glowing.private.countBadges = spy.new(function() return TOTALNUMBEROFBADGESREQUIRED end)
			end)

			describe("When called with a player as argument", function()
				it("Should count the number of badges the player has towards the jedi progression.", function()
					Glowing.private.isGlowing(pCreatureObject)

					assert.spy(Glowing.private.countBadges).was.called(1)
				end)

				describe("and the player has all the needed badges", function()
					before_each(function()
						Glowing.private.countBadges = spy.new(function() return TOTALNUMBEROFBADGESREQUIRED end)
					end)

					it("Should set the village jedi progression screen play state glowing on the player", function()
						Glowing.private.isGlowing(pCreatureObject)

						assert.spy(VillageJediManagerCommonMocks.setJediProgressionScreenPlayState).was.called_with(pCreatureObject, VILLAGE_JEDI_PROGRESSION_GLOWING)
					end)

					it("Should create an event to spawn the old man", function()
						Glowing.private.isGlowing(pCreatureObject)

						assert.spy(OldManMocks.createSpawnOldManEvent).was.called_with(pCreatureObject)
					end)
				end)

				describe("and the player does not have all the needed badges", function()
					it("Should not create an event to spawn the old man", function()
						Glowing.private.countBadges = spy.new(function() return TOTALNUMBEROFBADGESREQUIRED - 1 end)

						Glowing.private.isGlowing(pCreatureObject)

						assert.spy(OldManMocks.createSpawnOldManEvent).was.not_called()
					end)
				end)
			end)
		end)
	end)
end)
