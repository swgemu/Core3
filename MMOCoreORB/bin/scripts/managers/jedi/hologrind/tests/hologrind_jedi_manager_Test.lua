registerScreenPlay = spy.new(function() end)

local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
require("managers.jedi.hologrind.hologrind_jedi_manager")

local testHologrind = HologrindJediManager:new {

}

local EXPECTEDNUMBEROFPROFESSIONSTOGRIND = 6
local EXPECTEDMAXIMUMNUMBEROFPROFESSIONSTOSHOWWITHHOLOCRON = 4

describe("Hologrind Jedi Manager", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local pSceneObject = { "sceneObjectPointer" }
	local creatureObject
	local playerObject
	local sceneObject
	local hologrindProffs = {1,2,3,4,5,6}
	local grindableProffs = {
		{"a", 1},
		{"b", 2},
		{"c", 3},
		{"d", 4},
		{"e", 5},
		{"f", 6},
		{"g", 7},
		{"h", 8},
	}

	setup(function()
		DirectorManagerMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()

		creatureObject = {}
		creatureObject.getPlayerObject = spy.new(function() return pPlayerObject end)
		creatureObject.sendSystemMessage = spy.new(function() end)
		creatureObject.sendSystemMessageWithTO = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

		playerObject = {}
		playerObject.addHologrindProfession = spy.new(function() end)
		playerObject.getHologrindProfessions = spy.new(function() return hologrindProffs end)
		playerObject.hasBadge = spy.new(function() return true end)
		playerObject.isJedi = spy.new(function() return true end)
		playerObject.setJediState = spy.new(function() end)
		DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject

		sceneObject = {}
		sceneObject.destroyObjectFromWorld = spy.new(function() end)
		sceneObject.destroyObjectFromDatabase = spy.new(function() end)
		DirectorManagerMocks.sceneObjects[pSceneObject] = sceneObject

	end)

	describe("Interface functions", function()
		describe("onPlayerCreated", function()
			describe("When called with a player", function()
				local realGetGrindableProfessionList

				setup(function()
					realGetGrindableProfessionList = testHologrind.getGrindableProfessionList
				end)

				teardown(function()
					testHologrind.getGrindableProfessionList = realGetGrindableProfessionList
				end)

				before_each(function()
					testHologrind.getGrindableProfessionList = spy.new(function() return grindableProffs end)
				end)

				it("Should call the add hologrind profession method of the lua player object the defined number of times", function()
					testHologrind:onPlayerCreated(pCreatureObject)

					assert.spy(playerObject.addHologrindProfession).was.called(EXPECTEDNUMBEROFPROFESSIONSTOGRIND)
				end)
			end)
		end)

		describe("onPlayerLoggedIn", function()
			local realCheckIfProgressedToJedi
			local realRegisterObservers

			setup(function()
				realCheckIfProgressedToJedi = testHologrind.checkIfProgressedToJedi
				realRegisterObservers = testHologrind.registerObservers
			end)

			teardown(function()
				testHologrind.checkIfProgressedToJedi = realCheckIfProgressedToJedi
				testHologrind.registerObservers = realRegisterObservers
			end)

			before_each(function()
				testHologrind.checkIfProgressedToJedi = spy.new(function() end)
				testHologrind.registerObservers = spy.new(function() end)
			end)

			it("Should call the checkIfProgressedToJedi function.", function()
				testHologrind:onPlayerLoggedIn(pCreatureObject)

				assert.spy(testHologrind.checkIfProgressedToJedi).was.called_with(testHologrind, pCreatureObject)
			end)

			it("Should call the registerObservers function.", function()
				testHologrind:onPlayerLoggedIn(pCreatureObject)

				assert.spy(testHologrind.registerObservers).was.called_with(testHologrind, pCreatureObject)
			end)
		end)

		describe("useItem", function()
			local realSendHolocronMessage

			setup(function()
				realSendHolocronMessage = testHologrind.sendHolocronMessage
			end)

			teardown(function()
				testHologrind.sendHolocronMessage = realSendHolocronMessage
			end)

			before_each(function()
				testHologrind.sendHolocronMessage = spy.new(function() end)
			end)

			it("Should call sendHolocronMessage.", function()
				local itemType = 0
				testHologrind:useItem(pSceneObject, itemType, pCreatureObject)

				assert.spy(testHologrind.sendHolocronMessage).was.called_with(testHologrind, pCreatureObject)
			end)

			describe("When sendHolocronMessage returns false", function()
				it("Should destroy the holocron.", function()
					local itemType = 0
					testHologrind.sendHolocronMessage = spy.new(function() return false end)
					testHologrind:useItem(pSceneObject, itemType, pCreatureObject)

					assert.spy(sceneObject.destroyObjectFromWorld).was.called(1)
					assert.spy(sceneObject.destroyObjectFromDatabase).was.called(1)
				end)
			end)

			describe("When sendHolocronMessage returns true", function()
				it("Should not destroy the holocron.", function()
					local itemType = 0
					testHologrind.sendHolocronMessage = spy.new(function() return true end)
					testHologrind:useItem(pSceneObject, itemType, pCreatureObject)

					assert.spy(sceneObject.destroyObjectFromWorld).was_not.called()
					assert.spy(sceneObject.destroyObjectFromDatabase).was_not.called()
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
				assert.is_true(EXPECTEDNUMBEROFPROFESSIONSTOGRIND <= table.getn(testHologrind.getGrindableProfessionList()))
			end)

			it("Should not modify the size of the grindable profession list when items are removed from it in another function", function()
				local theList = testHologrind.getGrindableProfessionList()
				local firstSize = table.getn(theList)
				table.remove(theList, 1)
				assert.are.equal(firstSize, table.getn(testHologrind.getGrindableProfessionList()))
			end)
		end)

		describe("checkIfProgressedToJedi", function()
			describe("When called with a player", function()
				local realGetNumberOfMasteredProfessions
				local realIsJedi
				local realSendSuiWindow
				local realAwardJediStatusAndSkill

				setup(function()
					realGetNumberOfMasteredProfessions = testHologrind.getNumberOfMasteredProfessions
					realIsJedi = testHologrind.isJedi
					realSendSuiWindow = testHologrind.sendSuiWindow
					realAwardJediStatusAndSkill = testHologrind.awardJediStatusAndSkill
				end)

				teardown(function()
					testHologrind.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
					testHologrind.isJedi = realIsJedi
					testHologrind.sendSuiWindow = realSendSuiWindow
					testHologrind.awardJediStatusAndSkill = realAwardJediStatusAndSkill
				end)

				before_each(function()
					testHologrind.isJedi = spy.new(function() return true end)
					testHologrind.sendSuiWindow = spy.new(function() end)
					testHologrind.awardJediStatusAndSkill = spy.new(function() end)
				end)

				it("Should if the number of mastered professions are below the threshold not give the player jedi status nor send a sui window", function()
					testHologrind.getNumberOfMasteredProfessions = spy.new(function() return 0 end)
					testHologrind:checkIfProgressedToJedi(pCreatureObject)

					assert.spy(testHologrind.getNumberOfMasteredProfessions).was.called_with(testHologrind, pCreatureObject)
					assert.spy(testHologrind.isJedi).was.called(0)
					assert.spy(testHologrind.sendSuiWindow).was.called(0)
					assert.spy(testHologrind.awardJediStatusAndSkill).was.called(0)
				end)

				it("Should if player already is jedi not give the player jedi status nor send a sui window", function()
					testHologrind.getNumberOfMasteredProfessions = spy.new(function() return 7 end)
					testHologrind:checkIfProgressedToJedi(pCreatureObject)

					assert.spy(testHologrind.getNumberOfMasteredProfessions).was.called_with(testHologrind, pCreatureObject)
					assert.spy(testHologrind.isJedi).was.called_with(testHologrind, pCreatureObject)
					assert.spy(testHologrind.sendSuiWindow).was.called(0)
					assert.spy(testHologrind.awardJediStatusAndSkill).was.called(0)
				end)

				it("Should award the player with the jedi skills and send a sui message if the correct number of professions has been mastered.", function()
					testHologrind.getNumberOfMasteredProfessions = spy.new(function() return 7 end)
					testHologrind.isJedi = spy.new(function() return false end)
					testHologrind:checkIfProgressedToJedi(pCreatureObject)

					assert.spy(testHologrind.getNumberOfMasteredProfessions).was.called_with(testHologrind, pCreatureObject)
					assert.spy(testHologrind.isJedi).was.called_with(testHologrind, pCreatureObject)
					assert.spy(testHologrind.sendSuiWindow).was.called_with(testHologrind, pCreatureObject)
					assert.spy(testHologrind.awardJediStatusAndSkill).was.called_with(testHologrind, pCreatureObject)
				end)
			end)
		end)

		describe("getNumberOfMasteredProfessions", function()
			it("Should get the profession to master list for the player and count the number of mastered professions", function()
				playerObject.hasBadge = spy.new(function(self, badgeNumber) return badgeNumber < 3 end)

				assert.same(2, testHologrind:getNumberOfMasteredProfessions(pCreatureObject))
				assert.spy(playerObject.getHologrindProfessions).was.called(1)
				assert.spy(playerObject.hasBadge).was.called(6)
			end)
		end)

		describe("registerObservers", function()
			it("Should call createObserver for the BADGEAWARDED event on the player", function()
				testHologrind:registerObservers(pCreatureObject)

				assert.spy(createObserver).was.called_with(BADGEAWARDED, "HologrindJediManager", "badgeAwardedEventHandler", pCreatureObject)
			end)
		end)

		describe("badgeAwardedEventHandler", function()
			local realCheckIfProgressedToJedi

			setup(function()
				realCheckIfProgressedToJedi = testHologrind.checkIfProgressedToJedi
			end)

			teardown(function()
				testHologrind.checkIfProgressedToJedi = realCheckIfProgressedToJedi
			end)

			before_each(function()
				testHologrind.checkIfProgressedToJedi = spy.new(function() end)
			end)

			it("Should call checkIfProgressedToJedi", function()
				testHologrind:badgeAwardedEventHandler(pCreatureObject, nil, 42)

				assert.spy(testHologrind.checkIfProgressedToJedi).was.called_with(testHologrind, pCreatureObject)
			end)
		end)

		describe("sendHolocronMessage", function()
			setup(function()
				realGetNumberOfMasteredProfessions = testHologrind.getNumberOfMasteredProfessions
				realIsJedi = testHologrind.isJedi
				realSendSuiWindow = testHologrind.sendSuiWindow
				realAwardJediStatusAndSkill = testHologrind.awardJediStatusAndSkill
			end)

			teardown(function()
				testHologrind.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
				testHologrind.isJedi = realIsJedi
				testHologrind.sendSuiWindow = realSendSuiWindow
				testHologrind.awardJediStatusAndSkill = realAwardJediStatusAndSkill
			end)

			before_each(function()
				testHologrind.isJedi = spy.new(function() return true end)
				testHologrind.sendSuiWindow = spy.new(function() end)
				testHologrind.awardJediStatusAndSkill = spy.new(function() end)
			end)

			it("Should send next profession message to the player if the number of mastered professions is below the threshold", function()
				testHologrind.getNumberOfMasteredProfessions = spy.new(function() return 2 end)
				playerObject.hasBadge = spy.new(function(self, badgeNumber) return badgeNumber < 3 end)
				testHologrind:sendHolocronMessage(pCreatureObject)

				assert.spy(testHologrind.getNumberOfMasteredProfessions).was.called(1)
				assert.spy(playerObject.getHologrindProfessions).was.called(1)
				assert.spy(playerObject.hasBadge).was.called(6)
				assert.spy(creatureObject.sendSystemMessageWithTO).was.called(4)
			end)

			it("Should send find out on your own message to the player if the number of mastered professions is above the threshold", function()
				testHologrind.getNumberOfMasteredProfessions = spy.new(function() return 4 end)
				playerObject.hasBadge = spy.new(function(self, badgeNumber) return badgeNumber < 5 end)
				testHologrind:sendHolocronMessage(pCreatureObject)

				assert.spy(testHologrind.getNumberOfMasteredProfessions).was.called(1)
				assert.spy(playerObject.getHologrindProfessions).was.called(0)
				assert.spy(playerObject.hasBadge).was.called(0)
				assert.spy(creatureObject.sendSystemMessage).was.called(1)
			end)

			it("Should return false if the number of mastered professions is below the threshold", function()
				testHologrind.getNumberOfMasteredProfessions = spy.new(function() return 2 end)

				assert.is_not_true(testHologrind:sendHolocronMessage(pCreatureObject))
			end)

			it("Should return true if the number of mastered professions is above the threshold", function()
				testHologrind.getNumberOfMasteredProfessions = spy.new(function() return 4 end)

				assert.is_true(testHologrind:sendHolocronMessage(pCreatureObject))
			end)
		end)

		describe("isJedi", function()
			it("Should return what the isJedi method returns on the player object.", function()
				testHologrind:isJedi(pCreatureObject)

				assert.spy(playerObject.isJedi).was.called(1)
			end)
		end)

		describe("notifyOkPressed", function()
			it("Should do nothing.", function()
				testHologrind:notifyOkPressed()
			end)
		end)

		describe("sendSuiWindow", function()
			it("Should send a sui message window to the player with information about jedi being unlocked.", function()
				local sendMessageBoxSpy = spy.new(function() end)
				local luaSuiManager = { sendMessageBox = sendMessageBoxSpy }
				LuaSuiManager = spy.new(function() return luaSuiManager end)

				testHologrind:sendSuiWindow(pCreatureObject)

				assert.spy(LuaSuiManager).was.called(1)
				assert.spy(sendMessageBoxSpy).was.called_with(luaSuiManager, pCreatureObject, pCreatureObject, "@quest/force_sensitive/intro:force_sensitive", "Perhaps you should meditate somewhere alone...", "@ok", "HologrindJediManager", "notifyOkPressed")
			end)
		end)

		describe("awardJediStatusAndSkill", function()
			it("Should award the player the first force sensitive skill and set the jedi state to 1.", function()
				testHologrind:awardJediStatusAndSkill(pCreatureObject)

				assert.spy(awardSkill).was.called_with(pCreatureObject, "force_title_jedi_novice")
				assert.spy(playerObject.setJediState).was.called_with(playerObject, 1)
			end)
		end)
	end)
end)
