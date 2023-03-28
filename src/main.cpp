#include <iostream>
#include <array>

using namespace std;

inline void swap(int &a,int &b){
    int temp=a;
    a=b;
    b=temp;
    return;
}

class cnmd{
    public:
        float l;
        float x,y,z;
        cnmd(){
            this->l=0;
        }
        cnmd(float x,float y,float z){
            this->x=x;
            this->y=y;
            this->z=z;
            this->l=321.0f;
        }
};

namespace a{
    int cnmd=1;
    namespace b{
        int cnm=2;
    }
}

int main(int argc,char **argv){
    using namespace a;
    
    array<float,3> vec;
    std::cout << "hello world"<<endl;
    cout << get<3>(vec) <<endl;
    cout << a::b::cnm <<endl;

    return 0;
}