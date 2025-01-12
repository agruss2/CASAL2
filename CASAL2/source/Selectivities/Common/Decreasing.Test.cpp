/**
 * @file Decreasing.Test.cpp
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @version 1.0
 * @date 22/01/2013
 * @section LICENSE
 *
 * Copyright NIWA Science �2013 - www.niwa.co.nz
 *
 * $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
 */
#ifdef TESTMODE

// Headers
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>
#include <string>

#include "../../TestResources/MockClasses/Model.h"
#include "../../TestResources/MockClasses/ModelLength.h"
#include "Decreasing.h"

// Namespaces
namespace niwa {

using ::testing::Return;
using ::testing::ReturnRef;

/**
 * Test the results of our selectivity are correct
 */
TEST(Selectivities, Decreasing_Age) {
  shared_ptr<MockModel> model = shared_ptr<MockModel>(new MockModel());
  EXPECT_CALL(*model, min_age()).WillRepeatedly(Return(10));
  EXPECT_CALL(*model, max_age()).WillRepeatedly(Return(20));
  EXPECT_CALL(*model, age_spread()).WillRepeatedly(Return(11));
  EXPECT_CALL(*model, partition_type()).WillRepeatedly(Return(PartitionType::kAge));

  niwa::selectivities::Decreasing decreasing(model);

  vector<string> v;
  for (unsigned i = 12; i <= 18; ++i) v.push_back(boost::lexical_cast<string>(1.0 / (i * 1.5)));

  decreasing.parameters().Add(PARAM_LABEL, "unit_test_decreasing", __FILE__, __LINE__);
  decreasing.parameters().Add(PARAM_TYPE, "not needed in test", __FILE__, __LINE__);
  decreasing.parameters().Add(PARAM_L, "12", __FILE__, __LINE__);
  decreasing.parameters().Add(PARAM_H, "18", __FILE__, __LINE__);
  decreasing.parameters().Add(PARAM_V, v, __FILE__, __LINE__);
  decreasing.Validate();
  decreasing.Build();

  //ASSERT_THROW(decreasing.GetAgeResult(9, nullptr), std::string);  // Below model->min_age()
  EXPECT_DOUBLE_EQ(0.0, decreasing.GetAgeResult(10, nullptr));     // At model->min_age()
  EXPECT_DOUBLE_EQ(0.0, decreasing.GetAgeResult(11, nullptr));
  EXPECT_DOUBLE_EQ(0.055555555555555552, decreasing.GetAgeResult(12, nullptr));
  EXPECT_DOUBLE_EQ(0.055555555555555552, decreasing.GetAgeResult(13, nullptr));
  EXPECT_DOUBLE_EQ(0.10398860398860399, decreasing.GetAgeResult(14, nullptr));
  EXPECT_DOUBLE_EQ(0.14665581332247998, decreasing.GetAgeResult(15, nullptr));
  EXPECT_DOUBLE_EQ(0.18458222161925864, decreasing.GetAgeResult(16, nullptr));
  EXPECT_DOUBLE_EQ(0.21855796238512287, decreasing.GetAgeResult(17, nullptr));
  EXPECT_DOUBLE_EQ(0.24920274817394159, decreasing.GetAgeResult(18, nullptr));
  EXPECT_DOUBLE_EQ(0.037037037037037035, decreasing.GetAgeResult(19, nullptr));
  EXPECT_DOUBLE_EQ(0.037037037037037035, decreasing.GetAgeResult(20, nullptr));  // At model->max_age()
  //ASSERT_THROW(decreasing.GetAgeResult(21, nullptr), std::string);               // This is above model->max_age()
}

TEST(Selectivities, Decreasing_Length) {
  shared_ptr<MockModelLength> model   = shared_ptr<MockModelLength>(new MockModelLength());
  vector<double>        lengths = {10, 20, 30, 40, 50, 60, 120};
  vector<double>        length_midpoints = {15, 25, 35, 45, 55, 65, 130};

  EXPECT_CALL(*model, partition_type()).WillRepeatedly(Return(PartitionType::kLength));
  model->set_length_bins(lengths);
  model->set_length_plus(true);
  model->set_length_midpoints(length_midpoints);
  model->set_number_of_length_bins(); // if we chnage plus group need to reset thsi
  model->bind_calls();

  niwa::selectivities::Decreasing decreasing(model);

  vector<string> v               = {"0.05", "0.1", "0.2", "0.03"};
  vector<double> expected_values = {0, 0.05, 0.05, 0.145, 0.316, 0.03, 0.03};

  decreasing.parameters().Add(PARAM_LABEL, "unit_test_decreasing", __FILE__, __LINE__);
  decreasing.parameters().Add(PARAM_TYPE, "not needed in test", __FILE__, __LINE__);
  decreasing.parameters().Add(PARAM_L, "19", __FILE__, __LINE__);
  decreasing.parameters().Add(PARAM_H, "55", __FILE__, __LINE__);
  decreasing.parameters().Add(PARAM_V, v, __FILE__, __LINE__);
  ASSERT_THROW(decreasing.Validate(), std::string);
}

// TEST(Selectivities, Decreasing_Length_Throw_Exception) {
//  shared_ptr<MockModel> model = shared_ptr<MockModel>(new MockModel());
//  vector<unsigned> lengths = {10, 20, 30, 40, 50, 60, 120};
//
//  EXPECT_CALL(*model, length_bins()).WillRepeatedly(ReturnRef(lengths));
//  EXPECT_CALL(*model, partition_type()).WillRepeatedly(Return(PartitionType::kLength));
//
//  niwa::selectivities::Decreasing decreasing(model);
//
//  vector<string> v = {"0.1","0.2","0.3","0.5","0.2"};
//
//  decreasing.parameters().Add(PARAM_LABEL, "unit_test_decreasing", __FILE__, __LINE__);
//  decreasing.parameters().Add(PARAM_TYPE, "not needed in test", __FILE__, __LINE__);
//  decreasing.parameters().Add(PARAM_L, "19",  __FILE__, __LINE__);
//  decreasing.parameters().Add(PARAM_H, "55",  __FILE__, __LINE__);
//  decreasing.parameters().Add(PARAM_V, v,  __FILE__, __LINE__);
//  ASSERT_THROW(decreasing.Validate(), std::string);
//
//}

}  // namespace niwa

#endif /* ifdef TESTMODE */
