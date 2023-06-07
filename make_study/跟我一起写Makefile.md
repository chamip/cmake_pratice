#### 跟我一起写Makefile(陈皓)
#### 概述
一个工程的源文件不计其数，按功能、类型、模块分别放在若干目录下，makefile制定了整个工程的编译规则，哪些文件需要先编译，哪些后编译，哪些需要重新编译，甚至更复杂的功能操作。跟Shell一样可以执行操作系统命令。
makefile的优势就是**自动化编译**，只需一个make命令，整个工程自动编译，极大提高效率。
make是一个解释Makefile中指令的命令工具。
*编译和链接*
编译的过程，首先把源文件(.c/.cpp)**编译**成中间目标文件(.o)，然后把大量的.o文件合成执行文件（**链接**）。编译时，编译器检查程序语法，函数与变量是否声明，如果函数未被声明，编译器会给出警告，但可以生成中间目标文件。链接时，主要是链接函数和全局变量，链接器会在所有的.o文件中找寻函数的实现，找不到就报错误码。链接器并不管函数所在的源文件，只管函数的中间目标文件。大多数时候，源文件太多，生成的中间目标文件太多，链接时需要明显的指出中间目标文件，这对编译很不方便，所以，要给中间目标文件打个包，Unix下就是.a文件。

1. 介绍
make命令执行时，需要一个makefile文件告诉它怎样去编译和链接程序。
规则是：
1）如果这个工程没有编译过，那么所有的源文件都要编译并被链接。
2）如果这个工程的某几个文件被修改了，那么我们只编译被修改的源文件，并链接目标程序。
3）如果这个工程的头文件被修改了，那我们需要编译引用了这几个头文件的源文件，并链接目标程序。
只要写好makefile，一个make命令可以自动智能的根据当前的文件修改情况来确定哪些文件需要重新编译，从而自己编译所需要的文件和链接目标程序。

2. 规则
target ... : prerequisites ...
	command
	...
	...
target是一个目标文件，可以是中间目标文件，也可以是执行文件，还可以是标签(label)。
prequisites是要生成target所需的文件或目标。
command是make需要执行的命令(任意的shell命令)。
上述结构说明了文件的依赖关系，target依赖prerequisites中的文件，生成规则定义在command中。如果prerequisites中的文件比target要新的话就执行command中的命令。这是makefile的规则，也是最核心的内容。

3. 示例
4. make是如何工作的
默认方式下，只输入make命令：
1）make会在当前目录下找名字叫"Makefile"或"makefile"文件。
2）如果找到，它会找文件中的第一个目标文件(target)，并把这个文件作为最终的目标文件。
3）如果target文件不存在，或是它所依赖的.o文件的文件修改时间比target文件新，那么就会执行后面定义的命令生成target。
4）类似的对于.o文件，make会在当前文件中找目标为.o文件的依赖性，找到就根据其后的command生成.o文件（类似堆栈的过程）。
5）.c和.h文件肯定是存在的，于是make会生成.o文件，再用.o文件生成执行文件。
这便是make的依赖性，make会一层层去找文件的依赖关系，直到最终编译出第一个目标文件。在找寻过程中如果出错，比如最后被依赖的文件找不到，make会直接退出并报错，而对于所定义的命令的错误或是编译不成功，make根本不理会。make只管文件的依赖性，即如果在找到了依赖关系后，冒号后的文件还是不存在，就停止工作。像clean没有被第一个目标文件直接或间接关联，那么它后面所定义的命令将不会被自动执行。需要显示的调用make clean执行清除所有目标文件。

5. makefile中使用变量
如果makefile中有些内容重复多次，比如.o文件在target后面重复两次，clean中重复一次，后期修改需要修改多个地方，为了方便可以使用变量赋值代替重复出现的内容，比如OBJ = ...，然后使用时就是$(OBJ)。

6. 让make自动推导
make可以自动推导文件以及文件依赖关系后面的命令，所以没必要每个.o文件后都写上类似的命令。因为make会自动识别，并自己推导命令。
只要看到一个.o文件，他会自动把.c文件加在依赖关系中，并且command中的cc -c .c会被推导出来。
.PHNOY : clean中的.PHONY表示clean是一个伪目标文件。

