QT += widgets

HEADERS       = tetrixboard.h \
                tetrixpiece.h \
                tetrixwindow.h \
                camerawidget.h \
    			fistdetection.h
SOURCES       = main.cpp \
                tetrixboard.cpp \
                tetrixpiece.cpp \
                tetrixwindow.cpp \
                camerawidget.cpp \
    			fistdetection.cpp


INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core401 \
    -lopencv_highgui401 \
    -lopencv_imgproc401 \
    -lopencv_features2d401 \
    -lopencv_calib3d401 \
    -lopencv_objdetect401\
    -lopencv_videoio401.dll
