/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-06-04 15:37:53
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2025-07-19 09:37:22
 * @FilePath: \CNML\src\Geometry_2D\test.cpp
 * @Description: 2D 测试用, 编辑 svg 绘制代码
 */

#include <iostream>
#include "NML_Define.hpp"
#include "NML.hpp"
#include "Link_Block/NML_Link_Block.hpp"
#include "Geometry/NML_Bezier.hpp"
#include "Geometry/NML_Geometry.hpp"
#include "Geometry_2D/NML_Geometry_2D.hpp"
#include "Geometry_2D/NML_Path_2D.hpp"
#include "unit_test_basics.hpp"

namespace NML_Test{
    namespace Test_Act{
        using namespace NML;
        using namespace NML::Geometry_2D;
        using namespace NML::Geometry_2D::Path;

        Point_2D 
            p1     = {+1,+1},
            p2     = {-1,-1},
            p3     = {+1,-1},
            p4     = {-1,+1},
            p0     = {+0,+0},
            p1_d   = {+2,+2};

        
        void test_G2D(){
            Line_2D l1;
            
            var *transform_m2d__rotate_45deg=new var[Matrix_2D::m2d_l];
            Matrix_2D::setup_Matrix2D__Rotate(transform_m2d__rotate_45deg,45*DEG);

            l1=load_AABB_ByPoint(p3,p4);
            check_Test(l1.p0[0]==-1 && l1.p0[1]==-1 && l1.p1[0]==1 && l1.p1[1]==1, "setup_AABB_ByPoint");
            check_Test(check_Inside__AABB(l1.p0, l1.p1, p0), "check_Inside__AABB");
            check_Test(!check_Inside__AABB(l1.p0, l1.p1, p1_d), "check_Inside__AABB");

            transform_AABB(l1.p0,l1.p1,transform_m2d__rotate_45deg);
            check_Test((
                check_Equal(l1.p0[0],-1.4142135623730951) &&
                check_Equal(l1.p0[1],-1.4142135623730951) &&
                check_Equal(l1.p1[0], 1.4142135623730951) &&
                check_Equal(l1.p1[1], 1.4142135623730951)
            ), "transform_AABB");

            Rect_Data rect={1,1,-1,-1};
            normalize_RectData(rect);
            check_Test(rect.x==0&&rect.y==0&&rect.w==1&&rect.h==1, "normalize_RectData");

            Arc_Data arc={{1,1},-1,123,-123};
            normalize_DrawArcData(arc);
            check_Test(arc.radius==1 && check_Equal(arc.theta_ed,PI) && check_Equal(arc.theta_op,PI_I), "normalize_DrawArcData");
            arc={{1,1},-2,12,13};
            normalize_DrawArcData(arc);
            check_Test(arc.radius==2 && check_Equal(arc.theta_op, -0.5663706143591725) && check_Equal(arc.theta_ed,0.43362938564082754), "normalize_DrawArcData");

            delete transform_m2d__rotate_45deg;
        }

        // todo more test

        /**
         * @brief 测试 弧形 & 椭圆弧 相关
         */
        void test_g2d_arc(){
            // todo 计算测试数据
            Point_2D temp_point_0, temp_point_1, temp_point_2;
            setup_Vector2__Rotate(temp_point_0,45*DEG);
            Ellipse_Arc_Data ellipse_arc_data={ {100,200}, 123, 321, 30*DEG, DEG_180, 45*DEG };
            calc_EllipseFocus(temp_point_1,ellipse_arc_data);
            temp_point_2[0]=-104.8284312579368899142855663906;
            temp_point_2[1]= 104.8284312579368899142855663906;
            check_Test(check_Equal(2,(var*)temp_point_1,(var*)temp_point_2),"calc_EllipseFocus");
            check_Test(check_Equal(calc_EllipseScaleValue(ellipse_arc_data),0.38317757009345794392523364485981),"calc_EllipseScaleValue");
            check_Test(check_Equal(calc_EllipseFocalLength(ellipse_arc_data),296.49957841454007706573620234012),"calc_EllipseFocalLength");
        }
        
        void test_Path(){
            var temp[6];
            int i=0;
            setup_Values__ByString(temp,"-123.321, -456.789e+2,233,   -332  l123.456 -1e-3,5",i);

            SVG_Path_Cmds* d = new SVG_Path_Cmds();
            load_SVGPath(*d, "M10 80 h50 C 40 10, 65 10, 95 80 S -150 150, 180 80 q-25 -80, 80 0 t 80 80l 40 240a 300 180 45 0 0 -320 -40zM10 10 l20 20");
            

            std::cout<<"<path x=\"200\" y=\"100\" fill=\"#0000\" stroke=\"#f00\" stroke-width=\"4\" d=\"\n";
            print_SVGPathCmds(*d);
            std::cout<<"\n\" />\n";
            
            normalize_SvgCmd(*d);
            
            std::cout<<"<path x=\"200\" y=\"100\" fill=\"#0000\" stroke=\"#0f0\" stroke-width=\"2\" d=\"\n";
            print_SVGPathCmds(*d);
            std::cout<<"\n\" />\n";

            return;
        }

        void test_2D_Bezier(){
            // todo
            return;
        }
    }
}