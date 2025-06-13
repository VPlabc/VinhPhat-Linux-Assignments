# Tạo character device để ghi vào file nội dung "on"/"off" và in message ra log kernel

## 1. Tạo character device trong kernel module

- Đăng ký character device với `register_chrdev`.
- Cài đặt các hàm file_operations: `open`, `write`, `release`.

## 2. Xử lý ghi dữ liệu ("on"/"off") và in ra log kernel

- Trong hàm `write`, kiểm tra dữ liệu ghi vào:
    - Nếu là "on": ghi log kernel `pr_info("turn led on\n");`
    - Nếu là "off": ghi log kernel `pr_info("turn led on\n");`
    - Nếu khác: ghi log kernel `pr_info("Unknown command\n");`


tham khảo Bootlin (V5.4.0)

# Xác định và cấu hình GPIO cho Raspberry Pi Zero

## 1. Xác định địa chỉ của module GPIO

- **Peripherals Address:** 0x20000000 đến 0x20FFFFFF
- **Bus Address:** 0x7E000000 đến 0x7EFFFFFF
- **GPIO Address:** 0x7E200000 hoặc 0x20200000 (tùy theo mapping)

## 2. Cấu hình chức năng cho GPIO27 (Function Select/Muxing Pin)

- **Thanh ghi GPFSEL2:**  
    - Địa chỉ: 0x7E200008 hoặc 0x20200008
    - Các bit điều khiển GPIO27: FSEL27 (bit 23-21)
        - `000`: GPIO27 là input
        - `001`: GPIO27 là output
        - `010` - `111`: GPIO27 là các chức năng alternate function

**Để cấu hình GPIO27 làm output:**  
Ghi giá trị `001` vào các bit 23-21 của thanh ghi GPFSEL2.

## 3. Điều khiển mức điện áp của GPIO27

- **GPSET0:**  
    - Địa chỉ: 0x7E20001C hoặc 0x2020001C
    - Bit 27 (SET27):  
        - `0`: Không tác động  
        - `1`: Đưa GPIO27 lên mức cao (logic 1)

- **GPCLR0:**  
    - Địa chỉ: 0x7E200028 hoặc 0x20200028
    - Bit 27 (CLR27):  
        - `0`: Không tác động  
        - `1`: Kéo GPIO27 xuống mức thấp (logic 0)

**Ví dụ:**  
- Để đưa GPIO27 lên mức cao: ghi giá trị `0x08000000` (bit 27 = 1) vào GPSET0.
- Để kéo GPIO27 xuống mức thấp: ghi giá trị `0x08000000` vào GPCLR0.

---

## Tóm tắt quy trình

1. **Cấu hình GPIO27 làm output:**  
     - Ghi `001` vào bit 23-21 của GPFSEL2.

2. **Điều khiển mức điện áp:**  
     - Ghi `1` vào bit 27 của GPSET0 để lên mức cao.
     - Ghi `1` vào bit 27 của GPCLR0 để xuống mức thấp.

> Lưu ý: Địa chỉ thanh ghi trong tài liệu (BCM2708 manual reference) của Rsp Pi Zero W. đối với các board khác nhau sẽ có tài liệu khác.

