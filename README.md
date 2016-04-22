# SpeechRecogProject
基于alize的说话人识别引擎
原始项目官网：http://alize.codeplex.com/
一、编译准备：
整个项目基于vs2013以及vs2010（需要使用vs2010的编译器否则会无法编译通过）开发
1.如果电脑上安装的是vs2010，则可直接编译通过，
2.如果安装的是vs2013，则必须同时安装vs2010，并且在右键项目->属性->配置属性->常规->平台工具集 修改为“Visual Studio 2010 (v100)”  

1:data为原始的wav音频数据
2:features为从音频数据中提取出来的mfcc特征文件
3:scps为一个从wav到mfcc映射的文件
4:temp为临时生成的bat文件，xml文件以及res结果文件


trainworld.exe modelAdaption.exe computetest.exe 为原始的工程的编译的工具
现已经全部集成到SRSystemV2.exe中 根据对SRSystemV2.exe传的参数的不同执行不同的
功能。相应的配置文件分别为
trainworld.xml ：基础数据模型训练的配置文件
traintarget.xml ：特定人数据模型训练的配置文件
computetest.xml：测试配置文件

SRSystem\BinExec\temp\wld_256init.xml：wld_256的初始模型
SRSystem\BinExec\temp\wld_256.xml：基础模型，基于初始模型，使用一个较大的数据集训练出一个GMM模型（默认特征取mfcc，GMM分量256个）
SRSystem\BinExec\temp\target{x}.xml：特定人自适应模型，使用一个特定人的数据集训练对应的GMM模型
SRSystem\BinExec\compare.res：测试结果文件

HCOPY.exe为提取mfcc特征的一个工具
其配置文件为config

run.bat 为运行整个工程的一个批处理(里面有详细说明)


1:ALIZE(源码)为Alize官网下载下来的3.0的原始的未经修改的源代码
2:LIA_RAL(源码)为Alize官网下载下来的原始的未经修改的源代码
3:SRSystem为说话人识别工程系统


未完成的工作：

1:trainworld目前用的是以前的trainworld.exe（源码已丢失）工具
虽然SRSystemV2中的trainworld模块也能使用，但是训练起来时间要比以前的工具长很多

2:traintarget现在采用的是一次train一个target模式 这样要每次训练之前都得重新加载world模型导致时间上花费很多  以后可以改成一次加载world同时训练多个target

3:computest模块目前尚未改成同时保存多个compare.res 也就是说对于每个要测试的特征最终保存的都是compare.res文件 以后可以改成对不同的测试的特征按照其名字来保存结果文件
