object_installation_generators_power_generator_fusion_style_1 = object_installation_generators_shared_power_generator_fusion_style_1:new {
	lotSize = 1,
	baseMaintenanceRate = 60,
	-- SOLAR = 1; CHEMICAL = 2; FLORA = 3; GAS = 4; GEOTHERMAL = 5; MINERAL = 6; WATER = 7; WIND = 8; FUSION = 9;
	installationType = 9,
	basePowerRate = 0
}

ObjectTemplates:addTemplate(object_installation_generators_power_generator_fusion_style_1, "object/installation/generators/power_generator_fusion_style_1.iff")

object_installation_generators_power_generator_photo_bio_style_1 = object_installation_generators_shared_power_generator_photo_bio_style_1:new {
	lotSize = 1,
	baseMaintenanceRate = 60,
	basePowerRate = 0
}

ObjectTemplates:addTemplate(object_installation_generators_power_generator_photo_bio_style_1, "object/installation/generators/power_generator_photo_bio_style_1.iff")

object_installation_generators_power_generator_solar_style_1 = object_installation_generators_shared_power_generator_solar_style_1:new {
	lotSize = 1,
	baseMaintenanceRate = 60,
	-- SOLAR = 1; CHEMICAL = 2; FLORA = 3; GAS = 4; GEOTHERMAL = 5; MINERAL = 6; WATER = 7; WIND = 8; FUSION = 9;
	installationType = 1,
	basePowerRate = 0
}

ObjectTemplates:addTemplate(object_installation_generators_power_generator_solar_style_1, "object/installation/generators/power_generator_solar_style_1.iff")

object_installation_generators_power_generator_wind_style_1 = object_installation_generators_shared_power_generator_wind_style_1:new {
	lotSize = 1,
	baseMaintenanceRate = 60,
	-- SOLAR = 1; CHEMICAL = 2; FLORA = 3; GAS = 4; GEOTHERMAL = 5; MINERAL = 6; WATER = 7; WIND = 8; FUSION = 9;
	installationType = 8,
	basePowerRate = 0
}

ObjectTemplates:addTemplate(object_installation_generators_power_generator_wind_style_1, "object/installation/generators/power_generator_wind_style_1.iff")
