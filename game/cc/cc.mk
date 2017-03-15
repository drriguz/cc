##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=cc
ConfigurationName      :=Debug
WorkspacePath          :=/home/riguz/workspace/cc/game
ProjectPath            :=/home/riguz/workspace/cc/game/cc
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=riguz
Date                   :=15/03/17
CodeLitePath           :=/home/riguz/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="cc.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./src 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)tmxparser $(LibrarySwitch)SDL2 $(LibrarySwitch)SDL2_image $(LibrarySwitch)SDL2_ttf $(LibrarySwitch)SDL2_mixer 
ArLibs                 :=  "libtmxparser" "libSDL2" "libSDL2_image" "libSDL2_ttf" "libSDL2_mixer" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_game.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_object.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_map.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_texture.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/riguz/workspace/cc/game/cc/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/src_game.cpp$(ObjectSuffix): src/game.cpp $(IntermediateDirectory)/src_game.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/riguz/workspace/cc/game/cc/src/game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_game.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_game.cpp$(DependSuffix): src/game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_game.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_game.cpp$(DependSuffix) -MM src/game.cpp

$(IntermediateDirectory)/src_game.cpp$(PreprocessSuffix): src/game.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_game.cpp$(PreprocessSuffix) src/game.cpp

$(IntermediateDirectory)/src_object.cpp$(ObjectSuffix): src/object.cpp $(IntermediateDirectory)/src_object.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/riguz/workspace/cc/game/cc/src/object.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_object.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_object.cpp$(DependSuffix): src/object.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_object.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_object.cpp$(DependSuffix) -MM src/object.cpp

$(IntermediateDirectory)/src_object.cpp$(PreprocessSuffix): src/object.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_object.cpp$(PreprocessSuffix) src/object.cpp

$(IntermediateDirectory)/src_map.cpp$(ObjectSuffix): src/map.cpp $(IntermediateDirectory)/src_map.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/riguz/workspace/cc/game/cc/src/map.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_map.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_map.cpp$(DependSuffix): src/map.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_map.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_map.cpp$(DependSuffix) -MM src/map.cpp

$(IntermediateDirectory)/src_map.cpp$(PreprocessSuffix): src/map.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_map.cpp$(PreprocessSuffix) src/map.cpp

$(IntermediateDirectory)/src_texture.cpp$(ObjectSuffix): src/texture.cpp $(IntermediateDirectory)/src_texture.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/riguz/workspace/cc/game/cc/src/texture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_texture.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_texture.cpp$(DependSuffix): src/texture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_texture.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_texture.cpp$(DependSuffix) -MM src/texture.cpp

$(IntermediateDirectory)/src_texture.cpp$(PreprocessSuffix): src/texture.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_texture.cpp$(PreprocessSuffix) src/texture.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


