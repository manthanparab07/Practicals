import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.io.IOException;
import java.util.Scanner;
import java.net.InetAddress;



public class Server{

    public static void main(String args[]){
        
        try{

            DatagramSocket dsock = new DatagramSocket( 8080 , InetAddress.getByName("127.0.0.1") );
            byte[] arr = new byte[1000];

            DatagramPacket dpack_send , dpack_recv ;
            
            Scanner inp = new Scanner(System.in);

            while(true){
                
                clearBytes(arr);            // to remove data from previous operation from 
                dpack_recv = new DatagramPacket( arr , arr.length );
                dsock.receive(dpack_recv);
                System.out.println("Client : " + new String(arr) );
                
                clearBytes(arr);            // to remove data from previous operation from 
                System.out.print("Enter Message : ");
                arr = (inp.nextLine()).getBytes();
                dpack_send =  new DatagramPacket( arr , arr.length , dpack_recv.getAddress() , dpack_recv.getPort() );
                dsock.send(dpack_send);

            }

        }catch(IOException e){
            System.out.println("Error : " + e );
        }

    }

    public static void clearBytes(byte[] arr){
        for( int i = 0 ; i < arr.length ; i ++ )
            arr[i] = '\0' ;
    }

}
