/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80033 (8.0.33)
 Source Host           : localhost:3306
 Source Schema         : lab4.4

 Target Server Type    : MySQL
 Target Server Version : 80033 (8.0.33)
 File Encoding         : 65001

 Date: 24/12/2023 21:05:59
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for account
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account`  (
  `account_id` char(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `account_name` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `balance` decimal(10, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`account_id`) USING BTREE,
  CONSTRAINT `account_chk_1` CHECK (`balance` >= 0)
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of account
-- ----------------------------
INSERT INTO `account` VALUES ('202111', 'KeQing', 400.00);
INSERT INTO `account` VALUES ('202112', 'GanYu', 1600.00);

-- ----------------------------
-- Procedure structure for p_transfer
-- ----------------------------
DROP PROCEDURE IF EXISTS `p_transfer`;
delimiter ;;
CREATE PROCEDURE `p_transfer`(from_account CHAR(6),
    to_account CHAR(6),
    amount DECIMAL(10,2))
BEGIN
	# DECLARE EXIT HANDLER FOR SQLEXCEPTION ROLLBACK;
	START TRANSACTION;
		UPDATE account 
			SET balance = balance + amount 
			WHERE account_id = to_account;
		UPDATE account 
			SET balance = balance - amount 
			WHERE account_id = from_account;
	COMMIT;
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
