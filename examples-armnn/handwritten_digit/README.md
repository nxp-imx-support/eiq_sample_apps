Dependencies
============

* i.MX 8 board running an image with the eIQ release.

On i.MX Board
=============

After booting, create the needed folders:

```bash
# mkdir -p /opt/mnist
# chmod 777 /opt/mnist
```

On Host
=======

1) Get the models and dataset. The following command-lines create the
needed folder structure for the demos and retrieves the mnist dataset,
and the Caffe and TensorFlow models:

```bash
$ mkdir -p bin data model
$ wget -qN https://github.com/ARM-software/ML-examples/raw/master/armnn-mnist/data/t10k-images-idx3-ubyte -P data/
$ wget -qN https://github.com/ARM-software/ML-examples/raw/master/armnn-mnist/data/t10k-labels-idx1-ubyte -P data/
$ wget -qN https://github.com/ARM-software/ML-examples/raw/master/armnn-mnist/model/lenet_iter_9000.caffemodel -P model/
$ wget -qN https://github.com/ARM-software/ML-examples/raw/master/armnn-mnist/model/simple_mnist_tf.pb -P model/
$ wget -qN https://github.com/ARM-software/ML-examples/raw/master/armnn-mnist/model/simple_mnist_tf.prototxt -P model/
$ wget -qN https://github.com/ARM-software/Tool-Solutions/raw/master/ml-tool-examples/mnist-draw/model/optimized_mnist_tf.pb -P model/
```

2) With the eIQ toolchain installed on your machine, build the application code:

```bash
$ source /opt/fsl-imx-xwayland/<version>/environment-setup-aarch64-poky-linux
$ ${CXX} -Wall -Wextra -O3 -std=c++14 caffe_inference.cpp -o caffe_inference -larmnn -larmnnCaffeParser
$ ${CXX} -Wall -Wextra -O3 -std=c++14 tensorflow_inference.cpp -o tensorflow_inference -larmnn -larmnnTfParser
```

3) Deploy the built files to the board:

```bash
$ scp -r caffe_inference tensorflow_inference data/ model/ root@${IMX_INET_ADDR}:/opt/mnist
```

Run
===

1) For running these applications, please provide the wanted number of
predictions, which can vary from 0 to 9999 since the dataset has 10K images.

Using Caffe:

```bash
# ./caffe_inference 10
```

Using TensorFlow:

```bash
# ./tensorflow_inference 10
```

2) These tests run the inference on the input MNIST dataset images (Actual),
showing the inference results (Predict) and how long it took to complete the
prediction. 
