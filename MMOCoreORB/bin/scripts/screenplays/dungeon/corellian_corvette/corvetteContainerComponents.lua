local ObjectManager = require("managers.object.object_manager")

corvetteLootCrateContainerComponent = {}

function corvetteLootCrateContainerComponent:transferObject(pContainer, pObj, slot)
	return -1
end

function corvetteLootCrateContainerComponent:canAddObject(pContainer, pObj, slot)
	return -1
end

function corvetteLootCrateContainerComponent:removeObject(pContainer, pObj, slot)
	if (pContainer ~= nil) then
		CorellianCorvette:onCrateLooted(pContainer)
	end

	return -1
end

corvetteBrokenDroidContainerComponent = {}

function corvetteBrokenDroidContainerComponent:transferObject(pDroid, pItem, slot)
	if (pItem == nil) then
		return TRANSFERFAIL
	end

	if slot ~= -1 then
		return TRANSFERFAIL
	end

	local pPlayer = self:getObjOwner(pItem)

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return TRANSFERFAIL
	end

	local pCorvette = CorellianCorvette:getCorvetteObject(pDroid)

	if (pCorvette == nil) then
		return TRANSFERFAIL
	end

	local corvetteId = BuildingObject(pCorvette):getObjectID()

	if (SceneObject(pItem):getTemplateObjectPath() ~= "object/tangible/dungeon/droid_maint_module.iff") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:wont_fit")
		return TRANSFERFAIL
	end

	if (CreatureObject(pPlayer):isInCombat()) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:not_in_combat")
		return TRANSFERFAIL
	end

	SceneObject(pItem):destroyObjectFromWorld()
	SceneObject(pItem):destroyObjectFromDatabase()
	
	createEvent(10, "CorellianCorvette", "startRepairDroidMovement", pDroid, "")

	return TRANSFERSUCCESS
end

function corvetteBrokenDroidContainerComponent:canAddObject(pDroid, pItem, slot)
	if pItem == nil then
		return TRANSFERCANTADD
	end

	if slot ~= -1 then
		return TRANSFERCANTADD
	end

	local pPlayer = self:getObjOwner(pItem)

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return TRANSFERCANTADD
	end

	if (SceneObject(pItem):getTemplateObjectPath() ~= "object/tangible/dungeon/droid_maint_module.iff") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:wont_fit")
		return TRANSFERCANTADD
	end

	if (CreatureObject(pPlayer):isInCombat()) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:not_in_combat")
		return TRANSFERCANTADD
	end

	return TRANSFERCANADD
end

function corvetteBrokenDroidContainerComponent:removeObject(pContainer, pObj, slot)
	return TRANSFERFAIL
end

function corvetteBrokenDroidContainerComponent:getObjOwner(pObj)
	if (pObj == nil) then
		return nil
	end

	local pPlayerInv = SceneObject(pObj):getParent()

	if (pPlayerInv == nil) then
		return nil
	end

	local pParent = SceneObject(pPlayerInv):getParent()

	if (pParent == nil) then
		return nil
	end

	if (SceneObject(pParent):isCreatureObject()) then
		return pParent
	end

	return nil
end
