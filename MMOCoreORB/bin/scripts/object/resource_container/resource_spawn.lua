object_resource_container_resource_spawn = object_resource_container_shared_simple:new {
	playerUseMask = ALL,
	
	level = 10,
	
	maxCondition = 1000,
	
	useCount = 1,
	
	optionsBitmask = 256, --Default all objects to not display ham bars.
	pvpStatusBitmask = 0,
	objectMenuComponent = "TangibleObjectMenuComponent",
	attributeListComponent = "AttributeListComponent",

	sliceable = 0,
	
      templateType = RESOURCESPAWN,
      gameObjectType = 4259840
}

ObjectTemplates:addTemplate(object_resource_container_resource_spawn, "object/resource_container/resource_spawn.iff")
