#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define no_of_char 256 // no_of_char - количество символов во входном алфавите
class rabin
{
public:
    void search(string pat, string txt, int q);
    int get_next_state(string pat, int m, int state, int x);
    void get_table(string pat, int m, int TF[][no_of_char]);
    void search_string_finite(string pat, string text);
    void bad_char(string pat, int size, int table[no_of_char]);
    void search_string(string text, string pat);
    void KMP(string text, string pattern);
};
void rabin::search(string pat, string txt, int q) //Алгоритм Рабина-Карпа
{
    int M = pat.length();
    int N = txt.length();
    int i, j;
    int p = 0; //Хеш функция для образца
    int t = 0; //Хеш функция для текста
    int h = 1;
    int count;
    for (i = 0; i < M - 1; i++) //Значение h будет "pow (no_of_char, M-1)% q".
        h = (h * no_of_char) % q;
    for (i = 0; i < M; i++)
    {
        p = (no_of_char * p + pat[i]) % q; // По формуле: hash=(hash+char*no_of_char^(m-i-1))%q
        t = (no_of_char * t + txt[i]) % q;
    }
    for (i = 0; i <= N - M; i++)
    {
        count++;
        if (p == t)
        {

            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                {
                    break;
                }
            }
            if (j == M) // Если p == t и pat[0...M-1] = txt[i, i+1, ...i+M-1]
            {
                cout << "  Доспутимый сдвиг: " << i << endl;
                cout << "  Число сравнений: " << count << endl;
            }
        }
        if (i < N - M) //Вычислить значение хеш-функции для следующего окна текста: Удалить
                       //ведущая цифра, добавляем конечную цифру
        {
            t = (no_of_char * (t - txt[i] * h) + txt[i + M]) % q; //hash( txt[s+1 .. s+m] ) = ( no_of_char *( hash( txt[s .. s+m-1]) – txt[s]*h ) + txt[s + m] ) mod q
            if (t < 0)
                t = (t + q);
        }
    }
}
int rabin::get_next_state(string pat, int m, int state, int x) // функция нахождение следующего состояния
{
    if ((state < m) && (x == pat[state]))
        return state + 1;
    int k, i;
    for (k = state; k > 0; k--)
    {
        if (pat[k - 1] == x)
        {
            for (i = 0; i < k - 1; i++)
                if (pat[i] != pat[state - k + 1 + i])
                    break;
            if (i == k - 1)
                return k;
        }
    }
    return 0;
}
void rabin::get_table(string pat, int m, int TF[][no_of_char]) //создание таблицы состояний
{
    int state, x;
    for (state = 0; state <= m; ++state)
        for (x = 0; x < no_of_char; ++x)
            TF[state][x] = get_next_state(pat, m, state, x); //двухмерный массив
}
void rabin::search_string_finite(string pat, string text) //Алгоритм поиска подстрок с помощью конечных автоматов
{
    int n = text.length();
    int m = pat.length();
    int TF[m + 1][no_of_char];
    get_table(pat, m, TF);
    int count = 0;
    int i, state = 0;
    for (i = 0; i < n; i++)
    {
        count++;
        state = TF[state][text[i]];
        if (state == m)
        {
            cout << " Доспутимый сдвиг: " << i - m + 1 << endl;
            cout << " Число сравнений: " << count << endl;
        }
        else
            count++;
    }
    if (count == n)
    {
        cout << "Не найден образец " << endl;
    }
}
void rabin::bad_char(string pat, int size, int table[no_of_char])
{
    int i;
    for (i = 0; i < no_of_char; i++)
        table[i] = -1; // Инициализировать все вхождения как -1
    for (i = 0; i < size; i++)
        table[(int)pat[i]] = i; //Заполните фактическое значение последнего вхождения символы
}
void rabin::search_string(string text, string pat) //Алгоритм Бойера-Мура
{
    int n = text.length();
    int m = pat.length();
    int table[no_of_char];
    bad_char(pat, m, table);
    int count = 0;
    int s = 0; //позиция нахождения образца в тексте
    while (s <= (n - m))
    {
        count++;
        int j = m - 1;
        while ((j >= 0) && (pat[j] == text[s + j]))
            j--;
        if (j < 0)
        {
            cout << " Доспутимый сдвиг: " << s << endl;
            cout << " Число сравнений: " << count << endl;

            s += (s + m < n) ? (m - table[text[s + m]]) : 1;
        }
        else
            s += max(1, j - table[text[s + j]]);
    }
}
void rabin::KMP(string text, string pattern) //функция реализации алгоритма КМП
{
    int m = pattern.length();
    int n = text.length();
    vector<int> pi(m); // массив п
    pi[0] = 0;
    int i = 1;
    int j = 0;
    for (int k = 0; k < m; k++)
    {
        if (pattern[i] == pattern[j])
        {
            pi[i] = j + 1;
            i++;
            j++;
        }
        else if (j == 0)
        {
            pi[i] = 0;
            i++;
        }
        else
        {
            j = pi[j - 1];
        }
    }
    int k = 0;
    int l = 0;
    int count = 0; //число сравнений
    while (k < n)
    {
        if (text[k] == pattern[l])
        {
            k++;
            l++;
            count++;
            if (l == m)
            {
                cout << " Доспутимый сдвиг: " << k - m << endl;
                cout << " Число сравнений: " << count << endl;
            }
        }
        else if (l == 0)
        {
            ++k;
            count++;
        }
        else
        {
            l = pi[l - 1];
        }
    }
}
int main()
{
    rabin a;
    string text, pat;
    cout << " Исходная строка: ";
    cin >> text;
    cout << " Образец: ";
    cin >> pat;
    int q = 101;
    cout << endl;
    cout << " Алгоритм КМП: " << endl;
    a.KMP(text, pat);
    cout << endl;
    cout << " Алгоритм Рабина-Карпа: " << endl;
    a.search(pat, text, q);
    cout << endl;
    cout << " Алгоритм поиска подстрок с помощью конечных автоматов: " << endl;
    a.search_string_finite(pat, text);
    cout << endl;
    cout << " Алгоритм Бойера-Мура: " << endl;
    a.search_string(text, pat);
    return 0;
}
