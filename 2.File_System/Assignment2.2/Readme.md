# README

## Commands

### Build ra file thực thi
```bash
make
```
định dạng arg
     filename num-bytes [r/w] "content"
     
### run file thực thi ví dụ ghi vào file test.txt
```bash
./ test test.txt 11 w "hello World"
```

sau khi chạy sẽ ghi chuỗi "Hello World" vào file test.txt

### run file thực thi ví dụ đọc file test.txt
```bash
./ test test.txt 11 r ""
```

### làm sạch mã nguồn
```bash
make clean
```