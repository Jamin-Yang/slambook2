#include "ceres/ceres.h"
#include "glog/logging.h"
// A templated cost functor that implements the residual r = 10 -
// x. The method operator() is templated so that we can then use an
// automatic differentiation wrapper around it to generate its
// derivatives.
struct CostFunctor {
  CostFunctor(doubel x) : _x(x){}
  template <typename T>
  bool operator()(const T* const x, T* residual) const {
    residual[0] = 10.0 - T(_x);
    return true;
  }
};
int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  // The variable to solve for with its initial value. It will be
  // mutated in place by the solver.
  double x = 3.5;
  const double initial_x = x;
  // Build the problem.
  ceres::Problem problem;
  // Set up the only cost function (also known as residual). This uses
  // auto-differentiation to obtain the derivative (jacobian).
  CostFunctor* cost_functor = new CostFunctor(initial_x);
  ceres::CostFunction* cost_function =
      new ceres::AutoDiffCostFunction<CostFunctor, 1, 1>(cost_functor);
  problem.AddResidualBlock(cost_function, nullptr, &x);
  // Run the solver!
  ceres::Solver::Options options;
  options.minimizer_progress_to_stdout = true;
  ceres::Solver::Summary summary;
  ceres::Solve(options, &problem, &summary);
  std::cout << summary.BriefReport() << "\n";
  std::cout << "x : " << initial_x << " -> " << x << "\n";
  return 0;
}