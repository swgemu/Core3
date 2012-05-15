mission_spawn_area = SharedObjectTemplate:new {
clientTemplateFileName = "", 
	 planetMapCategory = "",
	 planetMapSubCategory = "",
	 autoRegisterWithPlanetMap = 1,
	 
	 zoneComponent = "ZoneComponent",
	 objectMenuComponent = {"cpp", "ObjectMenuComponent"},
	 containerComponent = {"cpp", "ContainerComponent"},
	gameObjectType = 33554434
}

ObjectTemplates:addTemplate(mission_spawn_area, "object/mission_spawn_area.iff")