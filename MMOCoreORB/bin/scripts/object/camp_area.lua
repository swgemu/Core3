camp_area = SharedObjectTemplate:new {
clientTemplateFileName = "", 
	 planetMapCategory = "",
	 planetMapSubCategory = "",
	 autoRegisterWithPlanetMap = 1,
	 
	 zoneComponent = "ZoneComponent",
	 objectMenuComponent = "ObjectMenuComponent",
	 containerComponent = "ContainerComponent",
	gameObjectType = 33554441
}
	
ObjectTemplates:addTemplate(camp_area, "object/camp_area.iff")
