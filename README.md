# subnetter
A tool that partitions a network into subnets of the desired size.

## Building
Execute the `build.sh` script. 


*Why don't you use CMake, or Make, or QMake or any other build tool?*

Simply put, I do not know (yet!) how to use any of them in a more or less decent manner.
Sooner or later I'll change it. Sorry in advance!

## Usage
Execute the executable that will be created in the `target/` directory.
First, the program will ask the user to insert the names of the subnets along with the expected number of hosts for each subnet.

When you're finished, type `\` to exit the subnet insertion mode. Then, type in the starting address to partition in the form `x.y.z.t/n`. By pressing enter, the program will output every subnet with
the relative IP address and the broadcast IP address.