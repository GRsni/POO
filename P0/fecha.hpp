#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <ctime>

class Fecha
{
public:
    static const int AnnoMaximo = 2037;
    static const int AnnoMinimo = 1902;

    class Invalida
    {
    public:
        Invalida(const char mot[]);
        void por_que();

    private:
        const char *motivo;
    };

    explicit Fecha(int d = 0, int m = 0, int a = 0);
    Fecha(const char in[]);
    operator const char *() const;

    Fecha operator++();
    Fecha operator--();
    Fecha operator++(int);
    Fecha operator--(int);
    Fecha operator+(int n);
    Fecha operator-(int n);
    Fecha operator+=(int n);
    Fecha operator-=(int n);

    bool operator==(const Fecha &F);
    bool operator!=(const Fecha &F);
    bool operator<(const Fecha &F);
    bool operator>(const Fecha &F);
    bool operator<=(const Fecha &F);
    bool operator>=(const Fecha &F);

    int dia() const { return dia_; };
    int mes() const { return mes_; };
    int anno() const { return anno_; };
    void imprimeFecha() const;

    ~Fecha() = default;

private:
    enum MES
    {
        ENERO = 1,
        FEBRERO,
        MARZO,
        ABRIL,
        MAYO,
        JUNIO,
        JULIO,
        AGOSTO,
        SEPTIEMBRE,
        OCTUBRE,
        NOVIEMBRE,
        DICIEMBRE
    };

    int dia_, mes_, anno_;
    mutable char salida[35];

    std::tm *getTiempoDesc() const;
    std::tm *getTiempoDescNormalizado(const int d, const int m, const int a) const;
    int extraeDia(const std::tm *t) const;
    int extraeMes(const std::tm *t) const;
    int extraeAnno(const std::tm *t) const;

    const bool esFechaValida();
    const bool esDiaValido();
    const bool esMesValido();
    const bool esAnnoValido();

    char *getNombreDeDia(int dia);

    const int getDiasEnMes(int mes);
    bool esAnnoBisiesto(int anno);
};

#endif //FECHA_H