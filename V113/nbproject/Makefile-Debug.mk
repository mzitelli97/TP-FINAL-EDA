#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/BurgleBrosBoard.o \
	${OBJECTDIR}/BurgleBrosCard.o \
	${OBJECTDIR}/BurgleBrosController.o \
	${OBJECTDIR}/BurgleBrosDices.o \
	${OBJECTDIR}/BurgleBrosFloor.o \
	${OBJECTDIR}/BurgleBrosGuard.o \
	${OBJECTDIR}/BurgleBrosLoots.o \
	${OBJECTDIR}/BurgleBrosModel.o \
	${OBJECTDIR}/BurgleBrosPlayer.o \
	${OBJECTDIR}/BurgleBrosSound.o \
	${OBJECTDIR}/BurgleBrosTokens.o \
	${OBJECTDIR}/BurgleBrosView.o \
	${OBJECTDIR}/Controller.o \
	${OBJECTDIR}/EventData.o \
	${OBJECTDIR}/GUI.o \
	${OBJECTDIR}/GraphicButton.o \
	${OBJECTDIR}/GraphicEDices.o \
	${OBJECTDIR}/GraphicGDie.o \
	${OBJECTDIR}/GraphicGuard.o \
	${OBJECTDIR}/GraphicGuardCards.o \
	${OBJECTDIR}/GraphicItem.o \
	${OBJECTDIR}/GraphicLoot.o \
	${OBJECTDIR}/GraphicMenuItem.o \
	${OBJECTDIR}/GraphicPlayer.o \
	${OBJECTDIR}/GraphicPlayerCard.o \
	${OBJECTDIR}/GraphicTile.o \
	${OBJECTDIR}/GraphicToken.o \
	${OBJECTDIR}/GraphicWall.o \
	${OBJECTDIR}/ImageLoader.o \
	${OBJECTDIR}/LibsInit.o \
	${OBJECTDIR}/Model.o \
	${OBJECTDIR}/MouseED.o \
	${OBJECTDIR}/NetworkED.o \
	${OBJECTDIR}/NetworkInterface.o \
	${OBJECTDIR}/Networking.o \
	${OBJECTDIR}/ProtocolFunctions.o \
	${OBJECTDIR}/SoundManager.o \
	${OBJECTDIR}/View.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs allegro-5.0` `pkg-config --libs allegro_acodec-5.0` `pkg-config --libs allegro_audio-5.0` `pkg-config --libs allegro_color-5.0` `pkg-config --libs allegro_dialog-5.0` `pkg-config --libs allegro_font-5.0` `pkg-config --libs allegro_image-5.0` `pkg-config --libs allegro_main-5.0` `pkg-config --libs allegro_memfile-5.0` `pkg-config --libs allegro_physfs-5.0` `pkg-config --libs allegro_primitives-5.0` `pkg-config --libs allegro_ttf-5.0` `pkg-config --libs apr-1`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/v113

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/v113: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/v113 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/BurgleBrosBoard.o: BurgleBrosBoard.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosBoard.o BurgleBrosBoard.cpp

${OBJECTDIR}/BurgleBrosCard.o: BurgleBrosCard.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosCard.o BurgleBrosCard.cpp

${OBJECTDIR}/BurgleBrosController.o: BurgleBrosController.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosController.o BurgleBrosController.cpp

${OBJECTDIR}/BurgleBrosDices.o: BurgleBrosDices.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosDices.o BurgleBrosDices.cpp

${OBJECTDIR}/BurgleBrosFloor.o: BurgleBrosFloor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosFloor.o BurgleBrosFloor.cpp

${OBJECTDIR}/BurgleBrosGuard.o: BurgleBrosGuard.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosGuard.o BurgleBrosGuard.cpp

${OBJECTDIR}/BurgleBrosLoots.o: BurgleBrosLoots.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosLoots.o BurgleBrosLoots.cpp

${OBJECTDIR}/BurgleBrosModel.o: BurgleBrosModel.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosModel.o BurgleBrosModel.cpp

${OBJECTDIR}/BurgleBrosPlayer.o: BurgleBrosPlayer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosPlayer.o BurgleBrosPlayer.cpp

${OBJECTDIR}/BurgleBrosSound.o: BurgleBrosSound.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosSound.o BurgleBrosSound.cpp

${OBJECTDIR}/BurgleBrosTokens.o: BurgleBrosTokens.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosTokens.o BurgleBrosTokens.cpp

${OBJECTDIR}/BurgleBrosView.o: BurgleBrosView.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BurgleBrosView.o BurgleBrosView.cpp

${OBJECTDIR}/Controller.o: Controller.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Controller.o Controller.cpp

${OBJECTDIR}/EventData.o: EventData.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EventData.o EventData.cpp

${OBJECTDIR}/GUI.o: GUI.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GUI.o GUI.cpp

${OBJECTDIR}/GraphicButton.o: GraphicButton.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicButton.o GraphicButton.cpp

${OBJECTDIR}/GraphicEDices.o: GraphicEDices.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicEDices.o GraphicEDices.cpp

${OBJECTDIR}/GraphicGDie.o: GraphicGDie.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicGDie.o GraphicGDie.cpp

${OBJECTDIR}/GraphicGuard.o: GraphicGuard.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicGuard.o GraphicGuard.cpp

${OBJECTDIR}/GraphicGuardCards.o: GraphicGuardCards.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicGuardCards.o GraphicGuardCards.cpp

${OBJECTDIR}/GraphicItem.o: GraphicItem.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicItem.o GraphicItem.cpp

${OBJECTDIR}/GraphicLoot.o: GraphicLoot.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicLoot.o GraphicLoot.cpp

${OBJECTDIR}/GraphicMenuItem.o: GraphicMenuItem.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicMenuItem.o GraphicMenuItem.cpp

${OBJECTDIR}/GraphicPlayer.o: GraphicPlayer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicPlayer.o GraphicPlayer.cpp

${OBJECTDIR}/GraphicPlayerCard.o: GraphicPlayerCard.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicPlayerCard.o GraphicPlayerCard.cpp

${OBJECTDIR}/GraphicTile.o: GraphicTile.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicTile.o GraphicTile.cpp

${OBJECTDIR}/GraphicToken.o: GraphicToken.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicToken.o GraphicToken.cpp

${OBJECTDIR}/GraphicWall.o: GraphicWall.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicWall.o GraphicWall.cpp

${OBJECTDIR}/ImageLoader.o: ImageLoader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ImageLoader.o ImageLoader.cpp

${OBJECTDIR}/LibsInit.o: LibsInit.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LibsInit.o LibsInit.cpp

${OBJECTDIR}/Model.o: Model.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Model.o Model.cpp

${OBJECTDIR}/MouseED.o: MouseED.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MouseED.o MouseED.cpp

${OBJECTDIR}/NetworkED.o: NetworkED.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NetworkED.o NetworkED.cpp

${OBJECTDIR}/NetworkInterface.o: NetworkInterface.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NetworkInterface.o NetworkInterface.cpp

${OBJECTDIR}/Networking.o: Networking.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Networking.o Networking.cpp

${OBJECTDIR}/ProtocolFunctions.o: ProtocolFunctions.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ProtocolFunctions.o ProtocolFunctions.cpp

${OBJECTDIR}/SoundManager.o: SoundManager.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SoundManager.o SoundManager.cpp

${OBJECTDIR}/View.o: View.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/View.o View.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