7. 另类风格的makefile
8. 清空目标文件的规则


#### Makefile总述
1. Makefile里有什么？
主要包含5个东西：显式规则、隐晦规则、变量定义、文件指示和注释
1）显式规则：如何生成一个或多个的目标文件，这是Makefile书写者明显指出的，要生成的文件，文件的依赖文件，生成的命令。
2）隐晦规则：make具有自动推导的功能，所以隐晦的规则可以让我们比较粗糙简略的写Makefile。
3）变量定义：定义的一系列变量（一般是字符串，类似宏），当Makefile被执行，其中的变量会扩展。
4）文件指示：包含三部分，一是在一个Makefile中引用另一个Makefile，就像include；另一个时根据某些情况指定Makefile中的有效部分，类似#if；还有是定义一个多行的命令。
5）注释：使用#。
Makefile中的命令，必须以[Tab]键开始。

2. Makefile的文件名
最好使用Makefile作为文件名，或者使用自定义名称，make时使用make -f(--file) filename。

3. 引用其他的Makefile
使用include关键字把别的Makefile包含进来。被包含的文件会原模原样的放在当前文件的包含位置。
语法：include <filename>
filename可以是当前操作系统Shell的文件模式(可以包含路径通配符)。
include前可以包含空格，但绝不能以[Tab]开始。
如果没有指定绝对路径或相对路径时，make会首先在当前目录查找，如果当前目录没有找到，make还会在以下目录查找：
1）如果make执行时，有"-I"或"--include-dir"参数，make就会在这个参数指定的目录下查找。
2）如果目录<prefix>/include(一般时/usr/local/bin或/usr/include)存在，make也会去找。

4. 环境变量MAKEFILES
环境中设置的变量MAKEFILES类似于include，不同的是，环境变量中定义出现错误，make会不理。
不建议使用，一旦定义，所有的Makefile都会收到这个变量影响。

5. make的工作方式
工作步骤：
第一阶段：
1）读入所有的Makefile
2）读入被include的其他Makefile
3）初始化文件中的变量
4）推导隐晦规则，并分析所有规则
5）为所有的目标文件创建依赖关系链
第二阶段：
6）根据依赖关系，决定哪些目标要重新生成
7）执行生成命令

#### 书写规则
规则包含两部分：依赖关系，生成目标的方法。
Makefile中规则的顺序很重要，因为Makefile中只应该有一个最终目标，其他目标都是被这个目标连带出来的，一般来说，定义在第一条规则中的将被确立为最终的目标，如果第一条规则中的目标有很多，第一个目标会成为最终目标。
1）在规则中使用通配符
make支持3个通配符："*"、"?"、"[...]"
2）文件搜寻
源文件存放在不同的目录下，make需要去查找文件的依赖关系时，可以在文件前加上路径，单最好的办法是把一个路径告诉make让它自动查找。
Makefile中特殊变量**VPATH**完成该工作，如果没有指明这个变量，make只会在当前目录下查找依赖文件和目标文件。如果定义了这个变量，那么make就在当前目录没找到的情况下到指定目录下去查找文件。
格式：VPATH src:/..header，按顺序查找文件（当前目录永远首先查找），目录用":"分隔。
另一个设置文件搜索路径的方法是使用关键字vpath。
3）伪目标
例如经常使用的例子：
clean:
	rm *.o temp
