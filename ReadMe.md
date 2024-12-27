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




plantuml

@startuml
actor User

User -> RunConfiguration : "Configure Debug"
RunConfiguration -> RunConfigurationType : "Select Configuration Type"
RunConfiguration -> RunState : "Define Run State"
RunConfigurationType -> Runner : "Run Debugger"
Runner -> DebugSession : "Start Debug Session"
DebugSession -> DebugProcess : "Manage Debug Process"
DebugProcess -> Debugger : "Trigger Debugger Actions"
DebugProcess -> SteppingCommand : "Trigger Step Command"
SteppingCommand -> SteppingHandler : "Handle Step Command"
SteppingHandler -> StepInto : "Step Into"
SteppingHandler -> StepOver : "Step Over"
DebugSession -> ConsoleView : "Show Console Output"
ConsoleView -> ConsoleRunner : "Display Debug Info"
ConsoleRunner -> ConsoleOutput : "Show Output"
DebugProcess -> DebugConsole : "Manage Console"
DebugConsole -> ConsoleView : "Show Log"

@enduml


***********************************************************************

@startuml
package "Debugging" {
  [DebugSession] --> [DebugProcess] : Manages
  [DebugProcess] --> [Debugger] : Controls Execution
  [DebugProcess] --> [ThreadManager] : Manages Threads
  [ThreadManager] --> [Thread] : Lists Threads
  [Thread] --> [StackTrace] : Tracks Execution
  [Debugger] --> [ConsoleView] : Displays Output
  [ConsoleView] --> [ConsoleRunner] : Runs Console
  [ConsoleRunner] --> [ConsoleOutput] : Displays Debug Info
}

package "User Interface" {
  [RunConfiguration] --> [RunState] : Configures Debug
  [RunConfiguration] --> [Runner] : Starts Debug
  [RunState] --> [Runner] : Manages State
}

@enduml


**********************************************************************************

@startuml
actor User

User -> RunConfiguration : "Configure Debug"
RunConfiguration -> RunConfigurationType : "Select Configuration Type"
RunConfiguration -> RunState : "Define Run State"
RunConfigurationType -> Runner : "Run Debugger"
Runner -> DebugSession : "Start Debug Session"
DebugSession -> DebugProcess : "Manage Debug Process"
DebugProcess -> Debugger : "Trigger Debugger Actions"
DebugProcess -> ThreadManager : "Manage Threads"
ThreadManager -> Thread : "List Threads"
Thread -> StackTrace : "Get Stack Trace"
StackTrace -> StackFrame : "Get Stack Frame"
Thread -> DebugCommand : "Trigger Debug Command"
DebugCommand -> SteppingHandler : "Handle Debug Command"
SteppingHandler -> StackTrace : "Update Stack Trace"
SteppingHandler -> ThreadManager : "Switch Threads"
DebugSession -> ConsoleView : "Show Console Output"
ConsoleView -> ConsoleRunner : "Display Debug Info"
ConsoleRunner -> ConsoleOutput : "Show Output"
DebugProcess -> DebugConsole : "Manage Console"
DebugConsole -> ConsoleView : "Show Log"

@enduml


