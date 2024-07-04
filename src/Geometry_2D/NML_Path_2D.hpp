/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-07-01 14:23:29
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-07-03 17:07:52
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
            
            using Primitives = Link_Block::Link_Block_Ctrl<Primitive_2D::Primitive_2D*>;

            extern char MAP__SVG_PATH_CMD_VALUE_STEP_SIZE[128];

            /** 
             * @brief 初始化 svg 步长映射表(使用ascii映射)
             * @param out_map 生成映射表的输出目标, 需要 out_map[0]==0 才会进行初始化;  -1 表示非法字符
             */
            void init__Map__SVG_PATH_CMD_VALUE_STEP_SIZE(char* out_map);

            typedef struct SVG_Cmd{
                char type;
                var param[8];
            } SVG_Cmd;
            
            using SVG_Cmds = Link_Block::Link_Block_Ctrl<SVG_Cmd>;
            
            /** 
             * @brief 将 svg 的 相对坐标(小写指令) 转换为 绝对坐标(大写指令)
             * @param cmd           要修改的 svg 指令
             * @param relative_x    当前 x 坐标相对值
             * @param relative_y    当前 y 坐标相对值
             */
            void toAbsolute_SvgCmd(SVG_Cmd& cmd, var relative_x, var relative_y);

            /**
             * @brief 解析svg指令
             * @param path_d  svg 中 path元素的 d 属性内容
             * @return 返回 svg 指令实例集合
             */
            SVG_Cmds* load_SVGPath(const char* path_d);


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
             * @return 修改并返回 cmds, 将所有命令修改为绝对坐标, H/V/T/S 简易命令修改为 L/Q/C 完整命令 
             */
            SVG_Cmds& normalize_SvgCmd(SVG_Cmds& cmds);

            class Path{
                public:
                SVG_Cmds* cmds;
                
            };

        }
    }
}

#endif