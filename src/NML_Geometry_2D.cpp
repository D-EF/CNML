/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-12-07 18:30:33
 * @FilePath: \cnml\src\NML_Geometry_2D.cpp
 * @Description: 2d 几何; 提供基本图元数据结构和部分算法
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "NML_Geometry_2D.hpp"
#include "NML_Algebra.hpp"

namespace NML{
    
    namespace Geometry_2D{
        
        
        Rect_Data& normalize_RectData(Rect_Data& rect_data){
            if(rect_data.w<0){
                rect_data.x+=rect_data.w;
                rect_data.w=-rect_data.w;
            }
            if(rect_data.h<0){
                rect_data.y+=rect_data.h;
                rect_data.h=-rect_data.h;
            }
            return rect_data;
        }

        void normalize_DrawArcTheta(var& theta_op, var& theta_ed){
            if(theta_op>theta_ed){
                std::swap(theta_op,theta_ed);
            }
            var theta_offset=theta_ed-theta_op;
            if(theta_offset>DEG_360){
                theta_ed  = DEG_180;
                theta_op = DEG_180_I;
                return;
            }
            if(theta_op<DEG_180_I||theta_op>DEG_180){
                theta_op=atan2(sin(theta_op),cos(theta_op));
                theta_ed=theta_op+theta_offset;
            }
        }

        
        Point_2D calc_EllipseFocus(var rx, var ry,var rotate){
            if(ry>rx){
                rotate+=DEG_90;
            }
            var c_focus_length=0.5*calc_EllipseFocalLength(rx, ry);
            Point_2D item=calc_Point2D__Rotate(rotate);
            return {c_focus_length*item.x, c_focus_length*item.y};
        }

        char calc_Intersection__Theta_Theta(Points_Iterator& out, var theta0_min, var theta0_max, var theta1_min, var theta1_max){
            char i=0;
            var *temp_out=out[i];
            if(theta0_max-theta0_min>=DEG_360){
                temp_out[0]=theta0_min;
                temp_out[1]=theta0_max;
                return 1;
            }else if(theta1_max-theta1_min>=DEG_360){
                temp_out[0]=theta1_min;
                temp_out[1]=theta1_max;
                return 1;
            }
            if(calc_Intersection__Range(temp_out[0],temp_out[1],theta0_min,theta0_max,theta1_min,theta1_max)){
                ++i;
                temp_out=out[i];
            }
            if(calc_Intersection__Range(temp_out[0],temp_out[1],theta0_min+DEG_360,theta0_max+DEG_360,theta1_min,theta1_max)){
                ++i;
                temp_out=out[i];
            }
            if(i<=1 && calc_Intersection__Range(temp_out[0],temp_out[1],theta0_min-DEG_360,theta0_max-DEG_360,theta1_min,theta1_max)){
                ++i;
                temp_out=out[i];
            }
            return i;
        }

        var calc_cross__Line_Line(Point_2D& line0_p0, Point_2D& line0_p1, Point_2D& line1_p0, Point_2D& line1_p1){
            var loc_tx = line0_p1.x - line0_p0.x;
            var loc_ty = line0_p1.y - line0_p0.y;
            return  (loc_tx*(line1_p0.y-line0_p0.y) - (line1_p0.x-line0_p0.x)*loc_ty) *
                    (loc_tx*(line1_p1.y-line0_p0.y) - (line1_p1.x-line0_p0.x)*loc_ty) ;
        }
        
