# 数据结构课程设计

所需环境:

- Qt Creator
- Graphviz

SplayTree 项目文件架构：

- data_structure_project
    - proof  
        - proof.pdf (时间复杂度证明)
	- slide  
		- demo.pptx (操作实例展示)  
		- SplayTree.pptx (验收汇报主讲PPT)
	- splay_qt_source (splayTreeDemo)
		- visual (可视化结果储存)
			- binarytree.gvpr (Graphviz绘制二叉树配置文件)
		- ErrorMessage.hpp (通用异常类)
		- folder.hpp (文件夹处理)
		- main.cpp (主程序)
		- qtsplaytree.h/.cpp (SplayTreeWindow所含的SplayTree封装)
		- splaytreewindow.h/.cpp (SplayTreeDemo窗口实现)
		- splaytreewindow.ui/ui_splaytreewindow.h (UI设计)
