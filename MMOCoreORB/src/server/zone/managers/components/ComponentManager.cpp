/*
 * ComponentManager.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "ComponentManager.h"

#include "server/zone/objects/player/components/PlayerContainerComponent.h"
#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "server/zone/objects/tangible/components/LootContainerComponent.h"
#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/scene/components/AttributeListComponent.h"
#include "server/zone/objects/tangible/components/vendor/VendorContainerComponent.h"
#include "server/zone/objects/building/components/GCWBaseContainerComponent.h"
#include "server/zone/objects/tangible/components/vendor/VendorZoneComponent.h"
#include "server/zone/objects/tangible/components/vendor/VendorMenuComponent.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/objects/tangible/terminal/components/SecurityTerminalDataComponent.h"
#include "server/zone/objects/tangible/terminal/components/TurretControlTerminalDataComponent.h"
#include "server/zone/objects/installation/components/TurretDataComponent.h"
#include "server/zone/objects/installation/components/MinefieldDataComponent.h"
#include "server/zone/objects/installation/components/DetectorDataComponent.h"
#include "server/zone/objects/installation/components/TurretZoneComponent.h"
#include "server/zone/objects/installation/components/MinefieldZoneComponent.h"
#include "server/zone/objects/installation/components/MinefieldContainerComponent.h"
#include "server/zone/objects/installation/components/DetectorZoneComponent.h"
#include "server/zone/objects/tangible/components/vendor/AuctionTerminalDataComponent.h"
#include "server/zone/objects/player/components/PlayerZoneComponent.h"
#include "server/zone/objects/building/components/BuildingDataComponent.h"
#include "server/zone/objects/building/components/DestructibleBuildingDataComponent.h"
#include "server/zone/objects/building/components/ShuttleZoneComponent.h"
#include "server/zone/objects/player/components/PlayerObjectMenuComponent.h"
#include "server/zone/objects/tangible/components/ContainerObjectComponent.h"
#include "server/zone/objects/tangible/components/TrapMenuComponent.h"
#include "server/zone/objects/tangible/components/LairMenuComponent.h"
#include "server/zone/objects/tangible/components/generic/DiceMenuComponent.h"
#include "server/zone/objects/tangible/components/TangibleObjectMenuComponent.h"
#include "server/zone/objects/tangible/components/generic/LootSchematicMenuComponent.h"
#include "server/zone/objects/tangible/components/BountyHunterDroidMenuComponent.h"
#include "server/zone/objects/tangible/components/CampKitMenuComponent.h"
#include "server/zone/objects/tangible/components/CampTerminalMenuComponent.h"
#include "server/zone/objects/tangible/components/InsuranceTerminalMenuComponent.h"
#include "server/zone/objects/tangible/components/BankTerminalMenuComponent.h"
#include "server/zone/objects/tangible/components/CloningTerminalMenuComponent.h"
#include "server/zone/objects/tangible/components/HologrindHolocronMenuComponent.h"
#include "server/zone/objects/tangible/components/VillageHolocronMenuComponent.h"
#include "server/zone/objects/tangible/components/ForceShrineMenuComponent.h"
#include "server/zone/objects/tangible/components/RobeObjectMenuComponent.h"
#include "server/zone/objects/tangible/components/generic/ArtCrateMenuComponent.h"
#include "server/zone/objects/tangible/components/WeaponObjectMenuComponent.h"
#include "server/zone/objects/tangible/components/LightsaberObjectMenuComponent.h"
#include "server/zone/objects/tangible/components/SaberInventoryContainerComponent.h"
#include "server/zone/objects/tangible/components/generic/LootSchematicAttributeListComponent.h"
#include "server/zone/objects/tangible/components/RobeObjectAttributeListComponent.h"
#include "server/zone/objects/tangible/deed/components/PlaceStructureComponent.h"
#include "server/zone/objects/tangible/deed/components/PlaceCityHallComponent.h"
#include "server/zone/objects/tangible/deed/components/PlaceGCWBaseComponent.h"
#include "server/zone/objects/tangible/terminal/components/StructureTerminalMenuComponent.h"
#include "server/zone/objects/tangible/terminal/components/HQMenuComponent.h"
#include "server/zone/objects/tangible/terminal/components/UplinkTerminalMenuComponent.h"
#include "server/zone/objects/tangible/terminal/components/SecurityTerminalMenuComponent.h"
#include "server/zone/objects/tangible/terminal/components/OverrideTerminalMenuComponent.h"
#include "server/zone/objects/tangible/terminal/components/PowerRegulatorMenuComponent.h"
#include "server/zone/objects/tangible/terminal/components/TurretControlMenuComponent.h"
#include "server/zone/objects/installation/components/InstallationObjectMenuComponent.h"
#include "server/zone/objects/installation/components/FactoryObjectMenuComponent.h"
#include "server/zone/objects/installation/components/MinefieldMenuComponent.h"
#include "server/zone/ZoneContainerComponent.h"
#include "server/zone/objects/structure/components/StructureContainerComponent.h"
#include "server/zone/objects/tangible/components/ElevatorMenuComponent.h"
#include "server/zone/objects/tangible/components/ElevatorUpMenuComponent.h"
#include "server/zone/objects/tangible/components/ElevatorDownMenuComponent.h"
#include "server/zone/objects/region/components/CityManagementMenuComponent.h"
#include "server/zone/objects/region/components/CityVotingMenuComponent.h"
#include "server/zone/objects/scene/components/AiInterfaceComponent.h"
#include "server/zone/objects/scene/components/AiDummyComponent.h"
#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/objects/creature/components/AiDefaultComponent.h"
#include "server/zone/objects/creature/components/AiCreatureComponent.h"
#include "server/zone/objects/creature/components/AiNPCComponent.h"
#include "server/zone/objects/tangible/components/generic/ShellfishHarvesterMenuComponent.h"
#include "server/zone/objects/tangible/components/generic/DiceDataComponent.h"
#include "server/zone/objects/tangible/components/generic/CreatureHabitatMenuComponent.h"
#include "server/zone/objects/tangible/components/WearableObjectMenuComponent.h"
#include "server/zone/objects/building/components/CityHallZoneComponent.h"
#include "server/zone/objects/installation/components/ShuttleInstallationZoneComponent.h"
#include "server/zone/objects/tangible/firework/components/FireworkMenuComponent.h"
#include "server/zone/objects/tangible/firework/components/FireworkShowMenuComponent.h"
#include "server/zone/objects/structure/components/StructureZoneComponent.h"
#include "server/zone/objects/creature/components/TrainerMenuComponent.h"
#include "server/zone/objects/tangible/components/FireHeavyWeaponMenuComponent.h"
#include "server/zone/objects/tangible/components/ThrowGrenadeMenuComponent.h"
#include "server/zone/objects/creature/ai/components/AiStateComponent.h"
#include "server/zone/objects/creature/ai/components/AlertStateComponent.h"
#include "server/zone/objects/creature/ai/components/AttackStateComponent.h"
#include "server/zone/objects/creature/ai/components/DeathStateComponent.h"
#include "server/zone/objects/creature/ai/components/FleeStateComponent.h"
#include "server/zone/objects/creature/ai/components/RetreatStateComponent.h"
#include "server/zone/objects/creature/ai/components/SpawnStateComponent.h"
#include "server/zone/objects/creature/ai/components/StandingStateComponent.h"
#include "server/zone/objects/creature/ai/components/WanderingStateComponent.h"
#include "server/zone/objects/tangible/components/GogglesColorMenuComponent.h"
#include "server/zone/objects/tangible/components/ArmorColorMenuComponent.h"
#include "server/zone/objects/tangible/components/PlaceableLootContainerComponent.h"

ComponentManager::ComponentManager() {
	components.put("ContainerComponent", new ContainerComponent());
	components.put("PlayerContainerComponent", new PlayerContainerComponent());
	components.put("LootContainerComponent", new LootContainerComponent());

	components.put("ZoneComponent", new ZoneComponent());
	components.put("PlayerZoneComponent", new PlayerZoneComponent());
	components.put("StructureZoneComponent", new StructureZoneComponent());
	components.put("ShuttleZoneComponent", new ShuttleZoneComponent());
	components.put("ShuttleInstallationZoneComponent", new ShuttleInstallationZoneComponent());

	components.put("BuildingDataComponent", new BuildingDataComponent() );
	components.put("DestructibleBuildingDataComponent", new DestructibleBuildingDataComponent());
	dataObjectFactory.registerObject<BuildingDataComponent>("BuildingDataComponent");
	dataObjectFactory.registerObject<DestructibleBuildingDataComponent>("DestructibleBuildingDataComponent");

	components.put("ObjectMenuComponent", new ObjectMenuComponent());
	components.put("TangibleObjectMenuComponent", new TangibleObjectMenuComponent());
	components.put("PlayerObjectMenuComponent", new PlayerObjectMenuComponent());

	components.put("LootSchematicMenuComponent", new LootSchematicMenuComponent());

	components.put("BountyHunterDroidMenuComponent", new BountyHunterDroidMenuComponent());

	components.put("CampKitMenuComponent", new CampKitMenuComponent());
	components.put("CampTerminalMenuComponent", new CampTerminalMenuComponent());

	components.put("InsuranceTerminalMenuComponent", new InsuranceTerminalMenuComponent());
	components.put("BankTerminalMenuComponent", new BankTerminalMenuComponent());
	components.put("CloningTerminalMenuComponent", new CloningTerminalMenuComponent());

	components.put("ArtCrateMenuComponent", new ArtCrateMenuComponent());

	components.put("ZoneContainerComponent", new ZoneContainerComponent());

	components.put("HologrindHolocronMenuComponent", new HologrindHolocronMenuComponent());
	components.put("VillageHolocronMenuComponent", new VillageHolocronMenuComponent());

	components.put("AttributeListComponent", new AttributeListComponent());
	components.put("LootSchematicAttributeListComponent", new LootSchematicAttributeListComponent());

	components.put("RobeObjectAttributeListComponent", new RobeObjectAttributeListComponent());

	components.put("PlaceStructureComponent", new PlaceStructureComponent());
	components.put("PlaceCityHallComponent", new PlaceCityHallComponent());
	components.put("PlaceGCWBaseComponent", new PlaceGCWBaseComponent());
	components.put("StructureTerminalMenuComponent", new StructureTerminalMenuComponent());
	components.put("FactoryObjectMenuComponent", new FactoryObjectMenuComponent());
	components.put("MinefieldMenuComponent", new MinefieldMenuComponent());	
	components.put("InstallationObjectMenuComponent", new InstallationObjectMenuComponent());


	components.put("HQMenuComponent", new HQMenuComponent());
	components.put("ContainerObjectComponent", new ContainerObjectComponent());
	components.put("StructureContainerComponent", new StructureContainerComponent());

	components.put("VendorContainerComponent", new VendorContainerComponent());
	components.put("VendorMenuComponent", new VendorMenuComponent());
	components.put("VendorZoneComponent", new VendorZoneComponent());
	components.put("TurretZoneComponent", new TurretZoneComponent());
	components.put("MinefieldZoneComponent", new MinefieldZoneComponent());
	components.put("MinefieldContainerComponent", new MinefieldContainerComponent());
	components.put("DetectorZoneComponent", new DetectorZoneComponent());

	dataObjectFactory.registerObject<VendorDataComponent>("VendorDataComponent");
	dataObjectFactory.registerObject<AuctionTerminalDataComponent>("AuctionTerminalDataComponent");
	dataObjectFactory.registerObject<SecurityTerminalDataComponent>("SecurityTerminalDataComponent");
	dataObjectFactory.registerObject<TurretControlTerminalDataComponent>("TurretControlTerminalDataComponent");

	components.put("CityManagementMenuComponent", new CityManagementMenuComponent());
	components.put("CityVotingMenuComponent", new CityVotingMenuComponent());
	components.put("TrapMenuComponent", new TrapMenuComponent());

	components.put("LairMenuComponent", new LairMenuComponent());

	components.put("AiInterfaceComponent", new AiInterfaceComponent());
	components.put("AiDummyComponent", new AiDummyComponent());
	components.put("AiDefaultComponent", new AiDefaultComponent());
	components.put("AiCreatureComponent", new AiCreatureComponent());
	components.put("AiNPCComponent", new AiNPCComponent());
	components.put("WeaponObjectMenuComponent", new WeaponObjectMenuComponent());

	components.put("ShellfishHarvesterMenuComponent", new ShellfishHarvesterMenuComponent());

	components.put("DiceMenuComponent", new DiceMenuComponent());
	dataObjectFactory.registerObject<DiceDataComponent>("DiceDataComponent");

	dataObjectFactory.registerObject<TurretDataComponent>("TurretDataComponent");
	dataObjectFactory.registerObject<MinefieldDataComponent>("MinefieldDataComponent");

	dataObjectFactory.registerObject<DetectorDataComponent>("DetectorDataComponent");

	components.put("CreatureHabitatMenuComponent", new CreatureHabitatMenuComponent());
	components.put("WearableObjectMenuComponent", new WearableObjectMenuComponent());
	components.put("ArmorColorMenuComponent", new ArmorColorMenuComponent());	

	components.put("CityHallZoneComponent", new CityHallZoneComponent());

	components.put("LightsaberObjectMenuComponent", new LightsaberObjectMenuComponent());
	components.put("RobeObjectMenuComponent", new RobeObjectMenuComponent());
	components.put("ForceShrineMenuComponent", new ForceShrineMenuComponent());
	components.put("SaberInventoryContainerComponent", new SaberInventoryContainerComponent());

	components.put("FireworkMenuComponent", new FireworkMenuComponent());
	components.put("FireworkShowMenuComponent", new FireworkShowMenuComponent());
	components.put("TrainerMenuComponent", new TrainerMenuComponent());

	components.put("FireHeavyWeaponMenuComponent", new FireHeavyWeaponMenuComponent());
	components.put("ThrowGrenadeMenuComponent", new ThrowGrenadeMenuComponent());

	components.put("AiStateComponent", new AiStateComponent());
	components.put("AlertStateComponent", new AlertStateComponent());
	components.put("AttackStateComponent", new AttackStateComponent());
	components.put("DeathStateComponent", new DeathStateComponent());
	components.put("FleeStateComponent", new FleeStateComponent());
	components.put("RetreatStateComponent", new RetreatStateComponent());
	components.put("SpawnStateComponent", new SpawnStateComponent());
	components.put("StandingStateComponent", new StandingStateComponent());
	components.put("WanderingStateComponent", new WanderingStateComponent());

	components.put("ElevatorMenuComponent", new ElevatorMenuComponent());
	components.put("ElevatorUpMenuComponent", new ElevatorUpMenuComponent());
	components.put("ElevatorDownMenuComponent", new ElevatorDownMenuComponent());
	components.put("UplinkTerminalMenuComponent", new UplinkTerminalMenuComponent());
	components.put("SecurityTerminalMenuComponent", new SecurityTerminalMenuComponent());
	components.put("OverrideTerminalMenuComponent", new OverrideTerminalMenuComponent());
	components.put("PowerRegulatorMenuComponent", new PowerRegulatorMenuComponent());
	components.put("TurretControlMenuComponent", new TurretControlMenuComponent());
	components.put("GCWBaseContainerComponent", new GCWBaseContainerComponent());

	// SE Goggles.
	components.put("GogglesColorMenuComponent", new GogglesColorMenuComponent());
	components.put("PlaceableLootContainerComponent", new PlaceableLootContainerComponent());
}
