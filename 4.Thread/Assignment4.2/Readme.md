# README

BT2. Đồng Bộ Hóa Threads với Mutex
Viết một chương trình sử dụng pthread và mutex để thực hiện các thao tác sau:
Tạo một biến toàn cục counter khởi tạo bằng 0.
Tạo ba threads, mỗi thread tăng giá trị của counter lên 1, 1.000.000 lần.
Sử dụng mutex để đảm bảo rằng việc tăng counter được thực hiện an toàn.
In ra giá trị cuối cùng của counter khi tất cả các threads hoàn thành.
Hỏi: Tại sao cần mutex trong bài này? Điều gì xảy ra nếu bỏ mutex?
Gợi ý: Sử dụng pthread_mutex_lock và pthread_mutex_unlock để khóa và mở khóa mutex khi truy cập vào counter.

=> Mutex được sử dụng để đảm bảo rằng chỉ một thread có thể truy cập vào biến counter tại một thời điểm nhất định. Nếu không sử dụng mutex, nhiều thread có thể cố gắng tăng giá trị của counter cùng một lúc, dẫn đến tình trạng bất đồng bộ và giá trị cuối cùng của counter có thể không chính xác. 
Điều này xảy ra vì các thao tác tăng giá trị của counter có thể bị ngắt giữa chừng bởi các thread khác, dẫn đến việc ghi đè lên nhau và mất dữ liệu. kết quả cuối cùng của counter có thể nhỏ hơn 3.000.000 (1.000.000 * 3) nếu không sử dụng mutex.
kết quả như hình cho 2 lần chạy.
lần đầu make và chạy mà không có mutex. kết quả không đúng với target đưa ra.
lần thứ 2 là chạy với mutex. kết quả đúng với target đưa ra.

![Thread with pthread_mutex](https://github.com/user-attachments/assets/9e5ecd4a-71fb-452f-9ce6-91f0ce0d7930)

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
