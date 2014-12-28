local ObjectManager = require("managers.object.object_manager")

HeroOfTatooineScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("HeroOfTatooineScreenPlay", true)

function HeroOfTatooineScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
	end
end

function HeroOfTatooineScreenPlay:spawnMobiles()
	spawnMobile("tatooine", "hermit_quest",0,36.5,-69,-103.7,0,7125586)
end