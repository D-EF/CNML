/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-06-04 15:37:53
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-07-04 08:50:13
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

namespace NML_Test{
    namespace Test_Act{
        using namespace NML;
        using namespace NML::Geometry_2D;

        // Link_Block::Link_Block_Ctrl<var>* load_SVGPath(std::string path_d){
        //     using namespace Link_Block;
        //     int i=0, j, k;
        //     int l=path_d.length();
        //     int l_type;
        //     var org_x=0, org_y=0;
        //     var temp_x=0, temp_y=0, ex_x, ex_y;
        //     var temp[7];
        //     char cmd;
            
        //     Link_Block_Ctrl<var>* out=new Link_Block_Ctrl<var>();

        //     // 寻找 cmd 
        //     while( !((path_d[i]>='a' && path_d[i]<='z') || (path_d[i]>='A' && path_d[i]<='Z')) ) ++i;
        //     cmd=path_d[i];
        //     while(cmd){
        //         if(path_d[i]>='a' && path_d[i]<='z'){ // 相对坐标处理
        //             if(path_d[i]=='a'){  //弧线仅处理 dx / dy
        //                 temp[k-2]+=temp_x;   temp[k-1]+=temp_y;
        //             }else{
        //                 for(j=0; j<k; j+=2 ){
        //                     temp[j]   += temp_x;
        //                     temp[j+1] += temp_y;
        //                 }
        //             }
        //         }

        //         switch (cmd){
        //             // 移动起始点坐标 
        //             case 'M': case 'm':   org_x=temp[0];   org_y=temp[1];   break;
        //             // 画直线
        //             case 'l': case 'L':   out->push_Items(temp,2);   break;
        //             case 'H': case 'h': // 水平线
        //             out->push_Item(temp[0]);
        //             out->push_Item(temp_y);
        //             temp_x=temp[k-1];   
        //             break;
        //             case 'V': case 'v': // 垂直线
        //             out->push_Item(temp_x);
        //             out->push_Item(temp[0]);
        //             temp_y=temp[k-1];   
        //             break;
        //             case 'C': case 'c': // 三次方贝塞尔曲线
        //             break;
        //             case 'S': case 's': // 三次方贝塞尔曲线 (简化)
        //             break;
        //             case 'Q': case 'q': // 二次方贝塞尔曲线
        //             break;
        //             case 'T': case 't': // 二次方贝塞尔曲线 (简化)
        //             break;
        //             case 'A': case 'a': // 椭圆曲线
        //             // todo
        //             break;
        //             case 'Z': case 'z': // 封闭路径 (直线回到 M 位置)
        //                 temp_x=org_x;   temp_y=org_y;   
        //             break;
        //         }
                
        //         // 更新落点到新坐标
        //         switch (cmd){
        //             case 'H': case 'h':   case 'V': case 'v':   case 'Z': case 'z':   break;
        //             default: temp_x=temp[k-2];   temp_y=temp[k-1];   
        //         }
        //     }
        // }

        using namespace NML::Geometry_2D::Path;
        
        void test_Path(){
            var temp[6];
            int i=0;
            setup_Values__ByString(temp,"123.321,456.789e+2l123.456,1e-3,5",i);

            SVG_Cmds* d = load_SVGPath("M10 80 C 40 10, 65 10, 95 80 S 150 150, 180 80 q 25 -80, 80 0 t 80 80 l 40 240 a 300 180 45 0 0 -320 -40zM10 10 l20 20");

            normalize_SvgCmd(*d);

            return;
        }
    }
}