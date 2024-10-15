/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-07-01 14:23:29
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-07-10 16:13:44
 * @FilePath: \CNML\src\Geometry_2D\NML_Path_2D.hpp
 * @Description: 2D 路径组
 */

#include "./NML_Path_2D.hpp"

namespace NML{
    namespace Geometry_2D{

        namespace Path{

            char MAP__SVG_PATH_CMD_VALUE_STEP_SIZE[128]={0};

            void init__Map__SVG_PATH_CMD_VALUE_STEP_SIZE(char *out_map) {
                if(out_map[0]==-1)return;

                // 非法字符
                for (int i = 0; i < 128; ++i) {
                    out_map[i] = -1;
                }

                // 指令
                out_map['M'] = 2;   out_map['m'] = 2;
                out_map['L'] = 2;   out_map['l'] = 2;
                out_map['H'] = 1;   out_map['h'] = 1;
                out_map['V'] = 1;   out_map['v'] = 1;
                out_map['C'] = 6;   out_map['c'] = 6;
                out_map['S'] = 4;   out_map['s'] = 4;
                out_map['Q'] = 4;   out_map['q'] = 4;
                out_map['T'] = 2;   out_map['t'] = 2;
                out_map['A'] = 7;   out_map['a'] = 7;
                out_map['Z'] = 0;   out_map['z'] = 0;

                // 数值
                out_map['.'] = -2;   out_map['.'] = -2;
                out_map['E'] = -3;   out_map['e'] = -3;
                for (int i = '0'; i <= '9'; ++i) {
                    out_map[i] = -4;
                }
                out_map['+'] = -5;   out_map['-'] = -5;
            }


            int setup_Values__ByString(var* out,const char* str, int& idx_str, int max_value_length) {
                int i=0, e;
                var d;
                bool flag=true,flag_e;
                while(str[idx_str] && !(str[idx_str]>='0' && str[idx_str]<='9')) ++idx_str;
                out[i]=0;
                while(str[idx_str] && i<max_value_length){
                    if(str[idx_str]=='.'){
                        flag=false;
                        d=0.1;
                    } else if(str[idx_str]>='0' && str[idx_str]<='9'){
                        if((flag)){
                            out[i]*=10;
                            out[i]+=str[idx_str]-'0';
                        }else{
                            out[i]+=(str[idx_str]-'0')*d;
                            d*=0.1;
                        }
                    }else{
                        if(str[idx_str]=='E' || str[idx_str]=='e'){   // 科学计数法指数部分 ( ${float}(e|E)±?${int} ) 
                            ++idx_str;
                            flag_e=true;
                            if(str[idx_str]=='-'){
                                ++idx_str;
                                flag_e=false;
                            }else if(str[idx_str]=='+'){
                                ++idx_str;
                            }
                            e=0;
                            do{
                                e*=10;
                                e+=str[idx_str]-'0';
                                ++idx_str;
                            }while(str[idx_str]>='0' && str[idx_str]<='9');
                            if(flag_e){
                                out[i]*=pow(10,e);
                            }else{
                                out[i]/=pow(10,e);
                            }
                        }
                        ++i;
                        while(!(str[idx_str]>='0' && str[idx_str]<='9')) {
                            // 遇到 svg cmd 符号, 退出
                            if((str[idx_str]>='A' && str[idx_str]<='Z')  ||  (str[idx_str]>='a' && str[idx_str]<='z')  ||  (!str[idx_str])  ||  i>max_value_length ) return i;
                            ++idx_str;
                        }
                        out[i]=str[idx_str]-'0';
                        flag=true;
                    }
                    ++idx_str;
                }
                return i;
            }

            void load_SVGPath(SVG_Path_Cmds& out, const char* path_d){
                init__Map__SVG_PATH_CMD_VALUE_STEP_SIZE(MAP__SVG_PATH_CMD_VALUE_STEP_SIZE);

                out.remove_EndItems(out.used_length);

                SVG_Path_Cmd temp_cmd;
                int i=0;

                do{
                    while(path_d[i] && (path_d[i]<'0' || path_d[i]>'9') && path_d[i]!='-' && path_d[i]!='+'){
                        if(MAP__SVG_PATH_CMD_VALUE_STEP_SIZE[path_d[i]]>=0) temp_cmd.type = path_d[i];
                        ++i;
                    }
                    setup_Values__ByString(temp_cmd.param,path_d,i,MAP__SVG_PATH_CMD_VALUE_STEP_SIZE[temp_cmd.type]);
                    out.push_Item(temp_cmd);
                }while(path_d[i]);
            }


