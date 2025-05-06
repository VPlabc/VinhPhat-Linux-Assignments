# README

## Bài tập 4.6: Tính tổng mảng lớn với nhiều threads
Viết một chương trình tính tổng một mảng lớn gồm 1 triệu số nguyên.
Chia mảng thành 4 phần bằng nhau.
Tạo 4 threads, mỗi thread tính tổng một phần của mảng.
Sử dụng một biến tổng toàn cục và mutex để tổng hợp kết quả từ tất cả các threads.
In ra kết quả tổng của mảng sau khi các threads hoàn thành.
Gợi ý: Sử dụng pthread_mutex_lock để bảo vệ biến tổng khi các threads cộng kết quả của chúng.

kết quả như hình bên dưới

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