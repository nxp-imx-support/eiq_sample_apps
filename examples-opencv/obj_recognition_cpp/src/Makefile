CXX?=g++
PROG=ObjectRecognitionCPP

SOURCES=main.cpp displayvideo.cpp inference.cpp

LIBS= -lopencv_dnn -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching \
      -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_videoio -lopencv_imgcodecs \
			-lopencv_features2d -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core \
			-ldl -lm -lpthread -lrt

all: $(PROG)

$(PROG): $(SOURCES)
	$(CXX) -o $@ $(INC) $(DEP_LIBS) $^ $(LIBS)

clean:
	rm -f $(PROG)
