#####################################
C11_Config()
############����OPENCV#########################################################
ConfigOpenCv()
###############################################################################

###############################################################################
SET(BASE_SRCS
			ImageDataBasic.cpp
			ImageSaveProc.cpp
	)  
###############################################################################
SET(BASE_LINK_LIB 
	         MY_SDK_LIB
	)
ADD_LIBRARY(SGVBaseCode  STATIC     ${BASE_SRCS}  )
TARGET_LINK_LIBRARIES(SGVBaseCode 	${BASE_LINK_LIB})
###############################################################################