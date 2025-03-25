#include <iostream>
using namespace std;

struct PhanSo {
    int tuso;
    int mauso;
};

// Hàm tìm ước chung lớn nhất (GCD)
int GCD(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return abs(a);
}

// Hàm nhập phân số
void Nhap(PhanSo &x) {
    cout << "Nhap tu so: ";
    cin >> x.tuso;

    cout << "Nhap mau so: ";
    cin >> x.mauso;

    // Nhập lại nếu mẫu số bằng 0
    while (x.mauso == 0) {
        cout << "Mau so khac 0, vui long nhap lai!\n";
        cout << "Nhap mau so: ";
        cin >> x.mauso;
    }
}

// Hàm rút gọn phân số
void RutGon(PhanSo &ps) {
    int gcd = GCD(ps.tuso, ps.mauso);
    ps.tuso /= gcd;
    ps.mauso /= gcd;

    // Đảm bảo mẫu số luôn dương
    if (ps.mauso < 0) {
        ps.tuso = -ps.tuso;
        ps.mauso = -ps.mauso;
    }
}

// Hàm xuất phân số
void Xuat(const PhanSo &x) {
    if (x.tuso == 0) {
        cout << 0;
    } else if (x.mauso == 1) {
        cout << x.tuso;
    } else {
        cout << x.tuso << "/" << x.mauso;
    }
}

// Hàm tính tổng hai phân số
PhanSo Tong(const PhanSo &ps1, const PhanSo &ps2) {
    PhanSo ketQua;
    ketQua.tuso = ps1.tuso * ps2.mauso + ps2.tuso * ps1.mauso;
    ketQua.mauso = ps1.mauso * ps2.mauso;
    RutGon(ketQua);
    return ketQua;
}

// Hàm tính hiệu hai phân số
PhanSo Hieu(const PhanSo &ps1, const PhanSo &ps2) {
    PhanSo ketQua;
    ketQua.tuso = ps1.tuso * ps2.mauso - ps2.tuso * ps1.mauso;
    ketQua.mauso = ps1.mauso * ps2.mauso;
    RutGon(ketQua);
    return ketQua;
}

// Hàm tính tích hai phân số
PhanSo Tich(const PhanSo &ps1, const PhanSo &ps2) {
    PhanSo ketQua;
    ketQua.tuso = ps1.tuso * ps2.tuso;
    ketQua.mauso = ps1.mauso * ps2.mauso;
    RutGon(ketQua);
    return ketQua;
}

// Hàm tính thương hai phân số
PhanSo Thuong(const PhanSo &ps1, const PhanSo &ps2) {
    PhanSo ketQua;
    // Kiểm tra mẫu số của phân số thứ hai khác 0
    if (ps2.tuso == 0) {
        cout << "Khong the chia cho 0!\n";
        ketQua.tuso = 0;
        ketQua.mauso = 1;
    } else {
        ketQua.tuso = ps1.tuso * ps2.mauso;
        ketQua.mauso = ps1.mauso * ps2.tuso;
        RutGon(ketQua);
    }
    return ketQua;
}

int main() {
    PhanSo ps1, ps2;

    cout << "Nhap phan so thu nhat:\n";
    Nhap(ps1);
    RutGon(ps1);

    cout << "Nhap phan so thu hai:\n";
    Nhap(ps2);
    RutGon(ps2);

    cout << "Phan so thu nhat: ";
    Xuat(ps1);
    cout << endl;

    cout << "Phan so thu hai: ";
    Xuat(ps2);
    cout << endl;

    // Tính tổng
    PhanSo tong = Tong(ps1, ps2);
    cout << "Tong hai phan so: ";
    Xuat(tong);
    cout << endl;

    // Tính hiệu
    PhanSo hieu = Hieu(ps1, ps2);
    cout << "Hieu hai phan so: ";
    Xuat(hieu);
    cout << endl;

    // Tính tích
    PhanSo tich = Tich(ps1, ps2);
    cout << "Tich hai phan so: ";
    Xuat(tich);
    cout << endl;

    // Tính thương
    PhanSo thuong = Thuong(ps1, ps2);
    cout << "Thuong hai phan so: ";
    Xuat(thuong);
    cout << endl;

    return 0;
}
