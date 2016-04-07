spawn_area = SharedObjectTemplate:new {
	planetMapCategory = "",
	planetMapSubCategory = "",
	autoRegisterWithPlanetMap = 1,

	zoneComponent = "ZoneComponent",
	objectMenuComponent = "ObjectMenuComponent",
	containerComponent = "ContainerComponent",
	gameObjectType = 33554436
}

ObjectTemplates:addTemplate(spawn_area, "object/spawn_area.iff")
