/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-28 16:57:35
 * @FilePath: \CNML\src\Geometry_2D\NML_Geometry_2D_Primitive_2D.cpp
 * @Description: 2D 图元 相关内容
 */

#include "./NML_Geometry_2D_Primitive_2D.hpp"

namespace NML{
    namespace Geometry_2D{
        namespace Primitive_2D{
            
            // open * 图元基类 * open

                var Primitive_2D::get_Girth(){
                    if(!had__girth){
                        _girth= calc_Girth();
                        had__girth = true;
                    }
                    return _girth;
                }

                AABB_2D Primitive_2D::get_LocalAABB(){
                    if(!had__loc_aabb){
                        loc_aabb = calc_LocalAABB();
                        had__loc_aabb = true;
                    }
                    return loc_aabb;
                }

                Points_Iterator& Primitive_2D::get_Polygon(){
                    if(!had__polygon){
                        load_Polygon();
                        had__polygon = true;
                    }
                    return *polygon;
                }

            // end  * 图元基类 * end 

            // open * 矩形图元 * open

                Points_Iterator& Primitive_2D__Rect::load_Polygon(){
                    if(!polygon){
                        polygon=new Points_Iterator__1DList(2, 4);
                    }
                    AABB_2D aabb=get_LocalAABB();
                        *polygon[0][0]=aabb.p0.x;   *polygon[0][1]=aabb.p0.y;
                        *polygon[1][0]=aabb.p1.x;   *polygon[1][1]=aabb.p0.y;
                        *polygon[2][0]=aabb.p1.x;   *polygon[2][1]=aabb.p1.y;
                        *polygon[3][0]=aabb.p0.x;   *polygon[3][1]=aabb.p1.y;
                    return *polygon;
                }
                
                char Primitive_2D__Rect::check_Inside__Local__P(Point_2D& point){ 
                    if(!had__loc_aabb){
                        loc_aabb = calc_LocalAABB();
                        had__loc_aabb = true;
                    }
                    return check_Inside__AABB(loc_aabb.p0, loc_aabb.p1, point); 
                }

            // end  * 矩形图元 * end 

            // open * 弧形图元 * open

                var Primitive_2D__Arc::calc_Girth(){
                    switch(auto_close){
                        case 2:    return data->radius*DEG_360;                break;
                        case 1:    return get_ArcLength()+get_ChordLength();   break;
                        default:   return get_ArcLength();                     break;
                    }
                }

                var Primitive_2D__Arc::get_ArcLength(){ 
                    if(arc_length<0){
                        arc_length=calc_ArcLength();
                    }
                    return arc_length;
                }
                var Primitive_2D__Arc::get_ChordLength(){ 
                    if(chord_length<0){
                        chord_length=calc_ChordLength();
                    }
                    return chord_length;
                }

                var Primitive_2D__Arc::calc_ArcLength(){
                    return data->radius*abs(data->theta_op - data->theta_ed);
                }

                var Primitive_2D__Arc::calc_ChordLength(){
                    if(!had__loc_chord){
                        loc_chord = calc_LocalChord();
                        had__loc_chord = true;
                    }
                    return calc_LineLength(loc_chord.p0,loc_chord.p1);
                }

                Line_2D Primitive_2D__Arc::get_local_chord(){
                    if(!had__loc_chord){
                        loc_chord= calc_LocalChord();
                        had__loc_chord = true;
                    }
                    return loc_chord;
                }

                Line_2D Primitive_2D__Arc::calc_LocalChord(){
                    Line_2D rtn;
                    normalize_DrawArcData(*data);
                    var &r=data->radius;
                    return {
                        p0:{x: cos(data->theta_op)*r,   y: sin(data->theta_op)*r},
                        p1:{x: cos(data->theta_ed)*r,   y: sin(data->theta_ed)*r} 
                    };
                }

