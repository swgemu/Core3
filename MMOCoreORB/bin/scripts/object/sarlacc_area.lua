sarlacc_area = SharedObjectTemplate:new {
	clientTemplateFileName = "",
	planetMapCategory = "",
	planetMapSubCategory = "",
	autoRegisterWithPlanetMap = 1,

	groundZoneComponent = "GroundZoneComponent",
	objectMenuComponent = "ObjectMenuComponent",
	containerComponent = "ContainerComponent",
	gameObjectType = 33554443
}
	
ObjectTemplates:addTemplate(sarlacc_area, "object/sarlacc_area.iff")
