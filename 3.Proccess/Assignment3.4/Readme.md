# README

BT4. Ghi nhận Trạng thái Process
Mô tả: Viết một chương trình tạo một tiến trình con, sau đó tiến trình cha sử dụng wait() để chờ tiến trình con kết thúc và ghi nhận trạng thái kết thúc của nó.
Yêu cầu:
Trong tiến trình con, chọn trạng thái kết thúc bằng cách gọi exit() với các giá trị khác nhau.
Sử dụng WIFEXITED() và WEXITSTATUS() để xác nhận và ghi nhận mã thoát của tiến trình con.
=> sau khi chạy truyền vào exit với các giá trị khác nhau, tiến trình cha sẽ nhận được các status tương ứng

## Commands

### Build ra file thực thi
```bash
make
```

### run file thực thi.
```bash
./test
```

### làm sạch mã nguồn
```bash
make clean
```