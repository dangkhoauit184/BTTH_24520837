#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>
using namespace std;

struct SoTietKiem {
    string maSo;
    string loaiTietKiem;
    string hoTen;
    string cmnd;
    int ngay, thang, nam;
    double soTienGui;
};

// Kiểm tra mã số (không dùng isalnum)
bool kiemTraMaSo(const string &maSo) {
    if (maSo.length() > 5) return false;
    for (int i = 0; i < maSo.length(); i++) {
        char c = maSo[i];
        if (!((c >= '0' && c <= '9') ||
              (c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z')))
            return false;
    }
    return true;
}

// Kiểm tra CMND (không dùng isdigit)
bool kiemTraCMND(const string &cmnd) {
    if (cmnd.length() != 9 && cmnd.length() != 12) return false;
    for (int i = 0; i < cmnd.length(); i++) {
        char c = cmnd[i];
        if (!(c >= '0' && c <= '9'))
            return false;
    }
    return true;
}

// Kiểm tra ngày hợp lệ
bool kiemTraNgay(int ngay, int thang, int nam) {
    if (thang < 1 || thang > 12) return false;
    int soNgayTrongThang = 31;
    if (thang == 4 || thang == 6 || thang == 9 || thang == 11)
        soNgayTrongThang = 30;
    else if (thang == 2) {
        if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0))
            soNgayTrongThang = 29;
        else
            soNgayTrongThang = 28;
    }
    return (ngay >= 1 && ngay <= soNgayTrongThang);
}

// Hàm nhập họ tên khách hàng
string nhapTenKhachHang() {
    cout << "Nhập họ tên khách hàng: ";
    string ten;
    getline(cin, ten);
    return ten;
}

// Hàm nhập CMND
string nhapCMND() {
    string cmnd;
    cout << "Nhập CMND (9 hoặc 12 chữ số): ";
    cin >> cmnd;
    while (!kiemTraCMND(cmnd)) {
        cout << "CMND không hợp lệ. Vui lòng nhập lại: ";
        cin >> cmnd;
    }
    return cmnd;
}

// Nhập thông tin số tiết kiệm
SoTietKiem nhapSoTietKiem() {
    SoTietKiem stk;
    cout << "Nhập mã số (tối đa 5 ký tự, không chứa ký tự đặc biệt): ";
    cin >> stk.maSo;
    while (!kiemTraMaSo(stk.maSo)) {
        cout << "Mã số không hợp lệ. Vui lòng nhập lại: ";
        cin >> stk.maSo;
    }
    
    cout << "Nhập loại tiết kiệm (ví dụ: ngắn hạn, dài hạn): ";
    cin >> stk.loaiTietKiem;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    stk.hoTen = nhapTenKhachHang();
    stk.cmnd = nhapCMND();
    
    cout << "Nhập ngày mở sổ (dd mm yyyy): ";
    cin >> stk.ngay >> stk.thang >> stk.nam;
    while (!kiemTraNgay(stk.ngay, stk.thang, stk.nam)) {
        cout << "Ngày không hợp lệ. Vui lòng nhập lại (dd mm yyyy): ";
        cin >> stk.ngay >> stk.thang >> stk.nam;
    }
    
    cout << "Nhập số tiền gửi (phải là số dương): ";
    cin >> stk.soTienGui;
    while (stk.soTienGui <= 0) {
        cout << "Số tiền gửi không hợp lệ. Vui lòng nhập lại: ";
        cin >> stk.soTienGui;
    }
    return stk;
}

// Xuất thông tin số tiết kiệm
void xuatSoTietKiem(const SoTietKiem &stk) {
    cout << "Mã số: " << stk.maSo
         << ", Loại tiết kiệm: " << stk.loaiTietKiem
         << ", Họ tên: " << stk.hoTen
         << ", CMND: " << stk.cmnd
         << ", Ngày mở sổ: " << stk.ngay << "/" << stk.thang << "/" << stk.nam
         << ", Số tiền gửi: " << stk.soTienGui << endl;
}

// Tính tiền lãi
double tinhTienLai(const SoTietKiem &stk, double laiSuat) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int namHienTai = 1900 + ltm->tm_year;
    int thangHienTai = 1 + ltm->tm_mon;
    int ngayHienTai = ltm->tm_mday;
    
    int soThang = (namHienTai - stk.nam) * 12 + (thangHienTai - stk.thang);
    if (ngayHienTai < stk.ngay)
        soThang--;
    if (stk.loaiTietKiem == "ngắn hạn" && soThang > 6)
        soThang = 6;
    return stk.soTienGui * laiSuat * soThang / 12 / 100;
}

