sarlacc_area = SharedObjectTemplate:new {
clientTemplateFileName = "", 
	 planetMapCategory = "",
	 planetMapSubCategory = "",
	 autoRegisterWithPlanetMap = 1,
	 
	 zoneComponent = "ZoneComponent",
	 objectMenuComponent = {"cpp", "ObjectMenuComponent"},
	 containerComponent = {"cpp", "ContainerComponent"},
	gameObjectType = 33554443
}
	
ObjectTemplates:addTemplate(sarlacc_area, "object/sarlacc_area.iff")
