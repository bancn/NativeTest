1. 在JAVA代码里编写native函数的声明

   ```java
   public native String getStringFromNative();
   ```

2. 进入到src/main/java 目录下，执行 `javah -jni this.is.a.package.name.classname`, 来生成.h文件。

3. 在app/src/main目录下新建一个文件夹，存放.c和.h文件，将生成的.h文件复制到这里来，删除原来生成的.h文件

4. 在app目录下的build.gradle中，android{}标签内添加，在path中指定CMakeLists的

```xml
externalNativeBuild {

        // Encapsulates your CMake build configurations.
        cmake {

            // Provides a relative path to your CMake build script.
            path "CMakeLists.txt"
        }
    }
```

5. 在app目录下新建CMakeLists.txt，输入以下内容

```xml
# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

add_library( # Specifies the name of the library.
             JNIStudy

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/jni/JNIStudy.c )

# Specifies a path to native header files.
include_directories(src/main/jni/)

```

6. 在需要调用的地方加入引用SO的代码

   ```java
   static {
           System.loadLibrary("JNIStudy");
       }
   ```

   