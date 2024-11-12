#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <algorithm>  // для std::sort
using namespace std;

enum Specialty { KOMP_NAUKY, INFORMATYKA, MATEMATYKA_EKONOMIKA, FIZYKA_INFORMATYKA, TRUDOVE_NAVCHANNYA };
string specialtyStr[] = { "Комп’ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

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
    cout << "Введіть кількість студентів N: "; cin >> N;

    Student* p = new Student[N];
    int* indexArray = new int[N];

    int menuItem;
    do {
        cout << endl << "Виберіть дію:" << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - Обчислення відсотка відмінників" << endl;
        cout << " [4] - Виведення студентів, які отримали з фізики оцінку “5”" << endl;
        cout << " [5] - Впорядкування масиву студентів" << endl;
        cout << " [6] - Індексне впорядкування масиву" << endl;
        cout << " [7] - Бінарний пошук студента" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            cout << "Відсоток студентів, які навчаються на “відмінно”: "
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
            cout << "Індексний масив після впорядкування:" << endl;
            for (int i = 0; i < N; i++)
                cout << indexArray[i] << " ";
            cout << endl;
            break;
            break;
        case 7:
            {
                string prizv;
                int specialty, math_grade;
                cout << "Введіть прізвище: "; cin >> prizv;
                cout << "Введіть спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): "; cin >> specialty;
                cout << "Введіть оцінку з математики: "; cin >> math_grade;

                int pos = BinarySearch(p, indexArray, N, prizv, (Specialty)specialty, math_grade);
                if (pos != -1)
                    cout << "Студент знайдений в позиції: " << pos + 1 << endl;
                else
                    cout << "Студента не знайдено." << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "Невірний вибір! Введіть номер пункту меню." << endl;
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
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << " прізвище: "; getline(cin, p[i].prizv);
        cout << " курс: "; cin >> p[i].course;
        cout << " спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> specialty;
        p[i].specialty = (Specialty)specialty;
        cout << " оцінки фізики: "; cin >> p[i].evaluations_physics;
        cout << " оцінки математики: "; cin >> p[i].evaluations_mathematics;

        if (p[i].specialty == KOMP_NAUKY)
        {
            cout << " оцінка з програмування: "; cin >> p[i].evaluations_programming;
        }
        else if (p[i].specialty == INFORMATYKA)
        {
            cout << " оцінка з чисельних методів: "; cin >> p[i].evaluations_numerical_methods;
        }
        else
        {
            cout << " оцінка з педагогіки: "; cin >> p[i].evaluations_pedagogy;
        }
    }
}

void Print(Student* p, const int N)
{
    cout << "===============================================================================================================================================" << endl;
    cout << "| № | Прізвище        | Курс | Спеціальність            |    Фізики     |   Математики    |   Програмування   |  Чисельні методи | Педагогіка |" << endl;
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
    cout << "Студенти, які отримали з фізики оцінку “5”:" << endl;
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
        cout << "Немає студентів з оцінкою “5” з фізики." << endl;
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
