##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=graph_solver
ConfigurationName      :=Debug
WorkspacePath          :=/home/grey/Public/codelite_workspace
ProjectPath            :=/home/grey/Public/codelite_workspace/graph_solver
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=grey sky
Date                   :=12/28/19
CodeLitePath           :=/home/grey/.codelite
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
ObjectsFileList        :="graph_solver.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell pkg-config --libs gtk+-3.0) -export-dynamic
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -Wall -O0 $(shell pkg-config --cflags gtk+-3.0) -export-dynamic $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/edge.c$(ObjectSuffix) $(IntermediateDirectory)/linked_list.c$(ObjectSuffix) $(IntermediateDirectory)/graph.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/grey/Public/codelite_workspace/graph_solver/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/edge.c$(ObjectSuffix): edge.c $(IntermediateDirectory)/edge.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/grey/Public/codelite_workspace/graph_solver/edge.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/edge.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/edge.c$(DependSuffix): edge.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/edge.c$(ObjectSuffix) -MF$(IntermediateDirectory)/edge.c$(DependSuffix) -MM edge.c

$(IntermediateDirectory)/edge.c$(PreprocessSuffix): edge.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/edge.c$(PreprocessSuffix) edge.c

$(IntermediateDirectory)/linked_list.c$(ObjectSuffix): linked_list.c $(IntermediateDirectory)/linked_list.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/grey/Public/codelite_workspace/graph_solver/linked_list.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/linked_list.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/linked_list.c$(DependSuffix): linked_list.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/linked_list.c$(ObjectSuffix) -MF$(IntermediateDirectory)/linked_list.c$(DependSuffix) -MM linked_list.c

$(IntermediateDirectory)/linked_list.c$(PreprocessSuffix): linked_list.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/linked_list.c$(PreprocessSuffix) linked_list.c

$(IntermediateDirectory)/graph.c$(ObjectSuffix): graph.c $(IntermediateDirectory)/graph.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/grey/Public/codelite_workspace/graph_solver/graph.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/graph.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/graph.c$(DependSuffix): graph.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/graph.c$(ObjectSuffix) -MF$(IntermediateDirectory)/graph.c$(DependSuffix) -MM graph.c

$(IntermediateDirectory)/graph.c$(PreprocessSuffix): graph.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/graph.c$(PreprocessSuffix) graph.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


