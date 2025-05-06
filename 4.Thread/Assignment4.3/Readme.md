# README

## Bài tập 4.3: Producer-Consumer Problem
Viết một chương trình có hai threads: producer và consumer như sau:
Producer: Tạo ra một số ngẫu nhiên từ 1 đến 10 và lưu vào một biến toàn cục data.
Consumer: Đợi producer cung cấp dữ liệu, sau đó đọc và in ra dữ liệu đó.
Sử dụng pthread_cond_wait và pthread_cond_signal để đồng bộ hóa giữa producer và consumer, đảm bảo rằng consumer chỉ đọc dữ liệu khi producer đã cung cấp xong.
Lặp lại quá trình trên 10 lần và in ra tất cả các giá trị do consumer đọc được.
Gợi ý: Sử dụng pthread_cond_wait để cho consumer đợi cho đến khi có tín hiệu từ producer rằng dữ liệu đã sẵn sàng.
Sử dụng pthread_cond_signal để thông báo cho consumer rằng dữ liệu đã sẵn sàng để đọc. Sử dụng mutex để bảo vệ biến toàn cục data khỏi truy cập đồng thời từ cả hai threads.

=> Chương trình này sử dụng mutex và condition variable để đồng bộ hóa giữa hai thread producer và consumer. Producer tạo ra một số ngẫu nhiên từ 1 đến 10 và lưu vào biến toàn cục data, sau đó thông báo cho consumer rằng dữ liệu đã sẵn sàng. Consumer đợi cho đến khi có tín hiệu từ producer và sau đó đọc và in ra dữ liệu đó. Quá trình này lặp lại 10 lần.
kết quả như hình bên dưới

![Thread with condition var](https://github.com/user-attachments/assets/bb921121-bac2-4f01-89f7-5155de476e09)

## Mô tả mã nguồn
## Commands

### Build ra file thực thi
```bash
make
```
 
### run file thực thi ví dụ chạy và in ra PID của tiến trình cha và tiến trình con
```bash
./test
```

### làm sạch mã nguồn
```bash
make clean
```
