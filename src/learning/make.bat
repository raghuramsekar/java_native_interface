@rem java compilation and header creation
javac -h  . StringIni.java

@rem compile cpp and link that output file to library
g++ -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o libNativeStr.dll NativeStringImpl.cpp


@rem run java program
java StringIni

