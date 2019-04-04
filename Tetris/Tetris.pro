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


INCLUDEPATH +=$$(OPENCV_DIR)file:///D:/Program_Files/opencv/build

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_features2d2413 \
    -lopencv_calib3d2413 \
    -lopencv_objdetect2413\
#    -lopencv_opencv2413.dll
