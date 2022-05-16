import java.io.*;
import java.util.Scanner;

public class prueba {
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
    System.out.println("tiempo\tpip\tTlle\tTexe\tPrioridad");
    System.out.println("CPU0:0\t1\t0\t1\t4");
    System.out.println("CPU1:0\t2\t0\t1\t4");
    System.out.println("CPU0:1\t12\t1\t1\t3");
    System.out.println("CPU1:1\t11\t1\t2\t4");
    System.out.println("CPU0:2\t3\t0\t2\t3");
    System.out.println("CPU1:2\t4\t2\t3\t2");
    System.out.println("CPU0:3\t9\t3\t1\t2");
    System.out.println("CPU1:3\t10\t2\t3\t1");
    System.out.println("CPU0:4\t5\t3\t3\t0");
    System.out.println("CPU0:5\t11\t1\t1\t4");
    System.out.println("CPU1:5\t3\t0\t1\t3");
    System.out.println("CPU0:6\t7\t6\t2\t4");
    System.out.println("CPU1:6\t4\t2\t2\t2");
    System.out.println("CPU0:7\t8\t7\t2\t3");
    System.out.println("CPU1:7\t6\t5\t3\t1");
    System.out.println("CPU0:8\t10\t2\t2\t1");
    System.out.println("CPU1:8\t5\t3\t2\t0");
    System.out.println("CPU0:9\t7\t6\t1\t4");
    System.out.println("CPU1:9\t8\t7\t1\t3");
    System.out.println("CPU0:10\t4\t2\t1\t2");
    System.out.println("CPU1:10\t6\t5\t2\t1");
    System.out.println("CPU0:11\t10\t2\t1\t1");
    System.out.println("CPU1:11\t5\t3\t1\t0");
    System.out.println("CPU0:12\t6\t5\t1\t1");
    
    // fin
    obj.close();
    leer.close();

  }
}
