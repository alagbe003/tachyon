#ifndef TACHYON_MATH_ELLIPTIC_CURVES_PROJECTIVE_POINT_H_
#define TACHYON_MATH_ELLIPTIC_CURVES_PROJECTIVE_POINT_H_

#include "tachyon/math/elliptic_curves/point_conversions_forward.h"

namespace tachyon::math {

template <typename Curve, typename SFINAE = void>
class ProjectivePoint;

template <typename ScalarField, typename Curve,
          std::enable_if_t<std::is_same_v<
              ScalarField, typename Curve::ScalarField>>* = nullptr>
ProjectivePoint<Curve> operator*(const ScalarField& v,
                                 const ProjectivePoint<Curve>& point) {
  return point * v;
}

template <typename Curve>
struct PointConversions<ProjectivePoint<Curve>, ProjectivePoint<Curve>> {
  constexpr static const ProjectivePoint<Curve>& Convert(
      const ProjectivePoint<Curve>& src_point) {
    return src_point;
  }
};

template <typename SrcCurve, typename DstCurve>
struct PointConversions<ProjectivePoint<SrcCurve>, ProjectivePoint<DstCurve>,
                        std::enable_if_t<!std::is_same_v<SrcCurve, DstCurve>>> {
  static ProjectivePoint<DstCurve> Convert(
      const ProjectivePoint<SrcCurve>& src_point) {
    static_assert(SrcCurve::kIsSWCurve && DstCurve::kIsSWCurve);
    return ProjectivePoint<DstCurve>::FromMontgomery(src_point.ToMontgomery());
  }
};

}  // namespace tachyon::math

#endif  // TACHYON_MATH_ELLIPTIC_CURVES_PROJECTIVE_POINT_H_
