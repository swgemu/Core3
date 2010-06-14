object_installation_mining_organic_mining_organic_creature_farm = object_installation_mining_organic_shared_mining_organic_creature_farm:new {
	lotSize = 1,
	baseMaintenanceRate = 30,
	basePowerRate = 25
}

ObjectTemplates:addTemplate(object_installation_mining_organic_mining_organic_creature_farm, "object/installation/mining_organic/mining_organic_creature_farm.iff")

object_installation_mining_organic_mining_organic_flora_farm = object_installation_mining_organic_shared_mining_organic_flora_farm:new {
	lotSize = 1,
	baseMaintenanceRate = 30,
	-- SOLAR = 1; CHEMICAL = 2; FLORA = 3; GAS = 4; GEOTHERMAL = 5; MINERAL = 6; WATER = 7; WIND = 8; FUSION = 9;
	installationType = 3,
	basePowerRate = 25
}

ObjectTemplates:addTemplate(object_installation_mining_organic_mining_organic_flora_farm, "object/installation/mining_organic/mining_organic_flora_farm.iff")

object_installation_mining_organic_mining_organic_flora_farm_medium = object_installation_mining_organic_shared_mining_organic_flora_farm_medium:new {
	lotSize = 1,
	baseMaintenanceRate = 60,
	-- SOLAR = 1; CHEMICAL = 2; FLORA = 3; GAS = 4; GEOTHERMAL = 5; MINERAL = 6; WATER = 7; WIND = 8; FUSION = 9;
	installationType = 3,
	basePowerRate = 50
}

ObjectTemplates:addTemplate(object_installation_mining_organic_mining_organic_flora_farm_medium, "object/installation/mining_organic/mining_organic_flora_farm_medium.iff")

object_installation_mining_organic_mining_organic_flora_farm_heavy = object_installation_mining_organic_shared_mining_organic_flora_farm_heavy:new {
	lotSize = 1,
	baseMaintenanceRate = 90,
	-- SOLAR = 1; CHEMICAL = 2; FLORA = 3; GAS = 4; GEOTHERMAL = 5; MINERAL = 6; WATER = 7; WIND = 8; FUSION = 9;
	installationType = 3,
	basePowerRate = 75
}

ObjectTemplates:addTemplate(object_installation_mining_organic_mining_organic_flora_farm_heavy, "object/installation/mining_organic/mining_organic_flora_farm_heavy.iff")
