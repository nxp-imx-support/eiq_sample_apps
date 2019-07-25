CXX?=g++
PROG=FaceRecognition

SOURCES=face_recognition.cpp face_detect_helpers.cpp

LIBS= -ltensorflow-lite -lpthread -ldl -g \
      -lopencv_objdetect -lopencv_highgui -lopencv_imgproc -lopencv_core -lopencv_videoio -lopencv_imgcodecs
INC=-I /usr/include/tensorflow/contrib/lite/tools/make/downloads/flatbuffers/include/ 

all: $(PROG)
	
$(PROG): $(SOURCES)
	$(CXX) -o $@ $(INC) $(DEP_LIBS) $^ $(LIBS)

clean:
	rm -f $(PROG)
