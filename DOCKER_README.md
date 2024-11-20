docker build -t mpi-container .

sudo docker run -it -v /home/nsorokin/mine/hpc:/workspace mpi-container