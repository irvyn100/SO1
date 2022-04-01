import java.io.*;

public class proyecto {
  // atributos
  int pip;
  int tiempoLlegada;
  int tiempoEjecucion;
  int prioridad;

  // metodo
  public static void main(String[] args) throws Exception {
    proyecto proceso[] = new proyecto[20];
    int i,k,j;
    int[] tem = new int[5];;
    String prueba = "";
    File doc = new File("E:/irvyn/Documents/GitHub/SO1/proyecto1/datos.txt");

    BufferedReader obj = new BufferedReader(new FileReader(doc));

    // String strng;
    // System.out.println(i);
    j=0;
    k=0;
    while ((i = obj.read()) != -1){
      if(i == 59){
        // -1 porque j se le suma uno entonces j se vuelve =0
        j=-1;

        // crea proceso
        proceso[k]=new proyecto();
        proceso[k].pip = tem[0];
        proceso[k].tiempoLlegada = tem[1];
        proceso[k].tiempoEjecucion = tem[2];
        proceso[k].prioridad = tem[3];

        k++;
      }
        if (i != 44 && i != 59) {
          i = i - 48;
          prueba += i+"";
  
          tem[j] = Integer.parseInt(prueba);   
        }else{
          j++;
          prueba = "";
        }
    }

    System.out.println("pip\tTlle\tTexe\tprioridad");
    for(i=0; i<k; i++){
      System.out.println(proceso[i].pip + "\t" + proceso[i].tiempoLlegada + "\t" + proceso[i].tiempoEjecucion + "\t" + proceso[i].prioridad);
    }

    obj.close();
  }
}