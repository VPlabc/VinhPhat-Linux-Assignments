# build Yocto

## Build trên Ubuntu hoặc Debian
```bash
sudo apt-get update
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
     build-essential chrpath socat cpio python python3 python3-pip python3-pexpect \
     xz-utils debianutils iputils-ping libsdl1.2-dev xterm vim

```
## 📥 Tải mã nguồn của Yocto Project

</> Tạo và di chuyển vào thư mục ~/yocto:
```bash
mkdir ~/yocto
cd ~/yocto
```

</> Bắt đầu bằng cách tải mã nguồn của Yocto Project từ kho chính thức:

```bash
~/yocto$ git clone git://git.yoctoproject.org/poky
Cloning into 'poky'...
remote: Enumerating objects: 658036, done.
remote: Counting objects: 100% (1018/1018), done.
remote: Compressing objects: 100% (250/250), done.
Receiving objects:   9% (63464/658036), 31.86 MiB | 1.23 MiB/s  s
```

## Xây dựng image cho QEMU
### Chuyển sang branch phù hợp

Đảm bảo bạn đang ở trong thư mục mã nguồn poky và chọn branch phù hợp với yêu cầu:

```bash
cd ~/yocto/poky
git checkout dunfell
```
### Khởi tạo môi trường
Chạy script oe-init-build-env để thiết lập môi trường xây dựng trên máy chủ.
```bash
source oe-init-build-env
```

### Tùy chỉnh file cấu hình 

tại file local.conf

```bash
nano conf/local.conf
```

File local.conf trong Yocto Project là một tệp cấu hình cục bộ được tạo ra khi khởi tạo môi trường xây dựng bằng script oe-init-build-env. Tệp này nằm trong thư mục conf của thư mục build (poky/build/conf) và là nơi để thiết lập các cấu hình cho quá trình build image.

⚠️  Để tiết kiệm dung lượng ổ đĩa, thêm dòng sau để xóa các thư mục work sau khi build xong:

```bash
NHERIT += "rm_work"
```

Mặc định, máy đích (target machine) là qemux86, tạo ra một image có thể sử dụng trong QEMU và được nhắm đến kiến trúc Intel 32-bit. Sau này, bạn có thể thay đổi nhanh chóng máy đích thông qua biến MACHINE để build một image cho máy khác.

⚠️ Đặt trình quản lý gói sử dụng trong quá trình build (mặc định là RPM):
```bash
ACKAGE_CLASSES ?= "package_rpm"
```

### bblayers.conf
⚠️ File bblayers.conf quản lý danh sách các layers mà BitBake sẽ sử dụng. Ví dụ:

```bash
BBLAYERS ?= " \
  /home/aosp/yocto/poky/meta \
  /home/aosp/yocto/poky/meta-poky \
  /home/aosp/yocto/meta-openembedded/meta-oe \
  /home/aosp/yocto/meta-yocto-bsp \
"
```

### Tiến hành xây dựng image
⚠️  Mở file build/conf/local.conf và thay đổi biến để MACHINE xây dựng máy ảo QEMU cho kiến trúc x86-64:
```bash
MACHINE ?= "qemux86-64"
```

🚀 Xây dựng image hệ điều hành cho máy ảo QEMU, trong ví dụ này là core-image-minimal.

```bash
bitbake core-image-minimal
```
# 🕘
![BuildSuccess](https://github.com/user-attachments/assets/b2c2a6de-bd5a-46b7-acec-f5bc368ccc99)

# ✅ 
![RunOnQemux](https://github.com/user-attachments/assets/cc23f9f5-4c5b-44b4-a05b-46fd841f6c38)
