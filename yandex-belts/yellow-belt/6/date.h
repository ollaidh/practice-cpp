class Date {
public:
    Date();

    Date(int year, int month, int day);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

private:
    int m_year;
    int m_month;
    int m_day;
};