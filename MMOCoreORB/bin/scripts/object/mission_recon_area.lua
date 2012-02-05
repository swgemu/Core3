mission_recon_area = SharedObjectTemplate:new {
clientTemplateFileName = "", 
	 planetMapCategory = "",
	 planetMapSubCategory = "",
	 autoRegisterWithPlanetMap = 1,
	 
	 zoneComponent = "ZoneComponent",
	 objectMenuComponent = {"cpp", "ObjectMenuComponent"},
	 containerComponent = {"cpp", "ContainerComponent"},
	gameObjectType = 33554435
}

ObjectTemplates:addTemplate(mission_recon_area, "object/mission_recon_area.iff")