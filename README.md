## RLibTest

[rlib](https://github.com/wxdwfc/rlib) is a header-only library for **easier** use of RDMA using C++. Basically it is a set of wrappers of the interfaces of `libibverbs`, 
yet it additionally handles many tedius things, such as establishing connections between RDMA QPs, and simplifies many configurations.

We make testing by using a modified version of [rlib](https://github.com/minghust/ford), which modifies: 1) Fix a bug in en/decoding the QP id. 2) Change the QP connections from the active mode to the passive mode in the server side.

### Compile the project
```sh
cd build
cmake ..
# build
make
# clean build
make clean
```