        Point_2D calc_Intersection__Line_Line(Point_2D& line0_p0, Point_2D& line0_p1, Point_2D& line1_p0, Point_2D& line1_p1){
            Point_2D rtn;
            var bx=line0_p1.x-line0_p0.x,
                by=line0_p1.y-line0_p0.y,
                dx=line1_p1.x-line1_p0.x,
                dy=line1_p1.y-line1_p0.y;
            var *rtn_p=(var*)&rtn;

            if(!Algebra::calc_RootsOfSquare(rtn_p,line0_p0.x,bx,line1_p0.x,dx,line0_p0.y,by,line1_p0.y,dy)){
                rtn.x=rtn.y=INFINITY;
            }
            if( rtn.x<=1 && rtn.x>=0 && rtn.y<=1 && rtn.y>=0 ){
                rtn.x=rtn.x*bx+line0_p0.x;
                rtn.y=rtn.x*by+line0_p0.y;
            }else{
                rtn.x=rtn.y=INFINITY;
            }
            return rtn;
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
            
            if(check_Equal(rr,l)) return 1;
            
            out[1][0]=x0+h*(c1y-c0y)/l,
            out[1][1]=y0-h*(c1x-c0x)/l;
            return 2;
        }

        
        char calc_Intersection__Arc_Arc(Points_Iterator& out, var c0_x, var c0_y, var r0, var theta0_op, var theta0_ed, var c1_x, var c1_y, var r1, var theta1_op, var theta1_ed,bool _use_normalize){
            char flag_il = calc_Intersection__Circle_Circle(out,c0_x,c0_y,r0,c1_x,c1_y,r1);

            if(!flag_il){
                // 无交点
                return 0;
            }
            if(!_use_normalize && flag_il==-1){
                // 圆重合
                return calc_Intersection__Theta_Theta(out,theta0_op,theta0_ed,theta1_op,theta1_ed);
            }
            
            if(theta0_op>theta0_ed){std::swap(theta0_op,theta0_ed);}
            if(theta1_op>theta1_ed){std::swap(theta1_op,theta1_ed);}

            Point_2D theta0_op_point={sin(theta0_op),cos(theta0_op)};
            Point_2D theta1_op_point={sin(theta1_op),cos(theta1_op)};

            bool flag_cycles0,flag_cycles1;
            var theta0_offset=theta0_ed-theta0_op;
            var theta1_offset=theta1_ed-theta1_op;

            if(flag_cycles0=theta0_offset>=DEG_360){ theta0_ed  = DEG_180; theta0_op = DEG_180_I; theta0_offset=DEG_360; }
            if(flag_cycles1=theta1_offset>=DEG_360){ theta1_ed  = DEG_180; theta1_op = DEG_180_I; theta1_offset=DEG_360; }
            
            if(_use_normalize){
                if(theta0_op<DEG_180_I||theta0_op>DEG_180){   theta0_op=atan2(theta0_op_point.y,theta0_op_point.x);   theta0_ed=theta0_op+theta0_offset;}
                if(theta1_op<DEG_180_I||theta1_op>DEG_180){   theta1_op=atan2(theta1_op_point.y,theta1_op_point.x);   theta1_ed=theta1_op+theta1_offset;}
                if(flag_il==-1){
                    // 圆重合
                    return calc_Intersection__Theta_Theta(out,theta0_op,theta0_ed,theta1_op,theta1_ed);
                }
            }
            
            Point_2D theta0_ed_point={sin(theta0_ed),cos(theta0_ed)};
            Point_2D theta1_ed_point={sin(theta1_ed),cos(theta1_ed)};

            bool is_theta0_offset_more_than_pi=theta0_offset>DEG_180;
            bool is_theta1_offset_more_than_pi=theta1_offset>DEG_180;

            char rtn=0;
            var* temp_out=out[0];
            Point_2D point__loc0={ temp_out[0]-c0_x, temp_out[1]-c0_y };
            Point_2D point__loc1={ temp_out[0]-c1_x, temp_out[1]-c1_y };

            if( check_Inside__Angle(theta0_ed_point,theta0_op_point,point__loc0,is_theta0_offset_more_than_pi) && 
                check_Inside__Angle(theta1_ed_point,theta1_op_point,point__loc1,is_theta1_offset_more_than_pi) 
            ){
                ++rtn;
            }

            if(flag_il==1){ // 两圆相切
                return rtn;
            }

            temp_out=out[1];
            point__loc0={ temp_out[0]-c0_x, temp_out[1]-c0_y };
            point__loc1={ temp_out[0]-c1_x, temp_out[1]-c1_y };
            
            
            if( check_Inside__Angle(theta0_ed_point,theta0_op_point,point__loc0,is_theta0_offset_more_than_pi) && 
                check_Inside__Angle(theta1_ed_point,theta1_op_point,point__loc1,is_theta1_offset_more_than_pi) 
            ){
                rtn+=2;
            }

            return rtn;
        }

    }
}
