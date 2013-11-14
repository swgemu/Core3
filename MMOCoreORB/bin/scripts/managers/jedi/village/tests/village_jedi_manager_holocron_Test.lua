VillageJediManagerHolocron = require("managers.jedi.village.village_jedi_manager_holocron")

describe("Village Jedi Manager Holocron", function()
	describe("Interface functions", function()
		describe("useHolocron", function()
			it("Should use the holocron if the player is a jedi and does not have max force at the moment", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local pSceneObject = { "sceneObjectPointer" }
				local realCanUseHolocron = VillageJediManagerHolocron.canUseHolocron
				local realCanReplenishForce = VillageJediManagerHolocron.canReplenishForce
				local realUseTheHolocron = VillageJediManagerHolocron.useTheHolocron

				VillageJediManagerHolocron.canUseHolocron = spy.new(function() return true end)
				VillageJediManagerHolocron.canReplenishForce = spy.new(function() return true end)
				VillageJediManagerHolocron.useTheHolocron = spy.new(function() end)

				VillageJediManagerHolocron.useHolocron(pSceneObject, pCreatureObject)

				assert.spy(VillageJediManagerHolocron.canUseHolocron).was.called_with(pCreatureObject)
				assert.spy(VillageJediManagerHolocron.canReplenishForce).was.called_with(pCreatureObject)
				assert.spy(VillageJediManagerHolocron.useTheHolocron).was.called_with(pSceneObject, pCreatureObject)

				VillageJediManagerHolocron.canUseHolocron = realCanUseHolocron
				VillageJediManagerHolocron.canReplenishForce = realCanReplenishForce
				VillageJediManagerHolocron.useTheHolocron = realUseTheHolocron
			end)

			it("Should send message about not able to replenish force if player is jedi but has full force", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local pSceneObject = { "sceneObjectPointer" }
				local realCanUseHolocron = VillageJediManagerHolocron.canUseHolocron
				local realCanReplenishForce = VillageJediManagerHolocron.canReplenishForce
				local realCannotReplenishForce = VillageJediManagerHolocron.cannotReplenishForce

				VillageJediManagerHolocron.canUseHolocron = spy.new(function() return true end)
				VillageJediManagerHolocron.canReplenishForce = spy.new(function() return false end)
				VillageJediManagerHolocron.cannotReplenishForce = spy.new(function() end)

				VillageJediManagerHolocron.useHolocron(pSceneObject, pCreatureObject)

				assert.spy(VillageJediManagerHolocron.canUseHolocron).was.called_with(pCreatureObject)
				assert.spy(VillageJediManagerHolocron.canReplenishForce).was.called_with(pCreatureObject)
				assert.spy(VillageJediManagerHolocron.cannotReplenishForce).was.called_with(pCreatureObject)

				VillageJediManagerHolocron.canUseHolocron = realCanUseHolocron
				VillageJediManagerHolocron.canReplenishForce = realCanReplenishForce
				VillageJediManagerHolocron.cannotReplenishForce = realCannotReplenishForce
			end)

			it("Should send message about not being able to use the holocron if player is not jedi", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local pSceneObject = { "sceneObjectPointer" }
				local realCanUseHolocron = VillageJediManagerHolocron.canUseHolocron
				local realCannotUseHolocron = VillageJediManagerHolocron.cannotUseHolocron

				VillageJediManagerHolocron.canUseHolocron = spy.new(function() return false end)
				VillageJediManagerHolocron.cannotUseHolocron = spy.new(function() end)

				VillageJediManagerHolocron.useHolocron(pSceneObject, pCreatureObject)

				assert.spy(VillageJediManagerHolocron.canUseHolocron).was.called_with(pCreatureObject)
				assert.spy(VillageJediManagerHolocron.cannotUseHolocron).was.called_with(pCreatureObject)

				VillageJediManagerHolocron.canUseHolocron = realCanUseHolocron
				VillageJediManagerHolocron.cannotUseHolocron = realCannotUseHolocron
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
				local realWithCreatureAndPlayerObject = VillageJediManagerHolocron.withCreatureAndPlayerObject
				VillageJediManagerHolocron.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)

				assert.is_false(VillageJediManagerHolocron.canUseHolocron(pCreatureObject))

				assert.spy(isJediSpy).was.called(1)
				assert.spy(checkCooldownRecoverySpy).was.called(0)
				assert.spy(VillageJediManagerHolocron.withCreatureAndPlayerObject).was.called(1)

				VillageJediManagerHolocron.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)

			it("Should return false if player has a cooldown for using a holocron", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local isJediSpy = spy.new(function() return true end)
				local checkCooldownRecoverySpy = spy.new(function(name) return true end)
				local creatureObject = { checkCooldownRecovery = checkCooldownRecoverySpy }
				local playerObject = { isJedi = isJediSpy }
				local realWithCreatureAndPlayerObject = VillageJediManagerHolocron.withCreatureAndPlayerObject
				VillageJediManagerHolocron.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)

				assert.is_false(VillageJediManagerHolocron.canUseHolocron(pCreatureObject))

				assert.spy(isJediSpy).was.called(1)
				assert.spy(checkCooldownRecoverySpy).was.called_with(creatureObject, USEDHOLOCRON)
				assert.spy(VillageJediManagerHolocron.withCreatureAndPlayerObject).was.called(1)

				VillageJediManagerHolocron.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)

			it("Should return true if player does not have a cooldown for using a holocron and is jedi", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local isJediSpy = spy.new(function() return true end)
				local checkCooldownRecoverySpy = spy.new(function(name) return false end)
				local creatureObject = { checkCooldownRecovery = checkCooldownRecoverySpy }
				local playerObject = { isJedi = isJediSpy }
				local realWithCreatureAndPlayerObject = VillageJediManagerHolocron.withCreatureAndPlayerObject
				VillageJediManagerHolocron.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)

				assert.is_true(VillageJediManagerHolocron.canUseHolocron(pCreatureObject))

				assert.spy(isJediSpy).was.called(1)
				assert.spy(checkCooldownRecoverySpy).was.called_with(creatureObject, USEDHOLOCRON)
				assert.spy(VillageJediManagerHolocron.withCreatureAndPlayerObject).was.called(1)

				VillageJediManagerHolocron.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)
		end)

		describe("canReplenishForce", function()
			it("Should return false if the player force is at max", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local getForcePowerSpy = spy.new(function() return 23 end)
				local getForcePowerMaxSpy = spy.new(function() return 23 end)
				local playerObject = { getForcePower = getForcePowerSpy, getForcePowerMax = getForcePowerMaxSpy }
				local realGetForcePower = VillageJediManagerHolocron.getForcePower
				local realGetForcePowerMax = VillageJediManagerHolocron.getForcePowerMax
				local realWithCreaturePlayerObject = VillageJediManagerHolocron.withCreaturePlayerObject
				VillageJediManagerHolocron.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(playerObject)
				end)

				assert.is_false(VillageJediManagerHolocron.canReplenishForce(pCreatureObject))

				assert.spy(getForcePowerSpy).was.called(1)
				assert.spy(getForcePowerMaxSpy).was.called(1)
				assert.spy(VillageJediManagerHolocron.withCreaturePlayerObject).was.called(1)

				VillageJediManagerHolocron.withCreaturePlayerObject = realWithCreaturePlayerObject
			end)

			it("Should return false if the player force is not at max", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local getForcePowerSpy = spy.new(function() return 22 end)
				local getForcePowerMaxSpy = spy.new(function() return 23 end)
				local playerObject = { getForcePower = getForcePowerSpy, getForcePowerMax = getForcePowerMaxSpy }
				local realGetForcePower = VillageJediManagerHolocron.getForcePower
				local realGetForcePowerMax = VillageJediManagerHolocron.getForcePowerMax
				local realWithCreaturePlayerObject = VillageJediManagerHolocron.withCreaturePlayerObject
				VillageJediManagerHolocron.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(playerObject)
				end)

				assert.is_true(VillageJediManagerHolocron.canReplenishForce(pCreatureObject))

				assert.spy(getForcePowerSpy).was.called(1)
				assert.spy(getForcePowerMaxSpy).was.called(1)
				assert.spy(VillageJediManagerHolocron.withCreaturePlayerObject).was.called(1)

				VillageJediManagerHolocron.withCreaturePlayerObject = realWithCreaturePlayerObject
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
				local realWithCreatureAndPlayerObject = VillageJediManagerHolocron.withCreatureAndPlayerObject
				VillageJediManagerHolocron.withCreatureAndPlayerObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject, playerObject)
				end)
				LuaSceneObject = spy.new(function() return sceneObject end)

				VillageJediManagerHolocron.useTheHolocron(pSceneObject, pCreatureObject)

				assert.spy(destroyObjectFromWorldSpy).was.called(1)
				assert.spy(setForcePowerSpy).was.called(1)
				assert.spy(sendSystemMessageSpy).was.called(1)
				assert.spy(addCooldownSpy).was.called(1)
				assert.spy(VillageJediManagerHolocron.withCreatureAndPlayerObject).was.called(1)

				VillageJediManagerHolocron.withCreatureAndPlayerObject = realWithCreatureAndPlayerObject
			end)
		end)

		describe("cannotReplenishForce", function()
			it("Should send a system message to the player about not being able to replenish the force", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local sendSystemMessageSpy = spy.new(function() end)
				local creatureObject = { sendSystemMessage = sendSystemMessageSpy }
				local realWithCreatureObject = VillageJediManagerHolocron.withCreatureObject
				VillageJediManagerHolocron.withCreatureObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject)
				end)

				VillageJediManagerHolocron.cannotReplenishForce(pCreatureObject)

				assert.spy(sendSystemMessageSpy).was.called_with(creatureObject, "@jedi_spam:holocron_force_max")

				VillageJediManagerHolocron.withCreatureObject = realWithCreatureObject
			end)
		end)

		describe("cannotUseHolocron", function()
			it("Should send a system message to the player about not being able to use the holocron", function()
				local pCreatureObject = { "creatureObjectPointer" }
				local sendSystemMessageSpy = spy.new(function() end)
				local creatureObject = { sendSystemMessage = sendSystemMessageSpy }
				local realWithCreatureObject = VillageJediManagerHolocron.withCreatureObject
				VillageJediManagerHolocron.withCreatureObject = spy.new(function(pCreatureObject, performThisFunction)
					return performThisFunction(creatureObject)
				end)

				VillageJediManagerHolocron.cannotUseHolocron(pCreatureObject)

				assert.spy(sendSystemMessageSpy).was.called_with(creatureObject, "@jedi_spam:holocron_no_effect")

				VillageJediManagerHolocron.withCreatureObject = realWithCreatureObject
			end)
		end)
	end)
end)
