# README

BT2. Viết một chương trình có só lượng command-line arguments là 3, có dạng như sau:
$ ./example_program filename num-bytes [r/w] "Hello"
Trong đó:
	1. example_grogram: Tên file thực thi
	2. filename: Tên file
	3. num-bytes: Số byte muốn read/write
	4. [r/w]: r -> Thực hiện đọc từ  filename và in ra màn hình
		    w -> Thực hiện ghi vào filename
	5. "Hello": Nội dung bất kì muốn read/write vào filename


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

sau khi chạy sẽ đọc 11 byte từ file test.txt tương ứng với chuỗi "Hello World" 

### làm sạch mã nguồn
```bash
make clean
```