其中clean就是一个目标。既然我们生成了许多文件，应该提供一个清除它们的"目标"。
但是我们并不生成"clean"这个文件，**"伪目标"并不是一个文件，而是一个标签**。由于"伪目标"不是文件，make无法生成他的依赖关系和决定它是否执行。只有显式
的指明这个"目标"才能使其生效。为了避免和文件名重名，可以使用特殊标记".PHONY"显式指明一个目标是"伪目标"。
伪目标一般没有依赖的文件，但是我们可以为伪目标指定所依赖的文件。伪目标可以作为"默认目标"，只要将其放在第一个。例如，Makefile需要一口气生成多个可执行文件，但是只想写一个make命令，可以使用伪目标：
"""
all : prog1 prog2 prog3
    .PHONY : all
    prog1 : prog1.o utils.o
            cc -o prog1 prog1.o utils.o
    prog2 : prog2.o
            cc -o prog2 prog2.o
    prog3 : prog3.o sort.o utils.o
            cc -o prog3 prog3.o sort.o utils.o
"""
Makefile会将第一个目标作为默认目标。伪目标的特性是总是被执行的。同样的，伪目标也可以成为依赖：
"""
.PHONY: cleanall cleanobj cleandiff
cleanall : cleanobj cleandiff
            rm program
    cleanobj :
            rm *.o
    cleandiff :
            rm *.diff
"""
4）多目标
5）静态模式
 <targets ...>: <target-pattern>: <prereq-patterns ...>
            <commands>
			...

target-pattern：目标集模式
prereq-patterns：依赖模式，对target-pattern形成的模式再进行一次依赖目标的定义。
6）自动生成依赖性

#### 书写命令
make命令默认是被/bin/sh解释执行的。
1. 显示命令
命令前有"@"，命令将不被显示。
make带有参数"-n"或"--just-print"，显示命令但不执行；有利于我们调试Makefile，看看书写的命令执行起来是什么顺序。
make带有参数"-s"或"--slient"，则是全面禁止命令的显示。
2. 命令执行
如果想要第二条命令在第一条命令的基础上运行，使用分号分隔命令。
3. 命令出错
有时候命令出错并不是出现错误。在Makefile命令行前加上"-"标记为命令不管出不出错都认为是成功的。
还有一个全局办法是make加上"i"或是"--ignore-errors"参数，Makefile中所有的命令都会忽略错误。
4. 嵌套执行make
5. 定义命令包

#### 使用变量
Makefile中的定义的变量就像c++中的宏，代表一个文本字串，Makefile执行时自动原模原样展开在所使用的地方。不同的是，可以在Makefile中改变其值，变量可以使用在"目标"、"依赖目标"、"命令"或是Makefile的其他部分。
变量的命名字可以包含字符、数字，下划线(可以是数字开头)，但不应该含有“:”、“#”、“=”或是空字符 (空格、回车等)。变量是大小写敏感的，“foo”、“Foo”和“FOO”是三个不同的变量名。传统的 Makefile 的变量名是全大写的命名方式，但我推荐使用大小写搭配的变量名，如:MakeFlags。这样可以避免和系 统的变量冲突，而发生意外的事情。
1. 变量的基础
变量在声明时需要给予初值，而在使用时，需要给在变量名前加上"$"符号，但最好用小括号"()"或是大括号"{}"把变量给包括起来。如果你要使用真实的"$"字符，那么你需要用"$$"来表示。
2. 变量中的变量
先看第一种方式，也就是简单的使用“=”号，在“=”左侧是变量，右侧是变量的值，右侧变量的值可以定义在 文件的任何一处，也就是说，右侧中的变量不一定非要是已定义好的值，其也可以使用后面定义的值。
为了避免上面的这种方法，我们可以使用 make 中的另一种用变量来定义变量的方法。这种方法使用的是 “:=”操作符，前面的变量不能使用后面的变量，只能使用前面已定义好了的变量
3. 变量的高级用法
第一种是变量值的替换。我们可以替换变量中的共有的部分，其格式是“$(var:a=b)”或是“${var:a=b}”，其意思是，把变量“var” 中所有以“a”字串“结尾”的“a”替换成“b”字串。这里的“结尾”意思是“空格”或是“结束符”。
第二种高级用法是——“把变量的值再当成变量”。
4. 追加变量值
我们可以使用“+=”操作符给变量追加值。如果变量之前没有定义过，那么，“+=”会自动变成“=”，如果前面有变量定义，那么“+=”会继承于前次操作 的赋值符。如果前一次的是“:=”，那么“+=”会以“:=”作为其赋值符。
5. override指示符
如果变量是在make命令行参数中设置的，Makefile中对这个变量的赋值会被忽略。如果想在Makefile中设置，可以使用override。
override <variable> = <value>
override <variable> := <value>
追加：override <variable> += <more text>
6. 多行变量
7. 环境变量
8. 目标变量
9. 模式变量
模式变量的好处就是，我们可以给定一种“模式”，可以把变量定义 在符合这种模式的所有目标上。
我们知道，make 的“模式”一般是至少含有一个“%”的，所以，我们可以以如下方式给所有以[.o]结尾的目标定义目标变量:
	%.o : CFLAGS = -O

