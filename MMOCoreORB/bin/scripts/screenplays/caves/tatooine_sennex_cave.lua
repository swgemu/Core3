SennexCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("SennexCaveScreenPlay", true)

function SennexCaveScreenPlay:start()
	self:spawnMobiles()
end

function SennexCaveScreenPlay:spawnMobiles()
	spawnMobile("corellia", "sennex_guard", 200, 116.123, -66.2826, -95.3285, 0, 5995572)
	spawnMobile("corellia", "sennex_guard", 200, 129.935, -66.7125, -106.683, 0, 5995572)
	spawnMobile("corellia", "sennex_guard", 200, 114.867, -66.4634, -117.855, 0, 5995572)
	spawnMobile("corellia", "sennex_slavemaster", 200, 143.509, -66.3559, -97.4195, 0, 5995572)
	spawnMobile("corellia", "sennex_hunter", 200, 73.8337, -66.3036, -137.968, 0, 5995571)
	spawnMobile("corellia", "sennex_hunter", 200, 78.5872, -65.3413, -142.072, 0, 5995571)
	spawnMobile("corellia", "sennex_guard", 200, 94.7662, -66.4373, -126.37, 0, 5995571)
	spawnMobile("corellia", "sennex_hunter", 200, 55.9044, -77.0308, -89.3457, 0, 5995570)
	spawnMobile("corellia", "sennex_hunter", 200, 54.9212, -71.576, -113.891, 0, 5995570)
	spawnMobile("corellia", "sennex_slaver", 200, 64.2851, -75.4256, -63.1042, 0, 5995568)
	spawnMobile("corellia", "sennex_slaver", 200, 94.6285, -75.6847, -64.7793, 0, 5995568)
	spawnMobile("corellia", "sennex_slaver", 200, 96.0028, -74.9623, -60.3445, 0, 5995568)
	spawnMobile("corellia", "sennex_slaver", 200, 91.5029, -67.4595, -39.297, 0, 5995567)
	spawnMobile("corellia", "sennex_slaver", 200, 92.9404, -61.9192, -14.6306, 0, 5995567)
	spawnMobile("corellia", "sennex_warder", 200, 86.7526, -61.1646, -7.92715, 0, 5995567)
	spawnMobile("corellia", "sennex_warder", 200, 49.9988, -47.6495, -10.4063, 0, 5995566)
	spawnMobile("corellia", "sennex_warder", 200, 42.2651, -46.4763, -13.0341, 0, 5995566)
	spawnMobile("corellia", "sennex_warder", 200, 53.5455, -48.8176, -60.8162, 0, 5995566)
	spawnMobile("corellia", "sennex_lookout", 200, 46.289, -47.8764, -59.2666, 0, 5995566)
	spawnMobile("corellia", "sennex_warder", 200, 26.4313, -43.0135, -66.9426, 0, 5995566)
	spawnMobile("corellia", "sennex_lookout", 200, 26.5043, -37.7114, -31.1657, 0, 5995566)
	spawnMobile("corellia", "sennex_lookout", 200, 22.1221, -34.8329, -24.0482, 0, 5995566)
	spawnMobile("corellia", "sennex_warder", 200, 54.5038, -68.105, -36.6345, 0, 5995566)
	spawnMobile("corellia", "sennex_slaver", 200, 54.0815, -68.2377, -40.9112, 0, 5995566)
	spawnMobile("corellia", "sennex_lookout", 200, 13.3221, -22.336, -6.4, 0, 5995565)
	spawnMobile("corellia", "sennex_lookout", 200, -14.763, -4.95023, -9.4686, 0, 5995565)

	--Beetles
	spawnMobile("corellia", "cave_beetle", 200, 84.6138, -46.3756, -111.955, 0, 5995569)
	spawnMobile("corellia", "large_rock_beetle", 200, 90.6391, -46.5946, -107.052, 0, 5995569)
	spawnMobile("corellia", "cave_beetle", 200, 94.9631, -46.6007, -134.941, 0, 5995575)
	spawnMobile("corellia", "cave_beetle", 200, 88.5285, -46.5252, -146.986, 0, 5995575)
	spawnMobile("corellia", "large_cave_beetle", 200, 82.3354, -46.5893, -144.681, 0, 5995575)
	spawnMobile("corellia", "cave_beetle", 200, 77.9578, -46.3635, -137.141, 0, 5995575)
	spawnMobile("corellia", "rock_beetle", 200, 49.3657, -51.5992, -82.1096, 0, 5995574)
	spawnMobile("corellia", "cave_beetle", 200, 54.0389, -48.7402, -105.26, 0, 5995574)
	spawnMobile("corellia", "rock_beetle", 200, 47.5229, -51.848, -87.5113, 0, 5995574)

	---OutSide Beetles
	--spawnCreature(duneBeetle, 8, 6547.05, -1311.56)
	--spawnCreature(duneBeetle, 8, 6552.22, -1325.97)
	--spawnCreature(duneBeetle, 8, 6566.36, -1330.49)
end