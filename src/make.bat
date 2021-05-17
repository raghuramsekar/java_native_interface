@rem compile java
javac -h . Caller.java


@rem compile cpp and link that output file to library
g++ -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o nativelib.dll Native.cpp
g++ -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o accessSec.dll access_mask.cpp



@rem run java program
java Caller