#### 使用条件判断
让 make 根据运行时的不同情况选择不同的执行分支。
1. 示例
2. 语法
<conditional-directive>
    <text-if-true>
    endif
以及:
    <conditional-directive>
    <text-if-true>
    else
    <text-if-false>
endif
其中<conditional-directive>表示条件关键字：ifeq、ifneq、ifdef、ifndef。

ifdef 只是测试一个变量是否有值，其并不会把变量扩展到当前位 置。还是来看两个例子:
示例一:
    bar =
    foo = $(bar)
    ifdef foo
frobozz = yes
    else
    frobozz = no
    endif
示例二:
    foo =
    ifdef foo
    frobozz = yes
    else
    frobozz = no
    endif
第一个例子中，“$(frobozz)”值是“yes”，第二个则是“no”。

make是在读取 Makefile 时就计算条件表达式的值，并根据条件表达式的值来选择语句， 所以，你最好不要把自动化变量(如“$@”等)放入条件表达式中，因为自动化变量是在运行时才有的。

#### 使用函数
在Makefile中可以使用函数来处理变量，从而让我们的命令或规则更为灵活和智能。函数调用后，函数的返回值可以当作变量使用。
1. 函数的调用语法
$(<function> <arguments>)
或是
${<function> <arguments>}
<function>就是函数名，make 支持的函数不多。<arguments>是函数的参数，参数间以逗号“,” 分隔，而函数名和参数之间以“空格”分隔。函数调用以“$”开头，以圆括号或花括号把函数名和参数括起。

2. 字符串处理函数
$(subst <from>,<to>,<text>)
名称:字符串替换函数——subst。 功能:把字串<text>中的<from>字符串替换成<to>。 返回:函数返回被替换过后的字符串。
示例:
$(subst ee,EE,feet on the street)，
把“feet on the street”中的“ee”替换成“EE”，返回结果是“fEEt on the strEEt”。

$(patsubst <pattern>,<replacement>,<text>)
名称:模式字符串替换函数——patsubst。
功能:查找<text>中的单词(单词以“空格”、“Tab”或“回车”“换行”分隔)是否符合模式<pattern>， 如果匹配的话，则以<replacement>替换。这里，<pattern>可以包括通配符“%”，表示任意长度的字串。 如果<replacement>中也包含“%”，那么，<replacement>中的这个“%”将是<pattern>中的那个“%”所 代表的字串。(可以用“\”来转义，以“\%”来表示真实含义的“%”字符)
返回:函数返回被替换过后的字符串。
示例:
$(patsubst %.c,%.o,x.c.c bar.c)
把字串“x.c.c bar.c”符合模式[%.c]的单词替换成[%.o]，返回结果是“x.c.o bar.o”
备注: 这和我们前面“变量章节”说过的相关知识有点相似。如:
        “$(var:<pattern>=<replacement>)”
相当于
“$(patsubst <pattern>,<replacement>,$(var))”，
而“$(var: <suffix>=<replacement>)”
则相当于
“$(patsubst %<suffix>,%<replacement>,$(var))”。
例如有:objects = foo.o bar.o baz.o， 那么，“$(objects:.o=.c)”和“$(patsubst %.o,%.c,$(objects))”是一样的。

$(strip <string>)
名称:去空格函数——strip。 功能:去掉<string>字串中开头和结尾的空字符。 返回:返回被去掉空格的字符串值。
示例:
$(strip a b c )
把字串“a b c ”去到开头和结尾的空格，结果是“a b c”。

