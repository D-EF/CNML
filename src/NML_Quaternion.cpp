#include "NML_Quaternion.hpp"

namespace NML{
    namespace Quaternion{
        var*& setup_Quaternion__ByMatrix(var*& out, var*& mat);
        var*& setup_Quaternion__ByEulerAngle(var*& out, var*& EulerAngle, Rotation_Order order=XYZ);
        var*& corss(var*& out, var*& quat_left, var*& quat_right);
        var*& setup_Quaternion_division(var*& out, var*& quat);
    }
}