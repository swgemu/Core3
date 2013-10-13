TalusDetainmentCenterScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TalusDetainmentCenterScreenPlay",

	buildingID = 9686208,

--9686208 bunker imperial detainment center
--9686346 terminal hq
--9686357 override terminal
--9686389 power regulator
--9686393 security terminal
--9686398 uplink terminal
}

registerScreenPlay("TalusDetainmentCenterScreenPlay", true)

function TalusDetainmentCenterScreenPlay:start()
	if (isZoneEnabled("talus")) then
		local pBuilding = getSceneObject(self.buildingID)
		createObserver(FACTIONBASEFLIPPED, "TalusDetainmentCenterScreenPlay", "flipBase", pBuilding)

		if math.random(100) >= 50 then
			self:spawnRebels(pBuilding)
		else
			self:spawnImperials(pBuilding)
		end
	end
end

function TalusDetainmentCenterScreenPlay:flipBase(pBuilding)

	if pBuilding ~= nil then
		local building = LuaBuildingObject(pBuilding)
		building:destroyChildObjects()

		if building:getFaction() == FACTIONIMPERIAL then
			self:spawnRebels(pBuilding)
		elseif building:getFaction() == FACTIONREBEL then
			self:spawnImperials(pBuilding)
		end
	end

	return 0
end

function TalusDetainmentCenterScreenPlay:spawnImperials(pBuilding)

	if pBuilding ~= nil then
		local building = LuaBuildingObject(pBuilding)
		building:initializeStaticGCWBase(FACTIONIMPERIAL)

		building:spawnChildCreature("imperial_staff_corporal", 300, 3.5, -9.0, 32.6, 179, 9686212)
   		building:spawnChildCreature("command_security_guard", 300, 4.4, -9.0, 35.5, 179, 9686212)
		building:spawnChildCreature("command_security_guard", 300, 2.5, -9.0, 35.5, 179, 9686212)
		building:spawnChildCreature("imperial_warrant_officer_i", 300, -48.1, -9.0, -6.6, 90, 9686214)
		building:spawnChildCreature("imperial_private", 300, -58.4, -9.0, 3.2, 0, 9686214)
		building:spawnChildCreature("imperial_noncom", 300, -72.9, -9.0, 21.2,  165, 9686214)
		building:spawnChildCreature("imperial_staff_corporal", 300, -54.5, -9.0, 67.1, 179, 9686214)
		building:spawnChildCreature("imperial_noncom", 300, -52.3, -9.0, 63.2, 90, 9686214)
		building:spawnChildCreature("imperial_noncom", 300, -53.2, -9.0, 59.0, 90, 9686214)
		building:spawnChildCreature("imperial_noncom", 300, -57.0, -9.0, 60.9, -120, 9686214)
		building:spawnChildCreature("command_security_guard", 300, -24.9, -9.0, 28.5, 90, 9686213)
		building:spawnChildCreature("command_security_guard", 300, -24.8, -9.0, 26.0, 90, 9686213)
		building:spawnChildCreature("command_security_guard", 300, 12.1, -17.0, 65.0, 179, 9686215)
		building:spawnChildCreature("command_security_guard", 300, 12.1, -17.0, 62.0, -1, 9686215)
		building:spawnChildCreature("stormtrooper", 300, 30.4, -17.0, 60.7, 1, 9686215)
		building:spawnChildCreature("stormtrooper", 300, 30.4, -17.0, 65.9, 179, 9686215)
		building:spawnChildCreature("imperial_captain", 300, 34.5, -17.0, 63.5, -90, 9686215)
		building:spawnChildCreature("dark_trooper", 300, -1.2, -23.0, 225.4, 179, 9686222)
		building:spawnChildCreature("dark_trooper", 300, -3.8, -23.0, 225.4, 179, 9686222)
		building:spawnChildCreature("imperial_first_lieutenant", 300, -19.8, -23.0, 234.4, 179, 9686222)
		building:spawnChildCreature("stormtrooper", 300, 1.0, -23.0, 192.3, 90, 9686217)
		building:spawnChildCreature("stormtrooper", 300, -2.0, -23.0, 192.3, 90, 9686217)
		building:spawnChildCreature("stormtrooper", 300, -5.0, -23.0, 192.3, 90, 9686217)
		building:spawnChildCreature("stormtrooper", 300, -8.0, -23.0, 192.3, 90, 9686217)
		building:spawnChildCreature("stormtrooper", 300, 1.0, -23.0, 196.3, 90, 9686217)
		building:spawnChildCreature("stormtrooper", 300, -2.0, -23.0, 196.3, 90, 9686217)
		building:spawnChildCreature("stormtrooper", 300, -5.0, -23.0, 196.3, 90, 9686217)
		building:spawnChildCreature("stormtrooper", 300, -8.0, -23.0, 196.3, 90, 9686217)
		building:spawnChildCreature("imperial_first_lieutenant", 300, 7.1, -23.0, 198.5, -135, 9686217)

	end
