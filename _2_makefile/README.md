### 使用Make和CMake进行构建

我们的项目可能会有很多很多的内容需要去进行编译，如何去进行组织成了一个大问题，比如让谁先编译，谁后编译，这时，我们就需要一个构建工具来帮助我们对程序的构建流程进行组织。

>  Make是最常用的构建工具，诞生于1977年，主要用于C语言的项目。但是实际上 ，任何只要某个文件有变化，就要重新构建的项目，都可以用Make构建。

要使用Make对我们的项目进行构建，我们需要先告诉Make我们的程序应该如何去进行构建，这时我们就要编写一下Makefile了：

![image-20220627135232863](https://s2.loli.net/2022/06/27/3bRneOcMtfZyPw7.png)

我们只需要把需要执行的命令按照我们想要的顺序全部写到里面就可以了，但是需要遵循以下格式：

```makefile
targets : prerequisites
  command
```

一个Makefile中可以有很多个目标，比如我们现在要分别编译main.c和test.c，那么就需要创建两个目标：

* targets：构建的目标，可以是一个普通的标签、文件名称等
* prerequisites：前置条件，可以设定要求完成其他目标才能开始构建当前目标
* command：构建需要执行的命令

比如现在我们想要分别先编译test.c和main.c，最后将他们变成一个可执行文件，那么makefile可以这样编写：

```makefile
main.exe: test.o main.o  #目标1：构建最终的程序，要求完成下面两个目标（注意最终目标需要写在第一个）
	gcc test.o main.o -o main

main.o: main.c  #目标2：构建目标为main.o，前置要求必须有main.c文件
	gcc -E main.c -o main.i
	gcc -S main.i -o main.s
	gcc -c main.s -o main.o

test.o: test.c  #目标3：同样的，要求必须有test.c文件才能开始
	gcc -E test.c -o test.i
	gcc -S test.i -o test.s
	gcc -c test.s -o test.o
```

接着我们只需要在控制台输入make命令（CLion自带环境需要输入mingw32-make命令，Mac下直接输入make）就可以进行编译了：

![image-20220627212727506](https://s2.loli.net/2022/06/27/9nGRvqp8SjUXhN7.png)

命令执行的每一步都会详细打印出来，我们可以看到构建确实是按照我们的顺序在进行，并且成功编译出最终目标：

![image-20220627212822806](https://s2.loli.net/2022/06/27/FTILC5evZ67rEXo.png)

当然，如果我们没有做任何的修改，那么再次执行make命令不会做任何事情：

![image-20220627212951245](https://s2.loli.net/2022/06/27/BQSIXTpvOc9Jukh.png)

但是如果我们修改一下源文件的话，执行make将会重新构建目标：

![image-20220627213029819](https://s2.loli.net/2022/06/27/sfQgxm34vlw8TKi.png)

再次执行：

![image-20220627213051247](https://s2.loli.net/2022/06/27/SrE9FcADYWaywRN.png)

通过使用Make，即使没有如此高级的IDE，哪怕我们纯靠记事本写C代码，都可以很方便地完成对一个项目的构建了。当然这只是Make的简单使用，它还支持使用变量、逻辑判断等高级玩法，这里我们就不多做介绍了。

虽然使用Make可以很方便地对项目构建流程进行配置，但是貌似CLion并没有采用这种方式来组织我们的项目进行构建，而是使用了CMake，我们来看看它又是做什么的。

> CMake是一个跨平台的安装（[编译](https://baike.baidu.com/item/编译/1258343)）工具，可以用简单的语句来描述所有平台的安装(编译过程)。他能够输出各种各样的makefile或者project文件，能测试[编译器](https://baike.baidu.com/item/编译器/8853067)所支持的C++特性,类似[UNIX](https://baike.baidu.com/item/UNIX/219943)下的automake。

简而言之， CMake是一个跨平台的Makefile生成工具!

实际上当我们创建一个项目后，CLion会自动为我们配置CMake，而具体的配置都是写在CMakeList.txt中的：

```cmake
cmake_minimum_required(VERSION 3.22)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c test.c test.h)
```

我们逐行来进行解读：

* 第一行使用cmake_minimum_required来指定当前项目使用的CMake最低版本，如果使用的CMake程序低于此版本是无法构建的。
* 第二行project指定项目名称，名称随意，后面的是项目使用的语言，这里是C。
* 第三行set用于设定一些环境变量等，这里设定的是C 99标准。
* 第四行add_executable用于指定一个编译出来的可执行文件，这里名称为untitled，后面的都是需要编译的源文件（头文件可以不写）

当然除了这些语法之外，还有各种各样的设定，比如设定库目录或是外部动态连接库等，这里就不多说了，感兴趣的可以自行了解。

这里我们来手动执行一下cmake：

![image-20220627215908039](https://s2.loli.net/2022/06/27/XFpHB1aPbRCA4kL.png)

首先还是添加环境变量，添加完成后重启CLion，我们输入cmake命令进行生成：

```sh
 cmake -S . -B test -G "MinGW Makefiles"
```

其中`-S`后面的是源文件目录，这里`.`表示当前目录，`-B`后面是构建目录，一会构建的文件都在这里面存放，最后`-G`是选择生成器（生成器有很多，甚至可以直接生成一个VS项目，我们可以直接使用Visual Studio打开），这里我们需要生成Makefile，所以填写"MinGW Makefiles"：

![image-20220627221226478](https://s2.loli.net/2022/06/27/MUgkvuARteyS2wQ.png)

可以看到已经成功在我们的构建目录中生成了：

![image-20220627221335557](https://s2.loli.net/2022/06/27/uMtaVgILmjFhiR9.png)

只不过它这个自动生成的Makefile写的就比较复杂了，我们也不需要去关心，接着我们像之前一样直接使用make就可以编译了：

这里要先进入一下test目录，使用`cd test`命令修改当前工作目录：

![image-20220627221459717](https://s2.loli.net/2022/06/27/DNnROjG1eh8V7kA.png)

可以看到它生成的Makefile还是挺高级的，还能输出进度，现在我们的程序就构建好了，直接启动把：

![image-20220627221546242](https://s2.loli.net/2022/06/27/IWPbV8nJ3XFLfEz.png)

当然CLion并没有使用Makefile的编译方式，而是Ninja，并且生成的构建文件默认存放在`cmake-build-debug`中，跟make比较类似，但是速度会更快一些，不过最后都会成功构建出我们的可执行程序。

这下，我们就清楚整个项目中个个文件是干嘛的了。