local ObjectManager = require("managers.object.object_manager")

EncodedDiskMenuComponent = { }

function EncodedDiskMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(120, 3, "@treasure_map/treasure_map:decode") -- Decode
end

function EncodedDiskMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil) then
		return 0
	end

	local object = SceneObject(pSceneObject)
	if (object:isASubChildOf(pPlayer) == false) then
		return 0
	end

	if (selectedID == 120) then
		object:destroyObjectFromWorld()
		object:destroyObjectFromDatabase()

		ObjectManager.withCreatureObject(pPlayer, function(creature)
			local pInventory = creature:getSlottedObject("inventory")
			local randType = getRandomNumber(1,3)
			local pItem
			if (randType == 1) then
				pItem = giveItem(pInventory, "object/tangible/treasure_map/treasure_map_pirate1.iff", -1)
			elseif (randType == 2) then
				pItem = giveItem(pInventory, "object/tangible/treasure_map/treasure_map_pirate2.iff", -1)
			else
				pItem = giveItem(pInventory, "object/tangible/treasure_map/treasure_map_bh.iff", -1)
			end
			if (pItem ~= nil) then
				SceneObject(pItem):sendTo(pPlayer)
			end
			creature:sendSystemMessage("@treasure_map/treasure_map:sys_decode_success") -- You have broken the data encryption and can now read the disk!
		end)
	end

	return 0
end
