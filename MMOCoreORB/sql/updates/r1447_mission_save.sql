/*
SQLyog Community Edition- MySQL GUI v6.56
MySQL - 5.0.67-0ubuntu6 : Database - swgemu
*********************************************************************
*/ 
/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

USE `swgemu`;

/*Table structure for table `mission_save` */

DROP TABLE IF EXISTS `mission_save`;

CREATE TABLE `mission_save` (
  `saveid` mediumint(8) unsigned NOT NULL auto_increment,
  `character_id` mediumint(8) unsigned NOT NULL default '0',
  `miso_key` text NOT NULL,
  `objective_vars` text NOT NULL,
  PRIMARY KEY  (`saveid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
