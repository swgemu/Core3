local ObjectManager = require("managers.object.object_manager")

TatooineBenKenobisHouse = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("TatooineBenKenobisHouse", true)

function TatooineBenKenobisHouse:start()
	if (isZoneEnabled("tatooine")) then
		local pCell = getSceneObject(3565386)
		if (pCell ~= nil) then
			SceneObject(pCell):setContainerInheritPermissionsFromParent(false)
			SceneObject(pCell):setContainerDefaultDenyPermission(WALKIN)
			SceneObject(pCell):clearContainerDefaultAllowPermission(WALKIN)
		end
	end
end
