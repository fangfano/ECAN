export GNURISCV_TOOLCHAIN_PATH=/home/robot/riscv-gnu-toolchain
export HPM_SDK_TOOLCHAIN_VARIANT=

cd /home/robot/桌面/ECAN/kh-ethercat-canfdx4-op/Firmware/hpm_ethercat_sdk

# 创建构建目录
cd build

# 配置项目（默认构建类型为 flash_xip）
cmake .. -DBOARD=hpm5e00evk -DCMAKE_BUILD_TYPE=Debug

# 编译
make -j$(nproc)




# 从站程序烧写
cd /home/robot/桌面/ECAN/HPMicro_Manufacturing_Tool_v0.6.0
sudo ./hpm_manufacturing_gui



# 编译主站
export PATH=/home/robot/Fano/Project/Lubancat/LubanCat_Gen_full_SDK_ZC/prebuilts/gcc/linux-x86/aarch64/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin:$PATH
cd /home/robot/Fano/Project/Lubancat/LubanCat_Gen_full_SDK_ZC/external/ethercat_igh/demo/canfd
make clean && make
file ethercat

chmod +x ./ethercat
sudo ./ethercat



# ethercat 指令
sudo ethercat slave -v
sudo ethercat master
sudo ethercat pdos



# ZLG CAN 分析仪
sudo ifconfig can0 down
sudo ifconfig can1 down
sudo ifconfig lin0 down
sudo ifconfig lin1 down

# 启动can分析议
cd /home/robot/桌面/ECAN/zlgcanfd驱动/usbcanfd200_400u_2.10
sudo modprobe can-dev
sudo insmod usbcanfd.ko

## 设置通道参数
sudo ip link set can0 type can fd on bitrate 1000000 dbitrate 5000000 sample-point 0.8 dsample-point 0.8
sudo ip link set can1 type can fd on bitrate 1000000 dbitrate 5000000 sample-point 0.8 dsample-point 0.8
sudo ip link set lin0 up type can fd on bitrate 1000000 dbitrate 5000000
sudo ip link set lin1 up type can fd on bitrate 1000000 dbitrate 5000000

## 启动通道
sudo ifconfig can0 up
sudo ifconfig can1 up
sudo ifconfig lin0 up
sudo ifconfig lin1 up

candump -t a any


