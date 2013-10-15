registerScreenPlay = spy.new(function() end)

package.path = package.path .. ";scripts/managers/?.lua"
require("village_jedi_manager")

describe("Village Jedi Manager", function()
	describe("Interface functions", function() 
		describe("useHolocron", function()
			it("Should use the holocron if the player is a jedi and does not have max force at the moment", function() 
				local pCreatureObject = { "creatureObjectPointer" }
				local pSceneObject = { "sceneObjectPointer" }
				local realCanUseHolocron = VillageJediManager.canUseHolocron
				local realCanReplenishForce = VillageJediManager.canReplenishForce
				local realUseTheHolocron = VillageJediManager.useTheHolocron
				
				VillageJediManager.canUseHolocron = spy.new(function() return true end)
				VillageJediManager.canReplenishForce = spy.new(function() return true end)
				VillageJediManager.useTheHolocron = spy.new(function() end)

				VillageJediManager:useHolocron(pSceneObject, pCreatureObject)

				assert.spy(VillageJediManager.canUseHolocron).was.called_with(pCreatureObject)
				assert.spy(VillageJediManager.canReplenishForce).was.called_with(pCreatureObject)
				assert.spy(VillageJediManager.useTheHolocron).was.called_with(pSceneObject, pCreatureObject)

				VillageJediManager.canUseHolocron = realCanUseHolocron
				VillageJediManager.canReplenishForce = realCanReplenishForce
				VillageJediManager.useTheHolocron = realUseTheHolocron
			end)

			it("Should send message about not able to replenish force if player is jedi but has full force", function() 
				local pCreatureObject = { "creatureObjectPointer" }
				local pSceneObject = { "sceneObjectPointer" }
				local realCanUseHolocron = VillageJediManager.canUseHolocron
				local realCanReplenishForce = VillageJediManager.canReplenishForce
				local realCannotReplenishForce = VillageJediManager.cannotReplenishForce
				
				VillageJediManager.canUseHolocron = spy.new(function() return true end)
				VillageJediManager.canReplenishForce = spy.new(function() return false end)
				VillageJediManager.cannotReplenishForce = spy.new(function() end)

				VillageJediManager:useHolocron(pSceneObject, pCreatureObject)

				assert.spy(VillageJediManager.canUseHolocron).was.called_with(pCreatureObject)
				assert.spy(VillageJediManager.canReplenishForce).was.called_with(pCreatureObject)
				assert.spy(VillageJediManager.cannotReplenishForce).was.called_with(pCreatureObject)

				VillageJediManager.canUseHolocron = realCanUseHolocron
				VillageJediManager.canReplenishForce = realCanReplenishForce
				VillageJediManager.cannotReplenishForce = realCannotReplenishForce
			end)

			it("Should send message about not being able to use the holocron if player is not jedi", function() 
				local pCreatureObject = { "creatureObjectPointer" }
				local pSceneObject = { "sceneObjectPointer" }
				local realCanUseHolocron = VillageJediManager.canUseHolocron
				local realCannotUseHolocron = VillageJediManager.cannotUseHolocron
				
				VillageJediManager.canUseHolocron = spy.new(function() return false end)
				VillageJediManager.cannotUseHolocron = spy.new(function() end)

				VillageJediManager:useHolocron(pSceneObject, pCreatureObject)

				assert.spy(VillageJediManager.canUseHolocron).was.called_with(pCreatureObject)
				assert.spy(VillageJediManager.cannotUseHolocron).was.called_with(pCreatureObject)

				VillageJediManager.canUseHolocron = realCanUseHolocron
				VillageJediManager.cannotUseHolocron = realCannotUseHolocron
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
		describe("canUseHolocron", function()
			it("Should return false if player is not jedi", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local isJediSpy = spy.new(function() return false end)
				local checkCooldownRecoverySpy = spy.new(function() end)
				local creatureObject = { checkCooldownRecovery = checkCooldownRecoverySpy }
				local playerObject = { isJedi = isJediSpy }
				local realWithCreatureAndPlayerObject = VillageJediManager.withCreatureAndPlayerObject
				VillageJediManager.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)

				assert.is_false(VillageJediManager.canUseHolocron(pCreatureObject))

				assert.spy(isJediSpy).was.called(1)
				assert.spy(checkCooldownRecoverySpy).was.called(0)
				assert.spy(VillageJediManager.withCreatureAndPlayerObject).was.called(1)

				VillageJediManager.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)

			it("Should return false if player has a cooldown for using a holocron", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local isJediSpy = spy.new(function() return true end)
				local checkCooldownRecoverySpy = spy.new(function(name) return true end)
				local creatureObject = { checkCooldownRecovery = checkCooldownRecoverySpy }
				local playerObject = { isJedi = isJediSpy }
				local realWithCreatureAndPlayerObject = VillageJediManager.withCreatureAndPlayerObject
				VillageJediManager.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)

				assert.is_false(VillageJediManager.canUseHolocron(pCreatureObject))

				assert.spy(isJediSpy).was.called(1)
				assert.spy(checkCooldownRecoverySpy).was.called_with(creatureObject, USEDHOLOCRON)
				assert.spy(VillageJediManager.withCreatureAndPlayerObject).was.called(1)

				VillageJediManager.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)

			it("Should return true if player does not have a cooldown for using a holocron and is jedi", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local isJediSpy = spy.new(function() return true end)
				local checkCooldownRecoverySpy = spy.new(function(name) return false end)
				local creatureObject = { checkCooldownRecovery = checkCooldownRecoverySpy }
				local playerObject = { isJedi = isJediSpy }
				local realWithCreatureAndPlayerObject = VillageJediManager.withCreatureAndPlayerObject
				VillageJediManager.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)

				assert.is_true(VillageJediManager.canUseHolocron(pCreatureObject))

				assert.spy(isJediSpy).was.called(1)
				assert.spy(checkCooldownRecoverySpy).was.called_with(creatureObject, USEDHOLOCRON)
				assert.spy(VillageJediManager.withCreatureAndPlayerObject).was.called(1)

				VillageJediManager.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)
		end)

		describe("canReplenishForce", function()
			it("Should return false if the player force is at max", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local getForcePowerSpy = spy.new(function() return 23 end)
				local getForcePowerMaxSpy = spy.new(function() return 23 end)
				local playerObject = { getForcePower = getForcePowerSpy, getForcePowerMax = getForcePowerMaxSpy }
				local realGetForcePower = VillageJediManager.getForcePower
				local realGetForcePowerMax = VillageJediManager.getForcePowerMax
				local realWithCreaturePlayerObject = VillageJediManager.withCreaturePlayerObject
				VillageJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(playerObject)
				end)

				assert.is_false(VillageJediManager.canReplenishForce(pCreatureObject))

				assert.spy(getForcePowerSpy).was.called(1)
				assert.spy(getForcePowerMaxSpy).was.called(1)
				assert.spy(VillageJediManager.withCreaturePlayerObject).was.called(1)

				VillageJediManager.withCreaturePlayerObject = realWithCreaturePlayerObject
			end)

			it("Should return false if the player force is not at max", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local getForcePowerSpy = spy.new(function() return 22 end)
				local getForcePowerMaxSpy = spy.new(function() return 23 end)
				local playerObject = { getForcePower = getForcePowerSpy, getForcePowerMax = getForcePowerMaxSpy }
				local realGetForcePower = VillageJediManager.getForcePower
				local realGetForcePowerMax = VillageJediManager.getForcePowerMax
				local realWithCreaturePlayerObject = VillageJediManager.withCreaturePlayerObject
				VillageJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(playerObject)
				end)

				assert.is_true(VillageJediManager.canReplenishForce(pCreatureObject))

				assert.spy(getForcePowerSpy).was.called(1)
				assert.spy(getForcePowerMaxSpy).was.called(1)
				assert.spy(VillageJediManager.withCreaturePlayerObject).was.called(1)

				VillageJediManager.withCreaturePlayerObject = realWithCreaturePlayerObject
			end)
		end)

		describe("useTheHolocron", function()
			it("Should send system message, set force to max, add cooldown and destroy the holocron", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local pSceneObject = { "sceneObjectPointer" }
				local destroyObjectFromWorldSpy = spy.new(function() end)
				local setForcePowerSpy = spy.new(function() end)
				local getForcePowerMaxSpy = spy.new(function() return 23 end)
				local addCooldownSpy = spy.new(function() end)
				local sendSystemMessageSpy = spy.new(function() end)
				local creatureObject = { addCooldown = addCooldownSpy, sendSystemMessage = sendSystemMessageSpy }
				local playerObject = { setForcePower = setForcePowerSpy, getForcePowerMax = getForcePowerMaxSpy }
				local sceneObject = { destroyObjectFromWorld = destroyObjectFromWorldSpy }
				local realWithCreatureAndPlayerObject = VillageJediManager.withCreatureAndPlayerObject
				VillageJediManager.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)
				LuaSceneObject = spy.new(function() return sceneObject end)

				VillageJediManager.useTheHolocron(pSceneObject, pCreatureObject)

				assert.spy(destroyObjectFromWorldSpy).was.called(1)
				assert.spy(setForcePowerSpy).was.called(1)
				assert.spy(sendSystemMessageSpy).was.called(1)
				assert.spy(addCooldownSpy).was.called(1)
				assert.spy(VillageJediManager.withCreatureAndPlayerObject).was.called(1)

				VillageJediManager.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)
		end)

		describe("cannotReplenishForce", function()
			it("Should send a system message to the player about not being able to replenish the force", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local sendSystemMessageSpy = spy.new(function() end)
				local creatureObject = { sendSystemMessage = sendSystemMessageSpy }
				local realWithCreatureObject = VillageJediManager.withCreatureObject
				VillageJediManager.withCreatureObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject)
				end)

				VillageJediManager.cannotReplenishForce(pCreatureObject)

				assert.spy(sendSystemMessageSpy).was.called_with(creatureObject, "@jedi_spam:holocron_force_max")

				VillageJediManager.withCreatureObject = realWithCreatureObject
			end)
		end)

		describe("cannotUseHolocron", function()
			it("Should send a system message to the player about not being able to use the holocron", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local sendSystemMessageSpy = spy.new(function() end)
				local creatureObject = { sendSystemMessage = sendSystemMessageSpy }
				local realWithCreatureObject = VillageJediManager.withCreatureObject
				VillageJediManager.withCreatureObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject)
				end)

				VillageJediManager.cannotUseHolocron(pCreatureObject)

				assert.spy(sendSystemMessageSpy).was.called_with(creatureObject, "@jedi_spam:holocron_no_effect")

				VillageJediManager.withCreatureObject = realWithCreatureObject
			end)
		end)

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
	end)
end)
