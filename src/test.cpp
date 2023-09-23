/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-20 00:58:11
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-18 17:00:08
 * @FilePath: \CNML\src\test.cpp
 * @Description: 2d图元 单元测试
 * @
 * @Copyright (c) 2023 by ${git_name} ${git_email}, All Rights Reserved. 
 */


#include <iostream>
#include <chrono>
#include "NML.hpp"
#include "NML_Transform_Action.hpp"
#include "NML_Geometry_2D.hpp"
#include "NML_Geometry_2D_Primitives_2D.hpp"


using namespace std;
using namespace NML;
using namespace chrono;

int _test_error_counter=0;
namespace print__check_Test{void check_Test(bool flag,char* msg="");}
namespace unprint__check_Test{void check_Test(bool flag,char* msg="");}


int main(){
    using namespace NML::Matrix;
    using namespace NML::Geometry_2D;
    using namespace NML::Geometry_2D::Primitives_2D;
    using namespace NML::Matrix::Transform_Action__2D;

    Transform_Matrix_Action **test_2d_transform=new Transform_Matrix_Action*[6]{
        new Init_Matrix2D(),
        new Scale_Action(1,2),
        new Translate_Action(123,321),
        new Rotate_Action(123*DEG)
    };
    Scale_Action *c=new Scale_Action();
    Rect_Data* r_data=new Rect_Data;
    r_data->x=100; r_data->w=100;
    r_data->y=100; r_data->h=100;
    Primitive_2D__Rect *r = new Primitive_2D__Rect(r_data);
    test_2d_transform[0]->transform(r->transform_matrix);
    test_2d_transform[1]->transform(r->transform_matrix);
    test_2d_transform[2]->transform(r->transform_matrix);
    test_2d_transform[3]->transform(r->transform_matrix);

    var* pg=new var[2]{123,200};

    printf("\n%d%d%d%d%d%d\n",
        r->check_Inside__Loc(pg),
        r->check_Inside__Loc(123,200),
        r->check_Inside__Loc(100,123),
        r->check_Inside__Loc(123,123),
        r->check_Inside__Loc(233,123),
        r->check_Inside__Loc(123,233),
        r->check_Inside__Loc(233,233)
    );

    AABB_2D aabb2d=r->get_LocalAABB();
    char cnm=r->check_Inside__Loc(pg);

    Matrix_2D::printf_M2dCss(r->transform_matrix);

    return 0;
}



namespace unprint__check_Test{
    void check_Test(bool flag,char* msg){
        if(!flag)_test_error_counter++;
    }
}
namespace print__check_Test{
    void check_Test(bool flag,char* msg){
        if(flag){
            printf("\033[32m done -> %s \033[0m \n",msg);
            return;
        }
        else {
            _test_error_counter++;
            printf("\033[31m error -> %s \033[0m \n",msg);
        }
    }
}