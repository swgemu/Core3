registerScreenPlay = spy.new(function() end)

package.path = package.path .. ";scripts/managers/jedi/village/?.lua"
require("village_jedi_manager")

describe("Village Jedi Manager", function()
	describe("Interface functions", function()
		describe("useHolocron", function()
			describe("When called with holocron and creature object", function()
				it("Should call the useHolocron function in the VillageJediManagerHolocron", function()
					local pCreatureObject = { "creatureObjectPointer" }
					local pSceneObject = { "sceneObjectPointer" }
					local realUseHolocron = VillageJediManagerHolocron.useHolocron
					VillageJediManagerHolocron.useHolocron = spy.new(function() end)

					VillageJediManager:useHolocron(pSceneObject, pCreatureObject)

					assert.spy(VillageJediManagerHolocron.useHolocron).was.called_with(pSceneObject, pCreatureObject)

					VillageJediManagerHolocron.useHolocron = realUseHolocron
				end)
			end)
		end)

		describe("checkForceStatusCommand", function()
			it("Should call getJediProgressionStatus and send the appropriate string id to the player", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local sendSystemMessageSpy = spy.new(function() end)
				local creatureObject = { sendSystemMessage = sendSystemMessageSpy }
				local realWithCreatureObject = VillageJediManager.withCreatureObject
				VillageJediManager.withCreatureObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject)
				end)
				local realGetJediProgressionStatus = VillageJediManager.getJediProgressionStatus
				VillageJediManager.getJediProgressionStatus = spy.new(function() return 2 end)

				VillageJediManager:checkForceStatusCommand(pCreatureObject)

				assert.spy(VillageJediManager.withCreatureObject).was.called(1)
				assert.spy(VillageJediManager.getJediProgressionStatus).was.called_with(pCreatureObject)
				assert.spy(sendSystemMessageSpy).was.called_with(creatureObject, "@jedi_spam:fs_progress_2")

				VillageJediManager.withCreatureObject = realWithCreatureObject
				VillageJediManager.getJediProgressionStatus = realGetJediProgressionStatus
			end)
		end)

		describe("onPlayerLoggedIn", function()
			describe("When called with a player as argument", function()
				it("Should check and handle the jedi progression of the player", function()
					local pCreatureObject = { "creatureObjectPointer" }
					local realCheckAndHandleJediProgression = VillageJediManager.checkAndHandleJediProgression
					VillageJediManager.checkAndHandleJediProgression = spy.new(function() end)
					local realRegisterObservers = VillageJediManager.registerObservers
					VillageJediManager.registerObservers = spy.new(function() end)

					VillageJediManager:onPlayerLoggedIn(pCreatureObject)

					assert.spy(VillageJediManager.checkAndHandleJediProgression).was.called_with(pCreatureObject)

					VillageJediManager.checkAndHandleJediProgression = realCheckAndHandleJediProgression
					VillageJediManager.registerObservers = realRegisterObservers
				end)

				it("Should register observers on the player", function()
					local pCreatureObject = { "creatureObjectPointer" }
					local realCheckAndHandleJediProgression = VillageJediManager.checkAndHandleJediProgression
					VillageJediManager.checkAndHandleJediProgression = spy.new(function() end)
					local realRegisterObservers = VillageJediManager.registerObservers
					VillageJediManager.registerObservers = spy.new(function() end)

					VillageJediManager:onPlayerLoggedIn(pCreatureObject)

					assert.spy(VillageJediManager.registerObservers).was.called_with(pCreatureObject)

					VillageJediManager.checkAndHandleJediProgression = realCheckAndHandleJediProgression
					VillageJediManager.registerObservers = realRegisterObservers
				end)
			end)
		end)
	end)

	describe("Private functions", function()
		describe("countBadgesInListToUpperLimit", function()
			it("Should check if the player has each badge number in the list", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local list = { 1, 2, 3, 4 }
				local currentListItem = 0
				local hasBadgeSpy = spy.new(function(playerObject, badgeNumber)
					currentListItem = currentListItem + 1
					return badgeNumber == list[currentListItem] 
				end)
				local playerObject = { hasBadge = hasBadgeSpy }
				local realWithCreaturePlayerObject = VillageJediManager.withCreaturePlayerObject
				VillageJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(playerObject)
				end)

				assert.is.same(VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, list, 10), 4)

				assert.spy(hasBadgeSpy).was.called(4)
				assert.spy(VillageJediManager.withCreaturePlayerObject).was.called(1)

				VillageJediManager.withCreaturePlayerObject = realWithCreaturePlayerObject
			end)

			it("Should return the correct number of badges that the player has", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local list = { 1, 2, 3, 4 }
				local hasBadgeSpy = spy.new(function(playerObject, badgeNumber) 
					return badgeNumber < 3 
				end)
				local playerObject = { hasBadge = hasBadgeSpy }
				local realWithCreaturePlayerObject = VillageJediManager.withCreaturePlayerObject
				VillageJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(playerObject)
				end)

				assert.is.same(VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, list, 10), 2)

				assert.spy(hasBadgeSpy).was.called(4)
				assert.spy(VillageJediManager.withCreaturePlayerObject).was.called(1)

				VillageJediManager.withCreaturePlayerObject = realWithCreaturePlayerObject
			end)

			it("Should abort the counting early if upper limit is reached", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local list = { 1, 2, 3, 4 }
				local hasBadgeSpy = spy.new(function(playerObject, badgeNumber) 
					return badgeNumber < 4 
				end)
				local playerObject = { hasBadge = hasBadgeSpy }
				local realWithCreaturePlayerObject = VillageJediManager.withCreaturePlayerObject
				VillageJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(playerObject)
				end)

				assert.is.same(VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, list, 2), 2)

				assert.spy(hasBadgeSpy).was.called(2)
				assert.spy(VillageJediManager.withCreaturePlayerObject).was.called(1)

				VillageJediManager.withCreaturePlayerObject = realWithCreaturePlayerObject
			end)
		end)

		describe("countBadges", function()
			it("Should call the countBadgesInListToUpperLimit five times with correct arguments", function()
				local pCreatureObject = { "creatureObjectPointer" }
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
				local pCreatureObject = { "creatureObjectPointer" }
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
				local pCreatureObject = { "creatureObjectPointer" }
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
					local pCreatureObject = { "creatureObjectPointer" }
					local realCreateObserver = createObserver
					createObserver = spy.new(function() end)

					VillageJediManager.registerObservers(pCreatureObject)

					assert.spy(createObserver).was.called_with(BADGEAWARDED, "VillageJediManager", "badgeAwardedEventHandler", pCreatureObject)

					createObserver = realCreateObserver
				end)
			end)
		end)

		describe("checkAndHandleJediProgression", function()
			describe("When player has all the needed badges", function()
				it("Should create an event to spawn the old man", function()
					local pCreatureObject = { "creatureObjectPointer" }
					local realCreateSpawnOldManEvent = OldMan.createSpawnOldManEvent
					OldMan.createSpawnOldManEvent = spy.new(function() end)
					local realCountBadges = VillageJediManager.countBadges
					VillageJediManager.countBadges = spy.new(function() return TOTALNUMBEROFBADGESREQUIRED end)

					VillageJediManager.checkAndHandleJediProgression(pCreatureObject)

					assert.spy(VillageJediManager.countBadges).was.called(1)
					assert.spy(OldMan.createSpawnOldManEvent).was.called_with(pCreatureObject)

					OldMan.createSpawnOldManEvent = realCreateSpawnOldManEvent
					VillageJediManager.countBadges = realCountBadges
				end)
			end)

			describe("When player does not have all the needed badges", function()
				it("Should not create an event to spawn the old man", function()
					local pCreatureObject = { "creatureObjectPointer" }
					local realCreateOldManEvent = VillageJediManager.createOldManEvent
					VillageJediManager.createOldManEvent = spy.new(function() end)
					local realCountBadges = VillageJediManager.countBadges
					VillageJediManager.countBadges = spy.new(function() return TOTALNUMBEROFBADGESREQUIRED - 1 end)

					VillageJediManager.checkAndHandleJediProgression(pCreatureObject)

					assert.spy(VillageJediManager.countBadges).was.called(1)
					assert.spy(VillageJediManager.createOldManEvent).was.not_called()

					VillageJediManager.createOldManEvent = realCreateOldManEvent
					VillageJediManager.countBadges = realCountBadges
				end)
			end)
		end)
	end)
end)
