## MFpre

Welcome to MFpre. This is a PreProcessor code developed to perform domain decomposition for the parallel meshfree Compressible flow solver. The code is developed using the routines available in the open-source graph partitioning tool [METIS](http://glaros.dtc.umn.edu/gkhome/metis/metis/overview). This is a private repository, contact the owner if your'e interested in contributing to the code.

### Running the program

1. Download METIS using [spack](https://spack.io/) or [here](http://glaros.dtc.umn.edu/gkhome/metis/metis/download)
2. Export the path of the METIS directory to `$METIS_DIR`(add to bash file)
3. To run the code type `make`
4. The input grid file must be named `point-input`
4. The format for execution is given by, `./graphpart numberofpartitions(required) -inputformat(required) -ifcudaoutputrequired(optional)`
5. For example, `./graphpart 8 -legacy` generates 8 partitions for legacy input format
5. This will produce the partitioned files with names partGrid* which can be used as an input for either mpi or cuda based meshfree solver
6. To visualize the partitions type `make plot`

### Execution options

| input format | loads |
| ------ | ------ |
| --legacy | legacy format from structured grids |
| --quadtree | quadtree format |
| --restart | to partition restart files with primitive values |

| output format | generates |
| ------ | ------ |
| --cuda | default = no, generates cuda datastructure for either quadtree or legacy input format |

### Input formats

#### Legacy format

| point index | X | Y | left index | right index | flag_1 | flag_2 | neighbours | connectivity
| ------ | ------ | ------ | ------ | ------ | ------ | ------| ------ | ------ | 

#### quadtree format

| point index | X | Y | left index | right index | flag_1 | flag_2 | neighbours | connectivity
| ------ | ------ | ------ | ------ | ------ | ------ | ------| ------ | ------ | 

#### Restart Format

| point index | X | Y | left index | right index | pressure | x velocity | y velocity | pressure | flag_1 | flag_2 | neighbours | connectivity
| ------ | ------ | ------ | ------ | ------ | ------ | ------| ------ | ------ | ------ | ------| ------ | ------ | 