                AABB_2D Primitive_2D__Arc::calc_LocalAABB(){
                    var angle=abs(data->theta_ed-data->theta_op);
                    if(angle>=CYCLES){
                        return {
                            p0:{x : data->centre.x - data->radius,   y : data->centre.y - data->radius},
                            p1:{x : data->centre.x + data->radius,   y : data->centre.y + data->radius} 
                        };
                    }

                    AABB_2D rtn={0, 0, 0, 0};
                    var &r= data->radius;
                    Line_2D chord=get_local_chord();

                    bool f = angle>DEG_180,
                        f1 = chord.p0.x>=0,   f2 = chord.p0.y>=0,
                        f3 = chord.p1.x>=0,   f4 = chord.p1.y>=0,
                        f5 = f1==f3,        f6 = f2==f4;


                    if(f5&&f6){// 在同一象限
                        if(f){// 大于半圆
                            rtn.p0.x=-r;
                            rtn.p0.y=-r;
                            rtn.p1.x=r;
                            rtn.p1.y=r;
                        }else{
                            rtn.p0.x=(chord.p0.x>chord.p1.x)?(chord.p1.x):(chord.p0.x);
                            rtn.p0.y=(chord.p0.y>chord.p1.y)?(chord.p1.y):(chord.p0.y);
                            rtn.p1.x=(chord.p0.x<chord.p1.x)?(chord.p1.x):(chord.p0.x);
                            rtn.p1.y=(chord.p0.y<chord.p1.y)?(chord.p1.y):(chord.p0.y);
                        }
                    }else if(f2){// a1 || a2
                        if(f1){
                            if((!f3)&&(f4)){// a1 b2
                                rtn.p0.x=chord.p1.x;
                                rtn.p0.y=(chord.p0.y>chord.p1.y)?(chord.p1.y):(chord.p0.y);
                                rtn.p1.x=chord.p0.x;
                                rtn.p1.y=r;
                            }else if((!f3)&&(!f4)){// a1 b3
                                rtn.p0.x=-r;
                                rtn.p0.y=chord.p1.y;
                                rtn.p1.x=chord.p0.x;
                                rtn.p1.y=r;
                            }else if((f3)&&(!f4)){// a1 b4
                                rtn.p0.x=-r;
                                rtn.p0.y=-r;
                                rtn.p1.x=(chord.p0.x<chord.p1.x)?(chord.p1.x):(chord.p0.x);
                                rtn.p1.y=r;
                            }
                        }else{//a2
                            if(f3&&f4){// a2 b1
                                rtn.p0.x=-r;
                                rtn.p0.y=-r;
                                rtn.p1.x=r;
                                rtn.p1.y=(chord.p0.y<chord.p1.y)?(chord.p1.y):(chord.p0.y);
                            }else if((!f3)&&(!f4)){// a2 b3
                                rtn.p0.x=-r;
                                rtn.p0.y=chord.p1.y;
                                rtn.p1.x=(chord.p0.x<chord.p1.x)?(chord.p1.x):(chord.p0.x);
                                rtn.p1.y=chord.p0.y;
                            }else if((f3)&&(!f4)){// a2 b4
                                rtn.p0.x=-r;
                                rtn.p0.y=-r;
                                rtn.p1.x=chord.p1.x;
                                rtn.p1.y=chord.p0.y;
                            }
                        }
                    }else{  // a3 || a4
                        if(!f1){
                            if(f3&&f4){// a3 b1
                                rtn.p0.x=-r;
                                rtn.p0.y=-r;
                                rtn.p1.x=chord.p1.x;
                                rtn.p1.y=chord.p0.y;
                            }if((!f3)&&(f4)){// a3 b2
                                rtn.p0.x=(chord.p0.x>chord.p1.x)?(chord.p1.x):(chord.p0.x);
                                rtn.p0.y=-r;
                                rtn.p1.x=r;
                                rtn.p1.y=r;
                            }else if((f3)&&(!f4)){// a3 b4
                                rtn.p0.x=chord.p0.x;
                                rtn.p0.y=-r;
                                rtn.p1.x=chord.p1.x;
                                rtn.p1.y=(chord.p0.y<chord.p1.y)?(chord.p1.y):(chord.p0.y);
                            }
                        }else{//a4
                            if(f3&&f4){// a4 b1
                                rtn.p0.x=(chord.p0.x>chord.p1.x)?(chord.p1.x):(chord.p0.x);
                                rtn.p0.y=chord.p0.y;
                                rtn.p1.x=r;
                                rtn.p1.y=chord.p1.y;
                            }if((!f3)&&(f4)){// a4 b2
                                rtn.p0.x=chord.p1.x;
                                rtn.p0.y=-r;
                                rtn.p1.x=r;
                                rtn.p1.y=r;
                            }else if((!f3)&&(!f4)){// a4 b3
                                rtn.p0.x=-r;
                                rtn.p0.y=chord.p0.y;
                                rtn.p1.x=r;
                                rtn.p1.y=r;
                            }
                        }
                    } 
                    

                    // rtn.p0.y*=-1;
                    // rtn.p1.y*=-1;

                    rtn.p0.x+=data->centre.x;
                    rtn.p1.x+=data->centre.x;
                    rtn.p0.y+=data->centre.y;
                    rtn.p1.y+=data->centre.y;

                    return rtn;
                }

            // end  * 弧形图元 * end 
        }
    }
}
