Dependencies
============

* i.MX 8 board running an image with the eIQ release.
* MIPI Camera (if camera input is wanted)
* Ethernet cable (for sending files)

On i.MX Board
=============

Boot the board with the correct .dtb file for camera operation and connect the
Ethernet cable.

After booting, create the needed folders:

# mkdir -p /opt/opencv/model
# mkdir -p /opt/opencv/media
# chmod 777 /opt/opencv

On Host
=======

1) Download the model:

$ mkdir -p model media
$ wget -qN https://github.com/diegohdorta/models/raw/master/caffe/MobileNetSSD_deploy.caffemodel -P model/
$ wget -qN https://github.com/diegohdorta/models/raw/master/caffe/MobileNetSSD_deploy.prototxt -P model/

2) Export the board's IP:

$ export IMX_INET_ADDR=<imx_ip>

3) Deploy the files to the board:

$ scp -r 1-example.py 2-example.py model/ media/ root@${IMX_INET_ADDR}:/opt/opencv

Run
===

1) For 1-example, put images inside media folder and run:

# ./1-example.py

2) For 2-example, make sure the MIPI camera is connected to the board using the
properly dtb file and run:

# ./2-example.py