$(findstring <find>,<in>)
名称:查找字符串函数——findstring。 功能:在字串<in>中查找<find>字串。 返回:如果找到，那么返回<find>，否则返回空字符串。 示例:
        $(findstring a,a b c)
        $(findstring a,b c)
第一个函数返回“a”字符串，第二个返回“”字符串(空字符串) 

$(filter <pattern...>,<text>)
名称:过滤函数——filter。
功能:以<pattern>模式过滤<text>字符串中的单词，保留符合模式<pattern>的单词。可以有 多个模式。
返回:返回符合模式<pattern>的字串。 示例:
        sources := foo.c bar.c baz.s ugh.h
        foo: $(sources)
cc $(filter %.c %.s,$(sources)) -o foo
$(filter %.c %.s,$(sources))返回的值是“foo.c bar.c baz.s”。

$(filter-out <pattern...>,<text>)
名称:反过滤函数——filter-out。
功能:以<pattern>模式过滤<text>字符串中的单词，去除符合模式<pattern>的单词。可以有 多个模式。
返回:返回不符合模式<pattern>的字串。 示例:
        objects=main1.o foo.o main2.o bar.o
        mains=main1.o main2.o
$(filter-out $(mains),$(objects)) 返回值是“foo.o bar.o”。 

$(sort <list>)
名称:排序函数——sort。 功能:给字符串<list>中的单词排序(升序)。 返回:返回排序后的字符串。
示例:$(sort foo bar lose)返回“bar foo lose” 。 备注:sort 函数会去掉<list>中相同的单词。

$(word <n>,<text>)
名称:取单词函数——word。
功能:取字符串<text>中第<n>个单词。(从一开始) 返回:返回字符串<text>中第<n>个单词。如果<n>比<text>中的单词数要大，那么返回空字符串。 示例:$(word 2, foo bar baz)返回值是“bar”。

$(wordlist <s>,<e>,<text>)
名称:取单词串函数——wordlist。 功能:从字符串<text>中取从<s>开始到<e>的单词串。<s>和<e>是一个数字。 返回:返回字符串<text>中从<s>到<e>的单词字串。如果<s>比<text>中的单词数要大，那么返回空字符串。如果<e>大于<text>的单词数，那么返回从<s>开始，到<text>结束的单词串。 示例: $(wordlist 2, 3, foo bar baz)返回值是“bar baz”。

$(words <text>)
名称:单词个数统计函数——words。
功能:统计<text>中字符串中的单词个数。
返回:返回<text>中的单词数。
示例:$(words, foo bar baz)返回值是“3”。 备注:如果我们要取<text>中最后的一个单词，我们可以这样:$(word $(words
<text>),<text>)。 

$(firstword <text>)
名称:首单词函数——firstword。 功能:取字符串<text>中的第一个单词。 返回:返回字符串<text>的第一个单词。
示例:$(firstword foo bar)返回值是“foo”。 备注:这个函数可以用 word 函数来实现:$(word 1,<text>)。
以上，是所有的字符串操作函数，如果搭配混合使用，可以完成比较复杂的功能。这里，举一个现实中应 用的例子。我们知道，make 使用“VPATH”变量来指定“依赖文件”的搜索路径。于是，我们可以利用这个搜 索路径来指定编译器对头文件的搜索路径参数 CFLAGS，如:
    override CFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))

如果我们的“$(VPATH)”值是“src:../headers”，那么“$(patsubst
%,-I%,$(subst :, ,$(VPATH)))”将返回“-Isrc -I../headers”，这正是 cc 或 gcc 搜索头文件路 径的参数。

3. 文件名操作函数
下面我们要介绍的函数主要是处理文件名的。每个函数的参数字符串都会被当做一个或是一系列的文件名
来对待。

$(dir <names...>)
名称:取目录函数——dir。
功能:从文件名序列<names>中取出目录部分。目录部分是指最后一个反斜杠(“/”)之前的部分。 如果没有反斜杠，那么返回“./”。
返回:返回文件名序列<names>的目录部分。
示例: $(dir src/foo.c hacks)返回值是“src/ ./”。

