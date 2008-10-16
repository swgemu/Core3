/*
MySQL Data Transfer
Source Host: 192.168.1.180
Source Database: swgemu
Target Host: 192.168.1.180
Target Database: swgemu
Date: 10/1/2008 8:16:16 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for statictangibleobjects
-- ----------------------------
CREATE TABLE `statictangibleobjects` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `zoneid` tinyint(4) NOT NULL,
  `parentid` bigint(20) NOT NULL,
  `name` varchar(255) NOT NULL,
  `template_file` varchar(200) NOT NULL,
  `template_type` int(255) NOT NULL,
  `template_name` varchar(255) NOT NULL,
  `oX` float NOT NULL,
  `oY` float NOT NULL,
  `oZ` float NOT NULL,
  `oW` float NOT NULL,
  `X` float NOT NULL,
  `Z` float NOT NULL,
  `Y` float NOT NULL,
  PRIMARY KEY (`id`),
  KEY `zone_id` (`zoneid`),
  FULLTEXT KEY `file_ix` (`template_file`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `statictangibleobjects` VALUES ('1', '5', '0', 'Jeff Freeman Memorial Fountain', 'object/tangible/furniture/city/shared_fountain_heroic.iff', '8203', 'fountain_heroic', '0', '-0.401868', '0', '0.915698', '-4879.48', '6', '4139.49');
