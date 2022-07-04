# tinyDarknet
 
This is one version of [darknet](https://github.com/pjreddie/darknet) ML framework being squeezed for running on tiny boards with MCUs. Only FC layers are kept as the weight-enabled layer. Still under development but can be tested with the following instruction.

 
First, clone and compile with
```
git clone https://github.com/mofanv/tinyDarknet.git
cd tinyDarknet
make
```

After successfully compiling, run the bellow command to do a simple training on dummy inputs:
```
./tinydarknet classifier train cfg/test_fc.cfg
```

Then, run the bellow command to do a simple prediction on one input
```
./tinydarknet classifier predict cfg/test_fc.cfg cfg/test_fc.weights
```
Note that `cfg/test_fc.cfg` is the configure of the model, and `cfg/test_fc.weights` is the pre-trained model weights. Dummy inputs are in `src/input_image.h`, with some input cfg in `src/input_datacfg.h`.