# README


## Bài tập 4.5: Đọc và ghi đồng bộ với nhiều thread
Viết một chương trình mô phỏng tình huống có nhiều thread đọc và ghi dữ liệu:
Tạo một biến data chứa một số nguyên.
Tạo 5 threads đọc và 2 threads ghi:
Các thread đọc sẽ chỉ đọc data mà không thay đổi.
Các thread ghi sẽ tăng giá trị của data lên 1.
Sử dụng read-write lock để đảm bảo nhiều threads có thể đọc cùng lúc, nhưng chỉ một thread được ghi tại bất kỳ thời điểm nào.
In ra giá trị của data sau khi tất cả các threads hoàn thành.
Gợi ý: Sử dụng pthread_rwlock_rdlock và pthread_rwlock_wrlock cho đọc-ghi đồng bộ.

kết quả như hình bên dưới

![Thread with share memorry](https://github.com/user-attachments/assets/e9d229ea-f08e-4995-9d22-1149c5c87b3d)


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
