#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

struct ChuyenBay {
    string maChuyenBay;
    int ngay, thang, nam;
    int gio, phut;
    string noiDi;
    string noiDen;
};

// Hàm chuyển chuỗi về chữ thường
string toLowerCase(const string& str) {
    string result = str;
    for (int i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] + 32; // Chuyển từ hoa sang thường
        }
    }
    return result;
}

// Kiểm tra mã chuyến bay (5 ký tự chữ và số)
bool kiemTraMaChuyenBay(const string& maChuyenBay) {
    if (maChuyenBay.length() != 5) return false;
    for (int i = 0; i < maChuyenBay.length(); i++) {
        char c = maChuyenBay[i];
        if (!((c >= '0' && c <= '9') ||
              (c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z')))
            return false;
    }
    return true;
}

// Kiểm tra giờ bay (00:00 đến 23:59)
bool kiemTraGioBay(int gio, int phut) {
    return (gio >= 0 && gio <= 23 && phut >= 0 && phut <= 59);
}

// Kiểm tra ngày bay
bool kiemTraNgayBay(int ngay, int thang, int nam) {
    if (thang < 1 || thang > 12) return false;
    int soNgayTrongThang = 31;
    if (thang == 4 || thang == 6 || thang == 9 || thang == 11) {
        soNgayTrongThang = 30;
    } else if (thang == 2) {
        if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0)) {
            soNgayTrongThang = 29;
        } else {
            soNgayTrongThang = 28;
        }
    }
    return (ngay >= 1 && ngay <= soNgayTrongThang);
}

// Kiểm tra nơi đi và nơi đến (tối đa 20 ký tự, không chứa số)
bool kiemTraNoiDiNoiDen(const string& noi) {
    if (noi.length() > 35) return false;
    for (int i = 0; i < noi.length(); i++) {
        char c = noi[i];
        if (c >= '0' && c <= '9') return false; // Không cho phép số
    }
    return true;
}

// Nhập thông tin chuyến bay
ChuyenBay nhapChuyenBay() {
    ChuyenBay chuyenBay;

    cout << "Nhập mã chuyến bay (5 ký tự, có thể chứa cả chữ và số): ";
    cin >> chuyenBay.maChuyenBay;
    while (!kiemTraMaChuyenBay(chuyenBay.maChuyenBay)) {
        cout << "Mã chuyến bay không hợp lệ. Vui lòng nhập lại: ";
        cin >> chuyenBay.maChuyenBay;
    }

    cout << "Nhập ngày bay (dd mm yyyy): ";
    cin >> chuyenBay.ngay >> chuyenBay.thang >> chuyenBay.nam;
    while (!kiemTraNgayBay(chuyenBay.ngay, chuyenBay.thang, chuyenBay.nam)) {
        cout << "Ngày bay không hợp lệ. Vui lòng nhập lại (dd mm yyyy): ";
        cin >> chuyenBay.ngay >> chuyenBay.thang >> chuyenBay.nam;
    }

    cout << "Nhập giờ bay (hh mm): ";
    cin >> chuyenBay.gio >> chuyenBay.phut;
    while (!kiemTraGioBay(chuyenBay.gio, chuyenBay.phut)) {
        cout << "Giờ bay không hợp lệ. Vui lòng nhập lại (hh mm): ";
        cin >> chuyenBay.gio >> chuyenBay.phut;
    }

    cin.ignore(); // Xóa ký tự newline
    cout << "Nhập nơi đi: ";
    getline(cin, chuyenBay.noiDi);
    while (!kiemTraNoiDiNoiDen(chuyenBay.noiDi)) {
        cout << "Nơi đi không hợp lệ. Vui lòng nhập lại: ";
        getline(cin, chuyenBay.noiDi);
    }

    cout << "Nhập nơi đến: ";
    getline(cin, chuyenBay.noiDen);
    while (!kiemTraNoiDiNoiDen(chuyenBay.noiDen)) {
        cout << "Nơi đến không hợp lệ. Vui lòng nhập lại: ";
        getline(cin, chuyenBay.noiDen);
    }

    return chuyenBay;
}

// Hiển thị thông tin chuyến bay
void hienThiChuyenBay(const ChuyenBay& chuyenBay) {
    cout << "Mã chuyến bay: " << chuyenBay.maChuyenBay 
         << ", Ngày bay: " << setw(2) << setfill('0') << chuyenBay.ngay << "/" 
         << setw(2) << setfill('0') << chuyenBay.thang << "/" << chuyenBay.nam
         << ", Giờ bay: " << setw(2) << setfill('0') << chuyenBay.gio << ":" 
         << setw(2) << setfill('0') << chuyenBay.phut
         << ", Nơi đi: " << chuyenBay.noiDi
         << ", Nơi đến: " << chuyenBay.noiDen << endl;
}

// So sánh để sắp xếp chuyến bay theo ngày giờ
bool soSanhChuyenBay(const ChuyenBay& a, const ChuyenBay& b) {
    if (a.nam != b.nam) return a.nam < b.nam;
    if (a.thang != b.thang) return a.thang < b.thang;
    if (a.ngay != b.ngay) return a.ngay < b.ngay;
    if (a.gio != b.gio) return a.gio < b.gio;
    return a.phut < b.phut;
}

// Sắp xếp danh sách chuyến bay
void sapXepChuyenBay(vector<ChuyenBay>& danhSachChuyenBay) {
    sort(danhSachChuyenBay.begin(), danhSachChuyenBay.end(), soSanhChuyenBay);
}

// Tìm kiếm chuyến bay (không phân biệt chữ hoa/thường)
vector<ChuyenBay> timChuyenBay(const vector<ChuyenBay>& danhSach, const string& tuKhoa) {
    vector<ChuyenBay> ketQua;
    string tuKhoaLower = toLowerCase(tuKhoa);
    for (int i = 0; i < danhSach.size(); ++i) {
        string maChuyenBayLower = toLowerCase(danhSach[i].maChuyenBay);
        string noiDiLower = toLowerCase(danhSach[i].noiDi);
        string noiDenLower = toLowerCase(danhSach[i].noiDen);
        if (maChuyenBayLower == tuKhoaLower || noiDiLower == tuKhoaLower || noiDenLower == tuKhoaLower) {
            ketQua.push_back(danhSach[i]);
        }
    }
    return ketQua;
}

// Đếm số chuyến bay từ nơi đi đến nơi đến
int demChuyenBay(const vector<ChuyenBay>& danhSach, const string& noiDi, const string& noiDen) {
    int dem = 0;
    string noiDiLower = toLowerCase(noiDi);
    string noiDenLower = toLowerCase(noiDen);
    for (int i = 0; i < danhSach.size(); ++i) {
        string chuyenBayNoiDiLower = toLowerCase(danhSach[i].noiDi);
        string chuyenBayNoiDenLower = toLowerCase(danhSach[i].noiDen);
        if (chuyenBayNoiDiLower == noiDiLower && chuyenBayNoiDenLower == noiDenLower) {
            dem++;
        }
    }
    return dem;
}

// Hiển thị chuyến bay theo ngày và nơi đi
void hienThiChuyenBayTheoNgayNoiDi(const vector<ChuyenBay>& danhSach, const string& noiDi, int ngay, int thang, int nam) {
    bool found = false;
    string noiDiLower = toLowerCase(noiDi);
    cout << "Danh sách chuyến bay khởi hành từ " << noiDi << " vào ngày " 
         << ngay << "/" << thang << "/" << nam << ":\n";
    for (int i = 0; i < danhSach.size(); ++i) {
        string chuyenBayNoiDiLower = toLowerCase(danhSach[i].noiDi);
        if (chuyenBayNoiDiLower == noiDiLower && danhSach[i].ngay == ngay && 
            danhSach[i].thang == thang && danhSach[i].nam == nam) {
            hienThiChuyenBay(danhSach[i]);
            found = true;
        }
    }
    if (!found) {
        cout << "Không tìm thấy chuyến bay nào.\n";
    }
}

int main() {
    int soLuongChuyenBay;
    cout << "Nhập số lượng chuyến bay: ";
    cin >> soLuongChuyenBay;
    cin.ignore(); // Xóa ký tự newline sau khi nhập số lượng

    vector<ChuyenBay> danhSachChuyenBay;

    // Nhập danh sách chuyến bay
    for (int i = 0; i < soLuongChuyenBay; ++i) {
        cout << "\nNhập thông tin chuyến bay thứ " << i + 1 << ":\n";
        ChuyenBay chuyenBay = nhapChuyenBay();
        danhSachChuyenBay.push_back(chuyenBay);
    }

    // Sắp xếp chuyến bay
    sapXepChuyenBay(danhSachChuyenBay);

    // Hiển thị danh sách đã sắp xếp
    cout << "\nDanh sách chuyến bay đã sắp xếp:\n";
    for (int i = 0; i < danhSachChuyenBay.size(); ++i) {
        hienThiChuyenBay(danhSachChuyenBay[i]);
    }

    // Tìm kiếm chuyến bay
    string tuKhoa;
    cout << "\nNhập từ khóa tìm kiếm (mã chuyến bay, nơi đi, nơi đến): ";
    getline(cin, tuKhoa);

    vector<ChuyenBay> ketQuaTimKiem = timChuyenBay(danhSachChuyenBay, tuKhoa);
    if (ketQuaTimKiem.empty()) {
        cout << "Không tìm thấy chuyến bay nào.\n";
    } else {
        cout << "\nKết quả tìm kiếm:\n";
        for (int i = 0; i < ketQuaTimKiem.size(); ++i) {
            hienThiChuyenBay(ketQuaTimKiem[i]);
        }
    }

    // Đếm số chuyến bay từ nơi đi đến nơi đến
    string noiDi, noiDen;
    cout << "\nNhập nơi đi: ";
    getline(cin, noiDi);
    cout << "Nhập nơi đến: ";
    getline(cin, noiDen);

    int soChuyenBay = demChuyenBay(danhSachChuyenBay, noiDi, noiDen);
    cout << "Số chuyến bay từ " << noiDi << " đến " << noiDen << " là: " << soChuyenBay << endl;

    // Hiển thị chuyến bay theo ngày và nơi đi
    int ngay, thang, nam;
    cout << "\nNhập nơi đi để hiển thị chuyến bay theo ngày: ";
    getline(cin, noiDi);
    cout << "Nhập ngày khởi hành (dd mm yyyy): ";
    cin >> ngay >> thang >> nam;
    hienThiChuyenBayTheoNgayNoiDi(danhSachChuyenBay, noiDi, ngay, thang, nam);

    return 0;
}
