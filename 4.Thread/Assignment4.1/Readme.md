# README

BT1. Tạo và Chạy Threads Cơ Bản
Viết một chương trình sử dụng thư viện pthread.h để thực hiện các thao tác sau:
Tạo hai threads. Mỗi thread sẽ in ra một chuỗi thông báo kèm theo ID của thread (ví dụ: "Thread 1: Hello from thread").
Sử dụng hàm pthread_join để đợi cả hai threads hoàn thành trước khi chương trình kết thúc.
Sử dụng pthread_create và pthread_join như thế nào? Khi nào thread kết thúc?
Gợi ý: Sử dụng hàm pthread_create để tạo threads và pthread_join để chờ các threads hoàn thành.

=> Khi một thread hoàn thành công việc của nó, nó sẽ tự động kết thúc. Tuy nhiên, nếu không sử dụng pthread_join, chương trình chính có thể kết thúc trước khi thread hoàn thành, dẫn đến việc không in ra thông báo của thread.
như hình bên dưới. 
lần make và chạy đầu tiên với trường hợp không có pthread_join, chương trình chính kết thúc trước khi thread hoàn thành, dẫn đến việc không in ra thông báo của thread. 
lần make và chạy thứ hai với trường hợp có pthread_join, chương trình chính đợi cho đến khi thread hoàn thành trước khi kết thúc. kết quả là thông báo của thread được in ra đầy đủ.

![Thread with pthread_join](https://github.com/user-attachments/assets/15f537f4-48ff-4611-9580-65017781c2d3)

## Mô tả mã nguồn
## Commands

### Build ra file thực thi
```bash
make
```
 
### run file thực thi
```bash
./test
```

### làm sạch mã nguồn
```bash
make clean
```
