local ObjectManager = require("managers.object.object_manager")

TatooineBenKenobisHouse = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("TatooineBenKenobisHouse", true)

function TatooineBenKenobisHouse:start()
	if (isZoneEnabled("tatooine")) then
		local pCell = getSceneObject(3565386)
		ObjectManager.withSceneObject(pCell, function(cell)
			cell:setContainerInheritPermissionsFromParent(false)
			cell:setContainerDefaultDenyPermission(WALKIN)
			cell:clearContainerDefaultAllowPermission(WALKIN)
		end)
	end
end