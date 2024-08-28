#include <SFML/Graphics.hpp>


#include "../Headers/Window.h"

#include <iostream>
#include <iomanip>


// 1. �������� ����� ����� Font � ������� �������� ����� ��������� ����� ��� ���� ���������
// 2(+). ������� ����� ������� ������� ������������ ����
// 3(�� ������ �����������, �� ��������). ������� ������������ ��������� ����� ������� ������ � ������ �� ������
// 4. ������� ����� ��� ������ � ��������� ��������� �������
// 5. ������� ����������� �������� �� ���������� �� ������
// 6(�� ������ �����������, �� ��������). �������� � ����������� ������ (��������). ����� ����������� �������� �� ������� ������������ ����
//      �����, ��� ��� ����� ������� �������, ����� ������ ������ ����������� ��������� ������� (��� � ����),
//      � ����� ������, ������ ���� �� ����� ���������� ���������(���� ��� ������ ���)
// 7.(+) ������� ������������ ������� �������� ������, ��� ��� ����� ������� ������� ������� ����, ���� ������ ���� �������� ����.
// 8.(+) ������� ������������ ���������� � �������� ������, ��� ��������� � �����������
// 9.(+) ������� ����������� ������� ��� ������ ����
// 10. ����������� � ��������� ��� ������, �� ��������� �������
// 11. ������� �������� GUI, ��� ����� ������������ debug ����������, ������ � ��������, �����-��
//      ������ ���������
// 12. ������� ����������� ������ ���
// 13. ������� ��������� ����������� ����, � ���������� ���������� � ���������
// 14. ������� ������ � ����������� � ��������� �������, ����� �������� �� �� �������
//      (�� ������� �����) ��� �� �������� �� ���� ������ ������� ����������
// 15. ������� ���, ������������ ������, ������ ����� �������� �� ������� �����


// Images
// https://deep-fold.itch.io/space-background-generator (VPN)
// https://deep-fold.itch.io/pixel-planet-generator



int main() {

    MyWindow::Window window;
    window.Run();

    return 0;
}