package.path = package.path .. ";scripts/managers/?.lua"
require("holocron_jedi_manager")

EXPECTEDNUMBEROFPROFESSIONSTOGRIND = 6

describe("Holocron Jedi Manager", function()
	describe("Interface functions", function() 
		it("Shall on call to onPlayerCreated call the add hologrind profession method of the lua player object the defined number of times", function()
			local creaturePointer = {}
			local playerPointer = {}
			addHologrindProfessionSpy = spy.new(function() end)
			local getPlayerObjectSpy = spy.new(function() return playerPointer end)
			local realWithCreaturePlayerObject = HolocronJediManager.withCreaturePlayerObject
			HolocronJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
				return performThisFunction({ addHologrindProfession = addHologrindProfessionSpy }) 
			end)

			HolocronJediManager.onPlayerCreated(creaturePointer)

			assert.spy(HolocronJediManager.withCreaturePlayerObject).was.called(1)
			assert.spy(addHologrindProfessionSpy).was.called(EXPECTEDNUMBEROFPROFESSIONSTOGRIND)

			HolocronJediManager.withCreaturePlayerObject = realWithCreaturePlayerObject
		end)

		it("Shall on call to onPlayerLoggedIn call the checkIfProgressedToJedi function.", function()
			local creaturePointer = { "creaturePointer" }
			local realCheckIfProgressedToJedi = HolocronJediManager.checkIfProgressedToJedi
			local realRegisterObservers = HolocronJediManager.registerObservers
			HolocronJediManager.checkIfProgressedToJedi = spy.new(function() end)
			HolocronJediManager.registerObservers = spy.new(function() end)

			HolocronJediManager:onPlayerLoggedIn(creaturePointer)

			assert.spy(HolocronJediManager.checkIfProgressedToJedi).was.called_with(creaturePointer)
		
			HolocronJediManager.checkIfProgressedToJedi = realCheckIfProgressedToJedi
			HolocronJediManager.registerObservers = realRegisterObservers
		end)

		it("Shall on call to onPlayerLoggedIn call the registerObservers function.", function()
			local creaturePointer = { "creaturePointer" }
			local realCheckIfProgressedToJedi = HolocronJediManager.checkIfProgressedToJedi
			local realRegisterObservers = HolocronJediManager.registerObservers
			HolocronJediManager.checkIfProgressedToJedi = spy.new(function() end)
			HolocronJediManager.registerObservers = spy.new(function() end)

			HolocronJediManager:onPlayerLoggedIn(creaturePointer)

			assert.spy(HolocronJediManager.registerObservers).was.called_with(creaturePointer)
		
			HolocronJediManager.checkIfProgressedToJedi = realCheckIfProgressedToJedi
			HolocronJediManager.registerObservers = realRegisterObservers
		end)

		it("Shall on call to useHolocron call sendHolocronMessage.", function() 
			local sceneObjectPointer = { "sceneObjectPointer" }
			local creaturePointer = { "creaturePointer" }
			local realSendHolocronMessage = HolocronJediManager.sendHolocronMessage
			HolocronJediManager.sendHolocronMessage = spy.new(function() end)
			local destroyObjectFromWorldSpy = spy.new(function() end)
			LuaSceneObject = spy.new(function() return { destroyObjectFromWorld = destroyObjectFromWorldSpy } end)

			HolocronJediManager:useHolocron(sceneObjectPointer, creaturePointer)

			assert.spy(HolocronJediManager.sendHolocronMessage).was.called_with(creaturePointer)

			HolocronJediManager.sendHolocronMessage = realSendHolocronMessage
		end)

		it("Shall on call to useHolocron destroy the holocron.", function() 
			local sceneObjectPointer = { "sceneObjectPointer" }
			local creaturePointer = { "creaturePointer" }
			local realSendHolocronMessage = HolocronJediManager.sendHolocronMessage
			HolocronJediManager.sendHolocronMessage = spy.new(function() end)
			local destroyObjectFromWorldSpy = spy.new(function() end)
			LuaSceneObject = spy.new(function() return { destroyObjectFromWorld = destroyObjectFromWorldSpy } end)

			HolocronJediManager:useHolocron(sceneObjectPointer, creaturePointer)

			assert.spy(destroyObjectFromWorldSpy).was.called(1)

			HolocronJediManager.sendHolocronMessage = realSendHolocronMessage
		end)
	end)

	describe("Private functions", function() 
		it("Defines the number of professions to master to 6", function()
			assert.same(EXPECTEDNUMBEROFPROFESSIONSTOGRIND, NUMBEROFPROFESSIONSTOMASTER)
		end)

		it("Get grindable profession list returns a list of at least the number of professions that has to be mastered", function()
			assert.is_true(EXPECTEDNUMBEROFPROFESSIONSTOGRIND <= table.getn(HolocronJediManager.getGrindableProfessionList()))
		end)

		it("The size of the grindable profession list is not affected when items are removed from it locally", function()
			local theList = HolocronJediManager.getGrindableProfessionList()
			local firstSize = table.getn(theList)
			table.remove(theList, 1)
			assert.are.equal(firstSize, table.getn(HolocronJediManager.getGrindableProfessionList()))
		end)

		it("Shall on call to checkIfProgressedToJedi count the number of mastered professions", function()
			local creaturePointer = { "creaturePointer" }
			local realGetNumberOfMasteredProfessions = HolocronJediManager.getNumberOfMasteredProfessions
			HolocronJediManager.getNumberOfMasteredProfessions = spy.new(function(pCreatureObject) return 0 end)

			HolocronJediManager.getNumberOfMasteredProfessions(creaturePointer)

			assert.spy(HolocronJediManager.getNumberOfMasteredProfessions).was.called_with(creaturePointer)

			HolocronJediManager.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
		end)

		it("Shall on call to checkIfProgressedToJedi if the number of mastered professions are below the threshold not give the player jedi status", function()
			local creaturePointer = { "creaturePointer" }
			-- To be implemented
		end)

		it("Shall on call to checkIfProgressedToJedi if the number of mastered professions are above the threshold give the player jedi status", function()
			local creaturePointer = { "creaturePointer" }
			-- To be implemented
		end)

		it("Shall on call to getNumberOfMasteredProfessions get the profession to master list for the player and count the number of mastered professions", function() 
			local creaturePointer = { "creaturePointer" }
			local getHologrindProfessionsSpy = spy.new(function() return { 1, 2, 3, 4 } end)
			local hasBadgeSpy = spy.new(function(self, badgeNumber) return badgeNumber < 3 end)
			local playerObject = { getHologrindProfessions = getHologrindProfessionsSpy, hasBadge = hasBadgeSpy }
			local realWithCreaturePlayerObject = HolocronJediManager.withCreaturePlayerObject
			HolocronJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction) return performThisFunction(playerObject) end)

			assert.same(2, HolocronJediManager.getNumberOfMasteredProfessions())

			assert.spy(HolocronJediManager.withCreaturePlayerObject).was.called(1)
			assert.spy(getHologrindProfessionsSpy).was.called(1)
			assert.spy(hasBadgeSpy).was.called(4)
		end)

		it("Shall on call to registerObservers call createObserver for the BADGEAWARDED event on the player", function()
			local creaturePointer = { "creaturePointer" }
			createObserver = spy.new(function() end)

			HolocronJediManager.registerObservers(creaturePointer)

			assert.spy(createObserver).was.called_with(BADGEAWARDED, "HolocronJediManager", "badgeAwardedEventHandler", creaturePointer)
		end)

		it("Shall on call to badgeAwardedEventHandler call checkIfProgressedToJedi", function()
			local creaturePointer1 = { "creaturePointer1" }
			local creaturePointer2 = { "creaturePointer2" }
			local realCheckIfProgressedToJedi = HolocronJediManager.checkIfProgressedToJedi
			HolocronJediManager.checkIfProgressedToJedi = spy.new(function() end)

			HolocronJediManager:badgeAwardedEventHandler(creaturePointer1, creaturePointer2, 42)

			assert.spy(HolocronJediManager.checkIfProgressedToJedi).was.called_with(creaturePointer1)

			HolocronJediManager.checkIfProgressedToJedi = realCheckIfProgressedToJedi
		end)

		it("Shall on call to sendHolocronMessage send next profession to the player if the number of mastered professions is below the threshold", function() 
			local creaturePointer = { "creaturePointer" }
			local sendSystemMessageSpy = spy.new(function() end)
			local sendSystemMessageWithTOSpy = spy.new(function() end)
			local creatureObject = { sendSystemMessage = sendSystemMessageSpy, sendSystemMessageWithTO = sendSystemMessageWithTOSpy }
			local getHologrindProfessionsSpy = spy.new(function() return { 1, 2, 3, 4 } end)
			local hasBadgeSpy = spy.new(function(self, badgeNumber) return badgeNumber < 3 end)
			local playerObject = { getHologrindProfessions = getHologrindProfessionsSpy, hasBadge = hasBadgeSpy }

			local realGetNumberOfMasteredProfessions = HolocronJediManager.getNumberOfMasteredProfessions
			local realWithCreatureObject = HolocronJediManager.withCreatureObject
			local realWithCreatureAndPlayerObject = HolocronJediManager.withCreatureAndPlayerObject
			HolocronJediManager.getNumberOfMasteredProfessions = spy.new(function() return 2 end)
			HolocronJediManager.withCreatureObject = spy.new(function(pCreatureObject, performThisFunction) 
				return performThisFunction(creatureObject) 
			end)
			HolocronJediManager.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction) 
				return performThisFunction(creatureObject, playerObject) 
			end)

			HolocronJediManager.sendHolocronMessage(creaturePointer)

			assert.spy(HolocronJediManager.getNumberOfMasteredProfessions).was.called(1)
			assert.spy(HolocronJediManager.withCreatureAndPlayerObject).was.called(1)
			assert.spy(getHologrindProfessionsSpy).was.called(1)
			assert.spy(hasBadgeSpy).was.called(3)
			assert.spy(sendSystemMessageWithTOSpy).was.called(1)

			HolocronJediManager.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
			HolocronJediManager.withCreatureObject = realWithCreatureObject
			HolocronJediManager.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
		end)

		it("Shall on call to sendHolocronMessage send find out on your own to the player if the number of mastered professions is above the threshold", function() 
			local creaturePointer = { "creaturePointer" }
			local sendSystemMessageSpy = spy.new(function() end)
			local sendSystemMessageWithTOSpy = spy.new(function() end)
			local creatureObject = { sendSystemMessage = sendSystemMessageSpy, sendSystemMessageWithTO = sendSystemMessageWithTOSpy }
			local getHologrindProfessionsSpy = spy.new(function() return { 1, 2, 3, 4, 5, 6 } end)
			local hasBadgeSpy = spy.new(function(self, badgeNumber) return badgeNumber < 5 end)
			local playerObject = { getHologrindProfessions = getHologrindProfessionsSpy, hasBadge = hasBadgeSpy }

			local realGetNumberOfMasteredProfessions = HolocronJediManager.getNumberOfMasteredProfessions
			local realWithCreatureObject = HolocronJediManager.withCreatureObject
			local realWithCreatureAndPlayerObject = HolocronJediManager.withCreatureAndPlayerObject
			HolocronJediManager.getNumberOfMasteredProfessions = spy.new(function() return 4 end)
			HolocronJediManager.withCreatureObject = spy.new(function(pCreatureObject, performThisFunction) 
				return performThisFunction(creatureObject) 
			end)
			HolocronJediManager.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction) 
				return performThisFunction(creatureObject, playerObject) 
			end)

			HolocronJediManager.sendHolocronMessage(creaturePointer)

			assert.spy(HolocronJediManager.getNumberOfMasteredProfessions).was.called(1)
			assert.spy(HolocronJediManager.withCreatureObject).was.called(1)
			assert.spy(getHologrindProfessionsSpy).was.called(0)
			assert.spy(hasBadgeSpy).was.called(0)
			assert.spy(sendSystemMessageSpy).was.called(1)

			HolocronJediManager.getNumberOfMasteredProfessions = realGetNumberOfMasteredProfessions
			HolocronJediManager.withCreatureObject = realWithCreatureObject
			HolocronJediManager.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
		end)
	end)
end)
