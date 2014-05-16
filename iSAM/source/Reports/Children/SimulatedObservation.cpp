/**
 * @file SimulatedObservation.cpp
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @date 8/05/2014
 * @section LICENSE
 *
 * Copyright NIWA Science �2014 - www.niwa.co.nz
 *
 */

// headers
#include "SimulatedObservation.h"

#include "Observations/Manager.h"

// namespaces
namespace isam {
namespace reports {

/**
 * default constructor
 */
SimulatedObservation::SimulatedObservation() {
  run_mode_    = RunMode::kSimulation;
  model_state_ = State::kIterationComplete;
  skip_end_tag_ = true;

  parameters_.Bind<string>(PARAM_OBSERVATION, &observation_label_, "Observation label");
}

/**
 * build method
 */
void SimulatedObservation::DoBuild() {
  observation_ = observations::Manager::Instance().GetObservation(observation_label_);
}

/**
 * execute method
 */
void SimulatedObservation::Execute() {
  cache_ << CONFIG_SINGLE_COMMENT << CONFIG_ARRAY_START << label_ << CONFIG_ARRAY_END << endl;
  cache_ << CONFIG_SINGLE_COMMENT << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << type_ << "\n";
  cache_ << CONFIG_SINGLE_COMMENT << PARAM_OBSERVATION << "." << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << observation_->label() << "\n";


  cache_ << CONFIG_SECTION_SYMBOL << PARAM_OBSERVATION << " " << observation_->label() << "\n";

  ParameterList& parameter_list = observation_->parameters();
  const map<string, ParameterPtr>& parameters = parameter_list.parameters();
  for (auto iter = parameters.begin(); iter != parameters.end(); ++iter) {
    if (iter->first == PARAM_LIKELIHOOD) {
      if (iter->second->values()[0] == PARAM_PSEUDO)
        cache_ << PARAM_LIKELIHOOD << " " << parameter_list.Get(PARAM_SIMULATED_OBSERVATION)->values()[0] << "\n";
      else
        cache_ << PARAM_LIKELIHOOD << " " << iter->second->values()[0] << "\n";

      continue;
    }

    if (iter->first == PARAM_OBS || iter->first == PARAM_ERROR_VALUE || iter->first == PARAM_LABEL || iter->first == PARAM_SIMULATION_LIKELIHOOD)
      continue;

    if (iter->second->values().size() > 0) {
      cache_ << iter->first << " ";
      const vector<string>& values = iter->second->values();
      for (string value : values)
        cache_ << value << " ";
      cache_ << "\n";
    }
  }

  map<unsigned, vector<obs::Comparison> >& comparison = observation_->comparisons();
  // obs
  cache_ << PARAM_OBS << " ";
  for (auto iter = comparison.begin(); iter != comparison.end(); ++iter) {
    for (obs::Comparison comparison : iter->second) {
      cache_ << comparison.observed_ << " ";
    }
  }
  cache_ << "\n";

  // error values
  // obs
    cache_ << PARAM_ERROR_VALUE << " ";
    for (auto iter = comparison.begin(); iter != comparison.end(); ++iter) {
      for (obs::Comparison comparison : iter->second) {
        cache_ << comparison.error_value_ << " ";
      }
    }

    cache_ << "\n";
    cache_ << "#end" << endl;

  ready_for_writing_ = true;
}

} /* namespace reports */
} /* namespace isam */