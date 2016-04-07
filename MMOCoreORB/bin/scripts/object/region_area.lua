region_area = SharedObjectTemplate:new {
	clientTemplateFileName = "",
	planetMapCategory = "",
	planetMapSubCategory = "",
	autoRegisterWithPlanetMap = 1,

	zoneComponent = "ZoneComponent",
	objectMenuComponent = "ObjectMenuComponent",
	containerComponent = "ContainerComponent",
	gameObjectType = 33554433
}
	
ObjectTemplates:addTemplate(region_area, "object/region_area.iff")
