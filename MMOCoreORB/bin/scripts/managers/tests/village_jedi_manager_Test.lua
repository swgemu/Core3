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
	end)
end)
