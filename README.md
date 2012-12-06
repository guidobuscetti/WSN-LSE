WSN-LSE
=======
Version 0.7:
- Cambios en main.c, fijo.c, movil.c. Ahora las rutinas de los nodos fijos y moviles se activan tras interrupciones externas. Para ahorrar energia, cambian a modo Sleep(fijos) o DeepSleep(movil).
- Cambios en cc2520 (inicializacion para configurar pin 5 de cc2520).
- Cambios en cc2520-mac.c. Ahora ccFrameRx() no inicia la radio. Debe iniciarse antes.

Version 0.5:
- Actualizados valores de ajuste para RSSI

Version 0.4:
- Corregido config.h
- Corregido main.c 
- Corregido fijo.c
- Corregido movil.c

Version 0.2:
- Agregado fijo.h y fijo.c
- Arreglados problemas con includes
- Modificado main.c: mains para nodos fijos y moviles
- Agregado config.h : configuraciones de direcciones de red

Version 0.1:
- Arreglados errores de compilacion
- Cambiado el nombre del proyecto

Version 0:
- Agregada CMSIS 2p00 LPC17XX
- Agregada DSPLIB CM3 2v10
- Agregado cc2520-lpc1769:
      - Agregado main() para nodo movil en main.c
      - Agregado stack de Pablo : cc2520.h, cc2520.c, cc2520-mac.h, cc2520-mac.c, includes.h
      - Agregado movil.c y movil.h : Rutina y trilateracion de nodo movil
      - Agregado rssi.c y rssi.h : algoritmos de conversion de RSSI (dBm) a distancia (m)

