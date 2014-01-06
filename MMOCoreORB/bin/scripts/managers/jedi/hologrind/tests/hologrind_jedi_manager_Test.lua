registerScreenPlay = spy.new(function() end)

require("managers.jedi.hologrind.hologrind_jedi_manager")

EXPECTEDNUMBEROFPROFESSIONSTOGRIND = 6
EXPECTEDMAXIMUMNUMBEROFPROFESSIONSTOSHOWWITHHOLOCRON = 4

describe("Hologrind Jedi Manager", function()
	describe("Interface functions", function()
		describe("onPlayerCreated", function()
			it("Should call the add hologrind profession method of the lua player object the defined number of times", function()
				local creaturePointer = {}
				local playerPointer = {}
				addHologrindProfessionSpy = spy.new(function() end)
				local getPlayerObjectSpy = spy.new(function() return playerPointer end)
				local realWithCreaturePlayerObject = HologrindJediManager.withCreaturePlayerObject
				HologrindJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction({ addHologrindProfession = addHologrindProfessionSpy })
				end)

				HologrindJediManager.onPlayerCreated(creaturePointer)

				assert.spy(HologrindJediManager.withCreaturePlayerObject).was.called(1)
				assert.spy(addHologrindProfessionSpy).was.called(EXPECTEDNUMBEROFPROFESSIONSTOGRIND)

				HologrindJediManager.withCreaturePlayerObject = realWithCreaturePlayerObject
			end)
		end)

		describe("onPlayerLoggedIn", function()
			it("Should call the checkIfProgressedToJedi function.", function()
				local creaturePointer = { "creaturePointer" }
				local realCheckIfProgressedToJedi = HologrindJediManager.checkIfProgressedToJedi
				local realRegisterObservers = HologrindJediManager.registerObservers
				HologrindJediManager.checkIfProgressedToJedi = spy.new(function() end)
				HologrindJediManager.registerObservers = spy.new(function() end)

				HologrindJediManager:onPlayerLoggedIn(creaturePointer)

				assert.spy(HologrindJediManager.checkIfProgressedToJedi).was.called_with(creaturePointer)

				HologrindJediManager.checkIfProgressedToJedi = realCheckIfProgressedToJedi
				HologrindJediManager.registerObservers = realRegisterObservers
			end)

			it("Should call the registerObservers function.", function()
				local creaturePointer = { "creaturePointer" }
				local realCheckIfProgressedToJedi = HologrindJediManager.checkIfProgressedToJedi
				local realRegisterObservers = HologrindJediManager.registerObservers
				HologrindJediManager.checkIfProgressedToJedi = spy.new(function() end)
				HologrindJediManager.registerObservers = spy.new(function() end)

				HologrindJediManager:onPlayerLoggedIn(creaturePointer)

				assert.spy(HologrindJediManager.registerObservers).was.called_with(creaturePointer)

				HologrindJediManager.checkIfProgressedToJedi = realCheckIfProgressedToJedi
				HologrindJediManager.registerObservers = realRegisterObservers
			end)
		end)

		describe("useItem", function()
			it("Should call sendHolocronMessage.", function()
				local sceneObjectPointer = { "sceneObjectPointer" }
				local creaturePointer = { "creaturePointer" }
				local realSendHolocronMessage = HologrindJediManager.sendHolocronMessage
				HologrindJediManager.sendHolocronMessage = spy.new(function() end)
				local destroyObjectFromWorldSpy = spy.new(function() end)
				LuaSceneObject = spy.new(function() return { destroyObjectFromWorld = destroyObjectFromWorldSpy } end)

				HologrindJediManager:useItem(sceneObjectPointer, ITEMHOLOCRON, creaturePointer)

				assert.spy(HologrindJediManager.sendHolocronMessage).was.called_with(creaturePointer)

				HologrindJediManager.sendHolocronMessage = realSendHolocronMessage
			end)

			describe("When sendHolocronMessage returns false", function()
				it("Should destroy the holocron.", function()
					local sceneObjectPointer = { "sceneObjectPointer" }
					local creaturePointer = { "creaturePointer" }
					local realSendHolocronMessage = HologrindJediManager.sendHolocronMessage
					HologrindJediManager.sendHolocronMessage = spy.new(function() return false end)
					local destroyObjectFromWorldSpy = spy.new(function() end)
					LuaSceneObject = spy.new(function() return { destroyObjectFromWorld = destroyObjectFromWorldSpy } end)

					HologrindJediManager:useItem(sceneObjectPointer, ITEMHOLOCRON, creaturePointer)

					assert.spy(destroyObjectFromWorldSpy).was.called(1)

					HologrindJediManager.sendHolocronMessage = realSendHolocronMessage
				end)
			end)

			describe("When sendHolocronMessage returns true", function()
				it("Should not destroy the holocron.", function()
					local sceneObjectPointer = { "sceneObjectPointer" }
					local creaturePointer = { "creaturePointer" }
					local realSendHolocronMessage = HologrindJediManager.sendHolocronMessage
					HologrindJediManager.sendHolocronMessage = spy.new(function() return true end)
					local destroyObjectFromWorldSpy = spy.new(function() end)
					LuaSceneObject = spy.new(function() return { destroyObjectFromWorld = destroyObjectFromWorldSpy } end)

					HologrindJediManager:useItem(sceneObjectPointer, ITEMHOLOCRON, creaturePointer)

					assert.spy(destroyObjectFromWorldSpy).was_not.called()

					HologrindJediManager.sendHolocronMessage = realSendHolocronMessage
				end)
			end)
		end)
	end)

	describe("Private functions", function()
		it("Should define the number of professions to master to 6", function()
			assert.same(EXPECTEDNUMBEROFPROFESSIONSTOGRIND, NUMBEROFPROFESSIONSTOMASTER)
		end)
		it("Should define the number of professions to show with a holocron to 4.", function()
			assert.same(EXPECTEDMAXIMUMNUMBEROFPROFESSIONSTOSHOWWITHHOLOCRON, MAXIMUMNUMBEROFPROFESSIONSTOSHOWWITHHOLOCRON)
		end)

		describe("getGrindableProfessionList", function()
			it("Should return a list of at least the number of professions that has to be mastered", function()
				assert.is_true(EXPECTEDNUMBEROFPROFESSIONSTOGRIND <= table.getn(HologrindJediManager.getGrindableProfessionList()))
			end)

			it("Should not modify the size of the grindable profession list when items are removed from it in another function", function()
				local theList = HologrindJediManager.getGrindableProfessionList()
				local firstSize = table.getn(theList)
				table.remove(theList, 1)
				assert.are.equal(firstSize, table.getn(HologrindJediManager.getGrindableProfessionList()))
			end)
		end)

		describe("checkIfProgressedToJedi", function()
			it("Should if the number of mastered professions are below the threshold not give the player jedi status nor send a sui window", function()
				local creaturePointer = { "creaturePointer" }
				local realGetNumberOfMasteredProfessions = HologrindJediManager.getNumberOfMasteredProfessions
				HologrindJediManager.getNumberOfMasteredProfessions = spy.new(function() return EXPECTEDMAXIMUMNUMBEROFPROFESSIONSTOSHOWWITHHOLOCRON end)
				local realIsJedi = HologrindJediManager.isJedi
				HologrindJediManager.isJedi = spy.new(function() return false end)
				local realSendSuiWindow = HologrindJediManager.sendSuiWindow
				HologrindJediManager.sendSuiWindow = spy.new(function() end)
				local realAwardJediStatusAndSkill = HologrindJediManager.awardJediStatusAndSkill
				HologrindJediManager.awardJediStatusAndSkill = spy.new(function() end)

				HologrindJediManager.checkIfProgressedToJedi(creaturePointer)

				assert.spy(HologrindJediManager.getNumberOfMasteredProfessions).was.called_with(creaturePointer)
				assert.spy(HologrindJediManager.isJedi).was.called(0)
				assert.spy(HologrindJediManager.sendSuiWindow).was.called(0)
				assert.spy(HologrindJediManager.awardJediStatusAndSkill).was.called(0)

				HologrindJediManager.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
				HologrindJediManager.isJedi = realIsJedi
				HologrindJediManager.sendSuiWindow = realSendSuiWindow
				HologrindJediManager.awardJediStatusAndSkill = realAwardJediStatusAndSkill
			end)

			it("Should if player already is jedi not give the player jedi status nor send a sui window", function()
				local creaturePointer = { "creaturePointer" }
				local realGetNumberOfMasteredProfessions = HologrindJediManager.getNumberOfMasteredProfessions
				HologrindJediManager.getNumberOfMasteredProfessions = spy.new(function() return EXPECTEDNUMBEROFPROFESSIONSTOGRIND end)
				local realIsJedi = HologrindJediManager.isJedi
				HologrindJediManager.isJedi = spy.new(function() return true end)
				local realSendSuiWindow = HologrindJediManager.sendSuiWindow
				HologrindJediManager.sendSuiWindow = spy.new(function() end)
				local realAwardJediStatusAndSkill = HologrindJediManager.awardJediStatusAndSkill
				HologrindJediManager.awardJediStatusAndSkill = spy.new(function() end)

				HologrindJediManager.checkIfProgressedToJedi(creaturePointer)

				assert.spy(HologrindJediManager.getNumberOfMasteredProfessions).was.called_with(creaturePointer)
				assert.spy(HologrindJediManager.isJedi).was.called_with(creaturePointer)
				assert.spy(HologrindJediManager.sendSuiWindow).was.called(0)
				assert.spy(HologrindJediManager.awardJediStatusAndSkill).was.called(0)

				HologrindJediManager.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
				HologrindJediManager.isJedi = realIsJedi
				HologrindJediManager.sendSuiWindow = realSendSuiWindow
				HologrindJediManager.awardJediStatusAndSkill = realAwardJediStatusAndSkill
			end)

			it("Should award the player with the jedi skills and send a sui message if the correct number of professions has been mastered.", function()
				local creaturePointer = { "creaturePointer" }
				local realGetNumberOfMasteredProfessions = HologrindJediManager.getNumberOfMasteredProfessions
				HologrindJediManager.getNumberOfMasteredProfessions = spy.new(function() return EXPECTEDNUMBEROFPROFESSIONSTOGRIND end)
				local realIsJedi = HologrindJediManager.isJedi
				HologrindJediManager.isJedi = spy.new(function() return false end)
				local realSendSuiWindow = HologrindJediManager.sendSuiWindow
				HologrindJediManager.sendSuiWindow = spy.new(function() end)
				local realAwardJediStatusAndSkill = HologrindJediManager.awardJediStatusAndSkill
				HologrindJediManager.awardJediStatusAndSkill = spy.new(function() end)

				HologrindJediManager.checkIfProgressedToJedi(creaturePointer)

				assert.spy(HologrindJediManager.getNumberOfMasteredProfessions).was.called_with(creaturePointer)
				assert.spy(HologrindJediManager.isJedi).was.called_with(creaturePointer)
				assert.spy(HologrindJediManager.sendSuiWindow).was.called_with(creaturePointer)
				assert.spy(HologrindJediManager.awardJediStatusAndSkill).was.called_with(creaturePointer)

				HologrindJediManager.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
				HologrindJediManager.isJedi = realIsJedi
				HologrindJediManager.sendSuiWindow = realSendSuiWindow
				HologrindJediManager.awardJediStatusAndSkill = realAwardJediStatusAndSkill
			end)
		end)

		describe("getNumberOfMasteredProfessions", function()
			it("Should get the profession to master list for the player and count the number of mastered professions", function()
				local creaturePointer = { "creaturePointer" }
				local getHologrindProfessionsSpy = spy.new(function() return { 1, 2, 3, 4 } end)
				local hasBadgeSpy = spy.new(function(self, badgeNumber) return badgeNumber < 3 end)
				local playerObject = { getHologrindProfessions = getHologrindProfessionsSpy, hasBadge = hasBadgeSpy }
				local realWithCreaturePlayerObject = HologrindJediManager.withCreaturePlayerObject
				HologrindJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction) return performThisFunction(playerObject) end)

				assert.same(2, HologrindJediManager.getNumberOfMasteredProfessions())

				assert.spy(HologrindJediManager.withCreaturePlayerObject).was.called(1)
				assert.spy(getHologrindProfessionsSpy).was.called(1)
				assert.spy(hasBadgeSpy).was.called(4)
			end)
		end)

		describe("registerObservers", function()
			it("Should call createObserver for the BADGEAWARDED event on the player", function()
				local creaturePointer = { "creaturePointer" }
				local realCreateObserver = createObserver
				createObserver = spy.new(function() end)

				HologrindJediManager.registerObservers(creaturePointer)

				assert.spy(createObserver).was.called_with(BADGEAWARDED, "HologrindJediManager", "badgeAwardedEventHandler", creaturePointer)

				createObserver = realCreateObserver
			end)
		end)

		describe("badgeAwardedEventHandler", function()
			it("Should call checkIfProgressedToJedi", function()
				local creaturePointer1 = { "creaturePointer1" }
				local creaturePointer2 = { "creaturePointer2" }
				local realCheckIfProgressedToJedi = HologrindJediManager.checkIfProgressedToJedi
				HologrindJediManager.checkIfProgressedToJedi = spy.new(function() end)

				HologrindJediManager:badgeAwardedEventHandler(creaturePointer1, creaturePointer2, 42)

				assert.spy(HologrindJediManager.checkIfProgressedToJedi).was.called_with(creaturePointer1)

				HologrindJediManager.checkIfProgressedToJedi = realCheckIfProgressedToJedi
			end)
		end)

		describe("sendHolocronMessage", function()
			it("Should send next profession message to the player if the number of mastered professions is below the threshold", function()
				local creaturePointer = { "creaturePointer" }
				local sendSystemMessageSpy = spy.new(function() end)
				local sendSystemMessageWithTOSpy = spy.new(function() end)
				local creatureObject = { sendSystemMessage = sendSystemMessageSpy, sendSystemMessageWithTO = sendSystemMessageWithTOSpy }
				local getHologrindProfessionsSpy = spy.new(function() return { 1, 2, 3, 4 } end)
				local hasBadgeSpy = spy.new(function(self, badgeNumber) return badgeNumber < 3 end)
				local playerObject = { getHologrindProfessions = getHologrindProfessionsSpy, hasBadge = hasBadgeSpy }

				local realGetNumberOfMasteredProfessions = HologrindJediManager.getNumberOfMasteredProfessions
				local realWithCreatureObject = HologrindJediManager.withCreatureObject
				local realWithCreatureAndPlayerObject = HologrindJediManager.withCreatureAndPlayerObject
				HologrindJediManager.getNumberOfMasteredProfessions = spy.new(function() return 2 end)
				HologrindJediManager.withCreatureObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject)
				end)
				HologrindJediManager.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)

				HologrindJediManager.sendHolocronMessage(creaturePointer)

				assert.spy(HologrindJediManager.getNumberOfMasteredProfessions).was.called(1)
				assert.spy(HologrindJediManager.withCreatureAndPlayerObject).was.called(1)
				assert.spy(getHologrindProfessionsSpy).was.called(1)
				assert.spy(hasBadgeSpy).was.called(4)
				assert.spy(sendSystemMessageWithTOSpy).was.called(2)

				HologrindJediManager.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
				HologrindJediManager.withCreatureObject = realWithCreatureObject
				HologrindJediManager.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)

			it("Should send find out on your own message to the player if the number of mastered professions is above the threshold", function()
				local creaturePointer = { "creaturePointer" }
				local sendSystemMessageSpy = spy.new(function() end)
				local sendSystemMessageWithTOSpy = spy.new(function() end)
				local creatureObject = { sendSystemMessage = sendSystemMessageSpy, sendSystemMessageWithTO = sendSystemMessageWithTOSpy }
				local getHologrindProfessionsSpy = spy.new(function() return { 1, 2, 3, 4, 5, 6 } end)
				local hasBadgeSpy = spy.new(function(self, badgeNumber) return badgeNumber < 5 end)
				local playerObject = { getHologrindProfessions = getHologrindProfessionsSpy, hasBadge = hasBadgeSpy }

				local realGetNumberOfMasteredProfessions = HologrindJediManager.getNumberOfMasteredProfessions
				local realWithCreatureObject = HologrindJediManager.withCreatureObject
				local realWithCreatureAndPlayerObject = HologrindJediManager.withCreatureAndPlayerObject
				HologrindJediManager.getNumberOfMasteredProfessions = spy.new(function() return 4 end)
				HologrindJediManager.withCreatureObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject)
				end)
				HologrindJediManager.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)

				HologrindJediManager.sendHolocronMessage(creaturePointer)

				assert.spy(HologrindJediManager.getNumberOfMasteredProfessions).was.called(1)
				assert.spy(HologrindJediManager.withCreatureObject).was.called(1)
				assert.spy(getHologrindProfessionsSpy).was.called(0)
				assert.spy(hasBadgeSpy).was.called(0)
				assert.spy(sendSystemMessageSpy).was.called(1)

				HologrindJediManager.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
				HologrindJediManager.withCreatureObject = realWithCreatureObject
				HologrindJediManager.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)

			it("Should return false if the number of mastered professions is below the threshold", function()
				local creaturePointer = { "creaturePointer" }
				local sendSystemMessageSpy = spy.new(function() end)
				local sendSystemMessageWithTOSpy = spy.new(function() end)
				local creatureObject = { sendSystemMessage = sendSystemMessageSpy, sendSystemMessageWithTO = sendSystemMessageWithTOSpy }
				local getHologrindProfessionsSpy = spy.new(function() return { 1, 2, 3, 4 } end)
				local hasBadgeSpy = spy.new(function(self, badgeNumber) return badgeNumber < 3 end)
				local playerObject = { getHologrindProfessions = getHologrindProfessionsSpy, hasBadge = hasBadgeSpy }

				local realGetNumberOfMasteredProfessions = HologrindJediManager.getNumberOfMasteredProfessions
				local realWithCreatureObject = HologrindJediManager.withCreatureObject
				local realWithCreatureAndPlayerObject = HologrindJediManager.withCreatureAndPlayerObject
				HologrindJediManager.getNumberOfMasteredProfessions = spy.new(function() return 2 end)
				HologrindJediManager.withCreatureObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject)
				end)
				HologrindJediManager.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)

				assert.is_not_true(HologrindJediManager.sendHolocronMessage(creaturePointer))

				HologrindJediManager.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
				HologrindJediManager.withCreatureObject = realWithCreatureObject
				HologrindJediManager.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)

			it("Should return true if the number of mastered professions is above the threshold", function()
				local creaturePointer = { "creaturePointer" }
				local sendSystemMessageSpy = spy.new(function() end)
				local sendSystemMessageWithTOSpy = spy.new(function() end)
				local creatureObject = { sendSystemMessage = sendSystemMessageSpy, sendSystemMessageWithTO = sendSystemMessageWithTOSpy }
				local getHologrindProfessionsSpy = spy.new(function() return { 1, 2, 3, 4, 5, 6 } end)
				local hasBadgeSpy = spy.new(function(self, badgeNumber) return badgeNumber < 5 end)
				local playerObject = { getHologrindProfessions = getHologrindProfessionsSpy, hasBadge = hasBadgeSpy }

				local realGetNumberOfMasteredProfessions = HologrindJediManager.getNumberOfMasteredProfessions
				local realWithCreatureObject = HologrindJediManager.withCreatureObject
				local realWithCreatureAndPlayerObject = HologrindJediManager.withCreatureAndPlayerObject
				HologrindJediManager.getNumberOfMasteredProfessions = spy.new(function() return 4 end)
				HologrindJediManager.withCreatureObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject)
				end)
				HologrindJediManager.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)

				assert.is_true(HologrindJediManager.sendHolocronMessage(creaturePointer))

				HologrindJediManager.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
				HologrindJediManager.withCreatureObject = realWithCreatureObject
				HologrindJediManager.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)
		end)

		describe("isJedi", function()
			it("Should return what the isJedi method returns on the player object.", function()
				local creaturePointer = { "creatureObjectPointer" }
				local isJediSpy = spy.new(function() return true end)
				local playerObject = { isJedi = isJediSpy }
				local realWithCreaturePlayerObject = HologrindJediManager.withCreaturePlayerObject
				HologrindJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(playerObject)
				end)

				assert.is_true(HologrindJediManager.isJedi(creaturePointer))

				assert.spy(isJediSpy).was.called(1)
				assert.spy(HologrindJediManager.withCreaturePlayerObject).was.called(1)

				HologrindJediManager.withCreaturePlayerObject = realWithCreaturePlayerObject
			end)
		end)

		describe("notifyOkPressed", function()
			it("Should do nothing.", function()
				HologrindJediManager.notifyOkPressed()
			end)
		end)

		describe("sendSuiWindow", function()
			it("Should send a sui message window to the player with information about jedi being unlocked.", function()
				local creaturePointer = { "creatureObjectPointer" }
				local sendMessageBoxSpy = spy.new(function() end)
				local luaSuiManager = { sendMessageBox = sendMessageBoxSpy }
				LuaSuiManager = spy.new(function() return luaSuiManager end)

				HologrindJediManager.sendSuiWindow(creaturePointer)

				assert.spy(LuaSuiManager).was.called(1)
				assert.spy(sendMessageBoxSpy).was.called_with(luaSuiManager, creaturePointer, creaturePointer, "@quest/force_sensitive/intro:force_sensitive", "Perhaps you should meditate somewhere alone...", "@ok", "HologrindJediManager", "notifyOkPressed")
			end)
		end)

		describe("awardJediStatusAndSkill", function()
			it("Should award the player the first force sensitive skill and set the jedi state to 1.", function()
				local creaturePointer = { "creatureObjectPointer" }
				awardSkill = spy.new(function() end)
				setJediStateSpy = spy.new(function() end)
				local playerObject = { setJediState = setJediStateSpy }
				local realWithCreaturePlayerObject = HologrindJediManager.withCreaturePlayerObject
				HologrindJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(playerObject)
				end)

				HologrindJediManager.awardJediStatusAndSkill(creaturePointer)

				assert.spy(awardSkill).was.called_with(creaturePointer, "force_title_jedi_novice")
				assert.spy(setJediStateSpy).was.called_with(playerObject, 1)
				assert.spy(HologrindJediManager.withCreaturePlayerObject).was.called(1)

				HologrindJediManager.withCreaturePlayerObject = realWithCreaturePlayerObject
			end)
		end)
	end)
end)
