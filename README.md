# Tarea 3: Optimización de Rutas con Dijkstra
Curso: Estructura de Datos y Algoritmos
Integrantes:
Isadora Belair
Fernando Guaita
Guillermo Hidalgo

Descripción del problema
El objetivo de esta tarea fue implementar un sistema de optimización de rutas aéreas entre ciudades de América, utilizando estructuras de grafos con pesos y el algoritmo de Dijkstra.
A partir de un archivo con rutas disponibles (ciudad origen, ciudad destino, distancia), se construye un grafo no dirigido y se permite al usuario ingresar dos ciudades para encontrar el camino más corto entre ellas.

Cómo se resolvió:
Se implementó una lista de adyacencia para representar el grafo.
Cada ciudad se representa como un vértice, y cada ruta como una arista con peso (distancia).
Se aplicó el algoritmo de Dijkstra para encontrar la ruta más corta entre dos ciudades:
Se utilizó una tabla Estado que almacena la distancia mínima a cada ciudad, el nodo anterior y si el nodo fue visitado.
Se eligió iterativamente el nodo con menor distancia no visitado.
Se actualizó la distancia y la ciudad anterior de sus vecinos.
Se reconstruyó la ruta una vez alcanzado el destino.

Funcionalidades implementadas
Lectura de archivo rutas.txt y validación de datos de entrada.
Construcción dinámica del grafo.
Aplicación completa del algoritmo de Dijkstra.
Impresión detallada del camino mínimo y su distancia.
Modularización del código en archivos .c y .h, y uso de Makefile.


Observaciones
El programa asume que todos los identificadores de ciudad tienen exactamente 3 letras (como SCL, LIM, MIA).
Si no existe un camino posible entre las ciudades ingresadas, el programa informa correctamente al usuario.

