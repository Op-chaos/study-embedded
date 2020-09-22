void TA_EvaluateThreatICW(float local_speed);

void TA_EvaluateThreatFCW(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel);

void TA_EvaluateThreatEBW(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel);

void TA_EvaluateThreatAVW(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel);

void TA_EvaluateThreatEVW(float frontvehicle_speed, float rearvehicle_speed);



float _Vetalk_calcSafeDistance(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel, float min_safety_distance);



