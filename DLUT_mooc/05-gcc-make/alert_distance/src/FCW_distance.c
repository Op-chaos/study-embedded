#include "FCW_distance.h"
float Vetalk_calcFCWSlowedDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel)
{
    float   readiness_time;
    float   min_safety_distance;

    min_safety_distance = 0.0f;
    readiness_time = 0.0f;

    min_safety_distance = 2;

    /* 前车速度大于后车，安全 */
    if (frontvehicle_speed > rearvehicle_speed) {
        return -1;
    } else {

        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

    }
}

float Vetalk_calcFCWWarningDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    float   warning_readiness_time;
    float   follow_readiness_time;
    float   min_safety_distance;
    float   follow_frontvehicle_lonaccel;
    float   rearvehicle_lonaccel;
    float   d_follow;
    float   d_warning;
	float 	Ts;


	Ts = 0.4;   
    warning_readiness_time = 1.2 + Ts;     // FCW_warning_reaction_time_s
    follow_readiness_time = 0.5 + Ts;      // FCW_follow_reaction_time_s
    min_safety_distance = 2;               // FCW_minsafety_distance_m
    follow_frontvehicle_lonaccel = -6;     // FCW_mindecelerate_mps2
    rearvehicle_lonaccel = -6;             // FCW_mindecelerate_mps2

    d_follow = _Vetalk_calcSafeDistance(follow_readiness_time, frontvehicle_speed, rearvehicle_speed, follow_frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

    d_warning = _Vetalk_calcSafeDistance(warning_readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

    
    if (frontvehicle_speed <= rearvehicle_speed) {
        if (rearvehicle_speed >= 60/3.6 && (rearvehicle_speed - frontvehicle_speed) < 5/3.6) {
            /* 返回跟随距离和soft距离较大的一个 */
            return (d_follow > d_warning ? d_follow : d_warning);
        } else {
            return d_warning;
        }
    } else {    
        /* 后车速度很快，及时小于前车也有危险 */
        if (rearvehicle_speed >= 60/3.6 && rearvehicle_speed + 5/3.6 > frontvehicle_speed) {
            return d_follow;
        } else {
            return -1;
        }
    } 
    return -1;
}


float Vetalk_calcFCWMajorDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    float   readiness_time;
    float   min_safety_distance;    
    float   rearvehicle_lonaccel;
	float 	Tr;
	float 	Ts;    

	Tr = 0.5;                  // FCW_major_reaction_time_s;
	Ts = 0.4;

    readiness_time = Tr + Ts;
    min_safety_distance = 2;   // FCW_minsafety_distance_m;
    rearvehicle_lonaccel = -6; // FCW_mindecelerate_mps2;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return -1;
    } 

}

float Vetalk_calcFCWEmergencyDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    float   readiness_time;
    float   min_safety_distance;    
    float   rearvehicle_lonaccel;
	float 	Ts;    
	float 	Tr;

	Ts = 0.4;
    Tr = 0.3;                  // FCW_emergency_reaction_time_s
    readiness_time = Ts + Tr;
    min_safety_distance = 2;   // FCW_minsafety_distance_m;
    rearvehicle_lonaccel = -6; // FCW_mindecelerate_mps2;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return -1;
    } 
    
}

float Vetalk_calcFCWWarningFlexibleDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    return (float)(1.0f + 5.0 / 100.0f) * (Vetalk_calcFCWWarningDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed));
}

float Vetalk_calcFCWMajorFlexibleDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    return (float)(1.0f + 5.0 / 100.0f) * (Vetalk_calcFCWMajorDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed)); 
}

float Vetalk_calcFCWEmergencyFlexibleDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    return (float)(1.0f + 5.0 / 100.0f) * (Vetalk_calcFCWEmergencyDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed));   
}

void TA_EvaluateThreatFCW(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel)
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
        d_slowed = Vetalk_calcFCWSlowedDistance(frontvehicle_speed, 
                                                rearvehicle_speed, 
                                                frontvehicle_lonaccel, 
                                                rearvehicle_lonaccel);
    } 

    d_warning = Vetalk_calcFCWWarningDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    d_major = Vetalk_calcFCWMajorDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    d_emergency = Vetalk_calcFCWEmergencyDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);

    // d_warning_Flexible = Vetalk_calcFCWWarningFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    // d_major_Flexible = Vetalk_calcFCWMajorFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    // d_emergency_Flexible = Vetalk_calcFCWEmergencyFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);

    printf("<FCW> d_warning:%4.2f, d_major:%4.2f, d_emergency:%4.2f, d_slowed:%4.2f\n",d_warning, d_major, d_emergency, d_slowed);
    // printf("d_warning_Flexible:%4.2f, d_major_Flexible:%4.2f, d_emergency_Flexible:%4.2f\n",d_warning_Flexible, d_major_Flexible, d_emergency_Flexible);
    
    return;
}