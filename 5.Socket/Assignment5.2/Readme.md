# README

## Bài tập 5.2: Socket Ipv4 Datagram Socket
Viết chương trình dùng socket Ipv4 Datagram Socket để gửi nhận một chuỗi dữ liệu đơn giản

=> sau khi make thì chạy với 2 role khác nhau là server và client ở 2 terminal khác nhau. 
bên Server sẽ lắng nghe kết nối từ client, sau khi kết nối thành công thì server sẽ gửi một chuỗi dữ liệu cho client. 
bên Client sau khi kết nối thành công sẽ gửi chuỗi dữ liệu đến server. khi nhận được chuỗi dữ liệu từ server thì in ra.

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