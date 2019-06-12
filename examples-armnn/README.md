Dependencies
============

* i.MX 8 board running an image with the eIQ release.
* MIPI Camera

On i.MX Board
=============

Boot the board with the correct .dtb file for camera operation.

After booting, create the needed folders:

# mkdir -p /opt/armnn/model
# mkdir -p /opt/armnn/data
# chmod 777 /opt/armnn

On Host
=======

Follow the steps from eIQ User Guide to generate the `InceptionV3` model.

Deploy the needed files to the board:

$ scp -r 2-example/* media/ root@${IMX_INET_ADDR}:/opt/armnn
$ scp -r models/* root@${IMX_INET_ADDR}:/opt/armnn/models

Getting the Flash Cards
=======================

This demo supports up to 1000 different objects. Just download some pictures at
your choice and include a thick black border around the edges. You can print
the flash cards or point the camera to the PC monitor as well.

Run
===

1) Run the demo:

/opt/armnn# python3 2-example.py

2) After the demo is running, show the flash cards to the camera and wait for
the detection message: "Image captured, wait". The flash cards should not be
twisted or curved on this step.

3) After a few seconds, the demo prints the detected object on the terminal.

NOTE: This can return "False" if the image was not correctly captured. In this
case, try showing the flash cards again.
