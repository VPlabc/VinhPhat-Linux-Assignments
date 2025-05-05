# README

BT5. Tạo Process Zombie và Orphan
Mô tả: Viết một chương trình tạo ra một tiến trình zombie và một tiến trình orphan để hiểu về các loại tiến trình đặc biệt này.
Yêu cầu:
Để tạo zombie, cho tiến trình cha kết thúc sớm trong khi tiến trình con vẫn còn chạy, và sử dụng ps để quan sát trạng thái zombie của tiến trình.
Để tạo orphan, cho tiến trình con ngủ trong một khoảng thời gian dài hơn tiến trình cha, để tiến trình con trở thành orphan.
Giải thích trạng thái zombie và orphan, cùng lý do tại sao chúng xuất hiện trong Linux.

=> trường hợp Orphan:
    sau khi chạy tiến trình cha kết thúc sau 10s tiến trình con vẫn chạy và rơi vào trạng thái orphan và được sự quản lý của sell/terminal
    trường hợp này tiến cha gặp vấn đề hoặc lý do nào đó cần kết thúc nhưng không làm ảnh hưởng đến tiến trình con.
    trình con vẫn đang hoạt động và được linux trao quyền quản lý cho tiến trình sell/terminal để người dùng vẫn có thể quản lý được nó.

    ### Trạng thái Orphan
    ![Orphan Process](..../image/orphan_process.png)

=> trường hợp Zombie:
    sau khi chạy 5 giây thì tiến trình con kết thúc và rơi vào trạng thái zombie do chưa được giải phóng hết tài nguyên. 
    nó phụ thuộc vào tiến trình cha và chỉ được giải phóng khi tiến trình cha kết thúc 
    trường hợp này xảy ra khi các tiến trình gặp lỗi hoặc lý do nào đó buộc nó phải kết thúc khiến nó rơi vào trạng thái ngừng hoạt động mà không thể giải phóng được tài nguyên.
    nó cần có tiến trình nào đó quản lý hoặc signal để kết thúc khi cần. điều này giúp hạn chế lãng phí tài nguyên.

    ### Trạng thái Zombie
    ![Zombie Process](..../image/zombie_process.png)

## Commands

### Build ra file thực thi ví dụ trạng thái orphan
```bash
make orphan
```

### Build ra file thực thi ví dụ trạng thái zombie
```bash
make zombie
```

### run file thực thi.
```bash
./exam
```

### làm sạch mã nguồn
```bash
make clean
```