# Multi-threaded Monte Carlo $\pi$ Estimation

Dự án này được thực hiện bởi **Nhóm Eternals** cho bài Lab 2 môn **Hệ điều hành (CO2018)** - Học kỳ HK252 tại **Đại học Bách Khoa TP.HCM (HCMUT)**. Mục tiêu là nghiên cứu ảnh hưởng của đa luồng và các chiến lược đồng bộ hóa lên hiệu suất tính toán số $\pi$ bằng phương pháp Monte Carlo.

## 👥 Thành viên nhóm
* **Huỳnh Tấn Tiến** (Lớp KSTN - Khoa KH&KT Máy tính)
* Bùi Minh Tân
* Lưu Bảo Trang
* Lê Minh Anh
* Đặng Trần Văn Bách
* Huỳnh Hoàng Anh

## 📋 Tổng quan đề tài
Dự án so sánh 3 phương pháp tiếp cận để đo lường giới hạn của khả năng mở rộng (scalability) và chi phí đồng bộ hóa (synchronization overhead):

1.  **Approach 1 (Single Thread):** Thiết lập mức cơ sở (baseline) để so sánh hiệu suất.
2.  **Approach 2 (Local Accumulation):** Sử dụng mô hình Map-Reduce. Mỗi luồng có bộ đếm riêng và chỉ gộp kết quả ở cuối. Không có tranh chấp tài nguyên (Contention-free).
3.  **Approach 3 (Shared Variable with Mutex):** Sử dụng một biến global chung được bảo vệ bởi Mutex/Semaphore. Dùng để quan sát hiện tượng nghẽn (Lock Contention) và suy giảm hiệu suất khi số luồng tăng.

## 🚀 Hướng dẫn cài đặt & Thực thi

### Yêu cầu hệ thống
* Hệ điều hành: Linux (khuyên dùng Ubuntu/WSL)
* Trình biên dịch: `gcc`
* Công cụ hỗ trợ: `make`, `bc` (để chạy script tính toán toán học)

### 1. Biên dịch
Sử dụng `Makefile` đi kèm để biên dịch tất cả các phiên bản:
```bash
make
```
Sau khi chạy, bạn sẽ có các file thực thi: `app1` (Single thread) và `app2` (Multi-thread).

### 2. Chạy thực nghiệm tự động
Chúng mình đã chuẩn bị sẵn một script `run_experiment.sh` để tự động chạy qua các cấu hình từ 2 đến 128 luồng với $10^8$ điểm ảnh:
```bash
make test
```

### 3. Chạy thủ công
* **Approach 1:** `./app1 <tổng_số_điểm>`
* **Approach 2:** `./app2 <tổng_số_điểm> <số_luồng>`
* **Approach 3:** Biên dịch thủ công `gcc -O3 src/approach3_mutex.c -lpthread -o app3` rồi chạy `./app3`

## 📊 Phương pháp đo lường (Methodology)
* **Thông số kiểm thử:** $100,000,000$ điểm mẫu mỗi lần chạy.
* **Số lần lặp:** Mỗi cấu hình luồng được chạy 5 lần để lấy giá trị trung bình (Average Execution Time).
* **Chỉ số đo lường:** * **Speedup:** $S = \frac{T_{single}}{T_{parallel}}$
    * **Parallel Efficiency:** $E = \frac{S}{N}$ (với $N$ là số luồng).

## 📄 Yêu cầu cho lớp Tài năng (KSTN)
Theo yêu cầu bổ sung, nhóm đang phát triển một bài báo khoa học ngắn (Academic Paper) định dạng **LaTeX** (Springer template) từ 4-6 trang để phân tích các khía cạnh sau:
* **Non-linear Speedup:** Tại sao tốc độ không tăng tuyến tính theo số luồng.
* **Saturation Point:** Xác định điểm bão hòa dựa trên số nhân CPU thực tế của máy TUF Gaming F15.
* **Synchronization Cost:** Phân tích sự sụt giảm hiệu suất nghiêm trọng của Approach 3 khi đối mặt với tranh chấp khóa (Lock contention).

## 📂 Cấu trúc thư mục
```text
.
├── src/                    # Mã nguồn C (.c, Makefile)
├── scripts/                # Script thực nghiệm (.sh)
├── report/                 # File LaTeX và bài báo học thuật
└── README.md
```

## 🛠 Công cụ phát triển
* **IDE:** Visual Studio Code
* **Environment:** Ubuntu on WSL / Linux Terminal
* **Version Control:** Git/GitHub

---
*Dự án này thuộc chương trình đào tạo của Khoa Khoa học và Kỹ thuật Máy tính - ĐH Bách Khoa TP.HCM.*

---

### Một vài góp ý thêm cho Tiến:
1.  **Về file `approach3_mutex.c`**: Trong code bạn gửi, bạn đang dùng `sem_t` (Semaphore). Mặc dù nó hoạt động tương tự Mutex trong trường hợp này (binary semaphore), nhưng nếu giảng viên khó tính, bạn nên đổi sang `pthread_mutex_t` để đúng với thuật ngữ "Mutex" trong yêu cầu Lab nhé.
2.  **Định dạng xuống dòng**: Mình đã nhắc ở lượt trước, hãy đảm bảo các script `.sh` trên GitHub luôn ở định dạng **LF** để nhóm của bạn không bị lỗi khi clone về máy Linux.

Bạn thấy bản README này đã ổn để nộp chưa?
