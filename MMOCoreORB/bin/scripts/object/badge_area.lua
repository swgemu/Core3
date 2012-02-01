badge_area = SharedObjectTemplate:new {
clientTemplateFileName = "", 
	 planetMapCategory = "",
	 planetMapSubCategory = "",
	 autoRegisterWithPlanetMap = 1,
	 
	 zoneComponent = "ZoneComponent",
	 objectMenuComponent = {"cpp", "ObjectMenuComponent"},
	 containerComponent = "ContainerComponent",
	gameObjectType = 33554432
}

ObjectTemplates:addTemplate(badge_area, "object/badge_area.iff")