$(notdir <names...>)
名称:取文件函数——notdir。
功能:从文件名序列<names>中取出非目录部分。非目录部分是指最后一个反斜杠(“/”)之后的部 分。
返回:返回文件名序列<names>的非目录部分。
示例: $(notdir src/foo.c hacks)返回值是“foo.c hacks”。

$(suffix <names...>)
名称:取后缀函数——suffix。 功能:从文件名序列<names>中取出各个文件名的后缀。 返回:返回文件名序列<names>的后缀序列，如果文件没有后缀，则返回空字串。 示例:$(suffix src/foo.c src-1.0/bar.c hacks)返回值是“.c .c”。

$(basename <names...>)
名称:取前缀函数——basename。
功能:从文件名序列<names>中取出各个文件名的前缀部分。 返回:返回文件名序列<names>的前缀序列，如果文件没有前缀，则返回空字串。 示例:$(basename src/foo.c src-1.0/bar.c hacks)返回值是“src/foo src-1.0/bar
hacks”。

$(addsuffix <suffix>,<names...>)
名称:加后缀函数——addsuffix。 功能:把后缀<suffix>加到<names>中的每个单词后面。 返回:返回加过后缀的文件名序列。
示例:$(addsuffix .c,foo bar)返回值是“foo.c bar.c”。

$(addprefix <prefix>,<names...>)
名称:加前缀函数——addprefix。 功能:把前缀<prefix>加到<names>中的每个单词前面。 返回:返回加过前缀的文件名序列。
示例:$(addprefix src/,foo bar)返回值是“src/foo src/bar”。

$(join <list1>,<list2>)
名称:连接函数——join。
功能:把<list2>中的单词对应地加到<list1>的单词后面。如果<list1>的单词个数要比<list2> 的多，那么，<list1>中的多出来的单词将保持原样。如果<list2>的单词个数要比<list1>多，那么， <list2>多出来的单词将被复制到<list2>中。
返回:返回连接过后的字符串。
示例:$(join aaa bbb , 111 222 333)返回值是“aaa111 bbb222 333”。

4. foreach函数
语法：
$(foreach <var>,<list>,<text>)
把参数<list>中的单词逐一取出放到参数<var>所指定的变量中，然后再执行 <text>所包含的表达式。每一次<text>会返回一个字符串，循环过程中，<text>的所返回的每个字符 串会以空格分隔，最后当整个循环结束时，<text>所返回的每个字符串所组成的整个字符串(以空格分隔) 将会是 foreach 函数的返回值。
所以，<var>最好是一个变量名，<list>可以是一个表达式，而<text>中一般会使用<var>这个参数来 依次枚举<list>中的单词。举个例子:
   names := a b c d
   files := $(foreach n,$(names),$(n).o)

5. if函数
if 函数很像 GNU 的 make 所支持的条件语句——ifeq，if 函数的语法是:
   $(if <condition>,<then-part>)
或是
   $(if <condition>,<then-part>,<else-part>)

6. call函数
call 函数是唯一一个可以用来创建新的参数化的函数。你可以写一个非常复杂的表达式，这个表达式中， 你可以定义许多参数，然后你可以用 call 函数来向这个表达式传递参数。其语法是:
   $(call <expression>,<parm1>,<parm2>,<parm3>...)
当 make 执行这个函数时，<expression>参数中的变量，如$(1)，$(2)，$(3)等，会被参数<parm1>， <parm2>，<parm3>依次取代。而<expression>的返回值就是 call 函数的返回值。例如:
reverse = $(1) $(2)
foo = $(call reverse,a,b)
那么，foo的值就是“a b”。

7. origin函数
origin 函数不像其它的函数，他并不操作变量的值，他只是告诉你你的这个变量是哪里来的?其语法是:
   $(origin <variable>)
