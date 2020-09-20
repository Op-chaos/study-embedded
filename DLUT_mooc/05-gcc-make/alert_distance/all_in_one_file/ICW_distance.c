#include <stdio.h>
#include "common_algorithm.h"
float Vetalk_calcICWWarningDistance(float local_speed)
{
    float   readiness_time;
    float   min_safety_distance;
    float   rearvehicle_lonaccel;
	float 	Tr;
	float 	Ts;    

    min_safety_distance = 0.0f;
    readiness_time = 0.0f;
    rearvehicle_lonaccel = 0.0f;

	Tr = 2.9;  // ICW_warning_reaction_time_s;
	Ts = 0.4;

    readiness_time = Tr + Ts;
    min_safety_distance = 4;   // ICW_minsafety_distance_m;
    rearvehicle_lonaccel = -2; // ICW_decelerate_value_mps2;

    return _Vetalk_calcSafeDistance(readiness_time * 1.5, 0.0f, local_speed, 0.0f, rearvehicle_lonaccel, min_safety_distance);
}

/*
 * Vetalk_calcICWMajorDistance()
 * 
 * 计算警告级别的ICW安全距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @local_speed: 车的速度
 *
 * return
 * float，警告级别的ICW安全距离
 */

float Vetalk_calcICWMajorDistance(float local_speed)
{
    float   readiness_time;
    float   min_safety_distance;
    float   rearvehicle_lonaccel;
	float 	Tr;
	float 	Ts;    

    min_safety_distance = 0.0f;
    readiness_time = 0.0f;
    rearvehicle_lonaccel = 0.0f;
	Tr = 1.8; // ICW_major_reaction_time_s;
	Ts = 0.4;

    readiness_time = Tr + Ts;
    min_safety_distance = 4;   // ICW_minsafety_distance_m;
    rearvehicle_lonaccel = -2; // ICW_decelerate_value_mps2;

    return _Vetalk_calcSafeDistance(readiness_time, 0.0f, local_speed, 0.0f, rearvehicle_lonaccel, min_safety_distance);
}

/*
 * Vetalk_calcICWEmergencyDistance()
 * 
 * 计算严重警告级别的ICW安全距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @local_speed: 车的速度
 *
 * return
 * float，严重警告级别的ICW安全距离
 */

float Vetalk_calcICWEmergencyDistance(float local_speed)
{
    float   readiness_time;
    float   min_safety_distance;
    float   rearvehicle_lonaccel;
	float 	Tr;
	float 	Ts;

    min_safety_distance = 0.0f;
    readiness_time = 0.0f;
    rearvehicle_lonaccel = 0.0f;
    Tr = 0.6; // ICW_major_reaction_time_s;
	Ts = 0.4;
    
    readiness_time = Tr + Ts; // ICW_emergency_reaction_time_s;
    min_safety_distance = 4;   // ICW_minsafety_distance_m;
    rearvehicle_lonaccel = -2; // ICW_decelerate_value_mps2;

    return _Vetalk_calcSafeDistance(readiness_time, 0.0f, local_speed, 0.0f, rearvehicle_lonaccel, min_safety_distance);
}

extern void TA_EvaluateThreatICW(float local_speed)
{    
    float d_warning;
    float d_major;
    float d_emergency;

    d_warning = 0.0f;
    d_major = 0.0f;
    d_emergency = 0.0f;

    d_warning = Vetalk_calcICWWarningDistance(local_speed);
    d_major = Vetalk_calcICWMajorDistance(local_speed);
    d_emergency = Vetalk_calcICWEmergencyDistance(local_speed);

    printf("<ICW> d_warning:%4.2f, d_major:%4.2f, d_emergency:%4.2f\n",d_warning, d_major, d_emergency);
}