
static float _Vetalk_calcSafeDistance_Oncoming(float readiness_time, float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed, float rearvehicle_lonaccel, float min_safety_distance);

static float _Vetalk_calcSafeDistance_Inreadinesstime(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float min_safety_distance);

static float _Vetalk_calcSafeDistance_RearVehicleStopedFirst(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel, float min_safety_distance);

static float _Vetalk_calcSafeDistance_FrontVehicleStopedFirst(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel, float min_safety_distance);

float _Vetalk_calcSafeDistance(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel, float min_safety_distance);

