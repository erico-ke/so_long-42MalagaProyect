# So_Long

**So_Long** es un proyecto de la escuela 42 en el que se crea un juego de aventura en 2D usando la librería gráfica **MLX42**. El juego consiste en mover un personaje a través de un mapa, interactuar con objetos, recolectar elementos y alcanzar la salida.

## Requisitos

- **C**: El proyecto debe ser desarrollado en el lenguaje de programación C.
- **MLX42**: Se debe usar la librería MiniLibX para la creación de la ventana gráfica, renderizado y gestión de eventos.
- **Norma 42**: El código debe cumplir con las normas de estilo de código de la escuela 42.

## Objetivo del Proyecto

El objetivo principal de **So_Long** es desarrollar un juego en 2D con los siguientes requisitos funcionales:

1. **Mapa**: El jugador debe poder moverse por un mapa que está compuesto por diferentes caracteres. 
   - **'1'**: Paredes del mapa.
   - **'0'**: Espacios vacíos en el mapa donde el jugador puede caminar.
   - **'P'**: Posición inicial del jugador.
   - **'E'**: La salida del mapa.
   - **'C'**: Ítems que el jugador debe recolectar.

2. **Movimiento del Jugador**: El jugador debe poder moverse usando las teclas `Up`, `Left`, `Rigth`, `Down`.

3. **Objetos**: El jugador debe poder recolectar los objetos **'C'** para alcanzar el objetivo de completar el mapa.

4. **Salida**: El jugador debe llegar a la casilla **'E'** para finalizar el juego, pero solo después de haber recogido todos los objetos **'C'**.

5. **Eventos**: El juego debe ser interactivo, permitiendo al jugador mover al personaje, cerrar la ventana con `ESC` y manejar eventos gráficos.

## Instrucciones de Ejecución

### Requisitos de compilación

1. Clonar el repositorio del proyecto.
   ```bash
   git@github.com:erico-ke/so_long-42MalagaProyect.git

2. Navegar al directorio del proyecto, compilar el proyecto y ejecutarlo.
```
  cd so_long ;
  make ;
  ./so_long maps/<map_file.ber>
