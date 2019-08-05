#!/usr/bin/env python3
# -*- coding: utf-8 -*-
__author__ = "Diego Dorta"
__copyright__ = "Copyright (C) 2019 NXP Semiconductors"
__license__ = "MIT"
import shutil
import subprocess as s
import csv, sys, os

class armNNClassifier(object):
    def __init__(self, **kwargs):
        self.__dict__.update(kwargs)
        self.str = " "
        self.strcmp = " "
        self.parsed = " "
        
    def labeler(self, data):
        with open(self.labelsPath) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=':')
            if (str(data) == 'error'):
                sys.stderr.write("error loading image\n")
                sys.exit(0)
            for row in csv_reader:
                if (str(data) == row[0]): self.str = row[1]

    def execArmnnParser(self):
        p = s.Popen(self.parserScript, stdout=s.PIPE)
        self.parsed = str(p.communicate()[0], encoding="utf-8").rstrip("\n")

    def executeArmnnTfInception(self):
        s.call(self.armnnCommandLine, shell=True)

    def run(self):
        if (len(sys.argv) < 2):
            sys.stderr.write("missing image file\n")
            sys.exit(0)
        dirs = os.listdir(self.dataPath)        
        if (sys.argv[1].startswith('data/')):
            self.strcmp = sys.argv[1][5:]        
        try:        
            for img in dirs:
                if (self.strcmp == img):                
                    shutil.copy2(self.dataPath + "/" + self.strcmp,
                                 self.dataPath + "/" + self.uglyHack)
        except:
            sys.stderr.write("Image not found\n")
            sys.exit(0)        
        finally:
            self.runTfInception()
            
    def runTfInception(self):
        self.executeArmnnTfInception()
        self.execArmnnParser()
        self.labeler(self.parsed)
        print(self.str)
        self.clear()
        sys.exit(0) 
        
    def clear(self): 
        os.remove(self.dataPath + "/" + self.uglyHack)

if __name__ == "__main__":
    dict = {"armnnCommandLine" : "TfInceptionV3-Armnn --data-dir=data --model-dir=models > /home/root/ArmnnTests/log.txt",
            "parserScript"     : "./parser.sh",
            "dataPath"         : "/home/root/ArmnnTests/data",
            "dataPrefix"       : "data/",
            "uglyHack"         : "Dog.jpg",
            "labelsPath"       : "labels.csv"
    }
    a = armNNClassifier(**dict)
    a.run()