// Cập nhật lãi suất và tính tiền lãi
void capNhatLaiSuat(vector<SoTietKiem> &danhSach) {
    double laiSuat;
    cout << "Nhập lãi suất (%/năm): ";
    cin >> laiSuat;
    for (int i = 0; i < danhSach.size(); i++) {
        double tienLai = tinhTienLai(danhSach[i], laiSuat);
        cout << "Mã số: " << danhSach[i].maSo << ", Tiền lãi: " << tienLai << endl;
    }
}

// Rút tiền từ số tiết kiệm
void rutTien(vector<SoTietKiem> &danhSach) {
    string maSo;
    cout << "Nhập mã số cần rút tiền: ";
    cin >> maSo;
    for (int i = 0; i < danhSach.size(); i++) {
        if (danhSach[i].maSo == maSo) {
            double soTienRut;
            cout << "Nhập số tiền cần rút: ";
            cin >> soTienRut;
            if (soTienRut > danhSach[i].soTienGui) {
                cout << "Số tiền rút vượt quá số tiền gửi." << endl;
                return;
            }
            danhSach[i].soTienGui -= soTienRut;
            cout << "Rút tiền thành công. Số tiền còn lại: " << danhSach[i].soTienGui << endl;
            return;
        }
    }
    cout << "Không tìm thấy số tiết kiệm với mã số này." << endl;
}

// Tìm kiếm theo CMND
void timKiemTheoCMND(const vector<SoTietKiem> &danhSach) {
    string cmnd;
    cout << "Nhập CMND cần tìm: ";
    cin >> cmnd;
    bool found = false;
    for (int i = 0; i < danhSach.size(); i++) {
        if (danhSach[i].cmnd == cmnd) {
            xuatSoTietKiem(danhSach[i]);
            found = true;
        }
    }
    if (!found) cout << "Không tìm thấy khách hàng với CMND này." << endl;
}

// Liệt kê theo khoảng thời gian mở sổ
void lietKeTheoThoiGian(const vector<SoTietKiem> &danhSach) {
    int ngayBatDau, thangBatDau, namBatDau;
    int ngayKetThuc, thangKetThuc, namKetThuc;
    cout << "Nhập ngày bắt đầu (dd mm yyyy): ";
    cin >> ngayBatDau >> thangBatDau >> namBatDau;
    cout << "Nhập ngày kết thúc (dd mm yyyy): ";
    cin >> ngayKetThuc >> thangKetThuc >> namKetThuc;
    bool found = false;
    for (int i = 0; i < danhSach.size(); i++) {
        if ((danhSach[i].nam > namBatDau || 
            (danhSach[i].nam == namBatDau && danhSach[i].thang > thangBatDau) || 
            (danhSach[i].nam == namBatDau && danhSach[i].thang == thangBatDau && danhSach[i].ngay >= ngayBatDau)) &&
            (danhSach[i].nam < namKetThuc || 
            (danhSach[i].nam == namKetThuc && danhSach[i].thang < thangKetThuc) || 
            (danhSach[i].nam == namKetThuc && danhSach[i].thang == thangKetThuc && danhSach[i].ngay <= ngayKetThuc))) {
            xuatSoTietKiem(danhSach[i]);
            found = true;
        }
    }
    if (!found) cout << "Không tìm thấy số tiết kiệm trong khoảng thời gian này." << endl;
}

// So sánh theo số tiền gửi giảm dần
bool soSanhTheoTienGiamDan(const SoTietKiem &a, const SoTietKiem &b) {
    return a.soTienGui > b.soTienGui;
}

