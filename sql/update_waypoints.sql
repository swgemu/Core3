/*
MySQL Data Transfer
Source Host: localhost
Source Database: swgemu
Target Host: localhost
Target Database: swgemu
Date: 04.07.2008 14:02:02
*/

DROP TABLE IF EXISTS waypoints;

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for waypoints
-- ----------------------------
CREATE TABLE `waypoints` (
  `waypoint_id` bigint(20) unsigned NOT NULL,
  `owner_id` mediumint(8) unsigned NOT NULL,
  `waypoint_name` text NOT NULL,
  `x` float(10,6) default NULL,
  `y` float(10,6) default NULL,
  `planet_name` text NOT NULL,
  `active` tinyint(1) NOT NULL default '1',
  `ix` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`ix`),
  KEY `objplid` (`waypoint_id`,`owner_id`)
) ENGINE=MyISAM AUTO_INCREMENT=46 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
