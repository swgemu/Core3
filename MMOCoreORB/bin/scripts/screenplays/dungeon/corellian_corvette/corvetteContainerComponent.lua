local ObjectManager = require("managers.object.object_manager")

brokenDroidContainerComponent = {}

function brokenDroidContainerComponent:transferObject(pDroid, pItem, slot)
	if (pItem == nil) then
		return TRANSFERFAIL
	end

	if slot ~= -1 then
		return TRANSFERFAIL
	end
	
	local pPlayer = brokenDroidContainerComponent:getObjOwner(pItem)
	local pCorvette = CorellianCorvetteScreenPlay:getCorvetteID(pDroid)
	local corvetteId = BuildingObject(pCorvette):getObjectID()
	
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return TRANSFERFAIL
	end
	if (SceneObject(pItem):getTemplateObjectPath() ~= "object/tangible/dungeon/droid_maint_module.iff") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:wont_fit")
		return 0
	end
	
	if (CreatureObject(pPlayer):isInCombat()) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:not_in_combat")
		return TRANSFERFAIL
	end
	
	local pCell = BuildingObject(pCorvette):getNamedCell("thrustersubroom28")
	if (pCell ~= nil) then
		local cellId = SceneObject(pCell):getObjectID()
		AiAgent(pDroid):stopWaiting()
		AiAgent(pDroid):setWait(0)
		AiAgent(pDroid):setNextPosition(-3, -14, -36.35, cellId)
		AiAgent(pDroid):executeBehavior()
	end
	return TRANSFERSUCCESS
end

function brokenDroidContainerComponent:canAddObject(pDroid, pItem, slot)
	if pItem == nil then
		return TRANSFERCANTADD
	end

	if slot ~= -1 then
		return TRANSFERCANTADD
	end

	local pPlayer = DeathWatchBunkerScreenPlay:getObjOwner(pItem)

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return TRANSFERCANTADD
	end
	
	if (SceneObject(pItem):getTemplateObjectPath() ~= "object/tangible/dungeon/droid_maint_module.iff") then
		return TRANSFERFAIL
	end
	
	if (CreatureObject(pPlayer):isInCombat()) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:not_in_combat")
		return TRANSFERFAIL
	end
	
	return TRANSFERCANADD
end

function brokenDroidContainerComponent:removeObject(pContainer, pObj, slot)
	return TRANSFERFAIL
end

function brokenDroidContainerComponent:getObjOwner(pObj)
	if (pObj == nil) then
		return nil
	end

	local pPlayerInv = SceneObject(pObj):getParent()

	if (pPlayerInv == nil) then
		return nil
	end

	local parent = SceneObject(pPlayerInv):getParent()

	if (parent == nil) then
		return nil
	end

	if (SceneObject(parent):isCreatureObject()) then
		return parent
	end

	return nil
end