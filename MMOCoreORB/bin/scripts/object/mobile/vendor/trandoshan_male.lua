--Copyright (C) 2007 <SWGEmu>

--This File is part of Core3.

--This program is free software; you can redistribute
--it and/or modify it under the terms of the GNU Lesser
--General Public License as published by the Free Software
--Foundation; either version 2 of the License,
--or (at your option) any later version.

--This program is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--See the GNU Lesser General Public License for
--more details.

--You should have received a copy of the GNU Lesser General
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

--Linking Engine3 statically or dynamically with other modules
--is making a combined work based on Engine3.
--Thus, the terms and conditions of the GNU Lesser General Public License
--cover the whole combination.

--In addition, as a special exception, the copyright holders of Engine3
--give you permission to combine Engine3 program with free software
--programs or libraries that are released under the GNU LGPL and with
--code included in the standard release of Core3 under the GNU LGPL
--license (or modified versions of such code, with unchanged license).
--You may copy and distribute such a system following the terms of the
--GNU LGPL for Engine3 and the licenses of the other code concerned,
--provided that you include the source code of that other code when
--and as the GNU LGPL requires distribution of source code.

--Note that people who make modified versions of Engine3 are not obligated
--to grant this special exception for their modified versions;
--it is their choice whether to do so. The GNU Lesser General Public License
--gives permission to release a modified version without this exception;
--this exception also makes it possible to release a modified version
--which carries forward this exception.


