garage_area = SharedObjectTemplate:new {
clientTemplateFileName = "", 
	 planetMapCategory = "",
	 planetMapSubCategory = "",
	 autoRegisterWithPlanetMap = 1,
	 
	 zoneComponent = "ZoneComponent",
	 objectMenuComponent = {"cpp", "ObjectMenuComponent"},
	 containerComponent = {"cpp", "ContainerComponent"},
	gameObjectType = 33554438
}

ObjectTemplates:addTemplate(garage_area, "object/garage_area.iff")