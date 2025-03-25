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

// Hàm so sánh hai phân số
int SoSanh(const PhanSo &ps1, const PhanSo &ps2) {
    // Quy đồng mẫu số
    int tu1 = ps1.tuso * ps2.mauso;
    int tu2 = ps2.tuso * ps1.mauso;

    if (tu1 > tu2) {
        return 1; // Phân số 1 lớn hơn
    } else if (tu1 < tu2) {
        return -1; // Phân số 2 lớn hơn
    } else {
        return 0; // Hai phân số bằng nhau
    }
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

    // So sánh hai phân số
    int ketQua = SoSanh(ps1, ps2);
    if (ketQua == 1) {
        cout << "Phan so lon nhat la: ";
        Xuat(ps1);
    } else if (ketQua == -1) {
        cout << "Phan so lon nhat la: ";
        Xuat(ps2);
    } else {
        cout << "Hai phan so bang nhau.";
    }
    cout << endl;

    return 0;
}
