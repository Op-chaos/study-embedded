#include <stdio.h>
#include <stdlib.h>
#include "common_algorithm.h"
#define SAFE_DISTANCE     -1.0f

/*
 * Vetalk_calcAVWSlowedDistance()
 * 
 * 计算主车已刹车的AVW安全距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加�?�? * @rearvehicle_lonaccel: 后车加�?�? *
 * return
 * float，主车已刹车的AVW安全距离
 */
float Vetalk_calcAVWSlowedDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel)
{
    float   readiness_time = 0.0f;
    float   min_safety_distance = 0.0f;

    min_safety_distance = 2; //.Min_Safety_Distance_m;

    if (frontvehicle_speed > rearvehicle_speed) {
        return SAFE_DISTANCE;
    } else {

        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

    }
}

/*
 * Vetalk_calcAVWWarningDistance()
 * 
 * 计算提示级别的AVW安全距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加�?�? *
 *
 * return
 * float，提示级别的AVW安全距离
 */
float Vetalk_calcAVWWarningDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   readiness_time = 0.0f;
    float   min_safety_distance = 0.0f;    
    float   rearvehicle_lonaccel = 0.0f;
	float 	Tr = 0.0f;
	float 	Ts = 0.0f;

	Tr = 3.2;   //.AVW_warning_reaction_time_s;
	Ts = 0.6;

    readiness_time = Tr + Ts;
    min_safety_distance = 2;     //.Min_Safety_Distance_m;
    rearvehicle_lonaccel = -3;   //.AVW_min_decelerate_mps2;

    if (frontvehicle_speed < rearvehicle_speed ) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return SAFE_DISTANCE;
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
 * @frontvehicle_lonaccel: 前车加�?�? *
 * return
 * 警告级别的AVW安全距离
 */
float Vetalk_calcAVWMajorDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   readiness_time = 0.0f;
    float   min_safety_distance = 0.0f;    
    float   rearvehicle_lonaccel = 0.0f;
	float 	Tr = 0.0f;
	float 	Ts = 0.0f;    

	Tr = 1.8;    //.AVW_major_reaction_time_s;
    
	Ts = 0.6;

    readiness_time = Tr + Ts;
    min_safety_distance = 2;  //.Min_Safety_Distance_m;
    rearvehicle_lonaccel = -3;  //.AVW_min_decelerate_mps2;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return SAFE_DISTANCE;
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
 * @frontvehicle_lonaccel: 前车加�?�? *
 * return
 * 严重警告级别的AVW安全距离
 */
float Vetalk_calcAVWEmergencyDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   readiness_time = 0.0f;
    float   min_safety_distance = 0.0f;    
    float   rearvehicle_lonaccel = 0.0f;
	float 	Ts = 0.0f;    
	float 	Tr = 0.0f;    

    Tr = 0.6;   //.AVW_emergency_reaction_time_s;
	Ts = 0.6;

    readiness_time = Ts + Tr;
    min_safety_distance = 2;  //.Min_Safety_Distance_m;
    rearvehicle_lonaccel = -3; //.AVW_min_decelerate_mps2;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return SAFE_DISTANCE;
    } 
    
}

/*
 * Vetalk_calcAVWWarningFlexibleDistance()
 * 
 * 计算提示级别的AVW安全回置距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加�?�? *
 *
 * return
 * float，提示级别的AVW安全回置距离
 */
float Vetalk_calcAVWWarningFlexibleDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    return (float)(1.0f + 5.0f / 100.0f) * (Vetalk_calcAVWWarningDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel));
}

/*
 * Vetalk_calcAVWMajorFlexibleDistance()
 * 
 * 计算警告级别的AVW安全回置距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加�?�? *
 *
 * return
 * float，警告级别的AVW安全回置距离
 */
float Vetalk_calcAVWMajorFlexibleDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    return (float)(1.0f + 5.0f / 100.0f) * (Vetalk_calcAVWMajorDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel));
}

/*
 * Vetalk_calcAVWMajorFlexibleDistance()
 * 
 * 计算警告级别的AVW安全回置距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加�?�? *
 *
 * return
 * float，警告级别的AVW安全回置距离
 */
float Vetalk_calcAVWEmergencyFlexibleDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    return (float)(1.0f + 5.0f / 100.0f) * (Vetalk_calcAVWEmergencyDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel));
}

void TA_EvaluateThreatAVW(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel)
{
    float d;
    float d_warning;
    float d_major;
    float d_emergency;
    float d_slowed;
    int kind = 1;           // 1:AHEAD

    d = 0.0f;
    d_warning = 0.0f;
    d_major = 0.0f;
    d_emergency = 0.0f;
    d_slowed = 0.0f;

    /*  ahead has soft , hard severe levels */
    if (frontvehicle_speed < 0) {
        d_warning = -1;
        d_major = -1;
        d_emergency = -1;
    } else if (kind == 1) {
        /* 车辆已刹车，并且减�?度达到一定程度，不�?虑反映时间，使用已减速公�?*/
        if (rearvehicle_lonaccel < -3) {

            /* The vehicle has slowed down */
            d_slowed = Vetalk_calcAVWSlowedDistance(frontvehicle_speed, 
                                                    rearvehicle_speed, 
                                                    frontvehicle_lonaccel, 
                                                    rearvehicle_lonaccel);
            d_warning = d_slowed;
            d_major = -1;
            d_emergency = -1;
        } else {
            d_warning = Vetalk_calcAVWWarningDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel);
            d_major = Vetalk_calcAVWMajorDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel);
            d_emergency = Vetalk_calcAVWEmergencyDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel);
        }
    } else {
        /* 车辆已刹车，并且减�?度达到一定程度，不�?虑反映时间，使用已减速公�?*/
        if (rearvehicle_lonaccel < -3) {

            /* The vehicle has slowed down */
            d_slowed = Vetalk_calcAVWSlowedDistance(frontvehicle_speed, 
                                                    rearvehicle_speed, 
                                                    frontvehicle_lonaccel, 
                                                    rearvehicle_lonaccel);
            d_warning = d_slowed;
            d_major = -1;
            d_emergency = -1;
        } else {
            d_warning = Vetalk_calcAVWWarningDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel);
            d_major = -1;
            d_emergency = -1;
        }
    }
    printf("<AVW> d_warning:%4.2f, d_major:%4.2f, d_emergency:%4.2f, d_slowed:%4.2f\n",d_warning, d_major, d_emergency, d_slowed);
    return;
}