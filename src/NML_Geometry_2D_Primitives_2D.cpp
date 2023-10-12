/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-19 18:10:45
 * @FilePath: \CNML\src\NML_Geometry_2D_Primitives.cpp
 * @Description: 2D 图元 相关内容
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "NML_Geometry_2D_Primitives_2D.hpp"

namespace NML{
    namespace Geometry_2D{
        namespace Primitives_2D{
            
            // open * 图元基类 * open

                var Primitive_2D::get_Girth(){
                    if(!had__girth){
                        _girth= calc_Girth();
                        had__girth = true;
                    }
                    return _girth;
                }

                AABB_2D Primitive_2D::get_LocalAABB(){
                    if(!had__girth){
                        loc_aabb = calc_LocalAABB();
                        had__loc_aabb = true;
                    }
                    return loc_aabb;
                }

                Points_Iterator*& Primitive_2D::get_Polygon(){
                    if(!had__girth){
                        polygon = load_Polygon();
                        had__polygon = true;
                    }
                    return polygon;
                }

            // end  * 图元基类 * end 

            // open * 矩形图元 * open

                Points_Iterator*& Primitive_2D__Rect::load_Polygon(){
                    if(!polygon){
                        polygon=new Points_Iterator__1DList(2, 4);
                    }
                    AABB_2D aabb=get_LocalAABB();
                        *polygon[0][0]=aabb.x0;   *polygon[0][1]=aabb.y0;
                        *polygon[1][0]=aabb.x1;   *polygon[1][1]=aabb.y0;
                        *polygon[2][0]=aabb.x1;   *polygon[2][1]=aabb.y1;
                        *polygon[3][0]=aabb.x0;   *polygon[3][1]=aabb.y1;
                    return polygon;
                }

            // end  * 矩形图元 * end 

            // open * 弧形图元 * open

                var Primitive_2D__Arc::calc_Girth(){
                    // todo
                    return 0;
                }

                var Primitive_2D__Arc::calc_ArcLength(){
                    // todo
                    return 0;
                }

                var Primitive_2D__Arc::calc_ChordLength(){
                    // get_Chord__Local();
                    return 0;
                }

                Line_Data_2D Primitive_2D__Arc::get_Chord__Local(){
                    if(!had__chord__local){
                        chord__local= load_Chord__Local();
                        had__chord__local = true;
                    }
                    return chord__local;
                }

                Line_Data_2D Primitive_2D__Arc::load_Chord__Local(){
                    Line_Data_2D rtn;
                    var& r=data->r;
                    return {
                        x0: cos(data->theta_0)*r,   y0: sin(data->theta_0)*r,
                        x1: cos(data->theta_1)*r,   y1: sin(data->theta_1)*r
                    };
                }

                AABB_2D Primitive_2D__Arc::calc_LocalAABB(){
                    var angle=fabs(data->theta_1-data->theta_0);
                    if(angle>=CYCLES){
                        return {
                            x0 : data->cx - data->r,   y0 : data->cy - data->r,
                            x1 : data->cx + data->r,   y1 : data->cy + data->r
                        };
                    }

                    AABB_2D rtn={0, 0, 0, 0};
                    var& r= data->r;
                    Line_Data_2D chord=get_Chord__Local();

                    bool f = angle>DEG_180,
                        f1 = chord.x0>=0,   f2 = chord.y0>=0,
                        f3 = chord.x1>=0,   f4 = chord.y1>=0,
                        f5 = f1==f3,        f6 = f2==f4;


                    if(f5&&f6){// 在同一象限
                        if(f){// 大于半圆
                            rtn.x0=-r;
                            rtn.y0=-r;
                            rtn.x1=r;
                            rtn.y1=r;
                        }else{
                            rtn.x0=(chord.x0>chord.x1)?(chord.x1):(chord.x0);
                            rtn.y0=(chord.y0>chord.y1)?(chord.y1):(chord.y0);
                            rtn.x1=(chord.x0<chord.x1)?(chord.x1):(chord.x0);
                            rtn.y1=(chord.y0<chord.y1)?(chord.y1):(chord.y0);
                        }
                    }else if(f2){// a1 || a2
                        if(f1){
                            if((!f3)&&(f4)){// a1 b2
                                rtn.x0=chord.x1;
                                rtn.y0=(chord.y0>chord.y1)?(chord.y1):(chord.y0);
                                rtn.x1=chord.x0;
                                rtn.y1=r;
                            }else if((!f3)&&(!f4)){// a1 b3
                                rtn.x0=-r;
                                rtn.y0=chord.y1;
                                rtn.x1=chord.x0;
                                rtn.y1=r;
                            }else if((f3)&&(!f4)){// a1 b4
                                rtn.x0=-r;
                                rtn.y0=-r;
                                rtn.x1=(chord.x0<chord.x1)?(chord.x1):(chord.x0);
                                rtn.y1=r;
                            }
                        }else{//a2
                            if(f3&&f4){// a2 b1
                                rtn.x0=-r;
                                rtn.y0=-r;
                                rtn.x1=r;
                                rtn.y1=(chord.y0<chord.y1)?(chord.y1):(chord.y0);
                            }else if((!f3)&&(!f4)){// a2 b3
                                rtn.x0=-r;
                                rtn.y0=chord.y1;
                                rtn.x1=(chord.x0<chord.x1)?(chord.x1):(chord.x0);
                                rtn.y1=chord.y0;
                            }else if((f3)&&(!f4)){// a2 b4
                                rtn.x0=-r;
                                rtn.y0=-r;
                                rtn.x1=chord.x1;
                                rtn.y1=chord.y0;
                            }
                        }
                    }else{  // a3 || a4
                        if(!f1){
                            if(f3&&f4){// a3 b1
                                rtn.x0=-r;
                                rtn.y0=-r;
                                rtn.x1=chord.x1;
                                rtn.y1=chord.y0;
                            }if((!f3)&&(f4)){// a3 b2
                                rtn.x0=(chord.x0>chord.x1)?(chord.x1):(chord.x0);
                                rtn.y0=-r;
                                rtn.x1=r;
                                rtn.y1=r;
                            }else if((f3)&&(!f4)){// a3 b4
                                rtn.x0=chord.x0;
                                rtn.y0=-r;
                                rtn.x1=chord.x1;
                                rtn.y1=(chord.y0<chord.y1)?(chord.y1):(chord.y0);
                            }
                        }else{//a4
                            if(f3&&f4){// a4 b1
                                rtn.x0=(chord.x0>chord.x1)?(chord.x1):(chord.x0);
                                rtn.y0=chord.y0;
                                rtn.x1=r;
                                rtn.y1=chord.y1;
                            }if((!f3)&&(f4)){// a4 b2
                                rtn.x0=chord.x1;
                                rtn.y0=-r;
                                rtn.x1=r;
                                rtn.y1=r;
                            }else if((!f3)&&(!f4)){// a4 b3
                                rtn.x0=-r;
                                rtn.y0=chord.y0;
                                rtn.x1=r;
                                rtn.y1=r;
                            }
                        }
                    } 
                    

                    // rtn.y0*=-1;
                    // rtn.y1*=-1;

                    rtn.x0+=data->cx;
                    rtn.x1+=data->cx;
                    rtn.y0+=data->cy;
                    rtn.y1+=data->cy;

                    return rtn;
                }

            // end  * 弧形图元 * end 
        }
    }
}
