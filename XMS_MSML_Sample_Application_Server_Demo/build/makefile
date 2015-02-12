#!/bin/bash
###############################################################################
##
## Copyright © 2006-2012 Dialogic Inc. All Rights Reserved.
##
## The source code contained or described herein and all documents related to
## the source code (collectively "Material") are owned by Dialogic Inc.,
## its subsidiaries, affiliates, suppliers, licensors and/or assigns 
## ("Dialogic"). Title to the Material remains with Dialogic. The Material 
## contains proprietary information and material of Dialogic. The Material is 
## protected by worldwide copyright, trade secret laws, treaty provisions 
## and/or other applicable intellectual property rights, laws and/or treaties.
## No part of the Material may be used, copied, reproduced, modified, 
## published, uploaded, posted, transmitted, distributed, or disclosed in any 
## way without Dialogic's prior express written permission.
##
## No license under any patent, copyright, trade secret or other intellectual
## property right is granted to or conferred upon you by disclosure or delivery
## of the Material, either expressly, by implication, inducement, estoppels
## or otherwise. Any license under such intellectual property rights must be
## express and approved by Dialogic in writing.
##
###############################################################################
## File Name: makefile
##
## Description: Linux makefile for app_server
##
##	Requires that the following environmental variables be defined:
##
##	INTEL_DIALOGIC_INC - path to the Intel Dialogic include directory
##	INTEL_DIALOGIC_LIB - path to the Intel Dialogic library directory
###############################################################################

# define the project
PROJECT  = app_server

# qualify target
ifeq ($(MAKECMDGOALS),debug)
BUILD:=debug
endif

ifeq ($(MAKECMDGOALS),release)
BUILD:=release
endif

ifeq ($(MAKECMDGOALS),)
BUILD:=release
endif

ifeq ($(MAKECMDGOALS),all)
BUILD:=release
endif

ifeq ($(MAKECMDGOALS),clean)
BUILD:=clean
endif

ifeq ($(findstring $(BUILD),debug release or clean),)
$(error make target is unknown, must be clean, debug or release)
endif

## Includes ###################################################################

INCLUDE = -I ../src -I $(INTEL_DIALOGIC_INC)

## Libraries ##################################################################

ifeq ($(BUILD),debug)
LIBS =  -lpthread -lsrl -lgc -ldevmgmt -ldxxx -ldti -lrtf -lxerces -lboost_thread -lcurl
else
LIBS =  -lpthread -lsrl -lgc -ldevmgmt -ldxxx -ldti -lrtf -lxerces -lboost_thread -lcurl
endif

## Object files ###############################################################

FILE_LIST = 	app_server \
		ACallflow \
		ACallflowManager \
		ADispatcher \
		AGlobalCallManager \
		AObserverSubject \
		ARemoteMediaControlClient \
		AResourceGroup \
		AResourceGroupManager \
		AResourceManager \
		ASipBoardResource \
		ASipResource \
		ASipResourceManager \
		ASrlEventManager \
		ATaskHandler \
		CallflowManagerStates \
		CallflowStates \
		CCallflow \
		CCallflowManager \
		CConfigOptions \
		CConference \
		CConferenceManager \
		CGlobalCallManager \
		CLogger \
		CMetaEvent \
		CMsmlCreateConference \
		CMsmlCreateVideoConference \
		CMsmlModifyVideoConference \
		CMsmlDialog \
		CMsmlDialogVideoMailPlay \
		CMsmlDialogVideoMailRecord \
		CMsmlDialogVideoMailRecordStart \
		CMsmlDialogVoiceMailPlay \
		CMsmlDialogVoiceMailRecord \
		CMsmlDialogVoiceMailRecordStart \
		CMsmlEvent \
		CMsmlJoinConference \
		CMsmlJoinVideoConference \
		CMsmlModifyStream \
		CMsmlCollectDtmfs \
		CMsmlResponse \
		CRemoteMediaControlClient \
		CResourceGroup \
		CResourceGroupManager \
		CResourceManager \
		CSipBoardResource \
		CSipCallInfo \
		CSipResource \
		CSipResourceManager \
		CSrlEventManager \
		CTask \
		CTaskProcessor \
		GlobalCallManagerStates \
		RemoteMediaControlClientStates \
		ResourceGroupManagerStates \
		ResourceGroupStates \
		ResourceManagerStates \
		SipBoardResourceStates \
		SipResourceManagerStates \
		SipResourceStates \
		SrlEventManagerStates \
		Utility \
		HttpManagerStates \
		AHttpManager \
		CHttpManager \
		AHttpRequest \
		CHttpRequest \
		CHttpDelete
		

TARGET_OBJS:=$(foreach name, $(FILE_LIST), ./$(BUILD)/$(name).o)

## Compilation and Linking ####################################################
ifeq ($(BUILD),debug)
CFLAGS = -pthread -g -c $(INCLUDE)
LFLAGS = -g -L$(INTEL_DIALOGIC_LIB)
else
CFLAGS = -pthread -c $(INCLUDE)
LFLAGS = -L$(INTEL_DIALOGIC_LIB)
endif

COMPILER = g++
LINKER   = g++

## rules

./$(BUILD)/%.o : ../src/%.cpp
	$(COMPILER) $(CFLAGS) $< -m32 -o $@

./$BUILD)/$(PROJECT): $(TARGET_OBJS)
	$(LINKER) $(TARGET_OBJS) $(LFLAGS) $(LIBS) -m32 -o ./$(BUILD)/$(PROJECT)

# targets
clean:
	-/bin/rm -f ./release/$(PROJECT)
	-/bin/rm -f ./release/*.o
	-/bin/rm -f ./debug/$(PROJECT)
	-/bin/rm -f ./debug/*.o

all: ./$BUILD)/$(PROJECT)

debug: ./$BUILD)/$(PROJECT)

release: ./$BUILD)/$(PROJECT)

