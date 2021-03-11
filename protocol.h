/*
  视觉与电控通信协议
*/

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AI_NOTICE_AOTUAIM (1 << 0)
#define AI_NOTICE_HITSWITCH (1 << 1)
#define AI_NOTICE_AUTOMATIC (1 << 2)
#define AI_NOTICE_FIRE (1 << 3)

#define AI_ID_MCU (0xC4)
#define AI_ID_REF (0xA8)

typedef uint8_t Protocol_ID_t;

/* 电控 -> 视觉 MCU数据结构体*/
typedef struct __attribute__((packed)) {
  struct __attribute__((packed)) {
    float q0;
    float q1;
    float q2;
    float q3;
  } quat; /* 四元数 */

  uint8_t notice; /* 控制命令 */

  float ball_speed; /* 子弹初速度 */

  struct __attribute__((packed)) {
    float left;
    float right;
  } distance; /* 左右距离(哨兵) */

  float chassis_speed; /* 底盘速度(哨兵) */
} Protocol_UpDataMCU_t;

/* 电控 -> 视觉 裁判系统数据结构体*/
typedef struct __attribute__((packed)) {
  uint16_t example;
} Protocol_UpDataReferee_t;

/* 视觉 -> 电控 数据结构体*/
typedef struct __attribute__((packed)) {
  struct __attribute__((packed)) {
    float yaw;    /* 偏航角（Yaw angle） */
    float pit;    /* 俯仰角（Pitch angle） */
    float rol;    /* 翻滚角（Roll angle） */
  } gimbal_delta; /* 欧拉角的变化量 */

  uint8_t notice; /* 控制命令 */

  struct __attribute__((packed)) {
    float vx;         /* x轴移动速度 */
    float vy;         /* y轴移动速度 */
    float wz;         /* z轴转动速度 */
  } chassis_move_vec; /* 底盘移动向量 */
} Protocol_DownData_t;

typedef struct __attribute__((packed)) {
  Protocol_UpDataMCU_t data;
  uint16_t crc16;
} Protocol_UpPackageMCU_t;

typedef struct __attribute__((packed)) {
  Protocol_UpDataReferee_t data;
  uint16_t crc16;
} Protocol_UpPackageReferee_t;

typedef struct __attribute__((packed)) {
  Protocol_DownData_t data;
  uint16_t crc16;
} Protocol_DownPackage_t;

#ifdef __cplusplus
}
#endif
