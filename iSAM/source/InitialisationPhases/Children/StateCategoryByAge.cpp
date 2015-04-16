/**
 * @file StateCategoryByAge.cpp
 * @author Scott Rasmussen (scott.rasmussen@zaita.com)
 * @github https://github.com/Zaita
 * @date 16/04/2015
 * @section LICENSE
 *
 * Copyright NIWA Science �2015 - www.niwa.co.nz
 *
 */

#include "StateCategoryByAge.h"

namespace niwa {
namespace initialisationphases {

StateCategoryByAge::StateCategoryByAge() {
  process_type_ = ProcessType::kRecruitment;
  partition_structure_ = PartitionStructure::kAge;

  n_table_ = TablePtr(new parameters::Table(PARAM_N));

  parameters_.Bind<string>(PARAM_CATEGORIES, &category_labels_, "List of categories to use", "");
  parameters_.Bind<unsigned>(PARAM_MIN_AGE, &min_age_, "Minimum age to use for this process", "");
  parameters_.Bind<unsigned>(PARAM_MAX_AGE, &max_age_, "Maximum age to use for this process", "");
  parameters_.BindTable(PARAM_N, n_table_, "Table of data", "", true, false);
}

/**
 * Validate the parameters passed in from the configuration file
 */
void StateCategoryByAge::DoValidate() {
  vector<string> columns = n_table_->columns();
  if (columns[0] != PARAM_CATEGORY)
    LOG_ERROR_P(PARAM_N) << " must have " << PARAM_CATEGORY << " as the first column header";

}

/**
 * Build runtime relationships between this object and other objects.
 * Build any data objects that need to be built.
 */
void StateCategoryByAge::DoBuild() {

}

/**
 * Execute this process
 */
void StateCategoryByAge::Execute() {

}

} /* namespace initialisationphases */
} /* namespace niwa */