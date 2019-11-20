#!/usr/bin/env python3
# -*- coding: utf-8 -*-
__author__ = "Diego Dorta, Marco Franchi"
__copyright__ = "Copyright 2019 NXP Semiconductors"
__license__ = "BSD-3-Clause"
from socket import gethostbyaddr, gethostname
import cv2 as opencv
from multiprocessing import Process, Queue

class singleShotDetector(object):
    def __init__(self, l, **kwargs):
        self.__dict__.update(kwargs)
        self.nn = opencv.dnn.readNetFromCaffe(self.modelSSDProtoPath,
                                              self.modelSSDCaffePath)
        self.video = opencv.VideoCapture(self.mode)
        self.labels = l
        self.coordinates = []
        self.files = []
        self.det = None
        self.inQueue = Queue(maxsize=1)
        self.outQueue = Queue(maxsize=1)
        self.ir = 0
        self.ic = 0
        self.hf = 0
        self.wf = 0
        self.blob = 0

    def caffeInference(self, nn, inQueue, outQueue):
        while True:
            if (not inQueue.empty()):
                self.ir = inQueue.get()
                self.ir = opencv.resize(self.ir, (self.height, self.width))
                self.blob = opencv.dnn.blobFromImage(self.ir, self.scaleFactor,
                            (self.height, self.width), self.normalize)
                nn.setInput(self.blob)
                det = nn.forward()
                outQueue.put(det)

    def run(self):
        inf = Process(target=self.caffeInference, args=(self.nn, self.inQueue,
                                                        self.outQueue))
        inf.daemon = True
        inf.start()

        while True:
            ret, frame = self.video.read()
            frame = opencv.resize(frame, (640, 480))
            (self.hf, self.wf) = frame.shape[:2]

            if (self.inQueue.empty()):
                self.inQueue.put(frame)
            if not (self.outQueue.empty()):
                self.det = self.outQueue.get()

            if (self.det is not None):
                for i in range(self.det.shape[2]):
                    confidence = self.det[0, 0, i, 2]
                    if (confidence < self.threshold):
                        continue;

                    index = int(self.det[0, 0, i, 1])
                    shapes = [self.wf, self.hf, self.wf, self.hf]
                    sbox = self.det[0, 0, i, 3:7] * shapes
                    (x1, y1, x2, y2) = sbox.astype("int")

                    l = labels[index] + " : {:.2f}%".format(confidence * 100)
                    opencv.rectangle(frame, (x1, y1), (x2, y2),
                        (255, 255, 255))
                    opencv.putText(frame, l, (x1, y1),
                        opencv.FONT_HERSHEY_DUPLEX, 0.5, (255, 255, 255))

            opencv.namedWindow("appFrame")
            opencv.imshow("appFrame", frame)
            if (opencv.waitKey(1) >= 0):
                break
        opencv.destroyAllWindows()
        self.video.release()

def getHostName():
    l = [ "imx8qxpmek", "imx8qmmek",
          "imx8mqevk", "imx8mmevk" ]
    return True if gethostname() in l else False

def gStreamerSettings(wh, hh):
    dev = "/dev/video0"
    fr = 30
    lq = "leaky=downstream max-size-buffers=1"
    se = "sync=false emit-signals=true drop=true max-buffers=1"
    return (("""v4l2src device={} ! video/x-raw,width={},height={},framerate={}/1
                ! queue {} ! videoconvert ! appsink {}""").format(dev, wh, hh, fr, lq, se))

if __name__ == "__main__":
    labels = {  0:  'Background',
                1:  'Aeroplane',
                2:  'Bicycle',
                3:  'Bird',
                4:  'Boat',
                5:  'Bottle',
                6:  'Bus',
                7:  'Car',
                8:  'Cat',
                9:  'Chair',
                10: 'Cow',
                11: 'Diningtable',
                12: 'Dog',
                13: 'Horse',
                14: 'Motorbike',
                15: 'Person',
                16: 'Pottedplant',
                17: 'Sheep',
                18: 'Sofa',
                19: 'Train',
                20: 'TVMonitor'
    }
    dict = {    "modelSSDProtoPath" : "model/MobileNetSSD_deploy.prototxt",
                "modelSSDCaffePath" : "model/MobileNetSSD_deploy.caffemodel",
                "mediaPath"         : "media/",
                "mode"              : gStreamerSettings(640, 480)
                                      if getHostName() else 0,
                "width"             : 300,
                "height"            : 300,
                "normalize"         : 127.5,
                "threshold"         : 0.2,
                "scaleFactor"       : 0.009718,
                "ext"               : (".jpeg", ".jpg", ".png")
    }
    app = singleShotDetector(labels, **dict)
    app.run()
