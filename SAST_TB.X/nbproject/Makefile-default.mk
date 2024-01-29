#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SAST_TB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SAST_TB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Accel_ADXL355.c ../Accel_ADXL373.c ../CAN.c ../CRC.c ../DMA.c ../Init.c ../MAG_MMC5983MA.c ../MEM_MT25QL01.c ../SPI.c ../Uart.c ../main.c ../MUX1_ADG732.c ../ADC_ADS868x.c ../ADC_ADS863x.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/Accel_ADXL355.o ${OBJECTDIR}/_ext/1472/Accel_ADXL373.o ${OBJECTDIR}/_ext/1472/CAN.o ${OBJECTDIR}/_ext/1472/CRC.o ${OBJECTDIR}/_ext/1472/DMA.o ${OBJECTDIR}/_ext/1472/Init.o ${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o ${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o ${OBJECTDIR}/_ext/1472/SPI.o ${OBJECTDIR}/_ext/1472/Uart.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/MUX1_ADG732.o ${OBJECTDIR}/_ext/1472/ADC_ADS868x.o ${OBJECTDIR}/_ext/1472/ADC_ADS863x.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/Accel_ADXL355.o.d ${OBJECTDIR}/_ext/1472/Accel_ADXL373.o.d ${OBJECTDIR}/_ext/1472/CAN.o.d ${OBJECTDIR}/_ext/1472/CRC.o.d ${OBJECTDIR}/_ext/1472/DMA.o.d ${OBJECTDIR}/_ext/1472/Init.o.d ${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o.d ${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o.d ${OBJECTDIR}/_ext/1472/SPI.o.d ${OBJECTDIR}/_ext/1472/Uart.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/MUX1_ADG732.o.d ${OBJECTDIR}/_ext/1472/ADC_ADS868x.o.d ${OBJECTDIR}/_ext/1472/ADC_ADS863x.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/Accel_ADXL355.o ${OBJECTDIR}/_ext/1472/Accel_ADXL373.o ${OBJECTDIR}/_ext/1472/CAN.o ${OBJECTDIR}/_ext/1472/CRC.o ${OBJECTDIR}/_ext/1472/DMA.o ${OBJECTDIR}/_ext/1472/Init.o ${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o ${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o ${OBJECTDIR}/_ext/1472/SPI.o ${OBJECTDIR}/_ext/1472/Uart.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/MUX1_ADG732.o ${OBJECTDIR}/_ext/1472/ADC_ADS868x.o ${OBJECTDIR}/_ext/1472/ADC_ADS863x.o