end

function TalusDetainmentCenterScreenPlay:spawnRebels(pBuilding)

	if pBuilding ~= nil then
		local building = LuaBuildingObject(pBuilding)
		building:initializeStaticGCWBase(FACTIONREBEL)

		building:spawnChildCreature("rebel_staff_corporal", 300, 3.5, -9.0, 32.6, 179, 9686212)
   		building:spawnChildCreature("specforce_marine", 300, 4.4, -9.0, 35.5, 179, 9686212)
		building:spawnChildCreature("specforce_marine", 300, 2.5, -9.0, 35.5, 179, 9686212)
		building:spawnChildCreature("rebel_warrant_officer_i", 300, -48.1, -9.0, -6.6, 90, 9686214)
		building:spawnChildCreature("rebel_corporal", 300, -58.4, -9.0, 3.2, 0, 9686214)
		building:spawnChildCreature("specforce_technician", 300, -72.9, -9.0, 21.2,  165, 9686214)
		building:spawnChildCreature("rebel_staff_corporal", 300, -54.5, -9.0, 67.1, 179, 9686214)
		building:spawnChildCreature("specforce_technician", 300, -52.3, -9.0, 63.2, 90, 9686214)
		building:spawnChildCreature("specforce_technician", 300, -53.2, -9.0, 59.0, 90, 9686214)
		building:spawnChildCreature("specforce_technician", 300, -57.0, -9.0, 60.9, -120, 9686214)
		building:spawnChildCreature("specforce_marine", 300, -24.9, -9.0, 28.5, 90, 9686213)
		building:spawnChildCreature("specforce_marine", 300, -24.8, -9.0, 26.0, 90, 9686213)
		building:spawnChildCreature("specforce_marine", 300, 12.1, -17.0, 65.0, 179, 9686215)
		building:spawnChildCreature("specforce_marine", 300, 12.1, -17.0, 62.0, -1, 9686215)
		building:spawnChildCreature("rebel_trooper", 300, 30.4, -17.0, 60.7, 1, 9686215)
		building:spawnChildCreature("rebel_trooper", 300, 30.4, -17.0, 65.9, 179, 9686215)
		building:spawnChildCreature("rebel_army_captain", 300, 34.5, -17.0, 63.5, -90, 9686215)
		building:spawnChildCreature("senior_specforce_infiltrator", 300, -1.2, -23.0, 225.4, 179, 9686222)
		building:spawnChildCreature("senior_specforce_infiltrator", 300, -3.8, -23.0, 225.4, 179, 9686222)
		building:spawnChildCreature("rebel_first_lieutenant", 300, -19.8, -23.0, 234.4, 179, 9686222)
		building:spawnChildCreature("rebel_trooper", 300, 1.0, -23.0, 192.3, 90, 9686217)
		building:spawnChildCreature("rebel_trooper", 300, -2.0, -23.0, 192.3, 90, 9686217)
		building:spawnChildCreature("rebel_trooper", 300, -5.0, -23.0, 192.3, 90, 9686217)
		building:spawnChildCreature("rebel_trooper", 300, -8.0, -23.0, 192.3, 90, 9686217)
		building:spawnChildCreature("rebel_trooper", 300, 1.0, -23.0, 196.3, 90, 9686217)
		building:spawnChildCreature("rebel_trooper", 300, -2.0, -23.0, 196.3, 90, 9686217)
		building:spawnChildCreature("rebel_trooper", 300, -5.0, -23.0, 196.3, 90, 9686217)
		building:spawnChildCreature("rebel_trooper", 300, -8.0, -23.0, 196.3, 90, 9686217)
		building:spawnChildCreature("rebel_first_lieutenant", 300, 7.1, -23.0, 198.5, -135, 9686217)

	end
end
