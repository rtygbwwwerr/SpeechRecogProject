1:data为原始的wav音频数据
2:features为从音频数据中提取出来的mfcc特征文件
3:scps为一个从wav到mfcc映射的文件
4:temp为临时生成的bat文件，xml文件以及res结果文件


trainworld.exe modelAdaption.exe computetest.exe 为原始的工程的编译的工具
现已经全部集成到SRSystemV2.exe中 根据对SRSystemV2.exe传的参数的不同执行不同的
功能。相应的配置文件分别为trainworld.xml traintarget.xml computetest.xml

HCOPY.exe为提取mfcc特征的一个工具
其配置文件为config

run.bat 为运行整个工程的一个批处理(里面有详细说明)
