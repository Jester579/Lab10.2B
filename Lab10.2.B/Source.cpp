#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <algorithm>  // ��� std::sort
using namespace std;

enum Specialty { KOMP_NAUKY, INFORMATYKA, MATEMATYKA_EKONOMIKA, FIZYKA_INFORMATYKA, TRUDOVE_NAVCHANNYA };
string specialtyStr[] = { "��������� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student
{
    string prizv;
    unsigned course;
    Specialty specialty;
    int evaluations_physics;
    int evaluations_mathematics;
    union
    {
        int evaluations_programming;
        int evaluations_numerical_methods;
        int evaluations_pedagogy;
    };
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
double ExcellentStudents(Student* p, const int N);
void PhysicsExcellent(Student* p, const int N);
void SortArray(Student* p, const int N);
void CreateIndexArray(Student* p, int* indexArray, const int N);
int BinarySearch(Student* p, int* indexArray, const int N, string prizv, Specialty specialty, int math_grade);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� �������� N: "; cin >> N;

    Student* p = new Student[N];
    int* indexArray = new int[N];

    int menuItem;
    do {
        cout << endl << "������� ��:" << endl;
        cout << " [1] - �������� ����� � ���������" << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ���������� ������� ��������" << endl;
        cout << " [4] - ��������� ��������, �� �������� � ������ ������ �5�" << endl;
        cout << " [5] - ������������� ������ ��������" << endl;
        cout << " [6] - �������� ������������� ������" << endl;
        cout << " [7] - �������� ����� ��������" << endl;
        cout << " [0] - ����� �� ���������� ������ ��������" << endl;
        cout << "������ ��������: "; cin >> menuItem;
        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            cout << "³������ ��������, �� ���������� �� �������: "
                 << ExcellentStudents(p, N) << "%" << endl;
            break;
        case 4:
            PhysicsExcellent(p, N);
            break;
        case 5:
            SortArray(p, N);
            Print(p, N);
            break;
        case 6:
            CreateIndexArray(p, indexArray, N);
            cout << "��������� ����� ���� �������������:" << endl;
            for (int i = 0; i < N; i++)
                cout << indexArray[i] << " ";
            cout << endl;
            break;
            break;
        case 7:
            {
                string prizv;
                int specialty, math_grade;
                cout << "������ �������: "; cin >> prizv;
                cout << "������ ������������ (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): "; cin >> specialty;
                cout << "������ ������ � ����������: "; cin >> math_grade;

                int pos = BinarySearch(p, indexArray, N, prizv, (Specialty)specialty, math_grade);
                if (pos != -1)
                    cout << "������� ��������� � �������: " << pos + 1 << endl;
                else
                    cout << "�������� �� ��������." << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "������� ����! ������ ����� ������ ����." << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    delete[] indexArray;
    return 0;
}

void Create(Student* p, const int N)
{
    int specialty;
    for (int i = 0; i < N; i++)
    {
        cout << "������� � " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << " �������: "; getline(cin, p[i].prizv);
        cout << " ����: "; cin >> p[i].course;
        cout << " ������������ (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> specialty;
        p[i].specialty = (Specialty)specialty;
        cout << " ������ ������: "; cin >> p[i].evaluations_physics;
        cout << " ������ ����������: "; cin >> p[i].evaluations_mathematics;

        if (p[i].specialty == KOMP_NAUKY)
        {
            cout << " ������ � �������������: "; cin >> p[i].evaluations_programming;
        }
        else if (p[i].specialty == INFORMATYKA)
        {
            cout << " ������ � ��������� ������: "; cin >> p[i].evaluations_numerical_methods;
        }
        else
        {
            cout << " ������ � ���������: "; cin >> p[i].evaluations_pedagogy;
        }
    }
}

void Print(Student* p, const int N)
{
    cout << "===============================================================================================================================================" << endl;
    cout << "| � | �������        | ���� | ������������            |    Գ����     |   ����������    |   �������������   |  ������� ������ | ��������� |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << i + 1 << " | "
            << setw(14) << left << p[i].prizv
            << "| " << setw(4) << right << p[i].course << " | "
            << setw(24) << left << specialtyStr[p[i].specialty] << " | "
            << setw(13) << right << p[i].evaluations_physics << " | "
            << setw(16) << right << p[i].evaluations_mathematics << " | ";

        if (p[i].specialty == KOMP_NAUKY)
            cout << setw(14) << right << p[i].evaluations_programming << " | " << setw(15) << " " << " | " << setw(10) << " ";
        else if (p[i].specialty == INFORMATYKA)
            cout << setw(14) << " " << " | " << setw(15) << right << p[i].evaluations_numerical_methods << " | " << setw(10) << " ";
        else
            cout << setw(14) << " " << " | " << setw(15) << " " << " | " << setw(10) << right << p[i].evaluations_pedagogy;

        cout << " |" << endl;
    }
    cout << "===============================================================================================================================================" << endl;
}
double ExcellentStudents(Student* p, const int N)
{
    int countExcellent = 0;
    for (int i = 0; i < N; i++)
    {
        bool isExcellent = p[i].evaluations_physics == 5 && p[i].evaluations_mathematics == 5;
        if (p[i].specialty == KOMP_NAUKY)
            isExcellent = isExcellent && (p[i].evaluations_programming == 5);
        else if (p[i].specialty == INFORMATYKA)
            isExcellent = isExcellent && (p[i].evaluations_numerical_methods == 5);
        else
            isExcellent = isExcellent && (p[i].evaluations_pedagogy == 5);

        if (isExcellent)
            countExcellent++;
    }
    return (double)countExcellent / N * 100;
}

void PhysicsExcellent(Student* p, const int N)
{
    cout << "��������, �� �������� � ������ ������ �5�:" << endl;
    bool found = false;
    for (int i = 0; i < N; i++)
    {
        if (p[i].evaluations_physics == 5)
        {
            cout << p[i].prizv << endl;
            found = true;
        }
    }
    if (!found)
        cout << "���� �������� � ������� �5� � ������." << endl;
}

void SortArray(Student* p, const int N)
{
    sort(p, p + N, [](Student a, Student b) {
        if (a.specialty != b.specialty)
            return a.specialty < b.specialty;
        if (a.evaluations_mathematics != b.evaluations_mathematics)
            return a.evaluations_mathematics < b.evaluations_mathematics;
        return a.prizv < b.prizv;
    });
}

void CreateIndexArray(Student* p, int* indexArray, const int N)
{
    for (int i = 0; i < N; i++)
        indexArray[i] = i;

    sort(indexArray, indexArray + N, [p](int a, int b) {
        if (p[a].specialty != p[b].specialty)
            return p[a].specialty < p[b].specialty;  

        if (p[a].evaluations_mathematics != p[b].evaluations_mathematics)
            return p[a].evaluations_mathematics > p[b].evaluations_mathematics;  

        return p[a].prizv < p[b].prizv;  
        });

}


int BinarySearch(Student* p, int* indexArray, const int N, string prizv, Specialty specialty, int math_grade)
{
    int left = 0, right = N - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        int idx = indexArray[mid];

        if (p[idx].specialty == specialty && p[idx].evaluations_mathematics == math_grade && p[idx].prizv == prizv)
            return idx;

        if (p[idx].specialty < specialty || 
           (p[idx].specialty == specialty && p[idx].evaluations_mathematics < math_grade) ||
           (p[idx].specialty == specialty && p[idx].evaluations_mathematics == math_grade && p[idx].prizv < prizv))
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
