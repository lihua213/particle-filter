#include <cmath>
#include "../include/measurement_model.h"

/**
 * @brief Constructor
**/
str::MeasurementModel::MeasurementModel()
{

}

/**
 * @brief Destructor
**/
str::MeasurementModel::~MeasurementModel()
{
	
}

/**
 * @brief TBD, should be main interface
**/
double str::MeasurementModel::getProbability()
{
	//Step1. calculate predict measurement
	//Step2. calculate probability
	return 0;
}


/**
 * @brief getProbFromBeamModel
**/
double str::MeasurementModel::getProbFromBeamModel(const double& measurement, const double& predict_measurement)
{
	double w_p_hit = params_.w_hit * this->prob_hit(measurement, predict_measurement);
	double w_p_short = params_.w_short * this->prob_short(measurement, predict_measurement);
	double w_p_max = params_.w_max * this->prob_max(measurement);
	double w_p_rand = params_.w_rand * this->prob_rand(measurement);
	return w_p_hit + w_p_short + w_p_max + w_p_rand;
}

/**
 * @brief tuneParameters
**/
void str::MeasurementModel::setParameters(tuningParameters& input_param)
{
	params_ = input_param;
}

/**
 * @brief tuneParameters
**/
double str::MeasurementModel::prob_hit(const double& measurement, const double& predict_measurement)
{
	double variance = params_.sigma_hit * params_.sigma_hit;
	double eta = 1/sqrt(2 * M_PI * variance);
	double diff = measurement - predict_measurement;
	double p_hit = eta*exp(-0.5 * diff * diff / variance);
	return (measurement >= 0 && measurement <= z_max_) ? p_hit : 0.0;
}

/**
 * @brief tuneParameters
**/
double str::MeasurementModel::prob_short(const double& measurement, const double& predict_measurement)
{
	double eta  = 1/(1 - exp(-params_.lambda_short * predict_measurement));
	double p_short = eta*params_.lambda_short * exp(-params_.lambda_short * measurement);
	return (measurement >= 0 && measurement <= predict_measurement) ? p_short : 0.0;
}

/**
 * @brief tuneParameters
**/
double str::MeasurementModel::prob_max(const double& measurement)
{
	return (measurement == z_max_) ? 1.0 : 0.0;
}

/**
 * @brief tuneParameters
**/
double str::MeasurementModel::prob_rand(const double& measurement)
{
	return (measurement >= 0 && measurement < z_max_) ? 1/z_max_ : 0.0;
}