# Source Files
SOURCEFILES=../Accel_ADXL355.c ../Accel_ADXL373.c ../CAN.c ../CRC.c ../DMA.c ../Init.c ../MAG_MMC5983MA.c ../MEM_MT25QL01.c ../SPI.c ../Uart.c ../main.c ../MUX1_ADG732.c ../ADC_ADS868x.c ../ADC_ADS863x.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/SAST_TB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33CK512MP605
MP_LINKER_FILE_OPTION=,--script=p33CK512MP605.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/Accel_ADXL355.o: ../Accel_ADXL355.c  .generated_files/flags/default/d7c08b649955b9d68520ed5fea2de0e47be7295b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Accel_ADXL355.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Accel_ADXL355.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Accel_ADXL355.c  -o ${OBJECTDIR}/_ext/1472/Accel_ADXL355.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Accel_ADXL355.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Accel_ADXL373.o: ../Accel_ADXL373.c  .generated_files/flags/default/658fd265c75115d5053fc25a74e5587f049c4f25 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Accel_ADXL373.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Accel_ADXL373.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Accel_ADXL373.c  -o ${OBJECTDIR}/_ext/1472/Accel_ADXL373.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Accel_ADXL373.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/CAN.o: ../CAN.c  .generated_files/flags/default/393700d00d5236d49c3dfc347ae51ec2211034aa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CAN.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CAN.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../CAN.c  -o ${OBJECTDIR}/_ext/1472/CAN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/CAN.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/CRC.o: ../CRC.c  .generated_files/flags/default/3cd741d3dbbfae26f36a9af007095ca9e67a095a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CRC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CRC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../CRC.c  -o ${OBJECTDIR}/_ext/1472/CRC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/CRC.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/DMA.o: ../DMA.c  .generated_files/flags/default/1cb5c195f1a9cf2b90fe914486f77590b3ac1baf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/DMA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/DMA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../DMA.c  -o ${OBJECTDIR}/_ext/1472/DMA.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/DMA.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Init.o: ../Init.c  .generated_files/flags/default/37413e880e483526b4928bae341f63503ebfc0f3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Init.c  -o ${OBJECTDIR}/_ext/1472/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Init.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o: ../MAG_MMC5983MA.c  .generated_files/flags/default/cc8acc47b490e06f7745221c22118113ce20351b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MAG_MMC5983MA.c  -o ${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o: ../MEM_MT25QL01.c  .generated_files/flags/default/baa7040dacc8ef1bc9124b3b4a82c9d4e6e61e5d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MEM_MT25QL01.c  -o ${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/SPI.o: ../SPI.c  .generated_files/flags/default/6765f367ca6c28b00c1b62186f785e68d931b85b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SPI.c  -o ${OBJECTDIR}/_ext/1472/SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/SPI.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Uart.o: ../Uart.c  .generated_files/flags/default/88b28cb6e170fa999b0e4d15b56ae9222507bf28 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Uart.c  -o ${OBJECTDIR}/_ext/1472/Uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Uart.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/default/efa8fcfcecb08ac11f84545ab53694704b14e453 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/MUX1_ADG732.o: ../MUX1_ADG732.c  .generated_files/flags/default/9f79cee7a89153f69f3c8ff6caf84b0c7cee1ac3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MUX1_ADG732.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MUX1_ADG732.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MUX1_ADG732.c  -o ${OBJECTDIR}/_ext/1472/MUX1_ADG732.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/MUX1_ADG732.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/ADC_ADS868x.o: ../ADC_ADS868x.c  .generated_files/flags/default/dfb806b46b95aedcf7467172ac57b3bb0c64259a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC_ADS868x.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC_ADS868x.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ADC_ADS868x.c  -o ${OBJECTDIR}/_ext/1472/ADC_ADS868x.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ADC_ADS868x.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/ADC_ADS863x.o: ../ADC_ADS863x.c  .generated_files/flags/default/cf782a632043407d68e171df5be3561f9b20b7eb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC_ADS863x.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC_ADS863x.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ADC_ADS863x.c  -o ${OBJECTDIR}/_ext/1472/ADC_ADS863x.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ADC_ADS863x.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1472/Accel_ADXL355.o: ../Accel_ADXL355.c  .generated_files/flags/default/c69d47f863a38135c6ee23355b9f766b638a6789 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Accel_ADXL355.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Accel_ADXL355.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Accel_ADXL355.c  -o ${OBJECTDIR}/_ext/1472/Accel_ADXL355.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Accel_ADXL355.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Accel_ADXL373.o: ../Accel_ADXL373.c  .generated_files/flags/default/da05326bc45433a6b7ae3611dea2589d75c4911a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Accel_ADXL373.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Accel_ADXL373.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Accel_ADXL373.c  -o ${OBJECTDIR}/_ext/1472/Accel_ADXL373.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Accel_ADXL373.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/CAN.o: ../CAN.c  .generated_files/flags/default/c624ae5f3e8fdd4fe9189a505d8df9afa1724ac2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CAN.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CAN.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../CAN.c  -o ${OBJECTDIR}/_ext/1472/CAN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/CAN.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/CRC.o: ../CRC.c  .generated_files/flags/default/dc99c958db871a9a30f42f14114e68a96b0e6630 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CRC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CRC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../CRC.c  -o ${OBJECTDIR}/_ext/1472/CRC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/CRC.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/DMA.o: ../DMA.c  .generated_files/flags/default/de52c6dd63c26b69f623fab6720380c95086a870 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/DMA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/DMA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../DMA.c  -o ${OBJECTDIR}/_ext/1472/DMA.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/DMA.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Init.o: ../Init.c  .generated_files/flags/default/e2e79adb9af45f49f714528e97b0e970f1589ade .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Init.c  -o ${OBJECTDIR}/_ext/1472/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Init.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o: ../MAG_MMC5983MA.c  .generated_files/flags/default/836c6a49d065dfdf05eeb507920559ed92976b57 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MAG_MMC5983MA.c  -o ${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/MAG_MMC5983MA.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o: ../MEM_MT25QL01.c  .generated_files/flags/default/e221994d1323d443c86f2a5e660d0533bd95f552 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MEM_MT25QL01.c  -o ${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/MEM_MT25QL01.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/SPI.o: ../SPI.c  .generated_files/flags/default/ca635da3fef0af2e5fe97b61ee0624acfba8b15e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SPI.c  -o ${OBJECTDIR}/_ext/1472/SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/SPI.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Uart.o: ../Uart.c  .generated_files/flags/default/58b3fb50852d27d447a346da1ee2f8f61061bcb4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Uart.c  -o ${OBJECTDIR}/_ext/1472/Uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Uart.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/default/cf5ff3f5811132021f89eb08e2c8fa307dcbb75f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/MUX1_ADG732.o: ../MUX1_ADG732.c  .generated_files/flags/default/e5d8663e115e0a69d4d6d59e934b38ccff73714c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MUX1_ADG732.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MUX1_ADG732.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MUX1_ADG732.c  -o ${OBJECTDIR}/_ext/1472/MUX1_ADG732.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/MUX1_ADG732.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/ADC_ADS868x.o: ../ADC_ADS868x.c  .generated_files/flags/default/bb6bb660f251cbfb4f4ecb8260715504f17382aa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC_ADS868x.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC_ADS868x.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ADC_ADS868x.c  -o ${OBJECTDIR}/_ext/1472/ADC_ADS868x.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ADC_ADS868x.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/ADC_ADS863x.o: ../ADC_ADS863x.c  .generated_files/flags/default/6f6ea585ac83a76909c45b1f567dc9b94ccad601 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC_ADS863x.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC_ADS863x.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ADC_ADS863x.c  -o ${OBJECTDIR}/_ext/1472/ADC_ADS863x.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ADC_ADS863x.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/SAST_TB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/SAST_TB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/SAST_TB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/SAST_TB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/SAST_TB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
