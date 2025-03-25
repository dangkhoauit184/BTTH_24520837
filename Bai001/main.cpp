#include <iostream>
using namespace std;

struct PhanSo {
    int tuso;
    int mauso;
};

// Hàm tìm ước chung lớn nhất (GCD)
int GCD(int a, int b) {
    while(b != 0) {
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
    while(x.mauso == 0) {
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
    if(ps.mauso < 0) {
        ps.tuso = -ps.tuso;
        ps.mauso = -ps.mauso;
    }
}

// Hàm xuất phân số theo yêu cầu
void Xuat(const PhanSo &x) {
    // Nếu tử số = 0 -> in ra 0
    if(x.tuso == 0) {
        cout << 0;
        return;
    }
    // Nếu mẫu số = 1 -> chỉ in ra tử số
    else if(x.mauso == 1) {
        cout << x.tuso;
        return;
    }
    // Ngược lại -> in dạng t/m
    cout << x.tuso << "/" << x.mauso;
}

int main() {
    PhanSo ps1;
    cout << "Nhap phan so" << endl;
    Nhap(ps1);

    cout << "Phan so vua nhap la: ";
    Xuat(ps1);
    cout << endl;

    // Rút gọn rồi xuất
    RutGon(ps1);
    cout << "Phan so sau khi rut gon la: ";
    Xuat(ps1);
    cout << endl;

    return 0;
}
