#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct HocSinh {
    string hoTen;
    double diemToan;
    double diemVan;
    double diemNgoaiNgu;
    string phanLoai;  // Đã bỏ diemTrungBinh khỏi struct
};

// Hàm tính điểm trung bình (tách riêng)
double tinhDiemTrungBinh(const HocSinh& hs) {
    return (2 * hs.diemToan + hs.diemVan + hs.diemNgoaiNgu) / 4;
}

// Hàm xếp loại (tách riêng)
string xepLoai(double diemTB) {
    if (diemTB >= 9) return "Xuất sắc";
    if (diemTB >= 8) return "Giỏi";
    if (diemTB >= 6.5) return "Khá";
    if (diemTB >= 5) return "Trung bình";
    return "Yếu";
}

bool kiemTraTen(const string& ten) {
    for (int i = 0; i < ten.length(); i++) {
        char c = ten[i];
        if (c >= '0' && c <= '9') return false;
    }
    return true;
}

bool kiemTraDiem(double diem) {
    return (diem >= 0 && diem <= 10);
}

void nhapHocSinh(HocSinh& hs) {
    cout << "Họ tên: ";
    cin.ignore();
    getline(cin, hs.hoTen);
    
    while (!kiemTraTen(hs.hoTen)) {
        cout << "Tên không hợp lệ, nhập lại (không chứa số): ";
        getline(cin, hs.hoTen);
    }

    cout << "Điểm Toán: ";
    cin >> hs.diemToan;
    while (!kiemTraDiem(hs.diemToan)) {
        cout << "Điểm không hợp lệ, nhập lại (0-10): ";
        cin >> hs.diemToan;
    }

    cout << "Điểm Văn: ";
    cin >> hs.diemVan;
    while (!kiemTraDiem(hs.diemVan)) {
        cout << "Điểm không hợp lệ, nhập lại (0-10): ";
        cin >> hs.diemVan;
    }

    cout << "Điểm Ngoại ngữ: ";
    cin >> hs.diemNgoaiNgu;
    while (!kiemTraDiem(hs.diemNgoaiNgu)) {
        cout << "Điểm không hợp lệ, nhập lại (0-10): ";
        cin >> hs.diemNgoaiNgu;
    }

    // Tính điểm TB và xếp loại khi cần thiết (không lưu trong struct)
}

void xuatHocSinh(const HocSinh& hs) {
    double diemTB = tinhDiemTrungBinh(hs);  // Tính khi cần xuất
    cout << "Họ tên: " << hs.hoTen 
         << ", Điểm TB: " << fixed << setprecision(2) << diemTB
         << ", Xếp loại: " << xepLoai(diemTB) << endl;
}

void xuatDanhSach(const vector<HocSinh>& ds) {
    cout << "\nDANH SÁCH HỌC SINH:\n";
    for (int i = 0; i < ds.size(); i++) {
        xuatHocSinh(ds[i]);
    }
}

HocSinh timDiemCaoNhat(const vector<HocSinh>& ds) {
    HocSinh max = ds[0];
    double maxTB = tinhDiemTrungBinh(max);
    
    for (int i = 1; i < ds.size(); i++) {
        double currentTB = tinhDiemTrungBinh(ds[i]);
        if (currentTB > maxTB) {
            max = ds[i];
            maxTB = currentTB;
        }
    }
    return max;
}

HocSinh timDiemThapNhat(const vector<HocSinh>& ds) {
    HocSinh min = ds[0];
    double minTB = tinhDiemTrungBinh(min);
    
    for (int i = 1; i < ds.size(); i++) {
        double currentTB = tinhDiemTrungBinh(ds[i]);
        if (currentTB < minTB) {
            min = ds[i];
            minTB = currentTB;
        }
    }
    return min;
}

char chuyenThuong(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

vector<HocSinh> timKiemTheoTen(const vector<HocSinh>& ds, const string& ten) {
    vector<HocSinh> ketQua;
    
    for (int i = 0; i < ds.size(); i++) {
        const string& hoTen = ds[i].hoTen;
        bool found = false;
        
        for (int j = 0; j <= hoTen.length() - ten.length(); j++) {
            bool match = true;
            
            for (int k = 0; k < ten.length(); k++) {
                if (chuyenThuong(hoTen[j+k]) != chuyenThuong(ten[k])) {
                    match = false;
                    break;
                }
            }
            
            if (match) {
                found = true;
                break;
            }
        }
        
        if (found) ketQua.push_back(ds[i]);
    }
    
    return ketQua;
}

int main() {
    int n;
    cout << "Nhập số lượng học sinh: ";
    cin >> n;

    vector<HocSinh> ds(n);

    for (int i = 0; i < n; i++) {
        cout << "\nNhập thông tin học sinh thứ " << i+1 << ":\n";
        nhapHocSinh(ds[i]);
    }

    // 1. Xuất toàn bộ danh sách
    xuatDanhSach(ds);

    // 2. Xuất học sinh điểm cao nhất
    cout << "\nHỌC SINH ĐIỂM CAO NHẤT:\n";
    xuatHocSinh(timDiemCaoNhat(ds));

    // 3. Tìm kiếm theo tên
    string ten;
    cout << "\nNhập tên cần tìm: ";
    cin.ignore();
    getline(cin, ten);
    
    vector<HocSinh> ketQua = timKiemTheoTen(ds, ten);
    if (ketQua.empty()) {
        cout << "Không tìm thấy học sinh nào!\n";
    } else {
        cout << "Tìm thấy " << ketQua.size() << " kết quả:\n";
        xuatDanhSach(ketQua);
    }

    // 4. Xuất học sinh điểm thấp nhất (cuối cùng)
    cout << "\nHỌC SINH ĐIỂM THẤP NHẤT:\n";
    xuatHocSinh(timDiemThapNhat(ds));

    return 0;
}
