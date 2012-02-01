lair_spawn_area = SharedObjectTemplate:new {
clientTemplateFileName = "", 
	 planetMapCategory = "",
	 planetMapSubCategory = "",
	 autoRegisterWithPlanetMap = 1,
	 
	 zoneComponent = "ZoneComponent",
	 objectMenuComponent = {"cpp", "ObjectMenuComponent"},
	 containerComponent = "ContainerComponent",
	gameObjectType = 33554440
}

ObjectTemplates:addTemplate(lair_spawn_area, "object/lair_spawn_area.iff")