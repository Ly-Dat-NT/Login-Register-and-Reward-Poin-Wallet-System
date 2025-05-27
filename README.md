# HỆ THỐNG QUẢN LÝ ĐIỂM THƯỞNG

## Giới Thiệu Dự Án

Dự án này xây dựng một **hệ thống ví điện tử quản lý điểm thưởng** với các chức năng cơ bản như:
- Đăng nhập, đăng ký tài khoản người dùng hoặc quản trị viên
- Quản lý thông tin ví điện tử (số dư, lịch sử giao dịch)
- Chuyển điểm giữa các tài khoản người dùng
- Thay đổi thông tin cá nhân như mật khẩu, số điện thoại
- Quản trị viên có thể tạo tài khoản và sao lưu dữ liệu

Ngôn ngữ sử dụng: **C++**

---

##  Thành Viên Tham Gia & Phân Công Công Việc

| Họ và Tên              | Vai Trò                         | Công Việc Được Giao                                  |
|------------------------|---------------------------------|------------------------------------------------------|
| Lý Nguyễn Thành Đạt    | Lưu trữ, bảo mật, báo cáo.      |- Lưu file người dùng/ví/giao dịch.                   |
|                        |                                 |- Mã hoá mật khẩu.                                    |
|                        |                                 |- Tự động tạo mật khẩu, sao lưu và khôi phục.         |
| Trần Văn Tiến Đạt      | Backend tài khoản.              |- Tạo class User và quản lý tài khoản.                |
|                        |                                 |- Đăng ký, đăng nhập, đổi mật khẩu.                   |
|                        |                                 |- Quản lý phân quyền (user/admin).                    | 
|                        |                                 |- OTP.                                                |
| Nguyễn Thành Đạt       | Ví và giao dịch.                |- Tạo class Wallet, Transaction.                      |
|                        |                                 |- Chuyển điểm giữa ví.                                |
|                        |                                 |- Giao dịch đảm bảo tính atomic (ACID).               |
|                        |                                 |- Lịch sử giao dịch.                                  |

---

## Đặc Tả Chức Năng

### 1. Người Dùng
- Đăng ký tài khoản mới (có thể tạo mật khẩu tạm thời hoặc tự nhập)
- Đăng nhập bằng tên đăng nhập và mật khẩu
- Xem thông tin ví: họ tên, ngày sinh, số điện thoại, số dư, lịch sử giao dịch
- Chuyển điểm đến ví khác (xác thực bằng OTP)
- Đổi mật khẩu (có OTP)
- Đổi số điện thoại (có OTP)

### 2. Quản Trị Viên
- Tạo tài khoản người dùng hoặc quản trị viên
- Xem danh sách tất cả ví điện tử
- Sao lưu dữ liệu người dùng ra tệp `backup_users.txt`

### 3. Hệ Thống
- Sinh ngẫu nhiên OTP xác thực
- Sinh ngẫu nhiên ID ví và mật khẩu tạm thời
- Tự động lưu và đọc dữ liệu từ tệp:
  - `users.txt` — thông tin người dùng
  - `transactions.txt` — lịch sử giao dịch
  - `backup_users.txt` — bản sao lưu

---

## Cài Đặt và Biên Dịch Chương Trình

### Yêu Cầu
- Trình biên dịch hỗ trợ C++11 trở lên (G++, Clang++, MSVC...)
- Hệ điều hành: Windows (vì dùng `system("cls")` để xóa màn hình)

### Cách Tải Và Biên Dịch
1. **Tải file ZIP**
- Truy cập Github -> Nhấn code -> Chọn download ZIP
- Giải nén và vào thư mục dự án
2. **Biên Dịch Bằng G++**
- g++ main.cpp -o wallet
