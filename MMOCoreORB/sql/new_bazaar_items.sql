/*
MySQL Data Transfer
Source Host: localhost
Source Database: swgemu
Target Host: localhost
Target Database: swgemu
Date: 27/02/2008 20:36:46
*/

SET FOREIGN_KEY_CHECKS=0;
DROP TABLE `bazaar_items`;
-- ----------------------------
-- Table structure for bazaar_items
-- ----------------------------
CREATE TABLE `bazaar_items` (
  `objectid` bigint(20) unsigned NOT NULL,
  `name` varchar(45) NOT NULL,
  `description` text NOT NULL,
  `item_type` int(10) unsigned NOT NULL,
  `ownerid` bigint(20) unsigned NOT NULL,
  `ownername` varchar(45) NOT NULL,
  `price` int(10) unsigned NOT NULL,
  `auction` tinyint(1) NOT NULL,
  `sold` tinyint(1) NOT NULL default '0',
  `expire` bigint(20) unsigned NOT NULL,
  `terminalid` bigint(20) unsigned NOT NULL,
  `planet` smallint(5) unsigned NOT NULL,
  `buyerid` bigint(20) unsigned NOT NULL default '0',
  `biddername` varchar(45) NOT NULL,
  PRIMARY KEY  (`objectid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
