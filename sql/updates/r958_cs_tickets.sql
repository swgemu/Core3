/*
MySQL Data Transfer
Source Host: 192.168.1.153
Source Database: swgemu
Target Host: 192.168.1.153
Target Database: swgemu
Date: 02/12/2008 6:01:17 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for cs_tickets
-- ----------------------------
CREATE TABLE `cs_tickets` (
  `ticket_id` int(10) unsigned NOT NULL auto_increment,
  `category_main` int(10) unsigned NOT NULL default '0',
  `category_sub` int(10) unsigned NOT NULL default '0',
  `player_name` varchar(45) NOT NULL default 'default',
  `station_id` int(10) unsigned NOT NULL default '0',
  `bug_type` varchar(45) NOT NULL default 'default',
  `repeatable` tinyint(1) NOT NULL default '0',
  `game_system` varchar(45) NOT NULL default 'default',
  `severity` tinyint(1) unsigned zerofill NOT NULL default '0',
  `position_x` float(10,6) NOT NULL default '0.000000',
  `position_y` float(10,6) NOT NULL default '0.000000',
  `position_z` float(10,6) NOT NULL default '0.000000',
  `position_heading` float(10,6) NOT NULL default '0.000000',
  `planet` varchar(20) NOT NULL default 'default',
  `cluster` varchar(45) NOT NULL default 'default',
  `race` varchar(20) NOT NULL default 'default',
  `client_version` varchar(45) NOT NULL default 'default',
  `date_time` varchar(45) NOT NULL default 'default',
  `other_info` varchar(45) NOT NULL default 'default',
  PRIMARY KEY  (`ticket_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records 
-- ----------------------------
