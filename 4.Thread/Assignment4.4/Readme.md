# README

## Bài tập 4.4: Đếm số chẵn và số lẻ trong mảng
Viết một chương trình để thực hiện các bước sau:
Tạo một mảng ngẫu nhiên chứa 100 số nguyên từ 1 đến 100.
Tạo hai threads: một thread đếm số chẵn và một thread đếm số lẻ trong mảng.
Khi hai threads hoàn tất việc đếm, in ra tổng số số chẵn và tổng số số lẻ.
Sử dụng pthread_join để đảm bảo rằng chương trình chỉ kết thúc khi cả hai threads hoàn thành nhiệm vụ.
Gợi ý: Mỗi thread sẽ xử lý một phần công việc khác nhau, vì vậy không cần mutex trong bài này.

=> Chương trình này không ghi vào biến chung chi đọc nên không cần mutex. chương trình sẽ in ra tổng số số chẵn và tổng số số lẻ.
kết quả như hình bên dưới

![Thread without mutex](https://github.com/user-attachments/assets/a30eec07-5eb0-4392-9ba3-84d5ebe7a9f2)

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