注意，<variable>是变量的名字，不应该是引用。所以你最好不要在<variable>中使用“$”字符。 Origin 函数会以其返回值来告诉你这个变量的“出生情况”，下面，是 origin 函数的返回值:
“undefined”
如果<variable>从来没有定义过，origin 函数返回这个值“undefined”。
“default” 如果<variable>是一个默认的定义，比如“CC”这个变量，这种变量我们将在后面讲述。
“environment”
如果<variable>是一个环境变量，并且当 Makefile 被执行时，“-e”参数没有被打开。
“file”
如果<variable>这个变量被定义在 Makefile 中。
“command line” 如果<variable>这个变量是被命令行定义的。
“override”
如果<variable>是被 override 指示符重新定义的。
“automatic” 如果<variable>是一个命令运行中的自动化变量。关于自动化变量将在后面讲述。
这些信息对于我们编写 Makefile 是非常有用的，例如，假设我们有一个 Makefile 其包了一个定义文件 Make.def，在 Make.def 中定义了一个变量“bletch”，而我们的环境中也有一个环境变量 “bletch”，此时，我们想判断一下，如果变量来源于环境，那么我们就把之重定义了，如果来源于 Make.def 或是命令行等非环境的，那么我们就不重新定义它。于是，在我们的 Makefile 中，我们可以 这样写:
   ifdef bletch
   ifeq "$(origin bletch)" "environment"
   bletch = barf, gag, etc.
   endif
   endif

