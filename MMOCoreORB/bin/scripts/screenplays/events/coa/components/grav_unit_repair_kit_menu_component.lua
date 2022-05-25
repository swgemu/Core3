local ObjectManager = require("managers.object.object_manager")

coa3GravUnitRepairKit = {  }

function coa3GravUnitRepairKit:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local response = LuaObjectMenuResponse(pMenuResponse)

	response:addRadialMenuItem(200, 3, "@theme_park/alderaan/act3/shared_rebel_missions:repair")
end

function coa3GravUnitRepairKit:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (selectedID == 200) then
		Coa3Screenplay:repairGravUnit(pPlayer)
	end
	return 0
end