local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
VillageJediManagerHolocron = require("managers.jedi.village.village_jedi_manager_holocron")

describe("Village Jedi Manager Holocron", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local pSceneObject = { "sceneObjectPointer" }
	local creatureObject
	local playerObject
	local sceneObject

	setup(function()
		DirectorManagerMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()

		creatureObject = {}
		creatureObject.addCooldown = spy.new(function() end)
		creatureObject.checkCooldownRecovery = spy.new(function() return true end)
		creatureObject.getPlayerObject = spy.new(function() return pPlayerObject end)
		creatureObject.sendSystemMessage = spy.new(function() end)
		creatureObject.sendSystemMessageWithTO = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

		playerObject = {}
		playerObject.isJedi = spy.new(function() return true end)
		playerObject.getForcePower = spy.new(function() return 23 end)
		playerObject.getForcePowerMax = spy.new(function() return 23 end)
		playerObject.setForcePower = spy.new(function() end)
		DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject

		sceneObject = {}
		sceneObject.destroyObjectFromWorld = spy.new(function() end)
		sceneObject.destroyObjectFromDatabase = spy.new(function() end)
		DirectorManagerMocks.sceneObjects[pSceneObject] = sceneObject

	end)

	describe("Interface functions", function()
		describe("useHolocron", function()
			local realCanUseHolocron = VillageJediManagerHolocron.canUseHolocron
			local realCannotUseHolocron = VillageJediManagerHolocron.cannotUseHolocron
			local realUseTheHolocron = VillageJediManagerHolocron.useTheHolocron
			local realCanReplenishForce = VillageJediManagerHolocron.canReplenishForce
			local realCannotReplenishForce = VillageJediManagerHolocron.cannotReplenishForce

			setup(function()
				realCanUseHolocron = VillageJediManagerHolocron.canUseHolocron
				realCannotUseHolocron = VillageJediManagerHolocron.cannotUseHolocron
				realUseTheHolocron = VillageJediManagerHolocron.useTheHolocron
				realCanReplenishForce = VillageJediManagerHolocron.canReplenishForce
				realCannotReplenishForce = VillageJediManagerHolocron.cannotReplenishForce
			end)

			teardown(function()
				VillageJediManagerHolocron.canUseHolocron = realCanUseHolocron
				VillageJediManagerHolocron.cannotUseHolocron = realCannotUseHolocron
				VillageJediManagerHolocron.useTheHolocron = realUseTheHolocron
				VillageJediManagerHolocron.canReplenishForce = realCanReplenishForce
				VillageJediManagerHolocron.cannotReplenishForce = realCannotReplenishForce
			end)

			before_each(function()
				VillageJediManagerHolocron.canUseHolocron = spy.new(function() return true end)
				VillageJediManagerHolocron.cannotUseHolocron = spy.new(function() end)
				VillageJediManagerHolocron.useTheHolocron = spy.new(function() end)
				VillageJediManagerHolocron.canReplenishForce = spy.new(function() return true end)
				VillageJediManagerHolocron.cannotReplenishForce = spy.new(function() end)
			end)

			it("Should use the holocron if the player is a jedi and does not have max force at the moment", function()
				VillageJediManagerHolocron.useHolocron(pSceneObject, pCreatureObject)

				assert.spy(VillageJediManagerHolocron.canUseHolocron).was.called_with(pCreatureObject)
				assert.spy(VillageJediManagerHolocron.canReplenishForce).was.called_with(pCreatureObject)
				assert.spy(VillageJediManagerHolocron.useTheHolocron).was.called_with(pSceneObject, pCreatureObject)
			end)

			it("Should send message about not able to replenish force if player is jedi but has full force", function()
				VillageJediManagerHolocron.canReplenishForce = spy.new(function() return false end)

				VillageJediManagerHolocron.useHolocron(pSceneObject, pCreatureObject)

				assert.spy(VillageJediManagerHolocron.canUseHolocron).was.called_with(pCreatureObject)
				assert.spy(VillageJediManagerHolocron.canReplenishForce).was.called_with(pCreatureObject)
				assert.spy(VillageJediManagerHolocron.cannotReplenishForce).was.called_with(pCreatureObject)
			end)

			it("Should send message about not being able to use the holocron if player is not jedi", function()
				VillageJediManagerHolocron.canUseHolocron = spy.new(function() return false end)

				VillageJediManagerHolocron.useHolocron(pSceneObject, pCreatureObject)

				assert.spy(VillageJediManagerHolocron.canUseHolocron).was.called_with(pCreatureObject)
				assert.spy(VillageJediManagerHolocron.cannotUseHolocron).was.called_with(pCreatureObject)
			end)
		end)
	end)

	describe("Private functions", function()
		describe("canUseHolocron", function()
			it("Should return false if player is not jedi", function()
				playerObject.isJedi = spy.new(function() return false end)

				assert.is_false(VillageJediManagerHolocron.canUseHolocron(pCreatureObject))

				assert.spy(playerObject.isJedi).was.called(1)
				assert.spy(creatureObject.checkCooldownRecovery).was.called(0)
			end)

			it("Should return false if player has a cooldown for using a holocron", function()
				assert.is_false(VillageJediManagerHolocron.canUseHolocron(pCreatureObject))

				assert.spy(playerObject.isJedi).was.called(1)
				assert.spy(creatureObject.checkCooldownRecovery).was.called_with(creatureObject, USEDHOLOCRON)
			end)

			it("Should return true if player does not have a cooldown for using a holocron and is jedi", function()
				creatureObject.checkCooldownRecovery = spy.new(function() return false end)

				assert.is_true(VillageJediManagerHolocron.canUseHolocron(pCreatureObject))

				assert.spy(playerObject.isJedi).was.called(1)
				assert.spy(creatureObject.checkCooldownRecovery).was.called_with(creatureObject, USEDHOLOCRON)
			end)
		end)

		describe("canReplenishForce", function()
			it("Should return false if the player force is at max", function()
				assert.is_false(VillageJediManagerHolocron.canReplenishForce(pCreatureObject))

				assert.spy(playerObject.getForcePower).was.called(1)
				assert.spy(playerObject.getForcePowerMax).was.called(1)
			end)

			it("Should return true if the player force is not at max", function()
				playerObject.getForcePower = spy.new(function() return 20 end)

				assert.is_true(VillageJediManagerHolocron.canReplenishForce(pCreatureObject))

				assert.spy(playerObject.getForcePower).was.called(1)
				assert.spy(playerObject.getForcePowerMax).was.called(1)
			end)
		end)

		describe("useTheHolocron", function()
			it("Should send system message, set force to max, add cooldown and destroy the holocron", function()
				VillageJediManagerHolocron.useTheHolocron(pSceneObject, pCreatureObject)

				assert.spy(sceneObject.destroyObjectFromWorld).was.called(1)
				assert.spy(sceneObject.destroyObjectFromDatabase).was.called(1)
				assert.spy(playerObject.setForcePower).was.called(1)
				assert.spy(creatureObject.sendSystemMessage).was.called(1)
				assert.spy(creatureObject.addCooldown).was.called(1)
			end)
		end)

		describe("cannotReplenishForce", function()
			it("Should send a system message to the player about not being able to replenish the force", function()
				VillageJediManagerHolocron.cannotReplenishForce(pCreatureObject)

				assert.spy(creatureObject.sendSystemMessage).was.called_with(creatureObject, "@jedi_spam:holocron_force_max")
			end)
		end)

		describe("cannotUseHolocron", function()
			it("Should send a system message to the player about not being able to use the holocron", function()
				VillageJediManagerHolocron.cannotUseHolocron(pCreatureObject)

				assert.spy(creatureObject.sendSystemMessage).was.called_with(creatureObject, "@jedi_spam:holocron_no_effect")
			end)
		end)
	end)
end)
