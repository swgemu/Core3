local ObjectManager = require("managers.object.object_manager")

tutorialItemDrumContainerComponent = {}

function tutorialItemDrumContainerComponent:transferObject(pContainer, pObj, slot)
	return -1
end

function tutorialItemDrumContainerComponent:canAddObject(pContainer, pObj, slot)
	return -1
end

function tutorialItemDrumContainerComponent:removeObject(pContainer, pObj, slot)
	if (pContainer ~= nil) then
		local playerID = readData(SceneObject(pContainer):getObjectID() .. ":playerOwnerID")
		local pPlayer = getSceneObject(playerID)
		
		if (pPlayer ~= nil) then
			TutorialScreenPlay:drumItemLootEvent(pContainer, pPlayer)
		end
	end
	return -1
end