import java.io.*;
import java.util.Scanner;

// GJM3C-CFPQK-YP3M3-4VGDR-WPMKZ
public class proyecto {
  // atributos
  int pip;
  int tiempoLlegada;
  int tiempoEjecucion;
  int prioridad;
  boolean finalizado = false;

  // metodo
  public static void main(String[] args) throws Exception {
    Scanner leer = new Scanner(System.in);
    proyecto proceso[] = new proyecto[20];
    int i, k, j;
    int[] tem = new int[5];
    ;
    String prueba = "";
    File doc = new File("E:/irvyn/Documents/GitHub/SO1/proyecto1/datos3.txt");

    BufferedReader obj = new BufferedReader(new FileReader(doc));

    j = 0;
    k = 0;
    while ((i = obj.read()) != -1) {
      if (i == 59) {
        // -1 porque j se le suma uno entonces j se vuelve =0
        j = -1;

        // crea proceso
        proceso[k] = new proyecto();
        proceso[k].pip = tem[0];
        proceso[k].tiempoLlegada = tem[1];
        proceso[k].tiempoEjecucion = tem[2];
        proceso[k].prioridad = tem[3];

        k++;
      }
      if (i != 44 && i != 59) {
        i = i - 48;
        prueba += i + "";

        tem[j] = Integer.parseInt(prueba);
      } else {
        j++;
        prueba = "";
      }
    }

    System.out.println("pip\tTlle\tTexe\tprioridad");
    for (i = 0; i < k; i++) {
      System.out.println(proceso[i].pip + "\t" + proceso[i].tiempoLlegada + "\t" + proceso[i].tiempoEjecucion + "\t"
          + proceso[i].prioridad);
    }

    // menu
    boolean monoTarea;
    boolean monoProceso;
    int a;

    // pregunta si es mono tarea
    do {
      System.out.println("\n1.-mono tarea \n2.-multi tarea");
      a = leer.nextInt();
    } while (a < 1 || a > 2);
    if (a == 1) {
      monoTarea = true;
    } else {
      monoTarea = false;
    }

    // pregunta si es mono proceso
    do {
      System.out.println("\n1.-mono proceso \n2.-multi proceso");
      a = leer.nextInt();
    } while (a < 1 || a > 2);
    if (a == 1) {
      monoProceso = true;
    } else {
      monoProceso = false;
      System.out.println("\ningresa el numero de CPUs: ");
      a = leer.nextInt();
    }

    int algoritmo;
    // selecciona el algoritmo
    do {
      System.out.println(
          "\nselecciona un algoritmo:\n1.-T.exe(ligero)\tprioridad(alta)\tpip(ascendente)\n2.-T.exe(ligero)\tprioridad(alta)\tpip(descendente)\n3.-prioridad(alta)\tT.exe(ligero)\tpip(ascendente)\n4.-prioridad(alta)\tT.exe(ligero)\tpip(descendente)\n");
      algoritmo = leer.nextInt();
    } while (algoritmo < 1 || algoritmo > 4);
    // empezamos

    int[] tiempo = new int[a];
    int[] tiempoEspera = new int[a];
    for (int l = 0; l < a; l++) {
      tiempo[l] = 0;
      tiempoEspera[l] = 0;
    }
    int[] cola = new int[20];
    int numCola = 0;
    boolean fin = false;
    proyecto aux = new proyecto();
    System.out.println("tiempo\tpip\tTlle\tTexe\tPrioridad");
    switch (algoritmo) {
      case 1:
        while (fin == false) {
          for (int cpu = 0; cpu < a; cpu++) {
            // System.out.println(cpu + ": " + tiempoEspera[cpu]);
            if (tiempoEspera[cpu] > 0) {
              tiempoEspera[cpu]--;
            } else {
              // primer campo tiempo de expera
              // reinicia las variables
              aux.tiempoEjecucion = 2000;
              aux.prioridad = -10;
              for (int l = 0; l < k; l++) {
                // verifica que : tiempo de llegada sea <= que el tiempo y busca el tiempo menor
                // de los no finalizados
                if (proceso[l].tiempoLlegada <= tiempo[cpu] && proceso[l].tiempoEjecucion < aux.tiempoEjecucion
                    && proceso[l].finalizado == false) {
                  // cuando no es monotarea
                  if (monoTarea == false) {
                    boolean enCola = false;
                    for (int m = 0; m < numCola; m++) {
                      if (proceso[l].pip == cola[m]) {
                        enCola = true;
                      }
                    }
                    if (enCola == false) {
                      aux.pip = proceso[l].pip;
                      aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                      aux.prioridad = proceso[l].prioridad;
                      aux.finalizado = proceso[l].finalizado;
                      aux.tiempoLlegada = proceso[l].tiempoLlegada;
                    }
                  } else { // cuando es monotarea
                    aux.pip = proceso[l].pip;
                    aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                    aux.prioridad = proceso[l].prioridad;
                    aux.finalizado = proceso[l].finalizado;
                    aux.tiempoLlegada = proceso[l].tiempoLlegada;
                  }
                }
              }

              int temp = 0;
              boolean found = false;
              boolean enCola = false;
              aux.prioridad = -10;
              for (int l = 0; l < k; l++) {
                if (proceso[l].tiempoLlegada <= tiempo[cpu] && proceso[l].tiempoEjecucion == aux.tiempoEjecucion
                    && proceso[l].finalizado == false) {
                  if (monoTarea == true) {
                    // obtiene el de mayor prioridad
                    if (proceso[l].prioridad > aux.prioridad) {
                      aux.pip = proceso[l].pip;
                      aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                      aux.prioridad = proceso[l].prioridad;
                      aux.finalizado = proceso[l].finalizado;
                      aux.tiempoLlegada = proceso[l].tiempoLlegada;
                    }
                    // si prioridad es igual revisa el pip
                    if (proceso[l].prioridad == aux.prioridad) {
                      if (proceso[l].pip < aux.pip) {
                        aux.pip = proceso[l].pip;
                        aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                        aux.prioridad = proceso[l].prioridad;
                        aux.finalizado = proceso[l].finalizado;
                        aux.tiempoLlegada = proceso[l].tiempoLlegada;
                      }
                    }
                  }

                  // System.out.println("pip " + proceso[l].pip);
                  if (monoTarea == false) {
                    enCola = false;
                    for (int m = 0; m < numCola; m++) {
                      // System.out.println("cola " + cola[m]);
                      if (cola[m] == proceso[l].pip) {
                        found = true;
                        enCola = true;
                      } else {
                        found = false;
                      }
                    }
                    if (enCola == false) {
                      // obtiene el de mayor prioridad
                      if (proceso[l].prioridad > aux.prioridad) {
                        aux.pip = proceso[l].pip;
                        aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                        aux.prioridad = proceso[l].prioridad;
                        aux.finalizado = proceso[l].finalizado;
                        aux.tiempoLlegada = proceso[l].tiempoLlegada;
                      }
                      // si prioridad es igual revisa el pip
                      if (proceso[l].prioridad == aux.prioridad) {
                        if (proceso[l].pip < aux.pip) {
                          aux.pip = proceso[l].pip;
                          aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                          aux.prioridad = proceso[l].prioridad;
                          aux.finalizado = proceso[l].finalizado;
                          aux.tiempoLlegada = proceso[l].tiempoLlegada;
                        }
                      }
                    }
                  }
                  if (found == false) {
                    temp++;
                  }
                }
              }
              // para pruebas
              // System.out.println("temp " + temp);
              // para pruebas
              // System.out.println("aux pip: " + aux.pip);
              // System.out.println("aux Texe: " + aux.tiempoEjecucion);
              if (temp == 0) {
                if (cola[0] == 1000) {
                  System.out.println("CPU" + cpu + ":" + tiempo[cpu] + "\t- - - - - -");
                  tiempo[cpu]++;
                }
                cola[0] = 1000;
                numCola = 0;
                if (monoTarea == false && a !=1) {
                  // System.out.println("CPU" + cpu + ":" + tiempo[cpu] + "\t- - - - - -");
                  tiempo[cpu]++;
                }
              } else { // existe
                // empieza a buscar
                for (int l = 0; l < k; l++) {
                  // cuando encuentra el proceso
                  if (proceso[l].pip == aux.pip) {
                    if (monoTarea == true) {
                      for (int m = 0; m < proceso[l].tiempoEjecucion; m++) {
                        System.out.println(
                            "CPU" + cpu + ":" + tiempo[cpu] + "\t" + proceso[l].pip + "\t" + proceso[l].tiempoLlegada
                                + "\t" + (proceso[l].tiempoEjecucion - m) + "\t" + proceso[l].prioridad);
                        tiempo[cpu]++;
                      }
                      tiempoEspera[cpu] += proceso[l].tiempoEjecucion;
                      // System.out.println(tiempoEspera[cpu]);
                      proceso[l].tiempoEjecucion = 0;
                      proceso[l].finalizado = true;
                    } else { // si no es monotarea
                      System.out.println("CPU" + cpu + ":" + tiempo[cpu] + "\t" + proceso[l].pip + "\t"
                          + proceso[l].tiempoLlegada + "\t" + proceso[l].tiempoEjecucion + "\t" + proceso[l].prioridad);
                      tiempo[cpu]++;
                      cola[numCola] = proceso[l].pip;
                      numCola++;
                      proceso[l].tiempoEjecucion = proceso[l].tiempoEjecucion - 1;
                      aux.tiempoEjecucion = 2000;
                      aux.prioridad = -10;
                      if (proceso[l].tiempoEjecucion == 0) {
                        proceso[l].finalizado = true;
                      }
                    }
                  }
                }
              }
            }

          }

          // fin
          fin = true;
          for (int l = 0; l < k; l++) {
            if (proceso[l].finalizado == false) {
              fin = false;
            }
          }
        }
        break;
      case 2:
        while (fin == false) {
          for (int cpu = 0; cpu < a; cpu++) {
            // System.out.println(cpu + ": " + tiempoEspera[cpu]);
            if (tiempoEspera[cpu] > 0) {
              tiempoEspera[cpu]--;
            } else {
              // primer campo tiempo de expera
              // reinicia las variables
              aux.tiempoEjecucion = 2000;
              aux.prioridad = -10;
              for (int l = 0; l < k; l++) {
                // verifica que : tiempo de llegada sea <= que el tiempo y busca el tiempo menor
                // de los no finalizados
                if (proceso[l].tiempoLlegada <= tiempo[cpu] && proceso[l].tiempoEjecucion < aux.tiempoEjecucion
                    && proceso[l].finalizado == false) {
                  // cuando no es monotarea
                  if (monoTarea == false) {
                    boolean enCola = false;
                    for (int m = 0; m < numCola; m++) {
                      if (proceso[l].pip == cola[m]) {
                        enCola = true;
                      }
                    }
                    if (enCola == false) {
                      aux.pip = proceso[l].pip;
                      aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                      aux.prioridad = proceso[l].prioridad;
                      aux.finalizado = proceso[l].finalizado;
                      aux.tiempoLlegada = proceso[l].tiempoLlegada;
                    }
                  } else { // cuando es monotarea
                    aux.pip = proceso[l].pip;
                    aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                    aux.prioridad = proceso[l].prioridad;
                    aux.finalizado = proceso[l].finalizado;
                    aux.tiempoLlegada = proceso[l].tiempoLlegada;
                  }
                }
              }

              // para pruebas
              // System.out.println("aux pip: " + aux.pip);
              // System.out.println("aux Texe: " + aux.tiempoEjecucion);

              int temp = 0;
              boolean found = false;
              aux.prioridad = -10;
              for (int l = 0; l < k; l++) {
                if (proceso[l].tiempoLlegada <= tiempo[cpu] && proceso[l].tiempoEjecucion == aux.tiempoEjecucion
                    && proceso[l].finalizado == false) {
                  // obtiene el de mayor prioridad
                  if (proceso[l].prioridad > aux.prioridad) {
                    aux.pip = proceso[l].pip;
                    aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                    aux.prioridad = proceso[l].prioridad;
                    aux.finalizado = proceso[l].finalizado;
                    aux.tiempoLlegada = proceso[l].tiempoLlegada;
                  }
                  // si prioridad es igual revisa el pip
                  if (proceso[l].prioridad == aux.prioridad) {
                    if (proceso[l].pip > aux.pip) {
                      aux.pip = proceso[l].pip;
                      aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                      aux.prioridad = proceso[l].prioridad;
                      aux.finalizado = proceso[l].finalizado;
                      aux.tiempoLlegada = proceso[l].tiempoLlegada;
                    }
                  }
                  // System.out.println("pip " + proceso[l].pip);
                  if (monoTarea == false) {
                    for (int m = 0; m < numCola; m++) {
                      // System.out.println("cola " + cola[m]);
                      if (cola[m] == proceso[l].pip) {
                        found = true;
                      } else {
                        found = false;
                      }
                    }
                  }
                  if (found == false) {
                    temp++;
                  }
                }
              }
              // para pruebas
              // System.out.println("temp " + temp);
              if (temp == 0) {
                if (cola[0] == 1000) {
                  System.out.println("CPU" + cpu + ":" + tiempo[cpu] + "\t- - - - - -");
                  tiempo[cpu]++;
                }
                cola[0] = 1000;
                numCola = 0;
              } else { // existe
                // empieza a buscar
                for (int l = 0; l < k; l++) {
                  // cuando encuentra el proceso
                  if (proceso[l].pip == aux.pip) {
                    if (monoTarea == true) {
                      for (int m = 0; m < proceso[l].tiempoEjecucion; m++) {
                        System.out.println(
                            "CPU" + cpu + ":" + tiempo[cpu] + "\t" + proceso[l].pip + "\t" + proceso[l].tiempoLlegada
                                + "\t" + (proceso[l].tiempoEjecucion - m) + "\t" + proceso[l].prioridad);
                        tiempo[cpu]++;
                      }
                      tiempoEspera[cpu] += proceso[l].tiempoEjecucion;
                      // System.out.println(tiempoEspera[cpu]);
                      proceso[l].tiempoEjecucion = 0;
                      proceso[l].finalizado = true;
                    } else { // si no es monotarea
                      System.out.println("CPU" + cpu + ":" + tiempo[cpu] + "\t" + proceso[l].pip + "\t"
                          + proceso[l].tiempoLlegada + "\t" + proceso[l].tiempoEjecucion + "\t" + proceso[l].prioridad);
                      tiempo[cpu]++;
                      cola[numCola] = proceso[l].pip;
                      numCola++;
                      proceso[l].tiempoEjecucion = proceso[l].tiempoEjecucion - 1;
                      aux.tiempoEjecucion = 2000;
                      aux.prioridad = -10;
                      if (proceso[l].tiempoEjecucion == 0) {
                        proceso[l].finalizado = true;
                      }
                    }
                  }
                }
              }
            }

          }

          // fin
          fin = true;
          for (int l = 0; l < k; l++) {
            if (proceso[l].finalizado == false) {
              fin = false;
            }
          }
        }
        break;
      case 3:
        while (fin == false) {
          for (int cpu = 0; cpu < a; cpu++) {
            // System.out.println(cpu + ": " + tiempoEspera[cpu]);
            if (tiempoEspera[cpu] > 0) {
              tiempoEspera[cpu]--;
            } else {
              // primer campo tiempo de expera
              // reinicia las variables
              aux.tiempoEjecucion = 2000;
              aux.prioridad = -10;
              for (int l = 0; l < k; l++) {
                // verifica que : tiempo de llegada sea <= que el tiempo y busca el tiempo menor
                // de los no finalizados
                if (proceso[l].tiempoLlegada <= tiempo[cpu] && proceso[l].prioridad > aux.prioridad
                    && proceso[l].finalizado == false) {
                  // cuando no es monotarea
                  if (monoTarea == false) {
                    boolean enCola = false;
                    for (int m = 0; m < numCola; m++) {
                      if (proceso[l].pip == cola[m]) {
                        enCola = true;
                      }
                    }
                    if (enCola == false) {
                      aux.pip = proceso[l].pip;
                      aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                      aux.prioridad = proceso[l].prioridad;
                      aux.finalizado = proceso[l].finalizado;
                      aux.tiempoLlegada = proceso[l].tiempoLlegada;
                    }
                  } else { // cuando es monotarea
                    aux.pip = proceso[l].pip;
                    aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                    aux.prioridad = proceso[l].prioridad;
                    aux.finalizado = proceso[l].finalizado;
                    aux.tiempoLlegada = proceso[l].tiempoLlegada;
                  }
                }
              }

              // para pruebas
              // System.out.println("aux pip: " + aux.pip);
              // System.out.println("aux Texe: " + aux.tiempoEjecucion);

              int temp = 0;
              boolean found = false;
              aux.tiempoEjecucion = 2000;
              for (int l = 0; l < k; l++) {
                if (proceso[l].tiempoLlegada <= tiempo[cpu] && proceso[l].prioridad == aux.prioridad
                    && proceso[l].finalizado == false) {
                  // obtiene el de mayor prioridad
                  if (proceso[l].tiempoEjecucion < aux.tiempoEjecucion) {
                    aux.pip = proceso[l].pip;
                    aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                    aux.prioridad = proceso[l].prioridad;
                    aux.finalizado = proceso[l].finalizado;
                    aux.tiempoLlegada = proceso[l].tiempoLlegada;
                  }
                  // si prioridad es igual revisa el pip
                  if (proceso[l].tiempoEjecucion == aux.tiempoEjecucion) {
                    if (proceso[l].pip < aux.pip) {
                      aux.pip = proceso[l].pip;
                      aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                      aux.prioridad = proceso[l].prioridad;
                      aux.finalizado = proceso[l].finalizado;
                      aux.tiempoLlegada = proceso[l].tiempoLlegada;
                    }
                  }
                  // System.out.println("pip " + proceso[l].pip);
                  if (monoTarea == false) {
                    for (int m = 0; m < numCola; m++) {
                      // System.out.println("cola " + cola[m]);
                      if (cola[m] == proceso[l].pip) {
                        found = true;
                      } else {
                        found = false;
                      }
                    }
                  }
                  if (found == false) {
                    temp++;
                  }
                }
              }
              // para pruebas
              // System.out.println("temp " + temp);
              if (temp == 0) {
                if (cola[0] == 1000) {
                  System.out.println("CPU" + cpu + ":" + tiempo[cpu] + "\t- - - - - -");
                  tiempo[cpu]++;
                }
                cola[0] = 1000;
                numCola = 0;
              } else { // existe
                // empieza a buscar
                for (int l = 0; l < k; l++) {
                  // cuando encuentra el proceso
                  if (proceso[l].pip == aux.pip) {
                    if (monoTarea == true) {
                      for (int m = 0; m < proceso[l].tiempoEjecucion; m++) {
                        System.out.println(
                            "CPU" + cpu + ":" + tiempo[cpu] + "\t" + proceso[l].pip + "\t" + proceso[l].tiempoLlegada
                                + "\t" + (proceso[l].tiempoEjecucion - m) + "\t" + proceso[l].prioridad);
                        tiempo[cpu]++;
                      }
                      tiempoEspera[cpu] += proceso[l].tiempoEjecucion;
                      // System.out.println(tiempoEspera[cpu]);
                      proceso[l].tiempoEjecucion = 0;
                      proceso[l].finalizado = true;
                    } else { // si no es monotarea
                      System.out.println("CPU" + cpu + ":" + tiempo[cpu] + "\t" + proceso[l].pip + "\t"
                          + proceso[l].tiempoLlegada + "\t" + proceso[l].tiempoEjecucion + "\t" + proceso[l].prioridad);
                      tiempo[cpu]++;
                      cola[numCola] = proceso[l].pip;
                      numCola++;
                      proceso[l].tiempoEjecucion = proceso[l].tiempoEjecucion - 1;
                      aux.tiempoEjecucion = 2000;
                      aux.prioridad = -10;
                      if (proceso[l].tiempoEjecucion == 0) {
                        proceso[l].finalizado = true;
                      }
                    }
                  }
                }
              }
            }

          }

          // fin
          fin = true;
          for (int l = 0; l < k; l++) {
            if (proceso[l].finalizado == false) {
              fin = false;
            }
          }
        }
        break;
      case 4:
        while (fin == false) {
          for (int cpu = 0; cpu < a; cpu++) {
            // System.out.println(cpu + ": " + tiempoEspera[cpu]);
            if (tiempoEspera[cpu] > 0) {
              tiempoEspera[cpu]--;
            } else {
              // primer campo tiempo de expera
              // reinicia las variables
              aux.tiempoEjecucion = 2000;
              aux.prioridad = -10;
              for (int l = 0; l < k; l++) {
                // verifica que : tiempo de llegada sea <= que el tiempo y busca el tiempo menor
                // de los no finalizados
                if (proceso[l].tiempoLlegada <= tiempo[cpu] && proceso[l].prioridad > aux.prioridad
                    && proceso[l].finalizado == false) {
                  // cuando no es monotarea
                  if (monoTarea == false) {
                    boolean enCola = false;
                    for (int m = 0; m < numCola; m++) {
                      if (proceso[l].pip == cola[m]) {
                        enCola = true;
                      }
                    }
                    if (enCola == false) {
                      aux.pip = proceso[l].pip;
                      aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                      aux.prioridad = proceso[l].prioridad;
                      aux.finalizado = proceso[l].finalizado;
                      aux.tiempoLlegada = proceso[l].tiempoLlegada;
                    }
                  } else { // cuando es monotarea
                    aux.pip = proceso[l].pip;
                    aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                    aux.prioridad = proceso[l].prioridad;
                    aux.finalizado = proceso[l].finalizado;
                    aux.tiempoLlegada = proceso[l].tiempoLlegada;
                  }
                }
              }

              // para pruebas
              // System.out.println("aux pip: " + aux.pip);
              // System.out.println("aux Texe: " + aux.tiempoEjecucion);

              int temp = 0;
              boolean found = false;
              aux.tiempoEjecucion = 2000;
              for (int l = 0; l < k; l++) {
                if (proceso[l].tiempoLlegada <= tiempo[cpu] && proceso[l].prioridad == aux.prioridad
                    && proceso[l].finalizado == false) {
                  // obtiene el de mayor prioridad
                  if (proceso[l].tiempoEjecucion < aux.tiempoEjecucion) {
                    aux.pip = proceso[l].pip;
                    aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                    aux.prioridad = proceso[l].prioridad;
                    aux.finalizado = proceso[l].finalizado;
                    aux.tiempoLlegada = proceso[l].tiempoLlegada;
                  }
                  // si prioridad es igual revisa el pip
                  if (proceso[l].tiempoEjecucion == aux.tiempoEjecucion) {
                    if (proceso[l].pip > aux.pip) {
                      aux.pip = proceso[l].pip;
                      aux.tiempoEjecucion = proceso[l].tiempoEjecucion;
                      aux.prioridad = proceso[l].prioridad;
                      aux.finalizado = proceso[l].finalizado;
                      aux.tiempoLlegada = proceso[l].tiempoLlegada;
                    }
                  }
                  // System.out.println("pip " + proceso[l].pip);
                  if (monoTarea == false) {
                    for (int m = 0; m < numCola; m++) {
                      // System.out.println("cola " + cola[m]);
                      if (cola[m] == proceso[l].pip) {
                        found = true;
                      } else {
                        found = false;
                      }
                    }
                  }
                  if (found == false) {
                    temp++;
                  }
                }
              }
              // para pruebas
              // System.out.println("temp " + temp);
              if (temp == 0) {
                if (cola[0] == 1000) {
                  System.out.println("CPU" + cpu + ":" + tiempo[cpu] + "\t- - - - - -");
                  tiempo[cpu]++;
                }
                cola[0] = 1000;
                numCola = 0;
              } else { // existe
                // empieza a buscar
                for (int l = 0; l < k; l++) {
                  // cuando encuentra el proceso
                  if (proceso[l].pip == aux.pip) {
                    if (monoTarea == true) {
                      for (int m = 0; m < proceso[l].tiempoEjecucion; m++) {
                        System.out.println(
                            "CPU" + cpu + ":" + tiempo[cpu] + "\t" + proceso[l].pip + "\t" + proceso[l].tiempoLlegada
                                + "\t" + (proceso[l].tiempoEjecucion - m) + "\t" + proceso[l].prioridad);
                        tiempo[cpu]++;
                      }
                      tiempoEspera[cpu] += proceso[l].tiempoEjecucion;
                      // System.out.println(tiempoEspera[cpu]);
                      proceso[l].tiempoEjecucion = 0;
                      proceso[l].finalizado = true;
                    } else { // si no es monotarea
                      System.out.println("CPU" + cpu + ":" + tiempo[cpu] + "\t" + proceso[l].pip + "\t"
                          + proceso[l].tiempoLlegada + "\t" + proceso[l].tiempoEjecucion + "\t" + proceso[l].prioridad);
                      tiempo[cpu]++;
                      cola[numCola] = proceso[l].pip;
                      numCola++;
                      proceso[l].tiempoEjecucion = proceso[l].tiempoEjecucion - 1;
                      aux.tiempoEjecucion = 2000;
                      aux.prioridad = -10;
                      if (proceso[l].tiempoEjecucion == 0) {
                        proceso[l].finalizado = true;
                      }
                    }
                  }
                }
              }
            }

          }

          // fin
          fin = true;
          for (int l = 0; l < k; l++) {
            if (proceso[l].finalizado == false) {
              fin = false;
            }
          }
        }
        break;
    }
    // fin
    obj.close();
    leer.close();

  }

}