            void toAbsolute_SvgCmd(SVG_Path_Cmd& cmd, var relative_x, var relative_y){
                Idx i,l;
                if(cmd.type=='a'){
                    cmd.param[6] += relative_x;
                    cmd.param[7] += relative_y;
                    cmd.type='A';
                }
                else if(cmd.type>'a' && cmd.type<='z'){
                    l=MAP__SVG_PATH_CMD_VALUE_STEP_SIZE[cmd.type];
                    for(i=0;  i<l;  i+=2){
                        cmd.param[i]   += relative_x;
                        cmd.param[i+1] += relative_y;
                    }
                    cmd.type=toupper(cmd.type);
                }
            }


            SVG_Path_Cmds& normalize_SvgCmd(SVG_Path_Cmds& cmds){
                Idx i,l, cmd_length=cmds.used_length;
                var x, y;
                SVG_Path_Cmd *prev_cmd=0;
                x=y=0;

                for(i=0;  i<9;  ++i){
                    SVG_Path_Cmd &cmd=cmds[i];
                    toAbsolute_SvgCmd(cmd,x,y);

                    // 处理简化直线段
                    switch(cmd.type){
                        case 'H': // 水平线
                            cmd.type='L';
                            cmd.param[1]=y;
                        break;
                        case 'V': // 垂直线
                            cmd.type='L';
                            cmd.param[1]=cmd.param[0];
                            cmd.param[0]=x;
                        break;
                    }

                    // 处理简化曲线
                    if(cmd.type=='S'||cmd.type=='T'){
                        switch(cmd.type){
                            case 'S': // 三阶贝塞尔曲线
                                std::copy_backward(cmd.param, cmd.param+2, cmd.param+2);
                                cmd.type='C';
                            break;
                            case 'T': // 二阶贝塞尔曲线
                                std::copy_backward(cmd.param, cmd.param+4, cmd.param+2);
                                cmd.type='Q';
                            break;
                        }
                        if(prev_cmd && (prev_cmd->type=='C'||prev_cmd->type=='Q')){
                            l = MAP__SVG_PATH_CMD_VALUE_STEP_SIZE[prev_cmd->type]-4;
                            cmd.param[0] = 2*prev_cmd->param[l+2] - prev_cmd->param[l];
                            cmd.param[1] = 2*prev_cmd->param[l+3] - prev_cmd->param[l+1];
                        }else{
                            cmd.param[0]=x;
                            cmd.param[1]=y;
                        }
                    }

                    l=MAP__SVG_PATH_CMD_VALUE_STEP_SIZE[cmd.type]-2;
                    x=cmd.param[l];
                    y=cmd.param[l+1];
                    prev_cmd=&cmd;
                }

                return cmds;
            }


            
            void Path_2D::init_Primitives(){
                if(primitives) return;
                primitives=new Primitives_2D(cmds->used_length);
                Primitive_2D::Primitive_2D** f=new Primitive_2D::Primitive_2D*[cmds->used_length];
                for(Idx i=0; i<cmds->used_length; ++i) f[i]=0;
                primitives->push_Items(f,cmds->used_length);
            }

            void get_CMDDroppoint(SVG_Path_Cmd& cmd, var& x, var& y){
                Idx_Algebra i=MAP__SVG_PATH_CMD_VALUE_STEP_SIZE[cmd.type]-2;
                x = cmd.param[i];
                y = cmd.param[i+1];
            }


            Primitive_2D::Primitive_2D* Path_2D::create_Primitives(Idx index){
                using namespace Primitive_2D;
                SVG_Path_Cmd& cmd=(*cmds)[index];
                
                if(cmd.type=='M')return 0;

                var x,y;

                if(index==0){
                    x = y = 0;
                }else{
                    get_CMDDroppoint((*cmds)[index-1],x,y);
                }
                

                switch (cmd.type){
                    case 'L':
                        // todo
                        // primitives[index]=new Primitive_2D__Line({{x,y},{cmd.param[0],cmd.param[1]}});
                    break;
                    case 'Q':
                        // todo
                    break;
                    case 'C':
                        // todo
                    break;
                    case 'A':
                        // todo
                    break;
                    case 'Z':
                        // todo
                    break;
                    
                    default:
                        char d[]="Error SVG_Path_Cmd.type : 0";
                        d[26]=cmd.type;
                        throw new std::logic_error(d);
                    break;
                }
                
            }

            void Path_2D::load_Primitives(bool reload, Idx index){

            }


        }
    }
}
