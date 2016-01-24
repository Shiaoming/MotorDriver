/*******************************Copyright (c)***********************************
  *                      北京交通大学Robocon2015机器人小组
  ******************************************************************************
  * @文件	Readme!!!.txt
  * @日期	2015-2-14
  * @说明	说明文档
  ******************************************************************************
  * 北京交通大学-通信1208-赵小铭
  *
  * 说明:	IAR版本:7.20.2.7314
  *      	库文件版本:标准库 V1.3.0
  * 文件缩进:	Tab Size:4
  * 自动缩进:	Body:4          
  * 详细说明见Documents中Readme.txt
  ******************************************************************************
  */
  
基本说明：
      1、此工程使用IAR7.20.2.7314版本创建，使用IAR7.20.2.7314或以上版本打开。
      2、此工程库文件版本为STM32F4XX标准库 V1.3.0。
      3、格式说明：
	     Tools -> Options -> Editor
		      Tab Size设置为4，Indent Size设置为4，勾选Insert Tab
	     Tools -> Options -> Editor右侧点击Configure
		      Body设置为4。
	  4、项目Options -> C/C++ Compiler -> Preprocessor
	     (1)Additional include directories:
		    $PROJ_DIR$\USER
		    $PROJ_DIR$\APP
		    $PROJ_DIR$\CMSIS
		    $PROJ_DIR$\FWLib\inc
		    $PROJ_DIR$\FWLib\src
		    $PROJ_DIR$\BSP\inc
		 (2)Defined Symbols:
		    STM32F40XX
		    USE_STDPERIPH_DRIVER
		    ARM_MATH_CM4
	   5、开启了FPU -> VFPv4

Workspace结构说明：
      1、BSP(Board Support Package)是板级支持包。下面为一些基本的驱动。
      2、App(应用层)下面主要为一些算法的上层实现。
      3、CM4中为系统初始化配置，不要随便动。
      4、Documents中为说明和一些ST官方的使用手册，整理在一起方便查找。
      5、DSP_Lib为针对ARM Cortex-M4内核的DSP库。引用arm_math.h使用DSP库中的函数
         比直接使用math.h速度更快，效率更高。由于文件较多，编译后占用空间大，
         默认不用的统统放在UnCompile中。具体使用方法参见ST官方给出的Examples。
         (1)Complie中为参与编译的文件。
         (2)UuCompile中为不参与编译的文件。
      5、FWLib中为标准固件库。为了加快编译速度，区分了Compile和UnCompile。
         (1)Complie中为参与编译的文件。
         (2)UuCompile中为不参与编译的文件。
      6、Startup中为STM32启动的汇编代码。
      7、Output为编译生成的文件。
      8、工程根路径下为通用文件。
	  
程序结构说明：
      1、BSP中每一个.c和.h文件对应一个外设。定义一个结构体变量。
      2、一个工程定义一个总的结构体变量，其中成员为各个外设和应用需要使用的变量。
      3、工程总的结构体变量中使用指针指向各个文件中的结构体。
	  
文件结构说明：
      CMSIS(Cortex 微控制器软件接口标准)
	        startup -> startup_stm32f40_41xxx.s ：启动汇编代码
	        core_cm4.h ：Cortex-M4全局声明和定义，静态函数定义
	        core_cm4_simd.h ：Cortex-M4单指令多数据流(simd)，优化性能为主
	        stm32f4xx.h ：顶层驱动头文件
	        system_stm32f4xx.c ：设备具体定义
	        system_stm32f4xx.h ：设备特定的声明
			arm_math.h :DSP库头文件定义
	       *core_cmFunc.h ：Cortex-M内核功能访问接口
	       *core_cmInstr.h ：Cortex-M内核访问指令
      Config
	        stm32f40x_ram.icf:RAM中调试的链接文件
	        stm32f40x_flash.icf:FLASH中调试的链接文件
      FWLib(标准外设库)
	        DSP_Lib(DSP库函数)DSP_Lib为针对ARM Cortex-M4内核的DSP库。
	        引用arm_math.h使用DSP库中的函数比直接使用math.h速度更快，效率更高。
	        具体使用方法参见ST官方给出的Examples。
      App(系统应用函数)
      BSP(板级支持包)
      USER(用户主文件)
	        stm32f4xx_conf.h ：配置文件,需要使用某一个外设时,到此文件中取消其注释
	        stm32f4xx_it.c ：中断函数模板
	        stm32f4xx_it.h ：中断函数模板
	        includes.h ：头文件引用
	        main.c ：主函数所在
	        Sysinit.c ：系统初始化函数定义
	        Sysinit.h ：系统初始化函数声明
      Documents(文档说明)