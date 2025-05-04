# README

BT1. Viết một chương trình mở một file bất kì và sử dụng cờ O_APPEND, sau đó thực hiện seek về đầu file rồi ghi một vài dữ  liệu vào file đó. Dữ liệu sẽ xuất hiện ở vị trí nào của file và tại sao lại như vậy?

## Commands

### Build ra file thực thi
```bash
make
```

### run file thực thi
```bash
./ test
```
sau khi lseek về đầu file và bắt đầu ghi sẽ gặp lỗi 
```bash
    Error writing to file: Bad file descriptor 
```
do cờ O_APPEND chỉ ghi và cuối chuỗi của file tránh tình trạng ghi đè
dữ liệu hiện có 
khi sử dụng cờ O_APPEND kèm với O_WRONLY và không cần sử dụng lseek

sau khi chạy sẽ ghi chuỗi "Hello, World!\n" vào file test.txt

### làm sạch mã nguồn
```bash
make clean
```