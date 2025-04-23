## how to release Windows Program
# 1. Project Properties
	1.1 Configuration Properties | C/C++ | Code Generation | Runtime Library: Multi-threaded DLL (/MD)
	1.2 Configuration Properties | Linker | System | Subsystem | Windows (/SUBSYSTEM:WINDOWS)

# 2. Build Using Command Line as follows:

	2.1 Tools | Command line | Developer Command Prompt
	2.2 Build Exe in release more as follows ->
	2.3 Go to folder were *.vcxproj is located 
	2.4 run ->  msbuild SteelProperties.vcxproj /p:Configuration=Release /p:Platform=x64
		
# 3. Check dependencies as follows:
	3.1 Tools | Command line | Developer Command Prompt
	3.2 to folder were *.vcxproj is located 
	3.3 run -> dumpbin /DEPENDENTS x64\Release\SteelProperties.exe
	3.4 This will list the dependencies similar to the following:
		  Image has the following dependencies:
			(*) MSVCP140.dll
			api-ms-win-crt-heap-l1-1-0.dll
			KERNEL32.dll
			api-ms-win-crt-runtime-l1-1-0.dll
			(*) VCRUNTIME140.dll
			api-ms-win-crt-stdio-l1-1-0.dll
			api-ms-win-crt-filesystem-l1-1-0.dll
			api-ms-win-crt-string-l1-1-0.dll
			mscoree.dll
# 4.  Package up the following files in a folder structure like the example below:
	4.1 Required data files (csv/binaries)
	4.2 Executible elf .exe
	4.3 dll files
	4.4 Example release files:
		steelProperties\
			Data\ShapeDescriptions.csv
			def_tables\field_names.csv
			def_tables\shapes.bin

			SteelProperties.exe
			
			msvcp140.dll
			ucrtbase.dll
			vcruntime140.dll

