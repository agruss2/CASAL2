/**
 * @file MCMCChain.h
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @date 15/05/2013
 * @section LICENSE
 *
 * Copyright NIWA Science �2013 - www.niwa.co.nz
 *
 * @section DESCRIPTION
 *
 * This report will print the MCMC chain. It won't print it all at once but it will instead
 * stream it out over time so it can be restarted if necessary
 */
#ifndef MCMCCHAIN_H_
#define MCMCCHAIN_H_

// headers
#include "Reports/Report.h"

// namespaces
namespace isam {
namespace reports {

class MCMCChain : public isam::Report {
public:
  MCMCChain();
  virtual                     ~MCMCChain() noexcept(true);
  void                        Execute() override final;
};

} /* namespace reports */
} /* namespace isam */
#endif /* MCMCCHAIN_H_ */