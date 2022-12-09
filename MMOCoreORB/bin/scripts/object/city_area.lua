city_area = SharedObjectTemplate:new {
	gameObjectType = 33554437,

	clientTemplateFileName = "",
	planetMapCategory = "",
	planetMapSubCategory = "",
	autoRegisterWithPlanetMap = 1,

	zoneComponent = "ZoneComponent",
	objectMenuComponent = "ObjectMenuComponent",
	containerComponent = "ContainerComponent"
}

ObjectTemplates:addTemplate(city_area, "object/city_area.iff")