local ObjectManager = require("managers.object.object_manager")

MagicEightBallMenuComponent = { }

function MagicEightBallMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(20, 3, "@sui:read_option") -- Read
end

function MagicEightBallMenuComponent:noCallback(pPlayer, pSui, eventIndex)
end

function MagicEightBallMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil) then
		return 0
	end

	if (SceneObject(pSceneObject):isASubChildOf(pPlayer) == false) then
		return 0
	end

	if (selectedID == 20) then
		local sui = SuiMessageBox.new("MagicEightBallMenuComponent", "noCallback")
		sui.setTitle("@sui:magic_eight_ball_title")
		local num = tostring(getRandomNumber(1,50))
		sui.setPrompt("@magic_eight_ball:response"..num)
		sui.setTargetNetworkId(SceneObject(pSceneObject):getObjectID())
		sui.sendTo(pPlayer)
	end
	return 0
end
