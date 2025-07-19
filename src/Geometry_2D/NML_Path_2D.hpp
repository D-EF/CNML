/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-07-01 14:23:29
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2025-07-19 07:09:23
 * @FilePath: \CNML\src\Geometry_2D\NML_Path_2D.hpp
 * @Description: 2D 路径组
 */

#include "./NML_Geometry_2D.hpp"
#include "./NML_Bezier_2D.hpp"
#include "./NML_Geometry_2D_Primitive.hpp"
#include "Link_Block/NML_Link_Block.hpp"

#ifndef __NML_PATH_2D__
#define __NML_PATH_2D__

namespace NML{
    namespace Geometry_2D{

        namespace Path{
            
            /** 图元集合 应为按顺序首位相连的多个图元, 当图元实例指针值为 0 时表示该处图元未初始化 */
            using Primitives_2D = Link_Block::Link_Block_Ctrl<Primitive_2D::Primitive_2D*>;

            /** 映射 svg cmd 的参数长度, 需要使用 init__Map__SVG_PATH_CMD_VALUE_STEP_SIZE 进行初始化 */
            extern char MAP__SVG_PATH_CMD_VALUE_STEP_SIZE[128];

            /** 
             * @brief 初始化 svg 步长映射表(使用ascii映射)
             * @param out_map 生成映射表的输出目标, 需要 out_map[0]==0 才会进行初始化;  -1 表示非法字符
             */
            void init__Map__SVG_PATH_CMD_VALUE_STEP_SIZE(char* out_map);

            /** 用于存储 svg 中 path 的 d 参数的一个指令 */
            typedef struct SVG_Path_Cmd{
                char type;
                var param[8];
            } SVG_Path_Cmd;
            
            /** 一组绘制指令  */
            using SVG_Path_Cmds = Link_Block::Link_Block_Ctrl<SVG_Path_Cmd>;
            
            /** 
             * @brief 将 svg 的 相对坐标(小写指令) 转换为 绝对坐标(大写指令)
             * @param cmd           要修改的 svg 指令
             * @param relative_x    当前 x 坐标相对值
             * @param relative_y    当前 y 坐标相对值
             */
            void toAbsolute_SvgCmd(SVG_Path_Cmd& cmd, var relative_x, var relative_y);

            /**
             * @brief 解析svg指令
             * @param 输出对象
             * @param path_d  svg 中 path元素的 d 属性内容
             */
            void load_SVGPath(SVG_Path_Cmds& out, const char* path_d);


            /**
             * @brief 字符串转换为数值数组
             * @param out                输出地址
             * @param str                初始字符串
             * @param idx_str            读取字符串时的访问下标引用
             * @param max_value_length   输出时的最大长度
             * @return 返回转换了多少个数值
             */
            int setup_Values__ByString(var* out, const char* str, int& idx_str, int max_value_length=__NML_IDX_INFINITY__);
            
            /**
             * 标准化 svg 指令为绘制时使用的格式
             * @param cmds 一组 svg 指令集合
             * @return 修改并返回 cmds, 将所有指令修改为绝对坐标, H/V/T/S 简易指令修改为 L/Q/C 完整指令 
             */
            SVG_Path_Cmds& normalize_SvgCmd(SVG_Path_Cmds& cmds);

            /** 
             * @brief 输出svg指令
             * @param cmds 一组 svg 指令集合
             */
            void print_SVGPathCmds(SVG_Path_Cmds& cmds, std::ostream* os=&std::cout);

            /**
             * 路径组对象
             */
            class Path_2D{
                public:
                /** 当前路径的 cmd 指令 */
                SVG_Path_Cmds* cmds;

                /** 实例化的图元对象集合 */
                Primitives_2D* primitives;

                /**
                 * @brief 根据 svg 中 path 元素的 d 属性内容创建路径
                 * @param path_d svg 中 path 元素的 d 属性内容
                 */
                Path_2D(const char* path_d){
                    cmds=new SVG_Path_Cmds();
                    load_SVGPath(*cmds,path_d);
                }

                /** 
                 * @brief 接管一组 svg 指令创建路径
                 * @param cmds 一组已初始化的指令
                 */
                Path_2D(SVG_Path_Cmds* cmds){
                    cmds=cmds;
                }

                /**
                 * @brief 初始化图元集合的空间
                 */
                void init_Primitives();

                /**
                 * @brief 生成指定下标的图元对象
                 * @param index   对应下标, 如果当前下标已有图元对象会delete
                 */
                Primitive_2D::Primitive_2D* create_Primitives(Idx index);

                /** 
                 * @brief 生成图元对象
                 * @param reload   是否需要清理旧的图元对象, 默认为否
                 * @param index    指定生成某一个下标的指令对应的图元对象, 默认为 -1 表示生成全部图元
                 */
                void load_Primitives(bool reload=false, Idx index=-1);

            };

        }
    }
}

#endif