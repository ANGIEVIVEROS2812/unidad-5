#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CONTENEDORES 30

void registrarPesos(int pesos[], int *cantidad, int *ordenado);
void generarPesosAleatorios(int pesos[], int *cantidad, int *ordenado);
void mostrarPesos(int pesos[], int cantidad);
void swap(int *a, int *b);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void merge(int arr[], int izquierda, int medio, int derecha);
void mergeSort(int arr[], int izquierda, int derecha);
void shellSort(int arr[], int n);
int busquedaBinaria(int arr[], int n, int objetivo);

int main()
{
    int pesos[MAX_CONTENEDORES];
    int cantidad = 0;
    int ordenado = 0;
    int opcion;

    srand(time(NULL));

    do
    {
        printf("\n========================================\n");
        printf("SISTEMA DE ORGANIZACION DE CONTENEDORES\n");
        printf("MUELLE DE CARGA\n");
        printf("========================================\n");
        printf("1. Registrar peso de contenedores manualmente\n");
        printf("2. Generar pesos aleatorios de contenedores\n");
        printf("3. Mostrar contenedores registrados\n");
        printf("4. Ordenar contenedores Metodo 1 (Quick Sort)\n");
        printf("5. Ordenar contenedores Metodo 2 (Merge Sort)\n");
        printf("6. Ordenar contenedores Metodo 3 (Shell Sort)\n");
        printf("7. Buscar contenedor\n");
        printf("8. Salir\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1:
                registrarPesos(pesos, &cantidad, &ordenado);
                break;

            case 2:
                generarPesosAleatorios(pesos, &cantidad, &ordenado);
                break;

            case 3:
                mostrarPesos(pesos, cantidad);
                break;

            case 4:
                if (cantidad == 0)
                {
                    printf("No hay contenedores registrados.\n");
                }
                else
                {
                    quickSort(pesos, 0, cantidad - 1);
                    ordenado = 1;
                    printf("Contenedores ordenados con Quick Sort.\n");
                }
                break;

            case 5:
                if (cantidad == 0)
                {
                    printf("No hay contenedores registrados.\n");
                }
                else
                {
                    mergeSort(pesos, 0, cantidad - 1);
                    ordenado = 1;
                    printf("Contenedores ordenados con Merge Sort.\n");
                }
                break;

            case 6:
                if (cantidad == 0)
                {
                    printf("No hay contenedores registrados.\n");
                }
                else
                {
                    shellSort(pesos, cantidad);
                    ordenado = 1;
                    printf("Contenedores ordenados con Shell Sort.\n");
                }
                break;

            case 7:
            {
                int pesoBuscado;
                int posicion;

                if (cantidad == 0)
                {
                    printf("No hay contenedores registrados.\n");
                }
                else if (ordenado == 0)
                {
                    printf("Debe ordenar el arreglo antes de realizar la busqueda binaria.\n");
                }
                else
                {
                    printf("Ingrese el peso a buscar: ");
                    scanf("%d", &pesoBuscado);

                    posicion = busquedaBinaria(pesos, cantidad, pesoBuscado);

                    if (posicion != -1)
                    {
                        printf("Contenedor encontrado en la posicion %d.\n", posicion + 1);
                    }
                    else
                    {
                        printf("Contenedor no encontrado.\n");
                    }
                }
                break;
            }

            case 8:
                printf("Programa finalizado.\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 8);

    return 0;
}

void registrarPesos(int pesos[], int *cantidad, int *ordenado)
{
    int n;
    int i;

    printf("Cantidad de contenedores (1-%d): ", MAX_CONTENEDORES);
    scanf("%d", &n);

    if (n < 1 || n > MAX_CONTENEDORES)
    {
        printf("Cantidad invalida.\n");
        return;
    }

    *cantidad = n;

    for (i = 0; i < n; i++)
    {
        printf("Peso del contenedor %d (kg): ", i + 1);
        scanf("%d", &pesos[i]);
    }

    *ordenado = 0;
    printf("Pesos registrados correctamente.\n");
}

void generarPesosAleatorios(int pesos[], int *cantidad, int *ordenado)
{
    int n;
    int i;

    printf("Cantidad de contenedores a generar (1-%d): ", MAX_CONTENEDORES);
    scanf("%d", &n);

    if (n < 1 || n > MAX_CONTENEDORES)
    {
        printf("Cantidad invalida.\n");
        return;
    }

    *cantidad = n;

    for (i = 0; i < n; i++)
    {
        pesos[i] = 1000 + rand() % 39001;
    }

    *ordenado = 0;
    printf("Pesos generados correctamente.\n");
}

void mostrarPesos(int pesos[], int cantidad)
{
    int i;

    if (cantidad == 0)
    {
        printf("No hay contenedores registrados.\n");
        return;
    }

    printf("\nListado de contenedores:\n");

    for (i = 0; i < cantidad; i++)
    {
        printf("Contenedor %d: %d kg\n", i + 1, pesos[i]);
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low;
    int j;

    for (j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[i], &arr[high]);

    return i;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int p = partition(arr, low, high);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

void merge(int arr[], int izquierda, int medio, int derecha)
{
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    int L[n1];
    int R[n2];

    int i, j, k;

    for (i = 0; i < n1; i++)
        L[i] = arr[izquierda + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    i = 0;
    j = 0;
    k = izquierda;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

void mergeSort(int arr[], int izquierda, int derecha)
{
    if (izquierda < derecha)
    {
        int medio = izquierda + (derecha - izquierda) / 2;

        mergeSort(arr, izquierda, medio);
        mergeSort(arr, medio + 1, derecha);

        merge(arr, izquierda, medio, derecha);
    }
}

void shellSort(int arr[], int n)
{
    int gap;
    int i;
    int j;
    int temp;

    for (gap = n / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < n; i++)
        {
            temp = arr[i];

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}

int busquedaBinaria(int arr[], int n, int objetivo)
{
    int izquierda = 0;
    int derecha = n - 1;

    while (izquierda <= derecha)
    {
        int medio = (izquierda + derecha) / 2;

        if (arr[medio] == objetivo)
        {
            return medio;
        }

        if (arr[medio] < objetivo)
        {
            izquierda = medio + 1;
        }
        else
        {
            derecha = medio - 1;
        }
    }

    return -1;
}