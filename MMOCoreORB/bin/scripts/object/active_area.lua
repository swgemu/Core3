active_area = SharedObjectTemplate:new {
	clientTemplateFileName = "",
	planetMapCategory = "",
	planetMapSubCategory = "",
	autoRegisterWithPlanetMap = 1,

	groundZoneComponent = "GroundZoneComponent",
	spaceZoneComponent = "SpaceZoneComponent",
	objectMenuComponent = "ObjectMenuComponent",
	containerComponent = "ContainerComponent",
	gameObjectType = 33554439
}

ObjectTemplates:addTemplate(active_area, "object/active_area.iff")
