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
        Invalida(const char *mot) : motivo(mot) {}
        const char *por_que() const { return motivo; }

    private:
        const char *motivo;
    };

    explicit Fecha(int d = 0, int m = 0, int a = 0);
    Fecha(const char in[]);
    const char *cadena() const noexcept;

    Fecha &operator+=(int n);
    Fecha &operator-=(int n);
    Fecha &operator++();
    Fecha &operator--();
    Fecha operator++(int);
    Fecha operator--(int);
    Fecha operator+(int n) const;
    Fecha operator-(int n) const;

    int dia() const noexcept { return dia_; };
    int mes() const noexcept { return mes_; };
    int anno() const noexcept { return anno_; };

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

    std::tm *getTiempoDesc() const noexcept;
    const int extraeDia(const std::tm *t) const noexcept;
    const int extraeMes(const std::tm *t) const noexcept;
    const int extraeAnno(const std::tm *t) const noexcept;

    const bool esFechaValida() noexcept;
    const bool esDiaValido() noexcept;
    const bool esMesValido() noexcept;
    const bool esAnnoValido() noexcept;

    const int getDiasEnMes(int mes) noexcept;
    bool esAnnoBisiesto(int anno) noexcept;
};

bool operator==(const Fecha &A, const Fecha &B) noexcept;
bool operator!=(const Fecha &A, const Fecha &B) noexcept;
bool operator<(const Fecha &A, const Fecha &B) noexcept;
bool operator>(const Fecha &A, const Fecha &B) noexcept;
bool operator<=(const Fecha &A, const Fecha &B) noexcept;
bool operator>=(const Fecha &A, const Fecha &B) noexcept;

std::ostream &operator<<(std::ostream &out, const Fecha &F) noexcept;
std::istream &operator>>(std::istream &in, Fecha &F);

#endif //FECHA_H