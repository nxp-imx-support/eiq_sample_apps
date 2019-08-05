Dependencies
============

* i.MX 8 board running an image with the eIQ release.
* MIPI Camera

On i.MX Board
=============

Boot the board with the correct .dtb file for camera operation.

After booting, create the needed folders:

```bash
# mkdir -p /opt/armnn/model
# mkdir -p /opt/armnn/data
# chmod 777 /opt/armnn
```

On Host
=======

Follow the steps from eIQ User Guide to prepare the `InceptionV3` model
for inference.

The file-based demo expects three types of animals: Cat, Dog and shark.
Download an image for each of these animals and rename as the following:

Cat.jpg
Dog.jpg
shark.jpg

Deploy the needed files to the board:

```bash
$ scp -r src/* root@${IMX_INET_ADDR}:/opt/armnn
$ scp -r Cat.jpg Dog.jpg shark.jpg root@${IMX_INET_ADDR}:/opt/armnn/data
$ scp -r models/* root@${IMX_INET_ADDR}:/opt/armnn/models
```

Getting the Flash Cards
=======================

This demo supports up to 1000 different objects. For the camera demo,
download some pictures at your choice and include a thick black border
around the edges. You can print the flash cards or point the camera to
the PC monitor as well.

Run
===

* File-based demo

1) Run the demo:

```bash
/opt/armnn# python3 file.py
```

2) After a few seconds, the demo prints the top 5 inference results for
the pictures and their confidence percentage.

* Camera demo

1) Run the demo:

```bash
/opt/armnn# python3 camera.py
```

2) After the demo is running, show the flash cards to the camera and wait for
the detection message: "Image captured, wait". The flash cards should not be
twisted or curved on this step.

3) After a few seconds, the demo prints the detected object on the terminal.

NOTE: This can return "False" if the image was not correctly captured. In this
case, try showing the flash cards again.
