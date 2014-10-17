/**
 * @file TimeStepProportionsAtAge.cpp
 * @author Scott Rasmussen (scott.rasmussen@zaita.com)
 * @github https://github.com/Zaita
 * @date 17/10/2014
 * @section LICENSE
 *
 * Copyright NIWA Science �2014 - www.niwa.co.nz
 *
 */

// headers
#include "TimeStepProportionsAtAge.h"

#include "TimeSteps/Manager.h"
#include "Utilities/DoubleCompare.h"

// namespaces
namespace isam {
namespace observations {

/**
 *
 */
TimeStepProportionsAtAge::TimeStepProportionsAtAge() {
  parameters_.Bind<unsigned>(PARAM_MIN_AGE, &min_age_, "Minimum age", "");
  parameters_.Bind<unsigned>(PARAM_MAX_AGE, &max_age_, "Maximum age", "");
  parameters_.Bind<bool>(PARAM_AGE_PLUS, &age_plus_, "Use age plus group", "", true);
  parameters_.Bind<double>(PARAM_TOLERANCE, &tolerance_, "Tolerance", "", 0.001);
  parameters_.Bind<unsigned>(PARAM_YEAR, &year_, "Year to execute in", "");
  parameters_.Bind<string>(PARAM_OBS, &obs_, "Observation values", "");
  parameters_.Bind<double>(PARAM_ERROR_VALUE, &error_values_, "Error values", "");
  parameters_.Bind<double>(PARAM_DELTA, &delta_, "Delta", "", DELTA);
  parameters_.Bind<double>(PARAM_PROCESS_ERROR, &process_error_, "Process error", "", 0.0);
  parameters_.Bind<string>(PARAM_AGEING_ERROR, &ageing_error_label_, "Label of ageing error to use", "", "");
  parameters_.Bind<double>(PARAM_TIME_STEP_PROPORTION, &time_step_proportion_, "Proportion through the time step to analyse the partition from", "", 0.5);

  mean_proportion_method_ = true;
}

/**
 *
 */
void TimeStepProportionsAtAge::DoBuild() {
  ProportionsAtAge::DoBuild();

  if (time_step_proportion_ < 0.0 || time_step_proportion_ > 1.0)
    LOG_ERROR(parameters_.location(PARAM_TIME_STEP_PROPORTION) << ": time_step_proportion (" << AS_DOUBLE(time_step_proportion_) << ") must be between 0.0 and 1.0");
  proportion_of_time_ = time_step_proportion_;

  TimeStepPtr time_step = timesteps::Manager::Instance().GetTimeStep(time_step_label_);
  if (!time_step)
    LOG_ERROR(parameters_.location(PARAM_TIME_STEP) << time_step_label_ << " could not be found. Have you defined it?");

  time_step->SubscribeToBlock(shared_ptr(), year_);
}

} /* namespace observations */
} /* namespace isam */
