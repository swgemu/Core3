dynamic_spawn_area = SharedObjectTemplate:new {
clientTemplateFileName = "", 
	 planetMapCategory = "",
	 planetMapSubCategory = "",
	 autoRegisterWithPlanetMap = 1,
	 
	 zoneComponent = "ZoneComponent",
	 objectMenuComponent = {"cpp", "ObjectMenuComponent"},
	 containerComponent = "ContainerComponent",
	gameObjectType = 33554436
}

ObjectTemplates:addTemplate(dynamic_spawn_area, "object/dynamic_spawn_area.iff")