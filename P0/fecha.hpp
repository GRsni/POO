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

    Fecha operator++();
    Fecha operator--();
    Fecha operator++(int);
    Fecha operator--(int);
    friend Fecha operator+(Fecha f, int n)
    {
        f += n;
        return f;
    }
    friend Fecha operator-(Fecha f, int n)
    {
        f += -n;
        return f;
    }
    Fecha operator+=(int n);
    Fecha operator-=(int n);

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

    static const std::string nombreDias[7];
    int dia_, mes_, anno_;

    std::tm *getTiempoDesc();
    const int extraeDia(const std::tm *t);
    const int extraeMes(const std::tm *t);
    const int extraeAnno(const std::tm *t);

    const bool esFechaValida();
    const bool esDiaValido();
    const bool esMesValido();
    const bool esAnnoValido();

    char *getNombreDeDia(int dia);

    const int getDiasEnMes(int mes);
    bool esAnnoBisiesto(int anno);
};

#endif //FECHA_H