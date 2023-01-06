<!--
 * @Author: chamip
 * @Date: 2023-01-06 15:04:03
 * @LastEditTime: 2023-01-06 15:30:30
 * @LastEditors: chamip
 * @FilePath: /cmake_practice/README.md
-->
# cmake_pratice
使用cmake构建c++项目的一般步骤：
1. 在cmake_study（我们的项目名称）目录下创建目录src、目录ext、文件CMakeLists.txt，src是源码目录，ext存放第三方库依赖文件和头文件，CMakeLists.txt是cmake构建配置文件
2. 在CMakeLists.txt中添加配置
3. 在cmake_study下创建build目录，build目录是为了不让编译产生的中间文件污染我们的工程，在build目录下执行cmake构建工具（cmake ../），执行成功后生成Makefile文件
4. build下make编译项目生成可执行文件cmake_study
5. ./cmake_study