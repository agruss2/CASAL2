/**
 * @file Category.h
 * @author Scott Rasmussen (scott.rasmussen@zaita.com)
 * @github https://github.com/Zaita
 * @date 18/02/2015
 * @section LICENSE
 *
 * Copyright NIWA Science �2015 - www.niwa.co.nz
 *
 * @section DESCRIPTION
 *
 * This object represents one category in the model.
 * Because stuff in this is built by the partition there is no need
 * to hide the members behind accessors.
 */
#ifndef PARTITION_CATEGORY_H_
#define PARTITION_CATEGORY_H_

// headers
#include <map>
#include <string>
#include <vector>

#include "../Selectivities/Selectivity.h"
#include "../Utilities/Types.h"

// namespaces
namespace niwa {
class AgeLength;
class LengthWeight;
class Model;

namespace partition {
using niwa::utilities::Double;
using std::map;
using std::pair;
using std::string;
using std::vector;

/**
 * Class definition
 */
class Category {
public:
  // methods
  Category(shared_ptr<Model> model) : model_(model){};
  virtual ~Category() = default;
  void UpdateMeanLengthData();
  void UpdateMeanWeightData();
  //  void                              UpdateAgeLengthData(const vector<Double>& length_bins, bool plus_grp, Selectivity* selectivity);
  void CollapseAgeLengthData();
  void CollapseAgeLengthDataToLength();

  void PopulateAgeLengthMatrix(Selectivity* selectivity);
  void CalculateNumbersAtLength(Selectivity* selectivity, const vector<Double>& length_bins, vector<vector<Double>>& age_length_matrix, vector<Double>& numbers_by_length,
                                const bool& length_plus);

  void PopulateCachedAgeLengthMatrix(Selectivity* selectivity);
  void CollapseCachedAgeLengthDataToLength();
  void CalculateCachedNumbersAtLength(Selectivity* selectivity, const vector<Double>& length_bins, vector<vector<Double>>& age_length_matrix, vector<Double>& numbers_by_length,
                                      const bool& length_plus);

  void Cache();

  // accessors
  unsigned age_spread() const { return (max_age_ - min_age_) + 1; }

  // members
  short            id_      = 0;
  string           name_    = "";
  unsigned         min_age_ = 0;
  unsigned         max_age_ = 0;
  vector<unsigned> years_;
  vector<Double>   data_;
  vector<Double>   cached_data_;
  vector<Double>   length_data_;
  vector<Double>   cached_length_data_;

  vector<vector<vector<vector<Double>>>> age_length_matrix_;         // age_length_matrix_[year][time_step][age][length]
  vector<vector<vector<vector<Double>>>> cached_age_length_matrix_;  // age_length_matrix_[year][time_step][age][length]

  vector<vector<vector<Double>>> mean_length_by_time_step_age_;  // value[year][time_step][age] = length;

  //  map<unsigned, map<unsigned, Double>> mean_length_by_time_step_age_; // map<time_step, age, length>
  map<unsigned, map<unsigned, Double>> mean_weight_by_time_step_age_;     // map<time_step, age, weight>
  map<unsigned, map<unsigned, Double>> mean_weight_by_time_step_length_;  // map<time_step, length_bin_index, weight>

  AgeLength* age_length_ = nullptr;

private:
  // members
  shared_ptr<Model> model_ = nullptr;

  // TODO: Re-enable this when we have a single unified accessor
  // DISALLOW_COPY_AND_ASSIGN(Category);
};

}  // namespace partition
} /* namespace niwa */

#endif /* PARTITION_CATEGORY_H_ */
