function Outfit(name, clothes)
	return {
		outfitName = name,
		clothing = clothes
	}
end

function addOutfit(o)
	table.insert(Outfits, o)
end

-- All Outfits
Outfits = {}

-- Default Outfit (HUMANIODS ONLY)
addOutfit(Outfit("default", {"object/tangible/wearables/shirt/shirt_s03.iff", "object/tangible/wearables/pants/pants_s01.iff", "object/tangible/wearables/shoes/shoes_s01.iff"}))

-- Run the subScripts
dofile("scripts/mobile/wearables/humanoid_outfits.lua")
dofile("scripts/mobile/wearables/humanoid_female_outfits.lua")
dofile("scripts/mobile/wearables/ithorian_outfits.lua")
dofile("scripts/mobile/wearables/wookiee_outfits.lua")
dofile("scripts/mobile/wearables/trandoshan_outfits.lua")
dofile("scripts/mobile/wearables/trandoshan_female_outfits.lua")