// So sánh theo ngày mở sổ tăng dần
bool soSanhTheoNgayTangDan(const SoTietKiem &a, const SoTietKiem &b) {
    if (a.nam != b.nam)
        return a.nam < b.nam;
    if (a.thang != b.thang)
        return a.thang < b.thang;
    return a.ngay < b.ngay;
}

// Sắp xếp danh sách theo yêu cầu
void sapXepDanhSach(vector<SoTietKiem> &danhSach) {
    int luaChon;
    cout << "Chọn cách sắp xếp:\n1. Theo số tiền gửi giảm dần\n2. Theo ngày mở sổ tăng dần\n";
    cout << "Nhập lựa chọn (1 hoặc 2): ";
    cin >> luaChon;
    
    if (luaChon == 1) {
        for (int i = 0; i < danhSach.size() - 1; i++) {
            for (int j = i + 1; j < danhSach.size(); j++) {
                if (soSanhTheoTienGiamDan(danhSach[j], danhSach[i])) {
                    SoTietKiem temp = danhSach[i];
                    danhSach[i] = danhSach[j];
                    danhSach[j] = temp;
                }
            }
        }
        cout << "Đã sắp xếp theo số tiền gửi giảm dần!\n";
    } else if (luaChon == 2) {
        for (int i = 0; i < danhSach.size() - 1; i++) {
            for (int j = i + 1; j < danhSach.size(); j++) {
                if (soSanhTheoNgayTangDan(danhSach[j], danhSach[i])) {
                    SoTietKiem temp = danhSach[i];
                    danhSach[i] = danhSach[j];
                    danhSach[j] = temp;
                }
            }
        }
        cout << "Đã sắp xếp theo ngày mở sổ tăng dần!\n";
    } else {
        cout << "Lựa chọn không hợp lệ!\n";
        return;
    }
    
    cout << "Danh sách sau khi sắp xếp:\n";
    for (int i = 0; i < danhSach.size(); i++) {
        xuatSoTietKiem(danhSach[i]);
    }
}

int main() {
    vector<SoTietKiem> danhSach;
    int soLuongKhachHang;
    int luaChon;
    
    cout << "Nhập số lượng khách hàng: ";
    cin >> soLuongKhachHang;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < soLuongKhachHang; i++) {
        cout << "\nNhập thông tin khách hàng thứ " << i + 1 << ":\n";
        SoTietKiem stk = nhapSoTietKiem();
        danhSach.push_back(stk);
    }
    
    // Sử dụng while thay vì do-while
    luaChon = -1; // Khởi tạo giá trị ban đầu để vào vòng lặp
    while (luaChon != 0) {
        cout << "\n1. Nhập số tiết kiệm\n2. Xuất danh sách số tiết kiệm\n3. Cập nhật lãi suất\n4. Rút tiền\n5. Tìm kiếm theo CMND\n6. Liệt kê theo thời gian\n7. Sắp xếp danh sách\n0. Thoát\n";
        cout << "Chọn chức năng: ";
        cin >> luaChon;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (luaChon == 0) {
            cout << "Thoát chương trình.\n";
            break; // Thoát vòng lặp
        }
        
        switch (luaChon) {
            case 1: {
                SoTietKiem stk = nhapSoTietKiem();
                danhSach.push_back(stk);
                break;
            }
            case 2: {
                if (danhSach.empty()) {
                    cout << "Danh sách trống!\n";
                } else {
                    for (int i = 0; i < danhSach.size(); i++) {
                        xuatSoTietKiem(danhSach[i]);
                    }
                }
                break;
            }
            case 3: {
                capNhatLaiSuat(danhSach);
                break;
            }
            case 4: {
                rutTien(danhSach);
                break;
            }
            case 5: {
                timKiemTheoCMND(danhSach);
                break;
            }
            case 6: {
                lietKeTheoThoiGian(danhSach);
                break;
            }
            case 7: {
                if (danhSach.empty()) {
                    cout << "Danh sách trống, không thể sắp xếp!\n";
                } else {
                    sapXepDanhSach(danhSach);
                }
                break;
            }
            default: {
                cout << "Lựa chọn không hợp lệ, vui lòng chọn lại.\n";
                break;
            }
        }
    }
    return 0;
}
