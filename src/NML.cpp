/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-02-28 20:18:33
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-11-26 12:00:03
 * @FilePath: \cnml\src\NML.cpp
 * @Description: Nittle Math Library 简单数学库
 * 
 * @Copyright (c) 2023 by Darth_Eternalfaith darth_ef@hotmail.com, All Rights Reserved. 
 */

#include "NML.hpp"
#include <iostream>

namespace NML{

    const var NML_TOLERANCE=1e-6;
    const var NML_TOLERANCE_D1=1-NML_TOLERANCE;
    const Idx SAMPLE_SIZE_SEED=__DEFINE_SAMPLE_SIZE_SEED__;
    const var SAMPLE_SIZE_SIZE=1.0/SAMPLE_SIZE_SEED;
    
    const var 
        PI       = 3.14159265358979323846,
        DEG      = 0.01745329251994329576,
        DEG_90   = 1.57079632679489661923,
        CYCLES   = 6.28318530717958647692,
        PI_I     = -3.14159265358979323846,
        DEG_90_I = -1.57079632679489661923,
        CYCLES_I = -6.28318530717958647692;

    const var &DEG_180_I = PI_I,
              &DEG_360_I = CYCLES_I,
              &DEG_180   = PI,
              &DEG_360   = CYCLES;

    const var ONE_OVER_THREE  = 1.0/3;
    const var FOUR_OVER_THREE = 4.0/3;

    void clone_To(var* to, const var* val, Idx length){
        for(Idx i=0;  i<length;  ++i){
            to[i]=val[i];
        }
    }

    var* create_Values__Clone(const var* val, Idx length){
        var *rtn=new var[length];
        for(Idx i=0;  i<length;  ++i){
            rtn[i]=val[i];
        }
        return rtn;
    }
    
    void printf_Vec(const var* val, Idx length){
        Idx i=0;
        printf("[%f", val[i]);
        for(i++;  i<length;  i++){
            printf(",%f", val[i]);
        }
        printf("]\n");
    }

    void printf_Points(Points_Iterator& points){
        printf("{\n");
        for(Idx i=0;  i<points.points_length;  i++){
            printf_Vec(points[i], points.dimensional);
        }
        printf("}\n");
    }

    bool check_Equal(Idx length, var*& val_left, var*& val_right, var _tolerance){
        for(Idx i=0;  i<length;  ++i){
            if(!check_Equal(val_left[i], val_right[i], _tolerance))return false;
        }
        return true;
    }

    bool check_Zero(Idx length, var*& value, var _tolerance){
        for(Idx i=0;  i<length;  ++i){
            if(!check_Zero(value[i], _tolerance))return false;
        }
        return true;
    }


    void sum(var*& out, Idx length, var*& val_left, var*& val_right){
        for(Idx i=0;  i<length;  ++i){
            out[i]=val_left[i]+val_left[i];
        }
    }

    var sum(var* start, Idx length){
        var rtn=0;
        for(int i=0;  i<length;  ++i){
            rtn+=start[i];
        }
        return rtn;
    }

    void dif(var*& out, Idx length, var*& val_left, var*& val_right){
        for(Idx i=0;  i<length;  ++i){
            out[i]=val_left[i]-val_left[i];
        }
    }

    var dot(Idx length, var*& val_left, var*& val_right){
        var rtn=0;
        for(Idx i=0;  i<length;  ++i){
            rtn+=val_left[i]*val_right[i];
        }
        return rtn;
    }

    var*& np(var*& out, Idx length, var k){
        for(Idx i=0;  i<length;  ++i){
            out[i]*=k;
        }
        return out;
    }

    void Points_Iterator__Link::free_Data(){
        Link_Block__Var *temp=((Link_Block__Var*)data), *next;
        while(temp!=data){
            delete temp->data;
            next=temp->next;
            delete temp;
            temp=next;
        }
    }

    var* Points_Iterator__Link::operator[](Idx v){
        Link_Block__Var *now_block;
        Idx now_block_head_v;
        if(v>=max_points_length) v = v % max_points_length;
        if(v>last_access_head_v){
            now_block=last_access_block;
            now_block_head_v=last_access_head_v;
        }else{
            now_block=((Link_Block__Var*)data)->next;
            now_block_head_v=0;
        }
        if((!now_block)||(!max_points_length)) return 0;

        Idx now_block_last_v=now_block_head_v+now_block->size/dimensional-1;
        while(now_block_last_v<v){
            now_block=now_block->next;
            now_block_head_v=now_block_last_v+1;
            now_block_last_v=now_block_head_v+now_block->size/dimensional-1;
        }
        last_access_block=now_block;
        last_access_head_v=now_block_head_v;
        return now_block->data + (v-now_block_head_v)*dimensional;
    }
    
    Idx Points_Iterator__Link::calc_MaxPointsLength(){
        Link_Block__Var *now_block=(Link_Block__Var*)data;
        if(!now_block) return 0;
        Idx rtn=0;
        do{
            rtn+=now_block->size/dimensional;
            now_block=now_block->next;
        }while(now_block!=data);
        max_points_length=rtn;
        return rtn;
    }

    void Points_Iterator__Link::append_Block(Idx size){
        if(size<__MIN_LINK_BLOCK_SIZE__)size=__MIN_LINK_BLOCK_SIZE__;
        if(size>__MAX_LINK_BLOCK_SIZE__)size=__MAX_LINK_BLOCK_SIZE__;
        Link_Block__Var *block=new Link_Block__Var{ new var[size], size, 0 };
        Link_Block__Var *last_block=(Link_Block__Var*)data;
        if(!last_block){
            block->next=block;
            data=block;
            max_points_length=size/dimensional;
        }else{
            block->next=last_block->next;
            last_block->next=block;
            max_points_length+=size/dimensional;
        }
    }

    
    void Points_Iterator__2DList::install_Data(Idx_Algebra dimensional, Idx points_length){
        var **d=new var*[points_length];
        for(int i=0;  i<points_length;  ++i){
            d[i]=new var[dimensional];
        }
        data=d;
    }
    void Points_Iterator__2DList::free_Data(){
        for(int i=0;  i<points_length;  ++i){
            delete ((var**)data)[i];
        }
        delete (var**)data;
        data=0;
    }

    // var* Points_Iterator::operator[](int v){return ((var**)data)[v];}


    // void Points_Iterator__1DList::install_Data(Idx_Algebra dimensional, Idx points_length){ data=new var[dimensional*points_length]; }
    // void Points_Iterator__1DList::free_Data(){delete (var*)data; data=0;}
    // var* Points_Iterator__1DList::operator[](int v){return ((var*)data)+(v*dimensional);}


    // void Points_Iterator__2DList::install_Data(Idx_Algebra dimensional, Idx points_length){ data=new var[dimensional*points_length]; }
    // void Points_Iterator__2DList::free_Data(){delete (var*)data; data=0;}
    // var* Points_Iterator__2DList::operator[](int v) {return ((var*)data)+(v*dimensional);}

    void calc_Intersection__Range(var& out_0, var& out_1, var a0, var a1, var b0, var b1){
        if(a0>a1)std::swap(a0,a1);
        if(b0>b1)std::swap(b0,b1);
        out_0=std::max(a0,b0);
        out_1=std::min(a1,b1);
        if(out_0>out_1){
            out_0=0;
            out_1=0;
        }
    }

}