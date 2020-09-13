#include "common_algorithm.h"
#include <stdio.h>
float Vetalk_calcEEBLSlowedDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel)
{
    float   readiness_time;
    float   min_safety_distance;
    
    readiness_time = 0.0f;

    min_safety_distance = 2; // EBW_min_safetydistance_m;

    return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
}

float Vetalk_calcEEBLWarningDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   min_safety_distance;
    float   rearvehicle_lonaccel;    
    float   readiness_time;
	float 	Tr;
	float 	Ts;    

	Tr = 2.9; // EBW_warning_reaction_time_s;
    
	Ts = 0.4;

    rearvehicle_lonaccel = -3;   // EBW_decelreate_value_mps2;
    readiness_time = Tr + Ts;
    min_safety_distance = 2.0;   // EBW_min_safetydistance_m;

    return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
}

float Vetalk_calcEEBLMajorDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   min_safety_distance;
    float   rearvehicle_lonaccel;    
    float   readiness_time;
    float   Tr;
    float   Ts;    

    Tr = 1.8;  //EBW_major_reaction_time_s
    Ts = 0.4;

    rearvehicle_lonaccel = -3;   // EBW_decelreate_value_mps2;
    readiness_time = Tr + Ts;
    min_safety_distance = 2;     //EBW_min_safetydistance_m;

    return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

}


float Vetalk_calcEEBLEmergencyDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   min_safety_distance;
    float   rearvehicle_lonaccel;    
    float   readiness_time;
    float   Ts;    
    float   Tr;

    Ts = 0.4;
    Tr = 0.6;                   // EBW_emergency_reaction_time_s;
    rearvehicle_lonaccel = -3;  // Min_Brake_Deceleration_mps2;
    readiness_time = Tr + Ts;
    min_safety_distance = 4;    // Min_Safety_Distance_m;

    return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
}

void TA_EvaluateThreatEBW(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel)
{
    float d_warning;
    float d_major;
    float d_emergency;
    float d_slowed = 0;

    float d_warning_Flexible = 0.0f;
    float d_major_Flexible = 0.0f;
    float d_emergency_Flexible = 0.0f;

    /* 车辆已刹车，并且减速度达到一定程度，不考虑反映时间，使用已减速公式 */
    if (rearvehicle_lonaccel < -3) {
        /* The vehicle has slowed down */
        d_slowed = Vetalk_calcEEBLSlowedDistance(frontvehicle_speed, 
                                                rearvehicle_speed, 
                                                frontvehicle_lonaccel, 
                                                rearvehicle_lonaccel);
    } 

    d_warning = Vetalk_calcEEBLWarningDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel);
    d_major = Vetalk_calcEEBLMajorDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel);
    d_emergency = Vetalk_calcEEBLEmergencyDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel);

    // d_warning_Flexible = Vetalk_calcFCWWarningFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    // d_major_Flexible = Vetalk_calcFCWMajorFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    // d_emergency_Flexible = Vetalk_calcFCWEmergencyFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);

    printf("<EBW> d_warning:%4.2f, d_major:%4.2f, d_emergency:%4.2f, d_slowed:%4.2f\n",d_warning, d_major, d_emergency, d_slowed);
    // printf("d_warning_Flexible:%4.2f, d_major_Flexible:%4.2f, d_emergency_Flexible:%4.2f\n",d_warning_Flexible, d_major_Flexible, d_emergency_Flexible);
    
    return;
}