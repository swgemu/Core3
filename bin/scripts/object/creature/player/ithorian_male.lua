object_creature_player_ithorian_male = SharedCreatureObjectTemplate:new {
	acceleration = {36,12},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ith_m.sat",
	arrangementDescriptors = {"rider"},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_ithorian_m.cdf",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 1.5,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.5,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 1033,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:ithorian",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,0,0,0,0,0,0,0,0,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 33,
	speed = {5.376,1.549},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {720,720},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,
	
	baseHAM = { 0, 0, 0, 0, 0, 150, 300, 300, 150 },

	clientObjectCRC = 951764932
}

ObjectTemplates:addTemplate(object_creature_player_ithorian_male, "object/creature/player/ithorian_male.iff")