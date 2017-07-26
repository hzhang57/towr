/**
 @file    contact_schedule.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Apr 5, 2017
 @brief   Brief description
 */

#ifndef XPP_OPT_INCLUDE_XPP_OPT_CONTACT_SCHEDULE_H_
#define XPP_OPT_INCLUDE_XPP_OPT_CONTACT_SCHEDULE_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <xpp/endeffectors.h>
#include <xpp/opt/bound.h>
#include <xpp/opt/constraints/composite.h>

namespace xpp {
namespace opt {


class ContactSchedule : public Component {
public:
  using FullPhase    = std::pair<EndeffectorsBool, double>; // swinglegs and time
  using FullPhaseVec = std::vector<FullPhase>;
  using Phase        = std::pair<bool, double>; // contact state and duration
  using PhaseVec     = std::vector<Phase>;

  ContactSchedule (EndeffectorID ee, double t_total, const FullPhaseVec& phases);
  virtual ~ContactSchedule ();

  bool IsInContact(double t_global) const;

  std::vector<double> GetTimePerPhase() const;

  // zmp_ make these std::vectors?
  virtual VectorXd GetValues() const override;
  virtual void SetValues(const VectorXd&) override;
  VecBound GetBounds () const override;
  int GetPhaseCount() const { return durations_.size(); };

  Jacobian GetJacobianOfPos(VectorXd pos_deriv_xyz, double t_global) const;

private:
  void SetPhaseSequence (const FullPhaseVec& phases, EndeffectorID ee);
  bool GetContact(int phase) const;

  bool first_phase_in_contact_ = true;
  double t_total_;

  mutable std::vector<double> durations_;
};



///** Makes sure all phase durations sum up to final specified motion duration.
// */
//class DurationConstraint : public Primitive {
//public:
//  using SchedulePtr = std::shared_ptr<ContactSchedule>;
//
//  DurationConstraint(const OptVarsPtr& opt_vars, double T_total, int ee);
//  ~DurationConstraint();
//
//  VectorXd GetValues() const override;
//  VecBound GetBounds() const override;
//  void FillJacobianWithRespectTo (std::string var_set, Jacobian&) const override;
//
//private:
//  SchedulePtr schedule_;
//  double T_total_;
//};




} /* namespace opt */
} /* namespace xpp */

#endif /* XPP_OPT_INCLUDE_XPP_OPT_CONTACT_SCHEDULE_H_ */
