# README

BT1: Tạo một static library (.a)
BT2: Tạo một shared library (.so)
Lưu ý: Sử dụng Makefile thực hiện tự động build tất cả các bước.


## Commands

### Make Shared Library
```bash
make shared
```

### Make Static Library
```bash
make static
```

### Run Static Library
```bash
./bin/use-static-library
```

### Run Shared Library
```bash
LD_LIBRARY_PATH=./lib/shared/ ./bin/use-shared-library
```