8. shell函数
shell 函数也不像其它的函数。顾名思义，它的参数应该就是操作系统 Shell 的命令。它和反引号“`” 是相同的功能。这就是说，shell 函数把执行操作系统命令后的输出作为函数返回。

9. 控制make的函数
make 提供了一些函数来控制 make 的运行。通常，你需要检测一些运行 Makefile 时的运行时信息，并 且根据这些信息来决定，你是让 make 继续执行，还是停止。

#### make的运行
1. make的退出码
0 —— 表示成功执行。
1 —— 如果 make 运行时出现任何错误，其返回 1。
2 —— 如果你使用了 make 的“-q”选项，并且 make 使得一些目标不需要更新，那么返回 2。

2. 指定Makefile
GNU make 找寻默认的 Makefile 的规则是在当前目录下依次找三个文件—— “GNUmakefile”、“makefile”和“Makefile”。其按顺序找这三个文件，一旦找到，就开始读取这个文件 并执行。
也可以给 make 命令指定一个特殊名字的 Makefile。要达到这个功能，我们要使用 make 的“-f” 或是“--file”参数(“--makefile”参数也行)。例如，我们有个 makefile 的名字是“hchen.mk”，那 么，我们可以这样来让 make 来执行这个文件:
make –f hchen.mk
如果在 make 的命令行是，你不只一次地使用了“-f”参数，那么，所有指定的 makefile 将会被连在一起传递给 make 执行。

3. 指定目标
一般来说，make 的最终目标是 makefile 中的第一个目标，而其它目标一般是由这个目标连带出来的。 这是 make 的默认行为。当然，一般来说，你的 makefile 中的第一个目标是由许多个目标组成，你可以指示make，让其完成你所指定的目标。要达到这一目的很简单，需在make命令后直接跟目标的名字就可 以完成(如前面提到的“make clean”形式)
即然 make 可以指定所有 makefile 中的目标，那么也包括“伪目标”，于是我们可以根据这种性质来让我 们的 makefile 根据指定的不同的目标来完成不同的事。
“all”
     这个伪目标是所有目标的目标，其功能一般是编译所有的目标。
“clean”
这个伪目标功能是删除所有被 make 创建的文件。 “install”
     这个伪目标功能是安装已编译好的程序，其实就是把目标执行文件拷贝到指定的目标中去。
“print”
     这个伪目标的功能是例出改变过的源文件。
“tar”
这个伪目标功能是把源程序打包备份。也就是一个 tar 文件。 
“dist”
这个伪目标功能是创建一个压缩文件，一般是把 tar 文件压成 Z 文件。或是 gz 文件。 
“TAGS”
这个伪目标功能是更新所有的目标，以备完整地重编译使用。 
“check”和“test”
这两个伪目标一般用来测试 makefile 的流程。

4. 检查规则

5. make的参数

#### 隐含规则
1. 使用隐含规则
如果我们为文件书写了自己的规则，那么 make 就不会自动推导并调用隐含规则，它会按照我 们写好的规则忠实地执行。
在 make 的“隐含规则库”中，每一条隐含规则都在库中有其顺序，越靠前的则是越被经常使用的，所 以，这会导致我们有些时候即使我们显示地指定了目标依赖，make 也不会管。

2. 隐含规则一览
所有预先设置(也就是 make 内建)的隐含规则，如果我们不明确地写下规则，那么，make 就会在这些规则中寻找所需要规则和命令。当然，我们也可以使用 make 的参数“-r”或 “--no-builtin-rules”选项来取消所有的预设置的隐含规则。
当然，即使是我们指定了“-r”参数，某些隐含规则还是会生效，因为有许多的隐含规则都是使用了“后缀规则”来定义的

3. 隐含规则使用的变量
在隐含规则中的命令中，基本上都是使用了一些预先设置的变量。你可以在你的 makefile 中改变这些变 量的值，或是在 make 的命令行中传入这些值，或是在你的环境变量中设置这些值，无论怎么样，只要设 置了这些特定的变量，那么其就会对隐含规则起作用。当然，你也可以利用 make 的“-R”或“--no–builtin-variables”参数来取消你所定义的变量对隐含规则的作用。
例如，第一条隐含规则——编译 C 程序的隐含规则的命令是“$(CC) –c $(CFLAGS) $(CPPFLAGS)”。 Make 默认的编译命令是“cc”，如果你把变量“$(CC)”重定义成“gcc”，把变量“$(CFLAGS)”重定义成“-g”， 那么，隐含规则中的命令全部会以“gcc –c -g $(CPPFLAGS)”的样子来执行了。我们可以把隐含规则中使用的变量分成两种:一种是命令相关的，如“CC”;一种是命令参数相关的，如“CFLAGS”。

4. 隐含规则链
有些时候，一个目标可能被一系列的隐含规则所作用。例如，一个[.o]的文件生成，可能会是先被 Yacc的[.y]文件先成[.c]，然后再被 C 的编译器生成。我们把这一系列的隐含规则叫做“隐含规则链”。

5. 定义模式规则
下面这个例子表示了,把所有的[.c]文件都编译成[.o]文件.
    %.o : %.c
            $(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
其中，"$@"表示所有的目标的挨个值，"$<"表示了所有依赖目标的挨个值。这些奇怪的变量我们叫"自动化变量"。
所谓自动化变量，就是这种变量会把模式中所定义的一系列的文件自动地挨个取出，直至所有的符合模式的文件都取完了。这种自动化变量只应出现在规则的命令中。

#### 使用make更新函数库文件
函数库文件也就是对 Object 文件(程序编译的中间文件)的打包文件。在 Unix 下，一般是由命令"ar" 来完成打包工作。
1. 函数库文件的成员
一个函数库文件由多个文件组成。你可以以如下格式指定函数库文件及其组成:
archive(member) 这个不是一个命令，而一个目标和依赖的定义。一般来说，这种用法基本上就是为了"ar"命令来服务的。
如:
如果要指定多个 member，那就以空格分开，如: foolib(hack.o kludge.o)

2. 函数库成员的隐含规则
当 make 搜索一个目标的隐含规则时，一个特殊的特性是，如果这个目标是"a(m)"形式的，其会把目标变 成"(m)"。于是，如果我们的成员是"%.o"的模式定义，并且如果我们使用"make foo.a(bar.o)"的形 式调用 Makefile 时，隐含规则会去找"bar.o"的规则，如果没有定义 bar.o 的规则，那么内建隐含规 则生效，make 会去找 bar.c 文件来生成 bar.o，如果找得到的话，make 执行的命令大致如下:
    cc -c bar.c -o bar.o
    ar r foo.a bar.o
    rm -f bar.o

3. 函数库文件的后缀规则
...