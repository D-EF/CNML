/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-02-28 20:18:33
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-03-06 11:17:11
 * @FilePath: \CNML\src\NML.cpp
 * @Description: Nittle Math Library 简单数学库
 * 
 * @Copyright (c) 2023 by Darth_Eternalfaith darth_ef@hotmail.com, All Rights Reserved. 
 */

#include "NML.hpp"
#include <iostream>

namespace NML{

    const var NML_TOLERANCE=__NML_TOLERANCE__;
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
    const var FOUR_OVER_THREE = ONE_OVER_THREE+1.0;
    

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


    void Points_Iterator::copy_Data(Points_Iterator& copy_obj){
        int i,j;
        Points_Iterator& pi =*this;
        var* temp_this;
        var* temp_obj;
        Idx _length=min(points_length,copy_obj.points_length);
        Idx_Algebra _dimensional=min(dimensional,copy_obj.dimensional);
        for(i=0;  i<_length;  ++i){
            temp_this=pi[i];
            temp_obj=copy_obj[i];
            for(j=0;  j<_dimensional;  ++j){
                temp_this[j]=temp_obj[j];
            }
        }
    }

    bool calc_Intersection__Range(var& out_min,var& out_max, var r0_min, var r0_max, var r1_min, var r1_max){
        if(r0_min<=r1_max && r1_min<=r0_max){
            out_min=max(r0_min,r1_min);
            out_max=min(r0_max,r1_max);
            return true;
        }
        return false;
    }

}