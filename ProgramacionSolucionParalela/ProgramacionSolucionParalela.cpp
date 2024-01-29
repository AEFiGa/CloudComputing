// Se importan las librerías a utilizar
#include <iostream>
#include <omp.h>

// Se definen las variables de cantidad de elementos, elementos a cargar en hilos y elementos a mostar en la validación
#define N 1000
#define chunk 100
#define mostrar 10

// Se declara la función para imprimir un arreglo
void imprimeArreglo(float* d);

int main()
{
    // Verificamos que Open MP esté disponible con  la librería importada
# ifdef _OPENMP
    std::cout << "Open MP disponible y funcionando\n\n" << std::endl;
# endif

    // Se definen los arreglos que se van a sumar y el entero con que se iterará para asignar valores
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    // Se asignan valores a cada uno de los valores de los arreglos a sumar
    for (i = 0; i < N; i++)
    {
        a[i] = i * 10 + 1;
        b[i] = (i + 1) * 2;
    }

    // Se definen la cantidad de elementos a cargar en los hilos para las operaciones paralelas
    int pedazos = chunk;

    // Se realiza la suma utilizando las operaciones en paralelo de Open MP
#pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    // Se imprimen los elementos de los arreglos a, b y c para verificar que se realizan las operaciones de manera correcta.
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << " " << std::endl;
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}

// Función para imprimir los elementos de los arreglos
void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        if (x < mostrar - 1)
        {
            std::cout << d[x] << " - ";
        }
        else
        {
            std::cout << d[x];
        }
    std::cout << std::endl;
}