object_mobile_vendor_trandoshan_male = object_mobile_vendor_shared_trandoshan_male:new {

	templateType = VENDORCREATURE,
	optionsBitmask = 386,
	pvpStatusBitmask = 0,

	objectMenuComponent = {"cpp", "VendorMenuComponent"},
	dataObjectComponent = "VendorDataComponent",	
	containerComponent = {"cpp", "VendorContainerComponent"},

	noTrade = 1,

	hair = {"object/tangible/hair/trandoshan/hair_trandoshan_male_s01.iff","object/tangible/hair/trandoshan/hair_trandoshan_male_s02.iff","object/tangible/hair/trandoshan/hair_trandoshan_male_s03.iff",
		"object/tangible/hair/trandoshan/hair_trandoshan_male_s04.iff","object/tangible/hair/trandoshan/hair_trandoshan_male_s05.iff","object/tangible/hair/trandoshan/hair_trandoshan_male_s06.iff",
		"object/tangible/hair/trandoshan/hair_trandoshan_male_s07.iff","object/tangible/hair/trandoshan/hair_trandoshan_male_s08.iff","object/tangible/hair/trandoshan/hair_trandoshan_male_s09.iff",
		"object/tangible/hair/trandoshan/hair_trandoshan_male_s10.iff","object/tangible/hair/trandoshan/hair_trandoshan_male_s11.iff","object/tangible/hair/trandoshan/hair_trandoshan_male_s12.iff",
		"object/tangible/hair/trandoshan/hair_trandoshan_male_s13.iff","object/tangible/hair/trandoshan/hair_trandoshan_male_s14.iff"},


	clothing = {"Trandoshan1","Trandoshan2","Trandoshan3","Trandoshan4","Trandoshan5","Trandoshan6","Trandoshan7","Trandoshan8","Trandoshan9","Trandoshan10",
			"Trandoshan11","Trandoshan12","Trandoshan13","Trandoshan14","Trandoshan15","Trandoshan16","Trandoshan17","Trandoshan18","Trandoshan19","Trandoshan20",
			"Trandoshan21","Trandoshan22","Trandoshan23","Trandoshan24","Trandoshan25","Trandoshan26","Trandoshan27","Trandoshan28","Trandoshan29","Trandoshan30",
			"Trandoshan31","Trandoshan32","Trandoshan33","Trandoshan34","Trandoshan35","Trandoshan36","Trandoshan37","Trandoshan38","Trandoshan39","Trandoshan40",
			"Trandoshan41","Trandoshan42","Trandoshan43","Trandoshan44","Trandoshan45","Trandoshan46","Trandoshan47","Trandoshan48","Trandoshan49","Trandoshan50",
			"Trandoshan51","Trandoshan52","Trandoshan53","Trandoshan54","Trandoshan55","Trandoshan56","Trandoshan57","Trandoshan58","Trandoshan59","Trandoshan60",
			"Trandoshan61","Trandoshan62","Trandoshan63","Trandoshan64","Trandoshan65","Trandoshan66","Trandoshan67","Trandoshan68","Trandoshan69","Trandoshan70",
			"Trandoshan71","Trandoshan72","Trandoshan73","Trandoshan74","Trandoshan75","Trandoshan76","Trandoshan77","Trandoshan78","Trandoshan79","Trandoshan80",
			"Trandoshan81","Trandoshan82","Trandoshan83","Trandoshan84","Trandoshan85","Trandoshan86","Trandoshan87","Trandoshan88","Trandoshan89","Trandoshan90",
			"Trandoshan91","Trandoshan92","Trandoshan93","Trandoshan94","Trandoshan95","Trandoshan96","Trandoshan97","Trandoshan98","Trandoshan99","Trandoshan100",
			"Trandoshan101","Trandoshan102","Trandoshan103","Trandoshan104","Trandoshan105","Trandoshan106","Trandoshan107","Trandoshan108","Trandoshan109","Trandoshan110",
			"Trandoshan111","Trandoshan112","Trandoshan113","Trandoshan114","Trandoshan115","Trandoshan116","Trandoshan117","Trandoshan118","Trandoshan119","Trandoshan120",
			"Trandoshan121","Trandoshan122","Trandoshan123","Trandoshan124","Trandoshan125","Trandoshan126","Trandoshan127","Trandoshan128","Trandoshan129","Trandoshan130",
			"Trandoshan131","Trandoshan132","Trandoshan133","Trandoshan134","Trandoshan135","Trandoshan136","Trandoshan137","Trandoshan138","Trandoshan139","Trandoshan140",
			"Trandoshan141","Trandoshan142","Trandoshan143","Trandoshan144","Trandoshan145","Trandoshan146","Trandoshan147","Trandoshan148","Trandoshan149","Trandoshan150",
			"Trandoshan151","Trandoshan152","Trandoshan153","Trandoshan154","Trandoshan155","Trandoshan156","Trandoshan157","Trandoshan158","Trandoshan159","Trandoshan160",
			"Trandoshan161","Trandoshan162","Trandoshan163","Trandoshan164","Trandoshan165","Trandoshan166","Trandoshan167","Trandoshan168","Trandoshan169","Trandoshan170",
			"Trandoshan171","Trandoshan172","Trandoshan173","Trandoshan174","Trandoshan175","Trandoshan176","Trandoshan177","Trandoshan178","Trandoshan179","Trandoshan180",
			"Trandoshan181","Trandoshan182","Trandoshan183","Trandoshan184","Trandoshan185","Trandoshan186","Trandoshan187","Trandoshan188","Trandoshan189","Trandoshan190",
			"Trandoshan191","Trandoshan192","Trandoshan193","Trandoshan194","Trandoshan195","Trandoshan196","Trandoshan197","Trandoshan198","Trandoshan199","Trandoshan200",
			"Trandoshan201","Trandoshan202","Trandoshan203","Trandoshan204","Trandoshan205","Trandoshan206","Trandoshan207","Trandoshan208","Trandoshan209","Trandoshan210",
			"Trandoshan211","Trandoshan212","Trandoshan213","Trandoshan214","Trandoshan215","Trandoshan216","Trandoshan217","Trandoshan218","Trandoshan219","Trandoshan220",
			"Trandoshan221","Trandoshan222","Trandoshan223","Trandoshan224","Trandoshan225","Trandoshan226","Trandoshan227","Trandoshan228","Trandoshan229","Trandoshan230",
			"Trandoshan231","Trandoshan232","Trandoshan233","Trandoshan234","Trandoshan235","Trandoshan236","Trandoshan237","Trandoshan238","Trandoshan239","Trandoshan240",
			"Trandoshan241","Trandoshan242","Trandoshan243","Trandoshan244","Trandoshan245","Trandoshan246","Trandoshan247","Trandoshan248","Trandoshan249","Trandoshan250",
			"Trandoshan251","Trandoshan252","Trandoshan253","Trandoshan254","Trandoshan255","Trandoshan256","Trandoshan257","Trandoshan258","Trandoshan259","Trandoshan260",
			"Trandoshan261","Trandoshan262","Trandoshan263","Trandoshan264","Trandoshan265","Trandoshan266","Trandoshan267","Trandoshan268","Trandoshan269","Trandoshan270",
			"Trandoshan271","Trandoshan272","Trandoshan273","Trandoshan274","Trandoshan275","Trandoshan276","Trandoshan277","Trandoshan278","Trandoshan279","Trandoshan280",
			"Trandoshan281","Trandoshan282","Trandoshan283","Trandoshan284","Trandoshan285","Trandoshan286","Trandoshan287","Trandoshan288","Trandoshan289","Trandoshan290",
			"Trandoshan291","Trandoshan292","Trandoshan293","Trandoshan294","Trandoshan295","Trandoshan296","Trandoshan297","Trandoshan298","Trandoshan299","Trandoshan300",
			"Trandoshan301","Trandoshan302","Trandoshan303","Trandoshan304","Trandoshan305","Trandoshan306","Trandoshan307","Trandoshan308","Trandoshan309","Trandoshan310",
			"Trandoshan311","Trandoshan312","Trandoshan313","Trandoshan314","Trandoshan315","Trandoshan316","Trandoshan317","Trandoshan318","Trandoshan319","Trandoshan320",
			"Trandoshan321","Trandoshan322","Trandoshan323","Trandoshan324","Trandoshan325","Trandoshan326","Trandoshan327","Trandoshan328","Trandoshan329","Trandoshan330",
			"Trandoshan331","Trandoshan332","Trandoshan333","Trandoshan334","Trandoshan335","Trandoshan336","Trandoshan337","Trandoshan338","Trandoshan339","Trandoshan340",
			"Trandoshan341","Trandoshan342","Trandoshan343","Trandoshan344","Trandoshan345","Trandoshan346","Trandoshan347","Trandoshan348","Trandoshan349","Trandoshan350",
			"Trandoshan351","Trandoshan352","Trandoshan353","Trandoshan354","Trandoshan355","Trandoshan356","Trandoshan357","Trandoshan358","Trandoshan359","Trandoshan360",
			"Trandoshan361","Trandoshan362","Trandoshan363","Trandoshan364","Trandoshan365","Trandoshan366","Trandoshan367","Trandoshan368","Trandoshan369","Trandoshan370",
			"Trandoshan371","Trandoshan372","Trandoshan373","Trandoshan374","Trandoshan375","Trandoshan376","Trandoshan377","Trandoshan378","Trandoshan379","Trandoshan380",
			"Trandoshan381","Trandoshan382","Trandoshan383","Trandoshan384","Trandoshan385","Trandoshan386","Trandoshan387","Trandoshan388","Trandoshan389","Trandoshan390",
			"Trandoshan391","Trandoshan392","Trandoshan393","Trandoshan394","Trandoshan395","Trandoshan396","Trandoshan397","Trandoshan398","Trandoshan399","Trandoshan400",
			"Trandoshan401","Trandoshan402","Trandoshan403","Trandoshan404","Trandoshan405","Trandoshan406","Trandoshan407","Trandoshan408","Trandoshan409","Trandoshan410",
			"Trandoshan411","Trandoshan412","Trandoshan413","Trandoshan414","Trandoshan415","Trandoshan416","Trandoshan417","Trandoshan418","Trandoshan419","Trandoshan420",
			"Trandoshan421","Trandoshan422","Trandoshan423","Trandoshan424","Trandoshan425","Trandoshan426","Trandoshan427","Trandoshan428","Trandoshan429","Trandoshan430",
			"Trandoshan431","Trandoshan432","Trandoshan433","Trandoshan434","Trandoshan435","Trandoshan436","Trandoshan437","Trandoshan438","Trandoshan439","Trandoshan440",
			"Trandoshan441","Trandoshan442","Trandoshan443","Trandoshan444","Trandoshan445","Trandoshan446","Trandoshan447","Trandoshan448","Trandoshan449","Trandoshan450",
			"Trandoshan451","Trandoshan452","Trandoshan453","Trandoshan454","Trandoshan455","Trandoshan456","Trandoshan457","Trandoshan458","Trandoshan459","Trandoshan460",
			"Trandoshan461","Trandoshan462","Trandoshan463","Trandoshan464","Trandoshan465","Trandoshan466","Trandoshan467","Trandoshan468","Trandoshan469","Trandoshan470",
			"Trandoshan471","Trandoshan472","Trandoshan473","Trandoshan474","Trandoshan475","Trandoshan476","Trandoshan477","Trandoshan478","Trandoshan479","Trandoshan480",
			"Trandoshan481","Trandoshan482","Trandoshan483","Trandoshan484","Trandoshan485","Trandoshan486","Trandoshan487","Trandoshan488","Trandoshan489","Trandoshan490",
			"Trandoshan491","Trandoshan492","Trandoshan493","Trandoshan494","Trandoshan495","Trandoshan496","Trandoshan497","Trandoshan498","Trandoshan499","Trandoshan500",
			"Trandoshan501","Trandoshan502","Trandoshan503","Trandoshan504","Trandoshan505","Trandoshan506","Trandoshan507","Trandoshan508","Trandoshan509","Trandoshan510",
			"Trandoshan511","Trandoshan512","Trandoshan513"}

}

ObjectTemplates:addTemplate(object_mobile_vendor_trandoshan_male, "object/mobile/vendor/trandoshan_male.iff")
