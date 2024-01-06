nebula_area = SharedObjectTemplate:new {
	clientTemplateFileName = "",
	planetMapCategory = "",
	planetMapSubCategory = "",
	autoRegisterWithPlanetMap = 1,

	groundZoneComponent = "GroundZoneComponent",
	spaceZoneComponent = "SpaceZoneComponent",
	objectMenuComponent = "ObjectMenuComponent",
	containerComponent = "ContainerComponent",
	gameObjectType = 33554446
}

ObjectTemplates:addTemplate(nebula_area, "object/nebula_area.iff")