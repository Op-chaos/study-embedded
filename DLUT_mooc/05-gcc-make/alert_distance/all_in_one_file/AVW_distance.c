#include "AVW_distance.h"

float Vetalk_calcAVWWarningDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   readiness_time = 0.0;
    float   min_safety_distance = 0.0;    
    float   rearvehicle_lonaccel = 0.0;
	float 	Tr = 3.2;
	float 	Ts = 0.4;    

    readiness_time = Tr + Ts;
    min_safety_distance = 2;
    rearvehicle_lonaccel = -3;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return 1000;
    } 

}

/*
 * Vetalk_calcAVWMajorDistance()
 * 
 * 计算警告级别的AVW安全距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加速度
 *
 * return
 * 警告级别的AVW安全距离
 */
float Vetalk_calcAVWMajorDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   readiness_time = 0.0f;
    float   min_safety_distance = 0.0f;    
    float   rearvehicle_lonaccel = 0.0f;
	float 	Tr = 1.8f;
	float 	Ts = 0.4f;

    readiness_time = Tr + Ts;
    min_safety_distance = 2;
    rearvehicle_lonaccel = -3;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return 1000.0;
    } 
}

/*
 * Vetalk_calcAVWEmergencyDistance()
 * 
 * 计算严重警告级别的AVW安全距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加速度
 *
 * return
 * 严重警告级别的AVW安全距离
 */
float Vetalk_calcAVWEmergencyDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   readiness_time = 0.0f;
    float   min_safety_distance = 0.0f;    
    float   rearvehicle_lonaccel = 0.0f;
	float 	Ts = 0.4f;    
	float 	Tr = 0.6f;    

    readiness_time = Ts + Tr;
    min_safety_distance = 2;
    rearvehicle_lonaccel = -3;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return 1000;
    } 
    
}