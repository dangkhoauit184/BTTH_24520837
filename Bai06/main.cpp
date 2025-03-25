#include <iostream>
using namespace std;

// Hàm đếm số lần xuất hiện của mảng A trong mảng B và liệt kê các vị trí bắt đầu
void countOccurrences(int* A, int n, int* B, int m) {
    int count = 0;
    int* positions = new int[m]; // Mảng động để lưu các vị trí bắt đầu
    int posIndex = 0; // Chỉ số của mảng positions

    // Duyệt qua mảng B để tìm các vị trí bắt đầu của A
    for (int i = 0; i <= m - n; ++i) {
        bool match = true;
        for (int j = 0; j < n; ++j) {
            if (B[i + j] != A[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            count++;
            positions[posIndex++] = i; // Lưu vị trí bắt đầu vào mảng positions
        }
    }

    // Xuất kết quả
    cout << "Số lần mảng A xuất hiện trong mảng B: " << count << endl;
    cout << "Danh sách các chỉ số bắt đầu: ";
    for (int i = 0; i < posIndex; ++i) {
        cout << positions[i] << " ";
    }
    cout << endl;

    // Giải phóng bộ nhớ động
    delete[] positions;
}

int main() {
    int n, m;
    cout << "Nhập số phần tử của mảng A và mảng B: ";
    cin >> n >> m;

    // Cấp phát động cho mảng A và B
    int* A = new int[n];
    int* B = new int[m];

    cout << "Nhập các phần tử của mảng A: ";
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    cout << "Nhập các phần tử của mảng B: ";
    for (int i = 0; i < m; ++i) {
        cin >> B[i];
    }

    // Gọi hàm đếm số lần xuất hiện
    countOccurrences(A, n, B, m);

    // Giải phóng bộ nhớ động
    delete[] A;
    delete[] B;

    return 0;
}
