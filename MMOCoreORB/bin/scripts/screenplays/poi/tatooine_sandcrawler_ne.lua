SandcrawlerNeScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("SandcrawlerNeScreenPlay", true)

function SandcrawlerNeScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
	end
end

function SandcrawlerNeScreenPlay:spawnMobiles()
	spawnMobile("tatooine", "jawa_avenger", 300, 5770.7, 49.8, 3992.8, 85, 0)
	spawnMobile("tatooine", "jawa_avenger", 300, 5781.4, 50.3, 3984.4, -10, 0)
	spawnMobile("tatooine", "jawa_avenger", 300, 5736.8, 53.5, 4016.4, 165, 0)
	spawnMobile("tatooine", "jawa_avenger", 300, 5733.1, 52.1, 4014.4, 165, 0)

	spawnMobile("tatooine", "jawa_engineer", 300, 5775.6, 53, 4009.3, -35, 0)
	spawnMobile("tatooine", "jawa_engineer", 300, 5768.2, 53.5, 4009.9, -10, 0)
	spawnMobile("tatooine", "jawa_engineer", 300, 5762, 52.1, 4005.4, 15, 0)
	spawnMobile("tatooine", "jawa_engineer", 300, 5751.3, 53.9, 4011.2, 30, 0)
	spawnMobile("tatooine", "jawa_engineer", 300, 5775.2, 51.2, 3977.1, 0, 0)

	spawnMobile("tatooine", "jawa_healer", 300, 5759, 52.3, 4005.8, -115, 0)
	spawnMobile("tatooine", "jawa_healer", 300, 5781.5, 50.4, 3982.9, -90, 0)
	spawnMobile("tatooine", "jawa_healer", 300, 5773, 51.1, 3977.3, 30, 0)
	spawnMobile("tatooine", "jawa_healer", 300, 5761.9, 49.9, 3987.4, 65, 0)
	spawnMobile("tatooine", "jawa_healer", 300, 5766.7, 49.8, 3988.2, 85, 0)
	spawnMobile("tatooine", "jawa_healer", 300, 5764, 52.7, 4007.3, 130, 0)

	spawnMobile("tatooine", "jawa_henchman", 300, 5776.4, 50.5, 4000.2, 90, 0)
	spawnMobile("tatooine", "jawa_henchman", 300, 5763.2, 50.5, 3998.5, -133, 0)
	spawnMobile("tatooine", "jawa_henchman", 300, 5748, 50.7, 3987.4, -165, 0)
	spawnMobile("tatooine", "jawa_henchman", 300, 5745, 50.2, 3997.4, -13, 0)
	spawnMobile("tatooine", "jawa_henchman", 300, 5805.3, 51.5, 3990.7, 135, 0)

	spawnMobile("tatooine", "jawa_leader", 300, 5757.0, 51.1, 4001.1, 175, 0)
	spawnMobile("tatooine", "jawa_leader", 300, 5768.8, 52.2, 4006.3, 130, 0)	

	spawnMobile("tatooine", "jawa_protector", 300, 5775.4, 49.7, 3989.3, 85, 0)
	spawnMobile("tatooine", "jawa_protector", 300, 5777.3, 49.7, 3990.6, -110, 0)
	spawnMobile("tatooine", "jawa_protector", 300, 5796.3, 50.7, 4004.5, -110, 0)
	spawnMobile("tatooine", "jawa_protector", 300, 5802.4, 51.2, 3990.8, 170, 0)

	spawnMobile("tatooine", "jawa_thief", 300, 5793.7, 50.5, 4001.3, 115, 0)
	spawnMobile("tatooine", "jawa_thief", 300, 5793.4, 50.3, 3993.1, -170, 0)
	spawnMobile("tatooine", "jawa_thief", 300, 5784.4, 54.5, 3978.8, 85, 0)
	spawnMobile("tatooine", "jawa_thief", 300, 5780.2, 55.9, 3975.5, 110, 0)

	spawnMobile("tatooine", "jawa_warlord", 300, 5788.8, 50.8, 3983.9, 120, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5788.5, 50.1, 3993.6, -85, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5791.2, 51.9, 4008.8, -85, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5764.2, 51.4, 3977.4, -140, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5782.1, 50.7, 4001.9, 70, 0)

	spawnMobile("tatooine", "tusken_bantha", 480, 5803, 54.2, 3952.8, -33, 0)
	spawnMobile("tatooine", "tusken_bantha", 480, 5793.4, 54.8, 3948.4, -33, 0)
	
	spawnMobile("tatooine", "tusken_raider", 480, 5809, 55.6, 3968.6, -40, 0)
	spawnMobile("tatooine", "tusken_raider", 480, 5813.1, 55.4, 3971.6, -40, 0)
	spawnMobile("tatooine", "tusken_raider", 480, 5806.2, 53.0, 3982.4, -45, 0)
	spawnMobile("tatooine", "tusken_raider", 480, 5803.5, 53.0, 3980.2, -60, 0)
	spawnMobile("tatooine", "tusken_raider", 480, 5800.6, 53.1, 3977.2, -60, 0)
	spawnMobile("tatooine", "tusken_raider", 480, 5797.2, 53.3, 3973.9, -55, 0)
	spawnMobile("tatooine", "tusken_raider", 480, 5781.5, 54.2, 3960.6, -5, 0)
	spawnMobile("tatooine", "tusken_raider", 480, 5768.9, 53.9, 3966.5, 0, 0)
	spawnMobile("tatooine", "tusken_raider", 480, 5748.1, 54.6, 3970.4, 30, 0)
	spawnMobile("tatooine", "tusken_raider", 480, 5746.5, 52.6, 3978.5, 45, 0)
	spawnMobile("tatooine", "tusken_raider", 480, 5740.8, 51.3, 3985.6, 35, 0)
	spawnMobile("tatooine", "tusken_raider", 480, 5739.1, 54.0, 3976.2, 50, 0)

	spawnMobile("tatooine", "tusken_commoner", 480, 5770.3, 50.2, 3983.4, 15, 0)
	spawnMobile("tatooine", "tusken_commoner", 480, 5756.3, 50.3, 3995.2, 95, 0)
	spawnMobile("tatooine", "tusken_commoner", 480, 5784.4, 50.7, 4001.9, -105, 0)
	spawnMobile("tatooine", "tusken_commoner", 480, 5798.9, 54.5, 3950.6, 0, 0)

	spawnMobile("tatooine", "tusken_raid_leader", 900, 5738.5, 56.7, 3965.8, 33, 0)
	spawnMobile("tatooine", "tusken_chief", 900, 5798.0, 56.0, 3961.1, -45, 0)

end

