/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-11-24 11:04:15
 * @FilePath: \cnml\src\NML_Geometry_2D.cpp
 * @Description: 2d 几何; 提供基本图元数据结构和部分算法
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "NML_Geometry_2D.hpp"
#include "NML_Algebra.hpp"

namespace NML{
    
    namespace Geometry_2D{
        
        Rect_Data*& normalize_RectData(Rect_Data*& rect_data){
            if(rect_data->w<0){
                rect_data->x+=rect_data->w;
                rect_data->w=-rect_data->w;
            }
            if(rect_data->h<0){
                rect_data->y+=rect_data->h;
                rect_data->h=-rect_data->h;
            }
            return rect_data;
        }


        Arc_Data*& normalize_ArcData(Arc_Data*& arc_data){
            if(arc_data->theta_0>arc_data->theta_1){
                std::swap(arc_data->theta_0, arc_data->theta_1);
            }
            return arc_data;
        }
        
        char check_Inside__AABB(AABB_2D aabb, var x, var y){
            if(aabb.x0>x||aabb.x1<x)     return 0;
            if(aabb.y0>y||aabb.y1<y)     return 0;
            if(aabb.x0==x||aabb.x1==x)   return 2;
            if(aabb.y0==y||aabb.y1==y)   return 2;
            return 1;
        }
        
        
        Line_Data_2D calc_EllipseFocus(var rx, var ry,var rotate){
            if(ry>rx){
                rotate+=DEG_90;
            }
            var c_focus_length=0.5*calc_EllipseFocalLength(rx, ry);
            Point_2D item=create_Point2D__Rotate(rotate);
            return {
                +c_focus_length*item.x,
                +c_focus_length*item.y,
                -c_focus_length*item.x,
                -c_focus_length*item.y,
            };
        }

        var calc_cross__Line_Line(var line0_p0_x, var line0_p0_y, var line0_p1_x, var line0_p1_y, var line1_p0_x, var line1_p0_y, var line1_p1_x, var line1_p1_y){
            var loc_tx = line0_p1_x - line0_p0_x;
            var loc_0x = line1_p0_x - line0_p0_x;
            var loc_1x = line1_p1_x - line0_p0_x;
            var loc_ty = line0_p1_y - line0_p0_y;
            var loc_0y = line1_p0_y - line0_p0_y;
            var loc_1y = line1_p1_y - line0_p0_y;
            return (loc_tx*loc_0y - loc_0x*loc_ty)*(loc_tx*loc_1y - loc_1x*loc_ty);
        }
        
        char check_Intersection__Line_Line__V2(var line0_p0_x, var line0_p0_y, var line0_p1_x, var line0_p1_y, var line1_p0_x, var line1_p0_y, var line1_p1_x, var line1_p1_y){
            var t0_x=line0_p1_x - line0_p0_x,
                t0_y=line0_p1_y - line0_p0_y,
                t0ox=line0_p1_x - line1_p0_x,
                t0oy=line0_p1_y - line1_p0_y,
                t0ex=line0_p1_x - line1_p1_x,
                t0ey=line0_p1_y - line1_p1_y,
                t1_x=line1_p1_x - line1_p0_x,
                t1_y=line1_p1_y - line1_p0_y,
                t1ox=line1_p1_x - line0_p0_x,
                t1oy=line1_p1_y - line0_p0_y,
                t1ex=line1_p1_x - line0_p1_x,
                t1ey=line1_p1_y - line0_p1_y;

            // fx   x是线段号码 (1 or 2)
            // fx1 是起点的 flag, fx2 是终点的 flag
            // vec_left[0]*vec_right[1] - vec_left[1]*vec_right[0]
            var f00=t0_x*t0oy - t0_y*t0ox,   // cross  t0 , t0o
                f01=t0_x*t0ey - t0_y*t0ex,   // cross  t0 , t0e
                f10=t1_x*t1oy - t1_y*t1ox,   // cross  t1 , t1o
                f11=t1_x*t1ey - t1_y*t1ex;   // cross  t1 , t1e
            if((f00==0)&&((f11>0)!=(f10>0))){
                // l1 起点在 l2 上
                return 2;
            }
            else if((f01==0)&&((f11>0)!=(f10>0))){
                // l1 终点在 l2 上
                return -1;
            }else if((f10==0)&&((f00>0)!=(f01>0))){
                // l2 起点在 l1 上
                return -1;
            }
            else if((f11==0)&&((f00>0)!=(f01>0))){
                // l2 终点在 l1 上
                return 2;
            }
            
            if((f01>0)!=(f00>0)&&(f11>0)!=(f10>0)){
                // 两线段相交
                return 1;
            }
            return 0;
        }

        var*& calc_Intersection__Line_Line(var*& out , var line0_p0_x, var line0_p0_y, var line0_p1_x, var line0_p1_y, var line1_p0_x, var line1_p0_y, var line1_p1_x, var line1_p1_y){
            var bx=line0_p1_x-line0_p0_x,
                by=line0_p1_y-line0_p0_y,
                dx=line1_p1_x-line1_p0_x,
                dy=line1_p1_y-line1_p0_y;
            var temp_root[2]={0,0};
            var *p__temp_root=temp_root;

            if(!Algebra::calc_RootsOfSquare(p__temp_root,line0_p0_x,bx,line1_p0_x,dx,line0_p0_y,by,line1_p0_y,dy)){
                out[0]=out[1]=INFINITY;
            }
            if( 
                p__temp_root[0]<=1 && p__temp_root[0]>=0 &&
                p__temp_root[1]<=1 && p__temp_root[1]>=0 
            ){
                out[0]=p__temp_root[0]*bx+line0_p0_x;
                out[1]=p__temp_root[0]*by+line0_p0_y;
            }else{
                out[0]=out[1]=INFINITY;
            }
            return out;
        }
        
        char calc_Intersection__Circle_Circle(Points_Iterator& out, var c0x, var c0y, var r0, var c1x, var c1y, var r1){
            var l=Vector::mag_v2( c1x-c0x , c1y-c0y );
            var rr=r1+r0;
            if( (l<NML_TOLERANCE) && (check_Equal(r0,r1))){
                return -1;
            }
            if( l>rr || l<abs(r1-r0) ){
                return 0;
            }
            var a = (r0*r0-r1*r1+l*l)/(2*l),
                fv= r0*r0-a*a;
            var x0=c0x+(a/l)*(c1x-c0x),
            y0=c0y+(a/l)*(c1y-c0y),
            h=sqrt(fv);
            
            out[0][0]=x0-h*(c1y-c0y)/l;
            out[0][1]=y0+h*(c1x-c0x)/l;
            out[1][0]=x0+h*(c1y-c0y)/l,
            out[1][1]=y0-h*(c1x-c0x)/l;
            
            if(check_Equal(rr,l)) return 1;
            return 2;
        }

        char calc_Intersection__Arc_Arc(Points_Iterator& out, var cx0, var cy0, var r0, var theta_0_0, var theta_0_1, var cx1, var cy1, var r1, var theta_1_0, var theta_1_1){
            char flag = calc_Intersection__Circle_Circle(out,cx0,cy0,r0,cx1,cy1,r1);
            if(!flag) return flag;
            get_VectorAngle(out[0]);

            return 0;
        }


        char d(Points_Iterator& const asd){
            var *t = asd[0];
            return 0;
        }
        char c(){
            Points_Iterator__1DList *dd=new Points_Iterator__1DList(2,2);
            d(*dd);
        }
    }
}
