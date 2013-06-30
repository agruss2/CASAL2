/**
 * @file Minimiser.h
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @version 1.0
 * @date 28/02/2013
 * @section LICENSE
 *
 * Copyright NIWA Science �2013 - www.niwa.co.nz
 *
 * @section DESCRIPTION
 *
 * A minimiser is responsible for taking the model
 * and trying to find the best fit of parameters using the
 * estimates and their bounds.
 *
 * $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
 */
#ifndef MINIMISER_H_
#define MINIMISER_H_

// Headers
#include <boost/numeric/ublas/matrix.hpp>

#include "BaseClasses/Object.h"

// Namespaces
namespace isam {

namespace ublas = boost::numeric::ublas;

/**
 * Class Definition
 */
class Minimiser : public isam::base::Object {
public:
  // Methods
  Minimiser();
  virtual                     ~Minimiser();
  virtual void                Validate();
  virtual void                Build();
  void                        Reset() {};
  virtual void                Execute() = 0;
  void                        BuildCovarianceMatrix();

  // Acessors
  bool                        active() const { return active_; }
  void                        set_active(bool new_value) { active_ = new_value; }
  ublas::matrix<double>       covariance_matrix() const { return covariance_matrix_; }
  ublas::matrix<double>       correlation_matrix() const { return correlation_matrix_; }

protected:
  // Members
  string                      type_;
  bool                        active_;
  double**                    hessian_;
  unsigned                    hessian_size_;
  bool                        build_covariance_;
  ublas::matrix<double>       covariance_matrix_;
  ublas::matrix<double>       correlation_matrix_;
};

// Typdef
typedef boost::shared_ptr<isam::Minimiser> MinimiserPtr;

} /* namespace isam */
#endif /* MINIMISER_H_ */