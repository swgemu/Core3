active_area = SharedObjectTemplate:new {
clientTemplateFileName = "", 
	 planetMapCategory = "",
	 planetMapSubCategory = "",
	 autoRegisterWithPlanetMap = 1,
	 
	 zoneComponent = "ZoneComponent",
	 objectMenuComponent = {"cpp", "ObjectMenuComponent"},
	 containerComponent = "ContainerComponent",
	gameObjectType = 33554439
}
	
ObjectTemplates:addTemplate(active_area, "object/active_area.iff")
