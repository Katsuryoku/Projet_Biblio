QT += core gui opengl widgets
# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
unix {
        LIBS     += -lGL -lGLU
}
CONFIG	 += c++14
# nom de l'exe genere
TARGET 	  = Tetrix
HEADERS       = tetrixboard.h \
                tetrixpiece.h \
                tetrixwindow.h \
                camerawidget.h \
    			fistdetection.h \
    			glwidget.h
SOURCES       = main.cpp \
                tetrixboard.cpp \
                tetrixpiece.cpp \
                tetrixwindow.cpp \
                camerawidget.cpp \
    			fistdetection.cpp \
    			glwidget.cpp


INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core401 \
    -lopencv_highgui401 \
    -lopencv_imgproc401 \
    -lopencv_features2d401 \
    -lopencv_calib3d401 \
    -lopencv_objdetect401\
    -lopencv_videoio401.dll
