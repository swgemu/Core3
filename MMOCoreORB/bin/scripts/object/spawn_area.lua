spawn_area = SharedObjectTemplate:new {
	gameObjectType = 33554436,

	clientTemplateFileName = "",
	planetMapCategory = "",
	planetMapSubCategory = "",
	autoRegisterWithPlanetMap = 1,

	groundZoneComponent = "GroundZoneComponent",
	objectMenuComponent = "ObjectMenuComponent",
	containerComponent = "ContainerComponent"
}

ObjectTemplates:addTemplate(spawn_area, "object/spawn_area.iff")
