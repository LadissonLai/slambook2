# ceres
cd 3rdparty/ceres-solver && mkdir build
cd build && cmake .. && make -j20
sudo make install

# sophus
cd ../../Sophus && mkdir build
cd build && cmake .. && make -j20
sudo make install

# g2o
cd ../../../3rdparty/g2o && mkdir build
cd build && cmake .. && make -j20
sudo make install

# DBoW3
cd ../../../3rdparty/DBoW3 && mkdir build
cd build && cmake .. && make -j20
sudo make install

# Pangolin
cd ../../../3rdparty/Pangolin && mkdir build
cd build && cmake .. && make -j20
sudo make install

# delete build cache.
cd ../../../
sudo rm -rf 3rdparty/ceres-solver/build
sudo rm -rf 3rdparty/DBoW3/build
sudo rm -rf 3rdparty/g2o/build
sudo rm -rf 3rdparty/Pangolin/build
sudo rm -rf 3rdparty/Sophus/build

