# README

BT2. Sử dụng exec và Biến Môi Trường
Mô tả: Viết một chương trình trong đó tiến trình con sẽ thay thế chương trình đang chạy bằng một chương trình khác, ví dụ ls hoặc date, sử dụng hàm execlp() hoặc execvp().
Yêu cầu:
Truyền các biến môi trường vào chương trình và thực hiện các công việc khác nhau (ví dụ biến môi trường được truyền vào là 1 thì thực hiện lệnh ls, nếu là 2 thì thực hiện lệnh date).
Giải thích điều gì xảy ra với tiến trình ban đầu sau khi exec được gọi.
=> tiến trình ban đầu chạy xong. sau khi gọi exec thì in các thông tin tương ứng với giá trị truyền vào của biến môi trường và đưa ra thông tin tương ứng và kết thúc

## Commands

### Build ra file thực thi
```bash
make
```

### truyền giá trị vào biến môi trường ở đây là biến ACTION với giá trị 1/2
```bash
export ACTION=1
```

### run file thực thi. nếu truyền vào 1 trả về thông tin sau lệnh ls, truyền vào 2 trả về thông tin sau lệnh date
```bash
./test
```

### làm sạch mã nguồn
```bash
make clean
```