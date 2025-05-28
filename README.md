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
|                        |                                 |- Lịch sử giao dịch.                                  |

---

## Đặc Tả Chức Năng

1. Chức năng Người Dùng
a. Đăng ký tài khoản mới
Giao diện: Nhập tên đăng nhập, họ tên, ngày sinh, số điện thoại, mật khẩu (có thể bỏ trống).

Tự động xử lý:

Nếu mật khẩu bỏ trống → hệ thống sinh mật khẩu tạm thời (6 ký tự ngẫu nhiên).

Sinh tự động walletId (8 ký tự).

Khởi tạo số dư ví là 1000 điểm.

Đặt isTempPassword = true nếu dùng mật khẩu tạm thời.

b. Đăng nhập
Xác thực bằng tên đăng nhập và mật khẩu đã hash qua singleHash.

Nếu là tài khoản admin → vào menu quản trị.

Nếu là tài khoản người dùng → vào menu người dùng.

Nếu là mật khẩu tạm thời → bắt buộc đổi mật khẩu sau khi đăng nhập.

c. Xem thông tin ví
Hiển thị:

Họ tên, ngày sinh, số điện thoại, số dư, ID ví.

Danh sách lịch sử giao dịch từ transactions[walletId].

d. Chuyển điểm đến ví khác (xác thực OTP)
Nhập ID ví người nhận và số điểm muốn chuyển.

Kiểm tra số dư.

Sinh mã OTP và yêu cầu người dùng nhập lại để xác minh.

Nếu OTP đúng:

Trừ điểm người gửi, cộng điểm người nhận.

Ghi giao dịch vào transactions.txt theo dạng:

Người gửi: Đã chuyển X điểm tới ví Y

Người nhận: Đã nhận X điểm từ ví Z

e. Đổi mật khẩu (có OTP)
Sinh OTP và yêu cầu xác nhận.

Nếu đúng → yêu cầu nhập mật khẩu mới.

Cập nhật password đã hash lại và đặt isTempPassword = false.

f. Đổi số điện thoại (có OTP)
Quy trình tương tự như đổi mật khẩu:

OTP xác minh.

Nhập số mới.

Ghi đè phone trong User.

🛠️ 2. Chức năng Quản Trị Viên
a. Tạo tài khoản người dùng hoặc quản trị viên
Tương tự chức năng tạo tài khoản người dùng.

Có thể chỉ định vai trò là "admin" hoặc "user" qua đối số isAdmin.

b. Xem danh sách tất cả ví điện tử
Duyệt toàn bộ map users và hiển thị:
username | fullName | role | walletId | balance

c. Sao lưu dữ liệu người dùng
Gọi backupUsers() → ghi toàn bộ users ra file backup_users.txt.

⚙️ 3. Chức năng Hệ Thống
a. Sinh mã OTP
Gọi generateOTP() → trả về chuỗi số ngẫu nhiên 6 chữ số (100000–999999).

b. Sinh ngẫu nhiên ID ví và mật khẩu tạm thời
Sử dụng generateRandomString(int length) để tạo chuỗi ký tự.

ID ví: 8 ký tự, Mật khẩu tạm: 6 ký tự.

c. Tự động lưu và đọc dữ liệu từ file
users.txt:

Mỗi dòng lưu 9 trường: username,password,role,walletId,balance,isTempPassword,fullName,dob,phone

Đọc và ghi qua loadUsers() và saveUsers()

transactions.txt:

Mỗi dòng lưu: walletId|message

Đọc qua loadTransactions() và ghi bằng saveTransactions().

backup_users.txt:

Được tạo thông qua backupUsers(), chứa nội dung như users.txt.

🔒 Bảo Mật
Mật khẩu không lưu dạng thuần → dùng hàm hash singleHash().

OTP giúp tăng cường bảo mật khi:

Đổi mật khẩu

Đổi số điện thoại

Chuyển điểm

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
