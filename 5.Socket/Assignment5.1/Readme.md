# README

## Bài tập 5.1: Socket IPv4 Stream Socket
Viết chương trình dùng socket IPv4 Stream Socket để gửi nhận một chuỗi dữ liệu đơn giản

=> sau khi make thì chạy với 2 role khác nhau là server và client ở 2 terminal khác nhau. 
bên Server sẽ lắng nghe kết nối từ client, sau khi kết nối thành công thì server sẽ gửi một chuỗi dữ liệu cho client. 
bên Client sau khi kết nối thành công sẽ gửi chuỗi dữ liệu đến server. khi nhận được chuỗi dữ liệu từ server thì in ra.

![Socket 5 1](https://github.com/user-attachments/assets/ea6b42c3-1952-4a26-acd6-aabf91ba4d0d)

## Mô tả mã nguồn
## Commands

### Build ra file thực thi
```bash
make
```
 
### run file thực thi ví dụ chạy và với role server
```bash
./test 0
```

### run file thực thi ví dụ chạy và với role client
```bash
./test 1
```

### làm sạch mã nguồn
```bash
make clean
```
